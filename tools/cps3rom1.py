#!/usr/bin/env python3
"""Street Fighter III New Generation (CPS3) program ROM tool.

    python tools/cps3rom1.py extract <sfiiin.zip> <rom.bin>
        Read the program file "10" from the ROM set, decrypt it and write the parts of the program that this source
        does not build (tools/rom_pieces.tsv), one after the other, to <rom.bin>.

    python tools/cps3rom1.py pack <sfn.bin> <rom.bin> <sfiiin.zip> <out dir>
        Put those parts and the alignment-gap bytes (tools/gaps.tsv) into the linked image, write
        <out dir>/prog.bin (06000000-067FFFFF) and compare it with the expected image (tools/prog.sha1); encrypt it,
        write <out dir>/10 and <out dir>/sfiiin.zip (the ROM set with "10" replaced), and compare "10" with the
        expected one and with your set's. Exit status 0 only when all three are the original's.

"10" is the CD's program image: 8 MB of big-endian words for 06000000-067FFFFF (no SIMM byte lanes). Every halfword is
stored encrypted with the CPS3 address mask (MAME's cps3_state::cps3_mask, keys b5fe053e, fc03925a), code and data
alike, except some parts outside the linked sections that are stored plain (tools/rom_pieces.tsv, stored = plain).
"""
import hashlib, sys, zipfile
from pathlib import Path

KEYS = (0xb5fe053e, 0xfc03925a)
SIZE = 0x800000
BASE = 0x06000000
HERE = Path(__file__).resolve().parent


def rol16(v, n):
    v &= 0xFFFF
    return ((v << n) | (v >> (16 - n))) & 0xFFFF


def rotxor(val, x):
    res = (val + rol16(val, 2)) & 0xFFFF
    return (rol16(res, 4) ^ (res & (val ^ x))) & 0xFFFF


def mask(addr, key1, key2):
    addr ^= key1
    v = (addr & 0xFFFF) ^ 0xFFFF
    v = rotxor(v, key2 & 0xFFFF)
    v ^= ((addr >> 16) & 0xFFFF) ^ 0xFFFF
    v = rotxor(v, key2 >> 16)
    v ^= (addr & 0xFFFF) ^ (key2 & 0xFFFF)
    return (v | (v << 16)) & 0xFFFFFFFF


def table(name):
    """the rows of a tools/ table (tab-separated; # comments and the column-name line left out)"""
    rows = []
    for l in open(HERE / name, encoding='utf-8'):
        if l.startswith('#') or not l.strip():
            continue
        c = l.rstrip('\n').split('\t')
        if c[0] in ('start', 'address'):
            continue
        rows.append(c)
    return rows


def pieces():
    """[(offset, end offset, stored, what)] of the parts read from the ROM"""
    return [(int(s, 16) - BASE, int(e, 16) - BASE, st, w) for s, e, st, w in table('rom_pieces.tsv')]


def crypt(buf):
    """XOR every halfword with its word's mask, except the parts stored plain (an involution)"""
    out = bytearray(len(buf))
    for o in range(0, len(buf), 4):
        w = int.from_bytes(buf[o:o + 4], 'big') ^ mask(BASE + o, *KEYS)
        out[o:o + 4] = w.to_bytes(4, 'big')
    for s, e, st, _ in pieces():
        if st == 'plain':
            out[s:e] = buf[s:e]
    return out


def expected():
    """{file: sha1} from tools/prog.sha1"""
    return {l.split()[1].rsplit('/', 1)[-1]: l.split()[0] for l in (HERE / 'prog.sha1').read_text().splitlines()
            if l.strip()}


def extract(rom, out):
    raw = zipfile.ZipFile(rom).read('10')
    if len(raw) != SIZE:
        sys.exit(f'{rom}: "10" is {len(raw):#x} bytes, expected {SIZE:#x}')
    if hashlib.sha1(raw).hexdigest() != expected()['10']:
        print(f'warning: {rom}: "10" is not the original sfiiin program (sha1 {hashlib.sha1(raw).hexdigest()})')
    dec = crypt(raw)
    data = b''.join(dec[s:e] for s, e, _, _ in pieces())
    Path(out).parent.mkdir(parents=True, exist_ok=True)
    Path(out).write_bytes(data)
    print(f'{out}: {len(pieces())} parts of the program, {len(data)} bytes, read from {rom}')


def pack(linked, piecefile, rom, outdir):
    prog = bytearray(Path(linked).read_bytes())
    if len(prog) != SIZE:
        sys.exit(f'{linked}: {len(prog):#x} bytes, expected {SIZE:#x}')
    data = Path(piecefile).read_bytes()
    at = 0
    for s, e, _, _ in pieces():
        prog[s:e] = data[at:at + e - s]
        at += e - s
    if at != len(data):
        sys.exit(f'{piecefile}: {len(data)} bytes, tools/rom_pieces.tsv needs {at}: extract it again')
    for a, h, *_ in table('gaps.tsv'):
        b = bytes.fromhex(h)
        prog[int(a, 16) - BASE:int(a, 16) - BASE + len(b)] = b
    out = Path(outdir)
    out.mkdir(parents=True, exist_ok=True)
    (out / 'prog.bin').write_bytes(prog)
    want = expected()
    ok = True
    sha = hashlib.sha1(prog).hexdigest()
    same = sha == want['prog.bin']
    ok &= same
    print(f'prog.bin sha1 {sha}: ' + ('matches the arcade program' if same else f'DIFFERS from the arcade program\'s {want["prog.bin"]}'))
    enc = bytes(crypt(prog))
    (out / '10').write_bytes(enc)
    sha = hashlib.sha1(enc).hexdigest()
    same = sha == want['10']
    ok &= same
    print(f'10 sha1 {sha}: ' + ('matches the original' if same else f'DIFFERS from the original\'s {want["10"]}'))
    with zipfile.ZipFile(rom) as src, zipfile.ZipFile(out / 'sfiiin.zip', 'w', zipfile.ZIP_DEFLATED) as dst:
        for info in src.infolist():
            old = src.read(info.filename)
            if info.filename == '10':
                same = old == enc
                ok &= same
                print(f'10: {"identical to" if same else "DIFFERS from"} the one in {rom}')
                old = enc
            dst.writestr(info, old)
    print(f'{out / "sfiiin.zip"} written; program ' + ('identical to the original' if ok else 'NOT the original'))
    return ok


def main():
    a = sys.argv[1:]
    if len(a) == 3 and a[0] == 'extract':
        extract(a[1], a[2])
    elif len(a) == 5 and a[0] == 'pack':
        sys.exit(0 if pack(*a[1:]) else 1)
    else:
        sys.exit(__doc__)


if __name__ == '__main__':
    main()
