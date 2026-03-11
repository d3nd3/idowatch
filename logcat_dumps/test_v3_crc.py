#!/usr/bin/env python3
"""
Test CRC16 algorithm against v3 packet CRCs from logcat_dumps.

V3 packet format (from TOOBUR.md and logcat): 33 DA AD DA AD [len_lo] [len_hi] [payload...]
Payload = data (total_len - 2 bytes) + CRC (2 bytes, little-endian: crc_lo, crc_hi).
So CRC is computed over the first (total_len - 2) bytes of the payload (bytes 7 to 7+total_len-2).

Extract test vectors from logcat lines (TX : / RX :) and try common CRC-16 variants.
Run from repo root: `python3 logcat_dumps/test_v3_crc.py`

Finds v3 packets (33 DA AD DA AD ...) in logcat_dumps/*.txt, treats last 2 bytes of payload as CRC (LE),
and tests CRC-16-CCITT and CRC-16-IBM over the preceding bytes. As of 2026-03 no captured vector
matched a standard algorithm; the firmware may use a custom CRC or different byte range (TOOBUR: "device didn't check").
"""

import os
import re

def parse_hex(s):
    s = re.sub(r"[^0-9A-Fa-f]", "", s.strip())
    if len(s) % 2:
        return bytes()
    return bytes.fromhex(s)

def crc16_ccitt(data, init=0xFFFF):
    """CRC-16-CCITT: poly 0x1021, init 0xFFFF. No reflection (same as used in confirmed-only.html)."""
    crc = init
    for b in data:
        crc ^= b << 8
        for _ in range(8):
            crc = (crc << 1) ^ 0x1021 if (crc & 0x8000) else (crc << 1)
            crc &= 0xFFFF
    return crc

def crc16_ibm(data):
    """CRC-16-IBM/ARC: poly 0x8005, init 0xFFFF, reflected."""
    crc = 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if (crc & 1) else (crc >> 1)
            crc &= 0xFFFF
    return crc

def extract_hex_from_logcat(dir_path):
    """Yield (source_file, line_label, hex_str) from TX : / RX : lines."""
    for fn in sorted(os.listdir(dir_path)):
        if not fn.endswith(".txt") or fn.startswith("test_"):
            continue
        path = os.path.join(dir_path, fn)
        try:
            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                for line in f:
                    m = re.search(r"(TX|RX)\s*:\s*([0-9A-Fa-f\s]+)", line)
                    if m:
                        yield fn, m.group(1), m.group(2).strip()
        except Exception as e:
            print("Skip %s: %s" % (fn, e))

def build_vectors(logcat_dir):
    """Build list of (name, data_bytes, expected_crc_le). Only v3 packets (33 DA AD DA AD)."""
    vectors = []
    for fn, kind, hex_str in extract_hex_from_logcat(logcat_dir):
        raw = parse_hex(hex_str)
        if len(raw) < 9:
            continue
        if raw[0] != 0x33 or raw[1] != 0xDA or raw[2] != 0xAD or raw[3] != 0xDA or raw[4] != 0xAD:
            continue
        # Payload = everything after 7-byte header
        payload = raw[7:]
        if len(payload) < 3:
            continue
        # Last 2 bytes = CRC (LE); data = bytes 1 to len-3 (excluding leading 0x33 and CRC)
        data = raw[1: len(raw) - 2]
        expected = payload[len(payload) - 2] | (payload[len(payload) - 1] << 8)
        name = "%s %s (payload=%dB)" % (fn, kind, len(payload))
        vectors.append((name, data, expected))
    return vectors

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    vectors = build_vectors(script_dir)
    if not vectors:
        print("No complete v3 packets (33 DA AD DA AD ...) found in logcat_dumps.")
        print("Add logcat lines with full hex to test.")
        return

    algorithms = [
        ("CRC-16-CCITT (init 0xFFFF)", lambda d: crc16_ccitt(d, 0xFFFF)),
        ("CRC-16-CCITT (init 0)", lambda d: crc16_ccitt(d, 0)),
        ("CRC-16-IBM/ARC", crc16_ibm),
    ]

    any_match = False
    for name, data, expected in vectors:
        print("\n%s  data_len=%d  expected_CRC_LE=0x%04X" % (name, len(data), expected))
        for algo_name, algo_fn in algorithms:
            got = algo_fn(data)
            match = " *** MATCH ***" if got == expected else ""
            print("  %s: 0x%04X%s" % (algo_name, got, match))
            if got == expected:
                any_match = True

    if not any_match and vectors:
        print("\n(No algorithm matched. CRC may be custom or over a different byte range.)")
        print("See TOOBUR.md: 'some sort of CRC16'; device didn't check.")

if __name__ == "__main__":
    main()
