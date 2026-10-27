/*
 * ACTIVE04_TBL.C  CPU active pattern table for character 04 (Dudley)
 *
 * Pattern04_Tbl lists the Pattern04_0000 .. Pattern04_0063 scripts the computer-controlled
 * Dudley runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE04.C
 * (Computer04).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern04_Tbl[])();
extern void Pattern04_0000();
extern void Pattern04_0001();
extern void Pattern04_0002();
extern void Pattern04_0003();
extern void Pattern04_0004();
extern void Pattern04_0005();
extern void Pattern04_0006();
extern void Pattern04_0007();
extern void Pattern04_0008();
extern void Pattern04_0009();
extern void Pattern04_0010();
extern void Pattern04_0011();
extern void Pattern04_0012();
extern void Pattern04_0013();
extern void Pattern04_0014();
extern void Pattern04_0015();
extern void Pattern04_0016();
extern void Pattern04_0017();
extern void Pattern04_0018();
extern void Pattern04_0019();
extern void Pattern04_0020();
extern void Pattern04_0021();
extern void Pattern04_0022();
extern void Pattern04_0023();
extern void Pattern04_0024();
extern void Pattern04_0025();
extern void Pattern04_0026();
extern void Pattern04_0027();
extern void Pattern04_0028();
extern void Pattern04_0029();
extern void Pattern04_0030();
extern void Pattern04_0031();
extern void Pattern04_0032();
extern void Pattern04_0033();
extern void Pattern04_0034();
extern void Pattern04_0035();
extern void Pattern04_0036();
extern void Pattern04_0037();
extern void Pattern04_0038();
extern void Pattern04_0039();
extern void Pattern04_0040();
extern void Pattern04_0041();
extern void Pattern04_0042();
extern void Pattern04_0043();
extern void Pattern04_0044();
extern void Pattern04_0045();
extern void Pattern04_0046();
extern void Pattern04_0047();
extern void Pattern04_0048();
extern void Pattern04_0049();
extern void Pattern04_0050();
extern void Pattern04_0051();
extern void Pattern04_0052();
extern void Pattern04_0053();
extern void Pattern04_0054();
extern void Pattern04_0055();
extern void Pattern04_0056();
extern void Pattern04_0057();
extern void Pattern04_0058();
extern void Pattern04_0059();
extern void Pattern04_0060();
extern void Pattern04_0061();
extern void Pattern04_0062();
extern void Pattern04_0063();

void (*const Pattern04_Tbl[64])() = {
    Pattern04_0000,
    Pattern04_0001,
    Pattern04_0002,
    Pattern04_0003,
    Pattern04_0004,
    Pattern04_0005,
    Pattern04_0006,
    Pattern04_0007,
    Pattern04_0008,
    Pattern04_0009,
    Pattern04_0010,
    Pattern04_0011,
    Pattern04_0012,
    Pattern04_0013,
    Pattern04_0014,
    Pattern04_0015,
    Pattern04_0016,
    Pattern04_0017,
    Pattern04_0018,
    Pattern04_0019,
    Pattern04_0020,
    Pattern04_0021,
    Pattern04_0022,
    Pattern04_0023,
    Pattern04_0024,
    Pattern04_0025,
    Pattern04_0026,
    Pattern04_0027,
    Pattern04_0028,
    Pattern04_0029,
    Pattern04_0030,
    Pattern04_0031,
    Pattern04_0032,
    Pattern04_0033,
    Pattern04_0034,
    Pattern04_0035,
    Pattern04_0036,
    Pattern04_0037,
    Pattern04_0038,
    Pattern04_0039,
    Pattern04_0040,
    Pattern04_0041,
    Pattern04_0042,
    Pattern04_0043,
    Pattern04_0044,
    Pattern04_0045,
    Pattern04_0046,
    Pattern04_0047,
    Pattern04_0048,
    Pattern04_0049,
    Pattern04_0050,
    Pattern04_0051,
    Pattern04_0052,
    Pattern04_0053,
    Pattern04_0054,
    Pattern04_0055,
    Pattern04_0056,
    Pattern04_0057,
    Pattern04_0058,
    Pattern04_0059,
    Pattern04_0060,
    Pattern04_0061,
    Pattern04_0062,
    Pattern04_0063,
};
