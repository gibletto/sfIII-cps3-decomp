#ifndef EFF94_H
#define EFF94_H

#include "structs.h"

void effect_94_move(WORK_Other* ewk);
void eff94_00(WORK_Other* ewk);
void eff94_go_00(WORK_Other* ewk);
void eff94_01(WORK_Other* ewk);
void eff94_go_01(WORK_Other* ewk);
void eff94_02(WORK_Other* ewk);
void eff94_go_02(WORK_Other* ewk);
void eff94_03(WORK_Other* ewk);
void eff94_04(WORK_Other* ewk);
void eff94_05(WORK_Other* ewk);
void eff94_06(WORK_Other* ewk);
void eff94_go_06(WORK_Other* ewk);
void eff94_07(WORK_Other* ewk);
s32 eff94_check_end(WORK_Other* ewk);
s32 eff94_check_front(WORK_Other* ewk);
void eff94_check_and_go(WORK_Other* ewk);
s32 eff94_select(WORK_Other* ewk);
void eff94_10(WORK_Other* ewk);
void eff94_11(WORK_Other* ewk);
void eff94_12(WORK_Other* ewk);
void eff94_13(WORK_Other* ewk);
void eff94_set_wait(WORK_Other* ewk);
s32 eff94_pl_attack_check(PLW* wk);
s32 effect_94_init(s16 PL_id, s16 sw);
void effect_94_entry(s16 sw);

#endif
