/*
 * CMD_DATA.C  tables read by cmd_main_2.c: the lever tables and the command lists the per-character tables of
 * pl_CMD (work RAM) point at (pc_cmd_NN: shared by every character, pX_cmd_NN: character X's entry NN, dm_cmd_xx:
 * the empty entry)
 */

/*
 * Record format (CMD_DATA.H names every field and flag): a 12-word header, then 4-word steps,
 * then CMD_END.  Ryu's Hadoken, 236+P:
 *
 *   CMD_RESET, CMD_LV_UP, 0,          reset: once entered, the command waits 12 frames for the
 *                                     move to start; dead, dead2: holding up (a jump) drops it
 *   CMD_WAZA(RYU_HADOKEN),            rno[4]: the attack routine each strength starts
 *   CMD_BT_CHG,                       btix: the button is a new press
 *   CMD_EX_PUNCHES,                   exdt[4]: LP, MP, HP, and all the punches together
 *   CMD_LEVER(0, CMD_LV_DOWN),        steps: down,
 *   CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),   down-forward within 12 frames,
 *   CMD_LEVER(12, CMD_LV_FORWARD),    forward within 12 frames
 *   CMD_END,
 */

#include "types.h"
#include "structs.h"
#include "cmd_data.h"

#pragma section TBL

extern const s16 lever_gacha_tbl[];
extern const s16 pl_cmd_num[][8];
extern const s16 pc_cmd_00[];
extern const s16 pc_cmd_01[];
extern const s16 pc_cmd_02[];
extern const s16 pc_cmd_03[];
extern const s16 pc_cmd_04[];
extern const s16 pc_cmd_05[];
extern const s16 pc_cmd_06[];
extern const s16 pc_cmd_07[];
extern const s16 pc_cmd_08[];
extern const s16 pc_cmd_09[];
extern const s16 pc_cmd_10[];
extern const s16 pc_cmd_11[];
extern const s16 pc_cmd_12[];
extern const s16 pc_cmd_13[];
extern const s16 pc_cmd_14[];
extern const s16 pc_cmd_15[];
extern const s16 dm_cmd_xx[];
extern const s16 p0_cmd_16[];
extern const s16 p0_cmd_17[];
extern const s16 p0_cmd_18[];
extern const s16 p0_cmd_22[];
extern const s16 p0_cmd_23[];
extern const s16 p0_cmd_24[];
extern const s16 p0_cmd_25[];
extern const s16 p0_cmd_26[];
extern const s16 p1_cmd_16[];
extern const s16 p1_cmd_17[];
extern const s16 p1_cmd_18[];
extern const s16 p1_cmd_22[];
extern const s16 p1_cmd_23[];
extern const s16 p1_cmd_24[];
extern const s16 p1_cmd_25[];
extern const s16 p1_cmd_46[];
extern const s16 p1_cmd_47[];
extern const s16 p2_cmd_16[];
extern const s16 p2_cmd_17[];
extern const s16 p2_cmd_18[];
extern const s16 p2_cmd_22[];
extern const s16 p2_cmd_23[];
extern const s16 p2_cmd_24[];
extern const s16 p2_cmd_25[];
extern const s16 p2_cmd_37[];
extern const s16 p3_cmd_16[];
extern const s16 p3_cmd_17[];
extern const s16 p3_cmd_18[];
extern const s16 p3_cmd_22[];
extern const s16 p3_cmd_23[];
extern const s16 p3_cmd_24[];
extern const s16 p3_cmd_25[];
extern const s16 p4_cmd_16[];
extern const s16 p4_cmd_17[];
extern const s16 p4_cmd_18[];
extern const s16 p4_cmd_22[];
extern const s16 p4_cmd_23[];
extern const s16 p4_cmd_24[];
extern const s16 p4_cmd_25[];
extern const s16 p4_cmd_26[];
extern const s16 p4_cmd_46[];
extern const s16 p4_cmd_47[];
extern const s16 p5_cmd_16[];
extern const s16 p5_cmd_17[];
extern const s16 p5_cmd_18[];
extern const s16 p5_cmd_22[];
extern const s16 p5_cmd_23[];
extern const s16 p5_cmd_24[];
extern const s16 p5_cmd_25[];
extern const s16 p5_cmd_26[];
extern const s16 p5_cmd_46[];
extern const s16 p5_cmd_47[];
extern const s16 p7_cmd_16[];
extern const s16 p7_cmd_17[];
extern const s16 p7_cmd_33[];
extern const s16 p7_cmd_22[];
extern const s16 p7_cmd_23[];
extern const s16 p7_cmd_24[];
extern const s16 p7_cmd_25[];
extern const s16 p7_cmd_26[];
extern const s16 p7_cmd_37[];
extern const s16 p8_cmd_16[];
extern const s16 p8_cmd_17[];
extern const s16 p8_cmd_18[];
extern const s16 p8_cmd_22[];
extern const s16 p8_cmd_23[];
extern const s16 p8_cmd_24[];
extern const s16 p9_cmd_16[];
extern const s16 p9_cmd_17[];
extern const s16 p9_cmd_18[];
extern const s16 p9_cmd_22[];
extern const s16 p9_cmd_23[];
extern const s16 p9_cmd_24[];
extern const s16 p9_cmd_25[];
extern const s16 p9_cmd_37[];
extern const s16 p9_cmd_38[];
extern const s16 pA_cmd_16[];
extern const s16 pA_cmd_17[];
extern const s16 pA_cmd_18[];
extern const s16 pA_cmd_22[];
extern const s16 pA_cmd_23[];
extern const s16 pA_cmd_24[];
extern const s16 pA_cmd_25[];
extern const s16 pB_cmd_16[];
extern const s16 pB_cmd_17[];
extern const s16 pB_cmd_18[];
extern const s16 pB_cmd_22[];
extern const s16 pB_cmd_23[];
extern const s16 pB_cmd_24[];
extern const s16 pB_cmd_25[];
extern const s16 pB_cmd_37[];
extern const s16 pC_cmd_16[];
extern const s16 pC_cmd_17[];
extern const s16 pC_cmd_18[];
extern const s16 pC_cmd_22[];
extern const s16 pC_cmd_23[];
extern const s16 pC_cmd_24[];
extern const s16 pC_cmd_25[];
extern const s16 pC_cmd_26[];
extern const s16 ukemi_time_tbl[];
extern const char player_cmd_line_str0[];
extern const char player_cmd_line_str1[];
extern const char player_cmd_line_str2[];
extern const char player_cmd_line_str3[];
extern const char player_cmd_line_str4[];
extern const char player_cmd_line_str5[];
extern const char player_cmd_line_str6[];
extern const char lvr_chk_line_str0[];
extern const char lvr_chk_line_str1[];
extern const char lvr_chk_line_str2[];

