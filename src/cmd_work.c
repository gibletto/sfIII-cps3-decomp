/*
 * CMD_WORK.C  command input tables and work
 *
 * The per-character command list tables (pl_cmd_list_N, entry k the command list k: the pc_cmd, pX_cmd and
 * dm_cmd_xx lists of cmd_data.c), pl_CMD and player_cmd, which point at them for cmd_main_2.c, Com_Pl.c and
 * Com_Sub.c, and the key-assignment and lever-check display tables: initialised work RAM (section D); pl_cmd_list_6
 * has two more entries than the others. The command input work (section B): the lever history, the special move
 * recognisers, the computer player's commands.
 */

#include "types.h"
#include "structs.h"

extern const s16* pl_cmd_list_0[];
extern const s16* pl_cmd_list_1[];
extern const s16* pl_cmd_list_2[];
extern const s16* pl_cmd_list_3[];
extern const s16* pl_cmd_list_4[];
extern const s16* pl_cmd_list_5[];
extern const s16* pl_cmd_list_6[];
extern const s16* pl_cmd_list_7[];
extern const s16* pl_cmd_list_8[];
extern const s16* pl_cmd_list_9[];
extern const s16* pl_cmd_list_A[];
extern const s16* pl_cmd_list_B[];
extern const s16* pl_cmd_list_C[];
extern void* pl_CMD[];
extern const_s16_arr* player_cmd[];
extern TMLINE player_cmd_lines[];
extern u16 player_cmd_cells[][2];
extern s16 lvr_chk_tbl[][4];
extern TMLINE lvr_chk_lines[];
extern const char lvr_chk_line_str0[];
extern const char lvr_chk_line_str1[];
extern const char lvr_chk_line_str2[];
extern const char player_cmd_line_str0[];
extern const char player_cmd_line_str1[];
extern const char player_cmd_line_str2[];
extern const char player_cmd_line_str3[];
extern const char player_cmd_line_str4[];
extern const char player_cmd_line_str5[];
extern const char player_cmd_line_str6[];
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
extern const s16 p7_cmd_22[];
extern const s16 p7_cmd_23[];
extern const s16 p7_cmd_24[];
extern const s16 p7_cmd_25[];
extern const s16 p7_cmd_26[];
extern const s16 p7_cmd_33[];
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

/* 02004F8C */
/* provisional name */
const s16* pl_cmd_list_0[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p0_cmd_16, (const s16 *)p0_cmd_17, (const s16 *)p0_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p0_cmd_22, (const s16 *)p0_cmd_23,
    (const s16 *)p0_cmd_24, (const s16 *)p0_cmd_25, (const s16 *)p0_cmd_26, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 0200504C */
/* provisional name */
const s16* pl_cmd_list_1[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p1_cmd_16, (const s16 *)p1_cmd_17, (const s16 *)p1_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p1_cmd_22, (const s16 *)p1_cmd_23,
    (const s16 *)p1_cmd_24, (const s16 *)p1_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p1_cmd_46, (const s16 *)p1_cmd_47,
};

/* 0200510C */
/* provisional name */
const s16* pl_cmd_list_2[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p2_cmd_16, (const s16 *)p2_cmd_17, (const s16 *)p2_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p2_cmd_22, (const s16 *)p2_cmd_23,
    (const s16 *)p2_cmd_24, (const s16 *)p2_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)p2_cmd_37, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 020051CC */
/* provisional name */
const s16* pl_cmd_list_3[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p3_cmd_16, (const s16 *)p3_cmd_17, (const s16 *)p3_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p3_cmd_22, (const s16 *)p3_cmd_23,
    (const s16 *)p3_cmd_24, (const s16 *)p3_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 0200528C */
/* provisional name */
const s16* pl_cmd_list_4[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p4_cmd_16, (const s16 *)p4_cmd_17, (const s16 *)p4_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p4_cmd_22, (const s16 *)p4_cmd_23,
    (const s16 *)p4_cmd_24, (const s16 *)p4_cmd_25, (const s16 *)p4_cmd_26, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p4_cmd_46, (const s16 *)p4_cmd_47,
};

/* 0200534C */
/* provisional name */
const s16* pl_cmd_list_5[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p5_cmd_16, (const s16 *)p5_cmd_17, (const s16 *)p5_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p5_cmd_22, (const s16 *)p5_cmd_23,
    (const s16 *)p5_cmd_24, (const s16 *)p5_cmd_25, (const s16 *)p5_cmd_26, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p5_cmd_46, (const s16 *)p5_cmd_47,
};

/* 0200540C */
/* provisional name */
const s16* pl_cmd_list_6[50] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 020054D4 */
/* provisional name */
const s16* pl_cmd_list_7[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p7_cmd_16, (const s16 *)p7_cmd_17, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p7_cmd_22, (const s16 *)p7_cmd_23,
    (const s16 *)p7_cmd_24, (const s16 *)p7_cmd_25, (const s16 *)p7_cmd_26, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)p7_cmd_33, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)p7_cmd_37, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 02005594 */
/* provisional name */
const s16* pl_cmd_list_8[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p8_cmd_16, (const s16 *)p8_cmd_17, (const s16 *)p8_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p8_cmd_22, (const s16 *)p8_cmd_23,
    (const s16 *)p8_cmd_24, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 02005654 */
/* provisional name */
const s16* pl_cmd_list_9[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)p9_cmd_16, (const s16 *)p9_cmd_17, (const s16 *)p9_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)p9_cmd_22, (const s16 *)p9_cmd_23,
    (const s16 *)p9_cmd_24, (const s16 *)p9_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)p9_cmd_37, (const s16 *)p9_cmd_38, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 02005714 */
