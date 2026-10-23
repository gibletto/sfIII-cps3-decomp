# Street Fighter III New Generation - CPS3 program source

**AI Disclosure**:
Yes, this used Claude, as the 3rd Strike and 2nd Impact decomps did. New Generation has no debug symbols of its own:
the finished [3rd Strike](https://github.com/gibletto/sfIII3-cps3-decomp) and
[2nd Impact](https://github.com/gibletto/sfIII2-cps3-decomp) decomps were the reference for its layout and names, and
the names of the files here follow Capcom's 3rd Strike file names (New Generation's own modules are named in the same
style).

C and SH-2 assembler source for the CPS3 program ROM of *Street Fighter III: New Generation* (MAME set sfiiin, Asia
970204, NO CD), built with the original Hitachi toolchain (SHC 5.0, asmsh, lnk 6.0, rof2bin). New Generation is the
first game on the engine that 2nd Impact and 3rd Strike continue.

The build is a byte-for-byte copy of the arcade program. `build/prog.bin` has the arcade program's SHA-1,
3dcfb7a2cea2dee0785ce4a3a90d555c107f5372, and the program file `10` written into `build/sfiiin.zip` is the original ROM's:

    10  sha1 47623820c64b72e69417afcafaacdd2c318cde1c

5,719 C routines, 37 assembler routines and 18 run-time routines compile and link from
this source to the arcade's exact bytes. The rest of the program is not source yet: 19 routines and some data tables, which the build copies from your ROM (see [What the build reads from your
ROM](#what-the-build-reads-from-your-rom)).

## Building

Needs Windows (the tools in `bin/` are Win32 programs) and Python 3.

1. Put your `sfiiin.zip` in `rom/`.
2. Run `build.bat` (or `make`).

The build reads from the ROM the parts of the program that are not source yet, compiles and links the program, and
writes:

- `build/prog.bin` - the program image, 06000000-067FFFFF
- `build/10` - the program file as the ROM set stores it (encrypted)
- `build/sfiiin.zip` - your ROM set with `10` replaced

The build checks `build/prog.bin` and `build/10` against the SHA-1s in `tools/prog.sha1`, the arcade program's, and
`10` against the one in your ROM set; if any differs it still writes the files, then stops with BUILD FAILED (`make`
fails too). New Generation stores its whole program encrypted, code and data alike, apart from a few parts outside the
linked sections that are stored plain (`tools/rom_pieces.tsv`).

When running a new build in MAME, use an empty `-nvram_directory`: MAME keeps the program flash in nvram and loads it
over the ROM files.

## Layout

    src/      game code (C, and SH-2 assembler in .src files), and the work RAM the modules share
    data/     game tables, the CD volume identifier, and the labels-only objects: the parts of the program that are
              not source yet (names and sizes only; the bytes come from the ROM)
    include/  headers
    lib/      the compiler's run-time routines, as linked into the program
    bin/      Hitachi SHC toolchain: shcmdl, shcgen, shcpep and shcasm are the rebuilt stages (see Compiler; the
              originals are in bin/original)
    sfn.sub   link order and section addresses
    functions.tsv  every routine of the arcade program: arcade address, size, name, file
    tools/    cps3rom1.py: reads the ROM set, writes the new one; rom_pieces.tsv: what it reads from the ROM;
              gaps.tsv: the alignment-gap bytes; prog.sha1

A data file holds the tables of the 3rd Strike file of that name, or is named after the module that reads its tables
(`<module>_tbl`) where no 3rd Strike file fits. A labels-only object is named after its section and address
(`CTBL_063D2C74`) or after the module it belongs to; the graphics' names are in `cg_labels.src`.

## What the build reads from your ROM

Apart from the alignment-gap bytes (`tools/gaps.tsv`, below), nothing from the ROM is in this repository.
`tools/cps3rom1.py extract` reads these 15 parts of the program
(3.8 MB) from `10` in your `sfiiin.zip`, and `pack` puts them into the linked image:

| part | address | size |
|---|---|---|
| outside the linked sections | 06000200-060003FF | 512 bytes |
| data/textsound_2_rom.src | 063CD16C-063CDA4B | 2,272 bytes |
| data/textsound_2_rom_b.src | 063CDA58-063CDC9F | 584 bytes |
| data/sound_voice_rom.src | 063CE212-063CE883 | 1,650 bytes |
| data/sound_voice_2_rom.src | 063CE884-063CF59F | 3,356 bytes |
| data/P_063CF610.src | 063CF610-063CFA0F | 1,024 bytes |
| data/P_063CFA78.src | 063CFA78-063D1277 | 6,144 bytes |
| data/D_02007398.src (initial values of work RAM 02007398) | 06442FF8-06443021 | 42 bytes |
| outside the linked sections | 06443022-0646A891 | 158 KB |
| outside the linked sections (stored plain) | 0646A892-064FFFFF | 598 KB |
| data/cg_labels.src | 06500000-0657A1DF | 488 KB |
| outside the linked sections (stored plain) | 0657A1E0-0657FFFF | 24 KB |
| data/cg_labels.src | 06580000-067CD98B | 2.3 MB |
| outside the linked sections (stored plain) | 067CD98C-067FFFDF | 202 KB |
| outside the linked sections (stored plain) | 067FFFEC-067FFFFF | 20 bytes |

- The `data/` objects are labels only: the names the rest of the program uses, with space reserved for the bytes.
  As they become C or assembler source they leave this list.
- The routines `sound_init`, `sound_request`, `sound_seq_start`, `sound_request_pan`, `bgm_stop`, `bgm_pause`, `bgm_resume`, `sound_fade_in_submit`, `bgm_fade_out`, `sound_reg_level_set`, `sound_driver_init`, `se_voice_stop`, `se_voice_stop_all`, `sound_driver_tick`, `voice_process_primary`, `sound_note_to_pitch`, `sound_voice_volume_compute`, `voice_process_secondary`, `sound_reg_write_verify` are not source yet; their bytes are in the labels-only objects that hold them.
- "outside the linked sections": the CD image New Generation was cut from kept whatever an earlier build had left
  where this program's link writes nothing (an earlier build's tables, bitmaps). No source produces those bytes.
  For the same reason the alignment gaps inside the sections (the halfword before a 4-aligned literal pool, the
  bytes between objects) hold leftovers instead of the link's fill; `tools/gaps.tsv` lists them and `pack` writes
  them.

