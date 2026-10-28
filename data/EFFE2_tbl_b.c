/*
 * EFFE2_TBL_B.C  after-image settings and colours
 *
 * after_image_data holds the after-image parameter sets (eight words each) that the effect E5
 * controller loads for a move; read by EFFE5.C. after_image_color is the { 1P, 2P } colour of
 * each image step; read by EFFE7.C and EFFE8.C, the single and burst-trail after-images.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u16 after_image_data[][8];
extern const u16 after_image_color[][2];

const u16 after_image_data[12][8] = {
    { 28, 14, 5, 3, 0, 80, 0, 0 }, { 24, 11, 6, 2, 0, 4, 0, 0 },
    { 28, 18, 4, 2, 0, 80, 0, 0 }, { 28, 22, 4, 2, 0, 40, 0, 0 },
    { 0, 0, 2, 2, 8, 3, 0, 0 }, { 28, 2, 4, 1, 0, 80, 0, 0 },
    { 28, 2, 3, 2, 0, 80, 0, 0 }, { 13, 9, 4, 2, 0, 4, 0, 0 },
    { 8, 0, 2, 4, 28, 1, 0, 0 }, { 12, 14, 6, 2, 0, 80, 0, 0 },
    { 28, 14, 4, 2, 0, 80, 0, 0 }, { 1, 1, 2, 2, 12, 3, 0, 0 },
};

const u16 after_image_color[26][2] = {
    { 0x2000, 0x2010 }, { 0x20A0, 0x20A8 }, { 0x20A1, 0x20A9 }, { 0x20A2, 0x20AA },
    { 0x20A3, 0x20AB }, { 0x20A4, 0x20AC }, { 0x20A5, 0x20AD }, { 0x20A6, 0x20AE },
    { 0x20A7, 0x20AF }, { 0x20A4, 0x20AD }, { 0x20A6, 0x20AF }, { 0x20A1, 0x20A8 },
    { 0x20A2, 0x20A9 }, { 0x20A3, 0x20AA }, { 0x20A0, 0x20A8 }, { 0x20A1, 0x20A9 },
    { 0x20A2, 0x20AA }, { 0x20A3, 0x20AB }, { 0x20A0, 0x20A9 }, { 0x20A2, 0x20AB },
    { 0x20A1, 0x20A8 }, { 0x20A3, 0x20AA }, { 0x20A0, 0x20A9 }, { 0x20A2, 0x20AB },
    { 0x20A1, 0x20A8 }, { 0x20A3, 0x20AA },
};