const s16 lever_gacha_tbl[16] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
};

const s16 pl_cmd_num[13][8] = {
    { 16, 19, 27, 30, 33, 37, 43, 46 },  /* Gill */
    { 16, 19, 26, 30, 33, 37, 43, 46 },  /* Alex */
    { 16, 19, 26, 30, 33, 37, 43, 46 },  /* Ryu */
    { 16, 19, 26, 30, 33, 37, 43, 46 },  /* Yun */
    { 16, 19, 27, 30, 33, 37, 43, 46 },  /* Dudley */
    { 16, 19, 27, 30, 33, 37, 43, 46 },  /* Necro */
    { 16, 16, 22, 30, 33, 37, 43, 46 },  /* Hugo */
    { 16, 18, 27, 30, 34, 38, 43, 46 },  /* Ibuki */
    { 16, 19, 25, 30, 33, 37, 43, 46 },  /* Elena */
    { 16, 19, 26, 30, 33, 39, 43, 46 },  /* Oro */
    { 16, 19, 26, 30, 33, 37, 43, 46 },  /* Yang */
    { 16, 19, 26, 30, 33, 37, 43, 46 },  /* Ken */
    { 16, 19, 27, 30, 33, 37, 43, 46 },  /* Sean */
};

/* The comment on each record names the move from the published move lists, checked against its
   motion, buttons, slot group and the plNN_exatt_table routine its rno starts; (?) marks a guess.
   A super art's number (SA I - III) is the one whose super_arts_data entry (PLCNT_tbl.c) names the
   record's slot; the slot order is not the super art order. The input after the name is in numpad
   notation (2 down, 6 forward, [4]6 charge back then forward), as the record's steps accept it. */
const s16 pc_cmd_00[29] = {  /* forward dash */
    8, CMD_LV_BACK, CMD_LV_DOWN, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_LEVER, 1, 1, CMD_LV_FORWARD),
    CMD_LEVER_ANY(6, CMD_LV_NEUTRAL),
    CMD_STEP(CK_LEVER_SET, 6, 0, CMD_EXACT(CMD_LV_FORWARD)),
    CMD_STEP(CK_LEVER_REPEAT, 6, 6, CMD_EXACT(CMD_LV_FORWARD)),
    CMD_END,
};

const s16 pc_cmd_01[29] = {  /* back dash */
    8, CMD_LV_FORWARD, CMD_LV_DOWN, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_LEVER_ANY(1, CMD_LV_BACK),
    CMD_LEVER_ANY(6, CMD_LV_NEUTRAL),
    CMD_STEP(CK_LEVER_SET, 6, 0, CMD_EXACT(CMD_LV_BACK)),
    CMD_STEP(CK_LEVER_REPEAT, 6, 6, CMD_EXACT(CMD_LV_BACK)),
    CMD_END,
};

const s16 pc_cmd_02[21] = {  /* high jump */
    8, 0, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_LEVER_NEW, 1, 0, CMD_LV_DOWN),
    CMD_STEP(CK_LEVER_NEW, 8, 0, CMD_LV_UP),
    CMD_END,
};

