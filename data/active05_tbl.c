/*
 * ACTIVE05_TBL.C  CPU active pattern table for character 05 (Necro)
 *
 * Pattern05_Tbl lists the Pattern05_0000 .. Pattern05_0065 scripts the computer-controlled
 * Necro runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE05.C
 * (Computer05).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern05_Tbl[])();
extern void Pattern05_0000();
extern void Pattern05_0001();
extern void Pattern05_0002();
extern void Pattern05_0003();
extern void Pattern05_0004();
extern void Pattern05_0005();
extern void Pattern05_0006();
extern void Pattern05_0007();
extern void Pattern05_0008();
extern void Pattern05_0009();
extern void Pattern05_0010();
extern void Pattern05_0011();
extern void Pattern05_0012();
extern void Pattern05_0013();
extern void Pattern05_0014();
extern void Pattern05_0015();
extern void Pattern05_0016();
extern void Pattern05_0017();
extern void Pattern05_0018();
extern void Pattern05_0019();
extern void Pattern05_0020();
extern void Pattern05_0021();
extern void Pattern05_0022();
extern void Pattern05_0023();
extern void Pattern05_0024();
extern void Pattern05_0025();
extern void Pattern05_0026();
extern void Pattern05_0027();
extern void Pattern05_0028();
extern void Pattern05_0029();
extern void Pattern05_0030();
extern void Pattern05_0031();
extern void Pattern05_0032();
extern void Pattern05_0033();
extern void Pattern05_0034();
extern void Pattern05_0035();
extern void Pattern05_0036();
extern void Pattern05_0037();
extern void Pattern05_0038();
extern void Pattern05_0039();
extern void Pattern05_0040();
extern void Pattern05_0041();
extern void Pattern05_0042();
extern void Pattern05_0043();
extern void Pattern05_0044();
extern void Pattern05_0045();
extern void Pattern05_0046();
extern void Pattern05_0047();
extern void Pattern05_0048();
extern void Pattern05_0049();
extern void Pattern05_0050();
extern void Pattern05_0051();
extern void Pattern05_0052();
extern void Pattern05_0053();
extern void Pattern05_0054();
extern void Pattern05_0055();
extern void Pattern05_0056();
extern void Pattern05_0057();
extern void Pattern05_0058();
extern void Pattern05_0059();
extern void Pattern05_0060();
extern void Pattern05_0061();
extern void Pattern05_0062();
extern void Pattern05_0063();
extern void Pattern05_0064();
extern void Pattern05_0065();

void (*const Pattern05_Tbl[66])() = {
    Pattern05_0000,
    Pattern05_0001,
    Pattern05_0002,
    Pattern05_0003,
    Pattern05_0004,
    Pattern05_0005,
    Pattern05_0006,
    Pattern05_0007,
    Pattern05_0008,
    Pattern05_0009,
    Pattern05_0010,
    Pattern05_0011,
    Pattern05_0012,
    Pattern05_0013,
    Pattern05_0014,
    Pattern05_0015,
    Pattern05_0016,
    Pattern05_0017,
    Pattern05_0018,
    Pattern05_0019,
    Pattern05_0020,
    Pattern05_0021,
    Pattern05_0022,
    Pattern05_0023,
    Pattern05_0024,
    Pattern05_0025,
    Pattern05_0026,
    Pattern05_0027,
    Pattern05_0028,
    Pattern05_0029,
    Pattern05_0030,
    Pattern05_0031,
    Pattern05_0032,
    Pattern05_0033,
    Pattern05_0034,
    Pattern05_0035,
    Pattern05_0036,
    Pattern05_0037,
    Pattern05_0038,
    Pattern05_0039,
    Pattern05_0040,
    Pattern05_0041,
    Pattern05_0042,
    Pattern05_0043,
    Pattern05_0044,
    Pattern05_0045,
    Pattern05_0046,
    Pattern05_0047,
    Pattern05_0048,
    Pattern05_0049,
    Pattern05_0050,
    Pattern05_0051,
    Pattern05_0052,
    Pattern05_0053,
    Pattern05_0054,
    Pattern05_0055,
    Pattern05_0056,
    Pattern05_0057,
    Pattern05_0058,
    Pattern05_0059,
    Pattern05_0060,
    Pattern05_0061,
    Pattern05_0062,
    Pattern05_0063,
    Pattern05_0064,
    Pattern05_0065,
};
