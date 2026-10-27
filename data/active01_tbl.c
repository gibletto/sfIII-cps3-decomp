/*
 * ACTIVE01_TBL.C  CPU active pattern table for character 01 (Alex)
 *
 * Pattern01_Tbl lists the Pattern01_0000 .. Pattern01_0055 scripts the computer-controlled
 * Alex runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE01.C
 * (Computer01).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern01_Tbl[])();
extern void Pattern01_0000();
extern void Pattern01_0001();
extern void Pattern01_0002();
extern void Pattern01_0003();
extern void Pattern01_0004();
extern void Pattern01_0005();
extern void Pattern01_0006();
extern void Pattern01_0007();
extern void Pattern01_0008();
extern void Pattern01_0009();
extern void Pattern01_0010();
extern void Pattern01_0011();
extern void Pattern01_0012();
extern void Pattern01_0013();
extern void Pattern01_0014();
extern void Pattern01_0015();
extern void Pattern01_0016();
extern void Pattern01_0017();
extern void Pattern01_0018();
extern void Pattern01_0019();
extern void Pattern01_0020();
extern void Pattern01_0021();
extern void Pattern01_0022();
extern void Pattern01_0023();
extern void Pattern01_0024();
extern void Pattern01_0025();
extern void Pattern01_0026();
extern void Pattern01_0027();
extern void Pattern01_0028();
extern void Pattern01_0029();
extern void Pattern01_0030();
extern void Pattern01_0031();
extern void Pattern01_0032();
extern void Pattern01_0033();
extern void Pattern01_0034();
extern void Pattern01_0035();
extern void Pattern01_0036();
extern void Pattern01_0037();
extern void Pattern01_0038();
extern void Pattern01_0039();
extern void Pattern01_0040();
extern void Pattern01_0041();
extern void Pattern01_0042();
extern void Pattern01_0043();
extern void Pattern01_0044();
extern void Pattern01_0045();
extern void Pattern01_0046();
extern void Pattern01_0047();
extern void Pattern01_0048();
extern void Pattern01_0049();
extern void Pattern01_0050();
extern void Pattern01_0051();
extern void Pattern01_0052();
extern void Pattern01_0053();
extern void Pattern01_0054();
extern void Pattern01_0055();

void (*const Pattern01_Tbl[56])() = {
    Pattern01_0000,
    Pattern01_0001,
    Pattern01_0002,
    Pattern01_0003,
    Pattern01_0004,
    Pattern01_0005,
    Pattern01_0006,
    Pattern01_0007,
    Pattern01_0008,
    Pattern01_0009,
    Pattern01_0010,
    Pattern01_0011,
    Pattern01_0012,
    Pattern01_0013,
    Pattern01_0014,
    Pattern01_0015,
    Pattern01_0016,
    Pattern01_0017,
    Pattern01_0018,
    Pattern01_0019,
    Pattern01_0020,
    Pattern01_0021,
    Pattern01_0022,
    Pattern01_0023,
    Pattern01_0024,
    Pattern01_0025,
    Pattern01_0026,
    Pattern01_0027,
    Pattern01_0028,
    Pattern01_0029,
    Pattern01_0030,
    Pattern01_0031,
    Pattern01_0032,
    Pattern01_0033,
    Pattern01_0034,
    Pattern01_0035,
    Pattern01_0036,
    Pattern01_0037,
    Pattern01_0038,
    Pattern01_0039,
    Pattern01_0040,
    Pattern01_0041,
    Pattern01_0042,
    Pattern01_0043,
    Pattern01_0044,
    Pattern01_0045,
    Pattern01_0046,
    Pattern01_0047,
    Pattern01_0048,
    Pattern01_0049,
    Pattern01_0050,
    Pattern01_0051,
    Pattern01_0052,
    Pattern01_0053,
    Pattern01_0054,
    Pattern01_0055,
};
