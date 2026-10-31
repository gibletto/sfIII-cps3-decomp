# Street Fighter III New Generation - CPS3 program source

**AI Disclosure**:
Yes, this used Claude, as the 3rd Strike and 2nd Impact decomps did. New Generation has no debug symbols of its own:
the finished [3rd Strike](https://github.com/gibletto/sfIII3-cps3-decomp) and
[2nd Impact](https://github.com/gibletto/sfIII2-cps3-decomp) decomps were the reference for its layout and names, and
the names of the files here follow Capcom's 3rd Strike file names (New Generation's own modules are named in the same
style).

## What this is

This is the program of the arcade game *Street Fighter III: New Generation* turned back into source code: the MAME
and FBNeo set sfiiina (Asia 970204, NO CD, BIOS set 2; sfiiin, BIOS set 1, has the same program). It is a
decompilation: the machine code in the CPS3 program ROM has been rewritten as C and as SH-2 assembler (the SH-2 is
the arcade board's CPU), so people can read it and change it. New Generation is the first game on the engine that
2nd Impact and 3rd Strike continue.

It is also a byte-for-byte match. It builds with the original Hitachi toolchain (SHC 5.0, asmsh, lnk 6.0, rof2bin):
the compiler turns the C into machine code, the assembler does the same for the assembler files, and the linker
joins the pieces into one program. `build/prog.bin` has the arcade program's SHA-1 (a fingerprint of the whole
file), 3dcfb7a2cea2dee0785ce4a3a90d555c107f5372, and the four program SIMM chips written into `build/sfiiina.zip` are the original ROM's:

    sfiii-simm1.0  crc cfc9e45a  sha1 5d9061f76680642e730373e3ac29b24926dc5c0c
    sfiii-simm1.1  crc 57920546  sha1 c8452e7e101b8888fb806d1c9874c6be49fc7dbd
    sfiii-simm1.2  crc 0d8f2680  sha1 ade7b28acd11023696c4b20136f3d2f34da6b1be
    sfiii-simm1.3  crc ea4ca054  sha1 f91c55c4e4fc428ce15d27be38aeed3a483d028c

What is source and what comes from your ROM:

- 5,660 C routines, 55 assembler routines and 18 run-time routines compile and link
  from this source to the arcade's exact bytes, and all the program's tables and work RAM (the game's variables) are
  source too.
- The build copies only the graphics and the parts outside the linked sections from your ROM (see [What the build
  reads from your ROM](#what-the-build-reads-from-your-rom)).
- 19 of the sound driver's routines are built from assembler source; their reconstructed C is in `src/nonmatching/` (see
  [Sound driver](#sound-driver)).

## Building

You need Windows (the tools in `bin/` are Win32 programs), Python 3 and your own ROM set.

1. Put your `sfiiina.zip` (or `sfiiin.zip`) in `rom/`. A split set's shared SIMM files are read from `sfiii.zip`
   when it is there too.
2. Run `build.bat` (or `make`).

The build reads the graphics and the parts outside the linked sections from the ROM, compiles and links the program,
and writes:

- `build/prog.bin` - the program image, 06000000-067FFFFF
- `build/sfiiina.zip` (or `sfiiin.zip`, after your set's BIOS) - your ROM set, in MAME's and FBNeo's layout, with the
  four program SIMM chips replaced by the new build

The build prints each program chip's CRC and SHA-1. It checks them, and `build/prog.bin`, against the arcade's
(`tools/prog.sha1`) and against your set's. If any differs, it still writes the files, then stops with BUILD FAILED
(`make` fails too).

How the program is stored: the program SIMM holds 06000000-067FFFFF in four chips, one byte lane each (each chip
holds one byte of every 4-byte word). New Generation stores its whole program encrypted, code and data alike, apart
from a few parts outside the linked sections that are stored plain (`tools/rom_pieces.tsv`).

To run a new build in MAME, use an empty `-nvram_directory`. MAME keeps the program flash memory in nvram and loads
it over the ROM files, so an old nvram would run the old program instead of your build.

## Layout

    src/      game code (C, and SH-2 assembler in .src files), and the work RAM the modules share
    src/nonmatching/  the sound driver's reconstructed C (not built; see Sound driver)
    data/     game tables, the CD volume identifier, and cg_labels.src: the graphics' names (labels only; the
              bytes come from the ROM)
    include/  headers
    lib/      the compiler's run-time routines (its built-in helpers), as linked into the program
    bin/      Hitachi SHC toolchain: shcmdl, shcgen, shcpep and shcasm are the rebuilt stages (see Compiler; the
              originals are in bin/original)
    sfn.sub   link order and section addresses
    functions.tsv  every routine of the arcade program: arcade address, size, name, file
    tools/    cps3rom1.py: reads the ROM set, writes the new one; rom_pieces.tsv: what it reads from the ROM;
              gaps.tsv: the alignment-gap bytes; prog.sha1

How files are named:

- A data file holds the tables of the 3rd Strike file of that name. Where no 3rd Strike file fits, it is named after
  the module that reads its tables (`<module>_tbl`).
- An assembler module that is part of a C module of the same name (the sound driver's) is named `<module>_x1`,
  `_x2`.

## What the build reads from your ROM

Apart from the alignment-gap bytes (`tools/gaps.tsv`, below), nothing from the ROM is in this repository.
`tools/cps3rom1.py extract` reads these 8 parts of the program
(3.7 MB) from the program SIMM in your ROM set, and `pack` puts them into the linked image:

| part | address | size |
|---|---|---|
| outside the linked sections | 06000200-060003FF | 512 bytes |
| outside the linked sections | 06443022-0646A891 | 158 KB |
| outside the linked sections (stored plain) | 0646A892-064FFFFF | 598 KB |
| data/cg_labels.src | 06500000-0657A1DF | 488 KB |
| outside the linked sections (stored plain) | 0657A1E0-0657FFFF | 24 KB |
| data/cg_labels.src | 06580000-067CD98B | 2.3 MB |
| outside the linked sections (stored plain) | 067CD98C-067FFFDF | 202 KB |
| outside the linked sections (stored plain) | 067FFFEC-067FFFFF | 20 bytes |

- `data/cg_labels.src` is labels only: the graphics' names the program uses, with space reserved for their bytes.
- "outside the linked sections": places in the program area where this program's link writes
  nothing. The CD image New Generation was cut from kept whatever an earlier build had left there (an earlier build's
  tables, bitmaps). No source produces those bytes. For the same reason, the alignment gaps inside the sections (the halfword before a
  4-aligned literal pool, the bytes between objects) hold leftovers instead of the link's fill. `tools/gaps.tsv`
  lists them, and `pack` writes them.

## Compiler

New Generation was built with the arcade compiler of 2nd Impact and 3rd Strike, [SHC 5.0 Release 26, decompiled and
rebuilt in C](https://github.com/gibletto/shc-5r26-decomp-sf3), in a slightly different revision. (The 3rd Strike
README explains why the compiler had to be rebuilt to get a byte match.)

- The rebuilt stages in `bin/` carry the rules found for those games.
- `build.bat` and the `Makefile` set 9 settings at the top (and a few more for the modules compiled
  with other options) for the revision that built New Generation.
- The compiler project's [SF3.md](https://github.com/gibletto/shc-5r26-decomp-sf3/blob/main/SF3.md) lists the rules
  with the routines that show them.

The settings New Generation adds:

- `MDL_IMM_REG=191`: bit 128 (with bit 4): a nonzero constant a register already holds may serve an arithmetic expression of scalar variables, constants and casts, globals included (RANKING)
- `PEP_SWITCH_END=3`: bits 1 and 2: a nested switch keeps its own break label (bit 1), also where nested switches end one after another (bit 2)
- `PEP_RETURN_EXIT=1`: when a return to the adjacent epilogue is removed and a final immediate load is left in a block of its own, the conditional-branch delay-slot pass may still take it if the next block holds only the exit (all its other checks stay)
- `GEN_AND_TEST=1`: only for the modules of the `SPEED_STABLE` group: a bit-and whose value is only tested is computed into a register and that register is tested (`and` + `tst Rn,Rn`)
- `GEN_LAST_KEEP=1`: only for the modules of the `SPEED_STABLE` group: releasing a node's registers keeps the register chosen last, so the next choice still passes over it
- `MDL_SAVED_PRIO=2`: only for the modules of the `SPEED_STABLE` group: a variable of priority 2 may take a callee-saved register (Release 26: 3)
- `MDL_CONST_ENTRY=1`: only for the modules of the `SPEED_STABLE` group: a constant kept in a register is loaded at the function's entry
- `MDL_PARAM_HOME=1`: only for the modules of the `SPEED_STABLE` group: a parameter passed in a register that the function never reads keeps a frame slot, and the entry stores the register there
- `ASM_SIDE_ORDER=3`: only for the modules of the `SPEED_STABLE` group: the scheduler keeps an access through a pointer it steps (`*p++`) and a store through a pointer in place, as a volatile access
- `ASM_READY_WAVES=1`: only for the modules of the `SPEED_STABLE` group: the scheduler takes the instructions that are ready at one time as a wave and frees their successors in order as their predecessors are placed, siblings in source order (sound_voice_3)

None of them tests for a function's name or address, but several have been seen in only one routine so far and rest
on that single example. A source form found later could make some of them unnecessary.

### Options per module

Not every module was compiled with the same options. Most modules compile with `-optimize=1 -speed`. The others are
listed in groups at the top of the `Makefile` (and spelled out in `build.bat`), each group named after its options:

- `-optimize=0 -nospeed`, with `GEN_NARROW_CONST=0` (the `OPT0_PSYS` group): the system modules - the test and
  configuration menus, coin, EEPROM, memory and sprite-list code
- `-noinline` (the `SPEED_NOINLINE` groups): no inline expansion of small routines (they stay separate calls)
- `-section=const=CTBL` (the `_CONSTTBL` groups): the module's constant data goes to the table section `CTBL`
- `SPEED_STABLE_PSYS`: the settings above that apply to the `SPEED_STABLE` group only, two sound modules

### Sections

A section is a block of the program that the linker places at a set address. The program image runs from 06000000:

1. the vector table (`CVECT`)
2. three code sections in a row: the game code (`P`), the fighters' data (`CCHR`: the `data/` files with
   `#pragma section CHR`) and the system code (`PSYS`: the modules whose group name ends in `_PSYS`, compiled with
   `-section=program=PSYS`)
3. the tables (`CTBL`)
4. the image of the initialised work RAM (`D`), which the boot code copies to 02000000

`sfn.sub` gives the link order and addresses.

A few tables lie between pieces of code in `P` and `PSYS` (`data/asstbl.c`, `data/sys_font.c` and others: the
`INCODE` groups). The linker would put C constant data after all the code. So these files are compiled to assembler
(`-code=asmcode`), `tools/incode.py` marks their constant section as code, and asmsh assembles them. The source
stays C.

### Sound driver

Some of the sound driver's routines are built from assembler instead of from their C. Unlike the 3rd Strike and
2nd Impact decomps, New Generation's sound driver was built with an SHC release much older than any that has been
found. Even the oldest available, 5.0 Release 10, already compiles it as Release 26 does, and matching it with the
rebuilt compiler would need massive modification.

So the driver's 19 routines are built from assembler source written from the arcade code (`src/textsound_2_x1.src`,
`src/textsound_2_x2.src`, `src/sound_voice_x1.src`, `src/sound_voice_2.src`). Their reconstructed C is in
`src/nonmatching/` (`textsound_2.c`, `sound_voice.c`, `sound_voice_2.c`, under `NONMATCHING`). It compiles to most
of the same instructions, but not to the exact bytes. The driver's other routines (`textsound_2.c`,
`sound_status.c`, `sound_voice.c`, `sound_voice_3.c`) and its tables and work RAM are C that builds the arcade's
bytes.

The driver was built as position-independent code (code that can run from any address). It calls through `BSRF`,
with the callee's offset from the call in the literal pool (the constants stored next to the code). The assembler
source writes that offset as a label difference (`.DATA.L __slow_mvn-sound_init_026`).

The assembler prints one expected warning (817, ILLEGAL BOUNDARY VALUE) for `src/sound_voice_x1.src`. That module
starts on a 2-byte boundary, right after the C of `sound_voice.c`, as it does in the arcade program.

## Contributing

As this is an exact byte-match, every contribution must keep the match. Contributions should either:

- improve or explain the code, or
- replace a compiler setting with source that produces the same bytes (with a PR to the compiler decomp project
  too).

The open tasks:

- C for the sound driver that builds its bytes (`src/nonmatching/` is the starting point)
- matching forms that look like workarounds rather than original source: source that builds the right bytes but is
  unlikely to be what Capcom wrote (dead reads, `if (0)` blocks, odd spellings)

## Thanks

Thanks to the 3sx Team and Artem for the 3s-decomp, which helped recover a large amount of the 3rd Strike code style
this tree builds on, and to DrewDos for his matching work and help.

Thanks also to Dominic Evans (X: [@oldmanuk](https://x.com/oldmanuk)) for clean-up suggestions.

## License

GNU Affero General Public License v3.0 (`LICENSE`): parts of the source come from the 3rd Strike and 2nd Impact
decomps and through them from the 3s-decomp, which is AGPL-3.0. `NOTICE.md` lists what the license does not cover.
