/*
 * DBG_WORK.C  debug menu text and work
 *
 * The text lines (TM_STRING) of the debug menus and object displays, and the tables of them that CMD_MAIN.c prints:
 * initialised work RAM (section D). The debug tools' work (section B): menu state, the recorder, the object look,
 * copy and edit buffers. A <name>_tail table holds the bytes between <name> and the next named variable.
 */

#include "types.h"
#include "structs.h"

extern TM_STRING dbg_menu_str[];
extern TM_STRING dbg_obj_info_str[];
extern TM_STRING dbg_obj_rel_str[];
extern TM_STRING dbg_all_char_str[];
extern TM_STRING dbg_edit_num_str[];
extern TM_STRING dbg_rec_menu_str[];
extern TM_STRING dbg_rec_clear_str[];
extern TM_STRING dbg_rec_nodata_str[];
extern TM_STRING dbg_hit_size_str[];
extern TM_STRING dbg_hit_part_str[];
extern TM_STRING dbg_cg_head_str[];
extern TM_STRING dbg_cg_att_str[];
extern TM_STRING dbg_cg_rival_str[];
extern TM_STRING dbg_cgd_info_str[];
extern TM_STRING dbg_att_data_str[];
extern TM_STRING dbg_hud_clr_str[];
extern TM_STRING dbg_hud_clr_mid_str[];
extern TM_STRING dbg_hud_clr_low_str[];
extern TM_STRING dbg_hud_clr_bottom_str[];
extern TM_STRING dbg_cm_label_str[];
extern TM_STRING dbg_cgd_type_str[];
extern TM_STRING dbg_pat_status_str[];
extern TM_STRING dbg_cg_group_str[];
extern TM_STRING dbg_preview_group_str[];
extern TM_STRING dbg_edit_group_str[];
extern TM_STRING dbg_extdat_str[];
extern TM_STRING dbg_eftype_names[];
extern TM_STRING dbg_eftype_s_str[];
extern TM_STRING dbg_eftype_usemj_str[];
extern TM_STRING dbg_cancel_on_str[];
extern TM_STRING dbg_cancel_off_str[];
extern TM_STRING dbg_koc_cmlp_str[];
extern TM_STRING dbg_koc_cml2_str[];
extern TM_STRING dbg_koc_cmsw_str[];
extern TM_STRING dbg_koc_cmja_str[];
extern TM_STRING dbg_koc_cmoa_str[];
extern TM_STRING dbg_koc_str[];
extern TM_STRING dbg_waza_kind_str[];
extern TM_STRING dbg_char_name_str[];
extern TM_STRING dbg_act_kind_str[];
extern TM_STRING * dbg_act_name_tbl[];
extern u32 * dbg_pl_char_tbl[][9];
extern const char str_1DATA_SH5[];
extern const char str_ADD_ARTS[];
extern const char str_AFRICA_1[];
extern const char str_AFRICA_1_2[];
extern const char str_AFRICA_2[];
extern const char str_AFRICA_2_2[];
extern const char str_AIR_L[];
extern const char str_AIR_M[];
extern const char str_AIR_SP[];
extern const char str_AIR_S[];
extern const char str_ALEX[];
extern const char str_ALEX_2[];
extern const char str_ALEX_B_D_A[];
extern const char str_ALEX_B_D_B[];
extern const char str_ALEX_B_D_C[];
extern const char str_ALEX_B_D_D[];
extern const char str_ALL[];
extern const char str_ALL_CHARACTER[];
extern const char str_APPEAR_1[];
extern const char str_APPEAR_2[];
extern const char str_APPEAR_3[];
extern const char str_APPEAR_4[];
extern const char str_APPEAR_5[];
extern const char str_APPEAR_6[];
extern const char str_APPEAR_7[];
extern const char str_APPEAR_8[];
extern const char str_APPEAR_JUNBI_1[];
extern const char str_APPEAR_JUNBI_2[];
extern const char str_APPEAR_JUNBI_3[];
extern const char str_APPEAR_JUNBI_4[];
extern const char str_APPEAR_JUNBI_5[];
extern const char str_APPEAR_JUNBI_6[];
extern const char str_APPEAR_JUNBI_7[];
extern const char str_APPEAR_JUNBI_8[];
extern const char str_ASHIBARAI_A[];
extern const char str_ASHIBARAI_B[];
extern const char str_ASHIBARAI_C[];
extern const char str_ASHIBARAI_D[];
extern const char str_ASIBRI_MAKE_A[];
extern const char str_ASIBRI_MAKE_B[];
extern const char str_ASIBRI_MAKE_C[];
extern const char str_ASIBRI_MAKE_D[];
extern const char str_ASIB_TN_MAKE_A[];
extern const char str_ASIB_TN_MAKE_B[];
extern const char str_ASIB_TN_MAKE_C[];
extern const char str_ASIB_TN_MAKE_D[];
extern const char str_ASI_B_SIRIMOTI[];
extern const char str_ATTACK[];
extern const char str_ATTACK_1[];
extern const char str_ATTACK_1_L[];
extern const char str_ATTACK_1_M[];
extern const char str_ATTACK_1_SP[];
extern const char str_ATTACK_1_S[];
extern const char str_ATTACK_2[];
extern const char str_ATTACK_2_L[];
extern const char str_ATTACK_2_M[];
extern const char str_ATTACK_2_SP[];
extern const char str_ATTACK_2_S[];
extern const char str_ATTACK_3_L[];
extern const char str_ATTACK_3_M[];
extern const char str_ATTACK_3_SP[];
extern const char str_ATTACK_3_S[];
extern const char str_ATTACK_4_L[];
extern const char str_ATTACK_4_M[];
extern const char str_ATTACK_4_SP[];
extern const char str_ATTACK_4_S[];
extern const char str_ATTACK_5_L[];
extern const char str_ATTACK_5_M[];
extern const char str_ATTACK_5_SP[];
extern const char str_ATTACK_5_S[];
extern const char str_ATTACK_6_L[];
extern const char str_ATTACK_6_M[];
extern const char str_ATTACK_6_SP[];
extern const char str_ATTACK_6_S[];
extern const char str_ATTACK_H[];
extern const char str_ATT_IX[];
extern const char str_AT[];
extern const char str_AT_LEVEL[];
extern const char str_A[];
extern const char str_BACK[];
extern const char str_BACK_WALK[];
extern const char str_BASE[];
extern const char str_BCP00[];
extern const char str_BCP01[];
extern const char str_BCP02[];
extern const char str_BCP03[];
extern const char str_BCP04[];
extern const char str_BCP05[];
extern const char str_BCP06[];
extern const char str_BCP07[];
extern const char str_BCP08[];
extern const char str_BCP09[];
extern const char str_BCP10[];
extern const char str_BCP11[];
extern const char str_BCP12[];
extern const char str_BCP13[];
extern const char str_BCP14[];
extern const char str_BCP15[];
extern const char str_BCP20[];
extern const char str_BCP21[];
extern const char str_BCP22[];
extern const char str_BCP23[];
extern const char str_BCP24[];
extern const char str_BCP25[];
extern const char str_BCP26[];
extern const char str_BCP27[];
extern const char str_BCP28[];
extern const char str_BCP29[];
extern const char str_BCP30[];
extern const char str_BCP31[];
extern const char str_BCP32[];
extern const char str_BCP33[];
extern const char str_BCP34[];
extern const char str_BCP35[];
extern const char str_BCP36[];
extern const char str_BCP37[];
extern const char str_BCP38[];
extern const char str_BCP39[];
extern const char str_BCP40[];
extern const char str_BCP41[];
extern const char str_BCP42[];
extern const char str_BCP43[];
extern const char str_BCP44[];
extern const char str_BCP45[];
extern const char str_BCP46[];
extern const char str_BCP47[];
extern const char str_BCP48[];
extern const char str_BCP49[];
extern const char str_BCP50[];
extern const char str_BCP51[];
extern const char str_BCP52[];
extern const char str_BCP53[];
extern const char str_BCP54[];
extern const char str_BCP55[];
extern const char str_BCP56[];
extern const char str_BCP57[];
extern const char str_BCP58[];
extern const char str_BCP59[];
extern const char str_BCP60[];
extern const char str_BCP61[];
extern const char str_BCP62[];
extern const char str_BCP63[];
extern const char str_BCP64[];
extern const char str_BCP65[];
extern const char str_BCP66[];
extern const char str_BCP67[];
extern const char str_BCP68[];
extern const char str_BCP69[];
extern const char str_BCP70[];
extern const char str_BCP71[];
extern const char str_BCP72[];
extern const char str_BCP73[];
extern const char str_BCP74[];
extern const char str_BCP75[];
extern const char str_BCP76[];
extern const char str_BCP77[];
extern const char str_BCP78[];
extern const char str_BCP79[];
extern const char str_BCP80[];
extern const char str_BCP81[];
extern const char str_BCP82[];
extern const char str_BCP83[];
extern const char str_BCP84[];
extern const char str_BCP85[];
extern const char str_BCP86[];
extern const char str_BCP87[];
extern const char str_BCP88[];
extern const char str_BCP89[];
extern const char str_BCP90[];
extern const char str_BCP91[];
extern const char str_BCP92[];
extern const char str_BCP93[];
extern const char str_BEFORE[];
extern const char str_BG_BLOCK[];
extern const char str_BLOCK_NO[];
extern const char str_BODY_BROW_L[];
extern const char str_BODY_BROW_M[];
extern const char str_BODY_BROW_SP[];
extern const char str_BODY_BROW_S[];
extern const char str_BODY_H[];
extern const char str_BODY_SLAM_A[];
extern const char str_BODY_SLAM_B[];
extern const char str_BODY_SLAM_C[];
extern const char str_BODY_SLAM_D[];
extern const char str_BODY_UPPER_A[];
extern const char str_BODY_UPPER_B[];
extern const char str_BODY_UPPER_C[];
extern const char str_BODY_UPPER_D[];
extern const char str_BODY_UPPER_L[];
extern const char str_BODY_UPPER_M[];
extern const char str_BODY_UPPER_SP[];
extern const char str_BODY_UPPER_S[];
extern const char str_BOSS_STAGE_OBJ[];
extern const char str_BRAZIL[];
extern const char str_BRAZIL_2[];
extern const char str_BREAST[];
extern const char str_BT[];
extern const char str_BUTTOBI[];
extern const char str_BUTTOBI_2[];
extern const char str_BUTT_PAT[];
extern const char str_BUTT_TYPE[];
extern const char str_B_JUMP_K_L_A[];
extern const char str_B_JUMP_K_L_B[];
extern const char str_B_JUMP_K_M_A[];
extern const char str_B_JUMP_K_M_B[];
extern const char str_B_JUMP_K_S_A[];
extern const char str_B_JUMP_K_S_B[];
extern const char str_B_JUMP_P_L_A[];
extern const char str_B_JUMP_P_L_B[];
extern const char str_B_JUMP_P_M_A[];
extern const char str_B_JUMP_P_M_B[];
extern const char str_B_JUMP_P_S_A[];
extern const char str_B_JUMP_P_S_B[];
extern const char str_CANCEL_SH6[];
extern const char str_CATCH[];
extern const char str_CATCH_1[];
extern const char str_CATCH_2[];
extern const char str_CATCH_3[];
extern const char str_CATCH_4[];
extern const char str_CATCH_5[];
extern const char str_CATCH_HIZAGERI[];
extern const char str_CATCH_NAGE[];
extern const char str_CATCH_TOBIKOE[];
extern const char str_CATCH_n[];
extern const char str_CAUGHT[];
extern const char str_CAUGHT_H[];
extern const char str_CAUGHT_n[];
extern const char str_CA[];
extern const char str_CB[];
extern const char str_CGD1[];
extern const char str_CGD2[];
extern const char str_CGD3[];
extern const char str_CGD_TYPE[];
extern const char str_CG_ADD_XY[];
extern const char str_CG_ATT_IX[];
extern const char str_CG_CANCEL[];
extern const char str_CG_CTR[];
extern const char str_CG_EFFECT[];
extern const char str_CG_EFTYPE[];
extern const char str_CG_EXTDAT[];
extern const char str_CG_FLIP[];
extern const char str_CG_HIT_IX[];
extern const char str_CG_NIX[];
extern const char str_CG_NUMBER[];
extern const char str_CG_OLC_IX[];
extern const char str_CG_RIVAL[];
extern const char str_CG_SE[];
extern const char str_CG_STATUS[];
extern const char str_CG_TYPE[];
extern const char str_CHAINA_1[];
extern const char str_CHAINA_1_OBJ_2[];
extern const char str_CHAINA_2[];
extern const char str_CHAINA_2_OBJ_2[];
extern const char str_CMCF[];
extern const char str_CMCR[];
extern const char str_CMJ2[];
extern const char str_CMJ3[];
extern const char str_CMJ4[];
extern const char str_CMJA[];
extern const char str_CML2[];
extern const char str_CMLP[];
extern const char str_CMMD[];
extern const char str_CMMS[];
extern const char str_CMOA[];
extern const char str_CMSW[];
extern const char str_CMYD[];
extern const char str_CODE_H[];
extern const char str_CURRENT[];
extern const char str_CURRENT_2[];
extern const char str_CU[];
extern const char str_C[];
extern const char str_DAMAGE[];
extern const char str_DASH_HUMIKOMI[];
extern const char str_DASH_TOBINOKI[];
extern const char str_DATA_NOTHING[];
extern const char str_DELETE_ALL_SH4[];
extern const char str_DENKI_A[];
extern const char str_DENKI_B[];
extern const char str_DENKI_C[];
extern const char str_DENKI_D[];
extern const char str_DIR[];
extern const char str_DIR_ATT[];
extern const char str_DM[];
extern const char str_DUDDLY[];
extern const char str_DUDLEY[];
extern const char str_D[];
extern const char str_D_P_GUARD_K_L[];
extern const char str_D_P_GUARD_K_M[];
extern const char str_D_P_GUARD_K_S[];
extern const char str_D_P_GUARD_P_L[];
extern const char str_D_P_GUARD_P_M[];
extern const char str_D_P_GUARD_P_S[];
extern const char str_EDIT_INT[];
extern const char str_EDIT_NUM[];
extern const char str_EFF01_CHAR[];
extern const char str_EFF13_CHAR[];
extern const char str_EFFECT[];
extern const char str_ELENA[];
extern const char str_ELENA_2[];
extern const char str_ENFLAND_OBJ[];
extern const char str_ENGLAND_1[];
extern const char str_ENGLAND_2[];
extern const char str_ETC[];
extern const char str_ETC_2[];
extern const char str_ETC_3[];
extern const char str_EX[];
extern const char str_FACE_A[];
extern const char str_FACE_B[];
extern const char str_FACE_C[];
extern const char str_FACE_D[];
extern const char str_FACE_L[];
extern const char str_FACE_M[];
extern const char str_FACE_SP[];
extern const char str_FACE_S[];
extern const char str_FLANKEN_S_A[];
extern const char str_FLANKEN_S_B[];
extern const char str_FLANKEN_S_C[];
extern const char str_FLANKEN_S_D[];
extern const char str_FLIP[];
extern const char str_FLIP_ED[];
extern const char str_FOOK_OKU_L[];
extern const char str_FOOK_OKU_M[];
extern const char str_FOOK_OKU_SP[];
extern const char str_FOOK_OKU_S[];
extern const char str_FOOK_TEMAE_L[];
extern const char str_FOOK_TEMAE_M[];
extern const char str_FOOK_TEMAE_SP[];
extern const char str_FOOK_TEMAE_S[];
extern const char str_FRONT_WALK[];
extern const char str_FURUDERA_OBJ[];
extern const char str_FUSHIN_K_L[];
extern const char str_FUSHIN_K_M[];
extern const char str_FUSHIN_K_S[];
extern const char str_FUSHIN_P_L[];
extern const char str_FUSHIN_P_M[];
extern const char str_FUSHIN_P_S[];
extern const char str_F_JUMP_K_L_A[];
extern const char str_F_JUMP_K_L_B[];
extern const char str_F_JUMP_K_M_A[];
extern const char str_F_JUMP_K_M_B[];
extern const char str_F_JUMP_K_S_A[];
extern const char str_F_JUMP_K_S_B[];
extern const char str_F_JUMP_P_L_A[];
extern const char str_F_JUMP_P_L_B[];
extern const char str_F_JUMP_P_M_A[];
extern const char str_F_JUMP_P_M_B[];
extern const char str_F_JUMP_P_S_A[];
extern const char str_F_JUMP_P_S_B[];
extern const char str_GERMANY[];
extern const char str_GERMANY_OBJ[];
extern const char str_GILL[];
extern const char str_GILL_2[];
extern const char str_GREECE[];
extern const char str_GUARD[];
extern const char str_GUARD_AIR[];
extern const char str_GUARD_AIR_2[];
extern const char str_GUARD_DOWN[];
extern const char str_GUARD_DOWN_2[];
extern const char str_GUARD_HEAD[];
extern const char str_GUARD_HEAD_2[];
extern const char str_GUARD_UP[];
extern const char str_GUARD_UP_2[];
extern const char str_HANASARE[];
extern const char str_HAND[];
extern const char str_HANEAGARI_A[];
extern const char str_HANEAGARI_B[];
extern const char str_HANEAGARI_C[];
extern const char str_HANEAGARI_D[];
extern const char str_HARAIGOSHI_A[];
extern const char str_HARAIGOSHI_B[];
extern const char str_HARAIGOSHI_C[];
extern const char str_HARAIGOSHI_D[];
extern const char str_HEAD[];
extern const char str_HISS[];
extern const char str_HIT[];
extern const char str_HIT_IX[];
extern const char str_HIT_RANGE[];
extern const char str_HOSEI_H[];
extern const char str_HS_ME[];
extern const char str_HS_YOU[];
extern const char str_HUGO[];
extern const char str_HUMI_ASIB_A[];
extern const char str_HUMI_ASIB_B[];
extern const char str_HUMI_ASIB_C[];
extern const char str_HUMI_ASIB_D[];
extern const char str_HURIMUKI[];
extern const char str_HUSHIN_AIR[];
extern const char str_HUSHIN_DOWN[];
extern const char str_HUSHIN_HEAD[];
extern const char str_HUSHIN_UP[];
extern const char str_H[];
extern const char str_H_2[];
extern const char str_H_3[];
extern const char str_IBUKI[];
extern const char str_IBUKI_2[];
extern const char str_IMPACT[];
extern const char str_INDEX[];
extern const char str_INTERRUT[];
extern const char str_INT_END[];
extern const char str_IPPONZEOI_A[];
extern const char str_IPPONZEOI_B[];
extern const char str_IPPONZEOI_C[];
extern const char str_IPPONZEOI_D[];
extern const char str_JAPAN_1[];
extern const char str_JAPAN_1_OBJ[];
extern const char str_JAPAN_2[];
extern const char str_JAPAN_2_OBJ[];
extern const char str_JUDGMENT_LOSE[];
extern const char str_JUDGMENT_WAIT[];
extern const char str_JUDGMENT_WIN[];
extern const char str_JUMP_BACK[];
extern const char str_JUMP_FRONT[];
extern const char str_JUMP_JUNBI[];
extern const char str_JUMP_VERTICAL[];
extern const char str_KAGAMI_B_WALK[];
extern const char str_KAGAMI_F_WALK[];
extern const char str_KAGAMI_KAMAE[];
extern const char str_KAGAMI_K_A[];
extern const char str_KAGAMI_K_B[];
extern const char str_KAGAMI_K_C[];
extern const char str_KAGAMI_L[];
extern const char str_KAGAMI_M[];
extern const char str_KAGAMI_P_A[];
extern const char str_KAGAMI_P_B[];
extern const char str_KAGAMI_P_C[];
extern const char str_KAGAMI_SP[];
extern const char str_KAGAMI_S[];
extern const char str_KAGAMI_TURN[];
extern const char str_KAGAMU[];
extern const char str_KAMAE[];
extern const char str_KEN[];
extern const char str_KEN_2[];
extern const char str_KGM_TATAKI_L[];
extern const char str_KGM_TATAKI_M[];
extern const char str_KGM_TATAKI_SP[];
extern const char str_KGM_TATAKI_S[];
extern const char str_KGM_TTKI_V_L[];
extern const char str_KGM_TTKI_V_M[];
extern const char str_KGM_TTKI_V_SP[];
extern const char str_KGM_TTKI_V_S[];
extern const char str_KIND_WAZA[];
extern const char str_KIRIMOMI[];
extern const char str_KIRIMOMI_A[];
extern const char str_KIRIMOMI_B[];
extern const char str_KIRIMOMI_C[];
extern const char str_KIRIMOMI_D[];
extern const char str_KISHINRIKI_A[];
extern const char str_KISHINRIKI_B[];
extern const char str_KISHINRIKI_C[];
extern const char str_KISHINRIKI_D[];
extern const char str_KOC_IX_PT_Nix[];
extern const char str_KOC_IX_PT_Nix_2[];
extern const char str_KUNOJI_A[];
extern const char str_KUNOJI_BUTTOBI[];
extern const char str_KUNOJI_B[];
extern const char str_KUNOJI_C[];
extern const char str_KUNOJI_D[];
extern const char str_KUNOJI_NOKE_A[];
extern const char str_KUNOJI_NOKE_B[];
extern const char str_KUNOJI_NOKE_C[];
extern const char str_KUNOJI_NOKE_D[];
extern const char str_KUSSHIN_FAST[];
extern const char str_KUSSHIN_SLOW[];
extern const char str_KYOTO_1[];
extern const char str_KYOTO_2[];
extern const char str_KYOTO_3[];
extern const char str_LEG[];
extern const char str_LOSE_KAGAMI[];
extern const char str_LOSE_NO_STAND[];
extern const char str_LOSE_SONABA[];
extern const char str_L_KICK_A[];
extern const char str_L_KICK_B[];
extern const char str_L_KICK_C[];
extern const char str_L_PUNCH_A[];
extern const char str_L_PUNCH_B[];
extern const char str_L_PUNCH_C[];
extern const char str_MLD[];
extern const char str_MLF[];
extern const char str_MLN[];
extern const char str_MLR[];
extern const char str_MLU[];
extern const char str_MONKEY_FLIP_A[];
extern const char str_MONKEY_FLIP_B[];
extern const char str_MONKEY_FLIP_C[];
extern const char str_MONKEY_FLIP_D[];
extern const char str_MOTION[];
extern const char str_M[];
extern const char str_M_2[];
extern const char str_M_KICK_A[];
extern const char str_M_KICK_B[];
extern const char str_M_KICK_C[];
extern const char str_M_PUNCH_A[];
extern const char str_M_PUNCH_B[];
extern const char str_M_PUNCH_C[];
extern const char str_NAGERARE_KAIHI[];
extern const char str_NECRO[];
extern const char str_NECRO_2[];
extern const char str_NEKOROBI_L[];
extern const char str_NEKOROBI_M[];
extern const char str_NEKOROBI_SP[];
extern const char str_NEKOROBI_S[];
extern const char str_NM[];
extern const char str_NM_BUTTOBI_A[];
extern const char str_NM_BUTTOBI_B[];
extern const char str_NM_BUTTOBI_C[];
extern const char str_NM_BUTTOBI_D[];
extern const char str_NM_DM[];
extern const char str_NM_JUMP_AT[];
extern const char str_NOBASITA_TE_L[];
extern const char str_NOBASITA_TE_M[];
extern const char str_NOBASITA_TE_SP[];
extern const char str_NOBASITA_TE_S[];
extern const char str_NOKEZORI_A[];
extern const char str_NOKEZORI_B[];
extern const char str_NOKEZORI_C[];
extern const char str_NOKEZORI_D[];
extern const char str_NORMAL[];
extern const char str_NOUTEN_L[];
extern const char str_NOUTEN_M[];
extern const char str_NOUTEN_SP[];
extern const char str_NOUTEN_S[];
extern const char str_NO_EDIT[];
extern const char str_NUM_END[];
extern const char str_N_Y_1[];
extern const char str_N_Y_1_OBJ_2[];
extern const char str_N_Y_2[];
extern const char str_N_Y_2_256_OBJ[];
extern const char str_N_Y_2_64_OBJ[];
extern const char str_OBJECT_EDIT[];
extern const char str_OBJECT_EDIT_2[];
extern const char str_OBJECT_LOOK[];
extern const char str_OBJECT_TEST[];
extern const char str_OKIAGARI[];
extern const char str_OKIAGARI_B[];
extern const char str_OKIAGARI_F[];
extern const char str_OKIAGARI_K_L[];
extern const char str_OKIAGARI_K_M[];
extern const char str_OKIAGARI_K_S[];
extern const char str_OKIAGARI_P_L[];
extern const char str_OKIAGARI_P_M[];
extern const char str_OKIAGARI_P_S[];
extern const char str_ORO[];
extern const char str_ORO_2[];
extern const char str_PARING_AIR_B[];
extern const char str_PARING_AIR_F[];
extern const char str_PARING_DOWN[];
extern const char str_PARING_HEAD[];
extern const char str_PARING_UP[];
extern const char str_PATTERN[];
extern const char str_PAT_ST[];
extern const char str_PA[];
extern const char str_PB[];
extern const char str_PIYO[];
extern const char str_PIYO_n[];
extern const char str_PLAYER[];
extern const char str_PLEF[];
extern const char str_PL_13[];
extern const char str_PL_14[];
extern const char str_PL_15[];
extern const char str_POS_X_H[];
extern const char str_POS_Y_H[];
extern const char str_POW[];
extern const char str_Pa[];
extern const char str_QUAKE[];
extern const char str_REACTION[];
extern const char str_REL_X_H[];
extern const char str_REL_Y_H[];
extern const char str_REVISE_X_H[];
extern const char str_REVISE_Y_H[];
extern const char str_ROSIA_OBJ[];
extern const char str_RUSSIA[];
extern const char str_RYU[];
extern const char str_RYU_2[];
extern const char str_R[];
extern const char str_S1[];
extern const char str_S2[];
extern const char str_S3[];
extern const char str_S4[];
extern const char str_S5[];
extern const char str_S6[];
extern const char str_SA[];
extern const char str_SEAN[];
extern const char str_SEAN_2[];
extern const char str_SHIMEOTASARE[];
extern const char str_SINSYOURYU_A[];
extern const char str_SINSYOURYU_B[];
extern const char str_SINSYOURYU_C[];
extern const char str_SINSYOURYU_D[];
extern const char str_SIZE_X_H[];
extern const char str_SIZE_Y_H[];
extern const char str_SNAKE_FANG_A[];
extern const char str_SNAKE_FANG_B[];
extern const char str_SNAKE_FANG_C[];
extern const char str_SNAKE_FANG_D[];
extern const char str_SPLASH_M_A[];
extern const char str_SPLASH_M_B[];
extern const char str_SPLASH_M_C[];
extern const char str_SPLASH_M_D[];
extern const char str_SP_APPEAR_1[];
extern const char str_SP_APPEAR_2[];
extern const char str_SP_APPEAR_3[];
extern const char str_SP_APPEAR_4[];
extern const char str_SP_APPEAR_5[];
extern const char str_SP_APPEAR_6[];
extern const char str_SP_APPEAR_7[];
extern const char str_SP_APPEAR_8[];
extern const char str_SP_AT[];
extern const char str_SP_JUMP_BACK[];
extern const char str_SP_JUMP_FRONT[];
extern const char str_SP_JUMP_JUNBI[];
extern const char str_SP_JUMP_V[];
extern const char str_SP_TECH[];
extern const char str_SP_WIN_1[];
extern const char str_SP_WIN_2[];
extern const char str_SP_WIN_3[];
extern const char str_SP_WIN_4[];
extern const char str_SP_WIN_5[];
extern const char str_SP_WIN_6[];
extern const char str_SP_WIN_7[];
extern const char str_SP_WIN_8[];
extern const char str_STAGE[];
extern const char str_STAND_UP[];
extern const char str_S[];
extern const char str_S_JUMP_BACK[];
extern const char str_S_JUMP_FRONT[];
extern const char str_S_JUMP_V[];
extern const char str_S_KICK_A[];
extern const char str_S_KICK_B[];
extern const char str_S_KICK_C[];
extern const char str_S_PUNCH_A[];
extern const char str_S_PUNCH_B[];
extern const char str_S_PUNCH_C[];
extern const char str_TATAKITUKERARE[];
extern const char str_TATAKI_AIR_A[];
extern const char str_TATAKI_AIR_B[];
extern const char str_TATAKI_AIR_C[];
extern const char str_TATAKI_AIR_D[];
extern const char str_TATAKI_L[];
extern const char str_TATAKI_M[];
extern const char str_TATAKI_SP[];
extern const char str_TATAKI_S[];
extern const char str_TATAKI_V_L[];
extern const char str_TATAKI_V_M[];
extern const char str_TATAKI_V_SP[];
extern const char str_TATAKI_V_S[];
extern const char str_TEN_IX[];
extern const char str_TOMOE_ORO_A[];
extern const char str_TOMOE_ORO_B[];
extern const char str_TOMOE_ORO_C[];
extern const char str_TOMOE_ORO_D[];
extern const char str_TOMOE_RYU_A[];
extern const char str_TOMOE_RYU_B[];
extern const char str_TOMOE_RYU_C[];
extern const char str_TOMOE_RYU_D[];
extern const char str_TOUKETSU_A[];
extern const char str_TOUKETSU_B[];
extern const char str_TOUKETSU_C[];
extern const char str_TOUKETSU_D[];
extern const char str_TRUNK_1[];
extern const char str_TRUNK_2[];
extern const char str_TTKI_V_AIR_A[];
extern const char str_TTKI_V_AIR_B[];
extern const char str_TTKI_V_AIR_C[];
extern const char str_TTKI_V_AIR_D[];
extern const char str_TUKAMIKAKARI_1[];
extern const char str_TUKAMIKAKARI_2[];
extern const char str_TUKAMIKAKARI_3[];
extern const char str_TUKAMIKAKARI_4[];
extern const char str_TUKAMIKAKARI_A[];
extern const char str_TUKAMIKAKARI_B[];
extern const char str_TUKAMIKAKARI_C_2[];
extern const char str_TUKAMIKAKARI_D_2[];
extern const char str_TUKAMIKAKARI_E_2[];
extern const char str_TUKAMIKAKARI_F_2[];
extern const char str_TUNNOMERI_A[];
extern const char str_TUNNOMERI_B[];
extern const char str_TUNNOMERI_C[];
extern const char str_TUNNOMERI_D[];
extern const char str_UKEMI_MOVE_F[];
extern const char str_UKEMI_MOVE_R[];
extern const char str_UNION[];
extern const char str_UPPER_A[];
extern const char str_UPPER_B[];
extern const char str_UPPER_C[];
extern const char str_UPPER_D[];
extern const char str_UPPER_L[];
extern const char str_UPPER_M[];
extern const char str_UPPER_SP[];
extern const char str_UPPER_S[];
extern const char str_UP_P_GUARD_K_L[];
extern const char str_UP_P_GUARD_K_M[];
extern const char str_UP_P_GUARD_K_S[];
extern const char str_UP_P_GUARD_P_L[];
extern const char str_UP_P_GUARD_P_M[];
extern const char str_UP_P_GUARD_P_S[];
extern const char str_USEMJ[];
extern const char str_VS_ID[];
extern const char str_V_JUMP_K_L_A[];
extern const char str_V_JUMP_K_L_B[];
extern const char str_V_JUMP_K_M_A[];
extern const char str_V_JUMP_K_M_B[];
extern const char str_V_JUMP_K_S_A[];
extern const char str_V_JUMP_K_S_B[];
extern const char str_V_JUMP_P_L_A[];
extern const char str_V_JUMP_P_L_B[];
extern const char str_V_JUMP_P_M_A[];
extern const char str_V_JUMP_P_M_B[];
extern const char str_V_JUMP_P_S_A[];
extern const char str_V_JUMP_P_S_B[];
extern const char str_WALK_END[];
extern const char str_WCA[];
extern const char str_WCA_IX[];
extern const char str_WIN_1[];
extern const char str_WIN_2[];
extern const char str_WIN_3[];
extern const char str_WIN_4[];
extern const char str_WIN_5[];
extern const char str_WIN_6[];
extern const char str_WIN_7[];
extern const char str_WIN_8[];
extern const char str_YANG[];
extern const char str_YOKE_PAT[];
extern const char str_YOKE_TYPE[];
extern const char str_YUN[];
extern const char str_YUN_2[];
extern const char str_YUN_YAN[];
extern const char str_ZANNEN_1[];
extern const char str_ZANNEN_2[];
extern const char str_ZANNEN_3[];
extern const char str_ZANNEN_4[];
extern const char str_ZANNEN_5[];
extern const char str_ZANNEN_6[];
extern const char str_ZANNEN_7[];
extern const char str_ZANNEN_8[];
extern const char str_ZOKUSEI[];
extern const char str_ZU_FLAG[];
extern const char str_a[];
extern const char str_a_2[];
extern const char str_blank_10[];
extern const char str_blank_11[];
extern const char str_blank_12[];
extern const char str_blank_13[];
extern const char str_blank_14[];
extern const char str_blank_4[];
extern const char str_blank_5[];
extern const char str_blank_6[];
extern const char str_blank_7[];
extern const char str_blank_8[];
extern const char str_blank_9[];
extern const char str_c[];
extern const char str_c_2[];
extern const char str_d[];
extern const char str_d_2[];
extern const char str_empty_9[];
extern const char str_h[];
extern const char str_h_2[];
extern const char str_hsA[];
extern const char str_hsC[];
extern const char str_huA[];
extern const char str_m[];
extern const char str_m_2[];
extern const char str_nmA[];
extern const char str_nmC[];
extern const char str_paA[];
extern const char str_r[];
extern const char str_r_2[];
extern const char str_s[];
extern const char str_s_2[];
extern const char str_saA[];
extern const char str_saC[];
extern const char str_sl_00[];
extern const char str_sl_10[];
extern const char str_sl_12[];
extern const char str_sl_20[];
extern const char str_sl_22[];
extern const char str_sl_30[];
extern const char str_sl_32[];
extern const char str_sl_40[];
extern const char str_sl_42[];
extern const char str_sl_44[];
extern const char str_sl_50[];
extern const char str_sl_52[];
extern const char str_sl_54[];
extern const char str_sl_60[];
extern const char str_sl_62[];
extern const char str_sl_64[];
extern const char str_sl_70[];
extern const char str_sl_80[];
extern const char str_sl_82[];
extern const char str_sl_90[];
extern const u32 ag_char_table_0[], ag_char_table_1[], ag_char_table_2[], ag_char_table_3[], ag_char_table_4[], ag_char_table_5[], ag_char_table_6[];
extern const u32 ag_char_table_0[];
extern const u32 ag_char_table_1[];
extern const u32 ag_char_table_2[];
extern const u32 ag_char_table_3[];
extern const u32 ag_char_table_4[];
extern const u32 ag_char_table_5[];
extern const u32 ag_face_panel_table[];
extern const u32 alex_atca[];
extern const u32 alex_btca[];
extern const u32 alex_caca[];
extern const u32 alex_cuca[];
extern const u32 alex_dmca[];
extern const u32 alex_exca[];
extern const u32 alex_nmca[];
extern const u32 alex_saca[];
extern const u32 alex_yuca[];
extern const u32 brz_char_table[];
extern const u32 direct_03_char_table[];
extern const u32 dudley_atca[];
extern const u32 dudley_btca[];
extern const u32 dudley_caca[];
extern const u32 dudley_cuca[];
extern const u32 dudley_dmca[];
extern const u32 dudley_exca[];
extern const u32 dudley_nmca[];
extern const u32 dudley_saca[];
extern const u32 dudley_yuca[];
extern const u32 ef01_char_table[];
extern const u32 ef13_char_table[];
extern const u32 eff45_char_table[];
extern const u32 eff77_char_table[];
extern const u32 eff86_char_table[];
extern const u32 effH3_char_table[];
extern const u32 elena_atca[];
extern const u32 elena_btca[];
extern const u32 elena_caca[];
extern const u32 elena_cuca[];
extern const u32 elena_dmca[];
extern const u32 elena_exca[];
extern const u32 elena_nmca[];
extern const u32 elena_saca[];
extern const u32 elena_yuca[];
extern const u32 etc2_char_table[];
extern const u32 etc_char_table[];
extern const u32 gill_atca[];
extern const u32 gill_btca[];
extern const u32 gill_caca[];
extern const u32 gill_cuca[];
extern const u32 gill_dmca[];
extern const u32 gill_exca[];
extern const u32 gill_nmca[];
extern const u32 gill_saca[];
extern const u32 gill_yuca[];
extern const u32 hugo_atca[];
extern const u32 hugo_btca[];
extern const u32 hugo_caca[];
extern const u32 hugo_cuca[];
extern const u32 hugo_dmca[];
extern const u32 hugo_exca[];
extern const u32 hugo_nmca[];
extern const u32 hugo_saca[];
extern const u32 hugo_yuca[];
extern const u32 ibuki_atca[];
extern const u32 ibuki_btca[];
extern const u32 ibuki_caca[];
extern const u32 ibuki_cuca[];
extern const u32 ibuki_dmca[];
extern const u32 ibuki_exca[];
extern const u32 ibuki_nmca[];
extern const u32 ibuki_saca[];
extern const u32 ibuki_yuca[];
extern const u32 ken_atca[];
extern const u32 ken_btca[];
extern const u32 ken_caca[];
extern const u32 ken_cuca[];
extern const u32 ken_dmca[];
extern const u32 ken_exca[];
extern const u32 ken_nmca[];
extern const u32 ken_saca[];
extern const u32 ken_yuca[];
extern const u32 necro_atca[];
extern const u32 necro_btca[];
extern const u32 necro_caca[];
extern const u32 necro_cuca[];
extern const u32 necro_dmca[];
extern const u32 necro_exca[];
extern const u32 necro_nmca[];
extern const u32 necro_saca[];
extern const u32 necro_yuca[];
extern const u32 oro_atca[];
extern const u32 oro_btca[];
extern const u32 oro_caca[];
extern const u32 oro_cuca[];
extern const u32 oro_dmca[];
extern const u32 oro_exca[];
extern const u32 oro_nmca[];
extern const u32 oro_saca[];
extern const u32 oro_yuca[];
extern const u32 plef_char_table[];
extern const u32 ryu_atca[];
extern const u32 ryu_btca[];
extern const u32 ryu_caca[];
extern const u32 ryu_cuca[];
extern const u32 ryu_dmca[];
extern const u32 ryu_exca[];
extern const u32 ryu_nmca[];
extern const u32 ryu_saca[];
extern const u32 ryu_yuca[];
extern const u32 sean_atca[];
extern const u32 sean_btca[];
extern const u32 sean_caca[];
extern const u32 sean_cuca[];
extern const u32 sean_dmca[];
extern const u32 sean_exca[];
extern const u32 sean_nmca[];
extern const u32 sean_saca[];
extern const u32 sean_yuca[];
extern const u32 stg00_char_table[];
extern const u32 stg01_char_table[];
extern const u32 stg02_char_table[];
extern const u32 stg03_char_table[];
extern const u32 stg04_char_table[];
extern const u32 stg05_char_table[];
extern const u32 stg06_char_table[];
extern const u32 stg07_char_table[];
extern const u32 stg10_char_table[];
extern const u32 stg11_char_table[];
extern const u32 stg12_char_table[];
extern const u32 yang_atca[];
extern const u32 yang_btca[];
extern const u32 yang_caca[];
extern const u32 yang_cuca[];
extern const u32 yang_dmca[];
extern const u32 yang_exca[];
extern const u32 yang_nmca[];
extern const u32 yang_saca[];
extern const u32 yang_yuca[];
extern const u32 yun_atca[];
extern const u32 yun_btca[];
extern const u32 yun_caca[];
extern const u32 yun_cuca[];
extern const u32 yun_dmca[];
extern const u32 yun_exca[];
extern const u32 yun_nmca[];
extern const u32 yun_saca[];
extern const u32 yun_yuca[];
extern u32 eff44_char_table[];

