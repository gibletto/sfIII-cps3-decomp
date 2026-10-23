#ifndef PLPCU_H
#define PLPCU_H

#include "structs.h"

void Caught_03000(PLW* wk);
void scdmd_14000(PLW* wk);
void scdmd_16000(PLW* wk);
void scdmd_17000(PLW* wk);
void scdmd_19000(PLW* wk);
void scdmd_21000(PLW* wk);
void scdmd_25000(PLW* wk);
void Player_caught(PLW* wk);
void Caught_00000(PLW* wk);
void caught_cg_type_check(PLW* wk, PLW* emwk);
s32 check_tsukamare_keizoku_check(PLW* wk, PLW* emwk);
void scdmd_23000(WORK* wk);
void Caught_01000(PLW* wk, PLW* emwk);
void Caught_02000(PLW* wk, PLW* emwk);
void scdmd_12000(PLW* wk);
void scdmd_18000(PLW* wk);
void scdmd_24000(PLW* wk);
void scdmd_20000(void);
void scdmd_26000(PLW* wk);

void scdmd_27000(PLW* wk);
void scdmd_28000(PLW* wk);

extern const u8 caught_dm_chg_tbl1[][2];   /* provisional name */
extern const u8 caught_dm_chg_tbl6[][2];   /* provisional name */
#endif
