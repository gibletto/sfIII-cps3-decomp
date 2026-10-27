/*
 * PLPAT00_TBL.C  Gill special attack tables
 *
 * pl00_exatt_table is the special attack routines of character 0 (Gill), indexed by attack
 * routine number minus 16; mnd_em_tall gives, by opponent character, the { x, y } target of
 * the moonsault knee drop; glap_table the vitality gained per frame step of the resurrection.
 * Read by PLPAT00.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 mnd_em_tall[][2];
extern const s16 glap_table[];
extern void (*const pl00_exatt_table[])(PLW*);
extern void Att_ABISEGERI();
extern void Att_HADOUKEN();
extern void Att_MOONSALT_KNEE_DROP();
extern void Att_RESURRECTION();
extern void Att_SENPUUKYAKU();

const s16 mnd_em_tall[16][2] = {
    { 28, 56 },  /* Gill */
    { 24, 44 },  /* Alex */
    { 24, 40 },  /* Ryu */
    { 20, 32 },  /* Yun */
    { 24, 48 },  /* Dudley */
    { 24, 40 },  /* Necro */
    { 28, 60 },  /* Hugo */
    { 16, 44 },  /* Ibuki */
    { 32, 32 },  /* Elena */
    { 28, 24 },  /* Oro */
    { 20, 32 },  /* Yang */
    { 24, 40 },  /* Ken */
    { 24, 40 },  /* Sean */
    { 0, 0 },  /* 13 */
    { 0, 0 },  /* 14 */
    { 0, 0 },  /* 15 */
};

const s16 glap_table[6] = {
    1, 2, 3, 4, 0, 33,
};

void (*const pl00_exatt_table[6])(PLW*) = {
    Att_HADOUKEN, Att_MOONSALT_KNEE_DROP, Att_ABISEGERI, Att_SENPUUKYAKU,
    Att_HADOUKEN, Att_RESURRECTION,
};
