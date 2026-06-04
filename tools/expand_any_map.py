#!/usr/bin/env python3
"""Generic map expansion tool - expands any map's tilemaps and terrain.

Usage: python3 tools/expand_any_map.py fomt.gba MAP_ID [NEW_W NEW_H]
   or: python3 tools/expand_any_map.py fomt.gba MAP_ID --factor 2
"""

from __future__ import annotations
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from patch_farm_expansion import (
    make_lzss4_blob, find_free_space, patch_mapdata_entry, patch_u16,
    FREE_SPACE_START, FREE_SPACE_END, expand_tilemap, expand_terrain
)
from decompress import unpack

MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28

def main():
    rom_path = sys.argv[1]
    map_id = int(sys.argv[2])

    # Check for --factor or explicit dimensions
    if '--factor' in sys.argv:
        factor = float(sys.argv[sys.argv.index('--factor') + 1])
    elif len(sys.argv) >= 5:
        new_w = int(sys.argv[3])
        new_h = int(sys.argv[4])
        factor = None
    else:
        print("Usage: expand_any_map.py ROM MAP_ID NEW_W NEW_H")
        print("   or: expand_any_map.py ROM MAP_ID --factor N")
        sys.exit(1)

    rom = bytearray(Path(rom_path).read_bytes())

    # Read MapData entry
    entry_off = MAPDATA_TABLE + map_id * ENTRY_SIZE
    entry = bytes(rom[entry_off:entry_off + ENTRY_SIZE])

    old_w = struct.unpack_from('<H', entry, 0x20)[0]
    old_h = struct.unpack_from('<H', entry, 0x22)[0]

    if factor:
        new_w = int(old_w * factor)
        new_h = int(old_h * factor)

    print(f"=== Expanding map {map_id}: {old_w}x{old_h} -> {new_w}x{new_h} ===")

    total_needed = 0
    blobs = []

    # Expand tilemaps (3 layers)
    for layer_idx in [0, 1, 2]:
        ptr_field = [0x0C, 0x10, 0x14][layer_idx]
        old_ptr = struct.unpack_from('<I', entry, ptr_field)[0]

        if old_ptr == 0:
            print(f"  Layer {layer_idx+1}: empty (no data), skipping")
            blobs.append(None)
            continue

        # Decompress
        try:
            tile_data, fmt, lad = unpack(bytes(rom), old_ptr & 0x1FFFFFF)
            print(f"  Layer {layer_idx+1}: {old_ptr:08X} -> {len(tile_data)}B decompressed (fmt={fmt})")
        except:
            print(f"  Layer {layer_idx+1}: failed to decompress at {old_ptr:08X}, skipping")
            blobs.append(None)
            continue

        # Expand
        new_data = expand_tilemap(tile_data, old_w, old_h, new_w, new_h)
        print(f"    Expanded: {len(tile_data)}B -> {len(new_data)}B")

        # Create lzss4 blob
        blob = make_lzss4_blob(new_data)
        blobs.append(blob)
        total_needed += len(blob)

    # Expand terrain_map
    old_terrain_ptr = struct.unpack_from('<I', entry, 0x1C)[0]
    if old_terrain_ptr != 0:
        old_terrain_size = old_w * old_h
        terrain_data = bytes(rom[(old_terrain_ptr & 0x1FFFFFF):(old_terrain_ptr & 0x1FFFFFF) + old_terrain_size])
        new_terrain = expand_terrain(terrain_data, old_w, old_h, new_w, new_h)
        terrain_blob = make_lzss4_blob(new_terrain)
        print(f"  Terrain: {old_terrain_ptr:08X} -> {len(terrain_data)}B expanded to {len(new_terrain)}B")
        total_needed += len(terrain_blob)
    else:
        terrain_blob = None
        print(f"  Terrain: none (ptr=0)")

    free_before = sum(1 for b in rom[FREE_SPACE_START:FREE_SPACE_END] if b == 0xFF)
    print(f"\n  Total needed: {total_needed}B ({total_needed/1024:.0f}KB)")
    print(f"  Free space before: {free_before/1024:.0f}KB")

    if total_needed > free_before:
        print(f"  ❌ NOT ENOUGH FREE SPACE! Need {total_needed/1024:.0f}KB but only {free_before/1024:.0f}KB free")
        sys.exit(1)

    # Write to free space
    cursor = FREE_SPACE_START
    patches = []

    name_idx = 0
    names = ['packed_tiles1', 'packed_tiles2', 'packed_tiles3', 'terrain']
    all_blobs = blobs + [terrain_blob]

    for name, blob in zip(names, all_blobs):
        if blob is None:
            patches.append((name, 0, 0, 0))
            continue

        offset = cursor
        while offset + len(blob) <= FREE_SPACE_END:
            region = bytes(rom[offset:offset + len(blob)])
            if all(b == 0xFF for b in region):
                break
            offset += 4

        rom[offset:offset + len(blob)] = blob
        addr = 0x08000000 | offset
        patches.append((name, offset, addr, len(blob)))
        cursor = offset + len(blob)
        print(f"  {name}: 0x{offset:06X} -> 0x{addr:08X} ({len(blob)}B)")

    # Patch MapData
    n = 0
    for i in range(3):
        if blobs[i] is not None:
            patch_mapdata_entry(rom, map_id, [0x0C, 0x10, 0x14][i], patches[i][2])

    if terrain_blob is not None:
        patch_mapdata_entry(rom, map_id, 0x1C, patches[3][2])

    patch_u16(rom, map_id, 0x20, new_w)
    patch_u16(rom, map_id, 0x22, new_h)

    print(f"  width: {old_w} -> {new_w}")
    print(f"  height: {old_h} -> {new_h}")

    # Write ROM
    Path(rom_path).write_bytes(bytes(rom))

    free_after = sum(1 for b in rom[FREE_SPACE_START:FREE_SPACE_END] if b == 0xFF)
    print(f"\n  Free space after: {free_after/1024:.0f}KB")
    print(f"  Done! Map {map_id} expanded to {new_w}x{new_h}")

if __name__ == '__main__':
    main()
