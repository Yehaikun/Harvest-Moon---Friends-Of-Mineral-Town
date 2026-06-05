#!/usr/bin/env python2
"""Ghidra script: analyze and decompile entity-related functions."""
import json
import struct

GHIDRA_BASE = 0  # Raw binary loaded at 0

def to_ghidra_addr(gba_addr):
    """Convert GBA ROM address to Ghidra address."""
    return gba_addr - 0x08000000

def add_func_and_decompile(gba_addr, name=None):
    """Add a function at the given GBA address and decompile it."""
    addr = to_ghidra_addr(gba_addr)
    try:
        func = getFunctionAt(toAddr(addr))
        if func is None:
            func = createFunction(toAddr(addr), name)
        if func:
            decomp = decompile(func)
            if decomp:
                return str(decomp)
    except Exception as e:
        return "Error: " + str(e)
    return "No function"

def run():
    results = {}

    # Entity function table at 0x080E602C
    print "=== Entity Function Table ==="
    table_data = getBytes(toAddr(to_ghidra_addr(0x080E602C)), 66 * 4)
    if table_data:
        for mid in range(66):
            ptr = struct.unpack("<I", table_data[mid*4:mid*4+4])[0]
            if ptr != 0 and ptr != 0x08000639:
                fn_addr = ptr & ~1
                decomp = add_func_and_decompile(fn_addr, "entity_init_map_%d" % mid)
                print "Map %d (0x%08X):" % (mid, ptr)
                print decomp[:200]
                print "---"

    # Entity helper function at 0x080DB7B4
    print "\n=== Entity Helper (0x080DB7B4) ==="
    decomp = add_func_and_decompile(0x080DB7B4, "entity_helper_1")
    print decomp[:500]
    print "==="

    # Entity constructor 0x0808ECD8
    print "\n=== Entity Constructor (0x0808ECD8) ==="
    decomp = add_func_and_decompile(0x0808ECD8, "entity_constructor")
    print decomp[:500]
    print "==="

    # Entity init helper at 0x080DB81C
    print "\n=== Entity Helper 2 (0x080DB81C) ==="
    decomp = add_func_and_decompile(0x080DB81C, "entity_helper_2")
    print decomp[:500]
    print "==="

run()
