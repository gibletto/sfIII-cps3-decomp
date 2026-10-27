/*
 * ACTIVE03_TBL.C  CPU active pattern table for character 03 (Yun and Yang)
 *
 * Pattern03_Tbl lists the Pattern03_0000 .. Pattern03_0066 scripts the computer-controlled Yun
 * runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE03.C (Computer03),
 * which Com_Active in COM_PL.C also runs for Yang.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern03_Tbl[])();
extern void Pattern03_0000();
extern void Pattern03_0001();
extern void Pattern03_0002();
extern void Pattern03_0003();
extern void Pattern03_0004();
extern void Pattern03_0005();
extern void Pattern03_0006();
extern void Pattern03_0007();
extern void Pattern03_0008();
extern void Pattern03_0009();
extern void Pattern03_0010();
extern void Pattern03_0011();
extern void Pattern03_0012();
extern void Pattern03_0013();
extern void Pattern03_0014();
extern void Pattern03_0015();
extern void Pattern03_0016();
extern void Pattern03_0017();
extern void Pattern03_0018();
extern void Pattern03_0019();
extern void Pattern03_0020();
extern void Pattern03_0021();
extern void Pattern03_0022();
extern void Pattern03_0023();
extern void Pattern03_0024();
extern void Pattern03_0025();
extern void Pattern03_0026();
extern void Pattern03_0027();
extern void Pattern03_0028();
extern void Pattern03_0029();
extern void Pattern03_0030();
extern void Pattern03_0031();
extern void Pattern03_0032();
extern void Pattern03_0033();
extern void Pattern03_0034();
extern void Pattern03_0035();
extern void Pattern03_0036();
extern void Pattern03_0037();
extern void Pattern03_0038();
extern void Pattern03_0039();
extern void Pattern03_0040();
extern void Pattern03_0041();
extern void Pattern03_0042();
extern void Pattern03_0043();
extern void Pattern03_0044();
extern void Pattern03_0045();
extern void Pattern03_0046();
extern void Pattern03_0047();
extern void Pattern03_0048();
extern void Pattern03_0049();
extern void Pattern03_0050();
extern void Pattern03_0051();
extern void Pattern03_0052();
extern void Pattern03_0053();
extern void Pattern03_0054();
extern void Pattern03_0055();
extern void Pattern03_0056();
extern void Pattern03_0057();
extern void Pattern03_0058();
extern void Pattern03_0059();
extern void Pattern03_0060();
extern void Pattern03_0061();
extern void Pattern03_0062();
extern void Pattern03_0063();
extern void Pattern03_0064();
extern void Pattern03_0065();
extern void Pattern03_0066();

void (*const Pattern03_Tbl[67])() = {
    Pattern03_0000,
    Pattern03_0001,
    Pattern03_0002,
    Pattern03_0003,
    Pattern03_0004,
    Pattern03_0005,
    Pattern03_0006,
    Pattern03_0007,
    Pattern03_0008,
    Pattern03_0009,
    Pattern03_0010,
    Pattern03_0011,
    Pattern03_0012,
    Pattern03_0013,
    Pattern03_0014,
    Pattern03_0015,
    Pattern03_0016,
    Pattern03_0017,
    Pattern03_0018,
    Pattern03_0019,
    Pattern03_0020,
    Pattern03_0021,
    Pattern03_0022,
    Pattern03_0023,
    Pattern03_0024,
    Pattern03_0025,
    Pattern03_0026,
    Pattern03_0027,
    Pattern03_0028,
    Pattern03_0029,
    Pattern03_0030,
    Pattern03_0031,
    Pattern03_0032,
    Pattern03_0033,
    Pattern03_0034,
    Pattern03_0035,
    Pattern03_0036,
    Pattern03_0037,
    Pattern03_0038,
    Pattern03_0039,
    Pattern03_0040,
    Pattern03_0041,
    Pattern03_0042,
    Pattern03_0043,
    Pattern03_0044,
    Pattern03_0045,
    Pattern03_0046,
    Pattern03_0047,
    Pattern03_0048,
    Pattern03_0049,
    Pattern03_0050,
    Pattern03_0051,
    Pattern03_0052,
    Pattern03_0053,
    Pattern03_0054,
    Pattern03_0055,
    Pattern03_0056,
    Pattern03_0057,
    Pattern03_0058,
    Pattern03_0059,
    Pattern03_0060,
    Pattern03_0061,
    Pattern03_0062,
    Pattern03_0063,
    Pattern03_0064,
    Pattern03_0065,
    Pattern03_0066,
};