/* 02000E8C */
TM_STRING dbg_menu_str[7] = {
    { 0xD, 2, 2, (const s8 *)str_OBJECT_TEST },
    { 0xA, 4, 2, (const s8 *)str_OBJECT_LOOK },
    { 0xA, 5, 2, (const s8 *)str_OBJECT_EDIT },
    { 0xA, 6, 2, (const s8 *)str_OBJECT_EDIT_2 },
    { 0xA, 7, 2, (const s8 *)str_HIT },
    { 0xA, 8, 2, (const s8 *)str_ALL_CHARACTER },
    { 0xA, 9, 2, (const s8 *)str_BG_BLOCK },
};

/* 02000EE0 */
TM_STRING dbg_obj_info_str[10] = {
    { 1, 3, 2, (const s8 *)str_PLAYER }, { 1, 4, 2, (const s8 *)str_ALL },
    { 1, 6, 2, (const s8 *)str_MOTION }, { 1, 8, 2, (const s8 *)str_PATTERN },
    { 1, 9, 2, (const s8 *)str_INTERRUT }, { 1, 0xA, 2, (const s8 *)str_CODE_H },
    { 1, 0xB, 2, (const s8 *)str_FLIP }, { 1, 0xC, 2, (const s8 *)str_FLIP_ED },
    { 1, 0xD, 2, (const s8 *)str_POS_X_H }, { 1, 0xE, 2, (const s8 *)str_POS_Y_H },
};

