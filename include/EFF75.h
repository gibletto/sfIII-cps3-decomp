#ifndef EFF75_H
#define EFF75_H

#include "structs.h"

s32 effect_75_init(void);
void effect_75_move(WORK_Other* ewk);

extern const u32 eff75_char_table[];
extern const s16 eff75_dir_tbl[];
extern const s16 eff75_prio_tbl[];

#endif
