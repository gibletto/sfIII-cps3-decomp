/*
 * EFF03_TBL.C  shadow, falling stone and stage scenery tables
 *
 * plef_kage_data gives the shadow offset, priority and pattern of each effect 03 shadow number
 * (a single empty entry); read by EFF03.C. eff04_stone_tbl holds the rows of stones dropped at
 * the start, one row picked at random, and eff04_wait_tbl the random waits between later
 * stones; read by EFF04.C, the falling stones controller. scr_obj_num is the number of
 * scenery objects of each stage and area; the scr_obj_data_S_A lists after it hold the object
 * rows (family, colour, position, priority, animation, hit stop and line-scroll sync) that
 * scr_obj_data names, each list after the first stage and area that uses it; read by EFF05.C,
 * the stage scenery objects.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 plef_kage_data[][4];
extern const s16 eff04_stone_tbl[];
extern const s16 eff04_wait_tbl[];
extern const s16 scr_obj_num[][3];
extern const s16 scr_obj_data_0_0[];
extern const s16 scr_obj_data_1_0[];
extern const s16 scr_obj_data_12_0[];
extern const s16 scr_obj_data_2_0[];
extern const s16 scr_obj_data_unref_0[];
extern const s16 scr_obj_data_2_1[];
extern const s16 scr_obj_data_3_0[];
extern const s16 scr_obj_data_3_1[];
extern const s16 scr_obj_data_4_0[];
extern const s16 scr_obj_data_4_1[];
extern const s16 scr_obj_data_5_0[];
extern const s16 scr_obj_data_6_0[];
extern const s16 scr_obj_data_6_1[];
extern const s16 scr_obj_data_6_2[];
extern const s16 scr_obj_data_7_0[];
extern const s16 scr_obj_data_8_0[];
extern const s16 scr_obj_data_8_1[];
extern const s16 scr_obj_data_9_0[];

const s16 plef_kage_data[1][4] = {
    { 0, 0, 0, 0 },
};

const s16 eff04_stone_tbl[56] = {
    1, 6, 8, 3, 4, 0, 5, 2, 3, 6, 1, 0, 4, 5, 5, 10,
    3, 0, 4, 2, 1, 9, 0, 2, 5, 3, 1, 6, 3, 2, 5, 1,
    6, 4, 0, 6, 2, 10, 7, 1, 0, 5, 0, 1, 2, 3, 4, 5,
    6, 6, 5, 4, 3, 2, 1, 0,
};

const s16 eff04_wait_tbl[32] = {
    10, 34, 128, 34, 100, 48, 50, 68, 40, 184, 58, 84, 118, 28, 134, 74,
    58, 144, 150, 74, 110, 28, 84, 78, 98, 128, 60, 28, 78, 51, 200, 81,
};

const s16 scr_obj_num[14][3] = {
    { 5, 5, 5 },
    { 4, 4, 4 },
    { 1, 4, 4 },
    { 6, 3, 3 },
    { 3, 5, 5 },
    { 9, 9, 9 },
    { 7, 6, 4 },
    { 2, 2, 2 },
    { 0, 4, 4 },
    { 2, 2, 2 },
    { 3, 6, 6 },
    { 4, 1, 1 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};

/* stage/area 0/0, 0/1, 0/2; provisional name */
const s16 scr_obj_data_0_0[45] = {
    0, 2, 8256, 416, 96, 82, 10, 0, 0,
    0, 2, 8256, 528, 79, 82, 9, 0, 0,
    0, 2, 8256, 480, 256, 92, 4, 0, 0,
    0, 2, 8256, 512, 64, 83, 22, 0, 0,
    0, 2, 8256, 512, 64, 83, 23, 0, 0,
};

/* stage/area 1/0, 1/1, 1/2; provisional name */
const s16 scr_obj_data_1_0[36] = {
    0, 2, 8256, 608, 40, 82, 1, 0, 0,
    0, 2, 8256, 512, 16, 22, 3, 0, 0,
    1, 2, 8256, 512, 318, 83, 9, 1, 0,
    0, 2, 8256, 512, 64, 80, 13, 0, 0,
};

/* stage/area 12/0, 12/1, 12/2 with no objects; not an object row; provisional name */
const s16 scr_obj_data_12_0[1] = {
    0,
};

/* stage/area 2/0, 11/1, 11/2; provisional name */
const s16 scr_obj_data_2_0[9] = {
    0, 2, 8256, 16, 19, 20, 11, 0, 1,
};

/* not referred to; provisional name */
const s16 scr_obj_data_unref_0[9] = {
    0, 2, 8256, 9, 65, 74, 12, 0, 1,
};

/* stage/area 2/1, 2/2, 11/0; provisional name */
const s16 scr_obj_data_2_1[36] = {
    0, 2, 64, 16, 80, 80, 2, 1, 1,
    0, 2, 64, -288, 80, 83, 4, 1, 1,
    1, 2, 8282, -17, 48, 84, 17, 0, 1,
    1, 2, 8282, -89, 136, 83, 24, 0, 1,
};

