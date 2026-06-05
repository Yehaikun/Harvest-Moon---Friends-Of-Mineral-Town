#!/usr/bin/env python3
"""NPC Schedule Editor - shows all NPC schedules with names.

Usage: python3 tools/edit_npc_schedule.py fomt.gba [--npc NAME]
"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

MAPS = {0:"MOTHERS_HILL",2:"FARM",3:"FOREST",5:"NORTH_TOWN",6:"?",7:"SOUTH_TOWN",
        8:"GODDESS",10:"?",11:"?",19:"?",21:"?",38:"?"}

# NPC[0..34] → name mapping from name table order
NPC_NAMES = ['Lillia','Rick','Popuri','Barley','May','Saibara','Gray','Duke',
             'Manna','Basil','Anna','Mary','Thomas','Harris','Ellen','Stu',
             'Jeff','Sasha','Karen','Doctor','Elli','Carter','Cliff','Doug',
             'Ann','Kai','Gotz','Zack','Won','Gourmet','H.Goddess','Kappa',
             'Lou','Lu','Staid']

# Schedule table for each NPC (index 0-34 maps to creator fn order)
NPC_SCHED_TABLES = [
    0x080F280C, 0x080F1A80, 0x080F1FC0, 0x080F8678, 0x080F81BC,
    0x080F77FC, 0x080F7294, 0x080F6370, 0x080F66C4, 0x080F49C0,
    0x080F5540, 0x080F4D74, 0x080F59CC, 0x080F6B4C, 0x080F33B8,
    0x080F61FC, 0x080F3408, 0x080F3FD8, 0x080F35E4, 0x080F3010,
    0x080F5D94, 0x080F6DE8, 0x080F2AF8, 0x080F42F0, 0x080F4974,
    0x080F43DC, 0x080F6FF8, 0x080F7B40, 0x080F2DC0, 0x080F597C,
    0, 0, 0, 0x080F6B10, 0x080F29C0,
]

def show_npc(npc_idx):
    name = NPC_NAMES[npc_idx]
    sched_addr = NPC_SCHED_TABLES[npc_idx]
    if not sched_addr:
        print(f"{name}: no schedule table found")
        return
    off = sched_addr & 0x1FFFFFF
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    print(f"\n=== {name} (NPC[{npc_idx}], {cnt} schedules) ===")
    toff = tbl & 0x1FFFFFF
    for si in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + si*4)[0]
        if not sa: continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        if si > 0:
            print()
        for j in range(num):
            eo = (eptr & 0x1FFFFFF) + j*8
            t = struct.unpack_from('<H', rom, eo)[0]
            pp = struct.unpack_from('<I', rom, eo+4)[0]
            po = pp & 0x1FFFFFF
            x = struct.unpack_from('<h', rom, po+6)[0]
            y = struct.unpack_from('<h', rom, po+8)[0]
            loc = struct.unpack_from('<H', rom, po+10)[0] & 0x3FF
            h, m = t//60, t%60
            mn = MAPS.get(loc, f"map_{loc}")
            print(f"  [{j:2d}] {h:02d}:{m:02d} -> ({x:4d},{y:4d}) in {mn}")

if __name__ == '__main__':
    if '--npc' in sys.argv:
        idx = sys.argv.index('--npc')
        name = sys.argv[idx+1]
        if name.isdigit():
            show_npc(int(name))
        else:
            for i, n in enumerate(NPC_NAMES):
                if n.lower() == name.lower():
                    show_npc(i)
                    break
            else:
                print(f"NPC '{name}' not found. Options: {', '.join(NPC_NAMES)}")
    else:
        print("Usage: --npc NAME (name or index)\nNPCs:")
        for i, n in enumerate(NPC_NAMES):
            print(f"  [{i:2d}] {n}")
