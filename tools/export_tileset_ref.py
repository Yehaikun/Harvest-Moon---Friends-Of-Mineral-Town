#!/usr/bin/env python3
"""导出 tileset 参考图（tile 索引编号）和 CSV 地图布局"""

import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from decompress import unpack

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000

def read_mapdata(rom, map_id):
    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    return {
        'img_ptr': struct.unpack_from('<I', data, 0)[0],
        'tiles1_ptr': struct.unpack_from('<I', data, 0x0C)[0],
        'tiles2_ptr': struct.unpack_from('<I', data, 0x10)[0],
        'terrain_map': struct.unpack_from('<I', data, 0x1C)[0],
        'width': struct.unpack_from('<H', data, 0x20)[0],
        'height': struct.unpack_from('<H', data, 0x22)[0],
    }

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    map_id = int(sys.argv[2]) if len(sys.argv) > 2 else 2

    rom = bytearray(Path(rom_path).read_bytes())
    md = read_mapdata(rom, map_id)
    w, h = md['width'], md['height']

    print(f"地图 {map_id} ({w}x{h} tiles)")
    print()

    # 导出 tielmap layer 1 为 CSV（在 Tiled 里直接打开）
    tile_ptr = md['tiles1_ptr'] & 0x1FFFFFF
    try:
        raw_result = unpack(rom[tile_ptr:])
        if isinstance(raw_result, tuple):
            raw_bytes = bytes(raw_result[0])
        else:
            raw_bytes = bytes(raw_result)
    except Exception as e:
        print(f"解压失败: {e}")
        raw_bytes = rom[tile_ptr:tile_ptr + w * h * 2]

    tiles = list(struct.unpack_from(f'<{w*h}H', raw_bytes))

    # 只取低 10 位（tile index）
    indices = [t & 0x3FF for t in tiles]

    # 导出 CSV
    csv_path = f'map{map_id}_layer1.csv'
    with open(csv_path, 'w') as f:
        for y in range(h):
            f.write(','.join(str(indices[y*w + x]) for x in range(w)) + '\n')
    print(f"导出 {csv_path}（在 Tiled 中打开此文件可看到地图布局）")
    print()

    # 统计用了哪些独特 tile
    unique = sorted(set(indices))
    print(f"本图使用了 {len(unique)} 种不同的 tile")
    print(f"最小 tile ID: {unique[0]}, 最大 tile ID: {unique[-1]}")

    # 找最有用的 tile 类型
    print()
    print("=== 推荐 tile（看你地图有哪些）===")
    print("打开 mapX_layer1.csv 到 Tiled，查看当前地图布局")
    print("然后新建一个小 CSV 画房子，画完用 tiled_to_fomt.py 写入")

if __name__ == '__main__':
    main()
