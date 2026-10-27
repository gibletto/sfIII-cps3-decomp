/*
 * ACTIVE02_TBL.C  CPU active pattern table for character 02 (Ryu)
 *
 * Pattern02_Tbl lists the Pattern02_0000 .. Pattern02_0070 scripts the computer-controlled Ryu
 * runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE02.C (Computer02).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern02_Tbl[])();
extern void Pattern02_0000();
extern void Pattern02_0001();
extern void Pattern02_0002();
extern void Pattern02_0003();
extern void Pattern02_0004();
extern void Pattern02_0005();
extern void Pattern02_0006();
extern void Pattern02_0007();
extern void Pattern02_0008();
extern void Pattern02_0009();
extern void Pattern02_0010();
extern void Pattern02_0011();
extern void Pattern02_0012();
extern void Pattern02_0013();
extern void Pattern02_0014();
extern void Pattern02_0015();
extern void Pattern02_0016();
extern void Pattern02_0017();
extern void Pattern02_0018();
extern void Pattern02_0019();
extern void Pattern02_0020();
extern void Pattern02_0021();
extern void Pattern02_0022();
extern void Pattern02_0023();
extern void Pattern02_0024();
extern void Pattern02_0025();
extern void Pattern02_0026();
extern void Pattern02_0027();
extern void Pattern02_0028();
extern void Pattern02_0029();
extern void Pattern02_0030();
extern void Pattern02_0031();
extern void Pattern02_0032();
extern void Pattern02_0033();
extern void Pattern02_0034();
extern void Pattern02_0035();
extern void Pattern02_0036();
extern void Pattern02_0037();
extern void Pattern02_0038();
extern void Pattern02_0039();
extern void Pattern02_0040();
extern void Pattern02_0041();
extern void Pattern02_0042();
extern void Pattern02_0043();
extern void Pattern02_0044();
extern void Pattern02_0045();
extern void Pattern02_0046();
extern void Pattern02_0047();
extern void Pattern02_0048();
extern void Pattern02_0049();
extern void Pattern02_0050();
extern void Pattern02_0051();
extern void Pattern02_0052();
extern void Pattern02_0053();
extern void Pattern02_0054();
extern void Pattern02_0055();
extern void Pattern02_0056();
extern void Pattern02_0057();
extern void Pattern02_0058();
extern void Pattern02_0059();
extern void Pattern02_0060();
extern void Pattern02_0061();
extern void Pattern02_0062();
extern void Pattern02_0063();
extern void Pattern02_0064();
extern void Pattern02_0065();
extern void Pattern02_0066();
extern void Pattern02_0067();
extern void Pattern02_0068();
extern void Pattern02_0069();
extern void Pattern02_0070();

void (*const Pattern02_Tbl[71])() = {
    Pattern02_0000,
    Pattern02_0001,
    Pattern02_0002,
    Pattern02_0003,
    Pattern02_0004,
    Pattern02_0005,
    Pattern02_0006,
    Pattern02_0007,
    Pattern02_0008,
    Pattern02_0009,
    Pattern02_0010,
    Pattern02_0011,
    Pattern02_0012,
    Pattern02_0013,
    Pattern02_0014,
    Pattern02_0015,
    Pattern02_0016,
    Pattern02_0017,
    Pattern02_0018,
    Pattern02_0019,
    Pattern02_0020,
    Pattern02_0021,
    Pattern02_0022,
    Pattern02_0023,
    Pattern02_0024,
    Pattern02_0025,
    Pattern02_0026,
    Pattern02_0027,
    Pattern02_0028,
    Pattern02_0029,
    Pattern02_0030,
    Pattern02_0031,
    Pattern02_0032,
    Pattern02_0033,
    Pattern02_0034,
    Pattern02_0035,
    Pattern02_0036,
    Pattern02_0037,
    Pattern02_0038,
    Pattern02_0039,
    Pattern02_0040,
    Pattern02_0041,
    Pattern02_0042,
    Pattern02_0043,
    Pattern02_0044,
    Pattern02_0045,
    Pattern02_0046,
    Pattern02_0047,
    Pattern02_0048,
    Pattern02_0049,
    Pattern02_0050,
    Pattern02_0051,
    Pattern02_0052,
    Pattern02_0053,
    Pattern02_0054,
    Pattern02_0055,
    Pattern02_0056,
    Pattern02_0057,
    Pattern02_0058,
    Pattern02_0059,
    Pattern02_0060,
    Pattern02_0061,
    Pattern02_0062,
    Pattern02_0063,
    Pattern02_0064,
    Pattern02_0065,
    Pattern02_0066,
    Pattern02_0067,
    Pattern02_0068,
    Pattern02_0069,
    Pattern02_0070,
};
