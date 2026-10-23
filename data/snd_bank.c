/*
 * SND_BANK.C  Instrument banks
 *
 * snd_bank_rom_tbl points at 16 banks. A bank starts with one offset per program, from the bank's
 * start, to that program's key splits (0: no program); a program is a list of SNDPATCH, one per key
 * range up to note_ceiling, ending with note_ceiling -1. Each SNDPATCH names the sample it plays
 * (snd_sample_rom_tbl) with its pan, volume, pitch and envelope curves.
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

extern const u16 snd_bank_00[], snd_bank_01[], snd_bank_02[], snd_bank_03[], snd_bank_04[], snd_bank_05[],
                 snd_bank_06[], snd_bank_07[], snd_bank_08[], snd_bank_09[], snd_bank_10[], snd_bank_11[],
                 snd_bank_12[], snd_bank_13[], snd_bank_14[], snd_bank_15[];

const u16* const snd_bank_rom_tbl[16] = {
    snd_bank_00,
    snd_bank_01,
    snd_bank_02,
    snd_bank_03,
    snd_bank_04,
    snd_bank_05,
    snd_bank_06,
    snd_bank_07,
    snd_bank_08,
    snd_bank_09,
    snd_bank_10,
    snd_bank_11,
    snd_bank_12,
    snd_bank_13,
    snd_bank_14,
    snd_bank_15,
};

const u16 snd_bank_00[128] = {  /* program -> offset of its key splits */
    256, 414, 488, 502, 516, 530, 544, 558, 572, 586, 600, 614,
    628, 642, 656, 694, 744, 770, 796, 822, 836, 862, 888, 914,
    940, 966, 980, 1006, 1020, 1034, 1048, 1062, 1076, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
