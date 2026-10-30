/*
 * EFFF9_MES.C  ending message tables
 *
 * The per-player ending message tables of effect F9 in each language (EFFF9.c), and txt_no_tbl: per player, the
 * table of scene lists (EFFF8.c's lists of message number and frames) of each ending scene: initialised work RAM
 * (section D).
 */

#include "types.h"
#include "structs.h"

extern const EFFF9_MESSAGE* effF9_mes_jp[];
extern const EFFF9_MESSAGE* effF9_mes_en[];
extern const EFFF9_MESSAGE* effF9_mes_es[];
extern const EFFF9_MESSAGE* effF9_mes_pt[];
extern const u16* txt_no_00[];
extern const u16* txt_no_02[];
extern const u16* txt_no_03[];
extern const u16* txt_no_10[];
extern const u16* txt_no_04[];
extern const u16* txt_no_05[];
extern const u16* txt_no_07[];
extern const u16* txt_no_08[];
extern const u16* txt_no_09[];
extern const u16* txt_no_11[];
extern const u16* txt_no_12[];
extern const u16** txt_no_tbl[];
extern const EFFF9_MESSAGE effF9_mes_en_0[];
extern const EFFF9_MESSAGE effF9_mes_en_11[];
extern const EFFF9_MESSAGE effF9_mes_en_12[];
extern const EFFF9_MESSAGE effF9_mes_en_2[];
extern const EFFF9_MESSAGE effF9_mes_en_3[];
extern const EFFF9_MESSAGE effF9_mes_en_4[];
extern const EFFF9_MESSAGE effF9_mes_en_5[];
extern const EFFF9_MESSAGE effF9_mes_en_7[];
extern const EFFF9_MESSAGE effF9_mes_en_8[];
extern const EFFF9_MESSAGE effF9_mes_en_9[];
extern const EFFF9_MESSAGE effF9_mes_es_0[];
extern const EFFF9_MESSAGE effF9_mes_es_11[];
extern const EFFF9_MESSAGE effF9_mes_es_12[];
extern const EFFF9_MESSAGE effF9_mes_es_2[];
extern const EFFF9_MESSAGE effF9_mes_es_3[];
extern const EFFF9_MESSAGE effF9_mes_es_4[];
extern const EFFF9_MESSAGE effF9_mes_es_5[];
extern const EFFF9_MESSAGE effF9_mes_es_7[];
extern const EFFF9_MESSAGE effF9_mes_es_8[];
extern const EFFF9_MESSAGE effF9_mes_es_9[];
extern const EFFF9_MESSAGE effF9_mes_jp_0[];
extern const EFFF9_MESSAGE effF9_mes_jp_11[];
extern const EFFF9_MESSAGE effF9_mes_jp_12[];
extern const EFFF9_MESSAGE effF9_mes_jp_2[];
extern const EFFF9_MESSAGE effF9_mes_jp_3[];
extern const EFFF9_MESSAGE effF9_mes_jp_4[];
extern const EFFF9_MESSAGE effF9_mes_jp_5[];
extern const EFFF9_MESSAGE effF9_mes_jp_7[];
extern const EFFF9_MESSAGE effF9_mes_jp_8[];
extern const EFFF9_MESSAGE effF9_mes_jp_9[];
extern const EFFF9_MESSAGE effF9_mes_pt_0[];
extern const EFFF9_MESSAGE effF9_mes_pt_11[];
extern const EFFF9_MESSAGE effF9_mes_pt_12[];
extern const EFFF9_MESSAGE effF9_mes_pt_2[];
extern const EFFF9_MESSAGE effF9_mes_pt_3[];
extern const EFFF9_MESSAGE effF9_mes_pt_4[];
extern const EFFF9_MESSAGE effF9_mes_pt_5[];
extern const EFFF9_MESSAGE effF9_mes_pt_7[];
extern const EFFF9_MESSAGE effF9_mes_pt_8[];
extern const EFFF9_MESSAGE effF9_mes_pt_9[];
extern const u16 plXXtxt0[];
extern const u16 txt_no_00_1[];
extern const u16 txt_no_00_2[];
extern const u16 txt_no_00_3[];
extern const u16 txt_no_00_4[];
extern const u16 txt_no_00_5[];
extern const u16 txt_no_00_6[];
extern const u16 txt_no_00_7[];
extern const u16 txt_no_00_8[];
extern const u16 txt_no_02_1[];
extern const u16 txt_no_02_2[];
extern const u16 txt_no_02_3[];
extern const u16 txt_no_02_4[];
extern const u16 txt_no_03_1[];
extern const u16 txt_no_03_2[];
extern const u16 txt_no_03_3[];
extern const u16 txt_no_03_4[];
extern const u16 txt_no_03_5[];
extern const u16 txt_no_03_6[];
extern const u16 txt_no_03_7[];
extern const u16 txt_no_03_8[];
extern const u16 txt_no_03_9[];
extern const u16 txt_no_04_1[];
extern const u16 txt_no_04_2[];
extern const u16 txt_no_04_3[];
extern const u16 txt_no_04_4[];
extern const u16 txt_no_04_5[];
extern const u16 txt_no_05_1[];
extern const u16 txt_no_05_2[];
extern const u16 txt_no_05_3[];
extern const u16 txt_no_05_4[];
extern const u16 txt_no_05_5[];
extern const u16 txt_no_05_6[];
extern const u16 txt_no_07_10[];
extern const u16 txt_no_07_1[];
extern const u16 txt_no_07_2[];
extern const u16 txt_no_07_3[];
extern const u16 txt_no_07_4[];
extern const u16 txt_no_07_5[];
extern const u16 txt_no_07_6[];
extern const u16 txt_no_07_7[];
extern const u16 txt_no_07_8[];
extern const u16 txt_no_07_9[];
extern const u16 txt_no_08_1[];
extern const u16 txt_no_08_2[];
extern const u16 txt_no_08_3[];
extern const u16 txt_no_08_4[];
extern const u16 txt_no_09_1[];
extern const u16 txt_no_09_2[];
extern const u16 txt_no_09_3[];
extern const u16 txt_no_09_4[];
extern const u16 txt_no_09_5[];
extern const u16 txt_no_11_1[];
extern const u16 txt_no_11_2[];
extern const u16 txt_no_11_3[];
extern const u16 txt_no_11_4[];
extern const u16 txt_no_11_5[];
extern const u16 txt_no_11_6[];
extern const u16 txt_no_12_1[];
extern const u16 txt_no_12_2[];
extern const u16 txt_no_12_3[];
extern const u16 txt_no_12_4[];
extern const u16 txt_no_12_5[];