const s16 pc_cmd_03[17] = {  /* parry (forward) */
    8, CMD_LV_DOWN, CMD_LV_DOWN | CMD_LV_FORWARD, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_PARRY, 8, 0, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pc_cmd_04[17] = {  /* low parry (down) */
    10, CMD_LV_UP, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_PARRY, 10, 0, CMD_LV_DOWN),
    CMD_END,
};

const s16 pc_cmd_05[17] = {  /* parry (forward), second record (?) */
    10, CMD_LV_DOWN, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_PARRY, 8, 0, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pc_cmd_06[17] = {  /* low parry (down), second record (?) */
    8, CMD_LV_DOWN, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_PARRY, 10, 0, CMD_LV_DOWN),
    CMD_END,
};

const s16 pc_cmd_07[17] = {  /* red parry window (down) (?) */
    2, 0, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_PARRY_STRICT, 8, 0, CMD_LV_DOWN),
    CMD_END,
};

const s16 pc_cmd_08[17] = {  /* punch mashing */
    7, 0, 0, 0, 1, 2, 3, CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_RENDA3, 48, 48, CMD_SW_LP),
    CMD_END,
};

const s16 pc_cmd_09[17] = {  /* punch mashing, longer window */
    11, 0, 0, 0, 1, 2, 3, CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_RENDA3, 72, 72, CMD_SW_LP),
    CMD_END,
};

const s16 pc_cmd_10[17] = {  /* kick mashing */
    7, 0, 0, 0, 1, 2, 3, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_RENDA3, 48, 48, CMD_SW_LK),
    CMD_END,
};

const s16 pc_cmd_11[17] = {  /* kick mashing, longer window */
    11, 0, 0, 0, 1, 2, 3, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_RENDA3, 72, 72, CMD_SW_LK),
    CMD_END,
};

const s16 pc_cmd_12[25] = {  /* back, up-back, up (?) */
    8, CMD_LV_FORWARD, CMD_LV_DOWN, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_UP | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_UP),
    CMD_END,
};

const s16 pc_cmd_13[25] = {  /* down, down */
    4, CMD_LV_UP, 0, 0, 0, 0, 0, CMD_BT_NONE, 0, 0, 0, 0,
    CMD_STEP(CK_LEVER_PRESS, 1, 1, CMD_EXACT(CMD_LV_DOWN)),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_LV_NEUTRAL),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_EXACT(CMD_LV_DOWN)),
    CMD_END,
};

const s16 pc_cmd_14[25] = {  /* down, down + punch */
    CMD_RESET, CMD_LV_UP, CMD_LV_UP, 10, 10, 10, 10, CMD_BT_NOW, CMD_EX_PUNCHES,
    CMD_STEP(CK_LEVER_PRESS, 1, 1, CMD_EXACT(CMD_LV_DOWN)),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_LV_NEUTRAL),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_EXACT(CMD_LV_DOWN)),
    CMD_END,
};

const s16 pc_cmd_15[25] = {  /* down, down + kick */
    CMD_RESET, CMD_LV_UP, CMD_LV_UP, 10, 10, 10, 10, CMD_BT_NOW, CMD_EX_KICKS,
    CMD_STEP(CK_LEVER_PRESS, 1, 1, CMD_EXACT(CMD_LV_DOWN)),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_LV_NEUTRAL),
    CMD_STEP(CK_LEVER_CHANGE, 6, 0, CMD_EXACT(CMD_LV_DOWN)),
    CMD_END,
};

