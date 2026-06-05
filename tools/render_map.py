#!/usr/bin/env python3
"""Render a GBA tilemap as a colored grid (text-based preview).

Usage: python3 tools/render_map.py fomt.gba --map 63 --layer 1
"""
import struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from decompress import unpack

rom = bytearray(Path(sys.argv[1]).read_bytes())

def render_map(map_id, layer=1):
    off = 0x105EDC + map_id * 0x28
    data = rom[off:off+0x28]
    w = struct.unpack_from('<H', data, 0x20)[0]
    h = struct.unpack_from('<H', data, 0x22)[0]
    t1_ptr = struct.unpack_from('<I', data, [0x0C,0x10,0x14][layer-1])[0]
    if not t1_ptr:
        print("Empty layer"); return
    try:
        tiles, fmt, _ = unpack(bytes(rom), t1_ptr & 0x1FFFFFF)
    except:
        print("Decompress failed"); return

    # Print a compact text map showing tile index categories
    for y in range(min(h, 30)):
        line = ''
        for x in range(min(w, 80)):
            idx = (y*w + x)*2
            tile = tiles[idx] | (tiles[idx+1] << 8)
            tidx = tile & 0x3FF
            # Categorize tile index into character
            if tidx == 0: ch = '.'
            elif tidx < 100: ch = chr(ord('a') + (tidx % 26))
            elif tidx < 500: ch = chr(ord('A') + (tidx % 26))
            elif tidx < 800: ch = '#'
            else: ch = '@'
            line += ch
        print(line)
    if h > 30: print(f"... ({h-30} more rows)")
    if w > 80: print(f"... ({w-80} more columns)")

if __name__ == '__main__':
    if '--map' in sys.argv:
        i = sys.argv.index('--map')
        map_id = int(sys.argv[i+1])
        layer = 1
        if '--layer' in sys.argv:
            layer = int(sys.argv[sys.argv.index('--layer')+1])
        render_map(map_id, layer)
    else:
        for mid in [2, 63, 5]:
            print(f"\nMap {mid}:")
            render_map(mid)
