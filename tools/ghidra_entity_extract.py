#!/usr/bin/env python2
"""Ghidra headless script to extract FoMT entity data."""
import json
import struct

# GBA ROM: loaded at 0x00000000 (raw binary), but actual ROM addresses are 0x08000000+
# Entity table at GBA 0x080E602C = file offset 0x0E602C
ENTITY_TABLE_FILE_OFF = 0x0E602C
NUM_MAPS = 66

read = None

def extract_entities():
    results = {}
    for mid in range(NUM_MAPS):
        table_addr = ENTITY_TABLE_FILE_OFF + mid * 4
        try:
            data = getBytes(toAddr(table_addr), 4)
            if data is None or len(data) < 4:
                results[mid] = {"handler": None}
                continue
            fn_ptr = struct.unpack("<I", data)[0]
        except:
            results[mid] = {"handler": None, "error": "read failed"}
            continue

        info = {"handler": hex(fn_ptr) if fn_ptr else None}

        if fn_ptr != 0 and fn_ptr != 0x08000639:
            fn_addr = fn_ptr & ~1  # Clear THUMB bit
            file_fn_addr = fn_addr - 0x08000000
            # Read the actual function bytes
            try:
                fn_data = getBytes(toAddr(file_fn_addr), 128)
                if fn_data:
                    info["bytes"] = " ".join("%02x" % ord(b) if isinstance(b, str) else "%02x" % b for b in fn_data[:32])
            except:
                pass

            # Find LDR instructions that load from literal pools
            try:
                fn_bytes = getBytes(toAddr(file_fn_addr), 64)
                if fn_bytes:
                    refs = []
                    for i in range(0, min(len(fn_bytes)-4, 64), 2):
                        instr_val = struct.unpack("<H", fn_bytes[i:i+2])[0]
                        if (instr_val >> 11) == 0b01001:  # LDR Rd, [PC, #imm]
                            rd = (instr_val >> 8) & 7
                            imm = instr_val & 0xFF
                            pool_addr = (file_fn_addr + i + 4) & ~2
                            pool_addr += imm * 4
                            pool_off = pool_addr - file_fn_addr
                            if 0 <= pool_off < len(fn_bytes)-4:
                                val = struct.unpack("<I", fn_bytes[pool_off:pool_off+4])[0]
                                refs.append({"from": hex(pool_addr), "value": hex(val)})
                    if refs:
                        info["literal_pool"] = refs
            except:
                pass

        results[mid] = info

    return results

if __name__ == "__main__":
    results = extract_entities()
    print(json.dumps(results, indent=2))
