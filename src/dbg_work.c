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
extern const s8 str_1DATA_SH5[];
extern const s8 str_ADD_ARTS[];
extern const s8 str_AFRICA_1[];
extern const s8 str_AFRICA_1_2[];
extern const s8 str_AFRICA_2[];
extern const s8 str_AFRICA_2_2[];
extern const s8 str_AIR_L[];
extern const s8 str_AIR_M[];
extern const s8 str_AIR_SP[];
extern const s8 str_AIR_S[];
extern const s8 str_ALEX[];
extern const s8 str_ALEX_2[];
extern const s8 str_ALEX_B_D_A[];
extern const s8 str_ALEX_B_D_B[];
extern const s8 str_ALEX_B_D_C[];
extern const s8 str_ALEX_B_D_D[];
extern const s8 str_ALL[];
extern const s8 str_ALL_CHARACTER[];
extern const s8 str_APPEAR_1[];
extern const s8 str_APPEAR_2[];
extern const s8 str_APPEAR_3[];
extern const s8 str_APPEAR_4[];
extern const s8 str_APPEAR_5[];
extern const s8 str_APPEAR_6[];
extern const s8 str_APPEAR_7[];
extern const s8 str_APPEAR_8[];
extern const s8 str_APPEAR_JUNBI_1[];
extern const s8 str_APPEAR_JUNBI_2[];
extern const s8 str_APPEAR_JUNBI_3[];
extern const s8 str_APPEAR_JUNBI_4[];
extern const s8 str_APPEAR_JUNBI_5[];
extern const s8 str_APPEAR_JUNBI_6[];
extern const s8 str_APPEAR_JUNBI_7[];
extern const s8 str_APPEAR_JUNBI_8[];
extern const s8 str_ASHIBARAI_A[];
extern const s8 str_ASHIBARAI_B[];
extern const s8 str_ASHIBARAI_C[];
extern const s8 str_ASHIBARAI_D[];
extern const s8 str_ASIBRI_MAKE_A[];
extern const s8 str_ASIBRI_MAKE_B[];
extern const s8 str_ASIBRI_MAKE_C[];
extern const s8 str_ASIBRI_MAKE_D[];
extern const s8 str_ASIB_TN_MAKE_A[];
extern const s8 str_ASIB_TN_MAKE_B[];
extern const s8 str_ASIB_TN_MAKE_C[];
extern const s8 str_ASIB_TN_MAKE_D[];
extern const s8 str_ASI_B_SIRIMOTI[];
extern const s8 str_ATTACK[];
extern const s8 str_ATTACK_1[];
extern const s8 str_ATTACK_1_L[];
extern const s8 str_ATTACK_1_M[];
extern const s8 str_ATTACK_1_SP[];
extern const s8 str_ATTACK_1_S[];
extern const s8 str_ATTACK_2[];
extern const s8 str_ATTACK_2_L[];
extern const s8 str_ATTACK_2_M[];
extern const s8 str_ATTACK_2_SP[];
extern const s8 str_ATTACK_2_S[];
extern const s8 str_ATTACK_3_L[];
extern const s8 str_ATTACK_3_M[];
extern const s8 str_ATTACK_3_SP[];
extern const s8 str_ATTACK_3_S[];
extern const s8 str_ATTACK_4_L[];
extern const s8 str_ATTACK_4_M[];
extern const s8 str_ATTACK_4_SP[];
extern const s8 str_ATTACK_4_S[];
extern const s8 str_ATTACK_5_L[];
extern const s8 str_ATTACK_5_M[];
extern const s8 str_ATTACK_5_SP[];
extern const s8 str_ATTACK_5_S[];
extern const s8 str_ATTACK_6_L[];
extern const s8 str_ATTACK_6_M[];
extern const s8 str_ATTACK_6_SP[];
extern const s8 str_ATTACK_6_S[];
extern const s8 str_ATTACK_H[];
extern const s8 str_ATT_IX[];
extern const s8 str_AT[];
extern const s8 str_AT_LEVEL[];
extern const s8 str_A[];
extern const s8 str_BACK[];
extern const s8 str_BACK_WALK[];
extern const s8 str_BASE[];
extern const s8 str_BCP00[];
extern const s8 str_BCP01[];
extern const s8 str_BCP02[];
extern const s8 str_BCP03[];
extern const s8 str_BCP04[];
extern const s8 str_BCP05[];
extern const s8 str_BCP06[];
extern const s8 str_BCP07[];
extern const s8 str_BCP08[];
extern const s8 str_BCP09[];
extern const s8 str_BCP10[];
extern const s8 str_BCP11[];
extern const s8 str_BCP12[];
extern const s8 str_BCP13[];
extern const s8 str_BCP14[];
extern const s8 str_BCP15[];
extern const s8 str_BCP20[];
extern const s8 str_BCP21[];
extern const s8 str_BCP22[];
extern const s8 str_BCP23[];
extern const s8 str_BCP24[];
extern const s8 str_BCP25[];
extern const s8 str_BCP26[];
extern const s8 str_BCP27[];
extern const s8 str_BCP28[];
extern const s8 str_BCP29[];
extern const s8 str_BCP30[];
extern const s8 str_BCP31[];
extern const s8 str_BCP32[];
extern const s8 str_BCP33[];
extern const s8 str_BCP34[];
extern const s8 str_BCP35[];
extern const s8 str_BCP36[];
extern const s8 str_BCP37[];
extern const s8 str_BCP38[];
extern const s8 str_BCP39[];
extern const s8 str_BCP40[];
extern const s8 str_BCP41[];
extern const s8 str_BCP42[];
extern const s8 str_BCP43[];
extern const s8 str_BCP44[];
extern const s8 str_BCP45[];
extern const s8 str_BCP46[];
extern const s8 str_BCP47[];
extern const s8 str_BCP48[];
extern const s8 str_BCP49[];
extern const s8 str_BCP50[];
extern const s8 str_BCP51[];
extern const s8 str_BCP52[];
extern const s8 str_BCP53[];
extern const s8 str_BCP54[];
extern const s8 str_BCP55[];
extern const s8 str_BCP56[];
extern const s8 str_BCP57[];
extern const s8 str_BCP58[];
extern const s8 str_BCP59[];
extern const s8 str_BCP60[];
extern const s8 str_BCP61[];
extern const s8 str_BCP62[];
extern const s8 str_BCP63[];
extern const s8 str_BCP64[];
extern const s8 str_BCP65[];
extern const s8 str_BCP66[];
extern const s8 str_BCP67[];
extern const s8 str_BCP68[];
extern const s8 str_BCP69[];
extern const s8 str_BCP70[];
extern const s8 str_BCP71[];
extern const s8 str_BCP72[];
extern const s8 str_BCP73[];
extern const s8 str_BCP74[];
extern const s8 str_BCP75[];
extern const s8 str_BCP76[];
extern const s8 str_BCP77[];
extern const s8 str_BCP78[];
extern const s8 str_BCP79[];
extern const s8 str_BCP80[];
extern const s8 str_BCP81[];
extern const s8 str_BCP82[];
extern const s8 str_BCP83[];
extern const s8 str_BCP84[];
extern const s8 str_BCP85[];
extern const s8 str_BCP86[];
extern const s8 str_BCP87[];
extern const s8 str_BCP88[];
extern const s8 str_BCP89[];
extern const s8 str_BCP90[];
extern const s8 str_BCP91[];
extern const s8 str_BCP92[];
extern const s8 str_BCP93[];
extern const s8 str_BEFORE[];
extern const s8 str_BG_BLOCK[];
extern const s8 str_BLOCK_NO[];
extern const s8 str_BODY_BROW_L[];
extern const s8 str_BODY_BROW_M[];
extern const s8 str_BODY_BROW_SP[];
extern const s8 str_BODY_BROW_S[];
extern const s8 str_BODY_H[];
extern const s8 str_BODY_SLAM_A[];
extern const s8 str_BODY_SLAM_B[];
extern const s8 str_BODY_SLAM_C[];
extern const s8 str_BODY_SLAM_D[];
extern const s8 str_BODY_UPPER_A[];
extern const s8 str_BODY_UPPER_B[];
extern const s8 str_BODY_UPPER_C[];
extern const s8 str_BODY_UPPER_D[];
extern const s8 str_BODY_UPPER_L[];
extern const s8 str_BODY_UPPER_M[];
extern const s8 str_BODY_UPPER_SP[];
extern const s8 str_BODY_UPPER_S[];
extern const s8 str_BOSS_STAGE_OBJ[];
extern const s8 str_BRAZIL[];
extern const s8 str_BRAZIL_2[];
extern const s8 str_BREAST[];
extern const s8 str_BT[];
extern const s8 str_BUTTOBI[];
extern const s8 str_BUTTOBI_2[];
extern const s8 str_BUTT_PAT[];
extern const s8 str_BUTT_TYPE[];
extern const s8 str_B_JUMP_K_L_A[];
extern const s8 str_B_JUMP_K_L_B[];
extern const s8 str_B_JUMP_K_M_A[];
extern const s8 str_B_JUMP_K_M_B[];
extern const s8 str_B_JUMP_K_S_A[];
extern const s8 str_B_JUMP_K_S_B[];
extern const s8 str_B_JUMP_P_L_A[];
extern const s8 str_B_JUMP_P_L_B[];
extern const s8 str_B_JUMP_P_M_A[];
extern const s8 str_B_JUMP_P_M_B[];
extern const s8 str_B_JUMP_P_S_A[];
extern const s8 str_B_JUMP_P_S_B[];
extern const s8 str_CANCEL_SH6[];
extern const s8 str_CATCH[];
extern const s8 str_CATCH_1[];
extern const s8 str_CATCH_2[];
extern const s8 str_CATCH_3[];
extern const s8 str_CATCH_4[];
extern const s8 str_CATCH_5[];
extern const s8 str_CATCH_HIZAGERI[];
extern const s8 str_CATCH_NAGE[];
extern const s8 str_CATCH_TOBIKOE[];
extern const s8 str_CATCH_n[];
extern const s8 str_CAUGHT[];
extern const s8 str_CAUGHT_H[];
extern const s8 str_CAUGHT_n[];
extern const s8 str_CA[];
extern const s8 str_CB[];
extern const s8 str_CGD1[];
extern const s8 str_CGD2[];
extern const s8 str_CGD3[];
extern const s8 str_CGD_TYPE[];
extern const s8 str_CG_ADD_XY[];
extern const s8 str_CG_ATT_IX[];
extern const s8 str_CG_CANCEL[];
extern const s8 str_CG_CTR[];
extern const s8 str_CG_EFFECT[];
extern const s8 str_CG_EFTYPE[];
extern const s8 str_CG_EXTDAT[];
extern const s8 str_CG_FLIP[];
extern const s8 str_CG_HIT_IX[];
extern const s8 str_CG_NIX[];
extern const s8 str_CG_NUMBER[];
extern const s8 str_CG_OLC_IX[];
extern const s8 str_CG_RIVAL[];
extern const s8 str_CG_SE[];
extern const s8 str_CG_STATUS[];
extern const s8 str_CG_TYPE[];
extern const s8 str_CHAINA_1[];
extern const s8 str_CHAINA_1_OBJ_2[];
extern const s8 str_CHAINA_2[];
extern const s8 str_CHAINA_2_OBJ_2[];
extern const s8 str_CMCF[];
extern const s8 str_CMCR[];
extern const s8 str_CMJ2[];
extern const s8 str_CMJ3[];
extern const s8 str_CMJ4[];
extern const s8 str_CMJA[];
extern const s8 str_CML2[];
extern const s8 str_CMLP[];
extern const s8 str_CMMD[];
extern const s8 str_CMMS[];
extern const s8 str_CMOA[];
extern const s8 str_CMSW[];
extern const s8 str_CMYD[];
extern const s8 str_CODE_H[];
extern const s8 str_CURRENT[];
extern const s8 str_CURRENT_2[];
extern const s8 str_CU[];
extern const s8 str_C[];
extern const s8 str_DAMAGE[];
extern const s8 str_DASH_HUMIKOMI[];
extern const s8 str_DASH_TOBINOKI[];
extern const s8 str_DATA_NOTHING[];
extern const s8 str_DELETE_ALL_SH4[];
extern const s8 str_DENKI_A[];
extern const s8 str_DENKI_B[];
extern const s8 str_DENKI_C[];
extern const s8 str_DENKI_D[];
extern const s8 str_DIR[];
extern const s8 str_DIR_ATT[];
extern const s8 str_DM[];
extern const s8 str_DUDDLY[];
extern const s8 str_DUDLEY[];
extern const s8 str_D[];
extern const s8 str_D_P_GUARD_K_L[];
extern const s8 str_D_P_GUARD_K_M[];
extern const s8 str_D_P_GUARD_K_S[];
extern const s8 str_D_P_GUARD_P_L[];
extern const s8 str_D_P_GUARD_P_M[];
extern const s8 str_D_P_GUARD_P_S[];
extern const s8 str_EDIT_INT[];
extern const s8 str_EDIT_NUM[];
extern const s8 str_EFF01_CHAR[];
extern const s8 str_EFF13_CHAR[];
extern const s8 str_EFFECT[];
extern const s8 str_ELENA[];
extern const s8 str_ELENA_2[];
extern const s8 str_ENFLAND_OBJ[];
extern const s8 str_ENGLAND_1[];
extern const s8 str_ENGLAND_2[];
extern const s8 str_ETC[];
extern const s8 str_ETC_2[];
extern const s8 str_ETC_3[];
extern const s8 str_EX[];
extern const s8 str_FACE_A[];
extern const s8 str_FACE_B[];
extern const s8 str_FACE_C[];
extern const s8 str_FACE_D[];
extern const s8 str_FACE_L[];
extern const s8 str_FACE_M[];
extern const s8 str_FACE_SP[];
extern const s8 str_FACE_S[];
extern const s8 str_FLANKEN_S_A[];
extern const s8 str_FLANKEN_S_B[];
extern const s8 str_FLANKEN_S_C[];
extern const s8 str_FLANKEN_S_D[];
extern const s8 str_FLIP[];
extern const s8 str_FLIP_ED[];
extern const s8 str_FOOK_OKU_L[];
extern const s8 str_FOOK_OKU_M[];
extern const s8 str_FOOK_OKU_SP[];
extern const s8 str_FOOK_OKU_S[];
extern const s8 str_FOOK_TEMAE_L[];
extern const s8 str_FOOK_TEMAE_M[];
extern const s8 str_FOOK_TEMAE_SP[];
extern const s8 str_FOOK_TEMAE_S[];
extern const s8 str_FRONT_WALK[];
extern const s8 str_FURUDERA_OBJ[];
extern const s8 str_FUSHIN_K_L[];
extern const s8 str_FUSHIN_K_M[];
extern const s8 str_FUSHIN_K_S[];
extern const s8 str_FUSHIN_P_L[];
extern const s8 str_FUSHIN_P_M[];
extern const s8 str_FUSHIN_P_S[];
extern const s8 str_F_JUMP_K_L_A[];
extern const s8 str_F_JUMP_K_L_B[];
extern const s8 str_F_JUMP_K_M_A[];
extern const s8 str_F_JUMP_K_M_B[];
extern const s8 str_F_JUMP_K_S_A[];
extern const s8 str_F_JUMP_K_S_B[];
extern const s8 str_F_JUMP_P_L_A[];
extern const s8 str_F_JUMP_P_L_B[];
extern const s8 str_F_JUMP_P_M_A[];
extern const s8 str_F_JUMP_P_M_B[];
extern const s8 str_F_JUMP_P_S_A[];
extern const s8 str_F_JUMP_P_S_B[];
extern const s8 str_GERMANY[];
extern const s8 str_GERMANY_OBJ[];
extern const s8 str_GILL[];
extern const s8 str_GILL_2[];
extern const s8 str_GREECE[];
extern const s8 str_GUARD[];
extern const s8 str_GUARD_AIR[];
extern const s8 str_GUARD_AIR_2[];
extern const s8 str_GUARD_DOWN[];
extern const s8 str_GUARD_DOWN_2[];
extern const s8 str_GUARD_HEAD[];
extern const s8 str_GUARD_HEAD_2[];
extern const s8 str_GUARD_UP[];
extern const s8 str_GUARD_UP_2[];
extern const s8 str_HANASARE[];
extern const s8 str_HAND[];
extern const s8 str_HANEAGARI_A[];
extern const s8 str_HANEAGARI_B[];
extern const s8 str_HANEAGARI_C[];
extern const s8 str_HANEAGARI_D[];
extern const s8 str_HARAIGOSHI_A[];
extern const s8 str_HARAIGOSHI_B[];
extern const s8 str_HARAIGOSHI_C[];
extern const s8 str_HARAIGOSHI_D[];
extern const s8 str_HEAD[];
extern const s8 str_HISS[];
extern const s8 str_HIT[];
extern const s8 str_HIT_IX[];
extern const s8 str_HIT_RANGE[];
extern const s8 str_HOSEI_H[];
extern const s8 str_HS_ME[];
extern const s8 str_HS_YOU[];
extern const s8 str_HUGO[];
extern const s8 str_HUMI_ASIB_A[];
extern const s8 str_HUMI_ASIB_B[];
extern const s8 str_HUMI_ASIB_C[];
extern const s8 str_HUMI_ASIB_D[];
extern const s8 str_HURIMUKI[];
extern const s8 str_HUSHIN_AIR[];
extern const s8 str_HUSHIN_DOWN[];
extern const s8 str_HUSHIN_HEAD[];
extern const s8 str_HUSHIN_UP[];
extern const s8 str_H[];
extern const s8 str_H_2[];
extern const s8 str_H_3[];
extern const s8 str_IBUKI[];
extern const s8 str_IBUKI_2[];
extern const s8 str_IMPACT[];
extern const s8 str_INDEX[];
extern const s8 str_INTERRUT[];
extern const s8 str_INT_END[];
extern const s8 str_IPPONZEOI_A[];
extern const s8 str_IPPONZEOI_B[];
extern const s8 str_IPPONZEOI_C[];
extern const s8 str_IPPONZEOI_D[];
extern const s8 str_JAPAN_1[];
extern const s8 str_JAPAN_1_OBJ[];
extern const s8 str_JAPAN_2[];
extern const s8 str_JAPAN_2_OBJ[];
extern const s8 str_JUDGMENT_LOSE[];
extern const s8 str_JUDGMENT_WAIT[];
extern const s8 str_JUDGMENT_WIN[];
extern const s8 str_JUMP_BACK[];
extern const s8 str_JUMP_FRONT[];
extern const s8 str_JUMP_JUNBI[];
extern const s8 str_JUMP_VERTICAL[];
extern const s8 str_KAGAMI_B_WALK[];
extern const s8 str_KAGAMI_F_WALK[];
extern const s8 str_KAGAMI_KAMAE[];
extern const s8 str_KAGAMI_K_A[];
extern const s8 str_KAGAMI_K_B[];
extern const s8 str_KAGAMI_K_C[];
extern const s8 str_KAGAMI_L[];
extern const s8 str_KAGAMI_M[];
extern const s8 str_KAGAMI_P_A[];
extern const s8 str_KAGAMI_P_B[];
extern const s8 str_KAGAMI_P_C[];
extern const s8 str_KAGAMI_SP[];
extern const s8 str_KAGAMI_S[];
extern const s8 str_KAGAMI_TURN[];
extern const s8 str_KAGAMU[];
extern const s8 str_KAMAE[];
extern const s8 str_KEN[];
extern const s8 str_KEN_2[];
extern const s8 str_KGM_TATAKI_L[];
extern const s8 str_KGM_TATAKI_M[];
extern const s8 str_KGM_TATAKI_SP[];
extern const s8 str_KGM_TATAKI_S[];
extern const s8 str_KGM_TTKI_V_L[];
extern const s8 str_KGM_TTKI_V_M[];
extern const s8 str_KGM_TTKI_V_SP[];
extern const s8 str_KGM_TTKI_V_S[];
extern const s8 str_KIND_WAZA[];
extern const s8 str_KIRIMOMI[];
extern const s8 str_KIRIMOMI_A[];
extern const s8 str_KIRIMOMI_B[];
extern const s8 str_KIRIMOMI_C[];
extern const s8 str_KIRIMOMI_D[];
extern const s8 str_KISHINRIKI_A[];
extern const s8 str_KISHINRIKI_B[];
extern const s8 str_KISHINRIKI_C[];
extern const s8 str_KISHINRIKI_D[];
extern const s8 str_KOC_IX_PT_Nix[];
extern const s8 str_KOC_IX_PT_Nix_2[];
extern const s8 str_KUNOJI_A[];
extern const s8 str_KUNOJI_BUTTOBI[];
extern const s8 str_KUNOJI_B[];
extern const s8 str_KUNOJI_C[];
extern const s8 str_KUNOJI_D[];
extern const s8 str_KUNOJI_NOKE_A[];
extern const s8 str_KUNOJI_NOKE_B[];
extern const s8 str_KUNOJI_NOKE_C[];
extern const s8 str_KUNOJI_NOKE_D[];
extern const s8 str_KUSSHIN_FAST[];
extern const s8 str_KUSSHIN_SLOW[];
extern const s8 str_KYOTO_1[];
extern const s8 str_KYOTO_2[];
extern const s8 str_KYOTO_3[];
extern const s8 str_LEG[];
extern const s8 str_LOSE_KAGAMI[];
extern const s8 str_LOSE_NO_STAND[];
extern const s8 str_LOSE_SONABA[];
extern const s8 str_L_KICK_A[];
extern const s8 str_L_KICK_B[];
extern const s8 str_L_KICK_C[];
extern const s8 str_L_PUNCH_A[];
extern const s8 str_L_PUNCH_B[];
extern const s8 str_L_PUNCH_C[];
extern const s8 str_MLD[];
extern const s8 str_MLF[];
extern const s8 str_MLN[];
extern const s8 str_MLR[];
extern const s8 str_MLU[];
extern const s8 str_MONKEY_FLIP_A[];
extern const s8 str_MONKEY_FLIP_B[];
extern const s8 str_MONKEY_FLIP_C[];
extern const s8 str_MONKEY_FLIP_D[];
extern const s8 str_MOTION[];
extern const s8 str_M[];
extern const s8 str_M_2[];
extern const s8 str_M_KICK_A[];
extern const s8 str_M_KICK_B[];
extern const s8 str_M_KICK_C[];
extern const s8 str_M_PUNCH_A[];
extern const s8 str_M_PUNCH_B[];
extern const s8 str_M_PUNCH_C[];
extern const s8 str_NAGERARE_KAIHI[];
extern const s8 str_NECRO[];
extern const s8 str_NECRO_2[];
extern const s8 str_NEKOROBI_L[];
extern const s8 str_NEKOROBI_M[];
extern const s8 str_NEKOROBI_SP[];
extern const s8 str_NEKOROBI_S[];
extern const s8 str_NM[];
extern const s8 str_NM_BUTTOBI_A[];
extern const s8 str_NM_BUTTOBI_B[];
extern const s8 str_NM_BUTTOBI_C[];
extern const s8 str_NM_BUTTOBI_D[];
extern const s8 str_NM_DM[];
extern const s8 str_NM_JUMP_AT[];
extern const s8 str_NOBASITA_TE_L[];
extern const s8 str_NOBASITA_TE_M[];
extern const s8 str_NOBASITA_TE_SP[];
extern const s8 str_NOBASITA_TE_S[];
extern const s8 str_NOKEZORI_A[];
extern const s8 str_NOKEZORI_B[];
extern const s8 str_NOKEZORI_C[];
extern const s8 str_NOKEZORI_D[];
extern const s8 str_NORMAL[];
extern const s8 str_NOUTEN_L[];
extern const s8 str_NOUTEN_M[];
extern const s8 str_NOUTEN_SP[];
extern const s8 str_NOUTEN_S[];
extern const s8 str_NO_EDIT[];
extern const s8 str_NUM_END[];
extern const s8 str_N_Y_1[];
extern const s8 str_N_Y_1_OBJ_2[];
extern const s8 str_N_Y_2[];
extern const s8 str_N_Y_2_256_OBJ[];
extern const s8 str_N_Y_2_64_OBJ[];
extern const s8 str_OBJECT_EDIT[];
extern const s8 str_OBJECT_EDIT_2[];
extern const s8 str_OBJECT_LOOK[];
extern const s8 str_OBJECT_TEST[];
extern const s8 str_OKIAGARI[];
extern const s8 str_OKIAGARI_B[];
extern const s8 str_OKIAGARI_F[];
extern const s8 str_OKIAGARI_K_L[];
extern const s8 str_OKIAGARI_K_M[];
extern const s8 str_OKIAGARI_K_S[];
extern const s8 str_OKIAGARI_P_L[];
extern const s8 str_OKIAGARI_P_M[];
extern const s8 str_OKIAGARI_P_S[];
extern const s8 str_ORO[];
extern const s8 str_ORO_2[];
extern const s8 str_PARING_AIR_B[];
extern const s8 str_PARING_AIR_F[];
extern const s8 str_PARING_DOWN[];
extern const s8 str_PARING_HEAD[];
extern const s8 str_PARING_UP[];
extern const s8 str_PATTERN[];
extern const s8 str_PAT_ST[];
extern const s8 str_PA[];
extern const s8 str_PB[];
extern const s8 str_PIYO[];
extern const s8 str_PIYO_n[];
extern const s8 str_PLAYER[];
extern const s8 str_PLEF[];
extern const s8 str_PL_13[];
extern const s8 str_PL_14[];
extern const s8 str_PL_15[];
extern const s8 str_POS_X_H[];
extern const s8 str_POS_Y_H[];
extern const s8 str_POW[];
extern const s8 str_Pa[];
extern const s8 str_QUAKE[];
extern const s8 str_REACTION[];
extern const s8 str_REL_X_H[];
extern const s8 str_REL_Y_H[];
extern const s8 str_REVISE_X_H[];
extern const s8 str_REVISE_Y_H[];
extern const s8 str_ROSIA_OBJ[];
extern const s8 str_RUSSIA[];
extern const s8 str_RYU[];
extern const s8 str_RYU_2[];
extern const s8 str_R[];
extern const s8 str_S1[];
extern const s8 str_S2[];
extern const s8 str_S3[];
extern const s8 str_S4[];
extern const s8 str_S5[];
extern const s8 str_S6[];
extern const s8 str_SA[];
extern const s8 str_SEAN[];
extern const s8 str_SEAN_2[];
extern const s8 str_SHIMEOTASARE[];
extern const s8 str_SINSYOURYU_A[];
extern const s8 str_SINSYOURYU_B[];
extern const s8 str_SINSYOURYU_C[];
extern const s8 str_SINSYOURYU_D[];
extern const s8 str_SIZE_X_H[];
extern const s8 str_SIZE_Y_H[];
extern const s8 str_SNAKE_FANG_A[];
extern const s8 str_SNAKE_FANG_B[];
extern const s8 str_SNAKE_FANG_C[];
extern const s8 str_SNAKE_FANG_D[];
extern const s8 str_SPLASH_M_A[];
extern const s8 str_SPLASH_M_B[];
extern const s8 str_SPLASH_M_C[];
extern const s8 str_SPLASH_M_D[];
extern const s8 str_SP_APPEAR_1[];
extern const s8 str_SP_APPEAR_2[];
extern const s8 str_SP_APPEAR_3[];
extern const s8 str_SP_APPEAR_4[];
extern const s8 str_SP_APPEAR_5[];
extern const s8 str_SP_APPEAR_6[];
extern const s8 str_SP_APPEAR_7[];
extern const s8 str_SP_APPEAR_8[];
extern const s8 str_SP_AT[];
extern const s8 str_SP_JUMP_BACK[];
extern const s8 str_SP_JUMP_FRONT[];
extern const s8 str_SP_JUMP_JUNBI[];
extern const s8 str_SP_JUMP_V[];
extern const s8 str_SP_TECH[];
extern const s8 str_SP_WIN_1[];
extern const s8 str_SP_WIN_2[];
extern const s8 str_SP_WIN_3[];
extern const s8 str_SP_WIN_4[];
extern const s8 str_SP_WIN_5[];
extern const s8 str_SP_WIN_6[];
extern const s8 str_SP_WIN_7[];
extern const s8 str_SP_WIN_8[];
extern const s8 str_STAGE[];
extern const s8 str_STAND_UP[];
extern const s8 str_S[];
extern const s8 str_S_JUMP_BACK[];
extern const s8 str_S_JUMP_FRONT[];
extern const s8 str_S_JUMP_V[];
extern const s8 str_S_KICK_A[];
extern const s8 str_S_KICK_B[];
extern const s8 str_S_KICK_C[];
extern const s8 str_S_PUNCH_A[];
extern const s8 str_S_PUNCH_B[];
extern const s8 str_S_PUNCH_C[];
extern const s8 str_TATAKITUKERARE[];
extern const s8 str_TATAKI_AIR_A[];
extern const s8 str_TATAKI_AIR_B[];
extern const s8 str_TATAKI_AIR_C[];
extern const s8 str_TATAKI_AIR_D[];
extern const s8 str_TATAKI_L[];
extern const s8 str_TATAKI_M[];
extern const s8 str_TATAKI_SP[];
extern const s8 str_TATAKI_S[];
extern const s8 str_TATAKI_V_L[];
extern const s8 str_TATAKI_V_M[];
extern const s8 str_TATAKI_V_SP[];
extern const s8 str_TATAKI_V_S[];
extern const s8 str_TEN_IX[];
extern const s8 str_TOMOE_ORO_A[];
extern const s8 str_TOMOE_ORO_B[];
extern const s8 str_TOMOE_ORO_C[];
extern const s8 str_TOMOE_ORO_D[];
extern const s8 str_TOMOE_RYU_A[];
extern const s8 str_TOMOE_RYU_B[];
extern const s8 str_TOMOE_RYU_C[];
extern const s8 str_TOMOE_RYU_D[];
extern const s8 str_TOUKETSU_A[];
extern const s8 str_TOUKETSU_B[];
extern const s8 str_TOUKETSU_C[];
extern const s8 str_TOUKETSU_D[];
extern const s8 str_TRUNK_1[];
extern const s8 str_TRUNK_2[];
extern const s8 str_TTKI_V_AIR_A[];
extern const s8 str_TTKI_V_AIR_B[];
extern const s8 str_TTKI_V_AIR_C[];
extern const s8 str_TTKI_V_AIR_D[];
extern const s8 str_TUKAMIKAKARI_1[];
extern const s8 str_TUKAMIKAKARI_2[];
extern const s8 str_TUKAMIKAKARI_3[];
extern const s8 str_TUKAMIKAKARI_4[];
extern const s8 str_TUKAMIKAKARI_A[];
extern const s8 str_TUKAMIKAKARI_B[];
extern const s8 str_TUKAMIKAKARI_C_2[];
extern const s8 str_TUKAMIKAKARI_D_2[];
extern const s8 str_TUKAMIKAKARI_E_2[];
extern const s8 str_TUKAMIKAKARI_F_2[];
extern const s8 str_TUNNOMERI_A[];
extern const s8 str_TUNNOMERI_B[];
extern const s8 str_TUNNOMERI_C[];
extern const s8 str_TUNNOMERI_D[];
extern const s8 str_UKEMI_MOVE_F[];
extern const s8 str_UKEMI_MOVE_R[];
extern const s8 str_UNION[];
extern const s8 str_UPPER_A[];
extern const s8 str_UPPER_B[];
extern const s8 str_UPPER_C[];
extern const s8 str_UPPER_D[];
extern const s8 str_UPPER_L[];
extern const s8 str_UPPER_M[];
extern const s8 str_UPPER_SP[];
extern const s8 str_UPPER_S[];
extern const s8 str_UP_P_GUARD_K_L[];
extern const s8 str_UP_P_GUARD_K_M[];
extern const s8 str_UP_P_GUARD_K_S[];
extern const s8 str_UP_P_GUARD_P_L[];
extern const s8 str_UP_P_GUARD_P_M[];
extern const s8 str_UP_P_GUARD_P_S[];
extern const s8 str_USEMJ[];
extern const s8 str_VS_ID[];
extern const s8 str_V_JUMP_K_L_A[];
extern const s8 str_V_JUMP_K_L_B[];
extern const s8 str_V_JUMP_K_M_A[];
extern const s8 str_V_JUMP_K_M_B[];
extern const s8 str_V_JUMP_K_S_A[];
extern const s8 str_V_JUMP_K_S_B[];
extern const s8 str_V_JUMP_P_L_A[];
extern const s8 str_V_JUMP_P_L_B[];
extern const s8 str_V_JUMP_P_M_A[];
extern const s8 str_V_JUMP_P_M_B[];
extern const s8 str_V_JUMP_P_S_A[];
extern const s8 str_V_JUMP_P_S_B[];
extern const s8 str_WALK_END[];
extern const s8 str_WCA[];
extern const s8 str_WCA_IX[];
extern const s8 str_WIN_1[];
extern const s8 str_WIN_2[];
extern const s8 str_WIN_3[];
extern const s8 str_WIN_4[];
extern const s8 str_WIN_5[];
extern const s8 str_WIN_6[];
extern const s8 str_WIN_7[];
extern const s8 str_WIN_8[];
extern const s8 str_YANG[];
extern const s8 str_YOKE_PAT[];
extern const s8 str_YOKE_TYPE[];
extern const s8 str_YUN[];
extern const s8 str_YUN_2[];
extern const s8 str_YUN_YAN[];
extern const s8 str_ZANNEN_1[];
extern const s8 str_ZANNEN_2[];
extern const s8 str_ZANNEN_3[];
extern const s8 str_ZANNEN_4[];
extern const s8 str_ZANNEN_5[];
extern const s8 str_ZANNEN_6[];
extern const s8 str_ZANNEN_7[];
extern const s8 str_ZANNEN_8[];
extern const s8 str_ZOKUSEI[];
extern const s8 str_ZU_FLAG[];
extern const s8 str_a[];
extern const s8 str_a_2[];
extern const s8 str_blank_10[];
extern const s8 str_blank_11[];
extern const s8 str_blank_12[];
extern const s8 str_blank_13[];
extern const s8 str_blank_14[];
extern const s8 str_blank_4[];
extern const s8 str_blank_5[];
extern const s8 str_blank_6[];
extern const s8 str_blank_7[];
extern const s8 str_blank_8[];
extern const s8 str_blank_9[];
extern const s8 str_c[];
extern const s8 str_c_2[];
extern const s8 str_d[];
extern const s8 str_d_2[];
extern const s8 str_empty_9[];
extern const s8 str_h[];
extern const s8 str_h_2[];
extern const s8 str_hsA[];
extern const s8 str_hsC[];
extern const s8 str_huA[];
extern const s8 str_m[];
extern const s8 str_m_2[];
extern const s8 str_nmA[];
extern const s8 str_nmC[];
extern const s8 str_paA[];
extern const s8 str_r[];
extern const s8 str_r_2[];
extern const s8 str_s[];
extern const s8 str_s_2[];
extern const s8 str_saA[];
extern const s8 str_saC[];
extern const s8 str_sl_00[];
extern const s8 str_sl_10[];
extern const s8 str_sl_12[];
extern const s8 str_sl_20[];
extern const s8 str_sl_22[];
extern const s8 str_sl_30[];
extern const s8 str_sl_32[];
extern const s8 str_sl_40[];
extern const s8 str_sl_42[];
extern const s8 str_sl_44[];
extern const s8 str_sl_50[];
extern const s8 str_sl_52[];
extern const s8 str_sl_54[];
extern const s8 str_sl_60[];
extern const s8 str_sl_62[];
extern const s8 str_sl_64[];
extern const s8 str_sl_70[];
extern const s8 str_sl_80[];
extern const s8 str_sl_82[];
extern const s8 str_sl_90[];
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
    { 13, 2, 2, str_OBJECT_TEST },
    { 10, 4, 2, str_OBJECT_LOOK },
    { 10, 5, 2, str_OBJECT_EDIT },
    { 10, 6, 2, str_OBJECT_EDIT_2 },
    { 10, 7, 2, str_HIT },
    { 10, 8, 2, str_ALL_CHARACTER },
    { 10, 9, 2, str_BG_BLOCK },
};

