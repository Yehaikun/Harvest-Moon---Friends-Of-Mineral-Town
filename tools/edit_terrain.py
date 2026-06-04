#!/usr/bin/env python3
"""Terrain/collision editor for FoMT maps.

Usage:
  python3 tools/edit_terrain.py fomt.gba --map 2 --export terrain_map.txt
  python3 tools/edit_terrain.py fomt.gba --map 2 --import terrain_map.txt --output fomt_patched.gba
  python3 tools/edit_terrain.py fomt.gba --map 2 --set-rect x1 y1 x2 y2 --value 1
  python3 tools/edit_terrain.py fomt.gba --map 2 --info
"""

from __future__ import annotations
import struct, sys
from pathlib import Path

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28

def read_mapdata(rom, map_id):
    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    fields = {}
    fields['packed_img'] = struct.unpack_from('<I', data, 0)[0]
    fields['terrain_info'] = struct.unpack_from('<I', data, 0x18)[0]
    fields['terrain_map'] = struct.unpack_from('<I', data, 0x1C)[0]
    fields['width'] = struct.unpack_from('<H', data, 0x20)[0]
    fields['height'] = struct.unpack_from('<H', data, 0x22)[0]
    return fields

def show_info(rom, map_id):
    md = read_mapdata(rom, map_id)
    print(f"Map {map_id}: {md['width']}x{md['height']} tiles")

    # Read terrain_info (u32 array of terrain attributes)
    ti_off = md['terrain_info'] & 0x1FFFFFF
    if ti_off:
        # Count entries by reading until we hit 0xFFFFFFFF or garbage
        ti_entries = []
        off = ti_off
        while off + 4 <= len(rom) and len(ti_entries) < 20:
            val = struct.unpack_from('<I', rom, off)[0]
            if val == 0xFFFFFFFF:
                break
            # Valid terrain entries are small values (bit flags)
            # Garbage values > 0xFFFF are definitely not terrain entries
            if val > 0xFFFF and len(ti_entries) > 2:
                break
            ti_entries.append(val)
            off += 4
        print(f"  Terrain types: {len(ti_entries)}")
        for i, v in enumerate(ti_entries[:8]):
            blocked = "BLOCKED" if v & 1 else "walkable"
            print(f"    type[{i}]: 0x{v:08X} ({blocked})")

    # Read terrain_map
    tm_off = md['terrain_map'] & 0x1FFFFFF
    w, h = md['width'], md['height']
    terrain_size = w * h
    terrain = rom[tm_off:tm_off + terrain_size]

    counts = {}
    for t in terrain:
        counts[t] = counts.get(t, 0) + 1
    print(f"  Terrain index distribution:")
    for idx, count in sorted(counts.items()):
        pct = count / terrain_size * 100
        print(f"    [{idx}]: {count} tiles ({pct:.1f}%)")

def export_terrain(rom, map_id, out_path):
    md = read_mapdata(rom, map_id)
    w, h = md['width'], md['height']
    tm_off = md['terrain_map'] & 0x1FFFFFF
    terrain = rom[tm_off:tm_off + w * h]

    lines = []
    for y in range(h):
        row = ''.join(str(terrain[y * w + x]) for x in range(w))
        lines.append(row)
    Path(out_path).write_text('\n'.join(lines))
    print(f"Exported {w}x{h} terrain to {out_path}")

def import_terrain(rom, map_id, in_path):
    md = read_mapdata(rom, map_id)
    w, h = md['width'], md['height']
    text = Path(in_path).read_text().strip().split('\n')

    terrain = bytearray(w * h)
    for y in range(min(h, len(text))):
        line = text[y].strip()
        for x in range(min(w, len(line))):
            if line[x].isdigit():
                terrain[y * w + x] = int(line[x])

    # Write terrain data to free space
    FREE_START = 0x75C244
    FREE_END = 0x2000000
    offset = FREE_START
    while offset + len(terrain) <= FREE_END:
        if all(b == 0xFF for b in rom[offset:offset + len(terrain)]):
            break
        offset += 4

    rom[offset:offset + len(terrain)] = terrain
    addr = 0x08000000 | offset
    struct.pack_into('<I', rom, MAPDATA_TABLE + map_id * ENTRY_SIZE + 0x1C, addr)
    print(f"Imported terrain at 0x{addr:08X} ({len(terrain)}B)")

def set_rect(rom, map_id, x1, y1, x2, y2, value):
    md = read_mapdata(rom, map_id)
    w, h = md['width'], md['height']
    tm_off = md['terrain_map'] & 0x1FFFFFF

    for y in range(max(0, y1), min(h, y2 + 1)):
        for x in range(max(0, x1), min(w, x2 + 1)):
            rom[tm_off + y * w + x] = value
    print(f"Set terrain rectangle ({x1},{y1})-({x2},{y2}) to {value}")

if __name__ == '__main__':
    rom = bytearray(Path(sys.argv[1]).read_bytes())
    map_id = None
    export_file = None
    import_file = None
    rect = None
    rect_val = 0
    show_info_flag = False

    for i, arg in enumerate(sys.argv):
        if arg == '--map' and i+1 < len(sys.argv):
            map_id = int(sys.argv[i+1])
        if arg == '--export' and i+1 < len(sys.argv):
            export_file = sys.argv[i+1]
        if arg == '--import' and i+1 < len(sys.argv):
            import_file = sys.argv[i+1]
        if arg == '--set-rect' and i+4 < len(sys.argv):
            x1, y1, x2, y2 = map(int, sys.argv[i+1:i+5])
            rect = (x1, y1, x2, y2)
            rect_val = int(sys.argv[i+5]) if i+5 < len(sys.argv) else 1
        if arg == '--info':
            show_info_flag = True

    if map_id is None:
        print("Usage: python3 tools/edit_terrain.py fomt.gba --map N --info")
        sys.exit(1)

    if show_info_flag:
        show_info(rom, map_id)
    if export_file:
        export_terrain(rom, map_id, export_file)
    if import_file:
        import_terrain(rom, map_id, import_file)
    if rect:
        set_rect(rom, map_id, *rect, rect_val)
        Path(sys.argv[1]).write_bytes(bytes(rom))
        print("Saved!")
