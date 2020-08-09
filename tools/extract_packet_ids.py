#!/bin/python3
import sys
import re
has_pe = True
try:
    import pefile
except Exception as e:
    has_pe = False

RE_VER = re.compile(rb'\x01\x00P\x00r\x00o\x00d\x00u\x00c\x00t\x00V\x00e\x00r\x00s\x00i\x00o\x00n\x00\x00\x00((?:[0-9\.]\x00)+)\x00\x00')

def find_REL(data, what):
    pat = b''.join([re.escape(bytes.fromhex(c)) if c.isalnum() else bytes(c, 'utf-8') for c in what.split()])
    r = re.compile(pat, re.DOTALL+re.MULTILINE).search(data)
    call = r.start()
    offset_start = r.span(1)[0]
    call_start = offset_start + len(r.group(1))
    offset = int.from_bytes(r.group(1), byteorder='little', signed=True)
    return call_start + offset

def read_num(data):
    return int.from_bytes(data, signed=False, byteorder='little')

def write_num(num, size=4):
    return num.to_bytes(size, signed = False, byteorder='little')

def read_zstring(data):
    end = data.index(b'\0')
    assert(end != -1)
    return data[:end].decode('ascii')

def read_zstring_ptr(data, ptr):
    offset = read_num(data[ptr:ptr+4])
    offset -= base
    return read_zstring(data[offset:])

data = bytes()
base = 0x400000
signature = None
version = "<UNKNOWN>"
if has_pe:
    pe = pefile.PE(sys.argv[1], fast_load=True)
    data = bytes(pe.get_memory_mapped_image())
    base = pe.OPTIONAL_HEADER.ImageBase
    signature = pe.OPTIONAL_HEADER.CheckSum
    # version = pe.VS_FIXEDFILEINFO.ProductVersionMS
else:
    data = open(sys.argv[1], "rb").read()
    e_lfanew = int.from_bytes(data[0x3C:][:4], byteorder='little', signed=False)
    base = int.from_bytes(data[e_lfanew + 0x34:][:4], byteorder='little', signed=False)
    signature = int.from_bytes(data[e_lfanew + 0x58:][:4], byteorder='little', signed=False)

version_match = RE_VER.search(data)
if version_match:
    version = version_match.group(1).decode('utf-16le')

dummy_offset = data.index(b"PKT_Dummy\0")
assert(dummy_offset != -1)
dummy_offset += base
start_offset = data.index(b"\x68" + write_num(dummy_offset, 4))
assert(start_offset != -1)

offset =  start_offset
packets = []
name = None
id = 0

while True:
    c = data[offset]
    offset += 1
    if c == 0x68:
        name = read_zstring_ptr(data, offset)
        offset += 4
    elif c == 0xC7:
        assert(data[offset] == 0x04)
        offset += 1
        assert(data[offset] == 0x24)
        offset += 1
        name = read_zstring_ptr(data, offset)
        offset += 4
    elif c == 0x33:
        assert(data[offset] == 0xF6)
        offset += 1
        id = 0
    elif c == 0x66:
        c = data[offset]
        offset += 1
        if c == 0x33:
            assert(data[offset] == 0xC0)
            id = 0
            offset += 1
        elif c == 0xB8:
            id = read_num(data[offset:offset+2])
            offset += 2
        else:
            raise Exception(f"Invalid instruction {offset:08X}")
    elif c == 0xBE:
        assert(name != None)
        id = read_num(data[offset:offset+4])
        offset += 4
    elif c == 0xE8:
        packets.append((name, id))
        offset += 4
    elif c == 0x83:
        offset += 2
    elif c >= 0x58 and c <= 0x5F:
        pass
    elif c == 0xC3:
        break
    else:
        raise Exception(f"Invalid instruction {offset:08X}")

packets.sort(key=lambda x: x[1])
#print(f"// Version: {version}")
#print(f"// Signature: 0x{signature:08X}")
print("enum pkttype_e")
print("{")
for name, id in packets:
    print(f"    {name} = 0x{id:X},")
print("};")
