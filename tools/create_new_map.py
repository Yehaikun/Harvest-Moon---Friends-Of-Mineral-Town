#!/usr/bin/env python3
"""Create a new custom map (3 houses + ground) for the chicken coop warp.

Uses map 63 slot (which has tileset but no terrain) and replaces its
tilemaps/terrain with a new outdoor map featuring 3 starter houses.
"""

from __future__ import annotations
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from patch_farm_expansion import make_lzss4_blob, find_free_space, patch_mapdata_entry, patch_u16, FREE_SPACE_START, FREE_SPACE_END

# Map 63 original data
MAP_ID = 63
MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28

# Read ROM
rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
rom = bytearray(Path(rom_path).read_bytes())

# Get map 63 original data
entry_off = MAPDATA_TABLE + MAP_ID * ENTRY_SIZE
entry_data = bytes(rom[entry_off:entry_off + ENTRY_SIZE])
old_img_ptr = struct.unpack_from('<I', entry_data, 0x00)[0]
old_pal1 = struct.unpack_from('<I', entry_data, 0x04)[0]
old_pal2 = struct.unpack_from('<I', entry_data, 0x08)[0]
old_w = struct.unpack_from('<H', entry_data, 0x20)[0]
old_h = struct.unpack_from('<H', entry_data, 0x22)[0]

# New map dimensions
NEW_W = 60
NEW_H = 60
TILEMAP_SIZE = NEW_W * NEW_H * 2  # 7200
TERRAIN_SIZE = NEW_W * NEW_H       # 3600

print(f"=== New Map Generator ===")
print(f"Map slot: {MAP_ID} (was {old_w}x{old_h})")
print(f"New size: {NEW_W}x{NEW_H}")
print(f"Tileset: 0x{old_img_ptr:08X}")
print()

# ----------------------------------------------------------------
# Step 1: Build tilemaps for the new map
# ----------------------------------------------------------------
# Use the shared tileset at old_img_ptr
# Based on analysis: tiles 61-64 = ground, tiles 687-748 = buildings/walls
#
# We'll create a simple layout with 3 houses:
# 60x60 grid (0-indexed):
#   - Ground: tile 61 (grass)
#   - House 1: top-left area (tiles 8,8 to 17,17)
#   - House 2: top-right area (tiles 38,8 to 47,17)
#   - House 3: bottom-center (tiles 20,38 to 29,47)
#   - Paths: tile 62 (path)

print("Step 1: Building tilemaps...")

# Tile assignments from the shared tileset
TILE_GRASS = 61
TILE_PATH = 62
TILE_FLOWER = 63
TILE_TREE = 64

# House wall/roof tiles (from map 62 analysis)
WALL_TL = 687    # top-left wall corner
WALL_T = 688     # top wall edge
WALL_TR = 689    # top-right wall corner
WALL_L = 690     # left wall edge
WALL_R = 702     # right wall edge
WALL_BL = 703    # bottom-left wall corner
WALL_B = 704     # bottom wall edge
WALL_BR = 705    # bottom-right wall corner
WALL_FILL = 706  # wall fill
ROOF_TL = 707    # roof top-left
ROOF_T = 708     # roof top
ROOF_TR = 717    # roof top-right
DOOR = 718        # door
WINDOW = 719      # window

