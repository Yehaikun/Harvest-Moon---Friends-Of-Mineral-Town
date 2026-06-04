#!/usr/bin/env python3
"""GBA tilemap editor for FoMT maps.

Usage:
  python3 tools/edit_tilemap.py fomt.gba --map 2 --export tilemap.csv
  python3 tools/edit_tilemap.py fomt.gba --map 2 --tile 10 20 --set-index 100
  python3 tools/edit_tilemap.py fomt.gba --map 2 --layer 1 --info
"""

from __future__ import annotations
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from decompress import unpack
from patch_farm_expansion import make_lzss4_blob, patch_mapdata_entry, FREE_SPACE_START, FREE_SPACE_END

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000
LAYER_OFFSETS = [0x0C, 0x10, 0x14]  # packed_tiles1/2/3 in MapData

def read_mapdata_entry(rom, map_id):
    off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    data = rom[off:off + ENTRY_SIZE]
    w = struct.unpack_from('<H', data, 0x20)[0]
    h = struct.unpack_from('<H', data, 0x22)[0]
    layers = []
    for lo in LAYER_OFFSETS:
        layers.append(struct.unpack_from('<I', data, lo)[0])
    return w, h, layers

def get_tilemap(rom, map_id, layer=1):
    w, h, layers = read_mapdata_entry(rom, map_id)
    ptr = layers[layer - 1]
    if ptr == 0:
        return None, None, w, h
    file_off = ptr & 0x1FFFFFF
    # Check if popuri format
    if rom[file_off:file_off+4][0] == 0x70:
        data, fmt, lad = unpack(bytes(rom), file_off)
    else:
        # Raw/uncompressed
        data = bytes(rom[file_off:file_off + w * h * 2])
        fmt = "raw"
    return data, fmt, w, h

def show_info(rom, map_id):
    w, h, layers = read_mapdata_entry(rom, map_id)
    print(f"Map {map_id}: {w}x{h} tiles = {w*h*2}B per layer")
    for i, ptr in enumerate(layers):
        if ptr:
            file_off = ptr & 0x1FFFFFF
            fmt_char = "popuri" if rom[file_off] == 0x70 else "raw"
            print(f"  Layer {i+1}: 0x{ptr:08X} ({fmt_char})")
        else:
            print(f"  Layer {i+1}: empty")

def export_csv(rom, map_id, out_path, layer=1):
    data, fmt, w, h = get_tilemap(rom, map_id, layer)
    if data is None:
        print(f"Layer {layer} empty")
        return

    lines = []
    for y in range(h):
        row = []
        for x in range(w):
            idx = (y * w + x) * 2
            tile = data[idx] | (data[idx+1] << 8)
            tile_idx = tile & 0x3FF
            pal = (tile >> 12) & 0xF
            hflip = (tile >> 10) & 1
            vflip = (tile >> 11) & 1
            row.append(f"{tile_idx}:{pal}:{hflip}:{vflip}")
        lines.append(','.join(row))
    Path(out_path).write_text('\n'.join(lines))
    print(f"Exported {w}x{h} tilemap ({fmt}) to {out_path}")

def set_tile(rom, map_id, x, y, tile_idx, layer=1, pal=0):
    """Modify a single tile (in free space, since tilemaps are compressed)."""
    data, fmt, w, h = get_tilemap(rom, map_id, layer)
    if data is None:
        print(f"Layer {layer} empty")
        return

    if x >= w or y >= h:
        print(f"Position ({x},{y}) out of bounds for {w}x{h}")
        return

    idx = (y * w + x) * 2
    tile = tile_idx & 0x3FF | (pal & 0xF) << 12
    new_data = bytearray(data)
    new_data[idx] = tile & 0xFF
    new_data[idx+1] = (tile >> 8) & 0xFF

    # Write to free space as lzss4 blob
    blob = make_lzss4_blob(bytes(new_data))
    offset = FREE_SPACE_START
    while offset + len(blob) <= FREE_SPACE_END:
        if all(b == 0xFF for b in rom[offset:offset + len(blob)]):
            break
        offset += 4

    rom[offset:offset + len(blob)] = blob
    addr = GBA_BASE | offset
    patch_mapdata_entry(rom, map_id, LAYER_OFFSETS[layer-1], addr)
    print(f"Tile ({x},{y}) -> index={tile_idx}, pal={pal}, written to 0x{addr:08X}")

if __name__ == '__main__':
    rom = bytearray(Path(sys.argv[1]).read_bytes())
    map_id = None
    layer = 1
    export_file = None
    set_tile_pos = None
    set_tile_val = None
    show_info_flag = False

    for i, arg in enumerate(sys.argv):
        if arg == '--map' and i+1 < len(sys.argv): map_id = int(sys.argv[i+1])
        if arg == '--layer' and i+1 < len(sys.argv): layer = int(sys.argv[i+1])
        if arg == '--export' and i+1 < len(sys.argv): export_file = sys.argv[i+1]
        if arg == '--info': show_info_flag = True
        if arg == '--tile' and i+3 < len(sys.argv):
            set_tile_pos = (int(sys.argv[i+1]), int(sys.argv[i+2]))
        if arg == '--set-index' and i+1 < len(sys.argv):
            set_tile_val = int(sys.argv[i+1])

    if map_id is None:
        print("Usage: python3 tools/edit_tilemap.py fomt.gba --map N --info")
        sys.exit(1)

    if show_info_flag:
        show_info(rom, map_id)
    if export_file:
        export_csv(rom, map_id, export_file, layer)
    if set_tile_pos and set_tile_val is not None:
        set_tile(rom, map_id, set_tile_pos[0], set_tile_pos[1], set_tile_val, layer)
        Path(sys.argv[1]).write_bytes(bytes(rom))
