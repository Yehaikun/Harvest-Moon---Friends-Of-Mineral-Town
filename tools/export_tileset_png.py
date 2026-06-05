#!/usr/bin/env python3
"""导出 FOMT tileset 为 PNG，可导入 Tiled（不带编号，原尺寸 8x8）"""

import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from decompress import unpack
from PIL import Image

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    map_id = int(sys.argv[2]) if len(sys.argv) > 2 else 2

    rom = bytearray(Path(rom_path).read_bytes())

    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    img_ptr = struct.unpack_from('<I', data, 0)[0] & 0x1FFFFFF
    pal1_ptr = struct.unpack_from('<I', data, 4)[0] & 0x1FFFFFF
    tiles1_ptr = struct.unpack_from('<I', data, 0x0C)[0] & 0x1FFFFFF
    w = struct.unpack_from('<H', data, 0x20)[0]
    h = struct.unpack_from('<H', data, 0x22)[0]

    # 解压
    tiles = unpack(rom[img_ptr:])
    tiles = tiles[0] if isinstance(tiles, tuple) else tiles
    pal = unpack(rom[pal1_ptr:])
    pal = pal[0] if isinstance(pal, tuple) else pal
    tilemap = unpack(rom[tiles1_ptr:])
    tilemap = tilemap[0] if isinstance(tilemap, tuple) else tilemap
    tilemap = struct.unpack(f'<{w*h}H', tilemap)

    # 调色板：15 组，每组 16 色（BGR555）
    pals = []
    for bank in range(15):
        cols = []
        for i in range(16):
            off2 = (bank * 16 + i) * 2
            if off2 + 2 <= len(pal):
                val = struct.unpack_from('<H', pal, off2)[0]
                r = (val & 0x1F) << 3
                g = ((val >> 5) & 0x1F) << 3
                b = ((val >> 10) & 0x1F) << 3
                cols.append((r|r>>5, g|g>>5, b|b>>5, 255))
            else:
                cols.append((0,0,0,0))
        pals.append(cols)

    # 统计每个 tile 最常用的 palette bank
    pal_usage = {}
    for se in tilemap:
        ti = se & 0x3FF
        bank = (se >> 12) & 0xF
        pal_usage.setdefault(ti, {})
        pal_usage[ti][bank] = pal_usage[ti].get(bank, 0) + 1
    tile_pal = {ti: max(banks, key=banks.get) for ti, banks in pal_usage.items()}

    tile_count = len(tiles) // 32
    side = 16  # 每行 16 个 tile
    rows = (tile_count + side - 1) // side

    img = Image.new('RGBA', (side * 8, rows * 8), (200,200,200,255))

    for ti in range(tile_count):
        tx = (ti % side) * 8
        ty = (ti // side) * 8
        t = tiles[ti*32:(ti+1)*32]

        bank = tile_pal.get(ti, 0)
        if bank >= len(pals): bank = 0
        cols = pals[bank]

        for py in range(8):
            for px in range(8):
                byte_val = t[py*4 + px//2]
                idx = byte_val & 0xF if px % 2 == 0 else (byte_val >> 4) & 0xF
                clr = cols[idx] if idx < len(cols) else (255,0,255)
                img.putpixel((tx + px, ty + py), clr)

    out = f'map{map_id}_tileset.png'
    img.save(out)
    print(f'✅ 已导出 {out}')
    print(f'   尺寸: {side*8} × {rows*8} 像素, {tile_count} 个瓦片')
    print(f'')
    print(f'在 Tiled 中使用:')
    print(f'  New Tileset → Based on Tileset Image → 选此文件')
    print(f'  Tile Width: 8, Tile Height: 8, 边距 0, 间距 0')
    print(f'')
    print(f'然后 New Map → Tile Size: 8×8, 画出建筑')
    print(f'画完后 File → Export As → CSV (.csv)')

if __name__ == '__main__':
    main()
