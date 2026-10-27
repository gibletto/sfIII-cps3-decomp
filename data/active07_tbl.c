/*
 * ACTIVE07_TBL.C  CPU active pattern table for character 07 (Ibuki)
 *
 * Pattern07_Tbl lists the Pattern07_0000 .. Pattern07_0063 scripts the computer-controlled
 * Ibuki runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE07.C
 * (Computer07).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern07_Tbl[])();
extern void Pattern07_0000();
extern void Pattern07_0001();
extern void Pattern07_0002();
extern void Pattern07_0003();
extern void Pattern07_0004();
extern void Pattern07_0005();
extern void Pattern07_0006();
extern void Pattern07_0007();
extern void Pattern07_0008();
extern void Pattern07_0009();
extern void Pattern07_0010();
extern void Pattern07_0011();
extern void Pattern07_0012();
extern void Pattern07_0013();
extern void Pattern07_0014();
extern void Pattern07_0015();
extern void Pattern07_0016();
extern void Pattern07_0017();
extern void Pattern07_0018();
extern void Pattern07_0019();
extern void Pattern07_0020();
extern void Pattern07_0021();
extern void Pattern07_0022();
extern void Pattern07_0023();
extern void Pattern07_0024();
extern void Pattern07_0025();
extern void Pattern07_0026();
extern void Pattern07_0027();
extern void Pattern07_0028();
extern void Pattern07_0029();
extern void Pattern07_0030();
extern void Pattern07_0031();
extern void Pattern07_0032();
extern void Pattern07_0033();
extern void Pattern07_0034();
extern void Pattern07_0035();
extern void Pattern07_0036();
extern void Pattern07_0037();
extern void Pattern07_0038();
extern void Pattern07_0039();
extern void Pattern07_0040();
extern void Pattern07_0041();
extern void Pattern07_0042();
extern void Pattern07_0043();
extern void Pattern07_0044();
extern void Pattern07_0045();
extern void Pattern07_0046();
extern void Pattern07_0047();
extern void Pattern07_0048();
extern void Pattern07_0049();
extern void Pattern07_0050();
extern void Pattern07_0051();
extern void Pattern07_0052();
extern void Pattern07_0053();
extern void Pattern07_0054();
extern void Pattern07_0055();
extern void Pattern07_0056();
extern void Pattern07_0057();
extern void Pattern07_0058();
extern void Pattern07_0059();
extern void Pattern07_0060();
extern void Pattern07_0061();
extern void Pattern07_0062();
extern void Pattern07_0063();

void (*const Pattern07_Tbl[64])() = {
    Pattern07_0000,
    Pattern07_0001,
    Pattern07_0002,
    Pattern07_0003,
    Pattern07_0004,
    Pattern07_0005,
    Pattern07_0006,
    Pattern07_0007,
    Pattern07_0008,
    Pattern07_0009,
    Pattern07_0010,
    Pattern07_0011,
    Pattern07_0012,
    Pattern07_0013,
    Pattern07_0014,
    Pattern07_0015,
    Pattern07_0016,
    Pattern07_0017,
    Pattern07_0018,
    Pattern07_0019,
    Pattern07_0020,
    Pattern07_0021,
    Pattern07_0022,
    Pattern07_0023,
    Pattern07_0024,
    Pattern07_0025,
    Pattern07_0026,
    Pattern07_0027,
    Pattern07_0028,
    Pattern07_0029,
    Pattern07_0030,
    Pattern07_0031,
    Pattern07_0032,
    Pattern07_0033,
    Pattern07_0034,
    Pattern07_0035,
    Pattern07_0036,
    Pattern07_0037,
    Pattern07_0038,
    Pattern07_0039,
    Pattern07_0040,
    Pattern07_0041,
    Pattern07_0042,
    Pattern07_0043,
    Pattern07_0044,
    Pattern07_0045,
    Pattern07_0046,
    Pattern07_0047,
    Pattern07_0048,
    Pattern07_0049,
    Pattern07_0050,
    Pattern07_0051,
    Pattern07_0052,
    Pattern07_0053,
    Pattern07_0054,
    Pattern07_0055,
    Pattern07_0056,
    Pattern07_0057,
    Pattern07_0058,
    Pattern07_0059,
    Pattern07_0060,
    Pattern07_0061,
    Pattern07_0062,
    Pattern07_0063,
};
