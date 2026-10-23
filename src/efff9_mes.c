/*
 * EFFF9_MES.C  ending message tables
 *
 * The per-player ending message tables of effect F9 in each language (EFFF9.c), and txt_no_tbl: per player, the
 * table of scene lists (EFFF8.c's lists of message number and frames) of each ending scene: initialised work RAM
 * (section D).
 */

#include "types.h"
#include "structs.h"

extern EFFF9_MESSAGE * effF9_mes_jp[];
extern EFFF9_MESSAGE * effF9_mes_en[];
extern EFFF9_MESSAGE * effF9_mes_es[];
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
extern const u16 efff9_no_scene[];
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
EFFF9_MESSAGE* effF9_mes_jp[13] = {
    (EFFF9_MESSAGE *)effF9_mes_jp_0, (EFFF9_MESSAGE *)effF9_mes_jp_0,
    (EFFF9_MESSAGE *)effF9_mes_jp_2, (EFFF9_MESSAGE *)effF9_mes_jp_3,
    (EFFF9_MESSAGE *)effF9_mes_jp_4, (EFFF9_MESSAGE *)effF9_mes_jp_5,
    (EFFF9_MESSAGE *)effF9_mes_jp_0, (EFFF9_MESSAGE *)effF9_mes_jp_7,
    (EFFF9_MESSAGE *)effF9_mes_jp_8, (EFFF9_MESSAGE *)effF9_mes_jp_9,
    (EFFF9_MESSAGE *)effF9_mes_jp_3, (EFFF9_MESSAGE *)effF9_mes_jp_11,
    (EFFF9_MESSAGE *)effF9_mes_jp_12,
};

/* 02006EBC */
EFFF9_MESSAGE* effF9_mes_en[13] = {
    (EFFF9_MESSAGE *)effF9_mes_en_0, (EFFF9_MESSAGE *)effF9_mes_en_0,
    (EFFF9_MESSAGE *)effF9_mes_en_2, (EFFF9_MESSAGE *)effF9_mes_en_3,
    (EFFF9_MESSAGE *)effF9_mes_en_4, (EFFF9_MESSAGE *)effF9_mes_en_5,
    (EFFF9_MESSAGE *)effF9_mes_en_0, (EFFF9_MESSAGE *)effF9_mes_en_7,
    (EFFF9_MESSAGE *)effF9_mes_en_8, (EFFF9_MESSAGE *)effF9_mes_en_9,
    (EFFF9_MESSAGE *)effF9_mes_en_3, (EFFF9_MESSAGE *)effF9_mes_en_11,
    (EFFF9_MESSAGE *)effF9_mes_en_12,
};

/* 02006EF0 */
EFFF9_MESSAGE* effF9_mes_es[13] = {
    (EFFF9_MESSAGE *)effF9_mes_es_0, (EFFF9_MESSAGE *)effF9_mes_es_0,
    (EFFF9_MESSAGE *)effF9_mes_es_2, (EFFF9_MESSAGE *)effF9_mes_es_3,
    (EFFF9_MESSAGE *)effF9_mes_es_4, (EFFF9_MESSAGE *)effF9_mes_es_5,
    (EFFF9_MESSAGE *)effF9_mes_es_0, (EFFF9_MESSAGE *)effF9_mes_es_7,
    (EFFF9_MESSAGE *)effF9_mes_es_8, (EFFF9_MESSAGE *)effF9_mes_es_9,
    (EFFF9_MESSAGE *)effF9_mes_es_3, (EFFF9_MESSAGE *)effF9_mes_es_11,
    (EFFF9_MESSAGE *)effF9_mes_es_12,
};

/* 02006F24 */
const EFFF9_MESSAGE* effF9_mes_pt[13] = {
    (const EFFF9_MESSAGE *)effF9_mes_pt_0, (const EFFF9_MESSAGE *)effF9_mes_pt_0,
    (const EFFF9_MESSAGE *)effF9_mes_pt_2, (const EFFF9_MESSAGE *)effF9_mes_pt_3,
    (const EFFF9_MESSAGE *)effF9_mes_pt_4, (const EFFF9_MESSAGE *)effF9_mes_pt_5,
    (const EFFF9_MESSAGE *)effF9_mes_pt_0, (const EFFF9_MESSAGE *)effF9_mes_pt_7,
    (const EFFF9_MESSAGE *)effF9_mes_pt_8, (const EFFF9_MESSAGE *)effF9_mes_pt_9,
    (const EFFF9_MESSAGE *)effF9_mes_pt_3, (const EFFF9_MESSAGE *)effF9_mes_pt_11,
    (const EFFF9_MESSAGE *)effF9_mes_pt_12,
};

