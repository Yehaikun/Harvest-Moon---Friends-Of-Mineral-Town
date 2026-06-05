#!/usr/bin/env python2
"""Ghidra script: trace where MapData gets cached in RAM."""
import json, struct

# Key addresses from our analysis
MAPDATA_TABLE = 0x08105EDC
LOAD_FUNC = 0x0804EEFC  # Function that reads packed_tiles1 from MapData
GET_MAPDATA = 0x080A4698

def run():
    print "=== MapData Cache Analysis ==="

    # 1. Find GetMapData callers
    print "\n1. GetMapData callers:"
    refs = getReferencesTo(toAddr(GET_MAPDATA))
    for ref in refs[:5]:
        addr = ref.getFromAddress()
        func = getFunctionContaining(addr)
        if func:
            print "  Called from: %s at 0x%X" % (func.getName(), addr.getOffset())
            decomp = decompile(func)
            if decomp:
                print "  (decompiled)"

    # 2. Find the function that loads tilemaps
    print "\n2. MapData reading function at 0x%X:" % LOAD_FUNC
    func = getFunctionAt(toAddr(LOAD_FUNC))
    if func:
        decomp = decompile(func)
        print str(decomp)[:2000]

    # 3. Search for functions that copy MapData
    print "\n3. Searching for functions that reference 0x%X:" % MAPDATA_TABLE
    refs = getReferencesTo(toAddr(MAPDATA_TABLE))
    for ref in refs[:10]:
        addr = ref.getFromAddress()
        func = getFunctionContaining(addr)
        if func:
            print "  Referenced from: %s at 0x%X" % (func.getName(), addr.getOffset())

run()