/* stage/area 3/0, 10/1, 10/2; provisional name */
const s16 scr_obj_data_3_0[54] = {
    1, 2, 8256, 383, 32, 78, 14, 0, 0,
    1, 2, 8256, 463, 304, 93, 6, 1, 0,
    0, 2, 8256, 413, 69, 81, 1, 0, 0,
    0, 2, 8256, 479, 64, 84, 2, 0, 0,
    0, 2, 64, 576, 64, 87, 3, 0, 0,
    0, 2, 8277, 523, 126, 86, 17, 1, 0,
};

/* stage/area 3/1, 3/2, 10/0; provisional name */
const s16 scr_obj_data_3_1[27] = {
    0, 2, 8256, 512, 176, 84, 0, 0, 0,
    0, 2, 8256, 352, 21, 20, 1, 0, 0,
    0, 2, 8272, 552, 88, 86, 68, 1, 0,
};

/* stage/area 4/0; provisional name */
const s16 scr_obj_data_4_0[27] = {
    0, 2, 8256, -32, 49, 78, 26, 0, 1,
    0, 2, 8256, 64, 136, 78, 27, 0, 1,
    0, 3, 64, 479, 160, 90, 8, 0, 0,
};

/* stage/area 4/1, 4/2; provisional name */
const s16 scr_obj_data_4_1[45] = {
    0, 2, 8256, -32, 49, 78, 26, 0, 1,
    0, 2, 8256, 64, 136, 78, 27, 0, 1,
    1, 2, 8280, -16, 56, 77, 22, 0, 1,
    1, 2, 8280, -114, 68, 78, 23, 0, 1,
    0, 1, 64, 479, 160, 90, 8, 0, 0,
};

/* stage/area 5/0, 5/1, 5/2; provisional name */
const s16 scr_obj_data_5_0[81] = {
    0, 2, 8256, 504, 192, 75, 3, 0, 0,
    0, 2, 8256, 552, 152, 75, 4, 0, 0,
    0, 2, 8256, 581, 123, 75, 15, 1, 0,
    0, 2, 8256, 386, 104, 75, 21, 1, 0,
    0, 2, 8256, 512, 104, 75, 12, 1, 0,
    0, 2, 8256, 872, 112, 75, 14, 1, 0,
    0, 2, 64, 472, 168, 76, 39, 1, 0,
    0, 2, 64, 499, 168, 76, 40, 1, 0,
    0, 2, 64, 528, 168, 76, 41, 1, 0,
};

/* stage/area 6/0; provisional name */
const s16 scr_obj_data_6_0[63] = {
    0, 2, 8292, -56, 66, 75, 3, 1, 1,
    1, 2, 8292, -48, 78, 76, 4, 0, 1,
    0, 2, 8256, 0, 144, 82, 17, 0, 1,
    0, 2, 8256, -64, 56, 73, 21, 0, 1,
    0, 2, 8256, 0, 70, 85, 22, 0, 1,
    0, 2, 64, 48, 97, 78, 25, 0, 1,
    0, 2, 8256, 94, 105, 83, 28, 1, 1,
};

/* stage/area 6/1; provisional name */
const s16 scr_obj_data_6_1[54] = {
    1, 2, 8256, 0, 224, 83, 29, 1, 1,
    0, 2, 8256, -176, 81, 80, 20, 0, 1,
    1, 2, 64, 48, 97, 78, 25, 0, 1,
    1, 2, 8256, 94, 105, 83, 28, 1, 1,
    0, 2, 8256, -64, 56, 73, 21, 0, 1,
    0, 2, 8256, 0, 70, 85, 22, 0, 1,
};

/* stage/area 6/2; provisional name */
const s16 scr_obj_data_6_2[36] = {
    1, 2, 8256, 0, 224, 83, 29, 1, 1,
    0, 2, 8256, -176, 81, 80, 20, 0, 1,
    1, 2, 64, 48, 97, 78, 25, 0, 1,
    1, 2, 8256, 94, 105, 83, 28, 1, 1,
};

/* stage/area 7/0, 7/1, 7/2; provisional name */
const s16 scr_obj_data_7_0[18] = {
    1, 1, 8256, 304, 112, 88, 0, 0, 0,
    1, 5, 8256, 288, 96, 73, 1, 0, 0,
};

/* stage/area 8/0 with no objects; provisional name */
const s16 scr_obj_data_8_0[9] = {
    0, 2, 8256, 512, 40, 76, 0, 0, 0,
};

/* stage/area 8/1, 8/2; provisional name */
const s16 scr_obj_data_8_1[36] = {
    0, 2, 8256, 480, 80, 81, 3, 0, 0,
    0, 2, 8256, 687, 64, 81, 18, 0, 0,
    0, 1, 8256, 535, 192, 93, 1, 1, 0,
    0, 2, 8256, 559, 62, 82, 5, 1, 0,
};

/* stage/area 9/0, 9/1, 9/2; provisional name */
const s16 scr_obj_data_9_0[18] = {
    1, 2, 8280, 416, 112, 79, 14, 0, 0,
    1, 2, 8280, 472, 88, 76, 19, 1, 0,
};
