#!/usr/bin/env python3
"""NPC and schedule inspector for FoMT.

Extracts NPC data from the ScheduleInfo structures.
"""
from __future__ import annotations
import struct, sys
from pathlib import Path

# Known schedule tables (from data_schedules.cc)
# ScheduleInfo_Unk_080F1A80 = { selector_fn, 5 schedules, ... }
SCHEDULE_TABLES = {
    0x080F1A80: "ScheduleInfo_Unk_080F1A80",
}

def read_u32(data, off):
    return struct.unpack_from('<I', data, off)[0]

def read_u16(data, off):
    return struct.unpack_from('<H', data, off)[0]

def read_i16(data, off):
    return struct.unpack_from('<h', data, off)[0]

def dump_schedule_info(rom, addr):
    file_off = addr & 0x1FFFFFF
    fn_ptr = read_u32(rom, file_off)
    num = read_u32(rom, file_off + 4)
    schedules_ptr = read_u32(rom, file_off + 8)
    print(f"ScheduleInfo @ 0x{addr:08X}:")
    print(f"  Selector: 0x{fn_ptr:08X}")
    print(f"  Schedules: {num}")
    print(f"  Table: 0x{schedules_ptr:08X}")

    # Read schedule pointer table
    tbl_off = schedules_ptr & 0x1FFFFFF
    for i in range(num):
        sched_ptr = read_u32(rom, tbl_off + i*4)
        if sched_ptr:
            sched_off = sched_ptr & 0x1FFFFFF
            num_entries = read_u16(rom, sched_off)
            entries_ptr = read_u32(rom, sched_off + 4)
            print(f"\n  Schedule [{i}]: {num_entries} entries @ 0x{entries_ptr:08X}")

            # Read entries
            ent_off = entries_ptr & 0x1FFFFFF
            for j in range(num_entries):
                time = read_u16(rom, ent_off + j*8)
                path_ptr = read_u32(rom, ent_off + j*8 + 4)
                print(f"    Entry [{j}]: time={time}, path=0x{path_ptr:08X}")

                if path_ptr:
                    p_off = path_ptr & 0x1FFFFFF
                    num_pts = read_u16(rom, p_off)
                    x = read_i16(rom, p_off + 2)
                    y = read_i16(rom, p_off + 4)
                    loc = read_u32(rom, p_off + 8)
                    facing = read_u16(rom, p_off + 12) & 3
                    print(f"      Start: ({x},{y}) loc={loc} facing={facing}, {num_pts} path points")
        else:
            print(f"  Schedule [{i}]: null")

if __name__ == '__main__':
    rom = bytearray(Path(sys.argv[1]).read_bytes())

    for addr in [0x080F1A80]:
        dump_schedule_info(rom, addr)
        print("---")