const SNDPATCH snd_bank_00_prog_000[13] = {  /* program 0 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   36,   64,   38,    0,   27,    0,   63,   42,  126,   38,   51 },
    {   37,  255,    0,    0,   46,    0,   63,   16,  126,   42,   51 },
    {   38,  255,   36,    0,    9,    0,   63,   17,  126,   43,   51 },
    {   39,  255,    0,    0,    4,    0,   63,   62,  126,   26,   51 },
    {   40,  255,   16,    0,    8,    0,   63,   62,  126,   28,   51 },
    {   42,  255,   -5,    0,    5,    0,   63,   62,  126,   38,   51 },
    {   46,  255,    0,    0,    6,    0,   63,   62,  126,   38,   51 },
    {   48,   64,   -1,    0,   13,    0,   63,   42,  126,   40,   51 },
    {   51,  255,    4,    0,    7,    0,   63,   48,  126,   33,   51 },
    {   54,  255,    0,    0,   10,    0,   62,   62,  126,   40,   51 },
    {   69,  255,    0,    0,    1,    0,   63,   56,  126,   39,   51 },
    {   72,   64,    0,    0,   36,    0,   63,   42,  126,   40,   51 },
    {   76,  255,    0,    0,    0,    0,   63,   17,  126,   46,   51 },
};
const u16 snd_bank_00_prog_000_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_001[6] = {  /* program 1 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   62,   24,    0,    0,   24,    0,   63,   62,  126,   38,   51 },
    {   63,   19,    0,    0,   22,    0,   63,   62,  126,   39,   51 },
    {   64,  109,    0,    0,   23,    0,   63,   62,  126,   38,   51 },
    {   67,  255,    0,    0,   62,    0,   63,   63,  127,   31,   51 },
    {   88,  124,    0,    0,   25,    0,   63,   62,  126,   38,   51 },
    {   89,  127,    0,    0,   26,    0,   63,   62,  126,   38,   51 },
};
const u16 snd_bank_00_prog_001_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_002[1] = {  /* program 2 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,    2,    0,   63,   48,  126,   36,   51 },
};
const u16 snd_bank_00_prog_002_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_003[1] = {  /* program 3 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   12,    0,   63,   15,  126,   40,   48 },
};
const u16 snd_bank_00_prog_003_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_004[1] = {  /* program 4 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   31,    0,   63,   62,  126,   31,   51 },
};
const u16 snd_bank_00_prog_004_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_005[1] = {  /* program 5 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   15,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_005_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_006[1] = {  /* program 6 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   20,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_006_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_007[1] = {  /* program 7 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   47,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_007_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_008[1] = {  /* program 8 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   30,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_008_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_009[1] = {  /* program 9 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   34,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_009_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_010[1] = {  /* program 10 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   14,    0,   63,   17,  126,   27,   51 },
};
const u16 snd_bank_00_prog_010_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_011[1] = {  /* program 11 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   55,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_011_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_012[1] = {  /* program 12 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   21,    0,   63,   16,  126,   20,   51 },
};
const u16 snd_bank_00_prog_012_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_013[1] = {  /* program 13 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   37,    0,   63,   63,  126,   35,   51 },
};
const u16 snd_bank_00_prog_013_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_014[3] = {  /* program 14 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   56,  255,    0,    0,   59,    0,   63,   62,  126,   36,   51 },
    {   68,  255,    0,    0,   60,    0,   63,   63,  126,   44,   51 },
    {  127,  255,    0,    0,   61,    0,   63,   63,  126,   45,   51 },
};
const u16 snd_bank_00_prog_014_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_015[4] = {  /* program 15 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   56,  255,    0,    0,   42,    0,   63,   17,  126,   22,   51 },
    {   68,  255,    0,    0,   43,    0,   63,   17,  126,   22,   51 },
    {   80,  255,    0,    0,   44,    0,   63,   20,  126,   22,   51 },
    {  127,  255,    0,    0,   45,    0,   63,   19,  126,   22,   51 },
};
const u16 snd_bank_00_prog_015_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_016[2] = {  /* program 16 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   71,  255,    0,    0,   28,    0,   63,   63,  126,   19,   51 },
    {  127,  255,    0,    0,   29,    0,   63,   63,  126,   19,   51 },
};
const u16 snd_bank_00_prog_016_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_017[2] = {  /* program 17 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   80,  255,    0,    0,   38,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   39,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_017_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_018[2] = {  /* program 18 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   80,  255,    0,    0,   57,    0,   63,   16,  126,   21,   51 },
    {  127,  255,    0,    0,   58,    0,   63,   16,  126,   21,   51 },
};
const u16 snd_bank_00_prog_018_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_019[1] = {  /* program 19 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,    3,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_019_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_020[2] = {  /* program 20 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   75,  255,    0,    0,   51,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   52,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_020_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_021[2] = {  /* program 21 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   71,  255,    0,    0,   40,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   41,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_021_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_022[2] = {  /* program 22 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   80,  255,    0,    0,   18,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   19,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_022_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_023[2] = {  /* program 23 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   80,  255,    0,    0,   53,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   54,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_023_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_024[2] = {  /* program 24 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   80,  255,    0,    0,   48,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   49,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_024_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_025[1] = {  /* program 25 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   56,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_025_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_026[2] = {  /* program 26 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   71,  255,    0,    0,   32,    0,   63,    1,    1,    1,   51 },
    {  127,  255,    0,    0,   33,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_026_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_027[1] = {  /* program 27 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   50,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_027_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_028[1] = {  /* program 28 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   35,    0,   63,   16,  126,   24,   51 },
};
const u16 snd_bank_00_prog_028_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_029[1] = {  /* program 29 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   67,  255,  -30,    0,   16,    0,   63,   19,  126,   40,   51 },
};
const u16 snd_bank_00_prog_029_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_030[1] = {  /* program 30 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {   67,  255,    0,    0,   17,    0,   63,   51,  126,   44,   51 },
};
const u16 snd_bank_00_prog_030_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_031[1] = {  /* program 31 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   39,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_031_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_00_prog_032[1] = {  /* program 32 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   38,    0,   63,    1,    1,    1,   51 },
};
const u16 snd_bank_00_prog_032_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */

const u16 snd_bank_01[128] = {  /* program -> offset of its key splits */
    256, 270, 284, 298, 312, 326, 340, 354, 368, 382, 396, 410,
    424, 438, 452, 466, 480, 494, 508, 522, 536, 550, 564, 578,
    592, 606, 620, 634, 648, 662, 676, 690, 704, 718, 732, 746,
    760, 774, 788, 802, 816, 830, 844, 858, 872, 0, 886, 900,
    914, 928, 942, 956, 970, 984, 998, 1012, 1026, 1040, 1054, 1068,
    1082, 1096, 1110, 1124, 1138, 1152, 1166, 1180, 1194, 1208, 1222, 1236,
    1250, 1264, 1278, 1292, 1306, 1320, 1334, 1348, 1362, 1376, 1390, 1404,
    1418, 1432, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
const SNDPATCH snd_bank_01_prog_000[1] = {  /* program 0 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   65,    0,   63,   63,  126,   42,   51 },
};
const u16 snd_bank_01_prog_000_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_001[1] = {  /* program 1 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   64,    0,   63,   63,  126,   42,   51 },
};
const u16 snd_bank_01_prog_001_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_002[1] = {  /* program 2 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   63,    0,   63,   63,  126,   42,   51 },
};
const u16 snd_bank_01_prog_002_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_003[1] = {  /* program 3 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   71,    0,   63,   63,  126,   21,   51 },
};
const u16 snd_bank_01_prog_003_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_004[1] = {  /* program 4 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,   70,    0,   63,   63,  126,   21,   51 },
};
const u16 snd_bank_01_prog_004_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_005[1] = {  /* program 5 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,   69,    0,   63,   63,  126,   21,   51 },
};
const u16 snd_bank_01_prog_005_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_006[1] = {  /* program 6 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,   68,    0,   63,   62,  126,   35,   51 },
};
const u16 snd_bank_01_prog_006_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_007[1] = {  /* program 7 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,   67,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_007_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_008[1] = {  /* program 8 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,   66,    0,   63,   63,  126,   21,   51 },
};
const u16 snd_bank_01_prog_008_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_009[1] = {  /* program 9 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   -5,    0,   72,    0,   63,   63,  126,   42,   51 },
};
const u16 snd_bank_01_prog_009_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_010[1] = {  /* program 10 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   73,    0,   63,   63,  126,   32,   51 },
};
const u16 snd_bank_01_prog_010_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_011[1] = {  /* program 11 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   74,    0,   63,   63,  126,   41,   51 },
};
const u16 snd_bank_01_prog_011_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_012[1] = {  /* program 12 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   75,    0,   63,   63,  126,   38,   51 },
};
const u16 snd_bank_01_prog_012_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_013[1] = {  /* program 13 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -15,    0,   76,    0,   63,   63,  126,   36,   51 },
};
const u16 snd_bank_01_prog_013_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_014[1] = {  /* program 14 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   77,    0,   63,   63,  126,   42,   51 },
};
const u16 snd_bank_01_prog_014_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_015[1] = {  /* program 15 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,   78,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_015_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_016[1] = {  /* program 16 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,   79,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_016_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_017[1] = {  /* program 17 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   -5,    0,   80,    0,   63,   62,  126,   42,   51 },
};
const u16 snd_bank_01_prog_017_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_018[1] = {  /* program 18 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   81,    0,   63,   62,  126,   42,   51 },
};
const u16 snd_bank_01_prog_018_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_019[1] = {  /* program 19 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,   82,    0,   63,   62,  126,   36,   51 },
};
const u16 snd_bank_01_prog_019_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_020[1] = {  /* program 20 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,   83,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_01_prog_020_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_021[1] = {  /* program 21 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   84,    0,   63,   62,  126,   33,   51 },
};
const u16 snd_bank_01_prog_021_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_022[1] = {  /* program 22 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,   85,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_01_prog_022_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_023[1] = {  /* program 23 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,   86,    0,   63,   63,  126,    1,   51 },
};
const u16 snd_bank_01_prog_023_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_024[1] = {  /* program 24 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,   87,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_01_prog_024_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_025[1] = {  /* program 25 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,   88,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_025_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_026[1] = {  /* program 26 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,   89,    0,   63,   62,  126,   37,   51 },
};
const u16 snd_bank_01_prog_026_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_027[1] = {  /* program 27 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -15,    0,   90,    0,   63,   62,  126,   37,   51 },
};
const u16 snd_bank_01_prog_027_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_028[1] = {  /* program 28 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,   91,    0,   63,   62,  126,   37,   51 },
};
const u16 snd_bank_01_prog_028_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_029[1] = {  /* program 29 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,   92,    0,   63,   62,  126,   21,   51 },
};
const u16 snd_bank_01_prog_029_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_030[1] = {  /* program 30 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,   94,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_030_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_031[1] = {  /* program 31 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,   95,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_031_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_032[1] = {  /* program 32 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   96,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_032_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_033[1] = {  /* program 33 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,   93,    0,   63,   63,  126,   36,   51 },
};
const u16 snd_bank_01_prog_033_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_034[1] = {  /* program 34 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,   97,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_034_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_035[1] = {  /* program 35 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,   98,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_035_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_036[1] = {  /* program 36 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,   99,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_036_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_037[1] = {  /* program 37 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,  100,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_037_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_038[1] = {  /* program 38 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  101,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_038_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_039[1] = {  /* program 39 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  102,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_039_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_040[1] = {  /* program 40 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  103,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_040_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_041[1] = {  /* program 41 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  104,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_041_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_042[1] = {  /* program 42 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  105,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_042_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_043[1] = {  /* program 43 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  265,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_01_prog_043_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_044[1] = {  /* program 44 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  266,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_044_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_046[1] = {  /* program 46 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  109,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_046_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_047[1] = {  /* program 47 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  110,    0,   63,   62,  126,   36,   51 },
};
const u16 snd_bank_01_prog_047_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_048[1] = {  /* program 48 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  111,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_048_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_049[1] = {  /* program 49 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  112,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_049_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_050[1] = {  /* program 50 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  113,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_050_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_051[1] = {  /* program 51 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  296,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_051_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_052[1] = {  /* program 52 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -20,    0,  297,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_052_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_053[1] = {  /* program 53 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  298,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_053_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_054[1] = {  /* program 54 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  299,    0,   63,    1,  126,   16,   51 },
};
const u16 snd_bank_01_prog_054_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_055[1] = {  /* program 55 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   37,    0,  300,    0,   63,   62,  126,   30,   26 },
};
const u16 snd_bank_01_prog_055_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_056[1] = {  /* program 56 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  301,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_056_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_057[1] = {  /* program 57 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  302,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_057_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_058[1] = {  /* program 58 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  303,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_058_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_059[1] = {  /* program 59 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  304,    0,   63,    1,  126,   16,   51 },
};
const u16 snd_bank_01_prog_059_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_060[1] = {  /* program 60 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  305,    0,   63,   62,  126,   30,   26 },
};
const u16 snd_bank_01_prog_060_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_061[1] = {  /* program 61 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  306,    0,   63,   62,  126,   30,   26 },
};
const u16 snd_bank_01_prog_061_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_062[1] = {  /* program 62 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  322,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_062_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_063[1] = {  /* program 63 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  323,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_063_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_064[1] = {  /* program 64 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  324,    0,   63,    1,  126,   16,   51 },
};
const u16 snd_bank_01_prog_064_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_065[1] = {  /* program 65 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  325,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_065_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_066[1] = {  /* program 66 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  326,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_066_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_067[1] = {  /* program 67 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  329,    0,   63,    1,  126,   21,   51 },
};
const u16 snd_bank_01_prog_067_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_068[1] = {  /* program 68 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  330,    0,   63,    1,  126,   32,   51 },
};
const u16 snd_bank_01_prog_068_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_069[1] = {  /* program 69 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    5,    0,  331,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_069_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_070[1] = {  /* program 70 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  332,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_070_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_071[1] = {  /* program 71 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  333,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_01_prog_071_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_072[1] = {  /* program 72 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  335,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_072_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_073[1] = {  /* program 73 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  337,    0,   63,   62,  126,   28,   51 },
};
const u16 snd_bank_01_prog_073_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_074[1] = {  /* program 74 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  338,    0,   63,   62,  126,   26,   51 },
};
const u16 snd_bank_01_prog_074_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_075[1] = {  /* program 75 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  339,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_075_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_076[1] = {  /* program 76 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  340,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_01_prog_076_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_077[1] = {  /* program 77 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   12,    0,  341,    0,   63,   62,  126,   16,    1 },
};
const u16 snd_bank_01_prog_077_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_078[1] = {  /* program 78 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  342,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_078_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_079[1] = {  /* program 79 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  343,    0,   63,   62,  127,   30,   51 },
};
const u16 snd_bank_01_prog_079_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_080[1] = {  /* program 80 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  364,    0,   63,   62,  127,   30,   51 },
};
const u16 snd_bank_01_prog_080_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_081[1] = {  /* program 81 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  365,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_081_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_082[1] = {  /* program 82 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  366,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_082_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_083[1] = {  /* program 83 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  367,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_083_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_084[1] = {  /* program 84 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  368,    0,   63,   62,  127,   30,   51 },
};
const u16 snd_bank_01_prog_084_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_01_prog_085[1] = {  /* program 85 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  372,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_01_prog_085_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */

const u16 snd_bank_02[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_03[128] = {  /* program -> offset of its key splits */
    256, 270, 284, 298, 312, 326, 340, 354, 368, 382, 396, 410,
    424, 438, 452, 466, 480, 494, 508, 522, 536, 550, 564, 578,
    592, 606, 620, 634, 648, 662, 676, 690, 704, 718, 732, 746,
    760, 774, 788, 802, 816, 830, 844, 858, 872, 886, 900, 914,
    928, 942, 956, 970, 984, 998, 1012, 1026, 1040, 1054, 1068, 1082,
    1096, 1110, 1124, 1138, 1152, 1166, 1180, 1194, 1208, 1222, 1236, 1250,
    1264, 1278, 1292, 1306, 1320, 1334, 1348, 1362, 1376, 1390, 1404, 1418,
    1432, 1446, 1460, 1474, 1488, 1502, 1516, 1530, 1544, 1558, 1572, 1586,
    1600, 1614, 1628, 1642, 1656, 1670, 1684, 1698, 1712, 1726, 1740, 1754,
    1768, 1782, 1796, 1810, 1824, 1838, 1852, 1866, 1880, 1894, 1908, 1922,
    1936, 1950, 1964, 1978, 1992, 2006, 2020, 2034,
};
const SNDPATCH snd_bank_03_prog_000[1] = {  /* program 0 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  106,    0,   63,   62,  126,   40,   53 },
};
const u16 snd_bank_03_prog_000_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_001[1] = {  /* program 1 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  107,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_03_prog_001_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_002[1] = {  /* program 2 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  108,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_002_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_003[1] = {  /* program 3 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  114,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_003_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_004[1] = {  /* program 4 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  115,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_004_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_005[1] = {  /* program 5 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  116,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_005_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_006[1] = {  /* program 6 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  117,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_006_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_007[1] = {  /* program 7 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  118,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_007_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_008[1] = {  /* program 8 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  119,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_008_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_009[1] = {  /* program 9 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  120,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_009_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_010[1] = {  /* program 10 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  121,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_010_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_011[1] = {  /* program 11 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  122,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_011_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_012[1] = {  /* program 12 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  123,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_012_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_013[1] = {  /* program 13 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  124,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_013_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_014[1] = {  /* program 14 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  125,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_03_prog_014_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_015[1] = {  /* program 15 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  126,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_015_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_016[1] = {  /* program 16 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  127,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_03_prog_016_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_017[1] = {  /* program 17 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  128,    0,   63,   62,  126,   25,   51 },
};
const u16 snd_bank_03_prog_017_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_018[1] = {  /* program 18 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  129,    0,   63,   62,  126,   25,   51 },
};
const u16 snd_bank_03_prog_018_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_019[1] = {  /* program 19 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  130,    0,   63,   62,  126,   25,   51 },
};
const u16 snd_bank_03_prog_019_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_020[1] = {  /* program 20 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  131,    0,   63,   62,  126,   21,   51 },
};
const u16 snd_bank_03_prog_020_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_021[1] = {  /* program 21 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  132,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_021_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_022[1] = {  /* program 22 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  133,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_022_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_023[1] = {  /* program 23 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  134,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_023_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_024[1] = {  /* program 24 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  135,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_024_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_025[1] = {  /* program 25 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  136,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_025_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_026[1] = {  /* program 26 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  137,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_026_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_027[1] = {  /* program 27 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  138,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_027_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_028[1] = {  /* program 28 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  139,    0,   63,   63,  127,    1,   63 },
};
const u16 snd_bank_03_prog_028_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_029[1] = {  /* program 29 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  140,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_029_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_030[1] = {  /* program 30 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  141,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_030_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_031[1] = {  /* program 31 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  142,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_031_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_032[1] = {  /* program 32 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  143,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_032_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_033[1] = {  /* program 33 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  144,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_033_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_034[1] = {  /* program 34 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  145,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_034_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_035[1] = {  /* program 35 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  146,    0,   63,   63,  126,    1,   63 },
};
const u16 snd_bank_03_prog_035_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_036[1] = {  /* program 36 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  147,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_036_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_037[1] = {  /* program 37 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  148,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_037_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_038[1] = {  /* program 38 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  149,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_038_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_039[1] = {  /* program 39 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  150,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_039_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_040[1] = {  /* program 40 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  151,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_040_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_041[1] = {  /* program 41 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  152,    0,   63,   63,  126,    1,   51 },
};
const u16 snd_bank_03_prog_041_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_042[1] = {  /* program 42 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  153,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_042_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_043[1] = {  /* program 43 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  154,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_043_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_044[1] = {  /* program 44 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  155,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_044_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_045[1] = {  /* program 45 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  156,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_045_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_046[1] = {  /* program 46 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  157,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_046_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_047[1] = {  /* program 47 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  158,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_047_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_048[1] = {  /* program 48 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  159,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_048_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_049[1] = {  /* program 49 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  160,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_049_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_050[1] = {  /* program 50 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  161,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_050_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_051[1] = {  /* program 51 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  162,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_051_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_052[1] = {  /* program 52 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  163,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_052_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_053[1] = {  /* program 53 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  164,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_053_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_054[1] = {  /* program 54 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  165,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_054_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_055[1] = {  /* program 55 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  166,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_055_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_056[1] = {  /* program 56 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  167,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_056_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_057[1] = {  /* program 57 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  168,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_057_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_058[1] = {  /* program 58 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  169,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_058_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_059[1] = {  /* program 59 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  170,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_059_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_060[1] = {  /* program 60 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  171,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_060_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_061[1] = {  /* program 61 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  172,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_061_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_062[1] = {  /* program 62 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  173,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_062_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_063[1] = {  /* program 63 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  174,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_063_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_064[1] = {  /* program 64 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  175,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_064_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_065[1] = {  /* program 65 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  176,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_065_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_066[1] = {  /* program 66 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  177,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_066_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_067[1] = {  /* program 67 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  178,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_067_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_068[1] = {  /* program 68 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  179,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_068_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_069[1] = {  /* program 69 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  180,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_069_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_070[1] = {  /* program 70 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  181,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_070_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_071[1] = {  /* program 71 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  182,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_071_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_072[1] = {  /* program 72 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  183,    0,   61,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_072_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_073[1] = {  /* program 73 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  184,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_073_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_074[1] = {  /* program 74 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  185,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_074_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_075[1] = {  /* program 75 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  186,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_075_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_076[1] = {  /* program 76 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  187,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_076_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_077[1] = {  /* program 77 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  188,    0,   63,    1,  126,    1,   63 },
};
const u16 snd_bank_03_prog_077_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_078[1] = {  /* program 78 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  189,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_078_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_079[1] = {  /* program 79 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   37,    0,  190,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_079_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_080[1] = {  /* program 80 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  191,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_080_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_081[1] = {  /* program 81 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  192,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_081_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_082[1] = {  /* program 82 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  193,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_082_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_083[1] = {  /* program 83 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  194,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_083_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_084[1] = {  /* program 84 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  195,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_084_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_085[1] = {  /* program 85 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  196,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_085_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_086[1] = {  /* program 86 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  197,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_086_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_087[1] = {  /* program 87 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  198,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_087_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_088[1] = {  /* program 88 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  199,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_088_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_089[1] = {  /* program 89 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  200,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_089_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_090[1] = {  /* program 90 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  201,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_090_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_091[1] = {  /* program 91 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  202,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_091_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_092[1] = {  /* program 92 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  203,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_092_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_093[1] = {  /* program 93 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  204,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_093_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_094[1] = {  /* program 94 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  205,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_094_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_095[1] = {  /* program 95 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  206,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_095_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_096[1] = {  /* program 96 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  207,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_096_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_097[1] = {  /* program 97 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,  -10,    0,  208,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_097_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_098[1] = {  /* program 98 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  209,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_098_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_099[1] = {  /* program 99 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  210,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_099_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_100[1] = {  /* program 100 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  211,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_100_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_101[1] = {  /* program 101 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  212,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_101_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_102[1] = {  /* program 102 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  213,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_102_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_103[1] = {  /* program 103 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  214,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_103_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_104[1] = {  /* program 104 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  215,    0,   63,    1,  126,    1,   63 },
};
const u16 snd_bank_03_prog_104_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_105[1] = {  /* program 105 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  216,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_105_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_106[1] = {  /* program 106 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  217,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_106_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_107[1] = {  /* program 107 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  218,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_107_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_108[1] = {  /* program 108 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  219,    0,   63,    1,  127,    1,   51 },
};
const u16 snd_bank_03_prog_108_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_109[1] = {  /* program 109 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  220,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_109_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_110[1] = {  /* program 110 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  221,    0,   63,   63,  127,   32,   51 },
};
const u16 snd_bank_03_prog_110_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_111[1] = {  /* program 111 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  222,    0,   63,   63,  126,   32,   51 },
};
const u16 snd_bank_03_prog_111_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_112[1] = {  /* program 112 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  223,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_03_prog_112_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_113[1] = {  /* program 113 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  224,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_113_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_114[1] = {  /* program 114 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  225,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_114_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_115[1] = {  /* program 115 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  226,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_115_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_116[1] = {  /* program 116 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  227,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_116_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_117[1] = {  /* program 117 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  228,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_117_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_118[1] = {  /* program 118 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  229,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_118_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_119[1] = {  /* program 119 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  230,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_119_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_120[1] = {  /* program 120 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  231,    0,   63,    1,  126,    1,   51 },
};
const u16 snd_bank_03_prog_120_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_121[1] = {  /* program 121 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  232,    0,   63,   62,  126,    1,   51 },
};
const u16 snd_bank_03_prog_121_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_122[1] = {  /* program 122 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  233,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_03_prog_122_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_123[1] = {  /* program 123 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  234,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_03_prog_123_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_124[1] = {  /* program 124 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  235,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_03_prog_124_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_125[1] = {  /* program 125 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  236,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_03_prog_125_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_126[1] = {  /* program 126 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  237,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_03_prog_126_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_03_prog_127[1] = {  /* program 127 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  238,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_03_prog_127_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */

const u16 snd_bank_04[128] = {  /* program -> offset of its key splits */
    256, 270, 284, 298, 312, 326, 340, 354, 368, 382, 396, 410,
    424, 438, 452, 466, 480, 494, 508, 522, 536, 550, 564, 578,
    592, 606, 620, 634, 648, 662, 676, 690, 704, 718, 732, 746,
    760, 774, 788, 802, 816, 830, 844, 858, 872, 886, 900, 914,
    928, 942, 956, 970, 984, 998, 1012, 1026, 1040, 1054, 1068, 1082,
    1096, 1110, 1124, 1138, 1152, 1166, 1180, 1194, 1208, 1222, 1236, 1250,
    1264, 1278, 1292, 1306, 1320, 1334, 1348, 1362, 1376, 1390, 1404, 1418,
    1432, 1446, 1460, 1474, 1488, 1502, 1516, 1530, 1544, 1558, 1572, 1586,
    1600, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
const SNDPATCH snd_bank_04_prog_000[1] = {  /* program 0 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  239,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_000_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_001[1] = {  /* program 1 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  240,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_001_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_002[1] = {  /* program 2 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  241,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_002_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_003[1] = {  /* program 3 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  242,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_003_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_004[1] = {  /* program 4 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  243,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_004_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_005[1] = {  /* program 5 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  244,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_005_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_006[1] = {  /* program 6 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  245,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_006_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_007[1] = {  /* program 7 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  246,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_007_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_008[1] = {  /* program 8 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  247,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_008_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_009[1] = {  /* program 9 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  248,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_009_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_010[1] = {  /* program 10 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  249,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_010_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_011[1] = {  /* program 11 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  250,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_011_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_012[1] = {  /* program 12 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  251,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_012_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_013[1] = {  /* program 13 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  252,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_013_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_014[1] = {  /* program 14 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  253,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_014_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_015[1] = {  /* program 15 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  254,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_015_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_016[1] = {  /* program 16 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  255,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_016_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_017[1] = {  /* program 17 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  256,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_017_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_018[1] = {  /* program 18 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  257,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_018_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_019[1] = {  /* program 19 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  258,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_019_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_020[1] = {  /* program 20 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  259,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_020_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_021[1] = {  /* program 21 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  260,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_021_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_022[1] = {  /* program 22 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  261,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_022_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_023[1] = {  /* program 23 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  262,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_023_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_024[1] = {  /* program 24 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  263,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_024_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_025[1] = {  /* program 25 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  264,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_025_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_026[1] = {  /* program 26 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  267,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_026_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_027[1] = {  /* program 27 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  268,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_027_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_028[1] = {  /* program 28 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  269,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_028_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_029[1] = {  /* program 29 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  270,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_029_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_030[1] = {  /* program 30 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  271,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_030_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_031[1] = {  /* program 31 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  272,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_031_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_032[1] = {  /* program 32 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  273,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_032_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_033[1] = {  /* program 33 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  274,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_033_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_034[1] = {  /* program 34 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  275,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_034_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_035[1] = {  /* program 35 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  276,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_035_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_036[1] = {  /* program 36 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  277,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_036_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_037[1] = {  /* program 37 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  278,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_04_prog_037_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_038[1] = {  /* program 38 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  279,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_04_prog_038_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_039[1] = {  /* program 39 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  280,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_039_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_040[1] = {  /* program 40 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  281,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_040_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_041[1] = {  /* program 41 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  282,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_041_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_042[1] = {  /* program 42 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  283,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_042_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_043[1] = {  /* program 43 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  284,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_043_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_044[1] = {  /* program 44 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  285,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_044_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_045[1] = {  /* program 45 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  286,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_045_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_046[1] = {  /* program 46 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  287,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_046_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_047[1] = {  /* program 47 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  288,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_047_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_048[1] = {  /* program 48 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  289,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_048_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_049[1] = {  /* program 49 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  290,    0,   63,   62,  126,    0,   51 },
};
const u16 snd_bank_04_prog_049_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_050[1] = {  /* program 50 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  291,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_050_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_051[1] = {  /* program 51 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  292,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_051_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_052[1] = {  /* program 52 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   55,    0,  293,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_052_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_053[1] = {  /* program 53 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  294,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_053_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_054[1] = {  /* program 54 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  295,    0,   63,    0,  126,    0,   51 },
};
const u16 snd_bank_04_prog_054_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_055[1] = {  /* program 55 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  307,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_055_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_056[1] = {  /* program 56 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  308,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_056_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_057[1] = {  /* program 57 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  309,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_057_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_058[1] = {  /* program 58 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  310,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_058_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_059[1] = {  /* program 59 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  311,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_059_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_060[1] = {  /* program 60 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  312,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_060_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_061[1] = {  /* program 61 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  313,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_061_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_062[1] = {  /* program 62 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  314,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_062_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_063[1] = {  /* program 63 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  315,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_063_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_064[1] = {  /* program 64 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  316,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_064_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_065[1] = {  /* program 65 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,    0,    0,  317,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_065_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_066[1] = {  /* program 66 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  318,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_066_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_067[1] = {  /* program 67 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  319,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_067_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_068[1] = {  /* program 68 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  320,    0,   63,    1,  126,   16,   51 },
};
const u16 snd_bank_04_prog_068_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_069[1] = {  /* program 69 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  321,    0,   63,    1,  126,   16,   51 },
};
const u16 snd_bank_04_prog_069_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_070[1] = {  /* program 70 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  327,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_04_prog_070_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_071[1] = {  /* program 71 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   10,    0,  328,    0,   63,   62,  126,   21,   51 },
};
const u16 snd_bank_04_prog_071_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_072[1] = {  /* program 72 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  334,    0,   63,   62,  126,   16,   51 },
};
const u16 snd_bank_04_prog_072_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_073[1] = {  /* program 73 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  336,    0,   63,   62,  126,   32,   51 },
};
const u16 snd_bank_04_prog_073_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_074[1] = {  /* program 74 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  344,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_074_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_075[1] = {  /* program 75 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  345,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_075_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_076[1] = {  /* program 76 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   30,    0,  346,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_076_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_077[1] = {  /* program 77 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  347,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_077_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_078[1] = {  /* program 78 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  348,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_078_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_079[1] = {  /* program 79 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  349,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_079_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_080[1] = {  /* program 80 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  350,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_080_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_081[1] = {  /* program 81 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   45,    0,  351,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_081_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_082[1] = {  /* program 82 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   60,    0,  352,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_082_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_083[1] = {  /* program 83 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  353,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_083_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_084[1] = {  /* program 84 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   50,    0,  354,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_084_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_085[1] = {  /* program 85 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  355,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_085_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_086[1] = {  /* program 86 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  356,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_086_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_087[1] = {  /* program 87 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   40,    0,  357,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_087_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_088[1] = {  /* program 88 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  358,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_088_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_089[1] = {  /* program 89 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   20,    0,  359,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_089_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_090[1] = {  /* program 90 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   25,    0,  360,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_090_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_091[1] = {  /* program 91 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  361,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_091_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_092[1] = {  /* program 92 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  362,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_092_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_093[1] = {  /* program 93 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   15,    0,  363,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_093_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_094[1] = {  /* program 94 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  370,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_094_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_095[1] = {  /* program 95 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   35,    0,  369,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_095_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */
const SNDPATCH snd_bank_04_prog_096[1] = {  /* program 96 */
    /* ceil  pan  vol  res  sample  pitch  att  dec  vel  rel  frel */
    {  127,  255,   38,    0,  371,    0,   63,   62,  127,   32,   51 },
};
const u16 snd_bank_04_prog_096_end = 0xFFFF;  /* note_ceiling -1: the end of the key splits */

const u16 snd_bank_05[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_06[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_07[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_08[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_09[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_10[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_11[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_12[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_13[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_14[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

const u16 snd_bank_15[128] = {  /* program -> offset of its key splits */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};
