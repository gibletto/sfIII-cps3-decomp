/*
 * EFFG0_WORK.C  effect G0 work
 *
 * The judge count and character table of effect G0 (EffG0.c): initialised work RAM (section D).
 */

#include "types.h"
#include "structs.h"

extern s16 effg0_judge_count;
extern u16 effg0_judge_count_tail[];
extern const u32* effg0_char_tbl[];
extern const u32 ag_char_table_0[], ag_char_table_1[], ag_char_table_2[], ag_char_table_3[], ag_char_table_4[], ag_char_table_5[], ag_char_table_6[];
extern const u32 ag_char_table_0[];
extern const u32 ag_char_table_1[];
extern const u32 ag_char_table_2[];
extern const u32 ag_char_table_3[];
extern const u32 ag_char_table_4[];
extern const u32 ag_char_table_5[];

/* 020070D4 */
s16 effg0_judge_count = 0;

/* 020070D6 */
u16 effg0_judge_count_tail[1] = {
    0,
};

/* 020070D8 */
const u32* effg0_char_tbl[7] = {
    ag_char_table_0, ag_char_table_1, ag_char_table_2, ag_char_table_3,
    ag_char_table_4, ag_char_table_5, ag_char_table_6,
};
