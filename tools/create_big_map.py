#!/usr/bin/env python3
"""Create a large new map (80x60) with 3 big houses, using map 63 slot.

New map uses Mother's Hill tileset (0x0869B730, shared by maps 0, 62, 63).
LZSS3 format (030) for game compatibility.
"""
import struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from patch_farm_expansion import make_lzss4_blob, patch_mapdata_entry, patch_u16, FREE_SPACE_START, FREE_SPACE_END

MAP_ID = 63
MAPDATA_TABLE = 0x105EDC
ENTRY_SIZE = 0x28
GBA_BASE = 0x08000000

# Use Mother's Hill tileset (shared by maps 0, 62, 63)
TILESET = 0x0869B730
PAL1 = 0x0869F2E0
PAL2 = 0x0869F2E0

# New map: 80x60
NEW_W, NEW_H = 80, 60
TILES = NEW_W * NEW_H

# Tile indices from Mother's Hill / shared tileset
T_GRASS = 61
T_PATH = 62
T_WALL_TL = 687   # building wall top-left
T_WALL_T = 688    # building wall top
T_WALL_TR = 689   # building wall top-right
T_WALL_L = 690    # building wall left
T_WALL_R = 702    # building wall right
T_WALL_BL = 703   # building wall bottom-left
T_WALL_B = 704    # building wall bottom
T_WALL_BR = 705   # building wall bottom-right
T_FLOOR = 706     # interior floor
T_ROOF_TL = 707   # roof top-left
T_ROOF_T = 708    # roof top
T_DOOR = 718      # door
T_ROAD = 745      # road/path

# 3 large houses: (x, y, w, h) in tiles
HOUSES = [(6, 5, 18, 16), (31, 3, 18, 18), (56, 5, 18, 16)]

def build_tilemap():
    tm = [0] * (TILES * 2)  # bytearray for 2 bytes per tile

    def set_t(x, y, tid, pal=0, flip=0):
        if 0 <= x < NEW_W and 0 <= y < NEW_H:
            i = (y * NEW_W + x) * 2
            tm[i] = tid & 0xFF
            tm[i+1] = ((tid >> 8) & 0x03) | (pal << 4) | (flip << 2)

    # Fill with grass
    for y in range(NEW_H):
        for x in range(NEW_W):
            set_t(x, y, T_GRASS)

    # Road/path from bottom center
    for x in range(35, 46):
        for y in range(50, 60):
            set_t(x, y, T_ROAD)

    # Buildings
    for bx, by, bw, bh in HOUSES:
        for y in range(by, by + bh):
            for x in range(bx, bx + bw):
                if y == by:  # top row = roof
                    if x == bx: set_t(x, y, T_ROOF_TL)
                    elif x == bx + bw - 1: set_t(x, y, T_ROOF_TL, 0, 1)
                    else: set_t(x, y, T_ROOF_T)
                elif y == by + 1:  # second row = wall top
                    if x == bx: set_t(x, y, T_WALL_TL)
                    elif x == bx + bw - 1: set_t(x, y, T_WALL_TR)
                    else: set_t(x, y, T_WALL_T)
                elif y == by + bh - 1:  # bottom row
                    if x == bx: set_t(x, y, T_WALL_BL)
                    elif x == bx + bw - 1: set_t(x, y, T_WALL_BR)
                    else: set_t(x, y, T_WALL_B)
                elif x == bx: set_t(x, y, T_WALL_L)
                elif x == bx + bw - 1: set_t(x, y, T_WALL_R)
                else: set_t(x, y, T_FLOOR)
        # Door
        door_x = bx + bw // 2
        door_y = by + bh - 2
        set_t(door_x, door_y, T_DOOR)

    return bytes(tm)

def build_terrain():
    ter = [0] * TILES
    # Block building areas
    for bx, by, bw, bh in HOUSES:
        for y in range(by, by + bh):
            for x in range(bx, bx + bw):
                if y >= by and y < by + bh and x >= bx and x < bx + bw:
                    # Only block walls, not floor inside
                    if y == by or y == by + bh - 1 or x == bx or x == bx + bw - 1:
                        ter[y * NEW_W + x] = 1
    return bytes(ter)

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = bytearray(Path(rom_path).read_bytes())

    print(f"=== Creating Big Map (MAP_ID={MAP_ID}, {NEW_W}x{NEW_W}) ===")
    print(f"Tileset: 0x{TILESET:08X}, Houses: {len(HOUSES)}")

    t1 = build_tilemap()
    t2 = bytes(len(t1))  # empty layer 2
    t3 = bytes(len(t1))  # empty layer 3
    terrain = build_terrain()
    print(f"Tilemap: {len(t1)}B, Terrain: {len(terrain)}B")

    b1 = make_lzss4_blob(t1)
    b2 = make_lzss4_blob(t2)
    b3 = make_lzss4_blob(t3)
    bt = make_lzss4_blob(terrain)
    terrain_info = struct.pack('<II', 0, 1)  # 0=walkable, 1=blocked

    cursor = FREE_SPACE_START
    blobs = {'tiles1':b1,'tiles2':b2,'tiles3':b3,'terrain':bt,'ti':terrain_info}
    addrs = {}
    for name, blob in blobs.items():
        off = cursor
        while off + len(blob) <= FREE_SPACE_END:
            if all(b==0xFF for b in rom[off:off+len(blob)]): break
            off += 4
        rom[off:off+len(blob)] = blob
        addrs[name] = GBA_BASE | off
        cursor = off + len(blob)
        print(f"  {name}: 0x{addrs[name]:08X} ({len(blob)}B)")

    # Patch MapData
    entry_off = MAPDATA_TABLE + MAP_ID * ENTRY_SIZE
    patch_mapdata_entry(rom, MAP_ID, 0x00, TILESET)
    patch_mapdata_entry(rom, MAP_ID, 0x04, PAL1)
    patch_mapdata_entry(rom, MAP_ID, 0x08, PAL2)
    patch_mapdata_entry(rom, MAP_ID, 0x0C, addrs['tiles1'])
    patch_mapdata_entry(rom, MAP_ID, 0x10, addrs['tiles2'])
    patch_mapdata_entry(rom, MAP_ID, 0x14, addrs['tiles3'])
    patch_mapdata_entry(rom, MAP_ID, 0x18, addrs['ti'])
    patch_mapdata_entry(rom, MAP_ID, 0x1C, addrs['terrain'])
    patch_u16(rom, MAP_ID, 0x20, NEW_W)
    patch_u16(rom, MAP_ID, 0x22, NEW_H)
    rom[entry_off + 0x24] = 0  # exterior

    print(f"Map {MAP_ID}: {NEW_W}x{NEW_H}")
    Path(rom_path).write_bytes(bytes(rom))
    print("Done!")

if __name__ == '__main__':
    main()
