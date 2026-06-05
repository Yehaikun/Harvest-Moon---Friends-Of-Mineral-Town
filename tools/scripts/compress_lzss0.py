#!/usr/bin/env python3
"""Popuri LZSS0 compressor. Creates valid popuri-format compressed data.

lzss0 format: atom=0(raw), lzss=0, diff=0(none)
Byte-reverses 4-byte groups for ReadBits compatibility.
"""

from __future__ import annotations
import struct

def make_lzss0_blob(raw_data: bytes) -> bytes:
    LADDER = [(1, 4), (17, 8)]

    # ladder spec: entry0 high nibble (first read), entry1 low nibble
    ladder_spec = ((LADDER[0][1] - 1) << 4) | (LADDER[1][1] - 1)

    # payload = format byte (0) + ladder_spec + bit-packed data
    payload = bytearray([0, ladder_spec])

    # Bit writer: accumulates bits MSB-first, flushes to bytearray
    buf = 0
    n = 0
    def w(val, cnt):
        nonlocal buf, n
        for i in range(cnt-1, -1, -1):
            buf = (buf << 1) | ((val >> i) & 1)
            n += 1
            if n == 8:
                payload.append(buf & 0xFF)
                buf = 0; n = 0
    def flush():
        nonlocal buf, n
        if n:
            payload.append(buf << (8-n) & 0xFF)
            buf = 0; n = 0

    raw = bytearray(raw_data)
    pos = 0
    while pos < len(raw):
        # Find best back-reference
        best_len, best_dist = 0, 0
        ws = max(0, pos - 272)
        for d in range(1, pos - ws + 1):
            if raw[pos-d] != raw[pos]:
                continue
            ml = 1
            while pos+ml < len(raw) and ml < 66 and raw[pos-d+ml] == raw[pos+ml]:
                ml += 1
            if ml > best_len:
                best_len, best_dist = ml, d
                if ml >= 66:
                    break

        # RLE check
        rle = 1
        while pos+rle < len(raw) and rle < 65 and raw[pos+rle] == raw[pos]:
            rle += 1

        if best_len >= 3 and best_len >= rle:
            if best_dist <= 16:
                w(0, 2); w(best_dist-1, 4)
            else:
                w(1, 2); w(best_dist-17, 8)
            w(best_len-3, 6)
            pos += best_len
        elif rle >= 3:
            w(3, 2); w(rle-2, 6); w(raw[pos], 8)
            pos += rle
        else:
            start = pos; pos += 1
            while pos < len(raw):
                can = False
                for d in range(1, min(273, pos)):
                    if pos+3 <= len(raw) and raw[pos-d:pos-d+3] == raw[pos:pos+3]:
                        can = True; break
                if pos+1 < len(raw) and raw[pos] == raw[pos+1]:
                    can = True
                if can:
                    break
                pos += 1
                if pos - start >= 64:
                    break
            cnt = pos - start
            w(2, 2); w(cnt-1, 6)
            for i in range(start, pos):
                w(raw[i], 8)

    flush()

    # Pad to 4 bytes and reverse each group
    while len(payload) % 4:
        payload.append(0)
    bs = bytearray()
    for i in range(0, len(payload), 4):
        bs.extend(payload[i:i+4][::-1])

    header = struct.pack('<I', 0x70 | (len(raw_data) << 8))
    return header + bytes(bs)


def main():
    import sys
    d = open(sys.argv[1], 'rb').read()
    c = make_lzss0_blob(d)
    open(sys.argv[2], 'wb').write(c)
    print(f"{len(d)}B -> {len(c)}B ({len(c)/len(d)*100:.1f}%)")
    # verify
    import sys
    sys.path.insert(0, '.')
    from tools.scripts.decompress import unpack
    r, f, l = unpack(c, 0)
    assert r == d, "Round-trip failed!"
    print(f"Verified: fmt={f}, ladder={l}")

if __name__ == '__main__':
    main()
