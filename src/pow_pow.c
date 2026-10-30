/*
 * POW_POW.C  Damage and score
 *
 * cal_damage_vitality and cal_damage_vitality_eff turn an attack's power into damage: each character has a
 * table of attacks (power and a rate column), and the round level picks the rate. Additinal_Score_DM,
 * Disp_Player_Score and Score_Sub add to and display the players' scores (six digits, capped at 9999900).
 * Disp_Player_Score_Debug (unreferenced) shows Score[id][SCORE_VS] on row 18 while exsw_3 bit 6 is set.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "end_main.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "sc_clear.h"
#include "cmb_win.h"
#include "Eff95.h"
#include "EFFB8.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "EFF49.h"
#include "eff56.h"
#include "eff57.h"
#include "EFF58.h"
#include "Eff76.h"
#include "EFFA7.h"
#include "effa8.h"
#include "effa9.h"
#include "aboutspr.h"
#include "bg000.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "win_2.h"
#include "pow_pow.h"
#include "fighter.h"



extern const DAMAGE_DATA* Damage_Data_Ptr[];    /* provisional name: per character, in work RAM */
extern const s8 Pow_Control_Data[8][3];         /* provisional name */


void cal_damage_vitality(PLW* as, PLW* ds) {
    u8 xx = as->wu.att.pow;
    s16 power = Damage_Data_Ptr[as->player_number][xx].power;
    s8 col = Damage_Data_Ptr[as->player_number][xx].rate_col;
    s16 yy = Pow_Control_Data[Round_Level][col];
    ds->wu.dm_vital = power * yy / 100;
}



void cal_damage_vitality_eff(WORK_Other* as, PLW* ds) {
    u8 xx = as->wu.att.pow;
    s16 power = Damage_Data_Ptr[((PLW*)as)->player_number][xx].power;
    s8 col = Damage_Data_Ptr[((PLW*)as)->player_number][xx].rate_col;
    s16 yy = Pow_Control_Data[Round_Level][col];
    ds->wu.dm_vital = power * yy / 100;
}

void Additinal_Score_DM(wk, ix)
WORK_Other* wk;
u16 ix;
{
    s16 id;
    if (wk->wu.work_id == 1) {
        id = wk->wu.id;
    } else {
        if (((WORK*)wk->my_master)->work_id != 1) {
            return;
        }
        id = wk->master_id;
    }
    Score[id][SCORE_ROUND] += Score_Data[ix];
    if (plw[id].wu.operator) {
        if (Play_Type == PLAY_VS_CPU) {
            Score[id][SCORE_CPU] += Score_Data[ix];
            if (Score[id][SCORE_CPU] >= 9999900) {
                Score[id][SCORE_CPU] = 9999900;
            }
        } else {
            Score[id][SCORE_VS] += Score_Data[ix];
        }
    }
    if (plw[id].wu.operator != 0) {
        Disp_Player_Score(id);
    }
}



/* provisional name */
void Disp_Player_Score(id)
s16 id;
{
    s16 digit[6];
    u32 score;
    s32 div;
    s16 top;
    s16 x;
    s16 i;
    score = Score[id][Play_Type];
    i = 5;
    div = 1000000;
    top = -1;
    while (i >= 1) {
        digit[i] = score / div;
        score -= digit[i] * div;
        if (top < 0) {
            if (digit[i]) {
                top = i;
            }
        }
        i--;
        div = div / 10;
    }
    x = Score_X_Pos_Data[id][Game_setting.Screen_Mode] - top - 1;
    for (i = top; i >= 1; i--, x++) {
        score8x16_put(x, 0, 38, digit[i]);
    }
}



/* provisional name */
void Disp_Player_Score_Debug(id)
s16 id;
{
    s16 digit[6];
    u32 score;
    s32 div;
    s16 top;
    s16 x;
    s16 i;
    if (!(exsw_3 & 0x40)) {
        return;
    }
    score = Score[id][SCORE_VS];
    i = 5;
    div = 1000000;
    top = -1;
    while (i >= 0) {
        digit[i] = score / div;
        score -= digit[i] * div;
        if (top < 0) {
            if (digit[i]) {
                top = i;
            }
        }
        i--;
        div = div / 10;
    }
    x = Score_X_Pos_Data[id][Game_setting.Screen_Mode] - top - 1;
    for (i = top; i >= 0; i--, x++) {
        score8x16_put(x, 18, 38, digit[i]);
    }
}



/* provisional name */
void Score_Sub(void) {
    u16 num;
    u16 tens;
    if (plw[0].wu.operator != 0 && Demo_Flag != 0) {
        tilemap_clear_rect(Score_X_Pos_Data[0][Game_setting.Screen_Mode] - 7, 0, Score_X_Pos_Data[0][Game_setting.Screen_Mode], 1);
        Disp_Player_Score(0);
        tens = Continue_Coin[0];
        num = Continue_Coin[0];
        tens = tens / 10;
        score8x16_put(Score_X_Pos_Data[0][Game_setting.Screen_Mode] - 1, 0, 38, tens);
        num -= tens * 10;
        score8x16_put(Score_X_Pos_Data[0][Game_setting.Screen_Mode], 0, 38, num);
    }
    if (plw[1].wu.operator != 0 && Demo_Flag != 0) {
        tilemap_clear_rect(Score_X_Pos_Data[1][Game_setting.Screen_Mode] - 7, 0, Score_X_Pos_Data[1][Game_setting.Screen_Mode], 1);
        Disp_Player_Score(1);
        tens = Continue_Coin[1];
        num = Continue_Coin[1];
        tens = tens / 10;
        score8x16_put(Score_X_Pos_Data[1][Game_setting.Screen_Mode] - 1, 0, 38, tens);
        num -= tens * 10;
        score8x16_put(Score_X_Pos_Data[1][Game_setting.Screen_Mode], 0, 38, num);
    }
}
