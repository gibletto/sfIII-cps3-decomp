/*
 * EFFB8_MES.C  message tables of effect B8
 *
 * The per-player message tables of effect B8 in each language and its panel table (EFFB8.c), after a scroll object
 * table nothing reads: initialised work RAM (section D).
 */

#include "types.h"
#include "structs.h"

extern const s16* scr_obj_data_unref[][4];
extern EFFB8_MESSAGE * effB8_mes_jp[];
extern EFFB8_MESSAGE * effB8_mes_en[];
extern EFFB8_MESSAGE * effB8_mes_es[];
extern EFFB8_MESSAGE * effB8_mes_pt[];
extern EFFB8_MESSAGE* effB8_conn_tbl[];
extern const EFFB8_MESSAGE effB8_conn_0[];
extern const EFFB8_MESSAGE effB8_conn_10[];
extern const EFFB8_MESSAGE effB8_conn_11[];
extern const EFFB8_MESSAGE effB8_conn_12[];
extern const EFFB8_MESSAGE effB8_conn_1[];
extern const EFFB8_MESSAGE effB8_conn_2[];
extern const EFFB8_MESSAGE effB8_conn_3[];
extern const EFFB8_MESSAGE effB8_conn_4[];
extern const EFFB8_MESSAGE effB8_conn_5[];
extern const EFFB8_MESSAGE effB8_conn_7[];
extern const EFFB8_MESSAGE effB8_conn_8[];
extern const EFFB8_MESSAGE effB8_conn_9[];
extern const EFFB8_MESSAGE effB8_mes_en_0[];
extern const EFFB8_MESSAGE effB8_mes_en_10[];
extern const EFFB8_MESSAGE effB8_mes_en_11[];
extern const EFFB8_MESSAGE effB8_mes_en_12[];
extern const EFFB8_MESSAGE effB8_mes_en_1[];
extern const EFFB8_MESSAGE effB8_mes_en_2[];
extern const EFFB8_MESSAGE effB8_mes_en_3[];
extern const EFFB8_MESSAGE effB8_mes_en_4[];
extern const EFFB8_MESSAGE effB8_mes_en_5[];
extern const EFFB8_MESSAGE effB8_mes_en_7[];
extern const EFFB8_MESSAGE effB8_mes_en_8[];
extern const EFFB8_MESSAGE effB8_mes_en_9[];
extern const EFFB8_MESSAGE effB8_mes_es_0[];
extern const EFFB8_MESSAGE effB8_mes_es_10[];
extern const EFFB8_MESSAGE effB8_mes_es_11[];
extern const EFFB8_MESSAGE effB8_mes_es_12[];
extern const EFFB8_MESSAGE effB8_mes_es_1[];
extern const EFFB8_MESSAGE effB8_mes_es_2[];
extern const EFFB8_MESSAGE effB8_mes_es_3[];
extern const EFFB8_MESSAGE effB8_mes_es_4[];
extern const EFFB8_MESSAGE effB8_mes_es_5[];
extern const EFFB8_MESSAGE effB8_mes_es_7[];
extern const EFFB8_MESSAGE effB8_mes_es_8[];
extern const EFFB8_MESSAGE effB8_mes_es_9[];
extern const EFFB8_MESSAGE effB8_mes_jp_0[];
extern const EFFB8_MESSAGE effB8_mes_jp_10[];
extern const EFFB8_MESSAGE effB8_mes_jp_11[];
extern const EFFB8_MESSAGE effB8_mes_jp_12[];
extern const EFFB8_MESSAGE effB8_mes_jp_1[];
extern const EFFB8_MESSAGE effB8_mes_jp_2[];
extern const EFFB8_MESSAGE effB8_mes_jp_3[];
extern const EFFB8_MESSAGE effB8_mes_jp_4[];
extern const EFFB8_MESSAGE effB8_mes_jp_5[];
extern const EFFB8_MESSAGE effB8_mes_jp_7[];
extern const EFFB8_MESSAGE effB8_mes_jp_8[];
extern const EFFB8_MESSAGE effB8_mes_jp_9[];
extern const EFFB8_MESSAGE effB8_mes_pt_0[];
extern const EFFB8_MESSAGE effB8_mes_pt_10[];
extern const EFFB8_MESSAGE effB8_mes_pt_11[];
extern const EFFB8_MESSAGE effB8_mes_pt_12[];
extern const EFFB8_MESSAGE effB8_mes_pt_1[];
extern const EFFB8_MESSAGE effB8_mes_pt_2[];
extern const EFFB8_MESSAGE effB8_mes_pt_3[];
extern const EFFB8_MESSAGE effB8_mes_pt_4[];
extern const EFFB8_MESSAGE effB8_mes_pt_5[];
extern const EFFB8_MESSAGE effB8_mes_pt_7[];
extern const EFFB8_MESSAGE effB8_mes_pt_8[];
extern const EFFB8_MESSAGE effB8_mes_pt_9[];
extern const s16 scr_obj_unref_0[];
extern const s16 scr_obj_unref_1[];
extern const s16 scr_obj_unref_2[];
extern const s16 scr_obj_unref_3[];
extern const s16 scr_obj_unref_4[];
extern const s16 scr_obj_unref_5[];
extern const s16 scr_obj_unref_6[];

