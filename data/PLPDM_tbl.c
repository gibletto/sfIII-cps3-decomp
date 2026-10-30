/*
 * PLPDM_TBL.C  player damage tables
 *
 * plpdm_lv_00 lists the damage routines Damage_00000 - Damage_29000. dm_reaction_table holds
 * the reaction data (routine, animation and data index) of each of the 111 damage codes, and
 * dd_convert changes a damage code by attack level when the hit is a KO. hok_table gives the
 * extra animation steps per frame of a stunned player by lever and button mashing,
 * sky_dm_zuru_ix and sky_dm_zuru_table the zuru_timer set on each air hit, oki_select_table2
 * the get-up routine after a recovery roll, tama_select the projectile hit count by projectile
 * type, and exdm_ix_data the per-character placement data of the special damage set against
 * the attacker. Read by PLPDM.C; guard_kind (guard kind per guard routine) also by PLPNM.C,
 * and atsagct (KO voice choice per damage routine) by PLS02.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 hok_table[];
extern const s16 oki_select_table2[];
extern const s16 sky_dm_zuru_table[];
extern const s16 sky_dm_zuru_ix[];
extern const s8 tama_select[];
extern const AS_ROW8 dm_reaction_table[];
extern const s16 dd_convert[][4];
extern const u8 guard_kind[];
extern const u8 guard_kind_tail[];
extern void (*const plpdm_lv_00[])(PLW* wk);
extern const s8 atsagct[];
extern const s16 exdm_ix_data[][16][5];
extern void Damage_00000();
extern void Damage_01000();
extern void Damage_04000();
extern void Damage_07000();
extern void Damage_08000();
extern void Damage_12000();
extern void Damage_14000();
extern void Damage_16000();
extern void Damage_17000();
extern void Damage_18000();
extern void Damage_19000();
extern void Damage_20000();
extern void Damage_21000();
extern void Damage_23000();
extern void Damage_24000();
extern void Damage_25000();
extern void Damage_26000();
extern void Damage_27000();
extern void Damage_28000();
extern void Damage_29000();

const s16 hok_table[8] = {
    1, 2, 3, 3, 4, 4, 5, 5,
};

const s16 oki_select_table2[4] = {
    13, 12, 12, 13,
};

const s16 sky_dm_zuru_table[16] = {
    0, 241, 201, 161, 121, 81, 41, 21, 9, 3, 1, 1, 1, 1, 1, 1,
};

const s16 sky_dm_zuru_ix[8] = {
    1, 3, 7, 15, 15, 15, 15, 15,
};

const s8 tama_select[82] = {
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3, 3, 3, 3, 1, 1, 1, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    1, 112,
};

const AS_ROW8 dm_reaction_table[111] = {
    { { 0, 0, 0 }, 0 }, { { 1, 64, 0 }, 1 }, { { 2, 64, 15 }, 1 }, { { 3, 64, 16 }, 1 },
    { { 4, 0, 0 }, 1 }, { { 5, 1, 0 }, 1 }, { { 6, 2, 0 }, 9 }, { { 7, 3, 0 }, 1 },
    { { 8, 4, 17 }, 1 }, { { 9, 5, 17 }, 1 }, { { 10, 6, 18 }, 1 }, { { 11, 7, 0 }, 1 },
    { { 2, 71, 19 }, 1 }, { { 3, 72, 20 }, 1 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 67, 0 }, 1 }, { { 24, 68, 0 }, 1 }, { { 24, 69, 0 }, 1 }, { { 25, 70, 0 }, 1 },
    { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 },
    { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 },
    { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 }, { { 25, 70, 0 }, 1 },
    { { 12, 8, 0 }, 1 }, { { 12, 12, 0 }, 1 }, { { 12, 16, 0 }, 1 }, { { 12, 20, 0 }, 1 },
    { { 12, 24, 0 }, 1 }, { { 12, 28, 0 }, 1 }, { { 12, 32, 0 }, 1 }, { { 14, 36, 0 }, 1 },
    { { 21, 40, 0 }, 1 }, { { 12, 44, 0 }, 1 }, { { 12, 92, 0 }, 1 }, { { 12, 82, 0 }, 1 },
    { { 12, 74, 0 }, 1 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 13, 48, 0 }, 9 }, { { 15, 52, 0 }, 9 }, { { 22, 56, 0 }, 9 }, { { 13, 48, 0 }, 1 },
    { { 13, 86, 0 }, 1 }, { { 13, 78, 0 }, 1 }, { { 27, 60, 0 }, 1 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 }, { { 0, 0, 0 }, 0 },
    { { 17, 0, 0 }, 1 }, { { 16, 4, 0 }, 1 }, { { 18, 8, 0 }, 1 }, { { 18, 32, 0 }, 1 },
    { { 18, 12, 0 }, 1 }, { { 19, 16, 0 }, 1 }, { { 19, 20, 0 }, 1 }, { { 18, 24, 0 }, 1 },
    { { 18, 28, 0 }, 1 }, { { 20, 36, 0 }, 1 }, { { 23, 40, 0 }, 1 }, { { 26, 44, 0 }, 1 },
    { { 18, 48, 0 }, 1 }, { { 18, 52, 0 }, 1 }, { { 18, 56, 0 }, 1 }, { { 18, 32, 0 }, 1 },
    { { 18, 60, 0 }, 1 }, { { 18, 76, 0 }, 1 }, { { 18, 64, 0 }, 1 }, { { 18, 68, 0 }, 1 },
    { { 28, 72, 0 }, 1 }, { { 29, 32, 18 }, 1 }, { { 29, 36, 20 }, 1 },
};

const s16 dd_convert[111][4] = {
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 16, 16, 16, 16 }, { 17, 17, 17, 17 }, { 18, 18, 18, 18 }, { 91, 91, 91, 91 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 17, 100, 100, 100 }, { 17, 100, 100, 100 }, { 17, 100, 94, 94 }, { 17, 100, 95, 95 },
    { 17, 36, 36, 36 }, { 17, 91, 91, 91 }, { 17, 96, 96, 96 }, { 17, 39, 39, 39 },
    { 17, 40, 40, 40 }, { 17, 91, 91, 91 }, { 103, 103, 103, 103 }, { 104, 104, 104, 104 },
    { 105, 105, 105, 105 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 18, 91, 91, 91 }, { 18, 65, 65, 65 }, { 18, 66, 66, 66 }, { 103, 103, 103, 103 },
    { 104, 104, 104, 104 }, { 105, 105, 105, 105 }, { 70, 70, 70, 70 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
    { 91, 91, 91, 91 }, { 101, 101, 101, 101 }, { 102, 102, 102, 102 }, { 91, 91, 91, 91 },
    { 92, 92, 92, 92 }, { 93, 93, 93, 93 }, { 94, 94, 94, 94 }, { 95, 95, 95, 95 },
    { 96, 96, 96, 96 }, { 97, 97, 97, 97 }, { 98, 98, 98, 98 }, { 99, 99, 99, 99 },
    { 100, 100, 100, 100 }, { 101, 101, 101, 101 }, { 102, 102, 102, 102 }, { 103, 103, 103, 103 },
    { 104, 104, 104, 104 }, { 105, 105, 105, 105 }, { 106, 106, 106, 106 }, { 107, 107, 107, 107 },
    { 108, 108, 108, 108 }, { 109, 109, 109, 109 }, { 110, 110, 110, 110 },
};

const u8 guard_kind[12] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0,
};

/* Stored after guard_kind. Nothing in the program refers to it by name or address (provisional name). */
const u8 guard_kind_tail[2] = {
    0xBF, 0x3C,
};