/* 02000F58 */
TM_STRING dbg_obj_rel_str[3] = {
    { 1, 0xF, 2, (const s8 *)str_REL_X_H }, { 1, 0x10, 2, (const s8 *)str_REL_Y_H },
    { 1, 0x11, 2, (const s8 *)str_CURRENT },
};

/* 02000F7C */
TM_STRING dbg_all_char_str[3] = {
    { 0xF, 1, 2, (const s8 *)str_ALL_CHARACTER },
    { 1, 5, 2, (const s8 *)str_H },
    { 1, 7, 2, (const s8 *)str_H_2 },
};

/* 02000FA0 */
TM_STRING dbg_edit_num_str[4] = {
    { 1, 0x12, 2, (const s8 *)str_EDIT_NUM }, { 1, 0x13, 2, (const s8 *)str_NUM_END },
    { 1, 0x14, 2, (const s8 *)str_EDIT_INT }, { 1, 0x15, 2, (const s8 *)str_INT_END },
};

/* 02000FD0 */
TM_STRING dbg_rec_menu_str[3] = {
    { 0x1B, 3, 6, (const s8 *)str_DELETE_ALL_SH4 },
    { 0x1B, 4, 6, (const s8 *)str_1DATA_SH5 },
    { 0x1B, 5, 6, (const s8 *)str_CANCEL_SH6 },
};

/* 02000FF4 */
TM_STRING dbg_rec_clear_str[3] = {
    { 0x1B, 3, 6, (const s8 *)str_blank_4 }, { 0x1B, 4, 6, (const s8 *)str_blank_4 },
    { 0x1B, 5, 6, (const s8 *)str_blank_5 },
};

/* 02001018 */
TM_STRING dbg_rec_nodata_str[2] = {
    { 0x1B, 3, 6, (const s8 *)str_NO_EDIT },
    { 0x1B, 4, 6, (const s8 *)str_DATA_NOTHING },
};

/* 02001030 */
TM_STRING dbg_hit_size_str[13] = {
    { 1, 0xF, 2, (const s8 *)str_REVISE_X_H },
    { 1, 0x10, 2, (const s8 *)str_SIZE_X_H },
    { 1, 0x11, 2, (const s8 *)str_REVISE_Y_H },
    { 1, 0x12, 2, (const s8 *)str_SIZE_Y_H },
    { 1, 0x14, 2, (const s8 *)str_INDEX },
    { 1, 0x15, 2, (const s8 *)str_BODY_H },
    { 1, 0x16, 2, (const s8 *)str_ATTACK_H },
    { 1, 0x17, 2, (const s8 *)str_CAUGHT_H },
    { 1, 0x18, 2, (const s8 *)str_HOSEI_H },
    { 1, 0x19, 2, (const s8 *)str_CURRENT_2 },
    { 0xF, 0x19, 2, (const s8 *)str_KOC_IX_PT_Nix },
    { 0xF, 0x1A, 2, (const s8 *)str_KOC_IX_PT_Nix },
    { 0xF, 0x1B, 2, (const s8 *)str_KOC_IX_PT_Nix_2 },
};

