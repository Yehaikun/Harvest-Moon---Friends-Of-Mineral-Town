#!/usr/bin/env python3
"""Popuri LZSS compressor - recompress tilemap data for ROM patching."""

from __future__ import annotations
import struct
import sys
from pathlib import Path


def _lzss_find_match(data: bytes, pos: int, max_dist: int) -> tuple[int, int]:
    """Find the longest match for position `pos` within `max_dist` bytes back."""
    best_len = 0
    best_dist = 0
    window_start = max(0, pos - max_dist)
    for dist in range(1, pos - window_start + 1):
        match_pos = pos - dist
        if data[match_pos] != data[pos]:
            continue
        length = 1
        while (pos + length < len(data) and
               length < 259 and
               data[match_pos + length] == data[pos + length]):
            length += 1
        if length > best_len:
            best_len = length
            best_dist = dist
            if length >= 259:
                break
    return best_len, best_dist


def compress(data: bytes) -> bytes:
    """Compress raw data using popuri LZSS format (atom=0, lzss=0, diff=0)."""
    header = 0x70 | (len(data) << 8)
    result = bytearray()
    result += struct.pack("<I", header)

    # Format byte: atom_fmt=0, lzss_fmt=0, diff_fmt=0
    format_byte = 0
    result.append(format_byte)

    # Bit stream buffer - we'll pack bits into bytes
    bit_buf = 0
    bit_pos = 0
    raw_buf = bytearray()

    pos = 0
    while pos < len(data):
        # Try to find a match
        best_len, best_dist = _lzss_find_match(data, pos, 4096)

        if best_len >= 3 and best_dist <= 4096:
            # Emit compressed: flag bit = 1
            bit_buf |= (1 << (7 - bit_pos))
            bit_pos += 1

            # Encode (length-3, dist) as 2 bytes + distance
            length_code = best_len - 3
            if length_code <= 15 and best_dist <= 4095:
                # Short form: 1 nibble length + 12 bits distance = 2 bytes
                enc = (length_code << 12) | best_dist
                result += struct.pack("<H", enc)
            else:
                # Long form: 4 bits (0xF) + 12 bits dist, then extra length byte
                enc = (0xF << 12) | best_dist
                result += struct.pack("<H", enc)
                result.append(best_len - 3 - 15)

            pos += best_len
        else:
            # Emit raw byte: flag bit = 0
            bit_pos += 1
            raw_buf.append(data[pos])
            pos += 1

        # Flush bit buffer every 8 bits
        if bit_pos == 8:
            # Insert flag bits before raw bytes
            result.append(bit_buf)
            result += raw_buf
            bit_buf = 0
            bit_pos = 0
            raw_buf = bytearray()

    # Flush remaining bits and raw bytes
    if bit_pos > 0 or raw_buf:
        result.append(bit_buf)
        result += raw_buf

    # Pad to 4-byte boundary
    while len(result) % 4:
        result.append(0)

    return bytes(result)


def main() -> int:
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} INPUT OUTPUT")
        return 1

    data = Path(sys.argv[1]).read_bytes()
    compressed = compress(data)
    Path(sys.argv[2]).write_bytes(compressed)
    print(f"Compressed: {len(data)}B -> {len(compressed)}B ({len(compressed)/len(data)*100:.1f}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
