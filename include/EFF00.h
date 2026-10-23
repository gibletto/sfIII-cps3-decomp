#ifndef EFF00_H
#define EFF00_H

#include "structs.h"

s32 effect_00_init(WORK* wk);
void renewal_table_data(WORK_Other_JUDGE* ewk);
void renewal_table_address(WORK_Other_JUDGE* ewk, WORK* twk);
void effect_00_move(WORK_Other_JUDGE* ewk);
void get_new_parts_data(WORK_Other* ewk, PLW* mwk);
void effect_01_move(WORK_Other* ewk);

s32 effect_01_init(WORK* wk, u8 koolc);

#endif