/* 020010CC */
TM_STRING dbg_hit_part_str[40] = {
    { 0x24, 0x10, 2, (const s8 *)str_HEAD },
    { 0x24, 0x11, 2, (const s8 *)str_BREAST },
    { 0x24, 0x12, 2, (const s8 *)str_TRUNK_1 },
    { 0x24, 0x13, 2, (const s8 *)str_LEG },
    { 0x24, 0x14, 2, (const s8 *)str_HAND },
    { 0x24, 0x15, 2, (const s8 *)str_CATCH_n },
    { 0x24, 0x16, 2, (const s8 *)str_ATTACK_1 },
    { 0x24, 0x17, 2, (const s8 *)str_ATTACK_2 },
    { 0x24, 0x18, 2, (const s8 *)str_CAUGHT_n },
    { 0x24, 0x19, 2, (const s8 *)str_TRUNK_2 },
    { 1, 2, 2, (const s8 *)str_STAGE },
    { 1, 3, 2, (const s8 *)str_BLOCK_NO },
    { 0xB, 2, 2, (const s8 *)str_GREECE },
    { 0xB, 2, 2, (const s8 *)str_N_Y_1 },
    { 0xB, 2, 2, (const s8 *)str_N_Y_2 },
    { 0xB, 2, 2, (const s8 *)str_JAPAN_1 },
    { 0xB, 2, 2, (const s8 *)str_JAPAN_2 },
    { 0xB, 2, 2, (const s8 *)str_CHAINA_1 },
    { 0xB, 2, 2, (const s8 *)str_CHAINA_2 },
    { 0xB, 2, 2, (const s8 *)str_ENGLAND_1 },
    { 0xB, 2, 2, (const s8 *)str_ENGLAND_2 },
    { 0xB, 2, 2, (const s8 *)str_RUSSIA },
    { 0xB, 2, 2, (const s8 *)str_GERMANY },
    { 0xB, 2, 2, (const s8 *)str_KYOTO_1 },
    { 0xB, 2, 2, (const s8 *)str_KYOTO_2 },
    { 0xB, 2, 2, (const s8 *)str_KYOTO_3 },
    { 0xB, 2, 2, (const s8 *)str_AFRICA_1 },
    { 0xB, 2, 2, (const s8 *)str_AFRICA_2 },
    { 0xB, 2, 2, (const s8 *)str_BRAZIL },
    { 2, 1, 2, (const s8 *)str_GILL },
    { 2, 1, 2, (const s8 *)str_ALEX },
    { 2, 1, 2, (const s8 *)str_RYU },
    { 2, 1, 2, (const s8 *)str_YUN },
    { 2, 1, 2, (const s8 *)str_DUDDLY },
    { 2, 1, 2, (const s8 *)str_NECRO },
    { 2, 1, 2, (const s8 *)str_IBUKI },
    { 2, 1, 2, (const s8 *)str_ELENA },
    { 2, 1, 2, (const s8 *)str_ORO },
    { 2, 1, 2, (const s8 *)str_KEN },
    { 2, 1, 2, (const s8 *)str_SEAN },
};

/* 020012AC */
TM_STRING dbg_cg_head_str[6] = {
    { 0x1B, 3, 2, (const s8 *)str_CG_CTR },
    { 0x1B, 4, 2, (const s8 *)str_CG_TYPE },
    { 0x1B, 5, 2, (const s8 *)str_CG_SE },
    { 0x1B, 6, 2, (const s8 *)str_CG_FLIP },
    { 0x1B, 7, 2, (const s8 *)str_CG_OLC_IX },
    { 0x1B, 8, 2, (const s8 *)str_CG_NUMBER },
};

/* 020012F4 */
TM_STRING dbg_cg_att_str[6] = {
    { 0x1B, 0xA, 2, (const s8 *)str_CG_ATT_IX },
    { 0x1B, 0xB, 2, (const s8 *)str_CG_HIT_IX },
    { 0x1B, 0xC, 2, (const s8 *)str_CG_EXTDAT },
    { 0x1B, 0xD, 2, (const s8 *)str_CG_CANCEL },
    { 0x1B, 0xE, 2, (const s8 *)str_CG_EFFECT },
    { 0x1B, 0xF, 2, (const s8 *)str_CG_EFTYPE },
};

/* 0200133C */
TM_STRING dbg_cg_rival_str[4] = {
    { 0x1B, 0x10, 2, (const s8 *)str_CG_RIVAL },
    { 0x1B, 0x11, 2, (const s8 *)str_CG_ADD_XY },
    { 0x1B, 0x12, 2, (const s8 *)str_CG_NIX },
    { 0x1B, 0x13, 2, (const s8 *)str_CG_STATUS },
};

/* 0200136C */
TM_STRING dbg_cgd_info_str[8] = {
    { 0x1B, 2, 2, (const s8 *)str_CGD_TYPE },
    { 0x1B, 3, 2, (const s8 *)str_PAT_ST },
    { 0x1B, 4, 2, (const s8 *)str_KIND_WAZA },
    { 0x1B, 5, 2, (const s8 *)str_HIT_RANGE },
    { 0x1B, 6, 2, (const s8 *)str_YOKE_TYPE },
    { 0x1B, 7, 2, (const s8 *)str_YOKE_PAT },
    { 0x1B, 8, 2, (const s8 *)str_SP_TECH },
    { 0x1B, 9, 2, (const s8 *)str_WCA_IX },
};

/* 020013CC */
TM_STRING dbg_att_data_str[21] = {
    { 0x1B, 2, 2, (const s8 *)str_ATT_IX },
    { 0x1B, 3, 2, (const s8 *)str_REACTION },
    { 0x1B, 4, 2, (const s8 *)str_HIT_IX },
    { 0x1B, 5, 2, (const s8 *)str_GUARD },
    { 0x1B, 6, 2, (const s8 *)str_HISS },
    { 0x1B, 7, 2, (const s8 *)str_DIR },
    { 0x1B, 8, 2, (const s8 *)str_TEN_IX },
    { 0x1B, 9, 2, (const s8 *)str_POW },
    { 0x1B, 0xA, 2, (const s8 *)str_IMPACT },
    { 0x1B, 0xB, 2, (const s8 *)str_PIYO_n },
    { 0x1B, 0xC, 2, (const s8 *)str_HS_ME },
    { 0x1B, 0xD, 2, (const s8 *)str_HS_YOU },
    { 0x1B, 0xE, 2, (const s8 *)str_QUAKE },
    { 0x1B, 0xF, 2, (const s8 *)str_ZU_FLAG },
    { 0x1B, 0x10, 2, (const s8 *)str_ZOKUSEI },
    { 0x1B, 0x11, 2, (const s8 *)str_AT_LEVEL },
    { 0x1B, 0x12, 2, (const s8 *)str_ADD_ARTS },
    { 0x1B, 0x13, 2, (const s8 *)str_BUTT_TYPE },
    { 0x1B, 0x14, 2, (const s8 *)str_BUTT_PAT },
    { 0x1B, 0x15, 2, (const s8 *)str_DIR_ATT },
    { 0x1B, 0x16, 2, (const s8 *)str_VS_ID },
};

/* 020014C8 */
TM_STRING dbg_hud_clr_str[26] = {
    { 0x1B, 2, 2, (const s8 *)str_blank_6 },
    { 0x1B, 3, 2, (const s8 *)str_blank_6 },
    { 0x1B, 4, 2, (const s8 *)str_blank_6 },
    { 0x1B, 5, 2, (const s8 *)str_blank_6 },
    { 0x1B, 6, 2, (const s8 *)str_blank_6 },
    { 0x1B, 7, 2, (const s8 *)str_blank_6 },
    { 0x1B, 8, 2, (const s8 *)str_blank_6 },
    { 0x1B, 9, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xA, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xB, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xC, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xD, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xE, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xF, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x10, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x11, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x12, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x13, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x14, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x15, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x16, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x17, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x18, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x19, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x1A, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x1B, 2, (const s8 *)str_blank_7 },
};

/* 02001600 */
TM_STRING dbg_hud_clr_mid_str[6] = {
    { 0x1B, 0xE, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0xF, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x10, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x11, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x12, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x13, 2, (const s8 *)str_blank_6 },
};

/* 02001648 */
TM_STRING dbg_hud_clr_low_str[9] = {
    { 0x1B, 0x14, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x15, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x16, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x17, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x18, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x19, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x1A, 2, (const s8 *)str_blank_6 },
    { 0x1B, 0x1B, 2, (const s8 *)str_blank_7 },
    { 0x1B, 0x1C, 2, (const s8 *)str_blank_7 },
};

/* 020016B4 */
TM_STRING dbg_hud_clr_bottom_str[3] = {
    { 5, 0x19, 2, (const s8 *)str_blank_8 }, { 5, 0x1A, 2, (const s8 *)str_blank_8 },
    { 5, 0x1B, 2, (const s8 *)str_blank_9 },
};

/* 020016D8 */
TM_STRING dbg_cm_label_str[13] = {
    { 0x1B, 2, 2, (const s8 *)str_CMOA }, { 0x1B, 3, 2, (const s8 *)str_CMSW },
    { 0x1B, 4, 2, (const s8 *)str_CMLP }, { 0x1B, 5, 2, (const s8 *)str_CML2 },
    { 0x1B, 6, 2, (const s8 *)str_CMJA }, { 0x1B, 7, 2, (const s8 *)str_CMJ2 },
    { 0x1B, 8, 2, (const s8 *)str_CMJ3 }, { 0x1B, 9, 2, (const s8 *)str_CMJ4 },
    { 0x1B, 0xA, 2, (const s8 *)str_CMMS }, { 0x1B, 0xB, 2, (const s8 *)str_CMMD },
    { 0x1B, 0xC, 2, (const s8 *)str_CMYD }, { 0x1B, 0xD, 2, (const s8 *)str_CMCF },
    { 0x1B, 0xE, 2, (const s8 *)str_CMCR },
};

/* 02001774 */
TM_STRING dbg_cgd_type_str[5] = {
    { 0x25, 1, 0xA, (const s8 *)str_WCA },
    { 0x25, 2, 0xA, (const s8 *)str_CGD1 },
    { 0x25, 2, 0xA, (const s8 *)str_CGD2 },
    { 0x25, 2, 0xA, (const s8 *)str_CGD3 },
    { 0x25, 2, 0xA, (const s8 *)str_blank_10 },
};

/* 020017B0 */
TM_STRING dbg_pat_status_str[23] = {
    { 0x25, 3, 0xA, (const s8 *)str_sl_00 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_10 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_12 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_20 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_22 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_30 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_32 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_40 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_42 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_44 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_50 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_52 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_54 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_60 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_62 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_64 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_70 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_80 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_82 },
    { 0x25, 3, 0xA, (const s8 *)str_sl_90 },
    { 0x25, 3, 0xA, (const s8 *)str_blank_11 },
    { 0x25, 3, 0xA, (const s8 *)str_blank_11 },
    { 0x25, 3, 0xA, (const s8 *)str_blank_11 },
};

/* 020018C4 */
TM_STRING dbg_cg_group_str[90] = {
    { 0x25, 8, 0xA, (const s8 *)str_BCP00 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP01 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP02 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP03 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP04 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP05 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP06 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP07 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP08 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP09 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP10 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP11 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP12 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP13 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP14 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP15 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP20 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP21 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP22 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP23 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP24 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP25 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP26 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP27 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP28 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP29 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP30 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP31 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP32 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP33 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP34 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP35 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP36 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP37 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP38 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP39 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP40 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP41 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP42 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP43 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP44 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP45 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP46 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP47 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP48 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP49 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP50 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP51 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP52 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP53 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP54 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP55 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP56 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP57 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP58 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP59 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP60 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP61 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP62 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP63 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP64 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP65 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP66 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP67 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP68 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP69 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP70 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP71 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP72 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP73 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP74 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP75 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP76 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP77 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP78 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP79 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP80 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP81 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP82 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP83 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP84 },
    { 0x25, 8, 0xA, (const s8 *)str_BCP85 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 8, 0xA, (const s8 *)str_blank_12 },
};

/* 02001CFC */
TM_STRING dbg_preview_group_str[96] = {
    { 4, 5, 2, (const s8 *)str_BCP00 }, { 4, 5, 2, (const s8 *)str_BCP01 },
    { 4, 5, 2, (const s8 *)str_BCP02 }, { 4, 5, 2, (const s8 *)str_BCP03 },
    { 4, 5, 2, (const s8 *)str_BCP04 }, { 4, 5, 2, (const s8 *)str_BCP05 },
    { 4, 5, 2, (const s8 *)str_BCP06 }, { 4, 5, 2, (const s8 *)str_BCP07 },
    { 4, 5, 2, (const s8 *)str_BCP08 }, { 4, 5, 2, (const s8 *)str_BCP09 },
    { 4, 5, 2, (const s8 *)str_BCP10 }, { 4, 5, 2, (const s8 *)str_BCP11 },
    { 4, 5, 2, (const s8 *)str_BCP12 }, { 4, 5, 2, (const s8 *)str_BCP13 },
    { 4, 5, 2, (const s8 *)str_BCP14 }, { 4, 5, 2, (const s8 *)str_BCP15 },
    { 4, 5, 2, (const s8 *)str_BCP20 }, { 4, 5, 2, (const s8 *)str_BCP21 },
    { 4, 5, 2, (const s8 *)str_BCP22 }, { 4, 5, 2, (const s8 *)str_BCP23 },
    { 4, 5, 2, (const s8 *)str_BCP24 }, { 4, 5, 2, (const s8 *)str_BCP25 },
    { 4, 5, 2, (const s8 *)str_BCP26 }, { 4, 5, 2, (const s8 *)str_BCP27 },
    { 4, 5, 2, (const s8 *)str_BCP28 }, { 4, 5, 2, (const s8 *)str_BCP29 },
    { 4, 5, 2, (const s8 *)str_BCP30 }, { 4, 5, 2, (const s8 *)str_BCP31 },
    { 4, 5, 2, (const s8 *)str_BCP32 }, { 4, 5, 2, (const s8 *)str_BCP33 },
    { 4, 5, 2, (const s8 *)str_BCP34 }, { 4, 5, 2, (const s8 *)str_BCP35 },
    { 4, 5, 2, (const s8 *)str_BCP36 }, { 4, 5, 2, (const s8 *)str_BCP37 },
    { 4, 5, 2, (const s8 *)str_BCP38 }, { 4, 5, 2, (const s8 *)str_BCP39 },
    { 4, 5, 2, (const s8 *)str_BCP40 }, { 4, 5, 2, (const s8 *)str_BCP41 },
    { 4, 5, 2, (const s8 *)str_BCP42 }, { 4, 5, 2, (const s8 *)str_BCP43 },
    { 4, 5, 2, (const s8 *)str_BCP44 }, { 4, 5, 2, (const s8 *)str_BCP45 },
    { 4, 5, 2, (const s8 *)str_BCP46 }, { 4, 5, 2, (const s8 *)str_BCP47 },
    { 4, 5, 2, (const s8 *)str_BCP48 }, { 4, 5, 2, (const s8 *)str_BCP49 },
    { 4, 5, 2, (const s8 *)str_BCP50 }, { 4, 5, 2, (const s8 *)str_BCP51 },
    { 4, 5, 2, (const s8 *)str_BCP52 }, { 4, 5, 2, (const s8 *)str_BCP53 },
    { 4, 5, 2, (const s8 *)str_BCP54 }, { 4, 5, 2, (const s8 *)str_BCP55 },
    { 4, 5, 2, (const s8 *)str_BCP56 }, { 4, 5, 2, (const s8 *)str_BCP57 },
    { 4, 5, 2, (const s8 *)str_BCP58 }, { 4, 5, 2, (const s8 *)str_BCP59 },
    { 4, 5, 2, (const s8 *)str_BCP60 }, { 4, 5, 2, (const s8 *)str_BCP61 },
    { 4, 5, 2, (const s8 *)str_BCP62 }, { 4, 5, 2, (const s8 *)str_BCP63 },
    { 4, 5, 2, (const s8 *)str_BCP64 }, { 4, 5, 2, (const s8 *)str_BCP65 },
    { 4, 5, 2, (const s8 *)str_BCP66 }, { 4, 5, 2, (const s8 *)str_BCP67 },
    { 4, 5, 2, (const s8 *)str_BCP68 }, { 4, 5, 2, (const s8 *)str_BCP69 },
    { 4, 5, 2, (const s8 *)str_BCP70 }, { 4, 5, 2, (const s8 *)str_BCP71 },
    { 4, 5, 2, (const s8 *)str_BCP72 }, { 4, 5, 2, (const s8 *)str_BCP73 },
    { 4, 5, 2, (const s8 *)str_BCP74 }, { 4, 5, 2, (const s8 *)str_BCP75 },
    { 4, 5, 2, (const s8 *)str_BCP76 }, { 4, 5, 2, (const s8 *)str_BCP77 },
    { 4, 5, 2, (const s8 *)str_BCP78 }, { 4, 5, 2, (const s8 *)str_BCP79 },
    { 4, 5, 2, (const s8 *)str_BCP80 }, { 4, 5, 2, (const s8 *)str_BCP81 },
    { 4, 5, 2, (const s8 *)str_BCP82 }, { 4, 5, 2, (const s8 *)str_BCP83 },
    { 4, 5, 2, (const s8 *)str_BCP84 }, { 4, 5, 2, (const s8 *)str_BCP85 },
    { 4, 5, 2, (const s8 *)str_BCP86 }, { 4, 5, 2, (const s8 *)str_BCP87 },
    { 4, 5, 2, (const s8 *)str_BCP88 }, { 4, 5, 2, (const s8 *)str_BCP89 },
    { 4, 5, 2, (const s8 *)str_BCP90 }, { 4, 5, 2, (const s8 *)str_BCP91 },
    { 4, 5, 2, (const s8 *)str_BCP92 }, { 4, 5, 2, (const s8 *)str_BCP93 },
    { 4, 5, 2, (const s8 *)str_blank_12 }, { 4, 5, 2, (const s8 *)str_blank_12 },
    { 4, 5, 2, (const s8 *)str_blank_12 }, { 4, 5, 2, (const s8 *)str_blank_12 },
    { 4, 5, 2, (const s8 *)str_blank_12 }, { 4, 5, 2, (const s8 *)str_blank_12 },
};