/* 02000EE0 */
TM_STRING dbg_obj_info_str[10] = {
    { 1, 3, 2, str_PLAYER }, { 1, 4, 2, str_ALL },
    { 1, 6, 2, str_MOTION }, { 1, 8, 2, str_PATTERN },
    { 1, 9, 2, str_INTERRUT }, { 1, 10, 2, str_CODE_H },
    { 1, 11, 2, str_FLIP }, { 1, 12, 2, str_FLIP_ED },
    { 1, 13, 2, str_POS_X_H }, { 1, 14, 2, str_POS_Y_H },
};

/* 02000F58 */
TM_STRING dbg_obj_rel_str[3] = {
    { 1, 15, 2, str_REL_X_H }, { 1, 16, 2, str_REL_Y_H },
    { 1, 17, 2, str_CURRENT },
};

/* 02000F7C */
TM_STRING dbg_all_char_str[3] = {
    { 15, 1, 2, str_ALL_CHARACTER },
    { 1, 5, 2, str_H },
    { 1, 7, 2, str_H_2 },
};

/* 02000FA0 */
TM_STRING dbg_edit_num_str[4] = {
    { 1, 18, 2, str_EDIT_NUM }, { 1, 19, 2, str_NUM_END },
    { 1, 20, 2, str_EDIT_INT }, { 1, 21, 2, str_INT_END },
};

