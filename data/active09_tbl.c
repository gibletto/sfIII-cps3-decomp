/*
 * ACTIVE09_TBL.C  CPU active pattern table for character 09 (Oro)
 *
 * Pattern09_Tbl lists the Pattern09_0000 .. Pattern09_0079 scripts the computer-controlled Oro
 * runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE09.C (Computer09).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern09_Tbl[])();
extern void Pattern09_0000();
extern void Pattern09_0001();
extern void Pattern09_0002();
extern void Pattern09_0003();
extern void Pattern09_0004();
extern void Pattern09_0005();
extern void Pattern09_0006();
extern void Pattern09_0007();
extern void Pattern09_0008();
extern void Pattern09_0009();
extern void Pattern09_0010();
extern void Pattern09_0011();
extern void Pattern09_0012();
extern void Pattern09_0013();
extern void Pattern09_0014();
extern void Pattern09_0015();
extern void Pattern09_0016();
extern void Pattern09_0017();
extern void Pattern09_0018();
extern void Pattern09_0019();
extern void Pattern09_0020();
extern void Pattern09_0021();
extern void Pattern09_0022();
extern void Pattern09_0023();
extern void Pattern09_0024();
extern void Pattern09_0025();
extern void Pattern09_0026();
extern void Pattern09_0027();
extern void Pattern09_0028();
extern void Pattern09_0029();
extern void Pattern09_0030();
extern void Pattern09_0031();
extern void Pattern09_0032();
extern void Pattern09_0033();
extern void Pattern09_0034();
extern void Pattern09_0035();
extern void Pattern09_0036();
extern void Pattern09_0037();
extern void Pattern09_0038();
extern void Pattern09_0039();
extern void Pattern09_0040();
extern void Pattern09_0041();
extern void Pattern09_0042();
extern void Pattern09_0043();
extern void Pattern09_0044();
extern void Pattern09_0045();
extern void Pattern09_0046();
extern void Pattern09_0047();
extern void Pattern09_0048();
extern void Pattern09_0049();
extern void Pattern09_0050();
extern void Pattern09_0051();
extern void Pattern09_0052();
extern void Pattern09_0053();
extern void Pattern09_0054();
extern void Pattern09_0055();
extern void Pattern09_0056();
extern void Pattern09_0057();
extern void Pattern09_0058();
extern void Pattern09_0059();
extern void Pattern09_0060();
extern void Pattern09_0061();
extern void Pattern09_0062();
extern void Pattern09_0063();
extern void Pattern09_0064();
extern void Pattern09_0065();
extern void Pattern09_0066();
extern void Pattern09_0067();
extern void Pattern09_0068();
extern void Pattern09_0069();
extern void Pattern09_0070();
extern void Pattern09_0071();
extern void Pattern09_0072();
extern void Pattern09_0073();
extern void Pattern09_0074();
extern void Pattern09_0075();
extern void Pattern09_0076();
extern void Pattern09_0077();
extern void Pattern09_0078();
extern void Pattern09_0079();

void (*const Pattern09_Tbl[80])() = {
    Pattern09_0000,
    Pattern09_0001,
    Pattern09_0002,
    Pattern09_0003,
    Pattern09_0004,
    Pattern09_0005,
    Pattern09_0006,
    Pattern09_0007,
    Pattern09_0008,
    Pattern09_0009,
    Pattern09_0010,
    Pattern09_0011,
    Pattern09_0012,
    Pattern09_0013,
    Pattern09_0014,
    Pattern09_0015,
    Pattern09_0016,
    Pattern09_0017,
    Pattern09_0018,
    Pattern09_0019,
    Pattern09_0020,
    Pattern09_0021,
    Pattern09_0022,
    Pattern09_0023,
    Pattern09_0024,
    Pattern09_0025,
    Pattern09_0026,
    Pattern09_0027,
    Pattern09_0028,
    Pattern09_0029,
    Pattern09_0030,
    Pattern09_0031,
    Pattern09_0032,
    Pattern09_0033,
    Pattern09_0034,
    Pattern09_0035,
    Pattern09_0036,
    Pattern09_0037,
    Pattern09_0038,
    Pattern09_0039,
    Pattern09_0040,
    Pattern09_0041,
    Pattern09_0042,
    Pattern09_0043,
    Pattern09_0044,
    Pattern09_0045,
    Pattern09_0046,
    Pattern09_0047,
    Pattern09_0048,
    Pattern09_0049,
    Pattern09_0050,
    Pattern09_0051,
    Pattern09_0052,
    Pattern09_0053,
    Pattern09_0054,
    Pattern09_0055,
    Pattern09_0056,
    Pattern09_0057,
    Pattern09_0058,
    Pattern09_0059,
    Pattern09_0060,
    Pattern09_0061,
    Pattern09_0062,
    Pattern09_0063,
    Pattern09_0064,
    Pattern09_0065,
    Pattern09_0066,
    Pattern09_0067,
    Pattern09_0068,
    Pattern09_0069,
    Pattern09_0070,
    Pattern09_0071,
    Pattern09_0072,
    Pattern09_0073,
    Pattern09_0074,
    Pattern09_0075,
    Pattern09_0076,
    Pattern09_0077,
    Pattern09_0078,
    Pattern09_0079,
};
