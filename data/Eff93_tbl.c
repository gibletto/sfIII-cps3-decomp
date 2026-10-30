/*
 * EFF93_TBL.C  stage background object records and BG1 display positions
 *
 * eff88_loop_tbl gives the number of effect 88 objects by type and compel flag, and
 * scr_obj_data88_0 .. scr_obj_data88_4_0 their records (family, colour, position, priority,
 * animation and settings), each list named after the first type and compel flag that uses it
 * and reached through scr_obj_data88 in EFF88.C, the stage background object.
 * eff90_pos_y_tbl gives the y position of each of the nine effect 90 works; read by EFF90.C,
 * the BG1 display object.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff88_loop_tbl[][4];
extern const s16 scr_obj_data88_0[];
extern const s16 scr_obj_data88_1_0[];
extern const s16 scr_obj_data88_1_2[];
extern const s16 scr_obj_data88_1_3[];
extern const s16 scr_obj_data88_2_0[];
extern const s16 scr_obj_data88_2_1[];
extern const s16 scr_obj_data88_2_2[];
extern const s16 scr_obj_data88_2_3[];
extern const s16 scr_obj_data88_3_0[];
extern const s16 scr_obj_data88_3_2[];
extern const s16 scr_obj_data88_4_0[];
extern const s16 eff90_pos_y_tbl[];

const s16 eff88_loop_tbl[5][4] = {
    { 0, 0, 0, 0 }, { 4, 4, 3, 1 }, { 2, 1, 1, 1 }, { 0, 1, 1, 1 },
    { 3, 3, 3, 3 },
};

/* type/compel flag 0/0, 0/1, 0/2, 0/3 with no objects; provisional name */
const s16 scr_obj_data88_0[9] = {
    1, 2, 8256, -330, 80, 80, 8, 1, 1,
};

/* type/compel flag 1/0, 1/1; provisional name */
const s16 scr_obj_data88_1_0[36] = {
    1, 2, 8288, 265, 89, 80, 6, 0, 0,
    1, 2, 8288, 327, 88, 81, 8, 0, 0,
    1, 2, 8288, 272, 80, 72, 9, 0, 0,
    1, 2, 8288, 352, 56, 71, 16, 1, 0,
};

/* type/compel flag 1/2; provisional name */
const s16 scr_obj_data88_1_2[27] = {
    1, 2, 8288, 265, 89, 80, 6, 0, 0,
    1, 2, 8288, 327, 88, 81, 8, 0, 0,
    1, 2, 8288, 319, 65, 71, 11, 1, 0,
};

/* type/compel flag 1/3; provisional name */
const s16 scr_obj_data88_1_3[9] = {
    1, 2, 8288, 319, 65, 71, 11, 1, 0,
};

/* type/compel flag 2/0; provisional name */
const s16 scr_obj_data88_2_0[18] = {
    1, 2, 64, 580, 109, 89, 1, 1, 0, 1, 2, 8280, 704, 38, 80, 13,
    0, 0,
};

/* type/compel flag 2/1; provisional name */
const s16 scr_obj_data88_2_1[9] = {
    1, 2, 8280, 854, 48, 80, 14, 0, 0,
};

/* type/compel flag 2/2; provisional name */
const s16 scr_obj_data88_2_2[9] = {
    1, 2, 8280, 854, 48, 80, 14, 0, 0,
};

/* type/compel flag 2/3; provisional name */
const s16 scr_obj_data88_2_3[9] = {
    1, 2, 8280, 130, 78, 79, 12, 0, 0,
};

/* type/compel flag 3/1; 3/0 with no objects; provisional name */
const s16 scr_obj_data88_3_0[9] = {
    1, 2, 8291, -288, 64, 74, 20, 1, 1,
};

/* type/compel flag 3/2, 3/3; provisional name */
const s16 scr_obj_data88_3_2[9] = {
    1, 2, 99, 256, 48, 74, 21, 1, 1,
};

/* type/compel flag 4/0, 4/1, 4/2, 4/3; provisional name */
const s16 scr_obj_data88_4_0[28] = {
    0, 2, 64, -96, 112, 82, 32, 0, 1, 0, 2, 64, 79, 129, 82, 30,
    0, 1, 0, 2, 64, 208, 65, 82, 31, 0, 1, 0,
};

const s16 eff90_pos_y_tbl[10] = {
    0, 32, 64, 96, 128, 160, 192, 224, 256, -10,
};
