/*
 * ACTIVE12_TBL.C  CPU active pattern table for character 12 (Sean)
 *
 * Pattern12_Tbl lists the Pattern12_0000 .. Pattern12_0083 scripts the computer-controlled
 * Sean runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE12.C
 * (Computer12).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern12_Tbl[])();
extern void Pattern12_0000();
extern void Pattern12_0001();
extern void Pattern12_0002();
extern void Pattern12_0003();
extern void Pattern12_0004();
extern void Pattern12_0005();
extern void Pattern12_0006();
extern void Pattern12_0007();
extern void Pattern12_0008();
extern void Pattern12_0009();
extern void Pattern12_0010();
extern void Pattern12_0011();
extern void Pattern12_0012();
extern void Pattern12_0013();
extern void Pattern12_0014();
extern void Pattern12_0015();
extern void Pattern12_0016();
extern void Pattern12_0017();
extern void Pattern12_0018();
extern void Pattern12_0019();
extern void Pattern12_0020();
extern void Pattern12_0021();
extern void Pattern12_0022();
extern void Pattern12_0023();
extern void Pattern12_0024();
extern void Pattern12_0025();
extern void Pattern12_0026();
extern void Pattern12_0027();
extern void Pattern12_0028();
extern void Pattern12_0029();
extern void Pattern12_0030();
extern void Pattern12_0031();
extern void Pattern12_0032();
extern void Pattern12_0033();
extern void Pattern12_0034();
extern void Pattern12_0035();
extern void Pattern12_0036();
extern void Pattern12_0037();
extern void Pattern12_0038();
extern void Pattern12_0039();
extern void Pattern12_0040();
extern void Pattern12_0041();
extern void Pattern12_0042();
extern void Pattern12_0043();
extern void Pattern12_0044();
extern void Pattern12_0045();
extern void Pattern12_0046();
extern void Pattern12_0047();
extern void Pattern12_0048();
extern void Pattern12_0049();
extern void Pattern12_0050();
extern void Pattern12_0051();
extern void Pattern12_0052();
extern void Pattern12_0053();
extern void Pattern12_0054();
extern void Pattern12_0055();
extern void Pattern12_0056();
extern void Pattern12_0057();
extern void Pattern12_0058();
extern void Pattern12_0059();
extern void Pattern12_0060();
extern void Pattern12_0061();
extern void Pattern12_0062();
extern void Pattern12_0063();
extern void Pattern12_0064();
extern void Pattern12_0065();
extern void Pattern12_0066();
extern void Pattern12_0067();
extern void Pattern12_0068();
extern void Pattern12_0069();
extern void Pattern12_0070();
extern void Pattern12_0071();
extern void Pattern12_0072();
extern void Pattern12_0073();
extern void Pattern12_0074();
extern void Pattern12_0075();
extern void Pattern12_0076();
extern void Pattern12_0077();
extern void Pattern12_0078();
extern void Pattern12_0079();
extern void Pattern12_0080();
extern void Pattern12_0081();
extern void Pattern12_0082();
extern void Pattern12_0083();

void (*const Pattern12_Tbl[84])() = {
    Pattern12_0000,
    Pattern12_0001,
    Pattern12_0002,
    Pattern12_0003,
    Pattern12_0004,
    Pattern12_0005,
    Pattern12_0006,
    Pattern12_0007,
    Pattern12_0008,
    Pattern12_0009,
    Pattern12_0010,
    Pattern12_0011,
    Pattern12_0012,
    Pattern12_0013,
    Pattern12_0014,
    Pattern12_0015,
    Pattern12_0016,
    Pattern12_0017,
    Pattern12_0018,
    Pattern12_0019,
    Pattern12_0020,
    Pattern12_0021,
    Pattern12_0022,
    Pattern12_0023,
    Pattern12_0024,
    Pattern12_0025,
    Pattern12_0026,
    Pattern12_0027,
    Pattern12_0028,
    Pattern12_0029,
    Pattern12_0030,
    Pattern12_0031,
    Pattern12_0032,
    Pattern12_0033,
    Pattern12_0034,
    Pattern12_0035,
    Pattern12_0036,
    Pattern12_0037,
    Pattern12_0038,
    Pattern12_0039,
    Pattern12_0040,
    Pattern12_0041,
    Pattern12_0042,
    Pattern12_0043,
    Pattern12_0044,
    Pattern12_0045,
    Pattern12_0046,
    Pattern12_0047,
    Pattern12_0048,
    Pattern12_0049,
    Pattern12_0050,
    Pattern12_0051,
    Pattern12_0052,
    Pattern12_0053,
    Pattern12_0054,
    Pattern12_0055,
    Pattern12_0056,
    Pattern12_0057,
    Pattern12_0058,
    Pattern12_0059,
    Pattern12_0060,
    Pattern12_0061,
    Pattern12_0062,
    Pattern12_0063,
    Pattern12_0064,
    Pattern12_0065,
    Pattern12_0066,
    Pattern12_0067,
    Pattern12_0068,
    Pattern12_0069,
    Pattern12_0070,
    Pattern12_0071,
    Pattern12_0072,
    Pattern12_0073,
    Pattern12_0074,
    Pattern12_0075,
    Pattern12_0076,
    Pattern12_0077,
    Pattern12_0078,
    Pattern12_0079,
    Pattern12_0080,
    Pattern12_0081,
    Pattern12_0082,
    Pattern12_0083,
};
