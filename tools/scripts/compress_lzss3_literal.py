#!/usr/bin/env python3
"""Popuri LZSS3 all-literal compressor.

Creates format "030" (atom=0, lzss=3, diff=0) data where all bytes
are stored as literals. This is the safest format for tilemaps since
the game definitely supports it (original farm tiles3 was format 030).
"""
import struct

def make_lzss3_literal_blob(raw_data: bytes) -> bytes:
    """Compress raw data as lzss3 literal pairs (2 bytes at a time)."""
    # Header
    header = 0x70 | (len(raw_data) << 8)

    # Build payload: format_byte(1) + ladder_spec(12bits) + data(bits+bytes)
    # lzss3 ladder: 3 entries × 4 bits = 12 bits
    LADDER_BITS = [4, 8, 10]  # distance bits per entry
    ladder_spec = 0
    for i, b in enumerate(LADDER_BITS):
        ladder_spec |= (b - 1) << (i * 4)

    # Pack: ladder_spec as 12 bits + data
    # Bit writer: accumulates bits MSB-first
    buf = 0
    n = 0
    result = bytearray()
    result.append(0)  # format byte: atom=0, lzss=3, diff=0 (0x30 would be... wait)
    # format byte for atom=0, lzss=3, diff=0:
    # bits[2:0] = lzss_fmt = 3
    # bits[4:3] = atom_fmt = 0
    # bits[7:5] = diff_fmt = 0
    # = 3
    result[-1] = 3  # format byte = 3

    def w(val, cnt):
        nonlocal buf, n
        for i in range(cnt-1, -1, -1):
            buf = (buf << 1) | ((val >> i) & 1)
            n += 1
            if n == 8:
                result.append(buf & 0xFF)
                buf = 0; n = 0

    def flush():
        nonlocal buf, n
        if n:
            result.append(buf << (8-n) & 0xFF)
            buf = 0; n = 0

    # Write ladder spec (12 bits)
    w(ladder_spec, 12)

    # Write data as lzss3 literals (2 bytes at a time)
    i = 0
    while i < len(raw_data):
        if i + 1 < len(raw_data):
            # Literal pair: bit=0, then 2 bytes
            w(0, 1)  # literal tag
            w(raw_data[i], 8)
            w(raw_data[i+1], 8)
            i += 2
        else:
            # Odd byte: use short literal
            w(0, 1)
            w(raw_data[i], 8)
            # lzss3 always reads pairs, so pad with 0
            # Actually, lzss3 reads 2 bytes when bit=0
            # If we have an odd byte, we need to handle it
            # For tilemaps this won't happen (always even)
            i += 1

    flush()

    # Pad to 4 bytes and reverse each group for ReadBits
    while len(result) % 4:
        result.append(0)

    bitstream = bytearray()
    for i in range(0, len(result), 4):
        bitstream.extend(result[i:i+4][::-1])

    return struct.pack('<I', header) + bytes(bitstream)

def main():
    import sys
    d = open(sys.argv[1], 'rb').read()
    c = make_lzss3_literal_blob(d)
    open(sys.argv[2], 'wb').write(c)
    print(f"{len(d)}B -> {len(c)}B ({len(c)/len(d)*100:.1f}%)")
    # Verify
    sys.path.insert(0, '.')
    from tools.scripts.decompress import unpack
    r, f, l = unpack(c, 0)
    assert r == d, "Round-trip failed!"
    print(f"Verified: fmt={f}, ladder={l}")

if __name__ == '__main__':
    main()