/* 02006D38 */
/* scroll object lists like scr_obj_data88's; nothing in the program refers to it (provisional name) */
const s16* scr_obj_data_unref[3][4] = {
    {
        (const s16 *)scr_obj_unref_0, (const s16 *)scr_obj_unref_1,
        (const s16 *)scr_obj_unref_2, (const s16 *)scr_obj_unref_3,
    },
    {
        (const s16 *)scr_obj_unref_4, (const s16 *)scr_obj_unref_4,
        (const s16 *)scr_obj_unref_5, (const s16 *)scr_obj_unref_5,
    },
    {
        (const s16 *)scr_obj_unref_6, (const s16 *)scr_obj_unref_6,
        (const s16 *)scr_obj_unref_6, (const s16 *)scr_obj_unref_6,
    },
};

/* 02006D68 */
EFFB8_MESSAGE* effB8_mes_jp[13] = {
    (EFFB8_MESSAGE *)effB8_mes_jp_0, (EFFB8_MESSAGE *)effB8_mes_jp_1,
    (EFFB8_MESSAGE *)effB8_mes_jp_2, (EFFB8_MESSAGE *)effB8_mes_jp_3,
    (EFFB8_MESSAGE *)effB8_mes_jp_4, (EFFB8_MESSAGE *)effB8_mes_jp_5,
    (EFFB8_MESSAGE *)effB8_mes_jp_0, (EFFB8_MESSAGE *)effB8_mes_jp_7,
    (EFFB8_MESSAGE *)effB8_mes_jp_8, (EFFB8_MESSAGE *)effB8_mes_jp_9,
    (EFFB8_MESSAGE *)effB8_mes_jp_10, (EFFB8_MESSAGE *)effB8_mes_jp_11,
    (EFFB8_MESSAGE *)effB8_mes_jp_12,
};

/* 02006D9C */
EFFB8_MESSAGE* effB8_mes_en[13] = {
    (EFFB8_MESSAGE *)effB8_mes_en_0, (EFFB8_MESSAGE *)effB8_mes_en_1,
    (EFFB8_MESSAGE *)effB8_mes_en_2, (EFFB8_MESSAGE *)effB8_mes_en_3,
    (EFFB8_MESSAGE *)effB8_mes_en_4, (EFFB8_MESSAGE *)effB8_mes_en_5,
    (EFFB8_MESSAGE *)effB8_mes_en_0, (EFFB8_MESSAGE *)effB8_mes_en_7,
    (EFFB8_MESSAGE *)effB8_mes_en_8, (EFFB8_MESSAGE *)effB8_mes_en_9,
    (EFFB8_MESSAGE *)effB8_mes_en_10, (EFFB8_MESSAGE *)effB8_mes_en_11,
    (EFFB8_MESSAGE *)effB8_mes_en_12,
};

/* 02006DD0 */
EFFB8_MESSAGE* effB8_mes_es[13] = {
    (EFFB8_MESSAGE *)effB8_mes_es_0, (EFFB8_MESSAGE *)effB8_mes_es_1,
    (EFFB8_MESSAGE *)effB8_mes_es_2, (EFFB8_MESSAGE *)effB8_mes_es_3,
    (EFFB8_MESSAGE *)effB8_mes_es_4, (EFFB8_MESSAGE *)effB8_mes_es_5,
    (EFFB8_MESSAGE *)effB8_mes_es_0, (EFFB8_MESSAGE *)effB8_mes_es_7,
    (EFFB8_MESSAGE *)effB8_mes_es_8, (EFFB8_MESSAGE *)effB8_mes_es_9,
    (EFFB8_MESSAGE *)effB8_mes_es_10, (EFFB8_MESSAGE *)effB8_mes_es_11,
    (EFFB8_MESSAGE *)effB8_mes_es_12,
};

/* 02006E04 */
EFFB8_MESSAGE* effB8_mes_pt[13] = {
    (EFFB8_MESSAGE *)effB8_mes_pt_0, (EFFB8_MESSAGE *)effB8_mes_pt_1,
    (EFFB8_MESSAGE *)effB8_mes_pt_2, (EFFB8_MESSAGE *)effB8_mes_pt_3,
    (EFFB8_MESSAGE *)effB8_mes_pt_4, (EFFB8_MESSAGE *)effB8_mes_pt_5,
    (EFFB8_MESSAGE *)effB8_mes_pt_0, (EFFB8_MESSAGE *)effB8_mes_pt_7,
    (EFFB8_MESSAGE *)effB8_mes_pt_8, (EFFB8_MESSAGE *)effB8_mes_pt_9,
    (EFFB8_MESSAGE *)effB8_mes_pt_10, (EFFB8_MESSAGE *)effB8_mes_pt_11,
    (EFFB8_MESSAGE *)effB8_mes_pt_12,
};

/* 02006E38 */
EFFB8_MESSAGE* effB8_conn_tbl[13] = {
    (EFFB8_MESSAGE *)effB8_conn_0, (EFFB8_MESSAGE *)effB8_conn_1,
    (EFFB8_MESSAGE *)effB8_conn_2, (EFFB8_MESSAGE *)effB8_conn_3,
    (EFFB8_MESSAGE *)effB8_conn_4, (EFFB8_MESSAGE *)effB8_conn_5,
    (EFFB8_MESSAGE *)effB8_conn_0, (EFFB8_MESSAGE *)effB8_conn_7,
    (EFFB8_MESSAGE *)effB8_conn_8, (EFFB8_MESSAGE *)effB8_conn_9,
    (EFFB8_MESSAGE *)effB8_conn_10, (EFFB8_MESSAGE *)effB8_conn_11,
    (EFFB8_MESSAGE *)effB8_conn_12,
};
