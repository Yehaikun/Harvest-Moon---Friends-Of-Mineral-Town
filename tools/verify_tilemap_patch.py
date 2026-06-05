#!/usr/bin/env python3
"""Verify FoMT MapData tilemap patches and hardcoded farm literals."""

import argparse
import hashlib
from pathlib import Path
import struct
import sys

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.scripts.decompress import UnpackException, unpack

BASE = 0x08000000
MAPDATA_TABLE = 0x08105EDC
MAPDATA_SIZE = 0x28

FARM_LITERALS = {
    "packed_tiles1": 0x080B573C,
    "packed_img": 0x080B574C,
    "packed_pal1": 0x080B5750,
}


def u16(data, addr):
    return struct.unpack_from("<H", data, addr - BASE)[0]


def u32(data, addr):
    return struct.unpack_from("<I", data, addr - BASE)[0]


def read_popuri_header(data, ptr):
    off = ptr - BASE
    if off < 0 or off + 5 > len(data):
        return None
    if data[off] != 0x70:
        return None
    size = data[off + 1] | (data[off + 2] << 8) | (data[off + 3] << 16)
    fmt = "???"
    ladder = ""
    try:
        _, fmt, ladder = unpack(data, off)
    except UnpackException:
        pass
    return {
        "size": size,
        "fmt": fmt,
        "fmt_str": fmt,
        "ladder": ladder,
        "offset": off,
    }


def find_refs(data, value):
    needle = struct.pack("<I", value)
    refs = []
    pos = 0
    while True:
        pos = data.find(needle, pos)
        if pos < 0:
            return refs
        refs.append(BASE + pos)
        pos += 1


def mapdata_addr(map_id):
    return MAPDATA_TABLE + map_id * MAPDATA_SIZE


def digest_region(data, ptr, size):
    off = ptr - BASE
    if off < 0 or off >= len(data):
        return "out-of-range"
    blob = data[off : min(len(data), off + size)]
    return hashlib.sha1(blob).hexdigest()[:12]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("rom")
    parser.add_argument("--map", type=int, default=2)
    parser.add_argument("--compare")
    args = parser.parse_args()

    rom = open(args.rom, "rb").read()
    base_rom = open(args.compare, "rb").read() if args.compare else None

    entry = mapdata_addr(args.map)
    width = u16(rom, entry + 0x20)
    height = u16(rom, entry + 0x22)
    ptrs = {
        "packed_img": u32(rom, entry + 0x00),
        "packed_pal1": u32(rom, entry + 0x04),
        "packed_pal2": u32(rom, entry + 0x08),
        "packed_tiles1": u32(rom, entry + 0x0C),
        "packed_tiles2": u32(rom, entry + 0x10),
        "packed_tiles3": u32(rom, entry + 0x14),
        "terrain_info": u32(rom, entry + 0x18),
        "terrain_map": u32(rom, entry + 0x1C),
    }

    print(f"ROM: {args.rom} ({len(rom)} bytes)")
    print(f"Map {args.map}: {width}x{height}, MapData @ 0x{entry:08X}")

    print("\nMapData pointers:")
    for name, ptr in ptrs.items():
        extra = ""
        hdr = read_popuri_header(rom, ptr)
        if hdr:
            extra = f" popuri_size={hdr['size']} fmt={hdr['fmt_str']}"
            if hdr["ladder"]:
                extra += f" ladder={hdr['ladder']}"
        if base_rom and entry - BASE + 0x24 <= len(base_rom):
            field_off = {
                "packed_img": 0x00,
                "packed_pal1": 0x04,
                "packed_pal2": 0x08,
                "packed_tiles1": 0x0C,
                "packed_tiles2": 0x10,
                "packed_tiles3": 0x14,
                "terrain_info": 0x18,
                "terrain_map": 0x1C,
            }[name]
            old = struct.unpack_from("<I", base_rom, entry - BASE + field_off)[0]
            if old != ptr:
                extra += f" CHANGED_FROM=0x{old:08X}"
        print(f"  {name:13s} 0x{ptr:08X}{extra}")

    if args.map == 2:
        print("\nFarm hardcoded literals:")
        for name, addr in FARM_LITERALS.items():
            ptr = u32(rom, addr)
            extra = ""
            if base_rom and addr - BASE + 4 <= len(base_rom):
                old = struct.unpack_from("<I", base_rom, addr - BASE)[0]
                if old != ptr:
                    extra = f" CHANGED_FROM=0x{old:08X}"
            print(f"  {name:13s} literal@0x{addr:08X} -> 0x{ptr:08X}{extra}")

    print("\nReferences to packed_tiles1 pointer value:")
    refs = find_refs(rom, ptrs["packed_tiles1"])
    for ref in refs[:40]:
        print(f"  0x{ref:08X}")
    if len(refs) > 40:
        print(f"  ... {len(refs) - 40} more")

    print("\nData digests:")
    for name in ("packed_tiles1", "packed_tiles2", "packed_tiles3"):
        ptr = ptrs[name]
        hdr = read_popuri_header(rom, ptr)
        size = 0x100 if not hdr else min(0x100, hdr["size"] + 0x100)
        print(f"  {name:13s} sha1(first region)={digest_region(rom, ptr, size)}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
