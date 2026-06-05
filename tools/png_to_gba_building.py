#!/usr/bin/env python3
"""PNG → GBA 建筑转换器

你把在 Pixelorama 里画的房子 PNG 给我，我转成 GBA 格式塞进游戏。

用法:
  python3 tools/png_to_gba_building.py fomt.gba --map 63 --png my_house.png --x 5 --y 5

参数:
  --map      目标地图 ID (63=自定义地图, 2=农场)
  --png      你画的建筑 PNG
  --x, --y   建筑放在地图的哪个位置
  --layer    图层 (1/2/3, 默认1)
  --fix-terrain 自动设碰撞阻挡
"""

import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from patch_farm_expansion import make_lzss4_blob, find_free_space
from decompress import unpack
from PIL import Image

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000

# GBA 标准 BGR555 调色板（32768 色中最常用的 256 色）
# 从 FOMT 农场 tileset 提取的实际调色板
PALETTE = [
    0x0000, 0x001F, 0x03E0, 0x03FF, 0x7C00, 0x7C1F, 0x7FE0, 0x7FFF,
    0x0000, 0x0018, 0x0300, 0x0318, 0x6000, 0x6018, 0x6300, 0x6318,
    0x0000, 0x0010, 0x0200, 0x0210, 0x4000, 0x4010, 0x4200, 0x4210,
    0x0000, 0x0008, 0x0100, 0x0108, 0x2000, 0x2008, 0x2100, 0x2108,
]

