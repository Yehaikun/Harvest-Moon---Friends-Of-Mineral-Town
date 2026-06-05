#!/usr/bin/env python3
"""NPC Schedule Editor - view and modify NPC daily schedules.

Usage:
  python3 tools/edit_npc_schedule.py fomt.gba --list
  python3 tools/edit_npc_schedule.py fomt.gba --schedule 0x080F1A80 --npc 1
  python3 tools/edit_npc_schedule.py fomt.gba --schedule 0x080F1A80 --npc 1 --time 120 --x 400 --y 300 --map 2
"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

MAP_NAMES = {0:"MOTHERS_HILL",2:"FARM",5:"NORTH_TOWN",7:"SOUTH_TOWN",8:"GODDESS"}

def dump_sched(addr, name):
    off = addr & 0x1FFFFFF
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    print(f"\n{name} @ 0x{addr:08X}: {cnt} NPCs")
    toff = tbl & 0x1FFFFFF
    for i in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + i*4)[0]
        if not sa: continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        print(f"\n  NPC[{i}]:")
        for j in range(num):
            eo = (eptr & 0x1FFFFFF) + j*8
            t = struct.unpack_from('<H', rom, eo)[0]
            pp = struct.unpack_from('<I', rom, eo+4)[0]
            po = pp & 0x1FFFFFF
            x = struct.unpack_from('<h', rom, po+6)[0]
            y = struct.unpack_from('<h', rom, po+8)[0]
            loc = struct.unpack_from('<H', rom, po+10)[0] & 0x3FF
            h, m = t//60, t%60
            mn = MAP_NAMES.get(loc, f"map_{loc}")
            print(f"    [{j}] {h:02d}:{m:02d} -> ({x},{y}) in {mn}")

def show_npc_list():
    """List all known schedule tables with their NPC counts."""
    tables = [
        (0x080F1A80, "ScheduleInfo (main)"),
        (0x080F280C, "Schedule (animals?)"),
        (0x080F1FC0, "Entity type schedules"),
    ]
    for addr, name in tables:
        off = addr & 0x1FFFFFF
        cnt = struct.unpack_from('<I', rom, off+4)[0]
        print(f"0x{addr:08X}: {name} ({cnt} entities)")

if __name__ == '__main__':
    if '--list' in sys.argv:
        show_npc_list()
    elif '--schedule' in sys.argv:
        idx = sys.argv.index('--schedule')
        addr = int(sys.argv[idx+1], 16)
        npc_id = None
        if '--npc' in sys.argv:
            ni = sys.argv.index('--npc')
            npc_id = int(sys.argv[ni+1])
        dump_sched(addr, f"Schedule @ {hex(addr)}")
    else:
        show_npc_list()
        print("\nUsage: --schedule ADDR [--npc N] to view, --list for tables")