/* provisional name */
const s16* pl_cmd_list_A[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)pA_cmd_16, (const s16 *)pA_cmd_17, (const s16 *)pA_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)pA_cmd_22, (const s16 *)pA_cmd_23,
    (const s16 *)pA_cmd_24, (const s16 *)pA_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 020057D4 */
/* provisional name */
const s16* pl_cmd_list_B[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)pB_cmd_16, (const s16 *)pB_cmd_17, (const s16 *)pB_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)pB_cmd_22, (const s16 *)pB_cmd_23,
    (const s16 *)pB_cmd_24, (const s16 *)pB_cmd_25, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)pB_cmd_37, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 02005894 */
/* provisional name */
const s16* pl_cmd_list_C[48] = {
    (const s16 *)pc_cmd_00, (const s16 *)pc_cmd_01, (const s16 *)pc_cmd_02, (const s16 *)pc_cmd_03,
    (const s16 *)pc_cmd_04, (const s16 *)pc_cmd_05, (const s16 *)pc_cmd_06, (const s16 *)pc_cmd_07,
    (const s16 *)pc_cmd_08, (const s16 *)pc_cmd_09, (const s16 *)pc_cmd_10, (const s16 *)pc_cmd_11,
    (const s16 *)pc_cmd_12, (const s16 *)pc_cmd_13, (const s16 *)pc_cmd_14, (const s16 *)pc_cmd_15,
    (const s16 *)pC_cmd_16, (const s16 *)pC_cmd_17, (const s16 *)pC_cmd_18, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)pC_cmd_22, (const s16 *)pC_cmd_23,
    (const s16 *)pC_cmd_24, (const s16 *)pC_cmd_25, (const s16 *)pC_cmd_26, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
    (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx, (const s16 *)dm_cmd_xx,
};

/* 02005954 */
void* pl_CMD[13] = {
    pl_cmd_list_0, pl_cmd_list_1, pl_cmd_list_2, pl_cmd_list_3,
    pl_cmd_list_4, pl_cmd_list_5, pl_cmd_list_6, pl_cmd_list_7,
    pl_cmd_list_8, pl_cmd_list_9, pl_cmd_list_A, pl_cmd_list_B,
    pl_cmd_list_C,
};

/* 02005988 */
const_s16_arr* player_cmd[13] = {
    (const_s16_arr *)pl_cmd_list_0, (const_s16_arr *)pl_cmd_list_1,
    (const_s16_arr *)pl_cmd_list_2, (const_s16_arr *)pl_cmd_list_3,
    (const_s16_arr *)pl_cmd_list_4, (const_s16_arr *)pl_cmd_list_5,
    (const_s16_arr *)pl_cmd_list_6, (const_s16_arr *)pl_cmd_list_7,
    (const_s16_arr *)pl_cmd_list_8, (const_s16_arr *)pl_cmd_list_9,
    (const_s16_arr *)pl_cmd_list_A, (const_s16_arr *)pl_cmd_list_B,
    (const_s16_arr *)pl_cmd_list_C,
};

