/*
 * ACTIVE08_TBL.C  CPU active pattern table for character 08 (Elena)
 *
 * Pattern08_Tbl lists the Pattern08_0000 .. Pattern08_0063 scripts the computer-controlled
 * Elena runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE08.C
 * (Computer08).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern08_Tbl[])();
extern void Pattern08_0000();
extern void Pattern08_0001();
extern void Pattern08_0002();
extern void Pattern08_0003();
extern void Pattern08_0004();
extern void Pattern08_0005();
extern void Pattern08_0006();
extern void Pattern08_0007();
extern void Pattern08_0008();
extern void Pattern08_0009();
extern void Pattern08_0010();
extern void Pattern08_0011();
extern void Pattern08_0012();
extern void Pattern08_0013();
extern void Pattern08_0014();
extern void Pattern08_0015();
extern void Pattern08_0016();
extern void Pattern08_0017();
extern void Pattern08_0018();
extern void Pattern08_0019();
extern void Pattern08_0020();
extern void Pattern08_0021();
extern void Pattern08_0022();
extern void Pattern08_0023();
extern void Pattern08_0024();
extern void Pattern08_0025();
extern void Pattern08_0026();
extern void Pattern08_0027();
extern void Pattern08_0028();
extern void Pattern08_0029();
extern void Pattern08_0030();
extern void Pattern08_0031();
extern void Pattern08_0032();
extern void Pattern08_0033();
extern void Pattern08_0034();
extern void Pattern08_0035();
extern void Pattern08_0036();
extern void Pattern08_0037();
extern void Pattern08_0038();
extern void Pattern08_0039();
extern void Pattern08_0040();
extern void Pattern08_0041();
extern void Pattern08_0042();
extern void Pattern08_0043();
extern void Pattern08_0044();
extern void Pattern08_0045();
extern void Pattern08_0046();
extern void Pattern08_0047();
extern void Pattern08_0048();
extern void Pattern08_0049();
extern void Pattern08_0050();
extern void Pattern08_0051();
extern void Pattern08_0052();
extern void Pattern08_0053();
extern void Pattern08_0054();
extern void Pattern08_0055();
extern void Pattern08_0056();
extern void Pattern08_0057();
extern void Pattern08_0058();
extern void Pattern08_0059();
extern void Pattern08_0060();
extern void Pattern08_0061();
extern void Pattern08_0062();
extern void Pattern08_0063();

void (*const Pattern08_Tbl[64])() = {
    Pattern08_0000,
    Pattern08_0001,
    Pattern08_0002,
    Pattern08_0003,
    Pattern08_0004,
    Pattern08_0005,
    Pattern08_0006,
    Pattern08_0007,
    Pattern08_0008,
    Pattern08_0009,
    Pattern08_0010,
    Pattern08_0011,
    Pattern08_0012,
    Pattern08_0013,
    Pattern08_0014,
    Pattern08_0015,
    Pattern08_0016,
    Pattern08_0017,
    Pattern08_0018,
    Pattern08_0019,
    Pattern08_0020,
    Pattern08_0021,
    Pattern08_0022,
    Pattern08_0023,
    Pattern08_0024,
    Pattern08_0025,
    Pattern08_0026,
    Pattern08_0027,
    Pattern08_0028,
    Pattern08_0029,
    Pattern08_0030,
    Pattern08_0031,
    Pattern08_0032,
    Pattern08_0033,
    Pattern08_0034,
    Pattern08_0035,
    Pattern08_0036,
    Pattern08_0037,
    Pattern08_0038,
    Pattern08_0039,
    Pattern08_0040,
    Pattern08_0041,
    Pattern08_0042,
    Pattern08_0043,
    Pattern08_0044,
    Pattern08_0045,
    Pattern08_0046,
    Pattern08_0047,
    Pattern08_0048,
    Pattern08_0049,
    Pattern08_0050,
    Pattern08_0051,
    Pattern08_0052,
    Pattern08_0053,
    Pattern08_0054,
    Pattern08_0055,
    Pattern08_0056,
    Pattern08_0057,
    Pattern08_0058,
    Pattern08_0059,
    Pattern08_0060,
    Pattern08_0061,
    Pattern08_0062,
    Pattern08_0063,
};
