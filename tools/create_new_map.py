#!/usr/bin/env python3
"""Create a new custom map for chicken coop warp.

Uses map 63 slot with mine interior tileset (0x086BDE04).
Map is 80x60 tiles, mine cave style, with 3 buildings.
"""
from __future__ import annotations
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from patch_farm_expansion import make_lzss4_blob, patch_mapdata_entry, patch_u16, FREE_SPACE_START, FREE_SPACE_END

MAP_ID = 63
MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000

# Mine interior tileset (used by maps 32-35)
MINE_IMG = 0x086BDE04
MINE_PAL1 = 0x086C1950
MINE_PAL2 = 0x086C1950

# Tile indices from mine maps (with correct palette numbers)
# Map 32 analysis: pal=4 for walls, pal=1 for floor, pal=2 for doors
TILE_FLOOR = 290     # cave floor (pal=1)
TILE_WALL = 288      # cave wall (pal=4)
TILE_WALL_TL = 267   # wall top-left (pal=4)
TILE_WALL_TR = 268   # wall top-right (pal=4)
TILE_LADDER = 291    # ladder (pal=1)
TILE_DARK = 303      # dark/empty (pal=4)
TILE_WALL_L = 317    # wall left edge (pal=4)
TILE_WALL_R = 318    # wall right edge (pal=4)
TILE_BUILDING = 320  # building wall (pal=1)
TILE_DOOR = 332      # door (pal=2)
TILE_PATH = 344      # path/ground variation (pal=1)

# Palette per tile type
PAL = {
    TILE_FLOOR: 1, TILE_WALL: 4, TILE_WALL_TL: 4, TILE_WALL_TR: 4,
    TILE_LADDER: 1, TILE_DARK: 4, TILE_WALL_L: 4, TILE_WALL_R: 4,
    TILE_BUILDING: 1, TILE_DOOR: 2, TILE_PATH: 1,
}

# Map dimensions
NEW_W = 80
NEW_H = 60
TILEMAP_SIZE = NEW_W * NEW_H * 2
TERRAIN_SIZE = NEW_W * NEW_H

# Building positions (x, y, w, h)
BUILDINGS = [
    (8, 6, 10, 10),    # Building 1: upper-left
    (32, 6, 10, 10),   # Building 2: upper-right
    (62, 6, 10, 10),   # Building 3: top-right
]

def create_tilemap(buildings, ground_tile=TILE_FLOOR, wall_tile=TILE_WALL):
    """Create tilemap with mine cave floor, walls, and buildings."""
    tm = bytearray(TILEMAP_SIZE)

    def set_tile(x, y, tile):
        if 0 <= x < NEW_W and 0 <= y < NEW_H:
            palette = PAL.get(tile, 4)
            idx = (y * NEW_W + x) * 2
            tm[idx] = tile & 0xFF
            tm[idx+1] = ((tile >> 8) & 0x03) | (palette << 4)

    # Fill with floor
    for y in range(NEW_H):
        for x in range(NEW_W):
            set_tile(x, y, ground_tile)

    # Border walls
    for x in range(NEW_W):
        set_tile(x, 0, TILE_WALL_TL if x == 0 else TILE_WALL if x < NEW_W-1 else TILE_WALL_TR)
        set_tile(x, NEW_H-1, TILE_WALL)
    for y in range(NEW_H):
        set_tile(0, y, TILE_WALL_L if y > 0 and y < NEW_H-1 else TILE_WALL)
        set_tile(NEW_W-1, y, TILE_WALL_R if y > 0 and y < NEW_H-1 else TILE_WALL)

    # Paths (center area)
    for x in range(20, 60):
        set_tile(x, 30, TILE_LADDER)
        set_tile(x, 31, TILE_PATH)
    for y in range(30, 45):
        set_tile(39, y, TILE_LADDER)
        set_tile(40, y, TILE_PATH)

    # Buildings
    for bx, by, bw, bh in buildings:
        for y in range(by, by + bh):
            for x in range(bx, bx + bw):
                if y == by or y == by + bh - 1 or x == bx or x == bx + bw - 1:
                    set_tile(x, y, TILE_BUILDING)  # walls
                elif y == by + 1 and x == bx + bw // 2:
                    set_tile(x, y, TILE_DOOR)  # door
                else:
                    set_tile(x, y, TILE_FLOOR)  # interior floor

    return bytes(tm)

