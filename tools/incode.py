#!/usr/bin/env python3
"""Make the constant section of an SHC assembler listing a code section, for the tables that sit between the code
objects of P or PSYS (build.bat and the Makefile: the units compiled with -code=asmcode -section=const=P or PSYS).

    python tools/incode.py obj/<unit>.src P|PSYS

SHC gives a constant section the DATA attribute, and lnk links a section of DATA attribute after all the code of
that name; as CODE, the object keeps its place among the code.
"""
import re, sys

path, sec = sys.argv[1], sys.argv[2]
text = open(path).read()
open(path, 'w').write(re.sub(r'(\.SECTION\s+' + sec + r'),DATA\b', r'\1,CODE', text))
