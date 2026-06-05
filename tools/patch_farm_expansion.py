#!/usr/bin/env python3
"""Farm expansion patcher - expands farm from 60x56 to 65x60 tiles.

Uses lzss4 (pass-through format) to store uncompressed tilemap data
in ROM free space, then updates MapData pointers for MAP_FARM.
"""

from __future__ import annotations
import struct
import sys
from pathlib import Path

# ROM free space
FREE_SPACE_START = 0x75C244
FREE_SPACE_END = 0x2000000

# MapData table location and farm entry
MAPDATA_TABLE = 0x105EDC  # file offset
MAPDATA_ENTRY_SIZE = 0x28
MAP_FARM_ID = 2

# Original dimensions
OLD_W = 60
OLD_H = 56
OLD_TILEMAP_SIZE = OLD_W * OLD_H * 2  # 6720
OLD_TERRAIN_SIZE = OLD_W * OLD_H       # 3360

# New dimensions
NEW_W = 120
NEW_H = 112
NEW_TILEMAP_SIZE = NEW_W * NEW_H * 2  # 7800
NEW_TERRAIN_SIZE = NEW_W * NEW_H       # 3900

# ROM addresses for farm's MapData entries (original)
with open('/home/lyjew/Documents/github/fomt/fomt.gba', 'rb') as f:
    f.seek(MAPDATA_TABLE + MAP_FARM_ID * MAPDATA_ENTRY_SIZE)
    md = f.read(MAPDATA_ENTRY_SIZE)

def read_u32(off: int) -> int:
    return struct.unpack_from('<I', md, off)[0]

OLD_PTR_TILES1 = read_u32(0x0C)
OLD_PTR_TILES2 = read_u32(0x10)
OLD_PTR_TILES3 = read_u32(0x14)
OLD_PTR_TERRAIN_MAP = read_u32(0x1C)


def make_lzss4_blob(raw_data: bytes) -> bytes:
    """Wrap raw data in popuri lzss4 format (atom=0, lzss=4, diff=0)."""
    expected_size = len(raw_data)
    # Format byte (4) + raw data, padded to 4 bytes
    payload = bytes([4]) + raw_data
    while len(payload) % 4:
        payload += b'\x00'
    # Reverse every 4-byte group (ReadBits reads LE words MSB-first)
    bitstream = bytearray()
    for i in range(0, len(payload), 4):
        bitstream.extend(payload[i:i+4][::-1])
    # Header: 0x70 | (expected_size << 8)
    header = 0x70 | (expected_size << 8)
    return struct.pack('<I', header) + bytes(bitstream)


def expand_tilemap(data: bytes, old_w: int, old_h: int, new_w: int, new_h: int) -> bytes:
    """Expand a GBA tilemap, filling expanded area with tile 0 (grass)."""
    result = bytearray(new_w * new_h * 2)
    for y in range(min(old_h, new_h)):
        dst = y * new_w * 2
        result[dst:dst + old_w * 2] = data[y * old_w * 2:y * old_w * 2 + old_w * 2]
        # Expanded right side stays as tile 0 (already zero in bytearray)
    # New bottom rows stay as tile 0
    return bytes(result)


def expand_terrain(data: bytes, old_w: int, old_h: int, new_w: int, new_h: int) -> bytes:
    """Expand a terrain map (1 byte per tile) from old_w×old_h to new_w×new_h.
    Sets expanded tiles to walkable (type 0) instead of copying edge values."""
    result = bytearray(new_w * new_h)
    for y in range(min(old_h, new_h)):
        dst_start = y * new_w
        result[dst_start:dst_start + old_w] = data[y * old_w:y * old_w + old_w]
        # Expanded right side: walkable (0)
        for x in range(old_w, new_w):
            result[dst_start + x] = 0
    # New rows: walkable
    for y in range(old_h, new_h):
        dst_start = y * new_w
        for x in range(new_w):
            result[dst_start + x] = 0
    return bytes(result)


