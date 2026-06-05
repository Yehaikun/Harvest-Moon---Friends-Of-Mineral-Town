#!/usr/bin/env python3
"""
FoMT tilemap patcher - handles BOTH generic MapData path and hardcoded farm loader.

Key findings:
- Generic maps: func_080A5CC0 reads packed_tiles1/2/3 from MapData -> modify MapData directly
- Farm (map 2): func_080B55D0 has hardcoded pointers -> must modify BOTH MapData AND literals

Usage:
  python3 tools/patch_tilemap.py <rom> --map <id> <action> [args]
"""
import struct, sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.scripts.decompress import UnpackException, unpack

BASE = 0x08000000

# Hardcoded farm resource pointers in func_080B55D0
FARM_HARDCODED = {
    'tilemap_layer1': {  # packed_tiles1 equivalent
        'literal_addr': 0x080B573C,
        'resource_addr': 0x086FD240,
        'name': 'farm packed_tiles1 (gUnk_086FD240)',
    },
    'tileset': {  # packed_img equivalent
        'literal_addr': 0x080B574C,
        'resource_addr': 0x086FB004,
        'name': 'farm packed_img (gUnk_086FB004)',
    },
    'palette': {  # packed_pal1 equivalent
        'literal_addr': 0x080B5750,
        'resource_addr': 0x086FD19C,
        'name': 'farm packed_pal1 (gUnk_086FD19C)',
    },
}

MAPDATA_TABLE = 0x08105EDC
MAPDATA_SIZE = 0x28

# Popuri compression helpers
def read_popuri_header(data, off):
    """Parse popuri compression header at data[off:]"""
    if data[off] != 0x70:
        return None
    decomp_size = data[off+1] | (data[off+2] << 8) | (data[off+3] << 16)
    fmt_str = "???"
    try:
        _, fmt_str, _ = unpack(data, off)
    except Exception:
        pass
    return {
        'decomp_size': decomp_size,
        'fmt_str': fmt_str,
        'header_size': 4,
    }

def decompress_popuri(data, off):
    """Popuri decompressor using the same bitstream model as the game tools."""
    try:
        return bytes(unpack(data, off)[0])
    except UnpackException:
        return None

def make_lzss3_blob(data):
    """Create a game-compatible all-literal Popuri LZSS3 blob (format 030).

    Format: 0x70 + 3-byte LE size + bitstream
    ReadBits reads 32-bit LE words from bitstream and extracts format
    from the HIGH byte of the first word.
    """
    header = 0x70 | (len(data) << 8)

    # LZSS3 requires a 3-entry distance ladder
    ladder = 0
    for i, bits in enumerate([4, 8, 10]):
        ladder |= (bits - 1) << (i * 4)

    # Payload starts with format byte: atom=0, lzss=3, diff=0 => 0x03
    # After 4-byte reversal, this becomes the MSB of the first bitstream word.
    payload = bytearray([3])  # format "030"
    buf = 0
    bit_count = 0

    def write_bits(value, count):
        nonlocal buf, bit_count
        for i in range(count - 1, -1, -1):
            buf = (buf << 1) | ((value >> i) & 1)
            bit_count += 1
            if bit_count == 8:
                payload.append(buf & 0xFF)
                buf = 0
                bit_count = 0

    write_bits(ladder, 12)
    for i in range(0, len(data), 2):
        write_bits(0, 1)  # literal pair tag
        write_bits(data[i], 8)
        write_bits(data[i + 1] if i + 1 < len(data) else 0, 8)

    if bit_count:
        payload.append((buf << (8 - bit_count)) & 0xFF)

    # Pad to 4-byte alignment (ReadBits reads 32-bit LE words)
    while len(payload) % 4:
        payload.append(0)

    # ReadBits reads LE words and extracts high bits first.
    # Reverse each 4-byte chunk so the format byte (payload[0])
    # becomes the MSB of the first word after reversal.
    bitstream = bytearray()
    for i in range(0, len(payload), 4):
        bitstream.extend(payload[i:i + 4][::-1])

    return struct.pack('<I', header) + bytes(bitstream)

def build_tilemap(width, height, tile_data=None):
    """Build a raw tilemap (2 bytes per tile)."""
    num_tiles = width * height
    tm = bytearray(num_tiles * 2)

    if tile_data:
        # Copy provided tile data
        for i, val in enumerate(tile_data):
            if i * 2 + 1 < len(tm):
                struct.pack_into('<H', tm, i * 2, val & 0xFFFF)
    else:
        # Default: fill with tile 0 + palette 0
        pass

    return bytes(tm)

def show_rom_info(rom):
    """Dump key info about the ROM."""
    print(f"ROM size: {len(rom)} bytes ({len(rom)//1024//1024}MB)")

    # Show MapData for all maps
    print(f"\n{'Map':>4} {'Width':>6} {'Height':>7} {'packed_tiles1':>18} {'packed_tiles2':>18} {'packed_tiles3':>18}")
    print("-" * 75)
    for map_id in range(66):
        eo = MAPDATA_TABLE - BASE + map_id * 0x28
        w = struct.unpack_from('<H', rom, eo + 0x20)[0]
        h = struct.unpack_from('<H', rom, eo + 0x22)[0]
        t1 = struct.unpack_from('<I', rom, eo + 0x0C)[0]
        t2 = struct.unpack_from('<I', rom, eo + 0x10)[0]
        t3 = struct.unpack_from('<I', rom, eo + 0x14)[0]
        print(f"{map_id:4d} {w:6d} {h:7d} 0x{t1:08X} 0x{t2:08X} 0x{t3:08X}")

    # Show hardcoded farm pointers
    print(f"\nHardcoded farm loader (func_080B55D0) pointers:")
    for key, info in FARM_HARDCODED.items():
        current_val = struct.unpack_from('<I', rom, info['literal_addr'] - BASE)[0]
        print(f"  {key}: literal at 0x{info['literal_addr']:08X} -> 0x{current_val:08X} (expected 0x{info['resource_addr']:08X})")