void (*const plpdm_lv_00[30])(PLW* wk) = {
    Damage_00000, Damage_01000, Damage_01000, Damage_01000, Damage_04000, Damage_04000, Damage_04000, Damage_07000,
    Damage_08000, Damage_08000, Damage_08000, Damage_08000, Damage_12000, Damage_12000, Damage_14000, Damage_14000,
    Damage_16000, Damage_17000, Damage_18000, Damage_19000, Damage_20000, Damage_21000, Damage_21000, Damage_23000,
    Damage_24000, Damage_25000, Damage_26000, Damage_27000, Damage_28000, Damage_29000,
};

const s8 atsagct[30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 17, 0, 1, 1, 0, 1,
};

/* { x offset, y offset, flip, cg_olc_ix, cg_number } per damage kind and character */
const s16 exdm_ix_data[1][16][5] = {
    {
        { 76, 0, 1, 0, 0x167 }, { 60, 12, 1, 0, 0x4E9 },
        { 63, 13, 1, 0, 0x898 }, { 65, 2, 1, 0, 0xD39 },
        { 58, 3, 1, 0, 0x1105 }, { 46, 9, 1, 0, 0x15C4 },
        { 0, 0, 1, 0, 0x1800 }, { 40, 21, 1, 964, 0x1D32 },
        { 91, 21, 1, 0, 0x20BA }, { 64, 23, 1, 0, 0x2487 },
        { 65, 2, 1, 0, 0x2939 }, { 63, 13, 1, 0, 0x2C98 },
        { 63, 13, 1, 0, 0x3098 }, { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 },
    },
};