/* 0200217C */
TM_STRING dbg_edit_group_str[99] = {
    { 1, 0x19, 2, (const s8 *)str_BCP00 }, { 1, 0x19, 2, (const s8 *)str_BCP01 },
    { 1, 0x19, 2, (const s8 *)str_BCP02 }, { 1, 0x19, 2, (const s8 *)str_BCP03 },
    { 1, 0x19, 2, (const s8 *)str_BCP04 }, { 1, 0x19, 2, (const s8 *)str_BCP05 },
    { 1, 0x19, 2, (const s8 *)str_BCP06 }, { 1, 0x19, 2, (const s8 *)str_BCP07 },
    { 1, 0x19, 2, (const s8 *)str_BCP08 }, { 1, 0x19, 2, (const s8 *)str_BCP09 },
    { 1, 0x19, 2, (const s8 *)str_BCP10 }, { 1, 0x19, 2, (const s8 *)str_BCP11 },
    { 1, 0x19, 2, (const s8 *)str_BCP12 }, { 1, 0x19, 2, (const s8 *)str_BCP13 },
    { 1, 0x19, 2, (const s8 *)str_BCP14 }, { 1, 0x19, 2, (const s8 *)str_BCP15 },
    { 1, 0x19, 2, (const s8 *)str_BCP20 }, { 1, 0x19, 2, (const s8 *)str_BCP21 },
    { 1, 0x19, 2, (const s8 *)str_BCP22 }, { 1, 0x19, 2, (const s8 *)str_BCP23 },
    { 1, 0x19, 2, (const s8 *)str_BCP24 }, { 1, 0x19, 2, (const s8 *)str_BCP25 },
    { 1, 0x19, 2, (const s8 *)str_BCP26 }, { 1, 0x19, 2, (const s8 *)str_BCP27 },
    { 1, 0x19, 2, (const s8 *)str_BCP28 }, { 1, 0x19, 2, (const s8 *)str_BCP29 },
    { 1, 0x19, 2, (const s8 *)str_BCP30 }, { 1, 0x19, 2, (const s8 *)str_BCP31 },
    { 1, 0x19, 2, (const s8 *)str_BCP32 }, { 1, 0x19, 2, (const s8 *)str_BCP33 },
    { 1, 0x19, 2, (const s8 *)str_BCP34 }, { 1, 0x19, 2, (const s8 *)str_BCP35 },
    { 1, 0x19, 2, (const s8 *)str_BCP36 }, { 1, 0x19, 2, (const s8 *)str_BCP37 },
    { 1, 0x19, 2, (const s8 *)str_BCP38 }, { 1, 0x19, 2, (const s8 *)str_BCP39 },
    { 1, 0x19, 2, (const s8 *)str_BCP40 }, { 1, 0x19, 2, (const s8 *)str_BCP41 },
    { 1, 0x19, 2, (const s8 *)str_BCP42 }, { 1, 0x19, 2, (const s8 *)str_BCP43 },
    { 1, 0x19, 2, (const s8 *)str_BCP44 }, { 1, 0x19, 2, (const s8 *)str_BCP45 },
    { 1, 0x19, 2, (const s8 *)str_BCP46 }, { 1, 0x19, 2, (const s8 *)str_BCP47 },
    { 1, 0x19, 2, (const s8 *)str_BCP48 }, { 1, 0x19, 2, (const s8 *)str_BCP49 },
    { 1, 0x19, 2, (const s8 *)str_BCP50 }, { 1, 0x19, 2, (const s8 *)str_BCP51 },
    { 1, 0x19, 2, (const s8 *)str_BCP52 }, { 1, 0x19, 2, (const s8 *)str_BCP53 },
    { 1, 0x19, 2, (const s8 *)str_BCP54 }, { 1, 0x19, 2, (const s8 *)str_BCP55 },
    { 1, 0x19, 2, (const s8 *)str_BCP56 }, { 1, 0x19, 2, (const s8 *)str_BCP57 },
    { 1, 0x19, 2, (const s8 *)str_BCP58 }, { 1, 0x19, 2, (const s8 *)str_BCP59 },
    { 1, 0x19, 2, (const s8 *)str_BCP60 }, { 1, 0x19, 2, (const s8 *)str_BCP61 },
    { 1, 0x19, 2, (const s8 *)str_BCP62 }, { 1, 0x19, 2, (const s8 *)str_BCP63 },
    { 1, 0x19, 2, (const s8 *)str_BCP64 }, { 1, 0x19, 2, (const s8 *)str_BCP65 },
    { 1, 0x19, 2, (const s8 *)str_BCP66 }, { 1, 0x19, 2, (const s8 *)str_BCP67 },
    { 1, 0x19, 2, (const s8 *)str_BCP68 }, { 1, 0x19, 2, (const s8 *)str_BCP69 },
    { 1, 0x19, 2, (const s8 *)str_BCP70 }, { 1, 0x19, 2, (const s8 *)str_BCP71 },
    { 1, 0x19, 2, (const s8 *)str_BCP72 }, { 1, 0x19, 2, (const s8 *)str_BCP73 },
    { 1, 0x19, 2, (const s8 *)str_BCP74 }, { 1, 0x19, 2, (const s8 *)str_BCP75 },
    { 1, 0x19, 2, (const s8 *)str_BCP76 }, { 1, 0x19, 2, (const s8 *)str_BCP77 },
    { 1, 0x19, 2, (const s8 *)str_BCP78 }, { 1, 0x19, 2, (const s8 *)str_BCP79 },
    { 1, 0x19, 2, (const s8 *)str_BCP80 }, { 1, 0x19, 2, (const s8 *)str_BCP81 },
    { 1, 0x19, 2, (const s8 *)str_BCP82 }, { 1, 0x19, 2, (const s8 *)str_BCP83 },
    { 1, 0x19, 2, (const s8 *)str_BCP84 }, { 1, 0x19, 2, (const s8 *)str_BCP85 },
    { 1, 0x19, 2, (const s8 *)str_BCP86 }, { 1, 0x19, 2, (const s8 *)str_BCP87 },
    { 1, 0x19, 2, (const s8 *)str_BCP88 }, { 1, 0x19, 2, (const s8 *)str_BCP89 },
    { 1, 0x19, 2, (const s8 *)str_BCP90 }, { 1, 0x19, 2, (const s8 *)str_BCP91 },
    { 1, 0x19, 2, (const s8 *)str_BCP92 }, { 1, 0x19, 2, (const s8 *)str_BCP93 },
    { 1, 0x19, 2, (const s8 *)str_blank_12 }, { 1, 0x19, 2, (const s8 *)str_blank_12 },
    { 1, 0x19, 2, (const s8 *)str_blank_12 }, { 1, 0x19, 2, (const s8 *)str_blank_12 },
    { 1, 0x19, 2, (const s8 *)str_blank_12 }, { 1, 0x19, 2, (const s8 *)str_blank_12 },
    { 1, 0x19, 2, (const s8 *)str_blank_12 }, { 1, 0x19, 2, (const s8 *)str_blank_12 },
    { 1, 0x19, 2, (const s8 *)str_blank_12 },
};

/* 02002620 */
TM_STRING dbg_extdat_str[3] = {
    { 0x25, 0xC, 0xA, (const s8 *)str_Pa }, { 0x25, 0xC, 0xA, (const s8 *)str_PA },
    { 0x25, 0xC, 0xA, (const s8 *)str_PB },
};

/* 02002644 */
TM_STRING dbg_eftype_names[9] = {
    { 0x25, 0xF, 0xA, (const s8 *)str_MLN }, { 0x25, 0xF, 0xA, (const s8 *)str_MLU },
    { 0x25, 0xF, 0xA, (const s8 *)str_MLD }, { 0x25, 0xF, 0xA, (const s8 *)str_MLF },
    { 0x25, 0xF, 0xA, (const s8 *)str_MLF }, { 0x25, 0xF, 0xA, (const s8 *)str_MLR },
    { 0x25, 0xF, 0xA, (const s8 *)str_MLR }, { 0x25, 0xF, 0xA, (const s8 *)str_MLR },
    { 0x25, 0xF, 0xA, (const s8 *)str_M },
};

/* 020026B0 */
TM_STRING dbg_eftype_s_str[6] = {
    { 0x28, 0xF, 0xA, (const s8 *)str_S1 }, { 0x28, 0xF, 0xA, (const s8 *)str_S2 },
    { 0x28, 0xF, 0xA, (const s8 *)str_S3 }, { 0x28, 0xF, 0xA, (const s8 *)str_S4 },
    { 0x28, 0xF, 0xA, (const s8 *)str_S5 }, { 0x28, 0xF, 0xA, (const s8 *)str_S6 },
};

/* 020026F8 */
TM_STRING dbg_eftype_usemj_str[8] = {
    { 0x2A, 0xF, 0xA, (const s8 *)str_blank_12 },
    { 0x2A, 0xF, 0xA, (const s8 *)str_USEMJ },
    { 0x25, 0x18, 0xA, (const s8 *)str_BASE },
    { 0x25, 0x18, 0xA, (const s8 *)str_BEFORE },
    { 0x25, 0x18, 0xA, (const s8 *)str_BACK },
    { 0x25, 0x18, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 0x18, 0xA, (const s8 *)str_blank_12 },
    { 0x25, 0x18, 0xA, (const s8 *)str_blank_12 },
};

/* 02002758 */
TM_STRING dbg_cancel_on_str[8] = {
    { 0x2C, 0xD, 0xA, (const s8 *)str_H_3 }, { 0x2B, 0xD, 0xA, (const s8 *)str_D },
    { 0x2A, 0xD, 0xA, (const s8 *)str_A }, { 0x29, 0xD, 0xA, (const s8 *)str_M_2 },
    { 0x28, 0xD, 0xA, (const s8 *)str_R }, { 0x27, 0xD, 0xA, (const s8 *)str_C },
    { 0x26, 0xD, 0xA, (const s8 *)str_S }, { 0x25, 0xD, 0xA, (const s8 *)str_S },
};

/* 020027B8 */
TM_STRING dbg_cancel_off_str[24] = {
    { 0x2C, 0xD, 0xA, (const s8 *)str_h }, { 0x2B, 0xD, 0xA, (const s8 *)str_d },
    { 0x2A, 0xD, 0xA, (const s8 *)str_a }, { 0x29, 0xD, 0xA, (const s8 *)str_m },
    { 0x28, 0xD, 0xA, (const s8 *)str_r }, { 0x27, 0xD, 0xA, (const s8 *)str_c },
    { 0x26, 0xD, 0xA, (const s8 *)str_s }, { 0x25, 0xD, 0xA, (const s8 *)str_s },
    { 0x25, 0x11, 0xA, (const s8 *)str_H_3 }, { 0x26, 0x11, 0xA, (const s8 *)str_D },
    { 0x27, 0x11, 0xA, (const s8 *)str_A }, { 0x28, 0x11, 0xA, (const s8 *)str_M_2 },
    { 0x29, 0x11, 0xA, (const s8 *)str_R }, { 0x2A, 0x11, 0xA, (const s8 *)str_C },
    { 0x2B, 0x11, 0xA, (const s8 *)str_S }, { 0x2C, 0x11, 0xA, (const s8 *)str_S },
    { 0x25, 0x11, 0xA, (const s8 *)str_h_2 }, { 0x26, 0x11, 0xA, (const s8 *)str_d_2 },
    { 0x27, 0x11, 0xA, (const s8 *)str_a_2 }, { 0x28, 0x11, 0xA, (const s8 *)str_m_2 },
    { 0x29, 0x11, 0xA, (const s8 *)str_r_2 }, { 0x2A, 0x11, 0xA, (const s8 *)str_c_2 },
    { 0x2B, 0x11, 0xA, (const s8 *)str_s_2 }, { 0x2C, 0x11, 0xA, (const s8 *)str_s_2 },
};

/* 020028D8 */
TM_STRING dbg_koc_cmlp_str[11] = {
    { 0xC, 0x19, 0xA, (const s8 *)str_NM },
    { 0xC, 0x19, 0xA, (const s8 *)str_DM },
    { 0xC, 0x19, 0xA, (const s8 *)str_CA },
    { 0xC, 0x19, 0xA, (const s8 *)str_CU },
    { 0xC, 0x19, 0xA, (const s8 *)str_AT },
    { 0xC, 0x19, 0xA, (const s8 *)str_BT },
    { 0xC, 0x19, 0xA, (const s8 *)str_EX },
    { 0xC, 0x19, 0xA, (const s8 *)str_SA },
    { 0x20, 0x19, 0xA, (const s8 *)str_CB },
    { 0x20, 0x19, 0xA, (const s8 *)str_blank_13 },
    { 0x20, 0x19, 0xA, (const s8 *)str_blank_13 },
};

