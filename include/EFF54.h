#ifndef EFF54_H
#define EFF54_H

#include "structs.h"

s32 effect_54_init(WORK_Other* oya);
void effect_54_move(WORK_Other* ewk);

extern const s32 eff54_move_tbl[3][5];      /* provisional name */
extern const u32 eff54_char_table[6];        /* provisional name */

#endif
