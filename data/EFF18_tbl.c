/*
 * EFF18_TBL.C  reacting stage object placement and effect 19 piece positions
 *
 * scr_obj_num18 gives the number of effect 18 objects for each display index and compel
 * setting, and scr_obj_data18_0 .. scr_obj_data18_7 their rows (family, colour, position,
 * priority, animations, line-scroll sync and behaviour routine), reached through
 * scr_obj_data18; read by EFF18.C, the reacting stage objects. eff19_data_tbl gives the
 * position and priority of each of the seven pieces of effect 19; read by EFF19.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 scr_obj_num18[][4];
extern const s16 scr_obj_data18_0[][12];
extern const s16 scr_obj_data18_1[][12];
extern const s16 scr_obj_data18_2[][12];
extern const s16 scr_obj_data18_3[][12];
extern const s16 scr_obj_data18_4[][12];
extern const s16 scr_obj_data18_5[][12];
extern const s16 scr_obj_data18_6[][12];
extern const s16 scr_obj_data18_7[][12];
extern const s16 eff19_data_tbl[][3];

const s16 scr_obj_num18[6][4] = {
    { 1, 1, 1, 1 }, { 3, 3, 3, 3 }, { 2, 2, 2, 2 }, { 4, 4, 4, 4 },
    { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
};

/* one row per object: { dead_f, my_family, colour code, x, y, priority, dir_old, dir_step, hit_stop,
   sync_suzi, routine_no[1], old_rno[0] } */
const s16 scr_obj_data18_0[1][12] = {
    { 1, 2, 0x2063, -224, 64, 74, 18, 19, 1, 0, 0, 1 },
};

const s16 scr_obj_data18_1[3][12] = {
    { 1, 2, 0x5A, 336, 80, 75, 20, 21, 1, 1, 0, 1 },
    { 1, 2, 0x5A, 48, 48, 73, 28, 29, 1, 1, 1, 0 },
    { 1, 2, 0x205A, -112, 57, 76, 25, 26, 1, 1, 0, 1 },
};

const s16 scr_obj_data18_2[2][12] = {
    { 1, 2, 0x2055, 608, 64, 85, 19, 20, 1, 0, 0, 1 },
    { 0, 2, 0x2055, 488, 48, 77, 21, 22, 1, 0, 0, 1 },
};

const s16 scr_obj_data18_3[2][12] = {
    { 0, 2, 0x2055, 496, 48, 75, 32, 33, 1, 0, 0, 1 },
    { 1, 2, 0x2055, 552, 56, 76, 30, 31, 1, 0, 0, 1 },
};

const s16 scr_obj_data18_4[4][12] = {
    { 0, 2, 0x64, 16, 66, 75, 7, 8, 1, 1, 0, 1 },
    { 1, 2, 0x2064, -305, 62, 76, 5, 6, 1, 1, 0, 1 },
    { 1, 2, 0x2064, -193, 56, 74, 9, 10, 1, 1, 0, 1 },
    { 0, 2, 0x2064, -113, 66, 75, 11, 12, 1, 1, 0, 1 },
};

const s16 scr_obj_data18_5[4][12] = {
    { 0, 2, 0x64, 16, 66, 75, 7, 8, 1, 1, 0, 1 },
    { 1, 2, 0x2064, -305, 62, 76, 5, 6, 1, 1, 0, 1 },
    { 0, 2, 0x2064, -113, 66, 75, 11, 12, 1, 1, 0, 1 },
    { 1, 2, 0x2064, 84, 66, 75, 13, 14, 1, 1, 0, 1 },
};

const s16 scr_obj_data18_6[1][12] = {
    { 0, 2, 0x2058, 464, 104, 77, 15, 16, 1, 0, 0, 1 },
};

const s16 scr_obj_data18_7[1][12] = {
    { 1, 2, 0x2059, 304, 48, 75, 25, 42, 1, 0, 0, 1 },
};

const s16 eff19_data_tbl[7][3] = {
    { 256, 256, 78 }, { 208, 208, 78 }, { 256, 160, 78 }, { 672, 160, 85 },
    { 568, 152, 78 }, { 432, 96, 79 }, { 96, 192, 94 },
};
