#!/usr/bin/env python3
"""Trace the tilemap loading path by analyzing MapData field access patterns."""
import struct, sys
from capstone import *

rom = open('fomt.gba', 'rb').read()
BASE = 0x08000000

# MapData field offsets
MAPDATA_FIELDS = {
    0x00: 'packed_img',
    0x04: 'packed_pal1',
    0x08: 'packed_pal2',
    0x0C: 'packed_tiles1',
    0x10: 'packed_tiles2',
    0x14: 'packed_tiles3',
    0x18: 'terrain_info',
    0x1C: 'terrain_map',
    0x20: 'width(u16)',
    0x22: 'height(u16)',
    0x24: 'is_interior(u8)',
}

# Pre-compute: for each THUMB function, collect what offsets it accesses
# via LDR Rd, [Rn, #imm5] where imm5*4 matches a MapData field offset

def find_functions_accessing_mapdata():
    """Find functions that access multiple MapData offset patterns."""
    # For each potential function start, track which MapData offsets it accesses
    # and which register holds the base pointer

    # Strategy: find functions by scanning for prologues,
    # then for each instruction check if it's an LDR from [R?, #imm5]
    # where imm5*4 is a MapData field offset

    func_candidates = {}  # func_addr -> {offset: [access_info]}

    # Scan the entire THUMB code range
    for addr in range(0x08000000, 0x08100000, 2):
        off = addr - BASE
        if off + 2 > len(rom):
            break

        insn = struct.unpack_from('<H', rom, off)[0]

        # Check if this is a function prologue
        if (insn & 0xFF00) == 0xB500:  # push {..., lr}
            func_start = addr
            # Track all LDR accesses to MapData offsets within this function
            # Scan up to 100 instructions (200 bytes)
            seen_offsets = {}  # rn -> [(offset, field_name)]

            for delta in range(0, 200, 2):
                if off + delta + 2 > len(rom):
                    break

                insn2 = struct.unpack_from('<H', rom, off+delta)[0]
                insn_addr = func_start + delta

                # LDR Rd, [Rn, #imm5]: 01101 imm5 Rn Rd
                if (insn2 >> 11) == 0b01101:
                    imm5 = (insn2 >> 6) & 0x1F
                    rd = insn2 & 0x07
                    rn = (insn2 >> 3) & 0x07
                    load_off = imm5 * 4

                    if load_off in MAPDATA_FIELDS:
                        if rn not in seen_offsets:
                            seen_offsets[rn] = []
                        seen_offsets[rn].append((load_off, MAPDATA_FIELDS[load_off], insn_addr))

                # Check for MOV Rd, Rn or ADDS Rd, Rn, #0 (common reg copy)
                # 0001 1 00 ddd nnn 000 = ADDS Rd, Rn, #0
                if (insn2 & 0xFC00) == 0x1C00 and (insn2 & 0x00F8) == 0x00:
                    rn = (insn2 >> 3) & 0x07
                    rd = insn2 & 0x07
                    # If we were tracking rn, now track rd too
                    if rn in seen_offsets:
                        pass  # register copy - we'd need to continue tracking

                # Stop at function end
                if insn2 == 0x4770:  # bx lr
                    break
                if (insn2 >> 8) == 0xBD:  # pop {..., pc}
                    break
                # Stop at BL (going to another function probably means this function
                # passes the pointer to a sub-function)
                if (insn2 >> 11) == 0x1E:
                    insn_lo = struct.unpack_from('<H', rom, off+delta+2)[0]
                    if (insn_lo >> 11) == 0x1F:
                        # Don't break - the caller might process the result
                        pass

            # Only keep functions that access packed_tiles1 (+0x0C)
            for rn, access_list in seen_offsets.items():
                offsets = [a[0] for a in access_list]
                if 0x0C in offsets:  # accesses packed_tiles1
                    func_candidates[func_start] = {
                        'rn': rn,
                        'offsets': offsets,
                        'accesses': access_list
                    }
                    break

    return func_candidates