/* 0200295C */
TM_STRING dbg_koc_cml2_str[11] = {
    { 0xC, 0x1A, 0xA, (const s8 *)str_NM },
    { 0xC, 0x1A, 0xA, (const s8 *)str_DM },
    { 0xC, 0x1A, 0xA, (const s8 *)str_CA },
    { 0xC, 0x1A, 0xA, (const s8 *)str_CU },
    { 0xC, 0x1A, 0xA, (const s8 *)str_AT },
    { 0xC, 0x1A, 0xA, (const s8 *)str_BT },
    { 0xC, 0x1A, 0xA, (const s8 *)str_EX },
    { 0xC, 0x1A, 0xA, (const s8 *)str_SA },
    { 0x20, 0x1A, 0xA, (const s8 *)str_CB },
    { 0x20, 0x1A, 0xA, (const s8 *)str_blank_13 },
    { 0x20, 0x1A, 0xA, (const s8 *)str_blank_13 },
};

/* 020029E0 */
TM_STRING dbg_koc_cmsw_str[11] = {
    { 0x20, 0x19, 0xA, (const s8 *)str_NM },
    { 0x20, 0x19, 0xA, (const s8 *)str_DM },
    { 0x20, 0x19, 0xA, (const s8 *)str_CA },
    { 0x20, 0x19, 0xA, (const s8 *)str_CU },
    { 0x20, 0x19, 0xA, (const s8 *)str_AT },
    { 0x20, 0x19, 0xA, (const s8 *)str_SA },
    { 0x20, 0x19, 0xA, (const s8 *)str_BT },
    { 0x20, 0x19, 0xA, (const s8 *)str_EX },
    { 0x20, 0x19, 0xA, (const s8 *)str_CB },
    { 0x20, 0x19, 0xA, (const s8 *)str_blank_13 },
    { 0x20, 0x19, 0xA, (const s8 *)str_blank_13 },
};

/* 02002A64 */
TM_STRING dbg_koc_cmja_str[11] = {
    { 0x20, 0x1A, 0xA, (const s8 *)str_NM },
    { 0x20, 0x1A, 0xA, (const s8 *)str_DM },
    { 0x20, 0x1A, 0xA, (const s8 *)str_CA },
    { 0x20, 0x1A, 0xA, (const s8 *)str_CU },
    { 0x20, 0x1A, 0xA, (const s8 *)str_AT },
    { 0x20, 0x1A, 0xA, (const s8 *)str_SA },
    { 0x20, 0x1A, 0xA, (const s8 *)str_BT },
    { 0x20, 0x1A, 0xA, (const s8 *)str_EX },
    { 0x20, 0x1A, 0xA, (const s8 *)str_CB },
    { 0x20, 0x1A, 0xA, (const s8 *)str_blank_13 },
    { 0x20, 0x1A, 0xA, (const s8 *)str_blank_13 },
};

/* 02002AE8 */
TM_STRING dbg_koc_cmoa_str[9] = {
    { 0x20, 0x1B, 0xA, (const s8 *)str_NM }, { 0x20, 0x1B, 0xA, (const s8 *)str_DM },
    { 0x20, 0x1B, 0xA, (const s8 *)str_CA }, { 0x20, 0x1B, 0xA, (const s8 *)str_CU },
    { 0x20, 0x1B, 0xA, (const s8 *)str_AT }, { 0x20, 0x1B, 0xA, (const s8 *)str_SA },
    { 0x20, 0x1B, 0xA, (const s8 *)str_BT }, { 0x20, 0x1B, 0xA, (const s8 *)str_EX },
    { 0x20, 0x1B, 0xA, (const s8 *)str_CB },
};

/* 02002B54 */
TM_STRING dbg_koc_str[9] = {
    { 0x20, 2, 2, (const s8 *)str_NM }, { 0x20, 2, 2, (const s8 *)str_DM },
    { 0x20, 2, 2, (const s8 *)str_CA }, { 0x20, 2, 2, (const s8 *)str_CU },
    { 0x20, 2, 2, (const s8 *)str_AT }, { 0x20, 2, 2, (const s8 *)str_SA },
    { 0x20, 2, 2, (const s8 *)str_BT }, { 0x20, 2, 2, (const s8 *)str_EX },
    { 0x20, 2, 2, (const s8 *)str_CB },
};

/* 02002BC0 */
TM_STRING dbg_waza_kind_str[8] = {
    { 0x25, 4, 0xA, (const s8 *)str_nmA }, { 0x25, 4, 0xA, (const s8 *)str_hsA },
    { 0x25, 4, 0xA, (const s8 *)str_nmC }, { 0x25, 4, 0xA, (const s8 *)str_hsC },
    { 0x25, 4, 0xA, (const s8 *)str_saA }, { 0x25, 4, 0xA, (const s8 *)str_saC },
    { 0x25, 4, 0xA, (const s8 *)str_paA }, { 0x25, 4, 0xA, (const s8 *)str_huA },
};

/* 02002C20 */
TM_STRING dbg_char_name_str[17] = {
    { 0xB, 3, 2, (const s8 *)str_GILL_2 }, { 0xB, 3, 2, (const s8 *)str_ALEX_2 },
    { 0xB, 3, 2, (const s8 *)str_RYU_2 }, { 0xB, 3, 2, (const s8 *)str_YUN_2 },
    { 0xB, 3, 2, (const s8 *)str_DUDLEY }, { 0xB, 3, 2, (const s8 *)str_NECRO_2 },
    { 0xB, 3, 2, (const s8 *)str_HUGO }, { 0xB, 3, 2, (const s8 *)str_IBUKI_2 },
    { 0xB, 3, 2, (const s8 *)str_ELENA_2 }, { 0xB, 3, 2, (const s8 *)str_ORO_2 },
    { 0xB, 3, 2, (const s8 *)str_YANG }, { 0xB, 3, 2, (const s8 *)str_KEN_2 },
    { 0xB, 3, 2, (const s8 *)str_SEAN_2 }, { 0xB, 3, 2, (const s8 *)str_PL_13 },
    { 0xB, 3, 2, (const s8 *)str_PL_14 }, { 0xB, 3, 2, (const s8 *)str_PL_15 },
    { 0xB, 3, 2, (const s8 *)str_ETC },
};