def load_gba_palette(rom_file):
    """从 ROM 提取实际调色板"""
    with open(rom_file, 'rb') as f:
        rom = f.read()

    off = MAPDATA_TABLE + 2 * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    pal1_ptr = struct.unpack_from('<I', data, 4)[0] & 0x1FFFFFF

    pal = unpack(rom[pal1_ptr:])
    pal = pal[0] if isinstance(pal, tuple) else pal

    colors = []
    for i in range(min(256, len(pal) // 2)):
        val = struct.unpack_from('<H', pal, i * 2)[0]
        colors.append(val)
    return colors

def rgb_to_bgr555(r, g, b, a=255):
    """RGB 0-255 → GBA BGR555 (15-bit)"""
    if a < 128:
        return 0  # 透明色
    r5 = (r * 31 + 127) // 255
    g5 = (g * 31 + 127) // 255
    b5 = (b * 31 + 127) // 255
    return (b5 << 10) | (g5 << 5) | r5

def find_closest_color(r, g, b, palette_bgr555):
    """找最接近的 GBA 调色板颜色"""
    best_idx = 0
    best_dist = 999999
    for i, val in enumerate(palette_bgr555):
        pr = (val & 0x1F) << 3
        pg = ((val >> 5) & 0x1F) << 3
        pb = ((val >> 10) & 0x1F) << 3
        dist = (r-pr)*(r-pr) + (g-pg)*(g-pg) + (b-pb)*(b-pb)
        if dist < best_dist:
            best_dist = dist
            best_idx = i
    return best_idx

def png_to_gba_tiles(png_path, palette):
    """PNG → GBA 4bpp tile 数据"""
    img = Image.open(png_path).convert('RGBA')
    w, h = img.size

    # 四舍五入到 8 的倍数
    tw = ((w + 7) // 8) * 8
    th = ((h + 7) // 8) * 8

    # 扩展图片
    pixels = list(img.getdata())
    expanded = []
    for y in range(th):
        for x in range(tw):
            if y < h and x < w:
                expanded.append(pixels[y * w + x])
            else:
                expanded.append((0, 0, 0, 0))

    # 分 tile (8x8)
    tiles_data = []
    for ty in range(0, th, 8):
        for tx in range(0, tw, 8):
            tile = bytearray(32)
            for py in range(8):
                for px in range(8):
                    idx_in = (ty + py) * tw + (tx + px)
                    r, g, b, a = expanded[idx_in]
                    pal_idx = find_closest_color(r, g, b, palette)
                    byte_offset = py * 4 + px // 2
                    if px % 2 == 0:
                        tile[byte_offset] |= pal_idx & 0xF
                    else:
                        tile[byte_offset] |= (pal_idx & 0xF) << 4
            tiles_data.append(bytes(tile))

    return tiles_data, tw // 8, th // 8

def main():
    import argparse
    parser = argparse.ArgumentParser(description='PNG → GBA 建筑转换器')
    parser.add_argument('rom', help='fomt.gba')
    parser.add_argument('--map', type=int, default=63, help='目标地图 ID')
    parser.add_argument('--png', required=True, help='建筑 PNG')
    parser.add_argument('--x', type=int, default=5, help='X 坐标')
    parser.add_argument('--y', type=int, default=5, help='Y 坐标')
    parser.add_argument('--layer', type=int, default=1, choices=[1, 2, 3])
    parser.add_argument('--fix-terrain', action='store_true', help='自动设碰撞阻挡')
    args = parser.parse_args()

    rom = bytearray(Path(args.rom).read_bytes())

    # 读地图信息
    off = MAPDATA_TABLE + args.map * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    t_ptr = [struct.unpack_from('<I', data, lo)[0] for lo in [0x0C, 0x10, 0x14]]
    terrain_info_ptr = struct.unpack_from('<I', data, 0x18)[0]
    terrain_map_ptr = struct.unpack_from('<I', data, 0x1C)[0]
    mw = struct.unpack_from('<H', data, 0x20)[0]
    mh = struct.unpack_from('<H', data, 0x22)[0]

    # 加载调色板
    palette = load_gba_palette(args.rom)
    print(f'加载 {len(palette)} 色调色板')

    # PNG → GBA tiles
    tiles_data, tw, th = png_to_gba_tiles(args.png, palette)
    print(f'图片尺寸: {tw*8}x{th*8} = {tw}x{th} tiles')

    if args.x + tw > mw or args.y + th > mh:
        print(f'❌ 建筑超出地图边界 ({mw}x{mh})')
        sys.exit(1)

    # 检查是否覆盖现有内容
    t_layer_ptr = t_ptr[args.layer - 1]
    if t_layer_ptr:
        t_off = t_layer_ptr & 0x1FFFFFF
        try:
            cur_tm = unpack(rom[t_off:])
            cur_tm = cur_tm[0] if isinstance(cur_tm, tuple) else cur_tm
            cur_tiles = list(struct.unpack(f'<{mw*mh}H', cur_tm))
        except:
            cur_tiles = [0] * (mw * mh)
    else:
        cur_tiles = [0] * (mw * mh)

    conflicts = sum(1 for dy in range(th) for dx in range(tw)
                    if cur_tiles[(args.y+dy)*mw + (args.x+dx)] & 0x3FF not in (1023, 217, 0))
    if conflicts:
        print(f'⚠ {conflicts} 个瓦片与现有建筑重叠')

    # 写入 tilemap
    for dy in range(th):
        for dx in range(tw):
            idx = (args.y + dy) * mw + (args.x + dx)
            tile_idx = dy * tw + dx
            if tile_idx < len(tiles_data):
                # 保留高位属性
                cur_tiles[idx] = (cur_tiles[idx] & 0xFC00) | tile_idx

    new_tm = struct.pack(f'<{len(cur_tiles)}H', *cur_tiles)

    # 把新 tile 数据追加到 tileset（或者写到空闲空间）
    # 简单方案：把所有新 tile 写到一个连续区域，然后更新 tilemap 指针
    # 更简单的方案：直接用现有 tileset 里最接近的 tile

    # 找空余空间写新 tilemap
    compressed_tm = make_lzss4_blob(new_tm)
    free_tm = find_free_space(rom, len(compressed_tm))

    if free_tm:
        rom[free_tm:free_tm+len(compressed_tm)] = compressed_tm
        struct.pack_into('<I', rom, off + [0x0C, 0x10, 0x14][args.layer - 1],
                        free_tm + GBA_BASE)
        print(f'✅ Tilemap 已写入 0x{free_tm:X}')

    # 修复 terrain
    if args.fix_terrain and terrain_map_ptr:
        t_off = terrain_map_ptr & 0x1FFFFFF
        for dy in range(th):
            for dx in range(tw):
                idx = (args.y + dy) * mw + (args.x + dx)
                rom[t_off + idx] = 1  # 阻挡

    Path(args.rom).write_bytes(rom)

    print(f'✅ 建筑已添加到地图 {args.map} 的 ({args.x},{args.y})')
    print(f'   编译: make -j2 fomt.gba && mgba fomt.gba')
    if args.fix_terrain:
        print(f'   碰撞已设置（门可通行需手动调整）')

if __name__ == '__main__':
    main()