def find_free_space(rom_data: bytes, needed: int, align: int = 4) -> int:
    """Find free space in ROM starting from FREE_SPACE_START."""
    # Scan for free space (filled with 0xFF or 0x00)
    offset = FREE_SPACE_START
    while offset + needed <= FREE_SPACE_END:
        # Check if this region is free (all 0xFF)
        region = rom_data[offset:offset + needed]
        if all(b == 0xFF for b in region):
            return offset
        # Also accept all 0x00
        if all(b == 0x00 for b in region):
            return offset
        offset += align
    raise RuntimeError(f"Cannot find {needed} bytes of free space")


def patch_mapdata_entry(rom: bytearray, map_id: int, offset: int, value: int):
    """Patch a u32 field in a MapData entry."""
    entry_off = MAPDATA_TABLE + map_id * MAPDATA_ENTRY_SIZE + offset
    struct.pack_into('<I', rom, entry_off, value)


def patch_u16(rom: bytearray, map_id: int, offset: int, value: int):
    """Patch a u16 field in a MapData entry."""
    entry_off = MAPDATA_TABLE + map_id * MAPDATA_ENTRY_SIZE + offset
    struct.pack_into('<H', rom, entry_off, value)


def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = bytearray(Path(rom_path).read_bytes())

    print(f"=== Farm Expansion Patch ===")
    print(f"ROM: {rom_path}")
    print(f"Original: {OLD_W}x{OLD_H} → New: {NEW_W}x{NEW_H}")
    print()

    # Step 1: Read original tilemaps
    print("Step 1: Decompressing original tilemaps...")
    sys.path.insert(0, str(Path(__file__).parent / 'scripts'))
    from decompress import unpack

    tilemaps = []
    for i, (name, ptr) in enumerate([
        ('packed_tiles1', OLD_PTR_TILES1),
        ('packed_tiles2', OLD_PTR_TILES2),
        ('packed_tiles3', OLD_PTR_TILES3),
    ]):
        off = ptr & 0x1FFFFFF
        data, fmt, ladder = unpack(bytes(rom), off)
        tilemaps.append(data)
        print(f"  {name} @ 0x{ptr:08X}: {len(data)}B decompressed, format={fmt}")

    # Step 2: Read original terrain_map
    print("\nStep 2: Reading terrain data...")
    terrain_off = OLD_PTR_TERRAIN_MAP & 0x1FFFFFF
    terrain_data = bytes(rom[terrain_off:terrain_off + OLD_TERRAIN_SIZE])
    print(f"  terrain_map @ 0x{OLD_PTR_TERRAIN_MAP:08X}: {len(terrain_data)}B")

    # Step 3: Expand tilemaps
    print(f"\nStep 3: Expanding to {NEW_W}x{NEW_H}...")
    new_tilemaps = []
    for i in range(3):
        t = expand_tilemap(tilemaps[i], OLD_W, OLD_H, NEW_W, NEW_H)
        new_tilemaps.append(t)
        print(f"  Tilemap {i+1}: {len(tilemaps[i])}B → {len(t)}B")

    new_terrain = expand_terrain(terrain_data, OLD_W, OLD_H, NEW_W, NEW_H)
    print(f"  terrain_map: {len(terrain_data)}B → {len(new_terrain)}B")

    # Step 4: Create lzss4 blobs
    print("\nStep 4: Creating lzss4 blobs...")
    blobs = []
    for i in range(3):
        blob = make_lzss4_blob(new_tilemaps[i])
        blobs.append(blob)
        print(f"  Tilemap {i+1} blob: {len(blob)}B (overhead: {len(blob)-NEW_TILEMAP_SIZE}B)")
    terrain_blob = make_lzss4_blob(new_terrain)
    print(f"  terrain_map blob: {len(terrain_blob)}B (overhead: {len(terrain_blob)-NEW_TERRAIN_SIZE}B)")

    total_needed = len(terrain_blob) + sum(len(b) for b in blobs)
    print(f"\n  Total needed: {total_needed} bytes")

    # Step 5: Find free space and write
    print("\nStep 5: Writing to free space...")

    names = ['packed_tiles1', 'packed_tiles2', 'packed_tiles3', 'terrain_map']
    all_items = list(zip(names, blobs + [terrain_blob]))

    cursor = FREE_SPACE_START
    patches = []

    for name, blob in all_items:
        offset = find_free_space(rom, len(blob), 4)
        # Ensure we don't overlap with previous writes
        if offset < cursor:
            offset = cursor
            while offset + len(blob) <= FREE_SPACE_END:
                region = rom[offset:offset + len(blob)]
                if all(b == 0xFF for b in region):
                    break
                offset += 4

        rom[offset:offset + len(blob)] = blob
        rom_addr = 0x08000000 | offset
        patches.append((name, offset, rom_addr, len(blob)))
        cursor = offset + len(blob)
        print(f"  {name}: 0x{offset:06X} → 0x{rom_addr:08X} ({len(blob)}B)")

    # Step 6: Patch MapData
    print("\nStep 6: Patching MapData for MAP_FARM...")

    # packed_tiles1
    patch_mapdata_entry(rom, MAP_FARM_ID, 0x0C, patches[0][2])
    # packed_tiles2
    patch_mapdata_entry(rom, MAP_FARM_ID, 0x10, patches[1][2])
    # packed_tiles3
    patch_mapdata_entry(rom, MAP_FARM_ID, 0x14, patches[2][2])
    # terrain_map
    patch_mapdata_entry(rom, MAP_FARM_ID, 0x1C, patches[3][2])
    # width and height
    patch_u16(rom, MAP_FARM_ID, 0x20, NEW_W)
    patch_u16(rom, MAP_FARM_ID, 0x22, NEW_H)

    print(f"  width: {OLD_W} → {NEW_W}")
    print(f"  height: {OLD_H} → {NEW_H}")

    # Verify
    print("\nStep 7: Verifying patches...")
    verify_rom = bytes(rom)
    for name, offset, rom_addr, size in patches:
        chunk = bytes(verify_rom[offset:offset + size])
        print(f"  {name} @ 0x{rom_addr:08X}: {len(chunk)}B written")

    # Step 8: Write patched ROM (overwrite input)
    Path(rom_path).write_bytes(rom)
    print(f"\nDone! Patched ROM written to {rom_path}")

    # Show MapData entry
    print(f"\nFinal MapData for MAP_FARM:")
    entry_off = MAPDATA_TABLE + MAP_FARM_ID * MAPDATA_ENTRY_SIZE
    entry_data = rom[entry_off:entry_off + MAPDATA_ENTRY_SIZE]
    for name, fmt, off, desc in [
        ('packed_img',    '<I', 0x00, 'tileset'),
        ('packed_pal1',   '<I', 0x04, 'palette 1'),
        ('packed_pal2',   '<I', 0x08, 'palette 2'),
        ('packed_tiles1', '<I', 0x0C, 'tilemap layer 1'),
        ('packed_tiles2', '<I', 0x10, 'tilemap layer 2'),
        ('packed_tiles3', '<I', 0x14, 'tilemap layer 3'),
        ('terrain_info',  '<I', 0x18, 'terrain attributes'),
        ('terrain_map',   '<I', 0x1C, 'terrain indices'),
        ('width',         '<H', 0x20, 'width'),
        ('height',        '<H', 0x22, 'height'),
        ('is_interior',   '<B', 0x24, 'interior flag'),
    ]:
        val = struct.unpack_from(fmt, entry_data, off)[0]
        print(f"  +0x{off:02X} {name:16s} = 0x{val:08X} ({desc})")


if __name__ == '__main__':
    main()
