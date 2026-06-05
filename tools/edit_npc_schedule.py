#!/usr/bin/env python3
"""NPC Schedule Editor - view and modify NPC daily schedules.

Usage:
  python3 tools/edit_npc_schedule.py fomt.gba --npc Mary
  python3 tools/edit_npc_schedule.py fomt.gba --npc 11 --set 0 600 352 7
"""
import struct, sys
from pathlib import Path

rom = bytearray(Path(sys.argv[1]).read_bytes())

NPC_NAMES = ['Lillia','Rick','Popuri','Barley','May','Saibara','Gray','Duke',
             'Manna','Basil','Anna','Mary','Thomas','Harris','Ellen','Stu',
             'Jeff','Sasha','Karen','Doctor','Elli','Carter','Cliff','Doug',
             'Ann','Kai','Gotz','Zack','Won','Gourmet','H.Goddess','Kappa',
             'Lou','Lu','Staid']

MAPS = {0:"MOTHERS_HILL",2:"FARM",3:"FOREST",5:"NORTH_TOWN",7:"SOUTH_TOWN"}

NPC_SCHED_TABLES = [
    0x080F280C,0x080F1A80,0x080F1FC0,0x080F8678,0x080F81BC,
    0x080F77FC,0x080F7294,0x080F6370,0x080F66C4,0x080F49C0,
    0x080F5540,0x080F4D74,0x080F59CC,0x080F6B4C,0x080F33B8,
    0x080F61FC,0x080F3408,0x080F3FD8,0x080F35E4,0x080F3010,
    0x080F5D94,0x080F6DE8,0x080F2AF8,0x080F42F0,0x080F4974,
    0x080F43DC,0x080F6FF8,0x080F7B40,0x080F2DC0,0x080F597C,
    0,0,0,0x080F6B10,0x080F29C0,
]

def find_npc(name):
    if name.isdigit():
        return int(name)
    for i, n in enumerate(NPC_NAMES):
        if n.lower() == name.lower():
            return i
    return -1

def get_schedule_entry(npc_idx, entry_idx=0):
    """Get the path address and data for a specific schedule entry."""
    sched_addr = NPC_SCHED_TABLES[npc_idx]
    if not sched_addr: return None
    off = sched_addr & 0x1FFFFFF
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    toff = tbl & 0x1FFFFFF
    for si in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + si*4)[0]
        if not sa: continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        for j in range(num):
            if j == entry_idx:
                eo = (eptr & 0x1FFFFFF) + j*8
                pp = struct.unpack_from('<I', rom, eo+4)[0]
                return (pp, si, j)  # (path_addr, schedule_idx, entry_idx)
    return None

def show_npc(npc_idx):
    name = NPC_NAMES[npc_idx]
    sched_addr = NPC_SCHED_TABLES[npc_idx]
    if not sched_addr:
        print(f"{name}: no schedule")
        return
    off = sched_addr & 0x1FFFFFF
    cnt = struct.unpack_from('<I', rom, off+4)[0]
    tbl = struct.unpack_from('<I', rom, off+8)[0]
    print(f"\n=== {name} (NPC[{npc_idx}]) ===")
    toff = tbl & 0x1FFFFFF
    for si in range(cnt):
        sa = struct.unpack_from('<I', rom, toff + si*4)[0]
        if not sa: continue
        soff = sa & 0x1FFFFFF
        num = struct.unpack_from('<H', rom, soff)[0]
        eptr = struct.unpack_from('<I', rom, soff+4)[0]
        if si > 0: print()
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

def set_entry(npc_idx, entry_idx, x, y, map_id):
    """Modify a schedule entry's position."""
    result = get_schedule_entry(npc_idx, entry_idx)
    if not result:
        print("Entry not found")
        return
    path_addr, sched_idx, ent_idx = result
    po = path_addr & 0x1FFFFFF
    old_x = struct.unpack_from('<h', rom, po+6)[0]
    old_y = struct.unpack_from('<h', rom, po+8)[0]
    old_loc = struct.unpack_from('<H', rom, po+10)[0] & 0x3FF
    rom[po+6:po+8] = struct.pack('<h', x)
    rom[po+8:po+10] = struct.pack('<h', y)
    # Update location (10 bits) - clear old, set new
    loc_data = struct.unpack_from('<H', rom, po+10)[0]
    loc_data = (loc_data & 0xFC00) | (map_id & 0x3FF)
    struct.pack_into('<H', rom, po+10, loc_data)
    name = NPC_NAMES[npc_idx]
    print(f"Updated {name}[{entry_idx}]: ({old_x},{old_y}) map={old_loc} -> ({x},{y}) map={map_id}")
    Path(sys.argv[1]).write_bytes(bytes(rom))
    print("Saved!")

if __name__ == '__main__':
    npc_idx = -1; entry_idx = 0; x = None; y = None; map_id = None

    if '--npc' in sys.argv:
        i = sys.argv.index('--npc')
        npc_idx = find_npc(sys.argv[i+1])
    if '--entry' in sys.argv:
        entry_idx = int(sys.argv[sys.argv.index('--entry')+1])
    if '--set' in sys.argv:
        i = sys.argv.index('--set')
        x, y = int(sys.argv[i+1]), int(sys.argv[i+2])
        map_id = int(sys.argv[i+3]) if i+3 < len(sys.argv) else 7

    if x is not None and npc_idx >= 0:
        set_entry(npc_idx, entry_idx, x, y, map_id)
    elif npc_idx >= 0:
        show_npc(npc_idx)
    else:
        print("NPCs:")
        for i, n in enumerate(NPC_NAMES):
            print(f"  [{i:2d}] {n}")
        print("\nUsage: --npc NAME [--entry N] [--set X Y MAP]")
