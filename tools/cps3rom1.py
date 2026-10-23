#!/usr/bin/env python3
"""Street Fighter III New Generation (CPS3) program ROM tool.

    python tools/cps3rom1.py extract <rom dir> <rom.bin>
        Read the program SIMM from your ROM set in <rom dir> (sfiiina.zip or sfiiin.zip), decrypt it and write the
        parts of the program that this source does not build (tools/rom_pieces.tsv), one after the other, to <rom.bin>.

    python tools/cps3rom1.py pack <sfn.bin> <rom.bin> <rom dir> <out dir>
        Put those parts and the alignment-gap bytes (tools/gaps.tsv) into the linked image, write <out dir>/prog.bin
        (06000000-067FFFFF) and compare it with the arcade program (tools/prog.sha1); encrypt it, split it into the four
        program SIMM chips and write <out dir>/<set>.zip: your ROM set with those chips replaced, in MAME's layout
        (sfiii-simm1.0 ... and the graphics SIMMs and BIOS as they are in your set). Each program chip's CRC and SHA-1
        is printed and compared with the arcade's and with your set's. Exit status 0 only when all of them match.

The ROM set is MAME's sfiiina (Asia 970204, NO CD, BIOS set 2) or sfiiin (BIOS set 1): both have the same program
SIMM, and the output zip takes its name from the BIOS your set carries. A set that stores each SIMM as one file
(10, 30, 31, 40, 41, 50) is read too, and written out in MAME's layout.

SIMM 1 holds the program: four 2 MB flash chips, one byte lane each, together 06000000-067FFFFF in big-endian words.
Every halfword is stored encrypted with the CPS3 address mask (MAME's cps3_state::cps3_mask, keys b5fe053e,
fc03925a), code and data alike, except some parts outside the linked sections that are stored plain
(tools/rom_pieces.tsv, stored = plain).
"""
import hashlib, sys, zipfile, zlib
from pathlib import Path

KEYS = (0xb5fe053e, 0xfc03925a)
SIZE = 0x800000
CHIP = 0x200000
BASE = 0x06000000
HERE = Path(__file__).resolve().parent
BIOS = {0x73e32463: 'sfiiina', 0xca2b715f: 'sfiiin'}
BIOS_NAME = 'sfiii_asia_nocd.29f400.u2'
# the arcade's program SIMM chips (MAME and FBNeo sfiiin / sfiiina)
PROGRAM = {
    'sfiii-simm1.0': ('cfc9e45a', '5d9061f76680642e730373e3ac29b24926dc5c0c'),
    'sfiii-simm1.1': ('57920546', 'c8452e7e101b8888fb806d1c9874c6be49fc7dbd'),
    'sfiii-simm1.2': ('0d8f2680', 'ade7b28acd11023696c4b20136f3d2f34da6b1be'),
    'sfiii-simm1.3': ('ea4ca054', 'f91c55c4e4fc428ce15d27be38aeed3a483d028c'),
}


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


def find_set(romdir):
    """the ROM set zip in <rom dir> (or the zip itself)"""
    p = Path(romdir)
    if p.is_file():
        return p
    for name in ('sfiiina.zip', 'sfiiin.zip'):
        if (p / name).exists():
            return p / name
    sys.exit(f'{romdir}: no sfiiina.zip or sfiiin.zip (see rom/README)')


def chip_split(simm, flat):
    """program SIMM image -> its four chips (one byte lane each)"""
    return {f'sfiii-simm{simm}.{c}': flat[c::4] for c in range(4)}


def chip_join(chips):
    flat = bytearray(SIZE)
    for c in range(4):
        flat[c::4] = chips[c]
    return bytes(flat)


def read_zip(path):
    with zipfile.ZipFile(path) as z:
        return {i.filename.rsplit('/', 1)[-1]: z.read(i.filename) for i in z.infolist() if not i.is_dir()}


def read_set(path):
    """{MAME file name: bytes} of a ROM set in either layout; a split set's shared SIMM files come from sfiii.zip"""
    files = read_zip(path)
    if '10' not in files:
        parent = Path(path).with_name('sfiii.zip')
        if parent.exists():
            for name, b in read_zip(parent).items():
                if name.startswith('sfiii-simm'):
                    files.setdefault(name, b)
        return files
    out = {BIOS_NAME: files[BIOS_NAME]}
    out.update(chip_split(1, files['10']))
    for simm, (lo, hi) in ((3, ('30', '31')), (4, ('40', '41'))):
        for k, flat in enumerate((files[lo], files[hi])):
            half = len(flat) // 2
            for h in range(2):
                part = flat[h * half:(h + 1) * half]
                for c in range(2):
                    out[f'sfiii-simm{simm}.{4 * k + 2 * h + c}'] = part[c::2]
    out['sfiii-simm5.0'] = files['50'][0::2]
    out['sfiii-simm5.1'] = files['50'][1::2]
    return out


def program(files, path):
    try:
        return chip_join([files[f'sfiii-simm1.{c}'] for c in range(4)])
    except KeyError:
        sys.exit(f'{path}: the program SIMM chips sfiii-simm1.0-1.3 are missing')


def extract(romdir, out):
    path = find_set(romdir)
    raw = program(read_set(path), path)
    if hashlib.sha1(raw).hexdigest() != expected()['simm1']:
        print(f'warning: {path}: the program SIMM is not the arcade\'s (sha1 {hashlib.sha1(raw).hexdigest()})')
    dec = crypt(raw)
    data = b''.join(dec[s:e] for s, e, _, _ in pieces())
    Path(out).parent.mkdir(parents=True, exist_ok=True)
    Path(out).write_bytes(data)
    print(f'{out}: {len(pieces())} parts of the program, {len(data)} bytes, read from {path}')


def pack(linked, piecefile, romdir, outdir):
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
    sha = hashlib.sha1(prog).hexdigest()
    ok = sha == want['prog.bin']
    print(f'prog.bin sha1 {sha}: ' + ('matches the arcade program' if ok else f'DIFFERS from the arcade program\'s {want["prog.bin"]}'))
    path = find_set(romdir)
    files = read_set(path)
    bios = zlib.crc32(files.get(BIOS_NAME, b''))
    setname = BIOS.get(bios, 'sfiiina')
    if bios not in BIOS:
        print(f'warning: {path}: BIOS {BIOS_NAME} crc {bios:08x} is neither sfiiina\'s nor sfiiin\'s')
    new = chip_split(1, bytes(crypt(prog)))
    for name, chip in new.items():
        crc, sha = f'{zlib.crc32(chip):08x}', hashlib.sha1(chip).hexdigest()
        arcade = (crc, sha) == PROGRAM[name]
        yours = files.get(name) == chip
        ok &= arcade and yours
        print(f'{name}  crc {crc}  sha1 {sha}: ' + ('identical to the arcade\'s' if arcade else 'DIFFERS from the arcade\'s')
              + ('' if yours else f' (differs from the one in {path.name})'))
    files.update(new)
    zpath = out / f'{setname}.zip'
    with zipfile.ZipFile(zpath, 'w', zipfile.ZIP_DEFLATED) as dst:
        for name in [BIOS_NAME] + sorted(n for n in files if n != BIOS_NAME):
            dst.writestr(name, files[name])
    print(f'{zpath} written (MAME/FBNeo set {setname}); program ' + ('identical to the original' if ok else 'NOT the original'))
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
