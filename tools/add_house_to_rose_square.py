#!/usr/bin/env python3
"""Add building tiles from North Town to Rose Square's tileset and place a house."""
import struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from tools.scripts.decompress import unpack
from tools.scripts.compress_lzss3_literal import make_lzss3_literal_blob

rom = bytearray(open(Path(__file__).resolve().parents[1] / 'fomt.gba', 'rb').read())
BASE = 0x08000000; MT = 0x08105EDC - BASE

# === 1. Decompress Rose Square (map 2) resources ===
rs_img = unpack(rom, 0x086FB004 - BASE)[0]
rs_pal = bytearray(unpack(rom, 0x086FD19C - BASE)[0])
rs_tm = unpack(rom, struct.unpack_from('<I', rom, MT+2*0x28+0x0C)[0] - BASE)[0]
rs_w = struct.unpack_from('<H', rom, MT+2*0x28+0x20)[0]
print(f"Rose Square: tileset={len(rs_img)}B palette={len(rs_pal)}B tilemap={len(rs_tm)}B")

# === 2. Decompress North Town (map 4) tilemap ===
nt_tm = unpack(rom, struct.unpack_from('<I', rom, MT+4*0x28+0x0C)[0] - BASE)[0]
nt_w = struct.unpack_from('<H', rom, MT+4*0x28+0x20)[0]
print(f"North Town tilemap: {len(nt_tm)}B")

# === 3. Decompress NT tileset and palette ===
NT_IMG = struct.unpack_from('<I', rom, MT+4*0x28+0x00)[0]
nt_img = unpack(rom, NT_IMG - BASE)[0]
print(f"NT tileset: {len(nt_img)}B")
NT_PAL = struct.unpack_from('<I', rom, MT+4*0x28+0x04)[0]
nt_pal = unpack(rom, NT_PAL - BASE)[0]
print(f"NT palette: {len(nt_pal)}B")

# === 4. Find free tile slots in RS tileset ===
used_rs = set()
for i in range(0, len(rs_tm), 2):
    tid = struct.unpack_from('<H', rs_tm, i)[0] & 0x3FF
    if tid != 1023: used_rs.add(tid)
free_slots = sorted(set(range(256, 900)) - used_rs)
print(f"Free RS tile slots: {len(free_slots)} (e.g. {free_slots[:10]})")

# === 5. Collect unique building tiles from NT ===
build_tiles = []
for y in range(20, 46):
    for x in range(40, 80):
        val = struct.unpack_from('<H', nt_tm, (y*nt_w+x)*2)[0]
        tid, pal = val & 0x3FF, (val >> 12) & 0xF
        if tid >= 300 and (tid, pal) not in build_tiles:
            build_tiles.append((tid, pal))
print(f"NT building tile candidates: {len(build_tiles)}")

# === 6. Copy tile graphics from NT to RS tileset ===
rs_img = bytearray(rs_img)
tile_map = {}
next_free = 0
for nt_tid, nt_pv in build_tiles[:60]:
    if nt_tid >= 1024 or next_free >= len(free_slots): break
    slot = free_slots[next_free]; next_free += 1
    src_off = nt_tid * 32; dst_off = slot * 32
    rs_img[dst_off:dst_off+32] = nt_img[src_off:src_off+32]
    tile_map[(nt_tid, nt_pv)] = slot

# Also add mapping without palette (for fallback)
for nt_tid, nt_pv in build_tiles[:60]:
    slot = tile_map.get((nt_tid, nt_pv))
    if slot is None and nt_tid not in [t for t, p in tile_map]:
        # Try to find same tile with different palette
        for (t, p), s in tile_map.items():
            if t == nt_tid:
                tile_map[(nt_tid, nt_pv)] = s
                break

print(f"Copied {len(tile_map)} tiles to RS tileset")

# === 7. Copy palette colors for palette banks 1,2,3,7 ===
# Place NT's building palette colors into RS palette bank 7 (unused)
rs_pal = bytearray(rs_pal)
for src_bank in [1, 2, 3, 7]:
    s = src_bank * 32; d = 7 * 32  # RS bank 7 gets the building palette
    if s+32 <= len(nt_pal) and d+32 <= len(rs_pal):
        rs_pal[d:d+32] = nt_pal[s:s+32]
print("Copied NT palette banks 1,2,3,7 to RS bank 7")

# === 8. Helper function to look up RS tile ID ===
def rs_tid(nt_id, nt_pv):
    if (nt_id, nt_pv) in tile_map: return tile_map[(nt_id, nt_pv)]
    for (t, p), s in tile_map.items():
        if t == nt_id: return s
    return 0

# === 9. Build house in tilemap ===
rs_tm = bytearray(rs_tm)
HX, HY = 25, 22  # center of Rose Square

# House rows: (nt_tile, palette) pairs
plan = [
    [(812,2),(812,2),(813,1),(813,1),(813,1),(814,1),(814,1)],
    [(816,2),(817,2),(817,2),(817,2),(817,2),(817,2),(818,2)],
    [(806,1),(860,7),(861,1),(862,1),(863,1),(864,1),(840,1)],
    [(806,1),(873,3),(874,3),(875,3),(858,7),(859,7),(840,1)],
    [(806,1),(847,1),(888,7),(889,7),(890,7),(891,7),(840,1)],
    [(892,7),(893,1),(893,1),(893,1),(893,1),(893,1),(894,1)],
]

placed = 0
for dy, row in enumerate(plan):
    for dx, (nt_id, nt_pv) in enumerate(row):
        x, y = HX+dx, HY+dy
        if x >= rs_w or y >= 56: continue
        slot = rs_tid(nt_id, nt_pv)
        if slot == 0: continue
        idx = (y * rs_w + x) * 2
        struct.pack_into('<H', rs_tm, idx, slot | (7 << 12))
        placed += 1
print(f"Placed {placed} tiles in house at ({HX},{HY})")

# === 10. Write everything back to ROM ===
for data, name, off in [
    (make_lzss3_literal_blob(bytes(rs_img)), "packed_img", 0x00),
    (make_lzss3_literal_blob(bytes(rs_pal)), "packed_pal1", 0x04),
    (make_lzss3_literal_blob(bytes(rs_tm)), "packed_tiles1", 0x0C),
]:
    eo = MT + 2*0x28 + off
    old = struct.unpack_from('<I', rom, eo)[0]
    for cand in range(0x08760000, 0x08800000, 4):
        co = cand - BASE
        if co+len(data) >= len(rom): break
        if all(b == 0xFF for b in rom[co:co+len(data)]):
            rom[co:co+len(data)] = data
            struct.pack_into('<I', rom, eo, cand)
            print(f"{name}: 0x{old:08X} -> 0x{cand:08X}")
            break

open(Path(__file__).resolve().parents[1] / 'fomt.gba', 'wb').write(bytes(rom))
print("\n✅ 进玫瑰广场(map 2)中间看房子！用了北镇的瓦片+调色板")
