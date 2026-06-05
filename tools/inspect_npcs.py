#!/usr/bin/env python3
"""NPC schedule inspector for FoMT.

Reads ScheduleInfo structures and displays NPC path/position data.
Usage: python3 tools/inspect_npcs.py fomt.gba [--schedule ADDR]
"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

# Known map names
MAP_NAMES = {0:"MOTHERS_HILL", 1:"BEACH", 2:"FARM", 3:"FOREST", 5:"NORTH_TOWN",
             7:"SOUTH_TOWN", 8:"GODDESS_POND", 15:"SHOP_INTERIOR", 29:"PLAYER_HOUSE"}

def read_path_info(addr):
    """Read a PathInfo structure."""
    off = addr & 0x1FFFFFF
    pts = struct.unpack_from('<I', rom, off)[0]
    num = struct.unpack_from('<H', rom, off+4)[0]
    x = struct.unpack_from('<h', rom, off+6)[0]
    y = struct.unpack_from('<h', rom, off+8)[0]
    loc_bits = struct.unpack_from('<H', rom, off+10)[0]
    loc = loc_bits & 0x3FF
    facing = (loc_bits >> 10) & 3
    map_name = MAP_NAMES.get(loc, f"map_{loc}")
    return {"addr": addr, "num": num, "x": x, "y": y, "loc": loc,
            "map": map_name, "facing": facing, "pts_ptr": pts}

def dump_schedule(addr):
    """Dump a ScheduleInfo structure."""
    off = addr & 0x1FFFFFF
    fn = struct.unpack_from('<I', rom, off)[0]
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    print(f"\nScheduleInfo @ 0x{addr:08X}: selector=0x{fn:08X}, {cnt} schedules")
    if cnt < 1 or cnt > 50 or not tbl:
        return
    toff = tbl & 0x1FFFFFF
    for i in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + i*4)[0]
        if not sa:
            continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        print(f"\n  Schedule[{i}]: {num} entries")
        for j in range(min(num, 8)):
            eo = (eptr & 0x1FFFFFF) + j*8
            t = struct.unpack_from('<H', rom, eo)[0]
            pp = struct.unpack_from('<I', rom, eo+4)[0]
            pi = read_path_info(pp)
            hour = t // 60
            minute = t % 60
            print(f"    {hour:02d}:{minute:02d} -> ({pi['x']:4d},{pi['y']:4d}) on {pi['map']} facing {pi['facing']}")
        if num > 8:
            print(f"    ... ({num-8} more entries)")

if __name__ == '__main__':
    if '--schedule' in sys.argv:
        idx = sys.argv.index('--schedule')
        dump_schedule(int(sys.argv[idx+1], 16))
    else:
        for addr in [0x080F1A80, 0x080F280C]:
            dump_schedule(addr)
