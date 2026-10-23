/*
 * EFF93_TBL.C  tables read by eff88.c and eff90.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff88_loop_tbl[][4];
extern const s16 scr_obj_data88_0[];
extern const s16 scr_obj_unref_0[];
extern const s16 scr_obj_unref_1[];
extern const s16 scr_obj_unref_2[];
extern const s16 scr_obj_unref_3[];
extern const s16 scr_obj_unref_4[];
extern const s16 scr_obj_unref_5[];
extern const s16 scr_obj_unref_6[];
extern const s16 eff90_pos_y_tbl[];

const s16 eff88_loop_tbl[5][4] = {
    { 0, 0, 0, 0 }, { 4, 4, 3, 1 }, { 2, 1, 1, 1 }, { 0, 1, 1, 1 },
    { 3, 3, 3, 3 },
};

const s16 scr_obj_data88_0[81] = {
    1, 2, 8256, -330, 80, 80, 8, 1, 1, 1, 2, 8288, 265, 89, 80, 6,
    0, 0, 1, 2, 8288, 327, 88, 81, 8, 0, 0, 1, 2, 8288, 272, 80,
    72, 9, 0, 0, 1, 2, 8288, 352, 56, 71, 16, 1, 0, 1, 2, 8288,
    265, 89, 80, 6, 0, 0, 1, 2, 8288, 327, 88, 81, 8, 0, 0, 1,
    2, 8288, 319, 65, 71, 11, 1, 0, 1, 2, 8288, 319, 65, 71, 11, 1,
    0,
};

/* scroll object lists that only scr_obj_data_unref (effb8_mes.c) points at, which nothing reads (provisional name)
   */
const s16 scr_obj_unref_0[18] = {
    1, 2, 64, 580, 109, 89, 1, 1, 0, 1, 2, 8280, 704, 38, 80, 13,
    0, 0,
};

/* provisional name */
const s16 scr_obj_unref_1[9] = {
    1, 2, 8280, 854, 48, 80, 14, 0, 0,
};

/* provisional name */
const s16 scr_obj_unref_2[9] = {
    1, 2, 8280, 854, 48, 80, 14, 0, 0,
};

/* provisional name */
const s16 scr_obj_unref_3[9] = {
    1, 2, 8280, 130, 78, 79, 12, 0, 0,
};

/* provisional name */
const s16 scr_obj_unref_4[9] = {
    1, 2, 8291, -288, 64, 74, 20, 1, 1,
};

/* provisional name */
const s16 scr_obj_unref_5[9] = {
    1, 2, 99, 256, 48, 74, 21, 1, 1,
};

/* provisional name */
const s16 scr_obj_unref_6[28] = {
    0, 2, 64, -96, 112, 82, 32, 0, 1, 0, 2, 64, 79, 129, 82, 30,
    0, 1, 0, 2, 64, 208, 65, 82, 31, 0, 1, 0,
};

const s16 eff90_pos_y_tbl[10] = {
    0, 32, 64, 96, 128, 160, 192, 224, 256, -10,
};
