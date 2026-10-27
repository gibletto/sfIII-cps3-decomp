/*
 * ACTIVE00_TBL.C  the computer player's active patterns for Gill
 *
 * Pattern00_Tbl lists the 57 active (attacking) pattern routines Pattern00_0000 ..
 * Pattern00_0056 of character 0 (Gill). Computer00 in ACTIVE00.C runs the one chosen by
 * Pattern_Index.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern00_Tbl[])();
extern void Pattern00_0000();
extern void Pattern00_0001();
extern void Pattern00_0002();
extern void Pattern00_0003();
extern void Pattern00_0004();
extern void Pattern00_0005();
extern void Pattern00_0006();
extern void Pattern00_0007();
extern void Pattern00_0008();
extern void Pattern00_0009();
extern void Pattern00_0010();
extern void Pattern00_0011();
extern void Pattern00_0012();
extern void Pattern00_0013();
extern void Pattern00_0014();
extern void Pattern00_0015();
extern void Pattern00_0016();
extern void Pattern00_0017();
extern void Pattern00_0018();
extern void Pattern00_0019();
extern void Pattern00_0020();
extern void Pattern00_0021();
extern void Pattern00_0022();
extern void Pattern00_0023();
extern void Pattern00_0024();
extern void Pattern00_0025();
extern void Pattern00_0026();
extern void Pattern00_0027();
extern void Pattern00_0028();
extern void Pattern00_0029();
extern void Pattern00_0030();
extern void Pattern00_0031();
extern void Pattern00_0032();
extern void Pattern00_0033();
extern void Pattern00_0034();
extern void Pattern00_0035();
extern void Pattern00_0036();
extern void Pattern00_0037();
extern void Pattern00_0038();
extern void Pattern00_0039();
extern void Pattern00_0040();
extern void Pattern00_0041();
extern void Pattern00_0042();
extern void Pattern00_0043();
extern void Pattern00_0044();
extern void Pattern00_0045();
extern void Pattern00_0046();
extern void Pattern00_0047();
extern void Pattern00_0048();
extern void Pattern00_0049();
extern void Pattern00_0050();
extern void Pattern00_0051();
extern void Pattern00_0052();
extern void Pattern00_0053();
extern void Pattern00_0054();
extern void Pattern00_0055();
extern void Pattern00_0056();

void (*const Pattern00_Tbl[57])() = {
    Pattern00_0000,
    Pattern00_0001,
    Pattern00_0002,
    Pattern00_0003,
    Pattern00_0004,
    Pattern00_0005,
    Pattern00_0006,
    Pattern00_0007,
    Pattern00_0008,
    Pattern00_0009,
    Pattern00_0010,
    Pattern00_0011,
    Pattern00_0012,
    Pattern00_0013,
    Pattern00_0014,
    Pattern00_0015,
    Pattern00_0016,
    Pattern00_0017,
    Pattern00_0018,
    Pattern00_0019,
    Pattern00_0020,
    Pattern00_0021,
    Pattern00_0022,
    Pattern00_0023,
    Pattern00_0024,
    Pattern00_0025,
    Pattern00_0026,
    Pattern00_0027,
    Pattern00_0028,
    Pattern00_0029,
    Pattern00_0030,
    Pattern00_0031,
    Pattern00_0032,
    Pattern00_0033,
    Pattern00_0034,
    Pattern00_0035,
    Pattern00_0036,
    Pattern00_0037,
    Pattern00_0038,
    Pattern00_0039,
    Pattern00_0040,
    Pattern00_0041,
    Pattern00_0042,
    Pattern00_0043,
    Pattern00_0044,
    Pattern00_0045,
    Pattern00_0046,
    Pattern00_0047,
    Pattern00_0048,
    Pattern00_0049,
    Pattern00_0050,
    Pattern00_0051,
    Pattern00_0052,
    Pattern00_0053,
    Pattern00_0054,
    Pattern00_0055,
    Pattern00_0056,
};
