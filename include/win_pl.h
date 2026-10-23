#ifndef WIN_PL_H
#define WIN_PL_H

#include "structs.h"

void win_player(PLW* wk);
void Win_00000(PLW* wk);
void Win_01000(PLW* wk);
void jijii_fly_up(PLW* wk);
void jijii_jump(PLW* wk);
void Win_02000(PLW* wk);
void Win_03000(PLW* wk);
void Win_04000(PLW* wk);
void Normal_normal_Winner(PLW* wk);
void Judge_normal_winner(PLW* wk);
s32 win_special_check(PLW* wk);
void Win_05000(PLW* wk);
void Win_06000(PLW* wk);
void win_stage8_action(PLW* wk);
s32 win_select(PLW* wk, s16 num);

#endif