/* 02006E88 */
const EFFF9_MESSAGE* effF9_mes_jp[13] = {
    effF9_mes_jp_0, effF9_mes_jp_0,
    effF9_mes_jp_2, effF9_mes_jp_3,
    effF9_mes_jp_4, effF9_mes_jp_5,
    effF9_mes_jp_0, effF9_mes_jp_7,
    effF9_mes_jp_8, effF9_mes_jp_9,
    effF9_mes_jp_3, effF9_mes_jp_11,
    effF9_mes_jp_12,
};

/* 02006EBC */
const EFFF9_MESSAGE* effF9_mes_en[13] = {
    effF9_mes_en_0, effF9_mes_en_0,
    effF9_mes_en_2, effF9_mes_en_3,
    effF9_mes_en_4, effF9_mes_en_5,
    effF9_mes_en_0, effF9_mes_en_7,
    effF9_mes_en_8, effF9_mes_en_9,
    effF9_mes_en_3, effF9_mes_en_11,
    effF9_mes_en_12,
};

/* 02006EF0 */
const EFFF9_MESSAGE* effF9_mes_es[13] = {
    effF9_mes_es_0, effF9_mes_es_0,
    effF9_mes_es_2, effF9_mes_es_3,
    effF9_mes_es_4, effF9_mes_es_5,
    effF9_mes_es_0, effF9_mes_es_7,
    effF9_mes_es_8, effF9_mes_es_9,
    effF9_mes_es_3, effF9_mes_es_11,
    effF9_mes_es_12,
};

