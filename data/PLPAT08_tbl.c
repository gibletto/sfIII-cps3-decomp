/*
 * PLPAT08_TBL.C  tables read by PLPAT08.c and PLPAT09.c: Elena's special attack routine table and the tables of
 * set_tenguiwa (Oro's rocks)
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const u8 pl08_hcs_tbl[];
extern void (*const pl08_exatt_table[])(PLW*);
extern const u8 tenguiwa_stage_data[][4];
extern const u8 tenguiwa_stand_by[][8];
extern const s16 tenguiwa_pos_hosei[][6];
extern const u8 tenguiwa_type_flag[];
extern void Att_PL08_HEALING();
extern void Att_SENPUUKYAKU();
extern void Att_SHOURYUUKEN();
extern void Att_SHOURYUUREPPA();

const u8 pl08_hcs_tbl[8] = {
    0, 0, 0, 1, 0, 1, 1, 1,
};

void (*const pl08_exatt_table[6])(PLW*) = {
    Att_SHOURYUUKEN, Att_SENPUUKYAKU, Att_SENPUUKYAKU, Att_SHOURYUUREPPA,
    Att_SHOURYUUREPPA, Att_PL08_HEALING,
};

const u8 tenguiwa_stage_data[16][4] = {
    { 0, 1, 0, 0 }, { 4, 5, 4, 5 }, { 0, 1, 0, 1 }, { 0, 1, 0, 1 },
    { 4, 5, 4, 5 }, { 0, 1, 0, 1 }, { 0, 1, 0, 1 }, { 0, 1, 0, 1 },
    { 2, 3, 2, 3 }, { 2, 3, 2, 3 }, { 0, 1, 0, 1 }, { 0, 1, 0, 1 },
    { 4, 5, 4, 5 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 },
};

const u8 tenguiwa_stand_by[6][8] = {
    { 24, 25, 26, 27, 28, 29, 30, 31 },
    { 32, 33, 34, 35, 24, 25, 26, 27 },
    { 24, 25, 26, 27, 28, 29, 30, 31 },
    { 29, 31, 34, 35, 24, 25, 26, 27 },
    { 24, 31, 26, 32, 33, 29, 30, 31 },
    { 32, 33, 29, 30, 24, 31, 26, 27 },
};

const s16 tenguiwa_pos_hosei[4][6] = {
    { 8, 112, 2, 16, 56, 48 }, { 48, 104, -2, 48, 48, 96 },
    { -48, 100, 2, -32, 48, 144 }, { -8, 96, -2, 0, 24, 192 },
};

const u8 tenguiwa_type_flag[32] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
