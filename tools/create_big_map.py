#!/usr/bin/env python3
"""Create a large new town map (80x60) with 3 big houses using South Town tileset."""
import struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
from patch_farm_expansion import make_lzss4_blob, patch_mapdata_entry, patch_u16, FREE_SPACE_START, FREE_SPACE_END

MAP_ID = 63
MAPDATA_TABLE = 0x105EDC
GBA_BASE = 0x08000000

# South Town tileset & palettes (proper outdoor town look)
TILESET = 0x0870B81C
PAL1 = 0x087104B4
PAL2 = 0x08711C90

NEW_W, NEW_H = 80, 60
TILES = NEW_W * NEW_H

# Town tile indices from South Town analysis
T_GRASS = 8
T_DIRT = 0
T_PATH = 124
T_ROOF_TL = 611
T_ROOF_T = 612
T_ROOF_TR = 613
T_WALL_L = 614
T_WALL = 615
T_WALL_R = 638
T_DOOR = 639
T_WIN = 640
T_FLOOR = 616

# Palettes
PAL_GROUND = 3
PAL_BUILDING = 12
PAL_DETAIL = 6

HOUSES = [(6, 5, 18, 16), (31, 3, 18, 18), (56, 5, 18, 16)]

def build():
    tm = [0] * (TILES * 2)
    def st(x, y, idx, pal):
        if 0 <= x < NEW_W and 0 <= y < NEW_H:
            i = (y * NEW_W + x) * 2
            tm[i] = idx & 0xFF
            tm[i+1] = ((idx >> 8) & 0x03) | (pal << 4)

    # Fill grass
    for y in range(NEW_H):
        for x in range(NEW_W):
            st(x, y, T_GRASS, PAL_GROUND)

    # Road at bottom
    for x in range(32, 48):
        for y in range(50, 60):
            st(x, y, T_PATH, PAL_GROUND)

    # Houses
    for bx, by, bw, bh in HOUSES:
        for y in range(by, by + bh):
            for x in range(bx, bx + bw):
                if y == by:  # roof top
                    st(x, y, T_ROOF_TL if x == bx else T_ROOF_TR if x == bx+bw-1 else T_ROOF_T, PAL_BUILDING)
                elif y == by+1:  # wall top
                    st(x, y, T_WALL_L if x == bx else T_WALL_R if x == bx+bw-1 else T_WALL, PAL_BUILDING)
                elif y == by+bh-1:  # bottom
                    st(x, y, T_WALL_L if x == bx else T_WALL_R if x == bx+bw-1 else T_WALL, PAL_BUILDING)
                elif x == bx or x == bx+bw-1:
                    st(x, y, T_WALL_L if x == bx else T_WALL_R, PAL_BUILDING)
                else:
                    st(x, y, T_FLOOR, PAL_BUILDING)
        # Door
        st(bx+bw//2, by+bh-2, T_DOOR, PAL_DETAIL)

    return bytes(tm)

def build_terrain():
    ter = [0] * TILES
    for bx, by, bw, bh in HOUSES:
        for y in range(by, by+bh):
            for x in range(bx, bx+bw):
                is_wall = y==by or y==by+bh-1 or x==bx or x==bx+bw-1
                if is_wall: ter[y*NEW_W+x] = 1
    return bytes(ter)

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = bytearray(Path(rom_path).read_bytes())
    print(f"=== Big Town Map ({NEW_W}x{NEW_H}, {len(HOUSES)} houses) ===")
    t1 = build()
    terrain = build_terrain()
    print(f"Tilemap: {len(t1)}B, Terrain: {len(terrain)}B")

    blobs = dict(zip(['t1','t2','t3','terrain','ti'],
        [make_lzss4_blob(x) for x in [t1, bytes(len(t1)), bytes(len(t1)), terrain,
         struct.pack('<II', 0, 1)]]))

    cursor = FREE_SPACE_START
    addrs = {}
    for name, blob in blobs.items():
        off = cursor
        while off+len(blob) <= 0x2000000 and not all(b==0xFF for b in rom[off:off+len(blob)]):
            off += 4
        rom[off:off+len(blob)] = blob
        addrs[name] = GBA_BASE | off
        cursor = off + len(blob)

    eo = MAPDATA_TABLE + MAP_ID * 0x28
    for f, v in [(0x00,TILESET),(0x04,PAL1),(0x08,PAL2),(0x0C,addrs['t1']),
                 (0x10,addrs['t2']),(0x14,addrs['t3']),(0x18,addrs['ti']),
                 (0x1C,addrs['terrain'])]:
        struct.pack_into('<I', rom, eo+f, v)
    struct.pack_into('<HH', rom, eo+0x20, NEW_W, NEW_H)
    rom[eo+0x24] = 0
    Path(rom_path).write_bytes(bytes(rom))
    print(f"Done! Map {MAP_ID}: {NEW_W}x{NEW_H}")

if __name__ == '__main__':
    main()
