#!/usr/bin/env python3
"""Tiled CSV → FOMT tilemap 转换器

流程：
  1. 在 Tiled 里新建地图，用 tile 索引号画建筑
  2. 导出为 CSV（File → Export As → CSV）
  3. 运行本脚本写入 ROM

用法：
  python3 tools/tiled_to_fomt.py fomt.gba --map 2 --layer 1 --csv house.csv

参数：
  --map      目标地图 ID（2=农场）
  --layer    图层（1/2/3，默认1）
  --csv      从 Tiled 导出的 CSV 文件
  --x-offset CSV 左上角对应地图的 X 坐标
  --y-offset CSV 左上角对应地图的 Y 坐标
  --terrain  同时设置碰撞（--terrain blocked 设置阻挡区域）
"""

import struct, sys, csv
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from patch_farm_expansion import make_lzss4_blob, find_free_space
from decompress import unpack

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000
LAYER_OFFSETS = [0x0C, 0x10, 0x14]  # packed_tiles1/2/3 offsets in MapData

def read_mapdata(rom, map_id):
    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    return {
        'img_ptr': struct.unpack_from('<I', data, 0)[0],
        'tiles_ptrs': [struct.unpack_from('<I', data, lo)[0] for lo in LAYER_OFFSETS],
        'terrain_info': struct.unpack_from('<I', data, 0x18)[0],
        'terrain_map': struct.unpack_from('<I', data, 0x1C)[0],
        'width': struct.unpack_from('<H', data, 0x20)[0],
        'height': struct.unpack_from('<H', data, 0x22)[0],
    }

def write_mapdata_entry(rom, map_id, field_name, value):
    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    FIELD_OFFSETS = {
        'img_ptr': 0, 'pal1_ptr': 4, 'pal2_ptr': 8,
        'tiles1_ptr': 0x0C, 'tiles2_ptr': 0x10, 'tiles3_ptr': 0x14,
        'terrain_info': 0x18, 'terrain_map': 0x1C,
        'width': 0x20, 'height': 0x22, 'is_interior': 0x24,
    }
    fo = FIELD_OFFSETS.get(field_name)
    if fo is not None:
        if field_name in ('width', 'height', 'is_interior'):
            struct.pack_into('<H', rom, off + fo, value)
        else:
            struct.pack_into('<I', rom, off + fo, value)

def write_tilemap_entry(rom, map_id, layer, new_rom_ptr, compressed_data):
    """写入新的 tilemap 并更新 MapData 指针"""
    # 写入压缩数据
    rom[new_rom_ptr:new_rom_ptr + len(compressed_data)] = compressed_data
    # 更新 MapData 指针
    field_map = {1: 'tiles1_ptr', 2: 'tiles2_ptr', 3: 'tiles3_ptr'}
    write_mapdata_entry(rom, map_id, field_map[layer], new_rom_ptr + GBA_BASE)

def main():
    import argparse
    parser = argparse.ArgumentParser(description='Tiled CSV → FOMT tilemap')
    parser.add_argument('rom', help='fomt.gba 路径')
    parser.add_argument('--map', type=int, required=True, help='地图 ID')
    parser.add_argument('--layer', type=int, default=1, choices=[1,2,3], help='图层')
    parser.add_argument('--csv', required=True, help='Tiled 导出的 CSV')
    parser.add_argument('--x-offset', type=int, default=0, help='CSV 在地图上的 X 偏移')
    parser.add_argument('--y-offset', type=int, default=0, help='CSV 在地图上的 Y 偏移')
    parser.add_argument('--terrain', choices=['blocked', 'passable'], help='同时设置碰撞')
    args = parser.parse_args()

    # 读取 CSV
    with open(args.csv) as f:
        reader = csv.reader(f)
        csv_data = [list(map(int, row)) for row in reader]

    csv_h = len(csv_data)
    csv_w = len(csv_data[0])
    print(f"CSV 尺寸: {csv_w}x{csv_h} tiles")

    # 读取 ROM
    rom = bytearray(Path(args.rom).read_bytes())
    md = read_mapdata(rom, args.map)
    map_w, map_h = md['width'], md['height']
    print(f"地图 {args.map} 尺寸: {map_w}x{map_h} tiles")

    # 检查边界
    if args.x_offset + csv_w > map_w or args.y_offset + csv_h > map_h:
        print(f"❌ CSV 超出地图边界！")
        sys.exit(1)

    # 解压当前的 tilemap
    tile_ptr = md['tiles_ptrs'][args.layer - 1]
    tile_off = tile_ptr & 0x1FFFFFF

    try:
        raw_data = unpack(rom[tile_off:])
    except:
        print(f"⚠ 解压失败，尝试读取原始数据")
        raw_data = rom[tile_off:tile_off + map_w * map_h * 2]

    # 原始数据是 16 位 screen entry 数组
    tilemap = list(struct.unpack_from(f'<{map_w * map_h}H', raw_data))

    # 把 CSV 写进去
    modified = tilemap.copy()
    for y in range(csv_h):
        for x in range(csv_w):
            idx = (args.y_offset + y) * map_w + (args.x_offset + x)
            tile_id = csv_data[y][x]
            # 保留高位属性（翻转、调色板），只改低 10 位 tile 索引
            modified[idx] = (modified[idx] & 0xFC00) | (tile_id & 0x3FF)

    # 重新压缩
    new_layer_data = struct.pack(f'<{len(modified)}H', *modified)
    compressed = make_lzss4_blob(new_layer_data)

    # 找空余空间写入
    free_start = find_free_space(rom, len(compressed))
    if not free_start:
        print(f"❌ ROM 空余空间不足！需要 {len(compressed)} 字节")
        sys.exit(1)

    write_tilemap_entry(rom, args.map, args.layer, free_start, compressed)

    if args.terrain:
        # 设碰撞
        for y in range(csv_h):
            for x in range(csv_w):
                idx = (args.y_offset + y) * map_w + (args.x_offset + x)
                val = 1 if args.terrain == 'blocked' else 0
                # terrain_map 地址
                terrain_map_ptr = md['terrain_map'] & 0x1FFFFFF
                if terrain_map_ptr:
                    rom[terrain_map_ptr + idx] = val

    # 写回
    Path(args.rom).write_bytes(rom)
    print(f"✅ 已写入 {args.rom}")
    print(f"   地图 {args.map} 图层 {args.layer}: ({args.x_offset},{args.y_offset}) 处覆盖 {csv_w}x{csv_h}")
    if args.terrain:
        print(f"   碰撞设置: {args.terrain}")
    print("   编译: make -j2 fomt.gba && mgba fomt.gba")

if __name__ == '__main__':
    main()
