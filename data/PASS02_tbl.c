/*
 * PASS02_TBL.C  CPU passive pattern table for Ryu
 *
 * Passive02_Tbl is the 110 passive (defensive) pattern routines of character 2 (Ryu), indexed
 * by Pattern_Index. Read by PASS02.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Passive02_Tbl[])();
extern void Passive02_0000();
extern void Passive02_0001();
extern void Passive02_0002();
extern void Passive02_0003();
extern void Passive02_0004();
extern void Passive02_0005();
extern void Passive02_0006();
extern void Passive02_0007();
extern void Passive02_0008();
extern void Passive02_0009();
extern void Passive02_0010();
extern void Passive02_0011();
extern void Passive02_0012();
extern void Passive02_0013();
extern void Passive02_0014();
extern void Passive02_0015();
extern void Passive02_0016();
extern void Passive02_0017();
extern void Passive02_0018();
extern void Passive02_0019();
extern void Passive02_0020();
extern void Passive02_0021();
extern void Passive02_0022();
extern void Passive02_0023();
extern void Passive02_0024();
extern void Passive02_0025();
extern void Passive02_0026();
extern void Passive02_0027();
extern void Passive02_0028();
extern void Passive02_0029();
extern void Passive02_0030();
extern void Passive02_0031();
extern void Passive02_0032();
extern void Passive02_0033();
extern void Passive02_0034();
extern void Passive02_0035();
extern void Passive02_0036();
extern void Passive02_0037();
extern void Passive02_0038();
extern void Passive02_0039();
extern void Passive02_0040();
extern void Passive02_0041();
extern void Passive02_0042();
extern void Passive02_0043();
extern void Passive02_0044();
extern void Passive02_0045();
extern void Passive02_0046();
extern void Passive02_0047();
extern void Passive02_0048();
extern void Passive02_0049();
extern void Passive02_0050();
extern void Passive02_0051();
extern void Passive02_0052();
extern void Passive02_0053();
extern void Passive02_0054();
extern void Passive02_0055();
extern void Passive02_0056();
extern void Passive02_0057();
extern void Passive02_0058();
extern void Passive02_0059();
extern void Passive02_0060();
extern void Passive02_0061();
extern void Passive02_0062();
extern void Passive02_0063();
extern void Passive02_0064();
extern void Passive02_0065();
extern void Passive02_0066();
extern void Passive02_0067();
extern void Passive02_0068();
extern void Passive02_0069();
extern void Passive02_0070();
extern void Passive02_0071();
extern void Passive02_0072();
extern void Passive02_0073();
extern void Passive02_0074();
extern void Passive02_0075();
extern void Passive02_0076();
extern void Passive02_0077();
extern void Passive02_0078();
extern void Passive02_0079();
extern void Passive02_0080();
extern void Passive02_0081();
extern void Passive02_0082();
extern void Passive02_0083();
extern void Passive02_0084();
extern void Passive02_0085();
extern void Passive02_0086();
extern void Passive02_0087();
extern void Passive02_0088();
extern void Passive02_0089();
extern void Passive02_0090();
extern void Passive02_0091();
extern void Passive02_0092();
extern void Passive02_0093();
extern void Passive02_0094();
extern void Passive02_0095();
extern void Passive02_0096();
extern void Passive02_0097();
extern void Passive02_0098();
extern void Passive02_0099();
extern void Passive02_0100();
extern void Passive02_0101();
extern void Passive02_0102();
extern void Passive02_0103();
extern void Passive02_0104();
extern void Passive02_0105();
extern void Passive02_0106();
extern void Passive02_0107();
extern void Passive02_0108();
extern void Passive02_0109();

void (*const Passive02_Tbl[110])() = {
    Passive02_0000,
    Passive02_0001,
    Passive02_0002,
    Passive02_0003,
    Passive02_0004,
    Passive02_0005,
    Passive02_0006,
    Passive02_0007,
    Passive02_0008,
    Passive02_0009,
    Passive02_0010,
    Passive02_0011,
    Passive02_0012,
    Passive02_0013,
    Passive02_0014,
    Passive02_0015,
    Passive02_0016,
    Passive02_0017,
    Passive02_0018,
    Passive02_0019,
    Passive02_0020,
    Passive02_0021,
    Passive02_0022,
    Passive02_0023,
    Passive02_0024,
    Passive02_0025,
    Passive02_0026,
    Passive02_0027,
    Passive02_0028,
    Passive02_0029,
    Passive02_0030,
    Passive02_0031,
    Passive02_0032,
    Passive02_0033,
    Passive02_0034,
    Passive02_0035,
    Passive02_0036,
    Passive02_0037,
    Passive02_0038,
    Passive02_0039,
    Passive02_0040,
    Passive02_0041,
    Passive02_0042,
    Passive02_0043,
    Passive02_0044,
    Passive02_0045,
    Passive02_0046,
    Passive02_0047,
    Passive02_0048,
    Passive02_0049,
    Passive02_0050,
    Passive02_0051,
    Passive02_0052,
    Passive02_0053,
    Passive02_0054,
    Passive02_0055,
    Passive02_0056,
    Passive02_0057,
    Passive02_0058,
    Passive02_0059,
    Passive02_0060,
    Passive02_0061,
    Passive02_0062,
    Passive02_0063,
    Passive02_0064,
    Passive02_0065,
    Passive02_0066,
    Passive02_0067,
    Passive02_0068,
    Passive02_0069,
    Passive02_0070,
    Passive02_0071,
    Passive02_0072,
    Passive02_0073,
    Passive02_0074,
    Passive02_0075,
    Passive02_0076,
    Passive02_0077,
    Passive02_0078,
    Passive02_0079,
    Passive02_0080,
    Passive02_0081,
    Passive02_0082,
    Passive02_0083,
    Passive02_0084,
    Passive02_0085,
    Passive02_0086,
    Passive02_0087,
    Passive02_0088,
    Passive02_0089,
    Passive02_0090,
    Passive02_0091,
    Passive02_0092,
    Passive02_0093,
    Passive02_0094,
    Passive02_0095,
    Passive02_0096,
    Passive02_0097,
    Passive02_0098,
    Passive02_0099,
    Passive02_0100,
    Passive02_0101,
    Passive02_0102,
    Passive02_0103,
    Passive02_0104,
    Passive02_0105,
    Passive02_0106,
    Passive02_0107,
    Passive02_0108,
    Passive02_0109,
};
