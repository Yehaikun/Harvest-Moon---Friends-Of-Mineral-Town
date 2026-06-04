#!/usr/bin/env python3
"""Extract dialogue text from FoMT RIFF/SCR scripts.

Usage:
  python3 tools/extract_text.py fomt.gba                  # Extract all dialogue
  python3 tools/extract_text.py fomt.gba --script 167     # Extract script 167
  python3 tools/extract_text.py fomt.gba --output texts/  # Output directory
"""

from __future__ import annotations
import struct, sys, json
from pathlib import Path

SCRIPT_TABLE_OFFSET = 0x0F89D4
SCRIPT_COUNT = 1328

def read_u32(data: bytes, off: int) -> int:
    return struct.unpack_from('<I', data, off)[0]

def extract_script_strings(data: bytes, offset: int, max_size: int = 4096) -> list[str]:
    """Extract all dialogue strings from a RIFF/SCR script."""
    if data[offset:offset+4] != b'RIFF':
        return []

    riff_size = read_u32(data, offset+4)
    actual_size = min(riff_size + 8, max_size)

    strings = []
    pos = offset + 12  # After RIFF header (8) + type (4)

    while pos < offset + actual_size - 8:
        chunk_type = data[pos:pos+4]
        chunk_size = read_u32(data, pos+4)

        if chunk_type == b'STR ':
            str_data = data[pos+8:pos+8+chunk_size]
            # Format: count(4B) + zeros(8B) + text1\x05 + text2\x05...
            text_start = pos + 8 + 12  # After STR header + count + zeros
            if chunk_size > 12:
                text_block = data[text_start:pos+8+chunk_size]
                tpos = 0
                while tpos < len(text_block):
                    if text_block[tpos] == 0x05:
                        tpos += 1
                        continue
                    if text_block[tpos] == 0:
                        tpos += 1
                        continue
                    end = text_block.find(b'\x05', tpos)
                    if end == -1:
                        break
                    text = text_block[tpos:end]
                    if text:
                        try:
                            strings.append(text.decode('ascii', errors='replace'))
                        except:
                            strings.append(text.hex())
                    tpos = end + 1
            break

        pos += 8 + chunk_size
        if pos % 2:
            pos += 1

    return strings

def main():
    rom_path = sys.argv[1] if len(sys.argv) > 1 else 'fomt.gba'
    rom = Path(rom_path).read_bytes()

    script_id = None
    output_dir = None

    for i, arg in enumerate(sys.argv):
        if arg == '--script' and i + 1 < len(sys.argv):
            script_id = int(sys.argv[i+1])
        if arg == '--output' and i + 1 < len(sys.argv):
            output_dir = Path(sys.argv[i+1])

    if script_id:
        # Extract single script
        script_off = SCRIPT_TABLE_OFFSET + (script_id - 1) * 4
        ptr = read_u32(rom, script_off)
        if ptr == 0:
            print(f"Script {script_id}: empty slot")
            return

        file_off = ptr & 0x1FFFFFF
        # Get size from RIFF header
        if rom[file_off:file_off+4] == b'RIFF':
            total_size = read_u32(rom, file_off+4) + 8
        else:
            total_size = 4096

        strings = extract_script_strings(rom, file_off, total_size)
        print(f"Script {script_id} @ 0x{ptr:08X} ({total_size}B): {len(strings)} strings")
        for i, s in enumerate(strings):
            print(f"  [{i}] \"{s}\"")
    else:
        # Extract all scripts
        all_strings = {}
        for sid in range(1, SCRIPT_COUNT + 1):
            script_off = SCRIPT_TABLE_OFFSET + (sid - 1) * 4
            ptr = read_u32(rom, script_off)
            if ptr == 0:
                continue

            file_off = ptr & 0x1FFFFFF
            if rom[file_off:file_off+4] != b'RIFF':
                continue

            total_size = read_u32(rom, file_off+4) + 8
            strings = extract_script_strings(rom, file_off, total_size)
            if strings:
                all_strings[sid] = strings

        print(f"Total: {len(all_strings)} scripts with dialogue")

        if output_dir:
            output_dir.mkdir(parents=True, exist_ok=True)
            for sid, strings in all_strings.items():
                (output_dir / f"script_{sid}.txt").write_text(
                    '\n---\n'.join(strings), encoding='utf-8')
            json.dump({str(k): v for k, v in all_strings.items()},
                      open(output_dir / 'all_text.json', 'w', encoding='utf-8'),
                      ensure_ascii=False, indent=2)
            print(f"Saved to {output_dir}/")
        else:
            # Print summary
            for sid in sorted(all_strings.keys())[:10]:
                print(f"  Script {sid}: {len(all_strings[sid])} strings")
            if len(all_strings) > 10:
                print(f"  ... and {len(all_strings)-10} more scripts")

if __name__ == '__main__':
    main()
