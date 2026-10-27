/*
 * PASS07_TBL.C  CPU passive pattern table for Ibuki
 *
 * Passive07_Tbl is the 203 passive (defensive) pattern routines of character 7 (Ibuki),
 * indexed by Pattern_Index. Read by PASS07.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Passive07_Tbl[])();
extern void Passive07_0000();
extern void Passive07_0001();
extern void Passive07_0002();
extern void Passive07_0003();
extern void Passive07_0004();
extern void Passive07_0005();
extern void Passive07_0006();
extern void Passive07_0007();
extern void Passive07_0008();
extern void Passive07_0009();
extern void Passive07_0010();
extern void Passive07_0011();
extern void Passive07_0012();
extern void Passive07_0013();
extern void Passive07_0014();
extern void Passive07_0015();
extern void Passive07_0016();
extern void Passive07_0017();
extern void Passive07_0018();
extern void Passive07_0019();
extern void Passive07_0020();
extern void Passive07_0021();
extern void Passive07_0022();
extern void Passive07_0023();
extern void Passive07_0024();
extern void Passive07_0025();
extern void Passive07_0026();
extern void Passive07_0027();
extern void Passive07_0028();
extern void Passive07_0029();
extern void Passive07_0030();
extern void Passive07_0031();
extern void Passive07_0032();
extern void Passive07_0033();
extern void Passive07_0034();
extern void Passive07_0035();
extern void Passive07_0036();
extern void Passive07_0037();
extern void Passive07_0038();
extern void Passive07_0039();
extern void Passive07_0040();
extern void Passive07_0041();
extern void Passive07_0042();
extern void Passive07_0043();
extern void Passive07_0044();
extern void Passive07_0045();
extern void Passive07_0046();
extern void Passive07_0047();
extern void Passive07_0048();
extern void Passive07_0049();
extern void Passive07_0050();
extern void Passive07_0051();
extern void Passive07_0052();
extern void Passive07_0053();
extern void Passive07_0054();
extern void Passive07_0055();
extern void Passive07_0056();
extern void Passive07_0057();
extern void Passive07_0058();
extern void Passive07_0059();
extern void Passive07_0060();
extern void Passive07_0061();
extern void Passive07_0062();
extern void Passive07_0063();
extern void Passive07_0064();
extern void Passive07_0065();
extern void Passive07_0066();
extern void Passive07_0067();
extern void Passive07_0068();
extern void Passive07_0069();
extern void Passive07_0070();
extern void Passive07_0071();
extern void Passive07_0072();
extern void Passive07_0073();
extern void Passive07_0074();
extern void Passive07_0075();
extern void Passive07_0076();
extern void Passive07_0077();
extern void Passive07_0078();
extern void Passive07_0079();
extern void Passive07_0080();
extern void Passive07_0081();
extern void Passive07_0082();
extern void Passive07_0083();
extern void Passive07_0084();
extern void Passive07_0085();
extern void Passive07_0086();
extern void Passive07_0087();
extern void Passive07_0088();
extern void Passive07_0089();
extern void Passive07_0090();
extern void Passive07_0091();
extern void Passive07_0092();
extern void Passive07_0093();
extern void Passive07_0094();
extern void Passive07_0095();
extern void Passive07_0096();
extern void Passive07_0097();
extern void Passive07_0098();
extern void Passive07_0099();
extern void Passive07_0100();
extern void Passive07_0101();
extern void Passive07_0102();
extern void Passive07_0103();
extern void Passive07_0104();
extern void Passive07_0105();
extern void Passive07_0106();
extern void Passive07_0107();
extern void Passive07_0108();
extern void Passive07_0109();
extern void Passive07_0110();
extern void Passive07_0111();
extern void Passive07_0112();
extern void Passive07_0113();
extern void Passive07_0114();
extern void Passive07_0115();
extern void Passive07_0116();
extern void Passive07_0117();
extern void Passive07_0118();
extern void Passive07_0119();
extern void Passive07_0120();
extern void Passive07_0121();
extern void Passive07_0122();
extern void Passive07_0123();
extern void Passive07_0124();
extern void Passive07_0125();
extern void Passive07_0126();
extern void Passive07_0127();
extern void Passive07_0128();
extern void Passive07_0129();
extern void Passive07_0130();
extern void Passive07_0131();
extern void Passive07_0132();
extern void Passive07_0133();
extern void Passive07_0134();
extern void Passive07_0135();
extern void Passive07_0136();
extern void Passive07_0137();
extern void Passive07_0138();
extern void Passive07_0139();
extern void Passive07_0140();
extern void Passive07_0141();
extern void Passive07_0142();
extern void Passive07_0143();
extern void Passive07_0144();
extern void Passive07_0145();
extern void Passive07_0146();
extern void Passive07_0147();
extern void Passive07_0148();
extern void Passive07_0149();
extern void Passive07_0150();
extern void Passive07_0151();
extern void Passive07_0152();
extern void Passive07_0153();
extern void Passive07_0154();
extern void Passive07_0155();
extern void Passive07_0156();
extern void Passive07_0157();
extern void Passive07_0158();
extern void Passive07_0159();
extern void Passive07_0160();
extern void Passive07_0161();
extern void Passive07_0162();
extern void Passive07_0163();
extern void Passive07_0164();
extern void Passive07_0165();
extern void Passive07_0166();
extern void Passive07_0167();
extern void Passive07_0168();
extern void Passive07_0169();
extern void Passive07_0170();
extern void Passive07_0171();
extern void Passive07_0172();
extern void Passive07_0173();
extern void Passive07_0174();
extern void Passive07_0175();
extern void Passive07_0176();
extern void Passive07_0177();
extern void Passive07_0178();
extern void Passive07_0179();
extern void Passive07_0180();
extern void Passive07_0181();
extern void Passive07_0182();
extern void Passive07_0183();
extern void Passive07_0184();
extern void Passive07_0185();
extern void Passive07_0186();
extern void Passive07_0187();
extern void Passive07_0188();
extern void Passive07_0189();
extern void Passive07_0190();
extern void Passive07_0191();
extern void Passive07_0192();
extern void Passive07_0193();
extern void Passive07_0194();
extern void Passive07_0195();
extern void Passive07_0196();
extern void Passive07_0197();
extern void Passive07_0198();
extern void Passive07_0199();
extern void Passive07_0200();
extern void Passive07_0201();
extern void Passive07_0202();

void (*const Passive07_Tbl[203])() = {
    Passive07_0000,
    Passive07_0001,
    Passive07_0002,
    Passive07_0003,
    Passive07_0004,
    Passive07_0005,
    Passive07_0006,
    Passive07_0007,
    Passive07_0008,
    Passive07_0009,
    Passive07_0010,
    Passive07_0011,
    Passive07_0012,
    Passive07_0013,
    Passive07_0014,
    Passive07_0015,
    Passive07_0016,
    Passive07_0017,
    Passive07_0018,
    Passive07_0019,
    Passive07_0020,
    Passive07_0021,
    Passive07_0022,
    Passive07_0023,
    Passive07_0024,
    Passive07_0025,
    Passive07_0026,
    Passive07_0027,
    Passive07_0028,
    Passive07_0029,
    Passive07_0030,
    Passive07_0031,
    Passive07_0032,
    Passive07_0033,
    Passive07_0034,
    Passive07_0035,
    Passive07_0036,
    Passive07_0037,
    Passive07_0038,
    Passive07_0039,
    Passive07_0040,
    Passive07_0041,
    Passive07_0042,
    Passive07_0043,
    Passive07_0044,
    Passive07_0045,
    Passive07_0046,
    Passive07_0047,
    Passive07_0048,
    Passive07_0049,
    Passive07_0050,
    Passive07_0051,
    Passive07_0052,
    Passive07_0053,
    Passive07_0054,
    Passive07_0055,
    Passive07_0056,
    Passive07_0057,
    Passive07_0058,
    Passive07_0059,
    Passive07_0060,
    Passive07_0061,
    Passive07_0062,
    Passive07_0063,
    Passive07_0064,
    Passive07_0065,
    Passive07_0066,
    Passive07_0067,
    Passive07_0068,
    Passive07_0069,
    Passive07_0070,
    Passive07_0071,
    Passive07_0072,
    Passive07_0073,
    Passive07_0074,
    Passive07_0075,
    Passive07_0076,
    Passive07_0077,
    Passive07_0078,
    Passive07_0079,
    Passive07_0080,
    Passive07_0081,
    Passive07_0082,
    Passive07_0083,
    Passive07_0084,
    Passive07_0085,
    Passive07_0086,
    Passive07_0087,
    Passive07_0088,
    Passive07_0089,
    Passive07_0090,
    Passive07_0091,
    Passive07_0092,
    Passive07_0093,
    Passive07_0094,
    Passive07_0095,
    Passive07_0096,
    Passive07_0097,
    Passive07_0098,
    Passive07_0099,
    Passive07_0100,
    Passive07_0101,
    Passive07_0102,
    Passive07_0103,
    Passive07_0104,
    Passive07_0105,
    Passive07_0106,
    Passive07_0107,
    Passive07_0108,
    Passive07_0109,
    Passive07_0110,
    Passive07_0111,
    Passive07_0112,
    Passive07_0113,
    Passive07_0114,
    Passive07_0115,
    Passive07_0116,
    Passive07_0117,
    Passive07_0118,
    Passive07_0119,
    Passive07_0120,
    Passive07_0121,
    Passive07_0122,
    Passive07_0123,
    Passive07_0124,
    Passive07_0125,
    Passive07_0126,
    Passive07_0127,
    Passive07_0128,
    Passive07_0129,
    Passive07_0130,
    Passive07_0131,
    Passive07_0132,
    Passive07_0133,
    Passive07_0134,
    Passive07_0135,
    Passive07_0136,
    Passive07_0137,
    Passive07_0138,
    Passive07_0139,
    Passive07_0140,
    Passive07_0141,
    Passive07_0142,
    Passive07_0143,
    Passive07_0144,
    Passive07_0145,
    Passive07_0146,
    Passive07_0147,
    Passive07_0148,
    Passive07_0149,
    Passive07_0150,
    Passive07_0151,
    Passive07_0152,
    Passive07_0153,
    Passive07_0154,
    Passive07_0155,
    Passive07_0156,
    Passive07_0157,
    Passive07_0158,
    Passive07_0159,
    Passive07_0160,
    Passive07_0161,
    Passive07_0162,
    Passive07_0163,
    Passive07_0164,
    Passive07_0165,
    Passive07_0166,
    Passive07_0167,
    Passive07_0168,
    Passive07_0169,
    Passive07_0170,
    Passive07_0171,
    Passive07_0172,
    Passive07_0173,
    Passive07_0174,
    Passive07_0175,
    Passive07_0176,
    Passive07_0177,
    Passive07_0178,
    Passive07_0179,
    Passive07_0180,
    Passive07_0181,
    Passive07_0182,
    Passive07_0183,
    Passive07_0184,
    Passive07_0185,
    Passive07_0186,
    Passive07_0187,
    Passive07_0188,
    Passive07_0189,
    Passive07_0190,
    Passive07_0191,
    Passive07_0192,
    Passive07_0193,
    Passive07_0194,
    Passive07_0195,
    Passive07_0196,
    Passive07_0197,
    Passive07_0198,
    Passive07_0199,
    Passive07_0200,
    Passive07_0201,
    Passive07_0202,
};
