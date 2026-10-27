/*
 * ACTIVE11_TBL.C  CPU active pattern table for character 11 (Ken)
 *
 * Pattern11_Tbl lists the Pattern11_0000 .. Pattern11_0071 scripts the computer-controlled Ken
 * runs in active (attacking) mode, indexed by Pattern_Index. Read by ACTIVE11.C (Computer11).
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Pattern11_Tbl[])();
extern void Pattern11_0000();
extern void Pattern11_0001();
extern void Pattern11_0002();
extern void Pattern11_0003();
extern void Pattern11_0004();
extern void Pattern11_0005();
extern void Pattern11_0006();
extern void Pattern11_0007();
extern void Pattern11_0008();
extern void Pattern11_0009();
extern void Pattern11_0010();
extern void Pattern11_0011();
extern void Pattern11_0012();
extern void Pattern11_0013();
extern void Pattern11_0014();
extern void Pattern11_0015();
extern void Pattern11_0016();
extern void Pattern11_0017();
extern void Pattern11_0018();
extern void Pattern11_0019();
extern void Pattern11_0020();
extern void Pattern11_0021();
extern void Pattern11_0022();
extern void Pattern11_0023();
extern void Pattern11_0024();
extern void Pattern11_0025();
extern void Pattern11_0026();
extern void Pattern11_0027();
extern void Pattern11_0028();
extern void Pattern11_0029();
extern void Pattern11_0030();
extern void Pattern11_0031();
extern void Pattern11_0032();
extern void Pattern11_0033();
extern void Pattern11_0034();
extern void Pattern11_0035();
extern void Pattern11_0036();
extern void Pattern11_0037();
extern void Pattern11_0038();
extern void Pattern11_0039();
extern void Pattern11_0040();
extern void Pattern11_0041();
extern void Pattern11_0042();
extern void Pattern11_0043();
extern void Pattern11_0044();
extern void Pattern11_0045();
extern void Pattern11_0046();
extern void Pattern11_0047();
extern void Pattern11_0048();
extern void Pattern11_0049();
extern void Pattern11_0050();
extern void Pattern11_0051();
extern void Pattern11_0052();
extern void Pattern11_0053();
extern void Pattern11_0054();
extern void Pattern11_0055();
extern void Pattern11_0056();
extern void Pattern11_0057();
extern void Pattern11_0058();
extern void Pattern11_0059();
extern void Pattern11_0060();
extern void Pattern11_0061();
extern void Pattern11_0062();
extern void Pattern11_0063();
extern void Pattern11_0064();
extern void Pattern11_0065();
extern void Pattern11_0066();
extern void Pattern11_0067();
extern void Pattern11_0068();
extern void Pattern11_0069();
extern void Pattern11_0070();
extern void Pattern11_0071();

void (*const Pattern11_Tbl[72])() = {
    Pattern11_0000,
    Pattern11_0001,
    Pattern11_0002,
    Pattern11_0003,
    Pattern11_0004,
    Pattern11_0005,
    Pattern11_0006,
    Pattern11_0007,
    Pattern11_0008,
    Pattern11_0009,
    Pattern11_0010,
    Pattern11_0011,
    Pattern11_0012,
    Pattern11_0013,
    Pattern11_0014,
    Pattern11_0015,
    Pattern11_0016,
    Pattern11_0017,
    Pattern11_0018,
    Pattern11_0019,
    Pattern11_0020,
    Pattern11_0021,
    Pattern11_0022,
    Pattern11_0023,
    Pattern11_0024,
    Pattern11_0025,
    Pattern11_0026,
    Pattern11_0027,
    Pattern11_0028,
    Pattern11_0029,
    Pattern11_0030,
    Pattern11_0031,
    Pattern11_0032,
    Pattern11_0033,
    Pattern11_0034,
    Pattern11_0035,
    Pattern11_0036,
    Pattern11_0037,
    Pattern11_0038,
    Pattern11_0039,
    Pattern11_0040,
    Pattern11_0041,
    Pattern11_0042,
    Pattern11_0043,
    Pattern11_0044,
    Pattern11_0045,
    Pattern11_0046,
    Pattern11_0047,
    Pattern11_0048,
    Pattern11_0049,
    Pattern11_0050,
    Pattern11_0051,
    Pattern11_0052,
    Pattern11_0053,
    Pattern11_0054,
    Pattern11_0055,
    Pattern11_0056,
    Pattern11_0057,
    Pattern11_0058,
    Pattern11_0059,
    Pattern11_0060,
    Pattern11_0061,
    Pattern11_0062,
    Pattern11_0063,
    Pattern11_0064,
    Pattern11_0065,
    Pattern11_0066,
    Pattern11_0067,
    Pattern11_0068,
    Pattern11_0069,
    Pattern11_0070,
    Pattern11_0071,
};