/* 02000FD0 */
TM_STRING dbg_rec_menu_str[3] = {
    { 27, 3, 6, str_DELETE_ALL_SH4 },
    { 27, 4, 6, str_1DATA_SH5 },
    { 27, 5, 6, str_CANCEL_SH6 },
};

/* 02000FF4 */
TM_STRING dbg_rec_clear_str[3] = {
    { 27, 3, 6, str_blank_4 }, { 27, 4, 6, str_blank_4 },
    { 27, 5, 6, str_blank_5 },
};

/* 02001018 */
TM_STRING dbg_rec_nodata_str[2] = {
    { 27, 3, 6, str_NO_EDIT },
    { 27, 4, 6, str_DATA_NOTHING },
};

/* 02001030 */
TM_STRING dbg_hit_size_str[13] = {
    { 1, 15, 2, str_REVISE_X_H },
    { 1, 16, 2, str_SIZE_X_H },
    { 1, 17, 2, str_REVISE_Y_H },
    { 1, 18, 2, str_SIZE_Y_H },
    { 1, 20, 2, str_INDEX },
    { 1, 21, 2, str_BODY_H },
    { 1, 22, 2, str_ATTACK_H },
    { 1, 23, 2, str_CAUGHT_H },
    { 1, 24, 2, str_HOSEI_H },
    { 1, 25, 2, str_CURRENT_2 },
    { 15, 25, 2, str_KOC_IX_PT_Nix },
    { 15, 26, 2, str_KOC_IX_PT_Nix },
    { 15, 27, 2, str_KOC_IX_PT_Nix_2 },
};