def patch_map_tilemap(rom, map_id, new_tilemap_data, match_hardcoded=False):
    """
    Patch packed_tiles1 for a given map.

    If match_hardcoded=True and this is the farm, also update hardcoded literals.
    """
    eo = MAPDATA_TABLE - BASE + map_id * 0x28
    old_ptr = struct.unpack_from('<I', rom, eo + 0x0C)[0]

    w = struct.unpack_from('<H', rom, eo + 0x20)[0]
    h = struct.unpack_from('<H', rom, eo + 0x22)[0]
    expected_size = w * h * 2

    if len(new_tilemap_data) != expected_size:
        print(f"WARNING: tilemap data size {len(new_tilemap_data)} != expected {expected_size} (w={w}*h={h}*2)")

    # Compress
    compressed = make_lzss3_blob(new_tilemap_data)
    print(f"Compressed tilemap: {len(new_tilemap_data)}B -> {len(compressed)}B lzss3 blob")

    # Find a free space to write the compressed data
    ptr = old_ptr
    if ptr >= BASE:
        off = ptr - BASE
        # Check if we can overwrite in place (same format, similar size)
        # Actually, let's append to free space instead
        pass

    # Write the new compressed data at the END of used ROM space
    # Scan from end for free space
    for candidate in range(0x08700000, 0x08800000, 4):
        c_off = candidate - BASE
        if c_off + len(compressed) >= len(rom):
            break
        # Check if all 0xFF
        if all(b == 0xFF for b in rom[c_off:c_off + len(compressed)]):
            rom[c_off:c_off + len(compressed)] = compressed

            # Update MapData pointer
            new_ptr = candidate
            struct.pack_into('<I', rom, eo + 0x0C, new_ptr)
            print(f"Updated MapData[{map_id}].packed_tiles1: 0x{old_ptr:08X} -> 0x{new_ptr:08X}")

            # Also update hardcoded literals if this is the farm
            if match_hardcoded and map_id == 2:
                for key, info in FARM_HARDCODED.items():
                    if 'tilemap' in key:
                        struct.pack_into('<I', rom, info['literal_addr'] - BASE, new_ptr)
                        print(f"  Also updated hardcoded literal at 0x{info['literal_addr']:08X} -> 0x{new_ptr:08X}")

            return candidate

    print("ERROR: Could not find free space!")
    return None

def main():
    if len(sys.argv) < 3:
        print("Usage:")
        print(f"  {sys.argv[0]} <rom> --info")
        print(f"  {sys.argv[0]} <rom> --map <id> --replace-tile <x> <y> <tile_id> <pal>")
        print(f"  {sys.argv[0]} <rom> --map <id> --set-tilemap <file.bin> [--match-hardcoded]")
        return

    rom_path = sys.argv[1]
    rom = bytearray(open(rom_path, 'rb').read())

    if '--info' in sys.argv:
        show_rom_info(rom)
        return

    if '--map' in sys.argv:
        idx = sys.argv.index('--map')
        map_id = int(sys.argv[idx + 1])

        eo = MAPDATA_TABLE - BASE + map_id * 0x28
        w = struct.unpack_from('<H', rom, eo + 0x20)[0]
        h = struct.unpack_from('<H', rom, eo + 0x22)[0]

        if '--replace-tile' in sys.argv:
            ti = sys.argv.index('--replace-tile')
            x = int(sys.argv[ti + 1])
            y = int(sys.argv[ti + 2])
            tile_id = int(sys.argv[ti + 3])
            pal = int(sys.argv[ti + 4])

            # Read existing tilemap, decompress it
            ptr = struct.unpack_from('<I', rom, eo + 0x0C)[0]
            decompressed = decompress_popuri(rom, ptr - BASE)
            if not decompressed:
                print(f"ERROR: Could not decompress packed_tiles1 at 0x{ptr:08X}")
                return

            print(f"Map {map_id}: {w}x{h}, tilemap at 0x{ptr:08X}")
            print(f"Decompressed: {len(decompressed)} bytes, expected {w*h*2}")

            # Modify the tile
            idx2 = (y * w + x) * 2
            if idx2 + 1 >= len(decompressed):
                print(f"ERROR: Position ({x},{y}) out of range")
                return
            val = tile_id | (pal << 12)
            decompressed = bytearray(decompressed)
            struct.pack_into('<H', decompressed, idx2, val)
            print(f"Modified tile at ({x},{y}): tile_id={tile_id}, pal={pal} -> value=0x{val:04X}")

            match_hc = '--match-hardcoded' in sys.argv
            new_ptr = patch_map_tilemap(rom, map_id, bytes(decompressed), match_hardcoded=match_hc)
            if new_ptr:
                open(rom_path, 'wb').write(bytes(rom))
                print(f"ROM saved to {rom_path}")

        elif '--set-tilemap' in sys.argv:
            ti = sys.argv.index('--set-tilemap')
            tilemap_file = sys.argv[ti + 1]
            with open(tilemap_file, 'rb') as f:
                tilemap_data = f.read()
            match_hc = '--match-hardcoded' in sys.argv
            new_ptr = patch_map_tilemap(rom, map_id, tilemap_data, match_hardcoded=match_hc)
            if new_ptr:
                open(rom_path, 'wb').write(bytes(rom))
                print(f"ROM saved to {rom_path}")

if __name__ == '__main__':
    main()