/* 02002CEC */
TM_STRING dbg_act_kind_str[666] = {
    { 3, 5, 4, (const s8 *)str_NORMAL },
    { 3, 5, 4, (const s8 *)str_DAMAGE },
    { 3, 5, 4, (const s8 *)str_CATCH },
    { 3, 5, 4, (const s8 *)str_CAUGHT },
    { 3, 5, 4, (const s8 *)str_ATTACK },
    { 3, 5, 4, (const s8 *)str_SP_AT },
    { 3, 5, 4, (const s8 *)str_BUTTOBI },
    { 3, 5, 4, (const s8 *)str_UNION },
    { 3, 5, 4, (const s8 *)str_ETC_2 },
    { 3, 5, 4, (const s8 *)str_ETC_2 },
    { 3, 5, 4, (const s8 *)str_EFFECT },
    { 3, 5, 4, (const s8 *)str_empty_9 },
    { 3, 7, 4, (const s8 *)str_KAMAE },
    { 3, 7, 4, (const s8 *)str_HURIMUKI },
    { 3, 7, 4, (const s8 *)str_FRONT_WALK },
    { 3, 7, 4, (const s8 *)str_BACK_WALK },
    { 3, 7, 4, (const s8 *)str_DASH_HUMIKOMI },
    { 3, 7, 4, (const s8 *)str_DASH_TOBINOKI },
    { 3, 7, 4, (const s8 *)str_KAGAMU },
    { 3, 7, 4, (const s8 *)str_KAGAMI_KAMAE },
    { 3, 7, 4, (const s8 *)str_KAGAMI_TURN },
    { 3, 7, 4, (const s8 *)str_KAGAMI_F_WALK },
    { 3, 7, 4, (const s8 *)str_KAGAMI_B_WALK },
    { 3, 7, 4, (const s8 *)str_STAND_UP },
    { 3, 7, 4, (const s8 *)str_JUMP_JUNBI },
    { 3, 7, 4, (const s8 *)str_SP_JUMP_JUNBI },
    { 3, 7, 4, (const s8 *)str_JUMP_FRONT },
    { 3, 7, 4, (const s8 *)str_JUMP_VERTICAL },
    { 3, 7, 4, (const s8 *)str_JUMP_BACK },
    { 3, 7, 4, (const s8 *)str_S_JUMP_FRONT },
    { 3, 7, 4, (const s8 *)str_S_JUMP_V },
    { 3, 7, 4, (const s8 *)str_S_JUMP_BACK },
    { 3, 7, 4, (const s8 *)str_SP_JUMP_FRONT },
    { 3, 7, 4, (const s8 *)str_SP_JUMP_V },
    { 3, 7, 4, (const s8 *)str_SP_JUMP_BACK },
    { 3, 7, 4, (const s8 *)str_WALK_END },
    { 3, 7, 4, (const s8 *)str_PARING_HEAD },
    { 3, 7, 4, (const s8 *)str_PARING_UP },
    { 3, 7, 4, (const s8 *)str_PARING_DOWN },
    { 3, 7, 4, (const s8 *)str_PARING_AIR_F },
    { 3, 7, 4, (const s8 *)str_PARING_AIR_B },
    { 3, 7, 4, (const s8 *)str_GUARD_HEAD },
    { 3, 7, 4, (const s8 *)str_GUARD_UP },
    { 3, 7, 4, (const s8 *)str_GUARD_DOWN },
    { 3, 7, 4, (const s8 *)str_GUARD_AIR },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_1 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_2 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_3 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_4 },
    { 3, 7, 4, (const s8 *)str_NAGERARE_KAIHI },
    { 3, 7, 4, (const s8 *)str_NAGERARE_KAIHI },
    { 3, 7, 4, (const s8 *)str_NAGERARE_KAIHI },
    { 3, 7, 4, (const s8 *)str_NAGERARE_KAIHI },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_GUARD_HEAD_2 },
    { 3, 7, 4, (const s8 *)str_GUARD_UP_2 },
    { 3, 7, 4, (const s8 *)str_GUARD_DOWN_2 },
    { 3, 7, 4, (const s8 *)str_GUARD_AIR_2 },
    { 3, 7, 4, (const s8 *)str_HUSHIN_HEAD },
    { 3, 7, 4, (const s8 *)str_HUSHIN_UP },
    { 3, 7, 4, (const s8 *)str_HUSHIN_DOWN },
    { 3, 7, 4, (const s8 *)str_HUSHIN_AIR },
    { 3, 7, 4, (const s8 *)str_FACE_S },
    { 3, 7, 4, (const s8 *)str_FACE_M },
    { 3, 7, 4, (const s8 *)str_FACE_L },
    { 3, 7, 4, (const s8 *)str_FACE_SP },
    { 3, 7, 4, (const s8 *)str_FOOK_OKU_S },
    { 3, 7, 4, (const s8 *)str_FOOK_OKU_M },
    { 3, 7, 4, (const s8 *)str_FOOK_OKU_L },
    { 3, 7, 4, (const s8 *)str_FOOK_OKU_SP },
    { 3, 7, 4, (const s8 *)str_FOOK_TEMAE_S },
    { 3, 7, 4, (const s8 *)str_FOOK_TEMAE_M },
    { 3, 7, 4, (const s8 *)str_FOOK_TEMAE_L },
    { 3, 7, 4, (const s8 *)str_FOOK_TEMAE_SP },
    { 3, 7, 4, (const s8 *)str_UPPER_S },
    { 3, 7, 4, (const s8 *)str_UPPER_M },
    { 3, 7, 4, (const s8 *)str_UPPER_L },
    { 3, 7, 4, (const s8 *)str_UPPER_SP },
    { 3, 7, 4, (const s8 *)str_NOUTEN_S },
    { 3, 7, 4, (const s8 *)str_NOUTEN_M },
    { 3, 7, 4, (const s8 *)str_NOUTEN_L },
    { 3, 7, 4, (const s8 *)str_NOUTEN_SP },
    { 3, 7, 4, (const s8 *)str_BODY_BROW_S },
    { 3, 7, 4, (const s8 *)str_BODY_BROW_M },
    { 3, 7, 4, (const s8 *)str_BODY_BROW_L },
    { 3, 7, 4, (const s8 *)str_BODY_BROW_SP },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_S },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_M },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_L },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_SP },
    { 3, 7, 4, (const s8 *)str_TATAKI_S },
    { 3, 7, 4, (const s8 *)str_TATAKI_M },
    { 3, 7, 4, (const s8 *)str_TATAKI_L },
    { 3, 7, 4, (const s8 *)str_TATAKI_SP },
    { 3, 7, 4, (const s8 *)str_TATAKI_V_S },
    { 3, 7, 4, (const s8 *)str_TATAKI_V_M },
    { 3, 7, 4, (const s8 *)str_TATAKI_V_L },
    { 3, 7, 4, (const s8 *)str_TATAKI_V_SP },
    { 3, 7, 4, (const s8 *)str_NOBASITA_TE_S },
    { 3, 7, 4, (const s8 *)str_NOBASITA_TE_M },
    { 3, 7, 4, (const s8 *)str_NOBASITA_TE_L },
    { 3, 7, 4, (const s8 *)str_NOBASITA_TE_SP },
    { 3, 7, 4, (const s8 *)str_KAGAMI_S },
    { 3, 7, 4, (const s8 *)str_KAGAMI_M },
    { 3, 7, 4, (const s8 *)str_KAGAMI_L },
    { 3, 7, 4, (const s8 *)str_KAGAMI_SP },
    { 3, 7, 4, (const s8 *)str_KGM_TATAKI_S },
    { 3, 7, 4, (const s8 *)str_KGM_TATAKI_M },
    { 3, 7, 4, (const s8 *)str_KGM_TATAKI_L },
    { 3, 7, 4, (const s8 *)str_KGM_TATAKI_SP },
    { 3, 7, 4, (const s8 *)str_KGM_TTKI_V_S },
    { 3, 7, 4, (const s8 *)str_KGM_TTKI_V_M },
    { 3, 7, 4, (const s8 *)str_KGM_TTKI_V_L },
    { 3, 7, 4, (const s8 *)str_KGM_TTKI_V_SP },
    { 3, 7, 4, (const s8 *)str_NEKOROBI_S },
    { 3, 7, 4, (const s8 *)str_NEKOROBI_M },
    { 3, 7, 4, (const s8 *)str_NEKOROBI_L },
    { 3, 7, 4, (const s8 *)str_NEKOROBI_SP },
    { 3, 7, 4, (const s8 *)str_OKIAGARI },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_F },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_B },
    { 3, 7, 4, (const s8 *)str_LOSE_NO_STAND },
    { 3, 7, 4, (const s8 *)str_LOSE_SONABA },
    { 3, 7, 4, (const s8 *)str_LOSE_KAGAMI },
    { 3, 7, 4, (const s8 *)str_PIYO },
    { 3, 7, 4, (const s8 *)str_UKEMI_MOVE_F },
    { 3, 7, 4, (const s8 *)str_UKEMI_MOVE_R },
    { 3, 7, 4, (const s8 *)str_SHIMEOTASARE },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_AIR_S },
    { 3, 7, 4, (const s8 *)str_AIR_M },
    { 3, 7, 4, (const s8 *)str_AIR_L },
    { 3, 7, 4, (const s8 *)str_AIR_SP },
    { 3, 7, 4, (const s8 *)str_ASHIBARAI_A },
    { 3, 7, 4, (const s8 *)str_ASHIBARAI_B },
    { 3, 7, 4, (const s8 *)str_ASHIBARAI_C },
    { 3, 7, 4, (const s8 *)str_ASHIBARAI_D },
    { 3, 7, 4, (const s8 *)str_TUNNOMERI_A },
    { 3, 7, 4, (const s8 *)str_TUNNOMERI_B },
    { 3, 7, 4, (const s8 *)str_TUNNOMERI_C },
    { 3, 7, 4, (const s8 *)str_TUNNOMERI_D },
    { 3, 7, 4, (const s8 *)str_NOKEZORI_A },
    { 3, 7, 4, (const s8 *)str_NOKEZORI_B },
    { 3, 7, 4, (const s8 *)str_NOKEZORI_C },
    { 3, 7, 4, (const s8 *)str_NOKEZORI_D },
    { 3, 7, 4, (const s8 *)str_KUNOJI_A },
    { 3, 7, 4, (const s8 *)str_KUNOJI_B },
    { 3, 7, 4, (const s8 *)str_KUNOJI_C },
    { 3, 7, 4, (const s8 *)str_KUNOJI_D },
    { 3, 7, 4, (const s8 *)str_KIRIMOMI_A },
    { 3, 7, 4, (const s8 *)str_KIRIMOMI_B },
    { 3, 7, 4, (const s8 *)str_KIRIMOMI_C },
    { 3, 7, 4, (const s8 *)str_KIRIMOMI_D },
    { 3, 7, 4, (const s8 *)str_UPPER_A },
    { 3, 7, 4, (const s8 *)str_UPPER_B },
    { 3, 7, 4, (const s8 *)str_UPPER_C },
    { 3, 7, 4, (const s8 *)str_UPPER_D },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_A },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_B },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_C },
    { 3, 7, 4, (const s8 *)str_BODY_UPPER_D },
    { 3, 7, 4, (const s8 *)str_NM_BUTTOBI_A },
    { 3, 7, 4, (const s8 *)str_NM_BUTTOBI_B },
    { 3, 7, 4, (const s8 *)str_NM_BUTTOBI_C },
    { 3, 7, 4, (const s8 *)str_NM_BUTTOBI_D },
    { 3, 7, 4, (const s8 *)str_TATAKI_AIR_A },
    { 3, 7, 4, (const s8 *)str_TATAKI_AIR_B },
    { 3, 7, 4, (const s8 *)str_TATAKI_AIR_C },
    { 3, 7, 4, (const s8 *)str_TATAKI_AIR_D },
    { 3, 7, 4, (const s8 *)str_TTKI_V_AIR_A },
    { 3, 7, 4, (const s8 *)str_TTKI_V_AIR_B },
    { 3, 7, 4, (const s8 *)str_TTKI_V_AIR_C },
    { 3, 7, 4, (const s8 *)str_TTKI_V_AIR_D },
    { 3, 7, 4, (const s8 *)str_HUMI_ASIB_A },
    { 3, 7, 4, (const s8 *)str_HUMI_ASIB_B },
    { 3, 7, 4, (const s8 *)str_HUMI_ASIB_C },
    { 3, 7, 4, (const s8 *)str_HUMI_ASIB_D },
    { 3, 7, 4, (const s8 *)str_FACE_A },
    { 3, 7, 4, (const s8 *)str_FACE_B },
    { 3, 7, 4, (const s8 *)str_FACE_C },
    { 3, 7, 4, (const s8 *)str_FACE_D },
    { 3, 7, 4, (const s8 *)str_ASIBRI_MAKE_A },
    { 3, 7, 4, (const s8 *)str_ASIBRI_MAKE_B },
    { 3, 7, 4, (const s8 *)str_ASIBRI_MAKE_C },
    { 3, 7, 4, (const s8 *)str_ASIBRI_MAKE_D },
    { 3, 7, 4, (const s8 *)str_ASIB_TN_MAKE_A },
    { 3, 7, 4, (const s8 *)str_ASIB_TN_MAKE_B },
    { 3, 7, 4, (const s8 *)str_ASIB_TN_MAKE_C },
    { 3, 7, 4, (const s8 *)str_ASIB_TN_MAKE_D },
    { 3, 7, 4, (const s8 *)str_DENKI_A },
    { 3, 7, 4, (const s8 *)str_DENKI_B },
    { 3, 7, 4, (const s8 *)str_DENKI_C },
    { 3, 7, 4, (const s8 *)str_DENKI_D },
    { 3, 7, 4, (const s8 *)str_KUNOJI_NOKE_A },
    { 3, 7, 4, (const s8 *)str_KUNOJI_NOKE_B },
    { 3, 7, 4, (const s8 *)str_KUNOJI_NOKE_C },
    { 3, 7, 4, (const s8 *)str_KUNOJI_NOKE_D },
    { 3, 7, 4, (const s8 *)str_SINSYOURYU_A },
    { 3, 7, 4, (const s8 *)str_SINSYOURYU_B },
    { 3, 7, 4, (const s8 *)str_SINSYOURYU_C },
    { 3, 7, 4, (const s8 *)str_SINSYOURYU_D },
    { 3, 7, 4, (const s8 *)str_HANEAGARI_A },
    { 3, 7, 4, (const s8 *)str_HANEAGARI_B },
    { 3, 7, 4, (const s8 *)str_HANEAGARI_C },
    { 3, 7, 4, (const s8 *)str_HANEAGARI_D },
    { 3, 7, 4, (const s8 *)str_TOUKETSU_A },
    { 3, 7, 4, (const s8 *)str_TOUKETSU_B },
    { 3, 7, 4, (const s8 *)str_TOUKETSU_C },
    { 3, 7, 4, (const s8 *)str_TOUKETSU_D },
    { 3, 7, 4, (const s8 *)str_BODY_SLAM_A },
    { 3, 7, 4, (const s8 *)str_BODY_SLAM_B },
    { 3, 7, 4, (const s8 *)str_BODY_SLAM_C },
    { 3, 7, 4, (const s8 *)str_BODY_SLAM_D },
    { 3, 7, 4, (const s8 *)str_IPPONZEOI_A },
    { 3, 7, 4, (const s8 *)str_IPPONZEOI_B },
    { 3, 7, 4, (const s8 *)str_IPPONZEOI_C },
    { 3, 7, 4, (const s8 *)str_IPPONZEOI_D },
    { 3, 7, 4, (const s8 *)str_TOMOE_RYU_A },
    { 3, 7, 4, (const s8 *)str_TOMOE_RYU_B },
    { 3, 7, 4, (const s8 *)str_TOMOE_RYU_C },
    { 3, 7, 4, (const s8 *)str_TOMOE_RYU_D },
    { 3, 7, 4, (const s8 *)str_MONKEY_FLIP_A },
    { 3, 7, 4, (const s8 *)str_MONKEY_FLIP_B },
    { 3, 7, 4, (const s8 *)str_MONKEY_FLIP_C },
    { 3, 7, 4, (const s8 *)str_MONKEY_FLIP_D },
    { 3, 7, 4, (const s8 *)str_TOMOE_ORO_A },
    { 3, 7, 4, (const s8 *)str_TOMOE_ORO_B },
    { 3, 7, 4, (const s8 *)str_TOMOE_ORO_C },
    { 3, 7, 4, (const s8 *)str_TOMOE_ORO_D },
    { 3, 7, 4, (const s8 *)str_SNAKE_FANG_A },
    { 3, 7, 4, (const s8 *)str_SNAKE_FANG_B },
    { 3, 7, 4, (const s8 *)str_SNAKE_FANG_C },
    { 3, 7, 4, (const s8 *)str_SNAKE_FANG_D },
    { 3, 7, 4, (const s8 *)str_FLANKEN_S_A },
    { 3, 7, 4, (const s8 *)str_FLANKEN_S_B },
    { 3, 7, 4, (const s8 *)str_FLANKEN_S_C },
    { 3, 7, 4, (const s8 *)str_FLANKEN_S_D },
    { 3, 7, 4, (const s8 *)str_KISHINRIKI_A },
    { 3, 7, 4, (const s8 *)str_KISHINRIKI_B },
    { 3, 7, 4, (const s8 *)str_KISHINRIKI_C },
    { 3, 7, 4, (const s8 *)str_KISHINRIKI_D },
    { 3, 7, 4, (const s8 *)str_SPLASH_M_A },
    { 3, 7, 4, (const s8 *)str_SPLASH_M_B },
    { 3, 7, 4, (const s8 *)str_SPLASH_M_C },
    { 3, 7, 4, (const s8 *)str_SPLASH_M_D },
    { 3, 7, 4, (const s8 *)str_HARAIGOSHI_A },
    { 3, 7, 4, (const s8 *)str_HARAIGOSHI_B },
    { 3, 7, 4, (const s8 *)str_HARAIGOSHI_C },
    { 3, 7, 4, (const s8 *)str_HARAIGOSHI_D },
    { 3, 7, 4, (const s8 *)str_ALEX_B_D_A },
    { 3, 7, 4, (const s8 *)str_ALEX_B_D_B },
    { 3, 7, 4, (const s8 *)str_ALEX_B_D_C },
    { 3, 7, 4, (const s8 *)str_ALEX_B_D_D },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_CATCH_1 },
    { 3, 7, 4, (const s8 *)str_CATCH_2 },
    { 3, 7, 4, (const s8 *)str_CATCH_3 },
    { 3, 7, 4, (const s8 *)str_CATCH_4 },
    { 3, 7, 4, (const s8 *)str_CATCH_5 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_CATCH_TOBIKOE },
    { 3, 7, 4, (const s8 *)str_CATCH_NAGE },
    { 3, 7, 4, (const s8 *)str_CATCH_HIZAGERI },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_S_PUNCH_A },
    { 3, 7, 4, (const s8 *)str_S_PUNCH_B },
    { 3, 7, 4, (const s8 *)str_S_PUNCH_C },
    { 3, 7, 4, (const s8 *)str_M_PUNCH_A },
    { 3, 7, 4, (const s8 *)str_M_PUNCH_B },
    { 3, 7, 4, (const s8 *)str_M_PUNCH_C },
    { 3, 7, 4, (const s8 *)str_L_PUNCH_A },
    { 3, 7, 4, (const s8 *)str_L_PUNCH_B },
    { 3, 7, 4, (const s8 *)str_L_PUNCH_C },
    { 3, 7, 4, (const s8 *)str_S_KICK_A },
    { 3, 7, 4, (const s8 *)str_S_KICK_B },
    { 3, 7, 4, (const s8 *)str_S_KICK_C },
    { 3, 7, 4, (const s8 *)str_M_KICK_A },
    { 3, 7, 4, (const s8 *)str_M_KICK_B },
    { 3, 7, 4, (const s8 *)str_M_KICK_C },
    { 3, 7, 4, (const s8 *)str_L_KICK_A },
    { 3, 7, 4, (const s8 *)str_L_KICK_B },
    { 3, 7, 4, (const s8 *)str_L_KICK_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_P_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_C },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_A },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_B },
    { 3, 7, 4, (const s8 *)str_KAGAMI_K_C },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_S_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_S_B },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_M_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_M_B },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_L_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_P_L_B },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_S_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_S_B },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_M_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_M_B },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_L_A },
    { 3, 7, 4, (const s8 *)str_V_JUMP_K_L_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_S_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_S_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_M_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_M_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_L_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_P_L_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_S_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_S_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_M_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_M_B },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_L_A },
    { 3, 7, 4, (const s8 *)str_F_JUMP_K_L_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_S_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_S_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_M_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_M_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_L_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_P_L_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_S_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_S_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_M_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_M_B },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_L_A },
    { 3, 7, 4, (const s8 *)str_B_JUMP_K_L_B },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_A },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_B },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_C_2 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_D_2 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_E_2 },
    { 3, 7, 4, (const s8 *)str_TUKAMIKAKARI_F_2 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_P_S },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_P_M },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_P_L },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_K_S },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_K_M },
    { 3, 7, 4, (const s8 *)str_UP_P_GUARD_K_L },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_P_S },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_P_M },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_P_L },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_K_S },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_K_M },
    { 3, 7, 4, (const s8 *)str_D_P_GUARD_K_L },
    { 3, 7, 4, (const s8 *)str_FUSHIN_P_S },
    { 3, 7, 4, (const s8 *)str_FUSHIN_P_M },
    { 3, 7, 4, (const s8 *)str_FUSHIN_P_L },
    { 3, 7, 4, (const s8 *)str_FUSHIN_K_S },
    { 3, 7, 4, (const s8 *)str_FUSHIN_K_M },
    { 3, 7, 4, (const s8 *)str_FUSHIN_K_L },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_P_S },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_P_M },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_P_L },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_K_S },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_K_M },
    { 3, 7, 4, (const s8 *)str_OKIAGARI_K_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_1_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_1_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_1_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_1_SP },
    { 3, 7, 4, (const s8 *)str_ATTACK_2_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_2_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_2_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_2_SP },
    { 3, 7, 4, (const s8 *)str_ATTACK_3_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_3_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_3_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_3_SP },
    { 3, 7, 4, (const s8 *)str_ATTACK_4_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_4_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_4_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_4_SP },
    { 3, 7, 4, (const s8 *)str_ATTACK_5_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_5_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_5_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_5_SP },
    { 3, 7, 4, (const s8 *)str_ATTACK_6_S },
    { 3, 7, 4, (const s8 *)str_ATTACK_6_M },
    { 3, 7, 4, (const s8 *)str_ATTACK_6_L },
    { 3, 7, 4, (const s8 *)str_ATTACK_6_SP },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_NM_DM },
    { 3, 7, 4, (const s8 *)str_KUSSHIN_SLOW },
    { 3, 7, 4, (const s8 *)str_KUSSHIN_FAST },
    { 3, 7, 4, (const s8 *)str_ASI_B_SIRIMOTI },
    { 3, 7, 4, (const s8 *)str_NM_JUMP_AT },
    { 3, 7, 4, (const s8 *)str_TATAKITUKERARE },
    { 3, 7, 4, (const s8 *)str_BUTTOBI_2 },
    { 3, 7, 4, (const s8 *)str_KUNOJI_BUTTOBI },
    { 3, 7, 4, (const s8 *)str_KIRIMOMI },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_HANASARE },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_EFF01_CHAR },
    { 3, 7, 4, (const s8 *)str_EFF13_CHAR },
    { 3, 7, 4, (const s8 *)str_BOSS_STAGE_OBJ },
    { 3, 7, 4, (const s8 *)str_N_Y_1_OBJ_2 },
    { 3, 7, 4, (const s8 *)str_N_Y_2_64_OBJ },
    { 3, 7, 4, (const s8 *)str_N_Y_2_256_OBJ },
    { 3, 7, 4, (const s8 *)str_JAPAN_1_OBJ },
    { 3, 7, 4, (const s8 *)str_JAPAN_2_OBJ },
    { 3, 7, 4, (const s8 *)str_CHAINA_1_OBJ_2 },
    { 3, 7, 4, (const s8 *)str_CHAINA_2_OBJ_2 },
    { 3, 7, 4, (const s8 *)str_ENFLAND_OBJ },
    { 3, 7, 4, (const s8 *)str_ROSIA_OBJ },
    { 3, 7, 4, (const s8 *)str_GERMANY_OBJ },
    { 3, 7, 4, (const s8 *)str_FURUDERA_OBJ },
    { 3, 7, 4, (const s8 *)str_AFRICA_1_2 },
    { 3, 7, 4, (const s8 *)str_AFRICA_2_2 },
    { 3, 7, 4, (const s8 *)str_BRAZIL_2 },
    { 3, 7, 4, (const s8 *)str_YUN_YAN },
    { 3, 7, 4, (const s8 *)str_ETC_3 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_PLEF },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_1 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_2 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_3 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_4 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_5 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_6 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_7 },
    { 3, 7, 4, (const s8 *)str_APPEAR_JUNBI_8 },
    { 3, 7, 4, (const s8 *)str_APPEAR_1 },
    { 3, 7, 4, (const s8 *)str_APPEAR_2 },
    { 3, 7, 4, (const s8 *)str_APPEAR_3 },
    { 3, 7, 4, (const s8 *)str_APPEAR_4 },
    { 3, 7, 4, (const s8 *)str_APPEAR_5 },
    { 3, 7, 4, (const s8 *)str_APPEAR_6 },
    { 3, 7, 4, (const s8 *)str_APPEAR_7 },
    { 3, 7, 4, (const s8 *)str_APPEAR_8 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_1 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_2 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_3 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_4 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_5 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_6 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_7 },
    { 3, 7, 4, (const s8 *)str_SP_APPEAR_8 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_1 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_2 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_3 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_4 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_5 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_6 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_7 },
    { 3, 7, 4, (const s8 *)str_ZANNEN_8 },
    { 3, 7, 4, (const s8 *)str_WIN_1 },
    { 3, 7, 4, (const s8 *)str_WIN_2 },
    { 3, 7, 4, (const s8 *)str_WIN_3 },
    { 3, 7, 4, (const s8 *)str_WIN_4 },
    { 3, 7, 4, (const s8 *)str_WIN_5 },
    { 3, 7, 4, (const s8 *)str_WIN_6 },
    { 3, 7, 4, (const s8 *)str_WIN_7 },
    { 3, 7, 4, (const s8 *)str_WIN_8 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_1 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_2 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_3 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_4 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_5 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_6 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_7 },
    { 3, 7, 4, (const s8 *)str_SP_WIN_8 },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WAIT },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WAIT },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WAIT },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WAIT },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WIN },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WIN },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WIN },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_WIN },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_LOSE },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_LOSE },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_LOSE },
    { 3, 7, 4, (const s8 *)str_JUDGMENT_LOSE },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
    { 3, 7, 4, (const s8 *)str_blank_14 },
};