/* 020010CC */
TM_STRING dbg_hit_part_str[40] = {
    { 36, 16, 2, str_HEAD },
    { 36, 17, 2, str_BREAST },
    { 36, 18, 2, str_TRUNK_1 },
    { 36, 19, 2, str_LEG },
    { 36, 20, 2, str_HAND },
    { 36, 21, 2, str_CATCH_n },
    { 36, 22, 2, str_ATTACK_1 },
    { 36, 23, 2, str_ATTACK_2 },
    { 36, 24, 2, str_CAUGHT_n },
    { 36, 25, 2, str_TRUNK_2 },
    { 1, 2, 2, str_STAGE },
    { 1, 3, 2, str_BLOCK_NO },
    { 11, 2, 2, str_GREECE },
    { 11, 2, 2, str_N_Y_1 },
    { 11, 2, 2, str_N_Y_2 },
    { 11, 2, 2, str_JAPAN_1 },
    { 11, 2, 2, str_JAPAN_2 },
    { 11, 2, 2, str_CHAINA_1 },
    { 11, 2, 2, str_CHAINA_2 },
    { 11, 2, 2, str_ENGLAND_1 },
    { 11, 2, 2, str_ENGLAND_2 },
    { 11, 2, 2, str_RUSSIA },
    { 11, 2, 2, str_GERMANY },
    { 11, 2, 2, str_KYOTO_1 },
    { 11, 2, 2, str_KYOTO_2 },
    { 11, 2, 2, str_KYOTO_3 },
    { 11, 2, 2, str_AFRICA_1 },
    { 11, 2, 2, str_AFRICA_2 },
    { 11, 2, 2, str_BRAZIL },
    { 2, 1, 2, str_GILL },
    { 2, 1, 2, str_ALEX },
    { 2, 1, 2, str_RYU },
    { 2, 1, 2, str_YUN },
    { 2, 1, 2, str_DUDDLY },
    { 2, 1, 2, str_NECRO },
    { 2, 1, 2, str_IBUKI },
    { 2, 1, 2, str_ELENA },
    { 2, 1, 2, str_ORO },
    { 2, 1, 2, str_KEN },
    { 2, 1, 2, str_SEAN },
};

/* 020012AC */
TM_STRING dbg_cg_head_str[6] = {
    { 27, 3, 2, str_CG_CTR },
    { 27, 4, 2, str_CG_TYPE },
    { 27, 5, 2, str_CG_SE },
    { 27, 6, 2, str_CG_FLIP },
    { 27, 7, 2, str_CG_OLC_IX },
    { 27, 8, 2, str_CG_NUMBER },
};

/* 020012F4 */
TM_STRING dbg_cg_att_str[6] = {
    { 27, 10, 2, str_CG_ATT_IX },
    { 27, 11, 2, str_CG_HIT_IX },
    { 27, 12, 2, str_CG_EXTDAT },
    { 27, 13, 2, str_CG_CANCEL },
    { 27, 14, 2, str_CG_EFFECT },
    { 27, 15, 2, str_CG_EFTYPE },
};

/* 0200133C */
TM_STRING dbg_cg_rival_str[4] = {
    { 27, 16, 2, str_CG_RIVAL },
    { 27, 17, 2, str_CG_ADD_XY },
    { 27, 18, 2, str_CG_NIX },
    { 27, 19, 2, str_CG_STATUS },
};

/* 0200136C */
TM_STRING dbg_cgd_info_str[8] = {
    { 27, 2, 2, str_CGD_TYPE },
    { 27, 3, 2, str_PAT_ST },
    { 27, 4, 2, str_KIND_WAZA },
    { 27, 5, 2, str_HIT_RANGE },
    { 27, 6, 2, str_YOKE_TYPE },
    { 27, 7, 2, str_YOKE_PAT },
    { 27, 8, 2, str_SP_TECH },
    { 27, 9, 2, str_WCA_IX },
};

/* 020013CC */
TM_STRING dbg_att_data_str[21] = {
    { 27, 2, 2, str_ATT_IX },
    { 27, 3, 2, str_REACTION },
    { 27, 4, 2, str_HIT_IX },
    { 27, 5, 2, str_GUARD },
    { 27, 6, 2, str_HISS },
    { 27, 7, 2, str_DIR },
    { 27, 8, 2, str_TEN_IX },
    { 27, 9, 2, str_POW },
    { 27, 10, 2, str_IMPACT },
    { 27, 11, 2, str_PIYO_n },
    { 27, 12, 2, str_HS_ME },
    { 27, 13, 2, str_HS_YOU },
    { 27, 14, 2, str_QUAKE },
    { 27, 15, 2, str_ZU_FLAG },
    { 27, 16, 2, str_ZOKUSEI },
    { 27, 17, 2, str_AT_LEVEL },
    { 27, 18, 2, str_ADD_ARTS },
    { 27, 19, 2, str_BUTT_TYPE },
    { 27, 20, 2, str_BUTT_PAT },
    { 27, 21, 2, str_DIR_ATT },
    { 27, 22, 2, str_VS_ID },
};

/* 020014C8 */
TM_STRING dbg_hud_clr_str[26] = {
    { 27, 2, 2, str_blank_6 },
    { 27, 3, 2, str_blank_6 },
    { 27, 4, 2, str_blank_6 },
    { 27, 5, 2, str_blank_6 },
    { 27, 6, 2, str_blank_6 },
    { 27, 7, 2, str_blank_6 },
    { 27, 8, 2, str_blank_6 },
    { 27, 9, 2, str_blank_6 },
    { 27, 10, 2, str_blank_6 },
    { 27, 11, 2, str_blank_6 },
    { 27, 12, 2, str_blank_6 },
    { 27, 13, 2, str_blank_6 },
    { 27, 14, 2, str_blank_6 },
    { 27, 15, 2, str_blank_6 },
    { 27, 16, 2, str_blank_6 },
    { 27, 17, 2, str_blank_6 },
    { 27, 18, 2, str_blank_6 },
    { 27, 19, 2, str_blank_6 },
    { 27, 20, 2, str_blank_6 },
    { 27, 21, 2, str_blank_6 },
    { 27, 22, 2, str_blank_6 },
    { 27, 23, 2, str_blank_6 },
    { 27, 24, 2, str_blank_6 },
    { 27, 25, 2, str_blank_6 },
    { 27, 26, 2, str_blank_6 },
    { 27, 27, 2, str_blank_7 },
};

/* 02001600 */
TM_STRING dbg_hud_clr_mid_str[6] = {
    { 27, 14, 2, str_blank_6 },
    { 27, 15, 2, str_blank_6 },
    { 27, 16, 2, str_blank_6 },
    { 27, 17, 2, str_blank_6 },
    { 27, 18, 2, str_blank_6 },
    { 27, 19, 2, str_blank_6 },
};

/* 02001648 */
TM_STRING dbg_hud_clr_low_str[9] = {
    { 27, 20, 2, str_blank_6 },
    { 27, 21, 2, str_blank_6 },
    { 27, 22, 2, str_blank_6 },
    { 27, 23, 2, str_blank_6 },
    { 27, 24, 2, str_blank_6 },
    { 27, 25, 2, str_blank_6 },
    { 27, 26, 2, str_blank_6 },
    { 27, 27, 2, str_blank_7 },
    { 27, 28, 2, str_blank_7 },
};

/* 020016B4 */
TM_STRING dbg_hud_clr_bottom_str[3] = {
    { 5, 25, 2, str_blank_8 }, { 5, 26, 2, str_blank_8 },
    { 5, 27, 2, str_blank_9 },
};

/* 020016D8 */
TM_STRING dbg_cm_label_str[13] = {
    { 27, 2, 2, str_CMOA }, { 27, 3, 2, str_CMSW },
    { 27, 4, 2, str_CMLP }, { 27, 5, 2, str_CML2 },
    { 27, 6, 2, str_CMJA }, { 27, 7, 2, str_CMJ2 },
    { 27, 8, 2, str_CMJ3 }, { 27, 9, 2, str_CMJ4 },
    { 27, 10, 2, str_CMMS }, { 27, 11, 2, str_CMMD },
    { 27, 12, 2, str_CMYD }, { 27, 13, 2, str_CMCF },
    { 27, 14, 2, str_CMCR },
};

/* 02001774 */
TM_STRING dbg_cgd_type_str[5] = {
    { 37, 1, 0xA, str_WCA },
    { 37, 2, 0xA, str_CGD1 },
    { 37, 2, 0xA, str_CGD2 },
    { 37, 2, 0xA, str_CGD3 },
    { 37, 2, 0xA, str_blank_10 },
};

/* 020017B0 */
TM_STRING dbg_pat_status_str[23] = {
    { 37, 3, 0xA, str_sl_00 },
    { 37, 3, 0xA, str_sl_10 },
    { 37, 3, 0xA, str_sl_12 },
    { 37, 3, 0xA, str_sl_20 },
    { 37, 3, 0xA, str_sl_22 },
    { 37, 3, 0xA, str_sl_30 },
    { 37, 3, 0xA, str_sl_32 },
    { 37, 3, 0xA, str_sl_40 },
    { 37, 3, 0xA, str_sl_42 },
    { 37, 3, 0xA, str_sl_44 },
    { 37, 3, 0xA, str_sl_50 },
    { 37, 3, 0xA, str_sl_52 },
    { 37, 3, 0xA, str_sl_54 },
    { 37, 3, 0xA, str_sl_60 },
    { 37, 3, 0xA, str_sl_62 },
    { 37, 3, 0xA, str_sl_64 },
    { 37, 3, 0xA, str_sl_70 },
    { 37, 3, 0xA, str_sl_80 },
    { 37, 3, 0xA, str_sl_82 },
    { 37, 3, 0xA, str_sl_90 },
    { 37, 3, 0xA, str_blank_11 },
    { 37, 3, 0xA, str_blank_11 },
    { 37, 3, 0xA, str_blank_11 },
};

