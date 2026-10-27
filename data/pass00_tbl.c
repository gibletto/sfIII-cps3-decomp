/*
 * PASS00_TBL.C  Gill's passive pattern table
 *
 * Passive00_Tbl lists the passive pattern routines Passive00_0000 .. Passive00_0131 of
 * character 0 (Gill), indexed by Pattern_Index. Read by PASS00.C, the CPU passive patterns for
 * Gill.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Passive00_Tbl[])();
extern void Passive00_0000();
extern void Passive00_0001();
extern void Passive00_0002();
extern void Passive00_0003();
extern void Passive00_0004();
extern void Passive00_0005();
extern void Passive00_0006();
extern void Passive00_0007();
extern void Passive00_0008();
extern void Passive00_0009();
extern void Passive00_0010();
extern void Passive00_0011();
extern void Passive00_0012();
extern void Passive00_0013();
extern void Passive00_0014();
extern void Passive00_0015();
extern void Passive00_0016();
extern void Passive00_0017();
extern void Passive00_0018();
extern void Passive00_0019();
extern void Passive00_0020();
extern void Passive00_0021();
extern void Passive00_0022();
extern void Passive00_0023();
extern void Passive00_0024();
extern void Passive00_0025();
extern void Passive00_0026();
extern void Passive00_0027();
extern void Passive00_0028();
extern void Passive00_0029();
extern void Passive00_0030();
extern void Passive00_0031();
extern void Passive00_0032();
extern void Passive00_0033();
extern void Passive00_0034();
extern void Passive00_0035();
extern void Passive00_0036();
extern void Passive00_0037();
extern void Passive00_0038();
extern void Passive00_0039();
extern void Passive00_0040();
extern void Passive00_0041();
extern void Passive00_0042();
extern void Passive00_0043();
extern void Passive00_0044();
extern void Passive00_0045();
extern void Passive00_0046();
extern void Passive00_0047();
extern void Passive00_0048();
extern void Passive00_0049();
extern void Passive00_0050();
extern void Passive00_0051();
extern void Passive00_0052();
extern void Passive00_0053();
extern void Passive00_0054();
extern void Passive00_0055();
extern void Passive00_0056();
extern void Passive00_0057();
extern void Passive00_0058();
extern void Passive00_0059();
extern void Passive00_0060();
extern void Passive00_0061();
extern void Passive00_0062();
extern void Passive00_0063();
extern void Passive00_0064();
extern void Passive00_0065();
extern void Passive00_0066();
extern void Passive00_0067();
extern void Passive00_0068();
extern void Passive00_0069();
extern void Passive00_0070();
extern void Passive00_0071();
extern void Passive00_0072();
extern void Passive00_0073();
extern void Passive00_0074();
extern void Passive00_0075();
extern void Passive00_0076();
extern void Passive00_0077();
extern void Passive00_0078();
extern void Passive00_0079();
extern void Passive00_0080();
extern void Passive00_0081();
extern void Passive00_0082();
extern void Passive00_0083();
extern void Passive00_0084();
extern void Passive00_0085();
extern void Passive00_0086();
extern void Passive00_0087();
extern void Passive00_0088();
extern void Passive00_0089();
extern void Passive00_0090();
extern void Passive00_0091();
extern void Passive00_0092();
extern void Passive00_0093();
extern void Passive00_0094();
extern void Passive00_0095();
extern void Passive00_0096();
extern void Passive00_0097();
extern void Passive00_0098();
extern void Passive00_0099();
extern void Passive00_0100();
extern void Passive00_0101();
extern void Passive00_0102();
extern void Passive00_0103();
extern void Passive00_0104();
extern void Passive00_0105();
extern void Passive00_0106();
extern void Passive00_0107();
extern void Passive00_0108();
extern void Passive00_0109();
extern void Passive00_0110();
extern void Passive00_0111();
extern void Passive00_0112();
extern void Passive00_0113();
extern void Passive00_0114();
extern void Passive00_0115();
extern void Passive00_0116();
extern void Passive00_0117();
extern void Passive00_0118();
extern void Passive00_0119();
extern void Passive00_0120();
extern void Passive00_0121();
extern void Passive00_0122();
extern void Passive00_0123();
extern void Passive00_0124();
extern void Passive00_0125();
extern void Passive00_0126();
extern void Passive00_0127();
extern void Passive00_0128();
extern void Passive00_0129();
extern void Passive00_0130();
extern void Passive00_0131();

void (*const Passive00_Tbl[132])() = {
    Passive00_0000,
    Passive00_0001,
    Passive00_0002,
    Passive00_0003,
    Passive00_0004,
    Passive00_0005,
    Passive00_0006,
    Passive00_0007,
    Passive00_0008,
    Passive00_0009,
    Passive00_0010,
    Passive00_0011,
    Passive00_0012,
    Passive00_0013,
    Passive00_0014,
    Passive00_0015,
    Passive00_0016,
    Passive00_0017,
    Passive00_0018,
    Passive00_0019,
    Passive00_0020,
    Passive00_0021,
    Passive00_0022,
    Passive00_0023,
    Passive00_0024,
    Passive00_0025,
    Passive00_0026,
    Passive00_0027,
    Passive00_0028,
    Passive00_0029,
    Passive00_0030,
    Passive00_0031,
    Passive00_0032,
    Passive00_0033,
    Passive00_0034,
    Passive00_0035,
    Passive00_0036,
    Passive00_0037,
    Passive00_0038,
    Passive00_0039,
    Passive00_0040,
    Passive00_0041,
    Passive00_0042,
    Passive00_0043,
    Passive00_0044,
    Passive00_0045,
    Passive00_0046,
    Passive00_0047,
    Passive00_0048,
    Passive00_0049,
    Passive00_0050,
    Passive00_0051,
    Passive00_0052,
    Passive00_0053,
    Passive00_0054,
    Passive00_0055,
    Passive00_0056,
    Passive00_0057,
    Passive00_0058,
    Passive00_0059,
    Passive00_0060,
    Passive00_0061,
    Passive00_0062,
    Passive00_0063,
    Passive00_0064,
    Passive00_0065,
    Passive00_0066,
    Passive00_0067,
    Passive00_0068,
    Passive00_0069,
    Passive00_0070,
    Passive00_0071,
    Passive00_0072,
    Passive00_0073,
    Passive00_0074,
    Passive00_0075,
    Passive00_0076,
    Passive00_0077,
    Passive00_0078,
    Passive00_0079,
    Passive00_0080,
    Passive00_0081,
    Passive00_0082,
    Passive00_0083,
    Passive00_0084,
    Passive00_0085,
    Passive00_0086,
    Passive00_0087,
    Passive00_0088,
    Passive00_0089,
    Passive00_0090,
    Passive00_0091,
    Passive00_0092,
    Passive00_0093,
    Passive00_0094,
    Passive00_0095,
    Passive00_0096,
    Passive00_0097,
    Passive00_0098,
    Passive00_0099,
    Passive00_0100,
    Passive00_0101,
    Passive00_0102,
    Passive00_0103,
    Passive00_0104,
    Passive00_0105,
    Passive00_0106,
    Passive00_0107,
    Passive00_0108,
    Passive00_0109,
    Passive00_0110,
    Passive00_0111,
    Passive00_0112,
    Passive00_0113,
    Passive00_0114,
    Passive00_0115,
    Passive00_0116,
    Passive00_0117,
    Passive00_0118,
    Passive00_0119,
    Passive00_0120,
    Passive00_0121,
    Passive00_0122,
    Passive00_0123,
    Passive00_0124,
    Passive00_0125,
    Passive00_0126,
    Passive00_0127,
    Passive00_0128,
    Passive00_0129,
    Passive00_0130,
    Passive00_0131,
};
