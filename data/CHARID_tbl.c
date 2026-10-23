/*
 * CHARID_TBL.C  tables read by HITCHECK.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const CHAR_INIT_ROM char_init_data[];
extern const s16 Dsas_dir_table[];
extern const s8 sel_sp_ch_tbl[];
extern const s16 rsix_r_table[][2];
extern const s16 attr_flame_tbl[];
extern const s16 attr_thunder_tbl[];
extern const s16 attr_freeze_tbl[];
extern const s16 sky_nm_damage_tbl[];
extern const s16 sky_nm2_damage_tbl[];
extern const s16 sky_sp_damage_tbl[];
extern const s16 kagami_damage_tbl[];
extern const s16 kagami2_damage_tbl[];
extern const s16 grd_hand_damage_tbl[];
extern const u8 hddm_damage_tbl[];
extern const u8 trdm_damage_tbl[];
extern const u8 ttk_damage_req_tbl[];
extern const u8 parisucc_pts[][50];
extern const u8 dm_oiuchi_catch[];
extern const ATTACK_ATTR alex_catt_table[];
extern const ATTACK_ATTR dudley_catt_table[];
extern const ATTACK_ATTR ef13_catt_table[];
extern const ATTACK_ATTR elena_catt_table[];
extern const ATTACK_ATTR gill_catt_table[];
extern const ATTACK_ATTR hugo_catt_table[];
extern const ATTACK_ATTR ibuki_catt_table[];
extern const ATTACK_ATTR ken_catt_table[];
extern const ATTACK_ATTR necro_catt_table[];
extern const ATTACK_ATTR oro_catt_table[];
extern const ATTACK_ATTR ryu_catt_table[];
extern const ATTACK_ATTR sean_catt_table[];
extern const ATTACK_ATTR yang_catt_table[];
extern const ATTACK_ATTR yun_catt_table[];
extern const ATTACK_BOX alex_att_box[];
extern const ATTACK_BOX dudley_att_box[];
extern const ATTACK_BOX ef13_att_box[];
extern const ATTACK_BOX elena_att_box[];
extern const ATTACK_BOX gill_att_box[];
extern const ATTACK_BOX hugo_att_box[];
extern const ATTACK_BOX ibuki_att_box[];
extern const ATTACK_BOX ken_att_box[];
extern const ATTACK_BOX necro_att_box[];
extern const ATTACK_BOX oro_att_box[];
extern const ATTACK_BOX ryu_att_box[];
extern const ATTACK_BOX sean_att_box[];
extern const ATTACK_BOX yang_att_box[];
extern const ATTACK_BOX yun_att_box[];
extern const BODY_BOX alex_body_box[];
extern const BODY_BOX dudley_body_box[];
extern const BODY_BOX ef13_body_box[];
extern const BODY_BOX elena_body_box[];
extern const BODY_BOX gill_body_box[];
extern const BODY_BOX hugo_body_box[];
extern const BODY_BOX ibuki_body_box[];
extern const BODY_BOX ken_body_box[];
extern const BODY_BOX necro_body_box[];
extern const BODY_BOX oro_body_box[];
extern const BODY_BOX ryu_body_box[];
extern const BODY_BOX sean_body_box[];
extern const BODY_BOX yang_body_box[];
extern const BODY_BOX yun_body_box[];
extern const CAUGHT_BOX alex_cau_box[];
extern const CAUGHT_BOX dudley_cau_box[];
extern const CAUGHT_BOX ef13_cau_box[];
extern const CAUGHT_BOX elena_cau_box[];
extern const CAUGHT_BOX gill_cau_box[];
extern const CAUGHT_BOX hugo_cau_box[];
extern const CAUGHT_BOX ibuki_cau_box[];
extern const CAUGHT_BOX ken_cau_box[];
extern const CAUGHT_BOX necro_cau_box[];
extern const CAUGHT_BOX oro_cau_box[];
extern const CAUGHT_BOX ryu_cau_box[];
extern const CAUGHT_BOX sean_cau_box[];
extern const CAUGHT_BOX yang_cau_box[];
extern const CAUGHT_BOX yun_cau_box[];
extern const CatchTable alex_rival_catch_tbl[];
extern const CatchTable dudley_rival_catch_tbl[];
extern const CatchTable elena_rival_catch_tbl[];
extern const CatchTable gill_rival_catch_tbl[];
extern const CatchTable hugo_rival_catch_tbl[];
extern const CatchTable ibuki_rival_catch_tbl[];
extern const CatchTable ken_rival_catch_tbl[];
extern const CatchTable necro_rival_catch_tbl[];
extern const CatchTable oro_rival_catch_tbl[];
extern const CatchTable ryu_rival_catch_tbl[];
extern const CatchTable sean_rival_catch_tbl[];
extern const CatchTable yang_rival_catch_tbl[];
extern const CatchTable yun_rival_catch_tbl[];
extern const HIT_IX alex_hit_ix_table[];
extern const HIT_IX dudley_hit_ix_table[];
extern const HIT_IX ef13_hit_ix_table[];
extern const HIT_IX elena_hit_ix_table[];
extern const HIT_IX gill_hit_ix_table[];
extern const HIT_IX hugo_hit_ix_table[];
extern const HIT_IX ibuki_hit_ix_table[];
extern const HIT_IX ken_hit_ix_table[];
extern const HIT_IX necro_hit_ix_table[];
extern const HIT_IX oro_hit_ix_table[];
extern const HIT_IX ryu_hit_ix_table[];
extern const HIT_IX sean_hit_ix_table[];
extern const HIT_IX yang_hit_ix_table[];
extern const HIT_IX yun_hit_ix_table[];
extern const HOSEI_BOX alex_hos_box[];
extern const HOSEI_BOX dudley_hos_box[];
extern const HOSEI_BOX ef13_hos_box[];
extern const HOSEI_BOX elena_hos_box[];
extern const HOSEI_BOX gill_hos_box[];
extern const HOSEI_BOX hugo_hos_box[];
extern const HOSEI_BOX ibuki_hos_box[];
extern const HOSEI_BOX ken_hos_box[];
extern const HOSEI_BOX necro_hos_box[];
extern const HOSEI_BOX oro_hos_box[];
extern const HOSEI_BOX ryu_hos_box[];
extern const HOSEI_BOX sean_hos_box[];
extern const HOSEI_BOX yang_hos_box[];
extern const HOSEI_BOX yun_hos_box[];
extern const OLC_IX alex_olc_ix_table[];
extern const OLC_IX dudley_olc_ix_table[];
extern const OLC_IX elena_olc_ix_table[];
extern const OLC_IX gill_olc_ix_table[];
extern const OLC_IX hugo_olc_ix_table[];
extern const OLC_IX ibuki_olc_ix_table[];
extern const OLC_IX ken_olc_ix_table[];
extern const OLC_IX necro_olc_ix_table[];
extern const OLC_IX oro_olc_ix_table[];
extern const OLC_IX ryu_olc_ix_table[];
extern const OLC_IX sean_olc_ix_table[];
extern const OLC_IX yang_olc_ix_table[];
extern const OLC_IX yun_olc_ix_table[];
extern const OVERLAP_PARTS alex_overlap_char_tbl[];
extern const OVERLAP_PARTS dudley_overlap_char_tbl[];
extern const OVERLAP_PARTS elena_overlap_char_tbl[];
extern const OVERLAP_PARTS gill_overlap_char_tbl[];
extern const OVERLAP_PARTS hugo_overlap_char_tbl[];
extern const OVERLAP_PARTS ibuki_overlap_char_tbl[];
extern const OVERLAP_PARTS ken_overlap_char_tbl[];
extern const OVERLAP_PARTS necro_overlap_char_tbl[];
extern const OVERLAP_PARTS oro_overlap_char_tbl[];
extern const OVERLAP_PARTS ryu_overlap_char_tbl[];
extern const OVERLAP_PARTS sean_overlap_char_tbl[];
extern const OVERLAP_PARTS yang_overlap_char_tbl[];
extern const OVERLAP_PARTS yun_overlap_char_tbl[];
extern const s16 alex_movexy_table[][6];
extern const s16 alex_stepxy_table[][2];
extern const s16 dudley_movexy_table[][6];
extern const s16 dudley_stepxy_table[][2];
extern const s16 ef13_movexy_table[][6];
extern const s16 ef13_stepxy_table[][2];
extern const s16 elena_movexy_table[][6];
extern const s16 elena_stepxy_table[][2];
extern const s16 gill_movexy_table[][6];
extern const s16 gill_stepxy_table[][2];
extern const s16 hugo_movexy_table[][6];
extern const s16 hugo_stepxy_table[][2];
extern const s16 ibuki_movexy_table[][6];
extern const s16 ibuki_stepxy_table[][2];
extern const s16 ken_movexy_table[][6];
extern const s16 ken_stepxy_table[][2];
extern const s16 necro_movexy_table[][6];
extern const s16 necro_stepxy_table[][2];
extern const s16 oro_movexy_table[][6];
extern const s16 oro_stepxy_table[][2];
extern const s16 ryu_movexy_table[][6];
extern const s16 ryu_stepxy_table[][2];
extern const s16 sean_movexy_table[][6];
extern const s16 sean_stepxy_table[][2];
extern const s16 yang_movexy_table[][6];
extern const s16 yang_stepxy_table[][2];
extern const s16 yun_movexy_table[][6];
extern const s16 yun_stepxy_table[][2];
extern const u32 alex_atca[];
extern const u32 alex_btca[];
extern const u32 alex_caca[];
extern const u32 alex_cbca[];
extern const u32 alex_cuca[];
extern const u32 alex_dmca[];
extern const u32 alex_exca[];
extern const u32 alex_nmca[];
extern const u32 alex_saca[];
extern const u32 alex_yuca[];
extern const u32 dudley_atca[];
extern const u32 dudley_btca[];
extern const u32 dudley_caca[];
extern const u32 dudley_cbca[];
extern const u32 dudley_cuca[];
extern const u32 dudley_dmca[];
extern const u32 dudley_exca[];
extern const u32 dudley_nmca[];
extern const u32 dudley_saca[];
extern const u32 dudley_yuca[];
extern const u32 ef13_char_table[];
extern const u32 elena_atca[];
extern const u32 elena_btca[];
extern const u32 elena_caca[];
extern const u32 elena_cbca[];
extern const u32 elena_cuca[];
extern const u32 elena_dmca[];
extern const u32 elena_exca[];
extern const u32 elena_nmca[];
extern const u32 elena_saca[];
extern const u32 elena_yuca[];
extern const u32 gill_atca[];
extern const u32 gill_btca[];
extern const u32 gill_caca[];
extern const u32 gill_cbca[];
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
extern const u32 ibuki_cbca[];
extern const u32 ibuki_cuca[];
extern const u32 ibuki_dmca[];
extern const u32 ibuki_exca[];
extern const u32 ibuki_nmca[];
extern const u32 ibuki_saca[];
extern const u32 ibuki_yuca[];
extern const u32 ken_atca[];
extern const u32 ken_btca[];
extern const u32 ken_caca[];
extern const u32 ken_cbca[];
extern const u32 ken_cuca[];
extern const u32 ken_dmca[];
extern const u32 ken_exca[];
extern const u32 ken_nmca[];
extern const u32 ken_saca[];
extern const u32 ken_yuca[];
extern const u32 necro_atca[];
extern const u32 necro_btca[];
extern const u32 necro_caca[];
extern const u32 necro_cbca[];
extern const u32 necro_cuca[];
extern const u32 necro_dmca[];
extern const u32 necro_exca[];
extern const u32 necro_nmca[];
extern const u32 necro_saca[];
extern const u32 necro_yuca[];
extern const u32 oro_atca[];
extern const u32 oro_btca[];
extern const u32 oro_caca[];
extern const u32 oro_cbca[];
extern const u32 oro_cuca[];
extern const u32 oro_dmca[];
extern const u32 oro_exca[];
extern const u32 oro_nmca[];
extern const u32 oro_saca[];
extern const u32 oro_yuca[];
extern const u32 ryu_atca[];
extern const u32 ryu_btca[];
extern const u32 ryu_caca[];
extern const u32 ryu_cbca[];
extern const u32 ryu_cuca[];
extern const u32 ryu_dmca[];
extern const u32 ryu_exca[];
extern const u32 ryu_nmca[];
extern const u32 ryu_saca[];
extern const u32 ryu_yuca[];
extern const u32 sean_atca[];
extern const u32 sean_btca[];
extern const u32 sean_caca[];
extern const u32 sean_cbca[];
extern const u32 sean_cuca[];
extern const u32 sean_dmca[];
extern const u32 sean_exca[];
extern const u32 sean_nmca[];
extern const u32 sean_saca[];
extern const u32 sean_yuca[];
extern const u32 yang_atca[];
extern const u32 yang_btca[];
extern const u32 yang_caca[];
extern const u32 yang_cbca[];
extern const u32 yang_cuca[];
extern const u32 yang_dmca[];
extern const u32 yang_exca[];
extern const u32 yang_nmca[];
extern const u32 yang_saca[];
extern const u32 yang_yuca[];
extern const u32 yun_atca[];
extern const u32 yun_btca[];
extern const u32 yun_caca[];
extern const u32 yun_cbca[];
extern const u32 yun_cuca[];
extern const u32 yun_dmca[];
extern const u32 yun_exca[];
extern const u32 yun_nmca[];
extern const u32 yun_saca[];
extern const u32 yun_yuca[];

const CHAR_INIT_ROM char_init_data[15] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {
        (u32 *)yun_nmca, (u32 *)yun_dmca,
        (u32 *)yun_btca, (u32 *)yun_caca,
        (u32 *)yun_cuca, (u32 *)yun_atca,
        (u32 *)yun_saca, (u32 *)yun_exca,
        (u32 *)yun_cbca, (u32 *)yun_yuca,
        (s16 *)yun_stepxy_table, (s16 *)yun_movexy_table,
        (OVERLAP_PARTS *)yun_overlap_char_tbl, (OLC_IX *)yun_olc_ix_table,
        (CatchTable *)yun_rival_catch_tbl, (HIT_IX *)yun_hit_ix_table,
        (BODY_BOX *)yun_body_box, (ATTACK_BOX *)yun_att_box,
        (CAUGHT_BOX *)yun_cau_box, (HOSEI_BOX *)yun_hos_box,
        (ATTACK_ATTR *)yun_catt_table, 1,
        16896, 8192,
        38, 2,
        0,
    },
    {
        (u32 *)dudley_nmca, (u32 *)dudley_dmca,
        (u32 *)dudley_btca, (u32 *)dudley_caca,
        (u32 *)dudley_cuca, (u32 *)dudley_atca,
        (u32 *)dudley_saca, (u32 *)dudley_exca,
        (u32 *)dudley_cbca, (u32 *)dudley_yuca,
        (s16 *)dudley_stepxy_table, (s16 *)dudley_movexy_table,
        (OVERLAP_PARTS *)dudley_overlap_char_tbl, (OLC_IX *)dudley_olc_ix_table,
        (CatchTable *)dudley_rival_catch_tbl, (HIT_IX *)dudley_hit_ix_table,
        (BODY_BOX *)dudley_body_box, (ATTACK_BOX *)dudley_att_box,
        (CAUGHT_BOX *)dudley_cau_box, (HOSEI_BOX *)dudley_hos_box,
        (ATTACK_ATTR *)dudley_catt_table, 1,
        16896, 8192,
        50, 2,
        0,
    },
    {
        (u32 *)alex_nmca, (u32 *)alex_dmca,
        (u32 *)alex_btca, (u32 *)alex_caca,
        (u32 *)alex_cuca, (u32 *)alex_atca,
        (u32 *)alex_saca, (u32 *)alex_exca,
        (u32 *)alex_cbca, (u32 *)alex_yuca,
        (s16 *)alex_stepxy_table, (s16 *)alex_movexy_table,
        (OVERLAP_PARTS *)alex_overlap_char_tbl, (OLC_IX *)alex_olc_ix_table,
        (CatchTable *)alex_rival_catch_tbl, (HIT_IX *)alex_hit_ix_table,
        (BODY_BOX *)alex_body_box, (ATTACK_BOX *)alex_att_box,
        (CAUGHT_BOX *)alex_cau_box, (HOSEI_BOX *)alex_hos_box,
        (ATTACK_ATTR *)alex_catt_table, 1,
        16896, 8192,
        52, 2,
        0,
    },
    {
        (u32 *)ibuki_nmca, (u32 *)ibuki_dmca,
        (u32 *)ibuki_btca, (u32 *)ibuki_caca,
        (u32 *)ibuki_cuca, (u32 *)ibuki_atca,
        (u32 *)ibuki_saca, (u32 *)ibuki_exca,
        (u32 *)ibuki_cbca, (u32 *)ibuki_yuca,
        (s16 *)ibuki_stepxy_table, (s16 *)ibuki_movexy_table,
        (OVERLAP_PARTS *)ibuki_overlap_char_tbl, (OLC_IX *)ibuki_olc_ix_table,
        (CatchTable *)ibuki_rival_catch_tbl, (HIT_IX *)ibuki_hit_ix_table,
        (BODY_BOX *)ibuki_body_box, (ATTACK_BOX *)ibuki_att_box,
        (CAUGHT_BOX *)ibuki_cau_box, (HOSEI_BOX *)ibuki_hos_box,
        (ATTACK_ATTR *)ibuki_catt_table, 1,
        16896, 8192,
        42, 2,
        0,
    },
    {
        (u32 *)ryu_nmca, (u32 *)ryu_dmca,
        (u32 *)ryu_btca, (u32 *)ryu_caca,
        (u32 *)ryu_cuca, (u32 *)ryu_atca,
        (u32 *)ryu_saca, (u32 *)ryu_exca,
        (u32 *)ryu_cbca, (u32 *)ryu_yuca,
        (s16 *)ryu_stepxy_table, (s16 *)ryu_movexy_table,
        (OVERLAP_PARTS *)ryu_overlap_char_tbl, (OLC_IX *)ryu_olc_ix_table,
        (CatchTable *)ryu_rival_catch_tbl, (HIT_IX *)ryu_hit_ix_table,
        (BODY_BOX *)ryu_body_box, (ATTACK_BOX *)ryu_att_box,
        (CAUGHT_BOX *)ryu_cau_box, (HOSEI_BOX *)ryu_hos_box,
        (ATTACK_ATTR *)ryu_catt_table, 1,
        16896, 8192,
        48, 2,
        0,
    },
    {
        (u32 *)gill_nmca, (u32 *)gill_dmca,
        (u32 *)gill_btca, (u32 *)gill_caca,
        (u32 *)gill_cuca, (u32 *)gill_atca,
        (u32 *)gill_saca, (u32 *)gill_exca,
        (u32 *)gill_cbca, (u32 *)gill_yuca,
        (s16 *)gill_stepxy_table, (s16 *)gill_movexy_table,
        (OVERLAP_PARTS *)gill_overlap_char_tbl, (OLC_IX *)gill_olc_ix_table,
        (CatchTable *)gill_rival_catch_tbl, (HIT_IX *)gill_hit_ix_table,
        (BODY_BOX *)gill_body_box, (ATTACK_BOX *)gill_att_box,
        (CAUGHT_BOX *)gill_cau_box, (HOSEI_BOX *)gill_hos_box,
        (ATTACK_ATTR *)gill_catt_table, 1,
        16896, 8192,
        54, 2,
        0,
    },
    {
        (u32 *)hugo_nmca, (u32 *)hugo_dmca,
        (u32 *)hugo_btca, (u32 *)hugo_caca,
        (u32 *)hugo_cuca, (u32 *)hugo_atca,
        (u32 *)hugo_saca, (u32 *)hugo_exca,
        (u32 *)alex_cbca, (u32 *)hugo_yuca,
        (s16 *)hugo_stepxy_table, (s16 *)hugo_movexy_table,
        (OVERLAP_PARTS *)hugo_overlap_char_tbl, (OLC_IX *)hugo_olc_ix_table,
        (CatchTable *)hugo_rival_catch_tbl, (HIT_IX *)hugo_hit_ix_table,
        (BODY_BOX *)hugo_body_box, (ATTACK_BOX *)hugo_att_box,
        (CAUGHT_BOX *)hugo_cau_box, (HOSEI_BOX *)hugo_hos_box,
        (ATTACK_ATTR *)hugo_catt_table, 1,
        16896, 8192,
        56, 2,
        0,
    },
    {
        (u32 *)oro_nmca, (u32 *)oro_dmca,
        (u32 *)oro_btca, (u32 *)oro_caca,
        (u32 *)oro_cuca, (u32 *)oro_atca,
        (u32 *)oro_saca, (u32 *)oro_exca,
        (u32 *)oro_cbca, (u32 *)oro_yuca,
        (s16 *)oro_stepxy_table, (s16 *)oro_movexy_table,
        (OVERLAP_PARTS *)oro_overlap_char_tbl, (OLC_IX *)oro_olc_ix_table,
        (CatchTable *)oro_rival_catch_tbl, (HIT_IX *)oro_hit_ix_table,
        (BODY_BOX *)oro_body_box, (ATTACK_BOX *)oro_att_box,
        (CAUGHT_BOX *)oro_cau_box, (HOSEI_BOX *)oro_hos_box,
        (ATTACK_ATTR *)oro_catt_table, 1,
        16896, 8192,
        40, 2,
        0,
    },
    {
        (u32 *)necro_nmca, (u32 *)necro_dmca,
        (u32 *)necro_btca, (u32 *)necro_caca,
        (u32 *)necro_cuca, (u32 *)necro_atca,
        (u32 *)necro_saca, (u32 *)necro_exca,
        (u32 *)necro_cbca, (u32 *)necro_yuca,
        (s16 *)necro_stepxy_table, (s16 *)necro_movexy_table,
        (OVERLAP_PARTS *)necro_overlap_char_tbl, (OLC_IX *)necro_olc_ix_table,
        (CatchTable *)necro_rival_catch_tbl, (HIT_IX *)necro_hit_ix_table,
        (BODY_BOX *)necro_body_box, (ATTACK_BOX *)necro_att_box,
        (CAUGHT_BOX *)necro_cau_box, (HOSEI_BOX *)necro_hos_box,
        (ATTACK_ATTR *)necro_catt_table, 1,
        16896, 8192,
        46, 2,
        0,
    },
    {
        (u32 *)elena_nmca, (u32 *)elena_dmca,
        (u32 *)elena_btca, (u32 *)elena_caca,
        (u32 *)elena_cuca, (u32 *)elena_atca,
        (u32 *)elena_saca, (u32 *)elena_exca,
        (u32 *)elena_cbca, (u32 *)elena_yuca,
        (s16 *)elena_stepxy_table, (s16 *)elena_movexy_table,
        (OVERLAP_PARTS *)elena_overlap_char_tbl, (OLC_IX *)elena_olc_ix_table,
        (CatchTable *)elena_rival_catch_tbl, (HIT_IX *)elena_hit_ix_table,
        (BODY_BOX *)elena_body_box, (ATTACK_BOX *)elena_att_box,
        (CAUGHT_BOX *)elena_cau_box, (HOSEI_BOX *)elena_hos_box,
        (ATTACK_ATTR *)elena_catt_table, 1,
        16896, 8192,
        44, 2,
        0,
    },
    {
        (u32 *)ef13_char_table, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        (s16 *)ef13_stepxy_table, (s16 *)ef13_movexy_table,
        0, 0,
        0, (HIT_IX *)ef13_hit_ix_table,
        (BODY_BOX *)ef13_body_box, (ATTACK_BOX *)ef13_att_box,
        (CAUGHT_BOX *)ef13_cau_box, (HOSEI_BOX *)ef13_hos_box,
        (ATTACK_ATTR *)ef13_catt_table, 1,
        16896, 8192,
        28, 2,
        0,
    },
    {
        (u32 *)yang_nmca, (u32 *)yang_dmca,
        (u32 *)yang_btca, (u32 *)yang_caca,
        (u32 *)yang_cuca, (u32 *)yang_atca,
        (u32 *)yang_saca, (u32 *)yang_exca,
        (u32 *)yang_cbca, (u32 *)yang_yuca,
        (s16 *)yang_stepxy_table, (s16 *)yang_movexy_table,
        (OVERLAP_PARTS *)yang_overlap_char_tbl, (OLC_IX *)yang_olc_ix_table,
        (CatchTable *)yang_rival_catch_tbl, (HIT_IX *)yang_hit_ix_table,
        (BODY_BOX *)yang_body_box, (ATTACK_BOX *)yang_att_box,
        (CAUGHT_BOX *)yang_cau_box, (HOSEI_BOX *)yang_hos_box,
        (ATTACK_ATTR *)yang_catt_table, 1,
        16896, 8192,
        38, 2,
        0,
    },
    {
        (u32 *)ken_nmca, (u32 *)ken_dmca,
        (u32 *)ken_btca, (u32 *)ken_caca,
        (u32 *)ken_cuca, (u32 *)ken_atca,
        (u32 *)ken_saca, (u32 *)ken_exca,
        (u32 *)ken_cbca, (u32 *)ken_yuca,
        (s16 *)ken_stepxy_table, (s16 *)ken_movexy_table,
        (OVERLAP_PARTS *)ken_overlap_char_tbl, (OLC_IX *)ken_olc_ix_table,
        (CatchTable *)ken_rival_catch_tbl, (HIT_IX *)ken_hit_ix_table,
        (BODY_BOX *)ken_body_box, (ATTACK_BOX *)ken_att_box,
        (CAUGHT_BOX *)ken_cau_box, (HOSEI_BOX *)ken_hos_box,
        (ATTACK_ATTR *)ken_catt_table, 1,
        16896, 8192,
        48, 2,
        0,
    },
    {
        (u32 *)sean_nmca, (u32 *)sean_dmca,
        (u32 *)sean_btca, (u32 *)sean_caca,
        (u32 *)sean_cuca, (u32 *)sean_atca,
        (u32 *)sean_saca, (u32 *)sean_exca,
        (u32 *)sean_cbca, (u32 *)sean_yuca,
        (s16 *)sean_stepxy_table, (s16 *)sean_movexy_table,
        (OVERLAP_PARTS *)sean_overlap_char_tbl, (OLC_IX *)sean_olc_ix_table,
        (CatchTable *)sean_rival_catch_tbl, (HIT_IX *)sean_hit_ix_table,
        (BODY_BOX *)sean_body_box, (ATTACK_BOX *)sean_att_box,
        (CAUGHT_BOX *)sean_cau_box, (HOSEI_BOX *)sean_hos_box,
        (ATTACK_ATTR *)sean_catt_table, 1,
        16896, 8192,
        48, 2,
        0,
    },
};

const s16 Dsas_dir_table[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
};

const s8 sel_sp_ch_tbl[10] = {
    0, 1, 0, 1, 1, 1, 1, 1, 0, 0,
};

const s16 rsix_r_table[9][2] = {
    { 31, 10 }, { 61, 11 }, { 91, 12 }, { 121, 13 }, { 151, 14 }, { 181, 19 }, { 211, 24 }, { 241, 29 },
    { 999, 39 },
};

const s16 attr_flame_tbl[79] = {
    42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    67, 67, 67, 67, 67, 67, 67, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 103, 103, 103, 103, 103, 103, 103, 103,
    103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103,
};

const s16 attr_thunder_tbl[79] = {
    43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    68, 68, 68, 68, 68, 68, 68, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 104, 104, 104, 104, 104, 104, 104, 104,
    104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104,
};

const s16 attr_freeze_tbl[79] = {
    44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    69, 69, 69, 69, 69, 69, 69, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 105, 105, 105, 105, 105, 105, 105, 105,
    105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105,
};

const s16 sky_nm_damage_tbl[79] = {
    88, 88, 88, 88, 88, 88, 88, 97, 98, 88, 103, 104, 105, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    88, 97, 98, 103, 104, 105, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 91, 109, 110,
};

const s16 sky_nm2_damage_tbl[79] = {
    88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    88, 88, 88, 88, 88, 88, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 88, 88, 88, 88, 88, 88, 88, 88,
    88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88,
};

const s16 sky_sp_damage_tbl[79] = {
    91, 91, 91, 95, 91, 91, 96, 97, 98, 91, 103, 104, 105, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    91, 97, 98, 103, 104, 105, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 97, 98, 90, 100, 101, 102, 103, 104, 105, 106, 107, 91, 109, 110,
};

const s16 kagami_damage_tbl[79] = {
    64, 64, 64, 64, 64, 64, 64, 65, 66, 64, 67, 68, 69, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    64, 65, 66, 67, 68, 69, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 65, 66, 90, 100, 101, 102, 103, 104, 105, 106, 107, 65, 109, 110,
};

const s16 kagami2_damage_tbl[79] = {
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 67, 68, 69, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    64, 64, 64, 67, 68, 69, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 67, 68, 69, 64, 64, 64, 64, 64,
};

const s16 grd_hand_damage_tbl[79] = {
    41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 43, 44, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    41, 41, 41, 42, 43, 44, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 41, 41, 41, 41, 41, 41, 41, 41,
    41, 41, 41, 41, 41, 41, 41, 42, 43, 44, 41, 41, 41, 41, 41,
};

const u8 hddm_damage_tbl[79] = {
    1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u8 trdm_damage_tbl[79] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u8 ttk_damage_req_tbl[79] = {
    0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
};

const u8 parisucc_pts[2][50] = {
    {
        0xA, 0xC, 0xE, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28,
        0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x44, 0x46, 0x48,
        0x4A, 0x4C, 0x4E, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5A, 0x5C, 0x5E, 0x60, 0x62, 0x64, 0x64, 0x64,
        0x64, 0x64,
    },
    {
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
        0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
        0x14, 0x14,
    },
};

const u8 dm_oiuchi_catch[31] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0x3C,
};