/* 020018C4 */
TM_STRING dbg_cg_group_str[90] = {
    { 37, 8, 0xA, str_BCP00 },
    { 37, 8, 0xA, str_BCP01 },
    { 37, 8, 0xA, str_BCP02 },
    { 37, 8, 0xA, str_BCP03 },
    { 37, 8, 0xA, str_BCP04 },
    { 37, 8, 0xA, str_BCP05 },
    { 37, 8, 0xA, str_BCP06 },
    { 37, 8, 0xA, str_BCP07 },
    { 37, 8, 0xA, str_BCP08 },
    { 37, 8, 0xA, str_BCP09 },
    { 37, 8, 0xA, str_BCP10 },
    { 37, 8, 0xA, str_BCP11 },
    { 37, 8, 0xA, str_BCP12 },
    { 37, 8, 0xA, str_BCP13 },
    { 37, 8, 0xA, str_BCP14 },
    { 37, 8, 0xA, str_BCP15 },
    { 37, 8, 0xA, str_BCP20 },
    { 37, 8, 0xA, str_BCP21 },
    { 37, 8, 0xA, str_BCP22 },
    { 37, 8, 0xA, str_BCP23 },
    { 37, 8, 0xA, str_BCP24 },
    { 37, 8, 0xA, str_BCP25 },
    { 37, 8, 0xA, str_BCP26 },
    { 37, 8, 0xA, str_BCP27 },
    { 37, 8, 0xA, str_BCP28 },
    { 37, 8, 0xA, str_BCP29 },
    { 37, 8, 0xA, str_BCP30 },
    { 37, 8, 0xA, str_BCP31 },
    { 37, 8, 0xA, str_BCP32 },
    { 37, 8, 0xA, str_BCP33 },
    { 37, 8, 0xA, str_BCP34 },
    { 37, 8, 0xA, str_BCP35 },
    { 37, 8, 0xA, str_BCP36 },
    { 37, 8, 0xA, str_BCP37 },
    { 37, 8, 0xA, str_BCP38 },
    { 37, 8, 0xA, str_BCP39 },
    { 37, 8, 0xA, str_BCP40 },
    { 37, 8, 0xA, str_BCP41 },
    { 37, 8, 0xA, str_BCP42 },
    { 37, 8, 0xA, str_BCP43 },
    { 37, 8, 0xA, str_BCP44 },
    { 37, 8, 0xA, str_BCP45 },
    { 37, 8, 0xA, str_BCP46 },
    { 37, 8, 0xA, str_BCP47 },
    { 37, 8, 0xA, str_BCP48 },
    { 37, 8, 0xA, str_BCP49 },
    { 37, 8, 0xA, str_BCP50 },
    { 37, 8, 0xA, str_BCP51 },
    { 37, 8, 0xA, str_BCP52 },
    { 37, 8, 0xA, str_BCP53 },
    { 37, 8, 0xA, str_BCP54 },
    { 37, 8, 0xA, str_BCP55 },
    { 37, 8, 0xA, str_BCP56 },
    { 37, 8, 0xA, str_BCP57 },
    { 37, 8, 0xA, str_BCP58 },
    { 37, 8, 0xA, str_BCP59 },
    { 37, 8, 0xA, str_BCP60 },
    { 37, 8, 0xA, str_BCP61 },
    { 37, 8, 0xA, str_BCP62 },
    { 37, 8, 0xA, str_BCP63 },
    { 37, 8, 0xA, str_BCP64 },
    { 37, 8, 0xA, str_BCP65 },
    { 37, 8, 0xA, str_BCP66 },
    { 37, 8, 0xA, str_BCP67 },
    { 37, 8, 0xA, str_BCP68 },
    { 37, 8, 0xA, str_BCP69 },
    { 37, 8, 0xA, str_BCP70 },
    { 37, 8, 0xA, str_BCP71 },
    { 37, 8, 0xA, str_BCP72 },
    { 37, 8, 0xA, str_BCP73 },
    { 37, 8, 0xA, str_BCP74 },
    { 37, 8, 0xA, str_BCP75 },
    { 37, 8, 0xA, str_BCP76 },
    { 37, 8, 0xA, str_BCP77 },
    { 37, 8, 0xA, str_BCP78 },
    { 37, 8, 0xA, str_BCP79 },
    { 37, 8, 0xA, str_BCP80 },
    { 37, 8, 0xA, str_BCP81 },
    { 37, 8, 0xA, str_BCP82 },
    { 37, 8, 0xA, str_BCP83 },
    { 37, 8, 0xA, str_BCP84 },
    { 37, 8, 0xA, str_BCP85 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
    { 37, 8, 0xA, str_blank_12 },
};

/* 02001CFC */
TM_STRING dbg_preview_group_str[96] = {
    { 4, 5, 2, str_BCP00 }, { 4, 5, 2, str_BCP01 },
    { 4, 5, 2, str_BCP02 }, { 4, 5, 2, str_BCP03 },
    { 4, 5, 2, str_BCP04 }, { 4, 5, 2, str_BCP05 },
    { 4, 5, 2, str_BCP06 }, { 4, 5, 2, str_BCP07 },
    { 4, 5, 2, str_BCP08 }, { 4, 5, 2, str_BCP09 },
    { 4, 5, 2, str_BCP10 }, { 4, 5, 2, str_BCP11 },
    { 4, 5, 2, str_BCP12 }, { 4, 5, 2, str_BCP13 },
    { 4, 5, 2, str_BCP14 }, { 4, 5, 2, str_BCP15 },
    { 4, 5, 2, str_BCP20 }, { 4, 5, 2, str_BCP21 },
    { 4, 5, 2, str_BCP22 }, { 4, 5, 2, str_BCP23 },
    { 4, 5, 2, str_BCP24 }, { 4, 5, 2, str_BCP25 },
    { 4, 5, 2, str_BCP26 }, { 4, 5, 2, str_BCP27 },
    { 4, 5, 2, str_BCP28 }, { 4, 5, 2, str_BCP29 },
    { 4, 5, 2, str_BCP30 }, { 4, 5, 2, str_BCP31 },
    { 4, 5, 2, str_BCP32 }, { 4, 5, 2, str_BCP33 },
    { 4, 5, 2, str_BCP34 }, { 4, 5, 2, str_BCP35 },
    { 4, 5, 2, str_BCP36 }, { 4, 5, 2, str_BCP37 },
    { 4, 5, 2, str_BCP38 }, { 4, 5, 2, str_BCP39 },
    { 4, 5, 2, str_BCP40 }, { 4, 5, 2, str_BCP41 },
    { 4, 5, 2, str_BCP42 }, { 4, 5, 2, str_BCP43 },
    { 4, 5, 2, str_BCP44 }, { 4, 5, 2, str_BCP45 },
    { 4, 5, 2, str_BCP46 }, { 4, 5, 2, str_BCP47 },
    { 4, 5, 2, str_BCP48 }, { 4, 5, 2, str_BCP49 },
    { 4, 5, 2, str_BCP50 }, { 4, 5, 2, str_BCP51 },
    { 4, 5, 2, str_BCP52 }, { 4, 5, 2, str_BCP53 },
    { 4, 5, 2, str_BCP54 }, { 4, 5, 2, str_BCP55 },
    { 4, 5, 2, str_BCP56 }, { 4, 5, 2, str_BCP57 },
    { 4, 5, 2, str_BCP58 }, { 4, 5, 2, str_BCP59 },
    { 4, 5, 2, str_BCP60 }, { 4, 5, 2, str_BCP61 },
    { 4, 5, 2, str_BCP62 }, { 4, 5, 2, str_BCP63 },
    { 4, 5, 2, str_BCP64 }, { 4, 5, 2, str_BCP65 },
    { 4, 5, 2, str_BCP66 }, { 4, 5, 2, str_BCP67 },
    { 4, 5, 2, str_BCP68 }, { 4, 5, 2, str_BCP69 },
    { 4, 5, 2, str_BCP70 }, { 4, 5, 2, str_BCP71 },
    { 4, 5, 2, str_BCP72 }, { 4, 5, 2, str_BCP73 },
    { 4, 5, 2, str_BCP74 }, { 4, 5, 2, str_BCP75 },
    { 4, 5, 2, str_BCP76 }, { 4, 5, 2, str_BCP77 },
    { 4, 5, 2, str_BCP78 }, { 4, 5, 2, str_BCP79 },
    { 4, 5, 2, str_BCP80 }, { 4, 5, 2, str_BCP81 },
    { 4, 5, 2, str_BCP82 }, { 4, 5, 2, str_BCP83 },
    { 4, 5, 2, str_BCP84 }, { 4, 5, 2, str_BCP85 },
    { 4, 5, 2, str_BCP86 }, { 4, 5, 2, str_BCP87 },
    { 4, 5, 2, str_BCP88 }, { 4, 5, 2, str_BCP89 },
    { 4, 5, 2, str_BCP90 }, { 4, 5, 2, str_BCP91 },
    { 4, 5, 2, str_BCP92 }, { 4, 5, 2, str_BCP93 },
    { 4, 5, 2, str_blank_12 }, { 4, 5, 2, str_blank_12 },
    { 4, 5, 2, str_blank_12 }, { 4, 5, 2, str_blank_12 },
    { 4, 5, 2, str_blank_12 }, { 4, 5, 2, str_blank_12 },
};

/* 0200217C */
TM_STRING dbg_edit_group_str[99] = {
    { 1, 25, 2, str_BCP00 }, { 1, 25, 2, str_BCP01 },
    { 1, 25, 2, str_BCP02 }, { 1, 25, 2, str_BCP03 },
    { 1, 25, 2, str_BCP04 }, { 1, 25, 2, str_BCP05 },
    { 1, 25, 2, str_BCP06 }, { 1, 25, 2, str_BCP07 },
    { 1, 25, 2, str_BCP08 }, { 1, 25, 2, str_BCP09 },
    { 1, 25, 2, str_BCP10 }, { 1, 25, 2, str_BCP11 },
    { 1, 25, 2, str_BCP12 }, { 1, 25, 2, str_BCP13 },
    { 1, 25, 2, str_BCP14 }, { 1, 25, 2, str_BCP15 },
    { 1, 25, 2, str_BCP20 }, { 1, 25, 2, str_BCP21 },
    { 1, 25, 2, str_BCP22 }, { 1, 25, 2, str_BCP23 },
    { 1, 25, 2, str_BCP24 }, { 1, 25, 2, str_BCP25 },
    { 1, 25, 2, str_BCP26 }, { 1, 25, 2, str_BCP27 },
    { 1, 25, 2, str_BCP28 }, { 1, 25, 2, str_BCP29 },
    { 1, 25, 2, str_BCP30 }, { 1, 25, 2, str_BCP31 },
    { 1, 25, 2, str_BCP32 }, { 1, 25, 2, str_BCP33 },
    { 1, 25, 2, str_BCP34 }, { 1, 25, 2, str_BCP35 },
    { 1, 25, 2, str_BCP36 }, { 1, 25, 2, str_BCP37 },
    { 1, 25, 2, str_BCP38 }, { 1, 25, 2, str_BCP39 },
    { 1, 25, 2, str_BCP40 }, { 1, 25, 2, str_BCP41 },
    { 1, 25, 2, str_BCP42 }, { 1, 25, 2, str_BCP43 },
    { 1, 25, 2, str_BCP44 }, { 1, 25, 2, str_BCP45 },
    { 1, 25, 2, str_BCP46 }, { 1, 25, 2, str_BCP47 },
    { 1, 25, 2, str_BCP48 }, { 1, 25, 2, str_BCP49 },
    { 1, 25, 2, str_BCP50 }, { 1, 25, 2, str_BCP51 },
    { 1, 25, 2, str_BCP52 }, { 1, 25, 2, str_BCP53 },
    { 1, 25, 2, str_BCP54 }, { 1, 25, 2, str_BCP55 },
    { 1, 25, 2, str_BCP56 }, { 1, 25, 2, str_BCP57 },
    { 1, 25, 2, str_BCP58 }, { 1, 25, 2, str_BCP59 },
    { 1, 25, 2, str_BCP60 }, { 1, 25, 2, str_BCP61 },
    { 1, 25, 2, str_BCP62 }, { 1, 25, 2, str_BCP63 },
    { 1, 25, 2, str_BCP64 }, { 1, 25, 2, str_BCP65 },
    { 1, 25, 2, str_BCP66 }, { 1, 25, 2, str_BCP67 },
    { 1, 25, 2, str_BCP68 }, { 1, 25, 2, str_BCP69 },
    { 1, 25, 2, str_BCP70 }, { 1, 25, 2, str_BCP71 },
    { 1, 25, 2, str_BCP72 }, { 1, 25, 2, str_BCP73 },
    { 1, 25, 2, str_BCP74 }, { 1, 25, 2, str_BCP75 },
    { 1, 25, 2, str_BCP76 }, { 1, 25, 2, str_BCP77 },
    { 1, 25, 2, str_BCP78 }, { 1, 25, 2, str_BCP79 },
    { 1, 25, 2, str_BCP80 }, { 1, 25, 2, str_BCP81 },
    { 1, 25, 2, str_BCP82 }, { 1, 25, 2, str_BCP83 },
    { 1, 25, 2, str_BCP84 }, { 1, 25, 2, str_BCP85 },
    { 1, 25, 2, str_BCP86 }, { 1, 25, 2, str_BCP87 },
    { 1, 25, 2, str_BCP88 }, { 1, 25, 2, str_BCP89 },
    { 1, 25, 2, str_BCP90 }, { 1, 25, 2, str_BCP91 },
    { 1, 25, 2, str_BCP92 }, { 1, 25, 2, str_BCP93 },
    { 1, 25, 2, str_blank_12 }, { 1, 25, 2, str_blank_12 },
    { 1, 25, 2, str_blank_12 }, { 1, 25, 2, str_blank_12 },
    { 1, 25, 2, str_blank_12 }, { 1, 25, 2, str_blank_12 },
    { 1, 25, 2, str_blank_12 }, { 1, 25, 2, str_blank_12 },
    { 1, 25, 2, str_blank_12 },
};

/* 02002620 */
TM_STRING dbg_extdat_str[3] = {
    { 37, 12, 0xA, str_Pa }, { 37, 12, 0xA, str_PA },
    { 37, 12, 0xA, str_PB },
};

/* 02002644 */
TM_STRING dbg_eftype_names[9] = {
    { 37, 15, 0xA, str_MLN }, { 37, 15, 0xA, str_MLU },
    { 37, 15, 0xA, str_MLD }, { 37, 15, 0xA, str_MLF },
    { 37, 15, 0xA, str_MLF }, { 37, 15, 0xA, str_MLR },
    { 37, 15, 0xA, str_MLR }, { 37, 15, 0xA, str_MLR },
    { 37, 15, 0xA, str_M },
};

/* 020026B0 */
TM_STRING dbg_eftype_s_str[6] = {
    { 40, 15, 0xA, str_S1 }, { 40, 15, 0xA, str_S2 },
    { 40, 15, 0xA, str_S3 }, { 40, 15, 0xA, str_S4 },
    { 40, 15, 0xA, str_S5 }, { 40, 15, 0xA, str_S6 },
};

/* 020026F8 */
TM_STRING dbg_eftype_usemj_str[8] = {
    { 42, 15, 0xA, str_blank_12 },
    { 42, 15, 0xA, str_USEMJ },
    { 37, 24, 0xA, str_BASE },
    { 37, 24, 0xA, str_BEFORE },
    { 37, 24, 0xA, str_BACK },
    { 37, 24, 0xA, str_blank_12 },
    { 37, 24, 0xA, str_blank_12 },
    { 37, 24, 0xA, str_blank_12 },
};

/* 02002758 */
TM_STRING dbg_cancel_on_str[8] = {
    { 44, 13, 0xA, str_H_3 }, { 43, 13, 0xA, str_D },
    { 42, 13, 0xA, str_A }, { 41, 13, 0xA, str_M_2 },
    { 40, 13, 0xA, str_R }, { 39, 13, 0xA, str_C },
    { 38, 13, 0xA, str_S }, { 37, 13, 0xA, str_S },
};

/* 020027B8 */
TM_STRING dbg_cancel_off_str[24] = {
    { 44, 13, 0xA, str_h }, { 43, 13, 0xA, str_d },
    { 42, 13, 0xA, str_a }, { 41, 13, 0xA, str_m },
    { 40, 13, 0xA, str_r }, { 39, 13, 0xA, str_c },
    { 38, 13, 0xA, str_s }, { 37, 13, 0xA, str_s },
    { 37, 17, 0xA, str_H_3 }, { 38, 17, 0xA, str_D },
    { 39, 17, 0xA, str_A }, { 40, 17, 0xA, str_M_2 },
    { 41, 17, 0xA, str_R }, { 42, 17, 0xA, str_C },
    { 43, 17, 0xA, str_S }, { 44, 17, 0xA, str_S },
    { 37, 17, 0xA, str_h_2 }, { 38, 17, 0xA, str_d_2 },
    { 39, 17, 0xA, str_a_2 }, { 40, 17, 0xA, str_m_2 },
    { 41, 17, 0xA, str_r_2 }, { 42, 17, 0xA, str_c_2 },
    { 43, 17, 0xA, str_s_2 }, { 44, 17, 0xA, str_s_2 },
};

/* 020028D8 */
TM_STRING dbg_koc_cmlp_str[11] = {
    { 12, 25, 0xA, str_NM },
    { 12, 25, 0xA, str_DM },
    { 12, 25, 0xA, str_CA },
    { 12, 25, 0xA, str_CU },
    { 12, 25, 0xA, str_AT },
    { 12, 25, 0xA, str_BT },
    { 12, 25, 0xA, str_EX },
    { 12, 25, 0xA, str_SA },
    { 32, 25, 0xA, str_CB },
    { 32, 25, 0xA, str_blank_13 },
    { 32, 25, 0xA, str_blank_13 },
};

/* 0200295C */
TM_STRING dbg_koc_cml2_str[11] = {
    { 12, 26, 0xA, str_NM },
    { 12, 26, 0xA, str_DM },
    { 12, 26, 0xA, str_CA },
    { 12, 26, 0xA, str_CU },
    { 12, 26, 0xA, str_AT },
    { 12, 26, 0xA, str_BT },
    { 12, 26, 0xA, str_EX },
    { 12, 26, 0xA, str_SA },
    { 32, 26, 0xA, str_CB },
    { 32, 26, 0xA, str_blank_13 },
    { 32, 26, 0xA, str_blank_13 },
};

/* 020029E0 */
TM_STRING dbg_koc_cmsw_str[11] = {
    { 32, 25, 0xA, str_NM },
    { 32, 25, 0xA, str_DM },
    { 32, 25, 0xA, str_CA },
    { 32, 25, 0xA, str_CU },
    { 32, 25, 0xA, str_AT },
    { 32, 25, 0xA, str_SA },
    { 32, 25, 0xA, str_BT },
    { 32, 25, 0xA, str_EX },
    { 32, 25, 0xA, str_CB },
    { 32, 25, 0xA, str_blank_13 },
    { 32, 25, 0xA, str_blank_13 },
};

/* 02002A64 */
TM_STRING dbg_koc_cmja_str[11] = {
    { 32, 26, 0xA, str_NM },
    { 32, 26, 0xA, str_DM },
    { 32, 26, 0xA, str_CA },
    { 32, 26, 0xA, str_CU },
    { 32, 26, 0xA, str_AT },
    { 32, 26, 0xA, str_SA },
    { 32, 26, 0xA, str_BT },
    { 32, 26, 0xA, str_EX },
    { 32, 26, 0xA, str_CB },
    { 32, 26, 0xA, str_blank_13 },
    { 32, 26, 0xA, str_blank_13 },
};

/* 02002AE8 */
TM_STRING dbg_koc_cmoa_str[9] = {
    { 32, 27, 0xA, str_NM }, { 32, 27, 0xA, str_DM },
    { 32, 27, 0xA, str_CA }, { 32, 27, 0xA, str_CU },
    { 32, 27, 0xA, str_AT }, { 32, 27, 0xA, str_SA },
    { 32, 27, 0xA, str_BT }, { 32, 27, 0xA, str_EX },
    { 32, 27, 0xA, str_CB },
};

/* 02002B54 */
TM_STRING dbg_koc_str[9] = {
    { 32, 2, 2, str_NM }, { 32, 2, 2, str_DM },
    { 32, 2, 2, str_CA }, { 32, 2, 2, str_CU },
    { 32, 2, 2, str_AT }, { 32, 2, 2, str_SA },
    { 32, 2, 2, str_BT }, { 32, 2, 2, str_EX },
    { 32, 2, 2, str_CB },
};

/* 02002BC0 */
TM_STRING dbg_waza_kind_str[8] = {
    { 37, 4, 0xA, str_nmA }, { 37, 4, 0xA, str_hsA },
    { 37, 4, 0xA, str_nmC }, { 37, 4, 0xA, str_hsC },
    { 37, 4, 0xA, str_saA }, { 37, 4, 0xA, str_saC },
    { 37, 4, 0xA, str_paA }, { 37, 4, 0xA, str_huA },
};

/* 02002C20 */
TM_STRING dbg_char_name_str[17] = {
    { 11, 3, 2, str_GILL_2 }, { 11, 3, 2, str_ALEX_2 },
    { 11, 3, 2, str_RYU_2 }, { 11, 3, 2, str_YUN_2 },
    { 11, 3, 2, str_DUDLEY }, { 11, 3, 2, str_NECRO_2 },
    { 11, 3, 2, str_HUGO }, { 11, 3, 2, str_IBUKI_2 },
    { 11, 3, 2, str_ELENA_2 }, { 11, 3, 2, str_ORO_2 },
    { 11, 3, 2, str_YANG }, { 11, 3, 2, str_KEN_2 },
    { 11, 3, 2, str_SEAN_2 }, { 11, 3, 2, str_PL_13 },
    { 11, 3, 2, str_PL_14 }, { 11, 3, 2, str_PL_15 },
    { 11, 3, 2, str_ETC },
};

/* 02002CEC */
TM_STRING dbg_act_kind_str[666] = {
    { 3, 5, 4, str_NORMAL },
    { 3, 5, 4, str_DAMAGE },
    { 3, 5, 4, str_CATCH },
    { 3, 5, 4, str_CAUGHT },
    { 3, 5, 4, str_ATTACK },
    { 3, 5, 4, str_SP_AT },
    { 3, 5, 4, str_BUTTOBI },
    { 3, 5, 4, str_UNION },
    { 3, 5, 4, str_ETC_2 },
    { 3, 5, 4, str_ETC_2 },
    { 3, 5, 4, str_EFFECT },
    { 3, 5, 4, str_empty_9 },
    { 3, 7, 4, str_KAMAE },
    { 3, 7, 4, str_HURIMUKI },
    { 3, 7, 4, str_FRONT_WALK },
    { 3, 7, 4, str_BACK_WALK },
    { 3, 7, 4, str_DASH_HUMIKOMI },
    { 3, 7, 4, str_DASH_TOBINOKI },
    { 3, 7, 4, str_KAGAMU },
    { 3, 7, 4, str_KAGAMI_KAMAE },
    { 3, 7, 4, str_KAGAMI_TURN },
    { 3, 7, 4, str_KAGAMI_F_WALK },
    { 3, 7, 4, str_KAGAMI_B_WALK },
    { 3, 7, 4, str_STAND_UP },
    { 3, 7, 4, str_JUMP_JUNBI },
    { 3, 7, 4, str_SP_JUMP_JUNBI },
    { 3, 7, 4, str_JUMP_FRONT },
    { 3, 7, 4, str_JUMP_VERTICAL },
    { 3, 7, 4, str_JUMP_BACK },
    { 3, 7, 4, str_S_JUMP_FRONT },
    { 3, 7, 4, str_S_JUMP_V },
    { 3, 7, 4, str_S_JUMP_BACK },
    { 3, 7, 4, str_SP_JUMP_FRONT },
    { 3, 7, 4, str_SP_JUMP_V },
    { 3, 7, 4, str_SP_JUMP_BACK },
    { 3, 7, 4, str_WALK_END },
    { 3, 7, 4, str_PARING_HEAD },
    { 3, 7, 4, str_PARING_UP },
    { 3, 7, 4, str_PARING_DOWN },
    { 3, 7, 4, str_PARING_AIR_F },
    { 3, 7, 4, str_PARING_AIR_B },
    { 3, 7, 4, str_GUARD_HEAD },
    { 3, 7, 4, str_GUARD_UP },
    { 3, 7, 4, str_GUARD_DOWN },
    { 3, 7, 4, str_GUARD_AIR },
    { 3, 7, 4, str_TUKAMIKAKARI_1 },
    { 3, 7, 4, str_TUKAMIKAKARI_2 },
    { 3, 7, 4, str_TUKAMIKAKARI_3 },
    { 3, 7, 4, str_TUKAMIKAKARI_4 },
    { 3, 7, 4, str_NAGERARE_KAIHI },
    { 3, 7, 4, str_NAGERARE_KAIHI },
    { 3, 7, 4, str_NAGERARE_KAIHI },
    { 3, 7, 4, str_NAGERARE_KAIHI },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_GUARD_HEAD_2 },
    { 3, 7, 4, str_GUARD_UP_2 },
    { 3, 7, 4, str_GUARD_DOWN_2 },
    { 3, 7, 4, str_GUARD_AIR_2 },
    { 3, 7, 4, str_HUSHIN_HEAD },
    { 3, 7, 4, str_HUSHIN_UP },
    { 3, 7, 4, str_HUSHIN_DOWN },
    { 3, 7, 4, str_HUSHIN_AIR },
    { 3, 7, 4, str_FACE_S },
    { 3, 7, 4, str_FACE_M },
    { 3, 7, 4, str_FACE_L },
    { 3, 7, 4, str_FACE_SP },
    { 3, 7, 4, str_FOOK_OKU_S },
    { 3, 7, 4, str_FOOK_OKU_M },
    { 3, 7, 4, str_FOOK_OKU_L },
    { 3, 7, 4, str_FOOK_OKU_SP },
    { 3, 7, 4, str_FOOK_TEMAE_S },
    { 3, 7, 4, str_FOOK_TEMAE_M },
    { 3, 7, 4, str_FOOK_TEMAE_L },
    { 3, 7, 4, str_FOOK_TEMAE_SP },
    { 3, 7, 4, str_UPPER_S },
    { 3, 7, 4, str_UPPER_M },
    { 3, 7, 4, str_UPPER_L },
    { 3, 7, 4, str_UPPER_SP },
    { 3, 7, 4, str_NOUTEN_S },
    { 3, 7, 4, str_NOUTEN_M },
    { 3, 7, 4, str_NOUTEN_L },
    { 3, 7, 4, str_NOUTEN_SP },
    { 3, 7, 4, str_BODY_BROW_S },
    { 3, 7, 4, str_BODY_BROW_M },
    { 3, 7, 4, str_BODY_BROW_L },
    { 3, 7, 4, str_BODY_BROW_SP },
    { 3, 7, 4, str_BODY_UPPER_S },
    { 3, 7, 4, str_BODY_UPPER_M },
    { 3, 7, 4, str_BODY_UPPER_L },
    { 3, 7, 4, str_BODY_UPPER_SP },
    { 3, 7, 4, str_TATAKI_S },
    { 3, 7, 4, str_TATAKI_M },
    { 3, 7, 4, str_TATAKI_L },
    { 3, 7, 4, str_TATAKI_SP },
    { 3, 7, 4, str_TATAKI_V_S },
    { 3, 7, 4, str_TATAKI_V_M },
    { 3, 7, 4, str_TATAKI_V_L },
    { 3, 7, 4, str_TATAKI_V_SP },
    { 3, 7, 4, str_NOBASITA_TE_S },
    { 3, 7, 4, str_NOBASITA_TE_M },
    { 3, 7, 4, str_NOBASITA_TE_L },
    { 3, 7, 4, str_NOBASITA_TE_SP },
    { 3, 7, 4, str_KAGAMI_S },
    { 3, 7, 4, str_KAGAMI_M },
    { 3, 7, 4, str_KAGAMI_L },
    { 3, 7, 4, str_KAGAMI_SP },
    { 3, 7, 4, str_KGM_TATAKI_S },
    { 3, 7, 4, str_KGM_TATAKI_M },
    { 3, 7, 4, str_KGM_TATAKI_L },
    { 3, 7, 4, str_KGM_TATAKI_SP },
    { 3, 7, 4, str_KGM_TTKI_V_S },
    { 3, 7, 4, str_KGM_TTKI_V_M },
    { 3, 7, 4, str_KGM_TTKI_V_L },
    { 3, 7, 4, str_KGM_TTKI_V_SP },
    { 3, 7, 4, str_NEKOROBI_S },
    { 3, 7, 4, str_NEKOROBI_M },
    { 3, 7, 4, str_NEKOROBI_L },
    { 3, 7, 4, str_NEKOROBI_SP },
    { 3, 7, 4, str_OKIAGARI },
    { 3, 7, 4, str_OKIAGARI_F },
    { 3, 7, 4, str_OKIAGARI_B },
    { 3, 7, 4, str_LOSE_NO_STAND },
    { 3, 7, 4, str_LOSE_SONABA },
    { 3, 7, 4, str_LOSE_KAGAMI },
    { 3, 7, 4, str_PIYO },
    { 3, 7, 4, str_UKEMI_MOVE_F },
    { 3, 7, 4, str_UKEMI_MOVE_R },
    { 3, 7, 4, str_SHIMEOTASARE },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_AIR_S },
    { 3, 7, 4, str_AIR_M },
    { 3, 7, 4, str_AIR_L },
    { 3, 7, 4, str_AIR_SP },
    { 3, 7, 4, str_ASHIBARAI_A },
    { 3, 7, 4, str_ASHIBARAI_B },
    { 3, 7, 4, str_ASHIBARAI_C },
    { 3, 7, 4, str_ASHIBARAI_D },
    { 3, 7, 4, str_TUNNOMERI_A },
    { 3, 7, 4, str_TUNNOMERI_B },
    { 3, 7, 4, str_TUNNOMERI_C },
    { 3, 7, 4, str_TUNNOMERI_D },
    { 3, 7, 4, str_NOKEZORI_A },
    { 3, 7, 4, str_NOKEZORI_B },
    { 3, 7, 4, str_NOKEZORI_C },
    { 3, 7, 4, str_NOKEZORI_D },
    { 3, 7, 4, str_KUNOJI_A },
    { 3, 7, 4, str_KUNOJI_B },
    { 3, 7, 4, str_KUNOJI_C },
    { 3, 7, 4, str_KUNOJI_D },
    { 3, 7, 4, str_KIRIMOMI_A },
    { 3, 7, 4, str_KIRIMOMI_B },
    { 3, 7, 4, str_KIRIMOMI_C },
    { 3, 7, 4, str_KIRIMOMI_D },
    { 3, 7, 4, str_UPPER_A },
    { 3, 7, 4, str_UPPER_B },
    { 3, 7, 4, str_UPPER_C },
    { 3, 7, 4, str_UPPER_D },
    { 3, 7, 4, str_BODY_UPPER_A },
    { 3, 7, 4, str_BODY_UPPER_B },
    { 3, 7, 4, str_BODY_UPPER_C },
    { 3, 7, 4, str_BODY_UPPER_D },
    { 3, 7, 4, str_NM_BUTTOBI_A },
    { 3, 7, 4, str_NM_BUTTOBI_B },
    { 3, 7, 4, str_NM_BUTTOBI_C },
    { 3, 7, 4, str_NM_BUTTOBI_D },
    { 3, 7, 4, str_TATAKI_AIR_A },
    { 3, 7, 4, str_TATAKI_AIR_B },
    { 3, 7, 4, str_TATAKI_AIR_C },
    { 3, 7, 4, str_TATAKI_AIR_D },
    { 3, 7, 4, str_TTKI_V_AIR_A },
    { 3, 7, 4, str_TTKI_V_AIR_B },
    { 3, 7, 4, str_TTKI_V_AIR_C },
    { 3, 7, 4, str_TTKI_V_AIR_D },
    { 3, 7, 4, str_HUMI_ASIB_A },
    { 3, 7, 4, str_HUMI_ASIB_B },
    { 3, 7, 4, str_HUMI_ASIB_C },
    { 3, 7, 4, str_HUMI_ASIB_D },
    { 3, 7, 4, str_FACE_A },
    { 3, 7, 4, str_FACE_B },
    { 3, 7, 4, str_FACE_C },
    { 3, 7, 4, str_FACE_D },
    { 3, 7, 4, str_ASIBRI_MAKE_A },
    { 3, 7, 4, str_ASIBRI_MAKE_B },
    { 3, 7, 4, str_ASIBRI_MAKE_C },
    { 3, 7, 4, str_ASIBRI_MAKE_D },
    { 3, 7, 4, str_ASIB_TN_MAKE_A },
    { 3, 7, 4, str_ASIB_TN_MAKE_B },
    { 3, 7, 4, str_ASIB_TN_MAKE_C },
    { 3, 7, 4, str_ASIB_TN_MAKE_D },
    { 3, 7, 4, str_DENKI_A },
    { 3, 7, 4, str_DENKI_B },
    { 3, 7, 4, str_DENKI_C },
    { 3, 7, 4, str_DENKI_D },
    { 3, 7, 4, str_KUNOJI_NOKE_A },
    { 3, 7, 4, str_KUNOJI_NOKE_B },
    { 3, 7, 4, str_KUNOJI_NOKE_C },
    { 3, 7, 4, str_KUNOJI_NOKE_D },
    { 3, 7, 4, str_SINSYOURYU_A },
    { 3, 7, 4, str_SINSYOURYU_B },
    { 3, 7, 4, str_SINSYOURYU_C },
    { 3, 7, 4, str_SINSYOURYU_D },
    { 3, 7, 4, str_HANEAGARI_A },
    { 3, 7, 4, str_HANEAGARI_B },
    { 3, 7, 4, str_HANEAGARI_C },
    { 3, 7, 4, str_HANEAGARI_D },
    { 3, 7, 4, str_TOUKETSU_A },
    { 3, 7, 4, str_TOUKETSU_B },
    { 3, 7, 4, str_TOUKETSU_C },
    { 3, 7, 4, str_TOUKETSU_D },
    { 3, 7, 4, str_BODY_SLAM_A },
    { 3, 7, 4, str_BODY_SLAM_B },
    { 3, 7, 4, str_BODY_SLAM_C },
    { 3, 7, 4, str_BODY_SLAM_D },
    { 3, 7, 4, str_IPPONZEOI_A },
    { 3, 7, 4, str_IPPONZEOI_B },
    { 3, 7, 4, str_IPPONZEOI_C },
    { 3, 7, 4, str_IPPONZEOI_D },
    { 3, 7, 4, str_TOMOE_RYU_A },
    { 3, 7, 4, str_TOMOE_RYU_B },
    { 3, 7, 4, str_TOMOE_RYU_C },
    { 3, 7, 4, str_TOMOE_RYU_D },
    { 3, 7, 4, str_MONKEY_FLIP_A },
    { 3, 7, 4, str_MONKEY_FLIP_B },
    { 3, 7, 4, str_MONKEY_FLIP_C },
    { 3, 7, 4, str_MONKEY_FLIP_D },
    { 3, 7, 4, str_TOMOE_ORO_A },
    { 3, 7, 4, str_TOMOE_ORO_B },
    { 3, 7, 4, str_TOMOE_ORO_C },
    { 3, 7, 4, str_TOMOE_ORO_D },
    { 3, 7, 4, str_SNAKE_FANG_A },
    { 3, 7, 4, str_SNAKE_FANG_B },
    { 3, 7, 4, str_SNAKE_FANG_C },
    { 3, 7, 4, str_SNAKE_FANG_D },
    { 3, 7, 4, str_FLANKEN_S_A },
    { 3, 7, 4, str_FLANKEN_S_B },
    { 3, 7, 4, str_FLANKEN_S_C },
    { 3, 7, 4, str_FLANKEN_S_D },
    { 3, 7, 4, str_KISHINRIKI_A },
    { 3, 7, 4, str_KISHINRIKI_B },
    { 3, 7, 4, str_KISHINRIKI_C },
    { 3, 7, 4, str_KISHINRIKI_D },
    { 3, 7, 4, str_SPLASH_M_A },
    { 3, 7, 4, str_SPLASH_M_B },
    { 3, 7, 4, str_SPLASH_M_C },
    { 3, 7, 4, str_SPLASH_M_D },
    { 3, 7, 4, str_HARAIGOSHI_A },
    { 3, 7, 4, str_HARAIGOSHI_B },
    { 3, 7, 4, str_HARAIGOSHI_C },
    { 3, 7, 4, str_HARAIGOSHI_D },
    { 3, 7, 4, str_ALEX_B_D_A },
    { 3, 7, 4, str_ALEX_B_D_B },
    { 3, 7, 4, str_ALEX_B_D_C },
    { 3, 7, 4, str_ALEX_B_D_D },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_CATCH_1 },
    { 3, 7, 4, str_CATCH_2 },
    { 3, 7, 4, str_CATCH_3 },
    { 3, 7, 4, str_CATCH_4 },
    { 3, 7, 4, str_CATCH_5 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_CATCH_TOBIKOE },
    { 3, 7, 4, str_CATCH_NAGE },
    { 3, 7, 4, str_CATCH_HIZAGERI },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_S_PUNCH_A },
    { 3, 7, 4, str_S_PUNCH_B },
    { 3, 7, 4, str_S_PUNCH_C },
    { 3, 7, 4, str_M_PUNCH_A },
    { 3, 7, 4, str_M_PUNCH_B },
    { 3, 7, 4, str_M_PUNCH_C },
    { 3, 7, 4, str_L_PUNCH_A },
    { 3, 7, 4, str_L_PUNCH_B },
    { 3, 7, 4, str_L_PUNCH_C },
    { 3, 7, 4, str_S_KICK_A },
    { 3, 7, 4, str_S_KICK_B },
    { 3, 7, 4, str_S_KICK_C },
    { 3, 7, 4, str_M_KICK_A },
    { 3, 7, 4, str_M_KICK_B },
    { 3, 7, 4, str_M_KICK_C },
    { 3, 7, 4, str_L_KICK_A },
    { 3, 7, 4, str_L_KICK_B },
    { 3, 7, 4, str_L_KICK_C },
    { 3, 7, 4, str_KAGAMI_P_A },
    { 3, 7, 4, str_KAGAMI_P_B },
    { 3, 7, 4, str_KAGAMI_P_C },
    { 3, 7, 4, str_KAGAMI_P_A },
    { 3, 7, 4, str_KAGAMI_P_B },
    { 3, 7, 4, str_KAGAMI_P_C },
    { 3, 7, 4, str_KAGAMI_P_A },
    { 3, 7, 4, str_KAGAMI_P_B },
    { 3, 7, 4, str_KAGAMI_P_C },
    { 3, 7, 4, str_KAGAMI_K_A },
    { 3, 7, 4, str_KAGAMI_K_B },
    { 3, 7, 4, str_KAGAMI_K_C },
    { 3, 7, 4, str_KAGAMI_K_A },
    { 3, 7, 4, str_KAGAMI_K_B },
    { 3, 7, 4, str_KAGAMI_K_C },
    { 3, 7, 4, str_KAGAMI_K_A },
    { 3, 7, 4, str_KAGAMI_K_B },
    { 3, 7, 4, str_KAGAMI_K_C },
    { 3, 7, 4, str_V_JUMP_P_S_A },
    { 3, 7, 4, str_V_JUMP_P_S_B },
    { 3, 7, 4, str_V_JUMP_P_M_A },
    { 3, 7, 4, str_V_JUMP_P_M_B },
    { 3, 7, 4, str_V_JUMP_P_L_A },
    { 3, 7, 4, str_V_JUMP_P_L_B },
    { 3, 7, 4, str_V_JUMP_K_S_A },
    { 3, 7, 4, str_V_JUMP_K_S_B },
    { 3, 7, 4, str_V_JUMP_K_M_A },
    { 3, 7, 4, str_V_JUMP_K_M_B },
    { 3, 7, 4, str_V_JUMP_K_L_A },
    { 3, 7, 4, str_V_JUMP_K_L_B },
    { 3, 7, 4, str_F_JUMP_P_S_A },
    { 3, 7, 4, str_F_JUMP_P_S_B },
    { 3, 7, 4, str_F_JUMP_P_M_A },
    { 3, 7, 4, str_F_JUMP_P_M_B },
    { 3, 7, 4, str_F_JUMP_P_L_A },
    { 3, 7, 4, str_F_JUMP_P_L_B },
    { 3, 7, 4, str_F_JUMP_K_S_A },
    { 3, 7, 4, str_F_JUMP_K_S_B },
    { 3, 7, 4, str_F_JUMP_K_M_A },
    { 3, 7, 4, str_F_JUMP_K_M_B },
    { 3, 7, 4, str_F_JUMP_K_L_A },
    { 3, 7, 4, str_F_JUMP_K_L_B },
    { 3, 7, 4, str_B_JUMP_P_S_A },
    { 3, 7, 4, str_B_JUMP_P_S_B },
    { 3, 7, 4, str_B_JUMP_P_M_A },
    { 3, 7, 4, str_B_JUMP_P_M_B },
    { 3, 7, 4, str_B_JUMP_P_L_A },
    { 3, 7, 4, str_B_JUMP_P_L_B },
    { 3, 7, 4, str_B_JUMP_K_S_A },
    { 3, 7, 4, str_B_JUMP_K_S_B },
    { 3, 7, 4, str_B_JUMP_K_M_A },
    { 3, 7, 4, str_B_JUMP_K_M_B },
    { 3, 7, 4, str_B_JUMP_K_L_A },
    { 3, 7, 4, str_B_JUMP_K_L_B },
    { 3, 7, 4, str_TUKAMIKAKARI_A },
    { 3, 7, 4, str_TUKAMIKAKARI_B },
    { 3, 7, 4, str_TUKAMIKAKARI_C_2 },
    { 3, 7, 4, str_TUKAMIKAKARI_D_2 },
    { 3, 7, 4, str_TUKAMIKAKARI_E_2 },
    { 3, 7, 4, str_TUKAMIKAKARI_F_2 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_UP_P_GUARD_P_S },
    { 3, 7, 4, str_UP_P_GUARD_P_M },
    { 3, 7, 4, str_UP_P_GUARD_P_L },
    { 3, 7, 4, str_UP_P_GUARD_K_S },
    { 3, 7, 4, str_UP_P_GUARD_K_M },
    { 3, 7, 4, str_UP_P_GUARD_K_L },
    { 3, 7, 4, str_D_P_GUARD_P_S },
    { 3, 7, 4, str_D_P_GUARD_P_M },
    { 3, 7, 4, str_D_P_GUARD_P_L },
    { 3, 7, 4, str_D_P_GUARD_K_S },
    { 3, 7, 4, str_D_P_GUARD_K_M },
    { 3, 7, 4, str_D_P_GUARD_K_L },
    { 3, 7, 4, str_FUSHIN_P_S },
    { 3, 7, 4, str_FUSHIN_P_M },
    { 3, 7, 4, str_FUSHIN_P_L },
    { 3, 7, 4, str_FUSHIN_K_S },
    { 3, 7, 4, str_FUSHIN_K_M },
    { 3, 7, 4, str_FUSHIN_K_L },
    { 3, 7, 4, str_OKIAGARI_P_S },
    { 3, 7, 4, str_OKIAGARI_P_M },
    { 3, 7, 4, str_OKIAGARI_P_L },
    { 3, 7, 4, str_OKIAGARI_K_S },
    { 3, 7, 4, str_OKIAGARI_K_M },
    { 3, 7, 4, str_OKIAGARI_K_L },
    { 3, 7, 4, str_ATTACK_1_S },
    { 3, 7, 4, str_ATTACK_1_M },
    { 3, 7, 4, str_ATTACK_1_L },
    { 3, 7, 4, str_ATTACK_1_SP },
    { 3, 7, 4, str_ATTACK_2_S },
    { 3, 7, 4, str_ATTACK_2_M },
    { 3, 7, 4, str_ATTACK_2_L },
    { 3, 7, 4, str_ATTACK_2_SP },
    { 3, 7, 4, str_ATTACK_3_S },
    { 3, 7, 4, str_ATTACK_3_M },
    { 3, 7, 4, str_ATTACK_3_L },
    { 3, 7, 4, str_ATTACK_3_SP },
    { 3, 7, 4, str_ATTACK_4_S },
    { 3, 7, 4, str_ATTACK_4_M },
    { 3, 7, 4, str_ATTACK_4_L },
    { 3, 7, 4, str_ATTACK_4_SP },
    { 3, 7, 4, str_ATTACK_5_S },
    { 3, 7, 4, str_ATTACK_5_M },
    { 3, 7, 4, str_ATTACK_5_L },
    { 3, 7, 4, str_ATTACK_5_SP },
    { 3, 7, 4, str_ATTACK_6_S },
    { 3, 7, 4, str_ATTACK_6_M },
    { 3, 7, 4, str_ATTACK_6_L },
    { 3, 7, 4, str_ATTACK_6_SP },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_NM_DM },
    { 3, 7, 4, str_KUSSHIN_SLOW },
    { 3, 7, 4, str_KUSSHIN_FAST },
    { 3, 7, 4, str_ASI_B_SIRIMOTI },
    { 3, 7, 4, str_NM_JUMP_AT },
    { 3, 7, 4, str_TATAKITUKERARE },
    { 3, 7, 4, str_BUTTOBI_2 },
    { 3, 7, 4, str_KUNOJI_BUTTOBI },
    { 3, 7, 4, str_KIRIMOMI },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_HANASARE },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_EFF01_CHAR },
    { 3, 7, 4, str_EFF13_CHAR },
    { 3, 7, 4, str_BOSS_STAGE_OBJ },
    { 3, 7, 4, str_N_Y_1_OBJ_2 },
    { 3, 7, 4, str_N_Y_2_64_OBJ },
    { 3, 7, 4, str_N_Y_2_256_OBJ },
    { 3, 7, 4, str_JAPAN_1_OBJ },
    { 3, 7, 4, str_JAPAN_2_OBJ },
    { 3, 7, 4, str_CHAINA_1_OBJ_2 },
    { 3, 7, 4, str_CHAINA_2_OBJ_2 },
    { 3, 7, 4, str_ENFLAND_OBJ },
    { 3, 7, 4, str_ROSIA_OBJ },
    { 3, 7, 4, str_GERMANY_OBJ },
    { 3, 7, 4, str_FURUDERA_OBJ },
    { 3, 7, 4, str_AFRICA_1_2 },
    { 3, 7, 4, str_AFRICA_2_2 },
    { 3, 7, 4, str_BRAZIL_2 },
    { 3, 7, 4, str_YUN_YAN },
    { 3, 7, 4, str_ETC_3 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_PLEF },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_APPEAR_JUNBI_1 },
    { 3, 7, 4, str_APPEAR_JUNBI_2 },
    { 3, 7, 4, str_APPEAR_JUNBI_3 },
    { 3, 7, 4, str_APPEAR_JUNBI_4 },
    { 3, 7, 4, str_APPEAR_JUNBI_5 },
    { 3, 7, 4, str_APPEAR_JUNBI_6 },
    { 3, 7, 4, str_APPEAR_JUNBI_7 },
    { 3, 7, 4, str_APPEAR_JUNBI_8 },
    { 3, 7, 4, str_APPEAR_1 },
    { 3, 7, 4, str_APPEAR_2 },
    { 3, 7, 4, str_APPEAR_3 },
    { 3, 7, 4, str_APPEAR_4 },
    { 3, 7, 4, str_APPEAR_5 },
    { 3, 7, 4, str_APPEAR_6 },
    { 3, 7, 4, str_APPEAR_7 },
    { 3, 7, 4, str_APPEAR_8 },
    { 3, 7, 4, str_SP_APPEAR_1 },
    { 3, 7, 4, str_SP_APPEAR_2 },
    { 3, 7, 4, str_SP_APPEAR_3 },
    { 3, 7, 4, str_SP_APPEAR_4 },
    { 3, 7, 4, str_SP_APPEAR_5 },
    { 3, 7, 4, str_SP_APPEAR_6 },
    { 3, 7, 4, str_SP_APPEAR_7 },
    { 3, 7, 4, str_SP_APPEAR_8 },
    { 3, 7, 4, str_ZANNEN_1 },
    { 3, 7, 4, str_ZANNEN_2 },
    { 3, 7, 4, str_ZANNEN_3 },
    { 3, 7, 4, str_ZANNEN_4 },
    { 3, 7, 4, str_ZANNEN_5 },
    { 3, 7, 4, str_ZANNEN_6 },
    { 3, 7, 4, str_ZANNEN_7 },
    { 3, 7, 4, str_ZANNEN_8 },
    { 3, 7, 4, str_WIN_1 },
    { 3, 7, 4, str_WIN_2 },
    { 3, 7, 4, str_WIN_3 },
    { 3, 7, 4, str_WIN_4 },
    { 3, 7, 4, str_WIN_5 },
    { 3, 7, 4, str_WIN_6 },
    { 3, 7, 4, str_WIN_7 },
    { 3, 7, 4, str_WIN_8 },
    { 3, 7, 4, str_SP_WIN_1 },
    { 3, 7, 4, str_SP_WIN_2 },
    { 3, 7, 4, str_SP_WIN_3 },
    { 3, 7, 4, str_SP_WIN_4 },
    { 3, 7, 4, str_SP_WIN_5 },
    { 3, 7, 4, str_SP_WIN_6 },
    { 3, 7, 4, str_SP_WIN_7 },
    { 3, 7, 4, str_SP_WIN_8 },
    { 3, 7, 4, str_JUDGMENT_WAIT },
    { 3, 7, 4, str_JUDGMENT_WAIT },
    { 3, 7, 4, str_JUDGMENT_WAIT },
    { 3, 7, 4, str_JUDGMENT_WAIT },
    { 3, 7, 4, str_JUDGMENT_WIN },
    { 3, 7, 4, str_JUDGMENT_WIN },
    { 3, 7, 4, str_JUDGMENT_WIN },
    { 3, 7, 4, str_JUDGMENT_WIN },
    { 3, 7, 4, str_JUDGMENT_LOSE },
    { 3, 7, 4, str_JUDGMENT_LOSE },
    { 3, 7, 4, str_JUDGMENT_LOSE },
    { 3, 7, 4, str_JUDGMENT_LOSE },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
    { 3, 7, 4, str_blank_14 },
};

/* 02004C24 */
TM_STRING* dbg_act_name_tbl[11] = {
    &dbg_act_kind_str[12], &dbg_act_kind_str[70],
    &dbg_act_kind_str[301], &dbg_act_kind_str[314],
    &dbg_act_kind_str[326], &dbg_act_kind_str[426],
    &dbg_act_kind_str[158], &dbg_act_kind_str[490],
    &dbg_act_kind_str[596], &dbg_act_kind_str[596],
    &dbg_act_kind_str[559],
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
        (u32 *)stg12_char_table, eff44_char_table, (u32 *)stg02_char_table, (u32 *)stg11_char_table,
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