def create_terrain(buildings):
    """Create terrain: 0=walkable, 1=blocked (walls+buildings)."""
    terrain = bytearray(TERRAIN_SIZE)

    # Default walkable
    for y in range(NEW_H):
        for x in range(NEW_W):
            terrain[y * NEW_W + x] = 0

    # Block border walls
    for x in range(NEW_W):
        terrain[0 * NEW_W + x] = 1
        terrain[(NEW_H-1) * NEW_W + x] = 1
    for y in range(NEW_H):
        terrain[y * NEW_W + 0] = 1
        terrain[y * NEW_W + NEW_W - 1] = 1

    # Block buildings
    for bx, by, bw, bh in buildings:
        for y in range(by, by + bh):
            for x in range(bx, bx + bw):
                if y == by or y == by + bh - 1 or x == bx or x == bx + bw - 1:
                    terrain[y * NEW_W + x] = 1

    return bytes(terrain)

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = bytearray(Path(rom_path).read_bytes())

    print(f"=== Redesigning Map {MAP_ID} ===")
    print(f"Size: {NEW_W}x{NEW_H}, Tileset: 0x{MINE_IMG:08X}")
    print(f"Buildings: {len(BUILDINGS)}")
    print()

    # Create tilemaps (3 layers, same visual for L1, empty for L2/L3)
    print("Creating tilemaps...")
    tilemap_l1 = create_tilemap(BUILDINGS, TILE_FLOOR)
    tilemap_l2 = bytearray(TILEMAP_SIZE)  # empty
    tilemap_l3 = bytearray(TILEMAP_SIZE)  # empty
    print(f"  Layer 1: {len(tilemap_l1)}B")
    print(f"  Layer 2: {len(tilemap_l2)}B (empty)")
    print(f"  Layer 3: {len(tilemap_l3)}B (empty)")

    # Create terrain
    print("Creating terrain...")
    terrain_data = create_terrain(BUILDINGS)
    walkable = sum(1 for b in terrain_data if b == 0)
    blocked = sum(1 for b in terrain_data if b != 0)
    print(f"  {walkable} walkable, {blocked} blocked")

    # Create lzss4 blobs
    print("\nWriting to free space...")
    blobs_data = [
        ('packed_tiles1', make_lzss4_blob(tilemap_l1)),
        ('packed_tiles2', make_lzss4_blob(tilemap_l2)),
        ('packed_tiles3', make_lzss4_blob(tilemap_l3)),
        ('terrain_map', make_lzss4_blob(terrain_data)),
    ]

    # Terrain_info: 2 entries (walkable=0, blocked=1)
    terrain_info = struct.pack('<II', 0, 1)

    cursor = FREE_SPACE_START
    patches = {}
    for name, blob in blobs_data:
        offset = cursor
        while offset + len(blob) <= FREE_SPACE_END:
            if all(b == 0xFF for b in rom[offset:offset + len(blob)]):
                break
            offset += 4
        rom[offset:offset + len(blob)] = blob
        addr = GBA_BASE | offset
        patches[name] = addr
        cursor = offset + len(blob)
        print(f"  {name}: 0x{addr:08X} ({len(blob)}B)")

    # Write terrain_info
    ti_off = cursor
    while ti_off + len(terrain_info) <= FREE_SPACE_END:
        if all(b == 0xFF for b in rom[ti_off:ti_off + len(terrain_info)]):
            break
        ti_off += 4
    rom[ti_off:ti_off + len(terrain_info)] = terrain_info
    patches['terrain_info'] = GBA_BASE | ti_off
    print(f"  terrain_info: 0x{patches['terrain_info']:08X} ({len(terrain_info)}B)")

    # Patch MapData entry
    entry_off = MAPDATA_TABLE + MAP_ID * ENTRY_SIZE
    patch_mapdata_entry(rom, MAP_ID, 0x00, MINE_IMG)
    patch_mapdata_entry(rom, MAP_ID, 0x04, MINE_PAL1)
    patch_mapdata_entry(rom, MAP_ID, 0x08, MINE_PAL2)
    patch_mapdata_entry(rom, MAP_ID, 0x0C, patches['packed_tiles1'])
    patch_mapdata_entry(rom, MAP_ID, 0x10, patches['packed_tiles2'])
    patch_mapdata_entry(rom, MAP_ID, 0x14, patches['packed_tiles3'])
    patch_mapdata_entry(rom, MAP_ID, 0x18, patches['terrain_info'])
    patch_mapdata_entry(rom, MAP_ID, 0x1C, patches['terrain_map'])
    patch_u16(rom, MAP_ID, 0x20, NEW_W)
    patch_u16(rom, MAP_ID, 0x22, NEW_H)
    rom[entry_off + 0x24] = 1  # is_interior = 1 (mine interior)

    print(f"\n  width={NEW_W}, height={NEW_H}, is_interior=1")
    print("Done!")

    Path(rom_path).write_bytes(bytes(rom))

if __name__ == '__main__':
    main()
