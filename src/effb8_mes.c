/*
 * EFFB8_MES.C  message tables of effect B8
 *
 * The per-player message tables of effect B8 in each language and its panel table (EFFB8.c): initialised work RAM
 * (section D).
 */

#include "types.h"
#include "structs.h"

extern const EFFB8_MESSAGE* effB8_mes_jp[];
extern const EFFB8_MESSAGE* effB8_mes_en[];
extern const EFFB8_MESSAGE* effB8_mes_es[];
extern const EFFB8_MESSAGE* effB8_mes_pt[];
extern const EFFB8_MESSAGE* effB8_conn_tbl[];
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

/* 02006D68 */
const EFFB8_MESSAGE* effB8_mes_jp[13] = {
    effB8_mes_jp_0, effB8_mes_jp_1,
    effB8_mes_jp_2, effB8_mes_jp_3,
    effB8_mes_jp_4, effB8_mes_jp_5,
    effB8_mes_jp_0, effB8_mes_jp_7,
    effB8_mes_jp_8, effB8_mes_jp_9,
    effB8_mes_jp_10, effB8_mes_jp_11,
    effB8_mes_jp_12,
};

/* 02006D9C */
const EFFB8_MESSAGE* effB8_mes_en[13] = {
    effB8_mes_en_0, effB8_mes_en_1,
    effB8_mes_en_2, effB8_mes_en_3,
    effB8_mes_en_4, effB8_mes_en_5,
    effB8_mes_en_0, effB8_mes_en_7,
    effB8_mes_en_8, effB8_mes_en_9,
    effB8_mes_en_10, effB8_mes_en_11,
    effB8_mes_en_12,
};

/* 02006DD0 */
const EFFB8_MESSAGE* effB8_mes_es[13] = {
    effB8_mes_es_0, effB8_mes_es_1,
    effB8_mes_es_2, effB8_mes_es_3,
    effB8_mes_es_4, effB8_mes_es_5,
    effB8_mes_es_0, effB8_mes_es_7,
    effB8_mes_es_8, effB8_mes_es_9,
    effB8_mes_es_10, effB8_mes_es_11,
    effB8_mes_es_12,
};

/* 02006E04 */
const EFFB8_MESSAGE* effB8_mes_pt[13] = {
    effB8_mes_pt_0, effB8_mes_pt_1,
    effB8_mes_pt_2, effB8_mes_pt_3,
    effB8_mes_pt_4, effB8_mes_pt_5,
    effB8_mes_pt_0, effB8_mes_pt_7,
    effB8_mes_pt_8, effB8_mes_pt_9,
    effB8_mes_pt_10, effB8_mes_pt_11,
    effB8_mes_pt_12,
};

/* 02006E38 */
const EFFB8_MESSAGE* effB8_conn_tbl[13] = {
    effB8_conn_0, effB8_conn_1,
    effB8_conn_2, effB8_conn_3,
    effB8_conn_4, effB8_conn_5,
    effB8_conn_0, effB8_conn_7,
    effB8_conn_8, effB8_conn_9,
    effB8_conn_10, effB8_conn_11,
    effB8_conn_12,
};