def make_house_tilemap(ox, oy, size=8):
    """Create an 8x8 house structure at position (ox, oy) in a flat tile array."""
    tiles = {}
    # Roof (top row)
    for x in range(size):
        if x == 0:
            tiles[(oy, ox + x)] = ROOF_TL
        elif x == size - 1:
            tiles[(oy, ox + x)] = ROOF_TR
        else:
            tiles[(oy, ox + x)] = ROOF_T

    # Roof second row (overhang)
    for x in range(1, size - 1):
        tiles[(oy + 1, ox + x)] = WALL_T

    # Walls
    for y in range(2, size - 1):
        tiles[(oy + y, ox)] = WALL_L
        tiles[(oy + y, ox + size - 1)] = WALL_R
        # Interior walls
        for x in range(1, size - 1):
            if y == size // 2 and x == size // 2:
                tiles[(oy + y, ox + x)] = DOOR
            elif (y == size // 2 + 1 and (x == 2 or x == size - 2)):
                tiles[(oy + y, ox + x)] = WINDOW
            else:
                tiles[(oy + y, ox + x)] = WALL_FILL

    # Bottom row
    for x in range(size):
        if x == 0:
            tiles[(oy + size - 1, ox + x)] = WALL_BL
        elif x == size - 1:
            tiles[(oy + size - 1, ox + x)] = WALL_BR
        else:
            tiles[(oy + size - 1, ox + x)] = WALL_B

    return tiles

# House positions (top-left corner)
HOUSES = [
    (10, 6, 8),    # House 1: upper-left, 8x8
    (28, 6, 8),    # House 2: upper-right, 8x8
    (16, 38, 8),   # House 3: bottom-center, 8x8
]

# Generate all house tiles
house_tiles = {}
for ox, oy, size in HOUSES:
    ht = make_house_tilemap(ox, oy, size)
    for (y, x), tile in ht.items():
        house_tiles[(y, x)] = tile

# Generate 3 tilemap layers
import copy

def create_tilemap_layer(ground_tile, add_house=True, add_paths=True):
    """Create a flat tilemap array with ground, paths, and houses."""
    # Flat array: [tile_index_lo, tile_index_hi] * width * height
    tilemap = bytearray(NEW_W * NEW_H * 2)

    # Fill with ground
    for y in range(NEW_H):
        for x in range(NEW_W):
            idx = (y * NEW_W + x) * 2
            tile = ground_tile
            tilemap[idx] = tile & 0xFF
            tilemap[idx + 1] = (tile >> 8) & 0x03

    # Add paths (horizontal/vertical)
    if add_paths:
        # Main path from bottom center
        path_tiles = []
        # Vertical path from House 3 down
        for y in range(48, NEW_H):
            path_tiles.append((y, 20))
            path_tiles.append((y, 21))
            path_tiles.append((y, 22))
        # Horizontal path connecting houses 1-2
        for x in range(10, 36):
            path_tiles.append((14, x))
            path_tiles.append((15, x))
        # Path from house 3 up
        for y in range(38, 46):
            path_tiles.append((y, 20))
            path_tiles.append((y, 21))
            path_tiles.append((y, 22))

        for y, x in path_tiles:
            if (y, x) not in house_tiles:
                idx = (y * NEW_W + x) * 2
                tile = TILE_PATH
                tilemap[idx] = tile & 0xFF
                tilemap[idx + 1] = (tile >> 8) & 0x03
                # Also path tile to left
                if x > 0 and (y, x-1) not in house_tiles:
                    idx2 = (y * NEW_W + (x-1)) * 2
                    tilemap[idx2] = TILE_PATH & 0xFF
                    tilemap[idx2 + 1] = (TILE_PATH >> 8) & 0x03

    # Add houses
    if add_house:
        for (y, x), tile in house_tiles.items():
            if y < NEW_H and x < NEW_W:
                idx = (y * NEW_W + x) * 2
                tilemap[idx] = tile & 0xFF
                tilemap[idx + 1] = (tile >> 8) & 0x03

    return bytes(tilemap)

tilemap_ground = create_tilemap_layer(TILE_GRASS, add_house=True, add_paths=True)

# Layer 1: main visual (ground + houses + paths)
tilemap_l1 = tilemap_ground
# Layer 2: some detail (flower patches, etc.)
tilemap_l2 = create_tilemap_layer(0, add_house=False, add_paths=False)  # empty
# Layer 3: empty
tilemap_l3 = create_tilemap_layer(0, add_house=False, add_paths=False)  # empty

print(f"  Layer 1: {len(tilemap_l1)}B")
print(f"  Layer 2: {len(tilemap_l2)}B")
print(f"  Layer 3: {len(tilemap_l3)}B")

# ----------------------------------------------------------------
# Step 2: Build terrain map
# ----------------------------------------------------------------
print("\nStep 2: Building terrain map...")

def create_terrain():
    """Create terrain index map: 0=walkable, 1=blocked (houses)."""
    terrain = bytearray(NEW_W * NEW_H)

    # Default: walkable (0)
    for y in range(NEW_H):
        for x in range(NEW_W):
            terrain[y * NEW_W + x] = 0

    # Block house areas
    for (y, x), tile in house_tiles.items():
        if y < NEW_H and x < NEW_W:
            terrain[y * NEW_W + x] = 1  # blocked

    return bytes(terrain)

terrain_data = create_terrain()
walkable = sum(1 for b in terrain_data if b == 0)
blocked = sum(1 for b in terrain_data if b != 0)
print(f"  Walkable tiles: {walkable}")
print(f"  Blocked tiles: {blocked}")

# ----------------------------------------------------------------
# Step 3: Create lzss4 blobs
# ----------------------------------------------------------------
print("\nStep 3: Creating lzss4 blobs...")

blob_t1 = make_lzss4_blob(tilemap_l1)
blob_t2 = make_lzss4_blob(tilemap_l2)
blob_t3 = make_lzss4_blob(tilemap_l3)
blob_terrain = make_lzss4_blob(terrain_data)

print(f"  Tilemap 1: {len(tilemap_l1)}B -> {len(blob_t1)}B")
print(f"  Tilemap 2: {len(tilemap_l2)}B -> {len(blob_t2)}B")
print(f"  Tilemap 3: {len(tilemap_l3)}B -> {len(blob_t3)}B")
print(f"  Terrain:   {len(terrain_data)}B -> {len(blob_terrain)}B")

# ----------------------------------------------------------------
# Step 4: Write to free space
# ----------------------------------------------------------------
print("\nStep 4: Writing to free space...")

blobs = [('tiles1', blob_t1), ('tiles2', blob_t2), ('tiles3', blob_t3), ('terrain', blob_terrain)]
patches = []
cursor = FREE_SPACE_START

for name, blob in blobs:
    offset = cursor
    while offset + len(blob) <= FREE_SPACE_END:
        region = bytes(rom[offset:offset + len(blob)])
        if all(b == 0xFF for b in region):
            break
        offset += 4

    rom[offset:offset + len(blob)] = blob
    addr = 0x08000000 | offset
    patches.append((name, offset, addr))
    cursor = offset + len(blob)
    print(f"  {name}: 0x{offset:06X} -> 0x{addr:08X}")

# ----------------------------------------------------------------
# Step 5: Patch MapData entry
# ----------------------------------------------------------------
print("\nStep 5: Patching MapData...")

# Reuse original tileset and palettes
# packed_img stays the same (already set)
# Update tilemap pointers
patch_mapdata_entry(rom, MAP_ID, 0x00, old_img_ptr)
patch_mapdata_entry(rom, MAP_ID, 0x04, old_pal1)
patch_mapdata_entry(rom, MAP_ID, 0x08, old_pal2)
patch_mapdata_entry(rom, MAP_ID, 0x0C, patches[0][2])  # packed_tiles1
patch_mapdata_entry(rom, MAP_ID, 0x10, patches[1][2])  # packed_tiles2
patch_mapdata_entry(rom, MAP_ID, 0x14, patches[2][2])  # packed_tiles3
patch_mapdata_entry(rom, MAP_ID, 0x1C, patches[3][2])  # terrain_map
patch_u16(rom, MAP_ID, 0x20, NEW_W)
patch_u16(rom, MAP_ID, 0x22, NEW_H)

# Set is_interior to 0 (outdoor)
rom[entry_off + 0x24] = 0

# Packed_tiles3 was 0x00000000 (no layer 3), now we have one
# terrain_info was 0x00000000 - need to provide at least basic terrain info
# terrain_info: array of u32, indexed by terrain_map value
# bit 0 = collision (0=walkable, 1=blocked)
# We use terrain index 0 (walkable) and 1 (blocked)
terrain_info = struct.pack('<II', 0, 1)  # type 0=walkable, type 1=blocked
ti_offset = cursor + 4  # find free space
while ti_offset + len(terrain_info) <= FREE_SPACE_END:
    region = bytes(rom[ti_offset:ti_offset + len(terrain_info)])
    if all(b == 0xFF for b in region):
        break
    ti_offset += 4
rom[ti_offset:ti_offset + len(terrain_info)] = terrain_info
patch_mapdata_entry(rom, MAP_ID, 0x18, 0x08000000 | ti_offset)
print(f"  terrain_info: 0x{ti_offset:06X} -> 0x{0x08000000 | ti_offset:08X}")

print(f"  width: {old_w} -> {NEW_W}")
print(f"  height: {old_h} -> {NEW_H}")
print(f"  is_interior: 0 -> 0 (outdoor)")

# ----------------------------------------------------------------
# Step 6: Verify
# ----------------------------------------------------------------
print("\nStep 6: Verifying...")
verify = bytes(rom)
for name, offset, addr in patches:
    chunk = bytes(verify[offset:offset + 8])
    print(f"  {name} @ 0x{addr:08X}: {chunk.hex()}...")

# Write patched ROM
Path(rom_path).write_bytes(rom)
print(f"\nDone! New map created in {rom_path}")

# Show final MapData
entry_final = bytes(rom[entry_off:entry_off + ENTRY_SIZE])
fields = [('packed_img', '<I', 0), ('packed_pal1', '<I', 4), ('packed_pal2', '<I', 8),
          ('packed_tiles1','<I',0x0C), ('packed_tiles2','<I',0x10), ('packed_tiles3','<I',0x14),
          ('terrain_info','<I',0x18), ('terrain_map','<I',0x1C),
          ('width','<H',0x20), ('height','<H',0x22), ('interior','<B',0x24)]
print(f"\nFinal MapData for map {MAP_ID}:")
for name, fmt, off in fields:
    val = struct.unpack_from(fmt, entry_final, off)[0]
    print(f"  +0x{off:02X} {name:18s}= 0x{val:08X}")