const s16 dm_cmd_xx[25] = {  /* unused slot (a dummy fireball motion) */
    CMD_RESET, 0, 0, 0, 0, 0, 0, CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

/* Gill's attack routines (routine_no[2]; 16 and up index pl00_exatt_table) */
#define GILL_PYROKINESIS          16  /* Att_HADOUKEN */
#define GILL_MOONSAULT_KNEE_DROP  17  /* Att_MOONSALT_KNEE_DROP */
#define GILL_CYBER_LARIAT         18  /* Att_ABISEGERI */
#define GILL_PSYCHO_HEADBUTT      19  /* Att_SENPUUKYAKU */
#define GILL_RESURRECTION         21  /* Att_RESURRECTION */

const s16 p0_cmd_16[13] = {  /* Gill: super art slot, disabled */
    CMD_RESET, 0, 0, CMD_WAZA(GILL_RESURRECTION), CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled; check_init reads the rest of the step from the next record */
};

const s16 p0_cmd_17[13] = {  /* Gill: super art slot, disabled */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(GILL_RESURRECTION), CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled; check_init reads the rest of the step from the next record */
};

const s16 p0_cmd_18[13] = {  /* Gill: super art slot, disabled */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(GILL_RESURRECTION), CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled; check_init reads the rest of the step from the next record */
};

const s16 p0_cmd_22[25] = {  /* Gill: Cyber Lariat, 623+P */
    CMD_RESET, 0, 0, CMD_WAZA(GILL_CYBER_LARIAT), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p0_cmd_23[25] = {  /* Gill: Moonsault Knee Drop, 63214+K */
    CMD_RESET, 0, 0, CMD_WAZA(GILL_MOONSAULT_KNEE_DROP), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p0_cmd_24[25] = {  /* Gill: Pyrokinesis, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(GILL_PYROKINESIS), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p0_cmd_25[25] = {  /* Gill: Psycho Headbutt, 214+P */
    CMD_RESET, 0, 0, CMD_WAZA(GILL_PSYCHO_HEADBUTT), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p0_cmd_26[18] = {  /* Gill: two punches together (?) */
    CMD_RESET, 0, 0, 20, 20, 20, 20, CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled: placed ahead of the steps below */
    CMD_STEP(CK_PRESS_P, 4, 0, 2),
    CMD_END,
};

/* Alex's attack routines (routine_no[2]; 16 and up index pl01_exatt_table) */
#define ALEX_FLASH_CHOP         16  /* Att_CHOUCHUURENGEKI */
#define ALEX_AIR_KNEE_SMASH     17  /* Att_SHOURYUUKEN */
#define ALEX_POWER_BOMB         18  /* Att_HADOUKEN */
#define ALEX_HYPER_BOMB         19  /* Att_HADOUKEN2 */
#define ALEX_BOOMERANG_RAID     20  /* Att_CHOUCHUURENGEKI */
#define ALEX_STUN_GUN_HEADBUTT  21  /* Att_SENPUUKYAKU2 */
#define ALEX_AIR_STAMPEDE       22  /* Att_SENPUUKYAKU */

const s16 p1_cmd_16[20] = {  /* Alex: SA I Hyper Bomb, 360+P */
    CMD_RESET, 0, 0, CMD_WAZA(ALEX_HYPER_BOMB), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_TURN, 32, 32, 0),
    0, 0, 0,                /* never read: CK_TURN completes the command itself */
    CMD_END,
};

const s16 p1_cmd_17[33] = {  /* Alex: SA II Boomerang Raid, 236236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ALEX_BOOMERANG_RAID), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p1_cmd_18[33] = {  /* Alex: SA III Stun Gun Headbutt, 236236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ALEX_STUN_GUN_HEADBUTT), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p1_cmd_22[25] = {  /* Alex: Air Knee Smash, 623+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ALEX_AIR_KNEE_SMASH), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p1_cmd_23[25] = {  /* Alex: Power Bomb, 63214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ALEX_POWER_BOMB), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p1_cmd_24[25] = {  /* Alex: Flash Chop, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ALEX_FLASH_CHOP), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p1_cmd_25[21] = {  /* Alex: Air Stampede, [2]8+K */
    CMD_RESET, 0, 0, CMD_WAZA(ALEX_AIR_STAMPEDE), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_CHARGE, 42, 42, CMD_LV_DOWN),
    CMD_LEVER_ANY(12, CMD_LV_UP),
    CMD_END,
};

const s16 p1_cmd_46[17] = {  /* Alex: up + punch, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, 23, 23, 23, 23, CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

const s16 p1_cmd_47[17] = {  /* Alex: up + kick, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, 23, 23, 23, 23, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

/* Ryu's attack routines (routine_no[2]; 16 and up index pl02_exatt_table) */
#define RYU_HADOKEN                   16  /* Att_HADOUKEN */
#define RYU_SHORYUKEN                 17  /* Att_SHOURYUUKEN */
#define RYU_TATSUMAKI_SENPUKYAKU      18  /* Att_SENPUUKYAKU */
#define RYU_SHINKUU_HADOKEN           19  /* Att_HADOUKEN */
#define RYU_SHIN_SHORYUKEN            20  /* Att_SHINSHOURYUUKEN */
#define RYU_DENJIN_HADOKEN            21  /* Att_HADOUKEN */
#define RYU_AIR_TATSUMAKI_SENPUKYAKU  22  /* Att_KUUCHUUNICHIRINSHOU */
#define RYU_JOUDAN_SOKUTOU_GERI       23  /* Att_HADOUKEN2 */

const s16 p2_cmd_16[33] = {  /* Ryu: SA I Shinkuu Hadoken, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(RYU_SHINKUU_HADOKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_17[33] = {  /* Ryu: SA III Denjin Hadoken, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(RYU_DENJIN_HADOKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_18[33] = {  /* Ryu: SA II Shin Shoryuken, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(RYU_SHIN_SHORYUKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_22[25] = {  /* Ryu: Shoryuken, 623+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(RYU_SHORYUKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_23[25] = {  /* Ryu: Hadoken, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(RYU_HADOKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_24[25] = {  /* Ryu: Tatsumaki Senpukyaku, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(RYU_TATSUMAKI_SENPUKYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p2_cmd_25[29] = {  /* Ryu: Joudan Sokutou Geri, 41236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(RYU_JOUDAN_SOKUTOU_GERI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p2_cmd_37[25] = {  /* Ryu: air Tatsumaki Senpukyaku, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(RYU_AIR_TATSUMAKI_SENPUKYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

/* Yun's attack routines (routine_no[2]; 16 and up index pl03_exatt_table) */
#define YUN_KOBOKUSHI           16  /* Att_HADOUKEN */
#define YUN_SENKYUUTAI          17  /* Att_TENSHINSENKYUUTAI */
#define YUN_ZESSHOU_HOHOU       18  /* Att_SENPUUKYAKU */
#define YUN_GENEI_JIN           19  /* Att_HADOUKEN */
#define YUN_SOURAI_RENGEKI      20  /* Att_SLIDE_and_JUMP */
#define YUN_TENSHIN_SENKYUUTAI  21  /* Att_TENSHINSENKYUUTAI */
#define YUN_ZENPOU_TENSHIN      22  /* Att_HADOUKEN */

const s16 p3_cmd_16[33] = {  /* Yun: SA III Genei Jin, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(YUN_GENEI_JIN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p3_cmd_17[33] = {  /* Yun: SA II Sourai Rengeki, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(YUN_SOURAI_RENGEKI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p3_cmd_18[33] = {  /* Yun: SA I Tenshin Senkyuutai, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(YUN_TENSHIN_SENKYUUTAI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p3_cmd_22[25] = {  /* Yun: Zenpou Tenshin, 63214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YUN_ZENPOU_TENSHIN), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p3_cmd_23[25] = {  /* Yun: Kobokushi, 214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YUN_KOBOKUSHI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p3_cmd_24[25] = {  /* Yun: Senkyuutai, 236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YUN_SENKYUUTAI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p3_cmd_25[25] = {  /* Yun: Zesshou Hohou, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YUN_ZESSHOU_HOHOU), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

/* Dudley's attack routines (routine_no[2]; 16 and up index pl04_exatt_table) */
#define DUDLEY_JET_UPPER                16  /* Att_SENPUUKYAKU */
#define DUDLEY_MACHINE_GUN_BLOW         17  /* Att_SENPUUKYAKU */
#define DUDLEY_CROSS_COUNTER            18  /* Att_HADOUKEN */
#define DUDLEY_ROCKET_UPPERCUT          19  /* Att_SHOURYUUREPPA */
#define DUDLEY_ROLLING_THUNDER          20  /* Att_HADOUKEN2 */
#define DUDLEY_CORKSCREW_BLOW           21  /* Att_CHOUCHUURENGEKI */
#define DUDLEY_PUNCH_AND_CROSS_COUNTER  25  /* Att_HADOUKEN */

const s16 p4_cmd_16[33] = {  /* Dudley: SA I Rocket Uppercut, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(DUDLEY_ROCKET_UPPERCUT), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_17[33] = {  /* Dudley: SA II Rolling Thunder, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(DUDLEY_ROLLING_THUNDER), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_18[33] = {  /* Dudley: SA III Corkscrew Blow, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(DUDLEY_CORKSCREW_BLOW), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_22[25] = {  /* Dudley: Jet Upper, 623+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(DUDLEY_JET_UPPER), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_23[33] = {  /* Dudley: Punch and Cross Counter, 6321456+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(DUDLEY_PUNCH_AND_CROSS_COUNTER), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_NEUTRAL),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_24[25] = {  /* Dudley: Cross Counter, 63214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(DUDLEY_CROSS_COUNTER), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p4_cmd_25[25] = {  /* Dudley: Machine Gun Blow, 41236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(DUDLEY_MACHINE_GUN_BLOW), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_26[50] = {  /* Dudley: Ducking; the second record is a down, down-forward, forward kick move (?) */
    CMD_RESET, CMD_LV_UP, 0, 22, 22, 22, 22, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_FORWARD),
    CMD_END,
    /* a second record follows, which no slot points at */
    CMD_RESET, CMD_LV_UP, 0, 23, 23, 23, 23, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p4_cmd_46[17] = {  /* Dudley: up + punch, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, 26, 26, 26, 26, CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

const s16 p4_cmd_47[17] = {  /* Dudley: up + kick, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, 26, 26, 26, 26, CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

/* Necro's attack routines (routine_no[2]; 16 and up index pl05_exatt_table) */
#define NECRO_TORNADO_HOOK    16  /* Att_CHOUCHUURENGEKI */
#define NECRO_DENJI_BLAST     17  /* Att_HADOUKEN */
#define NECRO_MAGNETIC_STORM  18  /* Att_HADOUKEN */
#define NECRO_SNAKE_FANG      19  /* Att_HADOUKEN */
#define NECRO_ELECTRIC_SNAKE  20  /* Att_HADOUKEN */
#define NECRO_FLYING_VIPER    21  /* Att_SENPUUKYAKU */
#define NECRO_SLAM_DANCE      22  /* Att_HADOUKEN */
#define NECRO_RISING_COBRA    24  /* Att_HADOUKEN */

const s16 p5_cmd_16[33] = {  /* Necro: SA I Magnetic Storm, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(NECRO_MAGNETIC_STORM), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_17[33] = {  /* Necro: SA III Electric Snake, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(NECRO_ELECTRIC_SNAKE), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_18[33] = {  /* Necro: SA II Slam Dance, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(NECRO_SLAM_DANCE), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_22[29] = {  /* Necro: Snake Fang, 41236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(NECRO_SNAKE_FANG), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_23[25] = {  /* Necro: Denji Blast, 623+P */
    CMD_RESET, 0, 0, CMD_WAZA(NECRO_DENJI_BLAST), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_24[29] = {  /* Necro: Tornado Hook, 41236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(NECRO_TORNADO_HOOK), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p5_cmd_25[25] = {  /* Necro: Flying Viper, 214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(NECRO_FLYING_VIPER), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p5_cmd_26[25] = {  /* Necro: Rising Cobra, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(NECRO_RISING_COBRA), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p5_cmd_46[17] = {  /* Necro: up + punch, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, CMD_WAZA(NECRO_DENJI_BLAST), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

const s16 p5_cmd_47[17] = {  /* Necro: up + kick, on the ground only (check_leap_attack2) (?) */
    CMD_RESET, CMD_LV_FORWARD, CMD_LV_BACK, CMD_WAZA(NECRO_DENJI_BLAST), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_STEP(CK_LEVER_HELD, 1, 0, CMD_LV_UP),
    CMD_END,
};

/* Ibuki's attack routines (routine_no[2]; 16 and up index pl07_exatt_table) */
#define IBUKI_KAZEKIRI       16  /* Att_SHOURYUUKEN */
#define IBUKI_KUBI_ORI       17  /* Att_PL07_AT1 */
#define IBUKI_RAIDA          18  /* Att_CHOUCHUURENGEKI */
#define IBUKI_HASHIN_SHO     19  /* Att_CHOUCHUURENGEKI */
#define IBUKI_TSUMUJI        20  /* Att_CHOUCHUURENGEKI */
#define IBUKI_YOROI_DOSHI    21  /* Att_PL07_SA2 */
#define IBUKI_HIEN           22  /* Att_PL07_AT2 */
#define IBUKI_KUNAI          23  /* Att_PL07_AT3 */
#define IBUKI_KASUMI_SUZAKU  24  /* Att_PL07_SA3 */

const s16 p7_cmd_16[33] = {  /* Ibuki: SA III Hashin Sho, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(IBUKI_HASHIN_SHO), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p7_cmd_17[33] = {  /* Ibuki: SA II Yoroi Doshi, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(IBUKI_YOROI_DOSHI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p7_cmd_33[33] = {  /* Ibuki: SA I Kasumi Suzaku (air), 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(IBUKI_KASUMI_SUZAKU), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p7_cmd_22[25] = {  /* Ibuki: Kazekiri, 623+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_KAZEKIRI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p7_cmd_23[25] = {  /* Ibuki: Raida, 63214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_RAIDA), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p7_cmd_24[25] = {  /* Ibuki: Hien, 421+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_HIEN), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_END,
};

const s16 p7_cmd_25[25] = {  /* Ibuki: Kubi Ori, 236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_KUBI_ORI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p7_cmd_26[25] = {  /* Ibuki: Tsumuji, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_TSUMUJI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 p7_cmd_37[25] = {  /* Ibuki: Kunai (air), 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(IBUKI_KUNAI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

/* Elena's attack routines (routine_no[2]; 16 and up index pl08_exatt_table) */
#define ELENA_SCRATCH_WHEEL  16  /* Att_SHOURYUUKEN */
#define ELENA_RHINO_HORN     17  /* Att_SENPUUKYAKU */
#define ELENA_MALLET_SMASH   18  /* Att_SENPUUKYAKU */
#define ELENA_SPINNING_BEAT  19  /* Att_SHOURYUUREPPA */
#define ELENA_BRAVE_DANCE    20  /* Att_SHOURYUUREPPA */
#define ELENA_HEALING        21  /* Att_PL08_HEALING */

const s16 p8_cmd_16[33] = {  /* Elena: SA I Spinning Beat, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(ELENA_SPINNING_BEAT), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p8_cmd_17[33] = {  /* Elena: SA II Brave Dance, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(ELENA_BRAVE_DANCE), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p8_cmd_18[33] = {  /* Elena: SA III Healing, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(ELENA_HEALING), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p8_cmd_22[25] = {  /* Elena: Scratch Wheel, 623+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ELENA_SCRATCH_WHEEL), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p8_cmd_23[25] = {  /* Elena: Rhino Horn, 41236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ELENA_RHINO_HORN), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p8_cmd_24[25] = {  /* Elena: Mallet Smash, 63214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ELENA_MALLET_SMASH), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

/* Oro's attack routines (routine_no[2]; 16 and up index pl09_exatt_table) */
#define ORO_NICHIRIN_SHOU       16  /* Att_HADOUKEN */
#define ORO_ONI_YANMA           17  /* Att_SHOURYUUKEN */
#define ORO_AIR_NICHIRIN_SHOU   18  /* Att_KUUCHUUNICHIRINSHOU */
#define ORO_NIOU_RIKI           19  /* Att_HADOUKEN */
#define ORO_TENGU_STONE         20  /* Att_HADOUKEN */
#define ORO_YAGYOU_DAMA         21  /* Att_HADOUKEN */
#define ORO_KISHIN_RIKI         22  /* Att_HADOUKEN */
#define ORO_AIR_JINCHUU_WATARI  23  /* Att_KUUCHUUJINNCHUUWATARI */
#define ORO_JINCHUU_WATARI      24  /* Att_JINNCHUUWATARI */

const s16 p9_cmd_16[33] = {  /* Oro: SA III Tengu Stone, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(ORO_TENGU_STONE), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_17[33] = {  /* Oro: SA II Yagyou Dama, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(ORO_YAGYOU_DAMA), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_18[33] = {  /* Oro: SA I Kishin Riki, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(ORO_KISHIN_RIKI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_22[21] = {  /* Oro: Oni Yanma, [2]8+P */
    CMD_RESET, 0, 0, CMD_WAZA(ORO_ONI_YANMA), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_CHARGE, 42, 42, CMD_LV_DOWN),
    CMD_LEVER_ANY(12, CMD_LV_UP),
    CMD_END,
};

const s16 p9_cmd_23[25] = {  /* Oro: Niou Riki, 63214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ORO_NIOU_RIKI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 p9_cmd_24[21] = {  /* Oro: Nichirin Shou, [4]6+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ORO_NICHIRIN_SHOU), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_STEP(CK_CHARGE, 42, 42, CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_25[25] = {  /* Oro: Jinchuu Watari, 236+K */
    CMD_RESET, 0, 0, CMD_WAZA(ORO_JINCHUU_WATARI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_37[26] = {  /* Oro: air Nichirin Shou, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ORO_AIR_NICHIRIN_SHOU), CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled: placed ahead of the steps below */
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 p9_cmd_38[25] = {  /* Oro: air Jinchuu Watari, 236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(ORO_AIR_JINCHUU_WATARI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

/* Yang's attack routines (routine_no[2]; 16 and up index pl10_exatt_table) */
#define YANG_KOBOKUSHI           16  /* Att_HADOUKEN */
#define YANG_SENKYUUTAI          17  /* Att_TENSHINSENKYUUTAI */
#define YANG_ZESSHOU_HOHOU       18  /* Att_SENPUUKYAKU */
#define YANG_GENEI_JIN           19  /* Att_HADOUKEN */
#define YANG_SOURAI_RENGEKI      20  /* Att_SLIDE_and_JUMP */
#define YANG_TENSHIN_SENKYUUTAI  21  /* Att_TENSHINSENKYUUTAI */
#define YANG_ZENPOU_TENSHIN      22  /* Att_HADOUKEN */

const s16 pA_cmd_16[33] = {  /* Yang: SA III Genei Jin, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(YANG_GENEI_JIN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pA_cmd_17[33] = {  /* Yang: SA II Sourai Rengeki, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(YANG_SOURAI_RENGEKI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pA_cmd_18[33] = {  /* Yang: SA I Tenshin Senkyuutai, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(YANG_TENSHIN_SENKYUUTAI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pA_cmd_22[25] = {  /* Yang: Zenpou Tenshin, 63214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YANG_ZENPOU_TENSHIN), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_FORWARD),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_BACK),
    CMD_END,
};

const s16 pA_cmd_23[25] = {  /* Yang: Kobokushi, 214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YANG_KOBOKUSHI), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 pA_cmd_24[25] = {  /* Yang: Senkyuutai, 236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YANG_SENKYUUTAI), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pA_cmd_25[25] = {  /* Yang: Zesshou Hohou, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(YANG_ZESSHOU_HOHOU), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

/* Ken's attack routines (routine_no[2]; 16 and up index pl11_exatt_table) */
#define KEN_HADOKEN                   16  /* Att_HADOUKEN */
#define KEN_SHORYUKEN                 17  /* Att_SHOURYUUKEN */
#define KEN_TATSUMAKI_SENPUKYAKU      18  /* Att_SENPUUKYAKU */
#define KEN_SHORYU_REPPA              19  /* Att_SHOURYUUREPPA */
#define KEN_SHINRYUKEN                20  /* Att_SHOURYUUREPPA */
#define KEN_SHIPPU_JINRAIKYAKU        21  /* Att_SLIDE_and_JUMP */
#define KEN_AIR_TATSUMAKI_SENPUKYAKU  22  /* Att_KUUCHUUNICHIRINSHOU */

const s16 pB_cmd_16[33] = {  /* Ken: SA I Shoryu Reppa, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(KEN_SHORYU_REPPA), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pB_cmd_17[33] = {  /* Ken: SA II Shinryuken, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(KEN_SHINRYUKEN), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pB_cmd_18[33] = {  /* Ken: SA III Shippu Jinraikyaku, 236236+K */
    CMD_RESET, 0, 0, CMD_WAZA(KEN_SHIPPU_JINRAIKYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pB_cmd_22[25] = {  /* Ken: Shoryuken, 623+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(KEN_SHORYUKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pB_cmd_23[25] = {  /* Ken: Hadoken, 236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(KEN_HADOKEN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pB_cmd_24[25] = {  /* Ken: Tatsumaki Senpukyaku, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(KEN_TATSUMAKI_SENPUKYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 pB_cmd_25[26] = {  /* Ken: special, punch (?) */
    CMD_RESET, CMD_LV_UP, 0, 23, 23, 23, 23, CMD_BT_CHG, CMD_EX_PUNCHES,
    CK_NONE,                /* disabled: placed ahead of the steps below */
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 pB_cmd_37[25] = {  /* Ken: air Tatsumaki Senpukyaku, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(KEN_AIR_TATSUMAKI_SENPUKYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

/* Sean's attack routines (routine_no[2]; 16 and up index pl12_exatt_table) */
#define SEAN_HADOU_BURST     16  /* Att_HADOUKEN */
#define SEAN_SHORYU_CANNON   17  /* Att_SHOURYUUREPPA */
#define SEAN_HYPER_TORNADO   18  /* Att_SLIDE_and_JUMP */
#define SEAN_RYUUBI_KYAKU    19  /* Att_ABISEGERI */
#define SEAN_ZENPOU_TENSHIN  20  /* Att_CHOUCHUURENGEKI */
#define SEAN_TORNADO         21  /* Att_SHOURYUUKEN */
#define SEAN_SEAN_TACKLE     22  /* Att_CHOUCHUURENGEKI */
#define SEAN_DRAGON_SMASH    24  /* Att_SENPUUKYAKU */

const s16 pC_cmd_16[33] = {  /* Sean: SA I Hadou Burst, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(SEAN_HADOU_BURST), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_17[33] = {  /* Sean: SA II Shoryu Cannon, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(SEAN_SHORYU_CANNON), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_18[33] = {  /* Sean: SA III Hyper Tornado, 236236+P */
    CMD_RESET, 0, 0, CMD_WAZA(SEAN_HYPER_TORNADO), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_LEVER(18, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_22[25] = {  /* Sean: Sean Tackle, 41236+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(SEAN_SEAN_TACKLE), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_BACK),
    CMD_LEVER_ANY(18, CMD_LV_DOWN),
    CMD_LEVER(18, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_23[25] = {  /* Sean: Dragon Smash, 623+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(SEAN_DRAGON_SMASH), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(1, CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_24[25] = {  /* Sean: Ryuubi Kyaku, 236+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(SEAN_RYUUBI_KYAKU), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_FORWARD),
    CMD_LEVER(12, CMD_LV_FORWARD),
    CMD_END,
};

const s16 pC_cmd_25[25] = {  /* Sean: Zenpou Tenshin (forward roll), 214+P */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(SEAN_ZENPOU_TENSHIN), CMD_BT_CHG, CMD_EX_PUNCHES,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 pC_cmd_26[25] = {  /* Sean: Tornado, 214+K */
    CMD_RESET, CMD_LV_UP, 0, CMD_WAZA(SEAN_TORNADO), CMD_BT_CHG, CMD_EX_KICKS,
    CMD_LEVER(0, CMD_LV_DOWN),
    CMD_LEVER(12, CMD_LV_DOWN | CMD_LV_BACK),
    CMD_LEVER(12, CMD_LV_BACK),
    CMD_END,
};

const s16 ukemi_time_tbl[17] = {
    0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
    7,
};

const char player_cmd_line_str0[20] = "UP    =    SHOT1 =\n";

const char player_cmd_line_str1[20] = "DOWN  =    SHOT2 =\n";

const char player_cmd_line_str2[20] = "LEFT  =    SHOT3 =\n";

const char player_cmd_line_str3[20] = "RIGHT =    SHOT4 =\n";

const char player_cmd_line_str4[20] = "DIR        SHOT5 =\n";

const char player_cmd_line_str5[12] = "SHOT6 =\n\0\x3F\x54\x54";

const char player_cmd_line_str6[8] = "SHOT6 =";

const char lvr_chk_line_str0[4] = "S \0\x23";

const char lvr_chk_line_str1[4] = "M \0\x21";

const char lvr_chk_line_str2[4] = "L \0\xFF";
