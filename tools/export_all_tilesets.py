#!/usr/bin/env python3
"""导出 ROM 中所有 31 套 tileset，去重后拼成一张大图"""

import struct, sys, hashlib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from decompress import unpack
from PIL import Image

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28

def bgr555_to_rgb(val):
    r = (val & 0x1F) << 3
    g = ((val >> 5) & 0x1F) << 3
    b = ((val >> 10) & 0x1F) << 3
    return (r|r>>5, g|g>>5, b|b>>5, 255)

def render_tile(tile_data, palette, tile_pal_bank=0):
    """render 8x8 tile with given 16-color palette"""
    cols = palette[tile_pal_bank] if tile_pal_bank < len(palette) else palette[0]
    pixels = []
    for py in range(8):
        for px in range(8):
            byte_val = tile_data[py*4 + px//2]
            idx = byte_val & 0xF if px % 2 == 0 else (byte_val >> 4) & 0xF
            pixels.append(cols[idx] if idx < len(cols) else (255,0,255))
    return pixels

def load_palettes(pal_data):
    """BGR555 bytearray → list of 16-color RGBA palettes"""
    pals = []
    for bank in range(15):
        cols = []
        for i in range(16):
            off = (bank*16+i)*2
            if off+2 <= len(pal_data):
                cols.append(bgr555_to_rgb(struct.unpack_from('<H', pal_data, off)[0]))
            else:
                cols.append((0,0,0,0))
        pals.append(cols)
    return pals

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = bytearray(Path(rom_path).read_bytes())

    # 收集所有唯一 tileset
    tilesets = {}  # img_ptr → {tiles, pals, maps}
    for mid in range(66):
        off = MAPDATA_TABLE + mid * ENTRY_SIZE
        data = rom[off:off+ENTRY_SIZE]
        img_ptr = struct.unpack_from('<I', data, 0)[0]
        pal1_ptr = struct.unpack_from('<I', data, 4)[0]
        w = struct.unpack_from('<H', data, 0x20)[0]
        h = struct.unpack_from('<H', data, 0x22)[0]
        if img_ptr == 0 or w == 0 or h == 0: continue

        if img_ptr not in tilesets:
            img_off = img_ptr & 0x1FFFFFF
            pal1_off = pal1_ptr & 0x1FFFFFF
            try:
                tiles = unpack(rom[img_off:])
                tiles = tiles[0] if isinstance(tiles, tuple) else tiles
                pal = unpack(rom[pal1_off:])
                pal = pal[0] if isinstance(pal, tuple) else pal
                pals = load_palettes(pal)
                tilesets[img_ptr] = {'tiles': tiles, 'pals': pals, 'maps': []}
            except:
                continue
        tilesets[img_ptr]['maps'].append(mid)

    print(f'共 {len(tilesets)} 套 tileset')

    # 渲染所有 tile，去重
    seen_hashes = {}  # pixel_hash → first_seen_info
    all_tiles = []    # (tileset_idx, tile_idx, pixels)

    for ts_idx, (ptr, ts) in enumerate(sorted(tilesets.items())):
        tile_count = len(ts['tiles']) // 32
        pals = ts['pals']
        print(f'  tileset {ts_idx}: {tile_count} tiles, 地图 {ts["maps"]}')

        # 从 tilemap 统计常用 palette bank（只对第一张关联地图）
        map_id = ts['maps'][0]
        off = MAPDATA_TABLE + map_id * ENTRY_SIZE
        data = rom[off:off+ENTRY_SIZE]
        t1_ptr = struct.unpack_from('<I', data, 0x0C)[0] & 0x1FFFFFF
        mw = struct.unpack_from('<H', data, 0x20)[0]
        mh = struct.unpack_from('<H', data, 0x22)[0]

        pal_usage = {}
        if t1_ptr and mw and mh:
            try:
                tm = unpack(rom[t1_ptr:])
                tm = tm[0] if isinstance(tm, tuple) else tm
                tm = struct.unpack(f'<{mw*mh}H', tm)
                for se in tm:
                    ti = se & 0x3FF
                    bank = (se >> 12) & 0xF
                    pal_usage.setdefault(ti, {})
                    pal_usage[ti][bank] = pal_usage[ti].get(bank, 0) + 1
            except:
                pass

        for ti in range(tile_count):
            t = ts['tiles'][ti*32:(ti+1)*32]
            if len(t) != 32: continue

            # 选最佳 palette bank
            best_bank = 0
            if ti in pal_usage:
                best_bank = max(pal_usage[ti], key=pal_usage[ti].get)
            else:
                # 试所有 bank，选颜色最丰富的
                max_colors = 0
                for bank in range(min(8, len(pals))):
                    colors_used = set()
                    for py in range(8):
                        for px in range(8):
                            byte_val = t[py*4 + px//2]
                            idx = byte_val & 0xF if px % 2 == 0 else (byte_val >> 4) & 0xF
                            colors_used.add(idx)
                    if len(colors_used) > max_colors:
                        max_colors = len(colors_used)
                        best_bank = bank

            pixels = render_tile(t, pals, best_bank)
            if best_bank >= len(pals):
                best_bank = 0

            # 取像素 hash 去重（flat bytes）
            px_bytes = bytes([c for px in pixels for c in px])
            h = hashlib.md5(px_bytes).hexdigest()
            if h not in seen_hashes:
                seen_hashes[h] = (ts_idx, ti)
                all_tiles.append((pixels, (ptr, ti, best_bank)))

    print(f'\n去重后: {len(all_tiles)} 个独立 tile')

    # 拼成大图（每行 32 个）
    per_row = 32
    rows = (len(all_tiles) + per_row - 1) // per_row
    img = Image.new('RGBA', (per_row * 8, rows * 8), (200,200,200,255))
    pixels_data = img.load()

    for i, (pixels, info) in enumerate(all_tiles):
        ox = (i % per_row) * 8
        oy = (i // per_row) * 8
        for py in range(8):
            for px in range(8):
                pixels_data[ox+px, oy+py] = pixels[py*8+px]

    out = 'all_tilesets.png'
    img.save(out)
    print(f'\n✅ 导出 {out}')
    print(f'   尺寸: {per_row*8} x {rows*8} 像素, {len(all_tiles)} 瓦片')
    print(f'   在 Tiled 中: New Tileset → 选此文件 → Tile 8×8')
    print(f'   导出 CSV 后用 tools/tiled_to_fomt.py 写入 ROM')

if __name__ == '__main__':
    main()