/* 02004C24 */
TM_STRING* dbg_act_name_tbl[11] = {
    (TM_STRING *)&dbg_act_kind_str[12], (TM_STRING *)&dbg_act_kind_str[70],
    (TM_STRING *)&dbg_act_kind_str[301], (TM_STRING *)&dbg_act_kind_str[314],
    (TM_STRING *)&dbg_act_kind_str[326], (TM_STRING *)&dbg_act_kind_str[426],
    (TM_STRING *)&dbg_act_kind_str[158], (TM_STRING *)&dbg_act_kind_str[490],
    (TM_STRING *)&dbg_act_kind_str[596], (TM_STRING *)&dbg_act_kind_str[596],
    (TM_STRING *)&dbg_act_kind_str[559],
};

/* 02004C50 */
u32* dbg_pl_char_tbl[20][9] = {
    {
        (u32 *)gill_nmca, (u32 *)gill_dmca, (u32 *)gill_caca, (u32 *)gill_cuca,
        (u32 *)gill_atca, (u32 *)gill_saca, (u32 *)gill_btca, (u32 *)gill_exca,
        (u32 *)gill_yuca,
    },
    {
        (u32 *)alex_nmca, (u32 *)alex_dmca, (u32 *)alex_caca, (u32 *)alex_cuca,
        (u32 *)alex_atca, (u32 *)alex_saca, (u32 *)alex_btca, (u32 *)alex_exca,
        (u32 *)alex_yuca,
    },
    {
        (u32 *)ryu_nmca, (u32 *)ryu_dmca, (u32 *)ryu_caca, (u32 *)ryu_cuca,
        (u32 *)ryu_atca, (u32 *)ryu_saca, (u32 *)ryu_btca, (u32 *)ryu_exca,
        (u32 *)ryu_yuca,
    },
    {
        (u32 *)yun_nmca, (u32 *)yun_dmca, (u32 *)yun_caca, (u32 *)yun_cuca,
        (u32 *)yun_atca, (u32 *)yun_saca, (u32 *)yun_btca, (u32 *)yun_exca,
        (u32 *)yun_yuca,
    },
    {
        (u32 *)dudley_nmca, (u32 *)dudley_dmca, (u32 *)dudley_caca, (u32 *)dudley_cuca,
        (u32 *)dudley_atca, (u32 *)dudley_saca, (u32 *)dudley_btca, (u32 *)dudley_exca,
        (u32 *)dudley_yuca,
    },
    {
        (u32 *)necro_nmca, (u32 *)necro_dmca, (u32 *)necro_caca, (u32 *)necro_cuca,
        (u32 *)necro_atca, (u32 *)necro_saca, (u32 *)necro_btca, (u32 *)necro_exca,
        (u32 *)necro_yuca,
    },
    {
        (u32 *)hugo_nmca, (u32 *)hugo_dmca, (u32 *)hugo_caca, (u32 *)hugo_cuca,
        (u32 *)hugo_atca, (u32 *)hugo_saca, (u32 *)hugo_btca, (u32 *)hugo_exca,
        (u32 *)hugo_yuca,
    },
    {
        (u32 *)ibuki_nmca, (u32 *)ibuki_dmca, (u32 *)ibuki_caca, (u32 *)ibuki_cuca,
        (u32 *)ibuki_atca, (u32 *)ibuki_saca, (u32 *)ibuki_btca, (u32 *)ibuki_exca,
        (u32 *)ibuki_yuca,
    },
    {
        (u32 *)elena_nmca, (u32 *)elena_dmca, (u32 *)elena_caca, (u32 *)elena_cuca,
        (u32 *)elena_atca, (u32 *)elena_saca, (u32 *)elena_btca, (u32 *)elena_exca,
        (u32 *)elena_yuca,
    },
    {
        (u32 *)oro_nmca, (u32 *)oro_dmca, (u32 *)oro_caca, (u32 *)oro_cuca,
        (u32 *)oro_atca, (u32 *)oro_saca, (u32 *)oro_btca, (u32 *)oro_exca,
        (u32 *)oro_yuca,
    },
    {
        (u32 *)yang_nmca, (u32 *)yang_dmca, (u32 *)yang_caca, (u32 *)yang_cuca,
        (u32 *)yang_atca, (u32 *)yang_saca, (u32 *)yang_btca, (u32 *)yang_exca,
        (u32 *)yang_yuca,
    },
    {
        (u32 *)ken_nmca, (u32 *)ken_dmca, (u32 *)ken_caca, (u32 *)ken_cuca,
        (u32 *)ken_atca, (u32 *)ken_saca, (u32 *)ken_btca, (u32 *)ken_exca,
        (u32 *)ken_yuca,
    },
    {
        (u32 *)sean_nmca, (u32 *)sean_dmca, (u32 *)sean_caca, (u32 *)sean_cuca,
        (u32 *)sean_atca, (u32 *)sean_saca, (u32 *)sean_btca, (u32 *)sean_exca,
        (u32 *)sean_yuca,
    },
    {
        (u32 *)alex_nmca, (u32 *)alex_dmca, (u32 *)alex_caca, (u32 *)alex_cuca,
        (u32 *)alex_atca, (u32 *)alex_saca, (u32 *)alex_btca, (u32 *)alex_exca,
        (u32 *)alex_yuca,
    },
    {
        (u32 *)alex_nmca, (u32 *)alex_dmca, (u32 *)alex_caca, (u32 *)alex_cuca,
        (u32 *)alex_atca, (u32 *)alex_saca, (u32 *)alex_btca, (u32 *)alex_exca,
        (u32 *)alex_yuca,
    },
    {
        (u32 *)alex_nmca, (u32 *)alex_dmca, (u32 *)alex_caca, (u32 *)alex_cuca,
        (u32 *)alex_atca, (u32 *)alex_saca, (u32 *)alex_btca, (u32 *)alex_exca,
        (u32 *)alex_yuca,
    },
    {
        (u32 *)ef01_char_table, (u32 *)ef13_char_table, (u32 *)stg00_char_table, (u32 *)stg01_char_table,
        (u32 *)stg12_char_table, (u32 *)eff44_char_table, (u32 *)stg02_char_table, (u32 *)stg11_char_table,
        (u32 *)stg03_char_table,
    },
    {
        (u32 *)stg10_char_table, (u32 *)stg04_char_table, (u32 *)stg05_char_table, (u32 *)stg06_char_table,
        (u32 *)stg07_char_table, (u32 *)eff45_char_table, (u32 *)eff86_char_table, (u32 *)brz_char_table,
        (u32 *)eff77_char_table,
    },
    {
        (u32 *)direct_03_char_table, (u32 *)etc_char_table,
        (u32 *)etc2_char_table, (u32 *)ag_char_table_1,
        (u32 *)ag_char_table_2, (u32 *)ag_char_table_3,
        (u32 *)ag_char_table_4, (u32 *)ag_char_table_5,
        (u32 *)ag_char_table_6,
    },
    {
        (u32 *)ag_char_table_0, (u32 *)ag_face_panel_table,
        (u32 *)plef_char_table, (u32 *)effH3_char_table,
        0, 0,
        0, 0,
        0,
    },
};

s8 Debug_R_No;  /* 02013934 */
s8 Debug_Select_No;  /* 02013935 */
s8 Debug_Menu_No;  /* 02013936 */
s8 Debug_Tool_No;  /* 02013937 */
s16 Debug_Rep_Timer[21];  /* 02013938 */
s8 Debug_Rep_Count[21];  /* 02013962 */
/* after Debug_Rep_Count: nothing refers to it by name or address */
u8 Debug_Rep_Count_tail[1];  /* 02013977 */
s8 Debug_RL_Flag[2];  /* 02013978 */
s8 Debug_CG_Flip[2];  /* 0201397A */
s8 Debug_Flip_Work[2];  /* 0201397C */
s8 Debug_Flip_Mask[2];  /* 0201397E */
s8 Debug_Play_Flag;  /* 02013980 */
s8 Debug_Snap_Disp;  /* 02013981 */
s8 Debug_Dec_Disp;  /* 02013982 */
s16 Debug_Rec_Frame;  /* 02013984 */
s16 Debug_Rec_Count;  /* 02013986 */
s8 Debug_PL_id;  /* 02013988 */
s8 Debug_Command;  /* 02013989 */
s8 Debug_Edit_Sub;  /* 0201398A */
s8 Debug_Hit_Sub;  /* 0201398B */
s8 Debug_Box_Edit;  /* 0201398C */
s8 dbg_copy_done;  /* 0201398D */
s8 dbg_snap_req;  /* 0201398E */
s8 dbg_hud_mode;  /* 0201398F */
s8 dbg_rec_menu;  /* 02013990 */
s8 dbg_save_mode;  /* 02013991 */
s8 dbg_look_mode;  /* 02013992 */
s8 dbg_kakusyuku_mode;  /* 02013993 */
s8 dbg_rec_exist;  /* 02013994 */
s8 dbg_cmd_panel;  /* 02013995 */
s8 dbg_col_ix[2];  /* 02013996 */
s16 dbg_judge_eff_ix;  /* 02013998 */
s16 dbg_zoom_x;  /* 0201399A */
s16 dbg_zoom_y;  /* 0201399C */
s16 dbg_old_cgd_type;  /* 0201399E */
s16 dbg_hud_x;  /* 020139A0 */
s16 dbg_copy_pat;  /* 020139A2 */
s16 dbg_copy_char;  /* 020139A4 */
/* after dbg_copy_char: nothing refers to it by name or address */
u8 dbg_copy_char_tail[2];  /* 020139A6 */
u16 dbg_p1sw_0;  /* 020139A8 */
u16 dbg_p1sw_1;  /* 020139AA */
u16 dbg_p2sw_0;  /* 020139AC */
u16 dbg_p2sw_1;  /* 020139AE */
s16 dbg_dipsw_0;  /* 020139B0 */
s16 dbg_dipsw_1;  /* 020139B2 */
s16* dbg_edit_box;  /* 020139B4 */
s16 dbg_col_char;  /* 020139B8 */
PLW* dbg_pl;  /* 020139BC */
DBG_SLOT* dbg_slot;  /* 020139C0 */
s16 dbg_slot_w[2][9];  /* 020139C4 */
SNAPSHOT* dbg_snap_ptr;  /* 020139E8 */
SNAPSHOT dbg_snap_w[2][128];  /* 020139EC */
WORK_Other* dbg_ghost_ewk[2][3];  /* 020153EC */
PATTERN_BUF dbg_look_buf;  /* 02015404 */
/* after dbg_look_buf: nothing refers to it by name or address */
u8 dbg_look_buf_tail[20];  /* 02015A58 */
PATTERN_BUF dbg_copy_buf;  /* 02015A6C */
/* after dbg_copy_buf: nothing refers to it by name or address */
u8 dbg_copy_buf_tail[20];  /* 020160C0 */
PATTERN_BUF dbg_edit_buf;  /* 020160D4 */
/* after dbg_edit_buf: nothing refers to it by name or address */
u8 dbg_edit_buf_tail[20];  /* 02016728 */
WORK_Other_JUDGE* dbg_judge_ewk;  /* 0201673C */
u8 dbg_look_judge[792];  /* 02016740 */
HITA_BOX dbg_look_body[123];  /* 02016A58 */
/* after dbg_look_body: nothing refers to it by name or address */
u8 dbg_look_body_tail[24];  /* 020179B8 */
HITA_BOX dbg_look_attack[74];  /* 020179D0 */
/* after dbg_look_attack: nothing refers to it by name or address */
u8 dbg_look_attack_tail[8];  /* 02018310 */
u8 dbg_look_caught[792];  /* 02018318 */
u8 dbg_look_hosei[792];  /* 02018630 */
u8 dbg_edit_judge[792];  /* 02018948 */
u8 dbg_edit_body[3960];  /* 02018C60 */
u8 dbg_edit_attack[2376];  /* 02019BD8 */
u8 dbg_edit_caught[792];  /* 0201A520 */
u8 dbg_edit_hosei[792];  /* 0201A838 */
u8 dbg_copy_judge[8];  /* 0201AB50 */
u8 dbg_copy_body[40];  /* 0201AB58 */
u8 dbg_copy_attack[24];  /* 0201AB80 */
u8 dbg_copy_caught[8];  /* 0201AB98 */
u8 dbg_copy_hosei[8];  /* 0201ABA0 */
