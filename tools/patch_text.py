#!/usr/bin/env python3
"""Patch dialogue text in FoMT scripts.

Usage:
  python3 tools/patch_text.py fomt.gba --script 167 --update "New text"
  python3 tools/patch_text.py fomt.gba --script 143 --list
"""

from __future__ import annotations
import struct, sys, json
from pathlib import Path

SCRIPT_TABLE = 0x0F89D4
SCRIPT_COUNT = 1328

def read_u32(data, off):
    return struct.unpack_from('<I', data, off)[0]

def write_u32(data, off, val):
    struct.pack_into('<I', data, off, val)

def get_script_ptr(rom, sid):
    off = SCRIPT_TABLE + (sid - 1) * 4
    return read_u32(rom, off)

def get_script(rom, sid):
    ptr = get_script_ptr(rom, sid)
    if ptr == 0:
        return None, None
    file_off = ptr & 0x1FFFFFF
    if rom[file_off:file_off+4] != b'RIFF':
        return None, None
    size = read_u32(rom, file_off + 4) + 8
    return size, file_off

def extract_strings(rom, sid):
    ptr = get_script_ptr(rom, sid)
    if ptr == 0:
        return []
    file_off = ptr & 0x1FFFFFF
    if rom[file_off:file_off+4] != b'RIFF':
        return []
    size = read_u32(rom, file_off + 4) + 8

    strings = []
    pos = file_off + 12
    while pos < file_off + size - 8:
        ctype = rom[pos:pos+4]
        csize = read_u32(rom, pos + 4)
        if ctype == b'STR ':
            str_data = rom[pos+8:pos+8+csize]
            text_start = 12  # skip header(8) + count(4)
            if csize > text_start:
                tdata = str_data[text_start:]
                tpos = 0
                while tpos < len(tdata):
                    if tdata[tpos] in (0x00, 0x05):
                        tpos += 1
                        continue
                    end = tdata.find(b'\x05', tpos)
                    if end == -1:
                        break
                    text = tdata[tpos:end]
                    if text:
                        strings.append({
                            "offset": pos + 8 + text_start + tpos,
                            "text": text.decode('ascii', errors='replace'),
                            "raw": text.hex()
                        })
                    tpos = end + 1
            break
        pos += 8 + csize
        if pos % 2:
            pos += 1
    return strings

def list_strings(rom, sid):
    strings = extract_strings(rom, sid)
    print(f"Script {sid}: {len(strings)} strings")
    for i, s in enumerate(strings):
        print(f"  [{i}] @0x{s['offset']:06X}: \"{s['text']}\"")

def update_string(rom, sid, idx, new_text):
    """Update a specific string in a script.
    NOTE: Only works if new text fits in the original slot size.
    For longer text, the script would need relocation.
    """
    strings = extract_strings(rom, sid)
    if idx < 0 or idx >= len(strings):
        print(f"Error: string index {idx} out of range (0-{len(strings)-1})")
        return False

    target = strings[idx]
    old_raw = bytes.fromhex(target['raw'])
    new_raw = new_text.encode('ascii') + b'\x05'

    if len(new_raw) > len(old_raw) + 1:
        # Text too long - would need script relocation
        # For now, truncate to fit
        new_raw = new_raw[:len(old_raw)]
        print(f"Warning: text truncated to {len(old_raw)} bytes")

    # Pad if shorter
    while len(new_raw) < len(old_raw):
        new_raw = bytes([0x00]) + new_raw

    offset = target['offset']
    rom[offset:offset+len(new_raw)] = new_raw
    print(f"Updated string [{idx}] at 0x{offset:06X}: \"{new_text}\"")
    return True

def main():
    rom = bytearray(Path(sys.argv[1]).read_bytes())
    sid = None
    idx = None
    new_text = None
    do_list = False

    for i, arg in enumerate(sys.argv):
        if arg == '--script' and i+1 < len(sys.argv):
            sid = int(sys.argv[i+1])
        if arg == '--list':
            do_list = True
        if arg == '--update' and i+1 < len(sys.argv):
            new_text = sys.argv[i+1]
        if arg == '--index' and i+1 < len(sys.argv):
            idx = int(sys.argv[i+1])

    if not sid:
        # List all scripts with text
        count = 0
        for s in range(1, SCRIPT_COUNT + 1):
            strings = extract_strings(rom, s)
            if strings:
                count += 1
        print(f"Total scripts with dialogue: {count}")
        return

    if do_list:
        list_strings(rom, sid)
        return

    if new_text is not None:
        if idx is None:
            idx = 0
        update_string(rom, sid, idx, new_text)
        # Save
        Path(sys.argv[1]).write_bytes(bytes(rom))
        return

    list_strings(rom, sid)

if __name__ == '__main__':
    main()