## Compiler

New Generation was built with the arcade compiler of 2nd Impact and 3rd Strike, [SHC 5.0 Release 26, decompiled and
rebuilt in C](https://github.com/gibletto/shc-5r26-decomp-sf3), in a slightly different revision. The rebuilt stages
in `bin/` carry the rules found for those games, and `build.bat` and the `Makefile` set 17 settings at
the top (and a few more for the modules compiled with other options) for the revision that built New Generation. The
compiler project's [SF3.md](https://github.com/gibletto/shc-5r26-decomp-sf3/blob/main/SF3.md) lists the rules with the
routines that show them. Those New Generation adds:

- `MDL_IMM_REG=255`: bit 128 (with bit 4): a nonzero constant a register already holds may serve an arithmetic expression of scalar variables, constants and casts, globals included (RANKING)
- `PEP_SWITCH_END=3`: bits 1 and 2: a nested switch keeps its own break label (bit 1), also where nested switches end one after another (bit 2)
- `PEP_RETURN_EXIT=1`: when a return to the adjacent epilogue is removed and a final immediate load is left in a block of its own, the conditional-branch delay-slot pass may still take it if the next block holds only the exit (all its other checks stay)
- `PEP_AUTOINC=0`: only for the modules of the `SPEED_STABLE` group: no folding of a load and a later pointer `add` into a post-increment load (as Release 26)
- `ASM_READY_WAVES=1`: only for the modules of the `SPEED_STABLE` group: the scheduler takes the instructions that are ready at one time as a wave and frees their successors in order as their predecessors are placed, siblings in source order (sound_voice_3)

None of them tests for a function's name or address, but several have been seen in only one routine so far and rest
on that single example. A source form found later could make some of them unnecessary.

### Options per module

Most modules compile with `-optimize=1 -speed`. The others are listed in groups at the top of the `Makefile` (and
spelled out in `build.bat`), each group named after its options:

- `-optimize=0 -nospeed`, with `GEN_NARROW_CONST=0` (the `OPT0_PSYS` group): the system modules - the test and
  configuration menus, coin, EEPROM, memory and sprite-list code
- `-noinline` (the `SPEED_NOINLINE` groups): no inline expansion of small routines
- `-section=const=CTBL` (the `_CONSTTBL` groups): the module's constant data goes to the table section `CTBL`
- `SPEED_STABLE_PSYS`: the two settings above that apply to one sound module only

### Sections

The program image runs from 06000000: the vector table (`CVECT`), then three code sections in a row, the game code
(`P`), the fighters' data (`CCHR`: the `data/` files with `#pragma section CHR`) and the system code (`PSYS`: the
modules whose group name ends in `_PSYS`, compiled with `-section=program=PSYS`), then the tables (`CTBL`) and the
image of the initialised work RAM (`D`), which the boot code copies to 02000000. `sfn.sub` gives the link order and
addresses.

A few tables lie between pieces of code in `P` and `PSYS` (`data/asstbl.c`, `data/sys_font.c` and others: the
`INCODE` groups). The linker would put C constant data after all the code, so these files are compiled to assembler
(`-code=asmcode`), `tools/incode.py` marks their constant section as code, and asmsh assembles them; the source stays
C.

### Sound driver

<!-- PLACEHOLDER: the sound driver's compiler profile goes here when its C lands: its options (the driver is built
with -pic=1, position-independent code), its settings, and the routines that show them. Until then its routines are
read from the ROM (see below). -->
The sound driver's routines are not source yet. They were built with position-independent code (`-pic=1`) and a
compiler profile that is still being worked out; this section will describe it when they land.

## Contributing
As this is an exact byte-match, contributions should maintain the match while improving or explaining the code, or
replace a compiler setting with source that produces the same bytes (with a PR to the compiler decomp project too).
Turning the labels-only objects into source is the open task. Matching forms that look
like workarounds rather than original source (dead reads, `if (0)` blocks, odd spellings) are the next candidates.

## Thanks

Thanks to the 3sx Team and Artem for the 3s-decomp, which helped recover a large amount of the 3rd Strike code style
this tree builds on, and to DrewDos for his matching work and help.

## License

GNU Affero General Public License v3.0 (`LICENSE`): parts of the source come from the 3rd Strike and 2nd Impact
decomps and through them from the 3s-decomp, which is AGPL-3.0. `NOTICE.md` lists what the license does not cover.