/* 02006F58 */
/* provisional name */
const u16* txt_no_00[9] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_00_1,
    (const u16 *)txt_no_00_2, (const u16 *)txt_no_00_3,
    (const u16 *)txt_no_00_4, (const u16 *)txt_no_00_5,
    (const u16 *)txt_no_00_6, (const u16 *)txt_no_00_7,
    (const u16 *)txt_no_00_8,
};

/* 02006F7C */
/* provisional name */
const u16* txt_no_02[5] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_02_1,
    (const u16 *)txt_no_02_2, (const u16 *)txt_no_02_3,
    (const u16 *)txt_no_02_4,
};

/* 02006F90 */
/* provisional name */
const u16* txt_no_03[10] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_03_1,
    (const u16 *)txt_no_03_2, (const u16 *)txt_no_03_3,
    (const u16 *)txt_no_03_4, (const u16 *)txt_no_03_5,
    (const u16 *)txt_no_03_6, (const u16 *)txt_no_03_7,
    (const u16 *)txt_no_03_8, (const u16 *)txt_no_03_9,
};

/* 02006FB8 */
/* provisional name */
const u16* txt_no_10[10] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_03_2,
    (const u16 *)txt_no_03_1, (const u16 *)txt_no_03_3,
    (const u16 *)txt_no_03_4, (const u16 *)txt_no_03_5,
    (const u16 *)txt_no_03_7, (const u16 *)txt_no_03_6,
    (const u16 *)txt_no_03_8, (const u16 *)txt_no_03_9,
};

/* 02006FE0 */
/* provisional name */
const u16* txt_no_04[6] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_04_1,
    (const u16 *)txt_no_04_2, (const u16 *)txt_no_04_3,
    (const u16 *)txt_no_04_4, (const u16 *)txt_no_04_5,
};

/* 02006FF8 */
/* provisional name */
const u16* txt_no_05[7] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_05_1,
    (const u16 *)txt_no_05_2, (const u16 *)txt_no_05_3,
    (const u16 *)txt_no_05_4, (const u16 *)txt_no_05_5,
    (const u16 *)txt_no_05_6,
};

/* 02007014 */
/* provisional name */
const u16* txt_no_07[11] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_07_1,
    (const u16 *)txt_no_07_2, (const u16 *)txt_no_07_3,
    (const u16 *)txt_no_07_4, (const u16 *)txt_no_07_5,
    (const u16 *)txt_no_07_6, (const u16 *)txt_no_07_7,
    (const u16 *)txt_no_07_8, (const u16 *)txt_no_07_9,
    (const u16 *)txt_no_07_10,
};

/* 02007040 */
/* provisional name */
const u16* txt_no_08[5] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_08_1,
    (const u16 *)txt_no_08_2, (const u16 *)txt_no_08_3,
    (const u16 *)txt_no_08_4,
};

/* 02007054 */
/* provisional name */
const u16* txt_no_09[6] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_09_1,
    (const u16 *)txt_no_09_2, (const u16 *)txt_no_09_3,
    (const u16 *)txt_no_09_4, (const u16 *)txt_no_09_5,
};

/* 0200706C */
/* provisional name */
const u16* txt_no_11[7] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_11_1,
    (const u16 *)txt_no_11_2, (const u16 *)txt_no_11_3,
    (const u16 *)txt_no_11_4, (const u16 *)txt_no_11_5,
    (const u16 *)txt_no_11_6,
};

/* 02007088 */
/* provisional name */
const u16* txt_no_12[6] = {
    (const u16 *)efff9_no_scene, (const u16 *)txt_no_12_1,
    (const u16 *)txt_no_12_2, (const u16 *)txt_no_12_3,
    (const u16 *)txt_no_12_4, (const u16 *)txt_no_12_5,
};

/* 020070A0 */
const u16** txt_no_tbl[13] = {
    (const u16 **)txt_no_00, (const u16 **)txt_no_00, (const u16 **)txt_no_02, (const u16 **)txt_no_03,
    (const u16 **)txt_no_04, (const u16 **)txt_no_05, (const u16 **)txt_no_00, (const u16 **)txt_no_07,
    (const u16 **)txt_no_08, (const u16 **)txt_no_09, (const u16 **)txt_no_10, (const u16 **)txt_no_11,
    (const u16 **)txt_no_12,
};