/* 020059BC */
/* text lines of the key-assignment display; nothing in the program refers to them (provisional name) */
TMLINE player_cmd_lines[12] = {
    { 1, 0xC, 0xE, 0, (u8 *)player_cmd_line_str0 },
    { 1, 0xD, 0xE, 0, (u8 *)player_cmd_line_str1 },
    { 1, 0xE, 0xE, 0, (u8 *)player_cmd_line_str2 },
    { 1, 0xF, 0xE, 0, (u8 *)player_cmd_line_str3 },
    { 1, 0x10, 0xE, 0, (u8 *)player_cmd_line_str4 },
    { 0xC, 0x11, 0xE, 0, (u8 *)player_cmd_line_str5 },
    { 0x17, 0xC, 0xE, 0, (u8 *)player_cmd_line_str0 },
    { 0x17, 0xD, 0xE, 0, (u8 *)player_cmd_line_str1 },
    { 0x17, 0xE, 0xE, 0, (u8 *)player_cmd_line_str2 },
    { 0x17, 0xF, 0xE, 0, (u8 *)player_cmd_line_str3 },
    { 0x17, 0x10, 0xE, 0, (u8 *)player_cmd_line_str4 },
    { 0x22, 0x11, 0xE, 0, (u8 *)player_cmd_line_str6 },
};

/* 02005A4C */
/* (x, y) cell positions; nothing in the program refers to them (provisional name) */
u16 player_cmd_cells[28][2] = {
    { 0xB, 3 }, { 0x1A, 3 }, { 0xB, 7 }, { 0x1A, 7 },
    { 0xF, 3 }, { 0x1E, 3 }, { 0xF, 7 }, { 0x1E, 7 },
    { 0xD, 3 }, { 0x1C, 3 }, { 0xD, 7 }, { 0x1C, 7 },
    { 0xB, 5 }, { 0x1A, 5 }, { 0xF, 5 }, { 0x1E, 5 },
    { 0xB, 9 }, { 0x1A, 9 }, { 0xD, 9 }, { 0x1C, 9 },
    { 0xF, 9 }, { 0x1E, 9 }, { 0xB, 0xA }, { 0x1A, 0xA },
    { 0xD, 0xA }, { 0x1C, 0xA }, { 0xF, 0xA }, { 0x1E, 0xA },
};

/* 02005ABC */
s16 lvr_chk_tbl[2][4] = {
    { 5, 6, 9, 10 }, { 1, 2, 4, 8 },
};

/* 02005ACC */
/* text lines of the lever-check display; nothing in the program refers to them (provisional name) */
TMLINE lvr_chk_lines[6] = {
    { 6, 0x13, 6, 0, (u8 *)lvr_chk_line_str0 },
    { 6, 0x13, 6, 0, (u8 *)lvr_chk_line_str1 },
    { 6, 0x13, 6, 0, (u8 *)lvr_chk_line_str2 },
    { 0x1D, 0x13, 6, 0, (u8 *)lvr_chk_line_str0 },
    { 0x1D, 0x13, 6, 0, (u8 *)lvr_chk_line_str1 },
    { 0x1D, 0x13, 6, 0, (u8 *)lvr_chk_line_str2 },
};

T_PL_LVR t_pl_lvr[2];  /* 0201ABA8 */
WAZA_WORK waza_work[2][48];  /* 0201AC30 */
/* after waza_work: nothing refers to it by name or address */
u8 waza_work_tail[2];  /* 0201B6B0 */
u16 sw_work;  /* 0201B6B2 */
s16* cmd_tbl_ptr;  /* 0201B6B4 */
s16 waza_type[2];  /* 0201B6B8 */
T_PL_LVR* chk_pl;  /* 0201B6BC */
WAZA_WORK* waza_ptr;  /* 0201B6C0 */
WORK_CP wcp[2];  /* 0201B6C4 */
s16 cmd_id;  /* 0201BDB0 */
PLW* cmd_pl;  /* 0201BDB4 */
/* after cmd_pl: nothing refers to it by name or address */
u8 cmd_pl_tail[4];  /* 0201BDB8 */
s16 eff_hit_flag[11];  /* 0201BDBC */
/* after eff_hit_flag: nothing refers to it by name or address */
u8 eff_hit_flag_tail[2];  /* 0201BDD2 */
