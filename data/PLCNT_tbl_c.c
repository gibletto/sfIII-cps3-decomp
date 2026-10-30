/*
 * PLCNT_TBL_C.C  stun recovery rates and stun times
 *
 * pl_nr_piyo_tbl gives each character's stun recovery rate; read by PLCNTSET_2.C. The
 * tsuujyou_dageki_*, hissatsu_dageki_*, tsuujyou_nage_*, hissatsu_nage_*, super_arts_dageki_*
 * and super_arts_nage_* tables are the stun times after normal strikes, special-move strikes,
 * throws, special-move throws, super art strikes and super art throws at three settings, 16
 * random choices each; reached through the kizetsu_timer_table lists of PLPDM.C, the player
 * damage process.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s32 pl_nr_piyo_tbl[];
extern const s16 tsuujyou_dageki_00[];
extern const s16 tsuujyou_dageki_01[];
extern const s16 tsuujyou_dageki_02[];
extern const s16 hissatsu_dageki_00[];
extern const s16 hissatsu_dageki_01[];
extern const s16 hissatsu_dageki_02[];
extern const s16 tsuujyou_nage_00[];
extern const s16 tsuujyou_nage_01[];
extern const s16 tsuujyou_nage_02[];
extern const s16 hissatsu_nage_00[];
extern const s16 hissatsu_nage_01[];
extern const s16 hissatsu_nage_02[];
extern const s16 super_arts_dageki_00[];
extern const s16 super_arts_dageki_01[];
extern const s16 super_arts_dageki_02[];
extern const s16 super_arts_nage_00[];
extern const s16 super_arts_nage_01[];
extern const s16 super_arts_nage_02[];

const s32 pl_nr_piyo_tbl[16] = {
    2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730, 2730,
};

const s16 tsuujyou_dageki_00[16] = {
    150, 150, 130, 130, 130, 110, 110, 110, 110, 110, 90, 90, 90, 90, 90, 90,
};

const s16 tsuujyou_dageki_01[16] = {
    150, 150, 150, 150, 130, 130, 130, 130, 110, 110, 110, 110, 90, 90, 90, 90,
};

const s16 tsuujyou_dageki_02[16] = {
    150, 150, 150, 150, 150, 150, 130, 130, 130, 130, 130, 110, 110, 110, 90, 90,
};

const s16 hissatsu_dageki_00[16] = {
    210, 210, 190, 190, 190, 170, 170, 170, 170, 170, 150, 150, 150, 150, 150, 150,
};

const s16 hissatsu_dageki_01[16] = {
    210, 210, 210, 210, 190, 190, 190, 190, 170, 170, 170, 170, 150, 150, 150, 150,
};

const s16 hissatsu_dageki_02[16] = {
    210, 210, 210, 210, 210, 210, 190, 190, 190, 190, 190, 170, 170, 170, 150, 150,
};

const s16 tsuujyou_nage_00[16] = {
    180, 180, 160, 160, 160, 140, 140, 140, 140, 140, 120, 120, 120, 120, 120, 120,
};

const s16 tsuujyou_nage_01[16] = {
    180, 180, 180, 180, 160, 160, 160, 160, 140, 140, 140, 140, 120, 120, 120, 120,
};

const s16 tsuujyou_nage_02[16] = {
    180, 180, 180, 180, 180, 180, 160, 160, 160, 160, 160, 140, 140, 140, 120, 120,
};

const s16 hissatsu_nage_00[16] = {
    240, 240, 200, 200, 200, 160, 160, 160, 160, 160, 120, 120, 120, 120, 120, 120,
};

const s16 hissatsu_nage_01[16] = {
    240, 240, 240, 240, 200, 200, 200, 200, 160, 160, 160, 160, 120, 120, 120, 120,
};

const s16 hissatsu_nage_02[16] = {
    240, 240, 240, 240, 240, 240, 200, 200, 200, 200, 200, 160, 160, 160, 120, 120,
};

const s16 super_arts_dageki_00[16] = {
    240, 240, 200, 200, 200, 160, 160, 160, 160, 160, 120, 120, 120, 120, 120, 120,
};

const s16 super_arts_dageki_01[16] = {
    240, 240, 240, 240, 200, 200, 200, 200, 160, 160, 160, 160, 120, 120, 120, 120,
};

const s16 super_arts_dageki_02[16] = {
    240, 240, 240, 240, 240, 240, 200, 200, 200, 200, 200, 160, 160, 160, 120, 120,
};

const s16 super_arts_nage_00[16] = {
    270, 270, 230, 230, 230, 190, 190, 190, 190, 190, 150, 150, 150, 150, 150, 150,
};

const s16 super_arts_nage_01[16] = {
    270, 270, 270, 270, 230, 230, 230, 230, 190, 190, 190, 190, 150, 150, 150, 150,
};

const s16 super_arts_nage_02[16] = {
    270, 270, 270, 270, 270, 270, 230, 230, 230, 230, 230, 190, 190, 190, 150, 150,
};
