#!/usr/bin/env python3
"""Ghidra headless script to extract FoMT entity data.

Usage:
  ghidraProject/analyzeHeadless /tmp/ghidra_out -import fomt.gba -processor GBA:LE:32:default -postScript ghidra_extract_entities.py

This script finds the entity function table at 0x080E602C,
decompiles each entity init function, and extracts entity position/script data.
"""

import json

ENTITY_TABLE_ADDR = 0x080E602C
NUM_MAPS = 66

def extract_entities():
    """Extract entity data from each map's init function."""
    results = {}

    for mid in range(NUM_MAPS):
        # Read function pointer from entity table
        table_addr = ENTITY_TABLE_ADDR + mid * 4
        ptr_data = getBytes(toAddr(table_addr), 4)
        fn_ptr = struct.unpack('<I', ptr_data)[0]

        if fn_ptr == 0:
            results[mid] = {"handler": None, "entities": []}
            continue

        fn_addr = fn_ptr & ~1  # Clear THUMB bit
        results[mid] = {"handler": f"0x{fn_ptr:08X}"}

        try:
            func = getFunctionAt(toAddr(fn_addr))
            if func:
                # Decompile the function
                decomp = decompile(func)
                if decomp:
                    results[mid]["decompiled"] = str(decomp)

                # Look for LDR Rd, [PC, #imm] instructions that load data
                # These load entity data addresses from literal pools
                instr_iter = listing.getInstructions(toAddr(fn_addr), True)
                for instr in instr_iter:
                    mnemonic = instr.getMnemonicString()
                    if mnemonic == "LDR":
                        ops = instr.getOpObjects(1)
                        if ops and len(ops) > 0:
                            # Could be loading entity data address
                            ref = instr.getOpObjects(0)
                            if ref:
                                ref_addr = ref[0]
                                if isinstance(ref_addr, Address):
                                    results[mid]["data_refs"] = results[mid].get("data_refs", [])
                                    results[mid]["data_refs"].append(str(ref_addr))
        except:
            pass

    return results

if __name__ == "__main__":
    import struct
    results = extract_entities()
    print(json.dumps(results, indent=2))