def analyze_with_capstone(func_addrs):
    """Use Capstone to disassemble candidate functions for better analysis."""
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)

    results = []
    for func_addr in sorted(func_addrs.keys())[:50]:  # limit to top 50
        info = func_addrs[func_addr]
        offsets = info['offsets']

        # Score: more MapData fields = higher likelihood
        score = len(offsets)
        if 0x0C in offsets:
            score += 2
        if 0x00 in offsets:
            score += 1
        if 0x04 in offsets:
            score += 1
        if 0x20 in offsets:
            score += 1

        results.append((score, func_addr, info))

    results.sort(reverse=True)
    return results

print("=== Phase 1: Scanning for functions accessing packed_tiles1 (+0x0C) ===")
candidates = find_functions_accessing_mapdata()
print(f"Found {len(candidates)} candidate functions that access +0x0C\n")

ranked = analyze_with_capstone(candidates)
print("=== Top candidates (by MapData field coverage) ===\n")

for score, func_addr, info in ranked[:30]:
    offsets_str = ', '.join([f"+0x{o:02X}({MAPDATA_FIELDS[o]})" for o in sorted(info['offsets']) if o in MAPDATA_FIELDS])
    print(f"[Score {score}] Function 0x{func_addr:08X}")
    print(f"  Base register: R{info['rn']}")
    print(f"  Fields: {offsets_str}")

    # Disassemble first 15 instructions
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB)
    code = rom[func_addr - BASE: func_addr - BASE + 60]
    try:
        dasm = ""
        for i in md.disasm(code, func_addr):
            dasm += f"    0x{i.address:08X}: {i.mnemonic} {i.op_str}\n"
        print(f"  First instructions:")
        print(dasm[:500])
    except:
        print(f"  (capstone disasm failed)")
    print()

print("=== Phase 2: Deep analysis of callers ===")

# Let me also check: for the TOP candidate function, trace who calls it
def find_bl_callers(target_addr):
    """Find all BL instructions targeting target_addr."""
    callers = []
    for i in range(0, len(rom)-4, 2):
        insn_hi = struct.unpack_from('<H', rom, i)[0]
        insn_lo = struct.unpack_from('<H', rom, i+2)[0]
        if (insn_hi >> 11) == 0x1E and (insn_lo >> 11) == 0x1F:
            S = (insn_hi >> 10) & 1
            imm10 = insn_hi & 0x3FF
            imm11 = insn_lo & 0x7FF

            # THUMB BL: PC = (insn_addr & ~3) + 4
            insn_addr = BASE | i
            pc = (insn_addr & ~3) + 4

            offset_23 = (S << 22) | (imm10 << 12) | (imm11 << 1)
            if offset_23 & 0x400000:
                offset_23 |= 0xFF800000

            tgt = pc + offset_23
            if tgt == target_addr:
                callers.append(insn_addr)

    return callers

# Analyze top candidate
if ranked:
    top = ranked[0]
    print(f"\nTop candidate: 0x{top[1]:08X} (score {top[0]})")
    callers = find_bl_callers(top[1])
    print(f"Direct BL callers: {len(callers)}")
    for c in callers[:10]:
        # show context
        off = c - BASE
        print(f"  Called from 0x{c:08X}")
        # show instructions around the call
        for j in range(max(0, off-16), min(len(rom)-2, off+8), 2):
            inst = struct.unpack_from('<H', rom, j)[0]
            addr2 = BASE | j
            marker = " <-- BL" if addr2 == c else ""
            print(f"    0x{addr2:08X}: {inst:04X}{marker}")
        print()

    # Also check the second and third candidates
    for rank_idx in range(1, min(3, len(ranked))):
        func_addr = ranked[rank_idx][1]
        callers = find_bl_callers(func_addr)
        if callers:
            print(f"\nRank {rank_idx+1} candidate 0x{func_addr:08X} has {len(callers)} callers:")
            for c in callers[:3]:
                print(f"  Called from: 0x{c:08X}")
