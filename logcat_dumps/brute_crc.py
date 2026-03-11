import os
import re

def parse_hex(s):
    s = re.sub(r"[^0-9A-Fa-f]", "", s.strip())
    if len(s) % 2: return bytes()
    return bytes.fromhex(s)

def crc16_ccitt(data, init=0xFFFF):
    crc = init
    for b in data:
        crc ^= b << 8
        for _ in range(8):
            crc = (crc << 1) ^ 0x1021 if (crc & 0x8000) else (crc << 1)
            crc &= 0xFFFF
    return crc

def crc16_ibm(data):
    crc = 0xFFFF
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if (crc & 1) else (crc >> 1)
            crc &= 0xFFFF
    return crc

def extract_hex_from_logcat(dir_path):
    for fn in sorted(os.listdir(dir_path)):
        if not fn.endswith(".txt") or fn.startswith("test_"): continue
        path = os.path.join(dir_path, fn)
        try:
            with open(path, "r", encoding="utf-8", errors="ignore") as f:
                for line in f:
                    m = re.search(r"(TX|RX)\s*:\s*([0-9A-Fa-f\s]+)", line)
                    if m: yield fn, m.group(1), m.group(2).strip()
        except: pass

vectors = []
script_dir = "/home/dinda/git-projects/d3nd3/public/idowatch/logcat_dumps"
for fn, kind, hex_str in extract_hex_from_logcat(script_dir):
    raw = parse_hex(hex_str)
    if len(raw) < 9: continue
    if raw[0:5] != b'\x33\xda\xad\xda\xad': continue
    
    payload = raw[7:]
    if len(payload) < 3: continue
    
    expected = payload[-2] | (payload[-1] << 8)
    if expected == 0: continue # Skip where padding is 0000 dummy CRC
    name = "%s %s" % (fn, kind)
    vectors.append((name, raw, expected))

algorithms = [
    ("CRC-16-CCITT (init 0xFFFF)", lambda d: crc16_ccitt(d, 0xFFFF)),
    ("CRC-16-CCITT (init 0)", lambda d: crc16_ccitt(d, 0)),
    ("CRC-16-IBM/ARC", crc16_ibm),
]

for name, raw, expected in vectors:
    print(f"\nTesting vector {name} expected=0x{expected:04X}")
    # Try different slices
    slices = [
        ("payload only", raw[7:-2]),
        ("full header+len+payload", raw[:-2]),
        ("len+payload", raw[5:-2]),
        ("header+len+payload, len-2", raw[:-4] + raw[-4:-2]), # if length doesn't include crc?
    ]
    for slice_name, data in slices:
        for algo_name, algo_fn in algorithms:
            got = algo_fn(data)
            if got == expected:
                print(f"  *** MATCH *** Slice: {slice_name}, Algo: {algo_name}")