/* 02006F24 */
const EFFF9_MESSAGE* effF9_mes_pt[13] = {
    effF9_mes_pt_0, effF9_mes_pt_0,
    effF9_mes_pt_2, effF9_mes_pt_3,
    effF9_mes_pt_4, effF9_mes_pt_5,
    effF9_mes_pt_0, effF9_mes_pt_7,
    effF9_mes_pt_8, effF9_mes_pt_9,
    effF9_mes_pt_3, effF9_mes_pt_11,
    effF9_mes_pt_12,
};

/* 02006F58 */
/* provisional name */
const u16* txt_no_00[9] = {
    plXXtxt0, txt_no_00_1,
    txt_no_00_2, txt_no_00_3,
    txt_no_00_4, txt_no_00_5,
    txt_no_00_6, txt_no_00_7,
    txt_no_00_8,
};

/* 02006F7C */
/* provisional name */
const u16* txt_no_02[5] = {
    plXXtxt0, txt_no_02_1,
    txt_no_02_2, txt_no_02_3,
    txt_no_02_4,
};

/* 02006F90 */
/* provisional name */
const u16* txt_no_03[10] = {
    plXXtxt0, txt_no_03_1,
    txt_no_03_2, txt_no_03_3,
    txt_no_03_4, txt_no_03_5,
    txt_no_03_6, txt_no_03_7,
    txt_no_03_8, txt_no_03_9,
};

/* 02006FB8 */
/* provisional name */
const u16* txt_no_10[10] = {
    plXXtxt0, txt_no_03_2,
    txt_no_03_1, txt_no_03_3,
    txt_no_03_4, txt_no_03_5,
    txt_no_03_7, txt_no_03_6,
    txt_no_03_8, txt_no_03_9,
};

/* 02006FE0 */
/* provisional name */
const u16* txt_no_04[6] = {
    plXXtxt0, txt_no_04_1,
    txt_no_04_2, txt_no_04_3,
    txt_no_04_4, txt_no_04_5,
};

/* 02006FF8 */
/* provisional name */
const u16* txt_no_05[7] = {
    plXXtxt0, txt_no_05_1,
    txt_no_05_2, txt_no_05_3,
    txt_no_05_4, txt_no_05_5,
    txt_no_05_6,
};

/* 02007014 */
/* provisional name */
const u16* txt_no_07[11] = {
    plXXtxt0, txt_no_07_1,
    txt_no_07_2, txt_no_07_3,
    txt_no_07_4, txt_no_07_5,
    txt_no_07_6, txt_no_07_7,
    txt_no_07_8, txt_no_07_9,
    txt_no_07_10,
};

/* 02007040 */
/* provisional name */
const u16* txt_no_08[5] = {
    plXXtxt0, txt_no_08_1,
    txt_no_08_2, txt_no_08_3,
    txt_no_08_4,
};

/* 02007054 */
/* provisional name */
const u16* txt_no_09[6] = {
    plXXtxt0, txt_no_09_1,
    txt_no_09_2, txt_no_09_3,
    txt_no_09_4, txt_no_09_5,
};

/* 0200706C */
/* provisional name */
const u16* txt_no_11[7] = {
    plXXtxt0, txt_no_11_1,
    txt_no_11_2, txt_no_11_3,
    txt_no_11_4, txt_no_11_5,
    txt_no_11_6,
};

/* 02007088 */
/* provisional name */
const u16* txt_no_12[6] = {
    plXXtxt0, txt_no_12_1,
    txt_no_12_2, txt_no_12_3,
    txt_no_12_4, txt_no_12_5,
};

/* 020070A0 */
const u16** txt_no_tbl[13] = {
    txt_no_00, txt_no_00, txt_no_02, txt_no_03,
    txt_no_04, txt_no_05, txt_no_00, txt_no_07,
    txt_no_08, txt_no_09, txt_no_10, txt_no_11,
    txt_no_12,
};
