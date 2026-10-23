/*
 * PLCNT_WORK.C  player work
 *
 * The two players' work (plw) and the player control work beside it: super arts, stun, combo and after-image tables
 * (section B). A <name>_tail table holds the bytes between <name> and the next named variable.
 */

#include "types.h"
#include "structs.h"

s16 pcon_rno[4];  /* 0200D17C */
s16 appear_type;  /* 0200D184 */
u8 round_slow_flag;  /* 0200D186 */
u8 pcon_dp_flag;  /* 0200D187 */
u8 pl_eff_disp_stop;  /* 0200D188 */
/* after pl_eff_disp_stop: nothing refers to it by name or address */
u8 pl_eff_disp_stop_tail[1];  /* 0200D189 */
u8 win_sp_flag;  /* 0200D18A */
char dead_voice_flag;  /* 0200D18B */
PLW plw[2];  /* 0200D18C */
SA_WORK super_arts[2];  /* 0200D93C */
PiyoriType piyori_type[2];  /* 0200D97C */
ComboType combo_type[2];  /* 0200D9A4 */
ComboType remake_power[2];  /* 0200DAF4 */
ZanzouTableEntry zanzou_table[2][48];  /* 0200DC44 */
