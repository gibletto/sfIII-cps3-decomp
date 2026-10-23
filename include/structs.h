#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

typedef struct {
    s16 h;
    s16 l;
} LoHi16;

typedef union {
    s32 sp;
    LoHi16 real;
} Reg32SpReal;

typedef struct {
    s16 boix;           /* signed (set_jugde_area sign-extends them) */
    s16 atix;           /* 4 box kinds: body, attack, caught, hosei */
    s16 cuix;
    s16 hoix;
} HIT_IX;

typedef struct {
    s16 body_dm[5][4];  /* 40 bytes (set_jugde_area steps boix by 40) */
} BODY_BOX;

typedef struct {
    s16 hand_dm[2][4];
} HAND_BOX;

typedef struct {
    s16 cat_box[4];
} CATCH_BOX;

typedef struct {
    s16 cau_box[4];
} CAUGHT_BOX;

typedef struct {
    s16 att_box[3][4];  /* 24 bytes (set_jugde_area steps atix by 24) */
} ATTACK_BOX;

typedef struct {
    s16 hos_box[4];
} HOSEI_BOX;

typedef struct {
    u16 reaction;       /* a halfword */
    u8 mkh_ix;
    u8 dipsw;
    u8 at_free4;        /* provisional name */
    u8 dir;
    u16 guard;
    u8 pow;
    u8 impact;
    u8 piyo;
    s8 ng_type;         /* signed (debug_draw_att_data prints it sign-extended) */
    s8 hs_me;
    s8 hs_you;
    u8 hit_mark;
    u8 dmg_mark;
} ATTACK_ATTR;

typedef struct {
    s16 parts_hos_x;
    s16 parts_hos_y;
    u8 parts_colmd;
    u8 parts_colcd;
    u8 parts_prio;
    u8 parts_flip;
    u8 parts_timer;
    u8 parts_disp;
    s16 parts_mts;
    u16 parts_nix;
    u16 parts_char;
} OVERLAP_PARTS;

typedef struct {
    s16 olc_ix[4];
} OLC_IX;

typedef struct {
    s16 catch_hos_x;
    s16 catch_hos_y;
    u8 catch_prio;
    u8 catch_flip;
    s16 catch_nix;
} CatchTable;

typedef struct {
    u16 code;
    s16 koc;
    s16 ix;
    s16 pat;
} CHAR_CMD;

typedef struct {
    Reg32SpReal a[2];
    Reg32SpReal d[2];
    s16 kop[2];
    u16 index;
} MVXY;

typedef union {
    s32 cal;
    struct {
        s16 pos;
        s16 low;
    } disp;
} XY;

typedef struct {
    s16 total;
    s16 new_dm;
    s16 req_f;
    s16 old_r;
    s16 kind_of[10][4][2];
} ComboType;

typedef struct {
    s8 flag;
    s16 genkai;
    s16 time;
    union {
        s32 timer;
        LoHi16 quantity;
    } now;
    s32 recover;
    s16 store;
    s16 again;
} PiyoriType;

typedef struct {
    s16 code;           /* character code, added to the pattern's slot_addr */
    s16 col;            /* palette, added to disp_colcd */
    s16 x;
    s16 y;              /* the top nibble is the sprite size */
} CHAR_CELL;

typedef struct {
    u8 done_flip;  /* cg_flip the sprite list was built for */
    s8 done_rl;  /* rl_flag the sprite list was built for (last facing it was mirrored to) */
    s16 spr_free0;  /* provisional name */
    s16 cg_ofs_x;  /* pattern origin x: cg_data_list[cg_number].x */
    u16 cg_ofs_y;  /* pattern origin y, negated: -cg_data_list[cg_number].y */
    u16 sprite_flip;  /* flip the list is drawn with: done_rl ^ done_flip */
    u16 gfx_ofs;  /* sprite code of the list's block in sprite RAM */
    s16 gfx_cells;  /* sprites in the list; effect 13 carries its master's colour code here until its first frame */
    s16 gfx_blk10[4];  /* graphics blocks: [0] current, [1] and [2] still used by the last two frames */
    s16 gfx_blk40[4];  /* sprite-list blocks, rotated the same way */
    s16 gfx_blk_ex[4];  /* a third block list, only ever cleared */
    CHAR_CELL* cells;  /* the pattern's cell records */
    struct {
        s16 x;
        s16 y;
    } old_mr;  /* my_mr.size the list was last zoomed to; 63,63 after a rebuild */
    u16 slot_addr;  /* character code of the pattern's graphics */
    s16 disp_colcd;  /* palette the list is drawn with */
} CHAR_SPR_WORK;

typedef struct {
    u8 done_flip;
    u8 done_rl;
    u8 sprite_flip;
    u8 pad0;
    s16 floor;
    u16 gfx_ofs;
    s16 gfx_cells;
    s16 gfx_blk10[4];
    s16 gfx_blk40[4];
    s16 gfx_blk_ex[4];
    u16 cells[2];
    s16 old_mr[2];
    u16 slot_addr;
    s16 disp_colcd;
} SPR_LIST_HEAD;

typedef struct {
    s8 be_flag;
    s8 disp_flag;
    u8 blink_timing;
    u8 operator;
    u8 type;
    u8 charset_id;
    s16 work_id;
    s16 id;
    s8 rl_flag;
    s8 rl_waza;
    u32* target_adrs;
    u32* hit_adrs;
    u32* dmg_adrs;
    s16 before;
    s16 myself;
    s16 behind;
    s16 listix;
    s16 dead_f;
    s16 timing;
    s16 routine_no[8];
    s16 old_rno[8];
    s16 hit_stop;
    s16 hit_quake;
    s8 cgromtype;
    u8 kage_flag;
    s16 kage_hx;
    s16 kage_hy;
    s16 kage_prio;
    s16 kage_width;
    s16 kage_char;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    s16 next_x;
    s16 next_y;
    s16 next_z;
    s16 scr_mv_x;
    s16 scr_mv_y;
    XY xyz[3];
    s16 old_pos[3];
    s16 sync_suzi;
    u16* suzi_offset;
    MVXY mvxy;
    s16 direction;
    s16 dir_old;
    s16 dir_step;
    s16 dir_timer;
    s16 vitality;
    s16 vital_new;
    s16 vital_old;
    s16 dm_vital;
    s16 dmcal_m;
    s16 dmcal_d;
    s8 weight_level;
    u8 pad0[0x1];
    CHAR_CMD cmoa;
    CHAR_CMD cmsw;
    CHAR_CMD cmlp;
    CHAR_CMD cml2;
    CHAR_CMD cmja;
    CHAR_CMD cmj2;
    CHAR_CMD cmj3;
    CHAR_CMD cmj4;
    CHAR_CMD cmj5;
    CHAR_CMD cmj6;
    CHAR_CMD cmj7;
    CHAR_CMD cmms;
    CHAR_CMD cmmd;
    CHAR_CMD cmyd;
    CHAR_CMD cmcf;
    CHAR_CMD cmcr;
    CHAR_CMD cmbk;
    CHAR_CMD cmb2;
    CHAR_CMD cmb3;
    CHAR_CMD cmr0;      /* provisional name: one CHAR_CMD, unreferenced */
    s16 cmwk[16];
    s16 my_bright_type;
    u32* char_table[12];
    u32* se_random_table;
    s16* step_xy_table;
    s16* move_xy_table;
    OVERLAP_PARTS* overlap_char_tbl;
    OLC_IX* olc_ix_table;
    OLC_IX cg_olc;
    CatchTable* rival_catch_tbl;
    CatchTable* curr_rca;
    u32* set_char_ad;
    s16 cg_ix;
    s16 now_koc;
    s16 char_index;
    s16 current_colcd;
    s16 cgd_type;
    u8 pat_status;
    u8 kind_of_waza;
    u8 hit_range;
    u8 total_paring;
    u8 total_att_set;
    u8 sp_tech_id;
    u8 cg_ctr;
    u8 cg_type;
    u16 cg_se;
    u16 cg_olc_ix;
    u16 cg_number;
    s16 cg_att_ix;
    u16 cg_hit_ix;
    u8 cg_extdat;
    u8 cg_cancel;
    u8 cg_effect;
    u8 cg_eftype;
    u16 cg_zoom;
    u16 cg_rival;
    u16 cg_add_xy;
    u8 cg_next_ix;
    u8 cg_status;
    s16 cg_wca_ix;
    s16 cg_jphos;
    u8 cg_prio;
    u8 cg_flip;
    u16 old_cgnum;
    CHAR_SPR_WORK spr;
    s16 my_col_mode;
    s16 my_col_code;
    s16 my_priority;
    s16 my_family;
    s16 my_ext_pri;
    s16 my_mr_flag;
    s16 my_mts;
    s16 my_trans_mode;
        struct {
        struct {
            s16 x;
            s16 y;
        } size;
    } my_mr;
    s16 waku_work_index;    /* also the shell reflect flag (EFF13, HITEFEF) */
    s16 olc_work_ix[4];
    u8 pad1[0x2];
    HIT_IX* hit_ix_table;
    HIT_IX cg_ja;
    BODY_BOX* body_adrs;
    BODY_BOX* h_bod;
    ATTACK_BOX* attack_adrs;    /* the attack boxes also serve as catch boxes (catch_hit_check) */
    ATTACK_BOX* h_att;
    CAUGHT_BOX* caught_adrs;
    CAUGHT_BOX* h_cau;
    HOSEI_BOX* hosei_adrs;
    HOSEI_BOX* h_hos;
    ATTACK_ATTR* att_ix_table;
    ATTACK_ATTR att;
    u16 zu_flag;
    u16 at_attribute;
    u16 kezuri_pow;     /* unsigned (set_new_attnum shifts it with shlr) */
    u16 add_arts_point;
    u16 buttobi_type;
    u16 att_zuru;
    s16 dir_atthit;
    s16 vs_id;
    u8 att_hit_ok;
    u8 meoshi_hit_flag;
    u16 at_koa;
    u8 paring_attack_flag;
    s8 no_death_attack;
    s16 renew_attack;
    u16 attack_num;
    u16 uketa_att[4];
        union {
        struct {
            u8 player;
            u8 effect;
        } hit;
        u16 hit_flag;
    } hf;
    s16 hit_mark_x;
    s16 hit_mark_y;
    s16 hit_mark_z;
    s16 kohm;
    u8 dm_fushin;
    s8 dm_weight;
    u16 dm_butt_type;
    u16 dm_zuru;
    u16 dm_attribute;
    s16 dm_guard_success;
    s16 dm_plnum;
    s16 dm_attlv;
    s16 dm_dir;
    s8 dm_rl;
    u8 dm_impact;
    s16 dm_stop;
    s16 dm_quake;
    u16 dm_piyo;
    u16 dm_ten_ix;
    u16 dm_koa;
    s16 dm_work_id;
    u16 dm_arts_point;
    s16 dm_jump_att_flag;   /* a halfword (PLPDM Damage_12000 tests it as > 0) */
    s16 dm_count_up;
    s8 dm_nodeathattack;
    u8 dm_exdm_ix;
    u8 dm_dip;
    u8 dm_kind_of_waza;
    s16 attpow;
    s16 defpow;
    u32* my_effadrs;
    s16 shell_ix[8];
    s16 hm_dm_side;
    s16 extra_col;
    s16 extra_col_2;
    s16 original_vitality;
    u8 hit_work_id;
    u8 dmg_work_id;
    u8 kow;
    u8 wrd_free[45];    /* provisional name: 45 bytes after kow (sizeof(WORK) 0x32C) */
} WORK;

typedef struct {        /* 32 bytes (super_arts[2] at 0200D93C, stride 0x20) */
    s16 kind_of_arts;   /* comm_sajp, Check_SA_Active */
    s16 nmsa_g_ix;      /* one halfword, set_super_arts_status stores data[0] there with mov.w; signed: indexes
                           waza_flag without extu.w in look_after_timers */
    s8 gauge_type;      /* check_sa_type_rebirth */
    s8 ok;              /* check_sa_type_rebirth, comm_sajp, player_mv_0000, Check_Dramatic */
    s16 sa_rno;         /* player_mv_0000 */
    s16 gauge_len;      /* get_sa_gauge_len (super_arts[0] + 8) */
    u8 sa_free0[2];     /* provisional name: unreferenced */
    union {
        s32 i;
        LoHi16 s;
    } gauge;
    s32 dtm;
    s16 store_max;      /* spgauge_cont_main */
    s16 store;          /* spgauge_cont_main, sa_time_moji_send */
    s16 id_arts;        /* kotp_02000 */
    s16 saeff_ok;       /* one halfword; Player_attack, Player_caught, effect_41_move store it with mov.w */
    u8 sa_free1[4];     /* provisional name: unreferenced */
} SA_WORK;

typedef struct {
    u16 sw_lvbt;
    u16 sw_new;
    u16 sw_old;
    u16 sw_now;
    u16 sw_off;
    u16 sw_chg;
    u16 old_now;
    s16 lgp;
    u8 ca14;
    u8 ca25;
    u8 ca36;
    u8 calf;
    u8 calr;
    u8 lever_dir;
    s16 waza_flag[48];
    s16 reset[48];
    u8 waza_r[48][4];
    u16 btix[48];
    u16 exdt[48][4];
} WORK_CP;

typedef struct {
    s16 r_no;
    s16 char_ix;
    s16 data_ix;
} AS;

typedef struct {
    WORK wu;
    WORK_CP* cp;
    u32 spmv_ng_flag;
    s16 player_number;
    s16 zuru_timer;
    u16 zuru_ix_counter;
    u8 zuru_flag;
    s8 tsukamarenai_flag;
    u8 kizetsu_kow;
    u8 micchaku_flag;
    u8 hos_fi_flag;
    u8 hos_em_flag;
    s16 tsukami_num;
    s8 tsukami_f;
    s8 tsukamare_f;
    s8 kind_of_catch;
    u8 old_gdflag;
    u8 guard_flag;
    u8 guard_chuu;
    s16 dm_ix;
    s16 hosei_amari;
    s8 dm_hos_flag;
    u8 dm_point;
    s8 scr_pos_set_flag;
    s8 hoshi_flag;
    s8 the_same_players;
    u8 pad0[0x1];
    s8* dm_step_tbl;
    s8 running_f;
    s8 cancel_timer;
    s8 jpdir;
    s8 jptim;
    s16 current_attack;
    u8 pad1[0x2];
    const AS* as;
    SA_WORK* sa;
    ComboType* cb;
    PiyoriType* py;
    s8 wkey_flag;
    s8 dead_flag;
    s16 ukemi_ok_timer;
    s16 backup_ok_timer;
    s8 uot_cd_ok_flag;
    s8 ukemi_success;
    s16 old_pos_data[8];
    s16 move_distance;
    s16 move_power;
    u8 saishin_lvdir;
    u8 sa_stop_lvdir;
    u8 exdm_ix;         /* dm_status_copy reads 0x38E */
    u8 pl_free0;        /* provisional name: unreferenced */
    u8 sa_stop_flag;
    u8 atemi_flag;
    u8 atemi_point;
    u8 kezurijini_flag;
    WORK* illusion_work;
    s16 image_setup_flag;
    s16 image_data_index;
    s16 dm_vital_backup;
    u8 caution_flag;
    u8 permited_koa;    /* a byte */
    ComboType* rp;
    s16 bullet_hcnt;
    s16 bhcnt_timer;
    u8 pt_free[48];     /* provisional name: 0x3A8-0x3D7, never referenced */
} PLW;

typedef struct {
    WORK wu;
    u32* my_master;
    s16 master_work_id;
    s16 master_id;
    s16 master_player;
    s16 master_priority;
    u8 dm_refrect;
    u8 refrected;
    s16 free;
    u32 master_ng_flag;
    u32 master_ng_flag2;
    u8 et_free[30];
} WORK_Other;

typedef struct {
    s8 be_flag;
    s8 disp_flag;
    s16 fam_no;
    s16 r_no_0;
    s16 r_no_1;
    s16 r_no_2;
    s16 position_x;
    s16 position_y;
    s32 speed_x;
    s32 speed_y;
    XY xy[2];
    XY wxy[2];
    u16* bg_address;
    u16* suzi_adrs;
    s16 old_pos_x;
    s32 zuubun;
    s16 no_suzi_line;
    u16* start_suzi;
    s16 u_line;
    s16 d_line;
    s16 bg_adrs_c_no;
    s16 suzi_c_no;
    s16 pos_x_work;
    s16 pos_y_work;
    s8 rewrite_flag;
    s8 suzi_base_flag;
    XY hos_xy[2];
    XY chase_xy[2];
    s16 free;
    s16 frame_deff;
    s16 r_limit;
    s16 r_limit2;
    s16 l_limit;
    s16 l_limit2;
    s16 y_limit;
    s16 y_limit2;
    s16 frame_deff2;
    s16* deff_rl0;
    s16* deff_plus0;
    s16* deff_rl1;
    s16* deff_plus1;
    s16* deff_minus0;
    s16* deff_minus1;
    s16 abs_x;
    s16 abs_y;
} BGW;

typedef struct {
    s8 bg_routine;
    s8 bg_r_1;
    s8 bg_r_2;
    s8 dmm0[1];         /* cleared with frame_flag */
    s8 stage;
    s8 area;
    s8 compel_flag;     /* random 0-3 layout variant */
    s8 compel_on;       /* forced-position mode on */
    s32 scroll_cg_adr;
    s32 ake_cg_adr;
    s16 scno;
    s16 bg2_sp_x;
    s16 bg2_sp_y;
    s16 r_limit;        /* the debug BG viewer (CMD_MAIN) fills these six from a table */
    s16 r_limit2;
    s16 l_limit;
    s16 l_limit2;
    s16 y_limit;
    s16 y_limit2;
    s16 scr_stop;
    s8 frame_flag;
    s8 chase_flag;
    s8 old_chase_flag;
    s8 old_frame_flag;
    s16 pos_offset;
    s16 quake_x_index;
    s16 quake_y_index;
    s16 bg_f_x;
    s16 bg_f_y;
    s16 old_bg_f_x;     /* bg_f_x of the previous frame */
    s16 old_bg_f_y;     /* bg_f_y of the previous frame */
    u8 pad1[0xa];
    s16 bg2_sp_x2;
    s16 bg2_sp_y2;
    s16 frame_deff;
    s16 center_x;
    s16 center_y;
    s16 bg_index;
    s8 dmm1;            /* set to 1 on scene set */
    s8 frame_vol;
    s16 max_x;
    u8 bg_opaque;
    u8 pad2[0x3];
    BGW bgw[7];
} BG;

typedef struct {
    s16 hx;
    s16 hy;
    s16 whx;
    s8 ixod;
    s8 rl;
    s16 rno;
    s16 char_index;
} APPEAR_DATA;

typedef struct {
    s16 timer;
    s16 jmplv;
    s16 kosuu;
    s16 bbdat[4][4];
} BBBSTable;

typedef struct {
    u16 sw_new;
    u16 sw_old;
    u16 sw_chg;
    u16 sw_now;
    u16 old_now;
    u16 now_lvbt;
    u16 old_lvbt;
    u16 new_lvbt;
    u16 sw_lever;
    u16 shot_up;
    u16 shot_down;
    u16 shot_ud;
    s16 lvr_status;
    s16 jaku_cnt;
    s16 chuu_cnt;
    s16 kyou_cnt;
    s16 up_cnt;
    s16 down_cnt;
    s16 left_cnt;
    s16 right_cnt;
    s16 s1_cnt;
    s16 s2_cnt;
    s16 s3_cnt;
    s16 s4_cnt;
    s16 s5_cnt;
    s16 s6_cnt;
    s16 lu_cnt;
    s16 ld_cnt;
    s16 ru_cnt;
    s16 rd_cnt;
    s16 waza_num;
    s16 waza_no;
    s16 wait_cnt;
    s16 cmd_r_no;
} T_PL_LVR;

typedef struct {
    union {
        s32 cal;
        struct {
            s16 pos;
            u16 low;
        } disp;
    } iw[2];
} Ideal_W;

/* per-line scroll work: step added per line and the running offset */
typedef struct {
    s32 step;
    s32 ofs;
} SUZI_CALC;

typedef union {
    s32 pl;
    LoHi16 ps;
} S32Split;

typedef struct {
    s32 timer;
    s32 timer2;
    S32Split x;
    S32Split y;
    s32 spx;
    s32 dlx;
    s32 spy;
    s32 dly;
    s32 amx;
    s32 amy;
    s8 swx;
    s8 swy;
} MotionState;

typedef union {
    s32 psi;
    LoHi16 pss;
} MS;

typedef union {
    s32 psy;
    LoHi16 psys;
} PS_UNI;

typedef union {
    s32 patl;
    LoHi16 pats;
} SST;

typedef union {
    s32 l;
    LoHi16 w;
} ST;

typedef struct {
    s16 x_pos_num;
    s8 routine_num;
    u8 hit;
    s8 kind;
    u32 pts;
    s8 pts_flag;
    s16 move[2];
    s16 x_posnum[2];
    s16 timer[2];
} CMST_WIN;

typedef struct {
    s16 w_type;
    s16 w_int;
    s16 free1;
    s16 w_lvr;
    s16* w_ptr;
    s16 free2;
    s16 w_dead;
    s16 w_dead2;
    union {
        struct {
            s16 flag;
            s16 shot_flag;
            s16 shot_flag2;
        } tame;
        struct {
            s16 s_cnt;
            s16 m_cnt;
            s16 l_cnt;
        } shot;
    } uni0;
    s16 free3;
    s16 shot_ok;
} WAZA_WORK;

typedef const s16* const_s16_arr;

/* provisional name */
typedef struct {
    s8 xxxx[8][2][32]; /* follow-up menu choice, by CP_No[1], CP_No[2] and a random draw */
} FOLLOW_MENU_1ST;

/* provisional name */
typedef struct {
    s8 zzzz[4][4]; /* pattern index, by menu choice and area */
} FOLLOW_MENU_2ND;

typedef s32 (*Term_Tbl_t)(PLW* wk, WORK* em);

/* 12 bytes; the second ranking keeps its key in score as well */
typedef struct {
    u8 name[3];
    u8 mark;            /* a letter shown after the initials */
    u16 player;
    u8 flag;            /* purpose not known */
    u8 player_color;
    u32 score;
} RANK_DATA;

typedef void (*Eff93_Jmp_Tbl_t)(WORK_Other* ewk);

typedef struct {
    s16 dir_timer;
    s16 chix;
    s16 vital;
    s16 color;
    s16 prio_hi;
    s16 prio_low;
} BS2;

typedef struct {
    s16 r_no_0;
    s16 r_no_1;
    s16 r_no_2;
    s16 type;
    s16 end_flag;
    s16 timer;
} END_W;

typedef struct {
    s16 pos_x;
    s16 pos_y;
    s16 pos_z;
    u16 cg_num;
    s16 renew;
    u16 hit_ix;
    s8 flip;
    u8 cg_flp;
    s16 kowaza;
} ZanzouTableEntry;

typedef struct {
    s16 nx;
    s16 ny;
    s16 col;
    u16 chr;
} CONN;

typedef struct {
    WORK wu;
    u32* my_master;
    s16 master_work_id;
    s16 master_id;
    s16 master_player;
    s16 master_priority;
    s16 prio_reverse;
    u8 conn_free[0x76];
    s16 num_of_conn;
    CONN conn[108];
} WORK_Other_CONN;

typedef struct {
    s16 pos_x;
    s16 pos_y;
} ImageBuff;

typedef struct {
    s16 rno;
    s16 cix;
    s16 hx;
    s16 hy;
    s16 hzr;
    s16 hzd;
    u8 pri_use;
    u8 bomb;
    s16 ispix;
    u8 bau;
    u8 kage_char;
    u8 doa;
    u8 init_dsp;
    s16 tmt;
    s16 gr1st;
} DADD;

typedef struct {
    s16 kosuu;
    s16 bomb;
    const DADD* dadd;
} HAHEN;

typedef union {
    s32 cal;
    LoHi16 pos;
} Reg32CalPos;

typedef struct {
    s16 body_dm[4][4];
} RAMBOD;

typedef struct {
    s16 hand_dm[4][4];
} RAMHAN;

typedef struct {
    s16 data[4];
} K5Data;

typedef struct {
    u16 index;
    u16 rno;
    Reg32SpReal a[4];
    Reg32SpReal d[4];
    Reg32CalPos r[4];
} MVJ;

typedef struct {
    s16 vs_cpu_result[16];
    s16 vs_cpu_grade[16];
    s16 vs_cpu_player[16];
    s16 vcr_ix;
    s16 grade;
    s16 all_clear;
    s16 keizoku;
    s16 sp_point;
    s16 fr_ix;
    u8 fr_sort_data[16][4];
} GradeFinalData;

typedef struct {
    u16 x;
    u16 y;
    u16 attr;
    const s8* str;
} TM_STRING;

typedef struct {
    s16 offence_total;
    s16 defence_total;
    s16 tech_pts_total;
    s16 ex_point_total;
    s16 em_stun;
    s16 max_combo;
    s16 clean_hits;
    s16 att_renew;
    s16 guard_succ;
    s16 vitality;
    s16 nml_blocking;
    s16 rpd_blocking;
    s16 grd_blocking;
    s16 def_free;
    s16 first_attack;
    s16 leap_attack;
    s16 target_combo;
    s16 nml_nage;
    s16 grap_def;
    s16 quick_stand;
    s16 personal_act;
    s16 reversal;
    s16 comwaza;
    s16 sa_exec;
    s16 tairyokusa;
    s16 kimarite;
    s16 renshou;
    s16 em_renshou;
    s16 app_nml_block;
    s16 app_rpd_block;
    s16 app_grd_block;
    s16 onaji_waza;
    s16 grd_miss;
    s16 grd_mcnt;
    s16 grade;
    s16 round;
    s16 win_round;
    s16 no_lose;
} GradeData;

typedef struct {
    s16 offence_total;
    s16 defence_total;
    s16 tech_pts_total;
    s16 ex_point_total;
    s16 grade;
} JudgeGals;

typedef struct {
    s16 offence_total;
    s16 defence_total;
    s16 tech_pts_total;
    s16 ex_point_total;
    s16 round;
    s16 grade;
} JudgeCom;

typedef struct {
    union {
        u16 results;
        struct {
            s8 att_result;
            s8 cat_result;
        } ca;
    } flag;
    u8 my_att;
    u8 dm_body;
    u16 my_hit;
    u16 dm_me;
    s16* ah;
    s16* dh;
} HS;

typedef struct {
    s16 data[32];
} POWER;

typedef struct {
    s16 step[10][4];        /* cal_combo_waribiki reads 10 rows */
} KOATT;

typedef union {
    s32 ixl;
    LoHi16 ixs;
} TBL;

typedef struct {
    s8 code[4];
} RANK_NAME_W;

typedef struct {
    s16 data[4][6];
} PARABORA_DATA;

typedef struct {
    AS as;
    s16 dmm;
} AS_ROW;

typedef struct {
    void (*fn[3])();
} OBJ_JMP_TBL;

typedef struct {
    u8 Shot[8];
    u8 Vibration;
    u8 free[3];
} _PAD_INFOR;

typedef struct {
    s8 contents[4][8];
} _EXTRA_OPTION;

struct _SAVE_W {
    _PAD_INFOR Pad_Infor[2];
    u8 Difficulty;
    s8 Time_Limit;
    u8 Battle_Number[2];
    u8 Damage_Level;
    u8 Handicap;
    u8 Partner_Type[2];
    s8 Adjust_X;
    s8 Adjust_Y;
    u8 Screen_Size;
    u8 Screen_Mode;
    u8 GuardCheck;
    u8 Auto_Save;
    u8 AnalogStick;
    u8 BgmType;
    u8 SoundMode;
    u8 BGM_Level;
    u8 SE_Level;
    u8 Extra_Option;
    u8 PL_Color[2][20];
    _EXTRA_OPTION extra_option;
    RANK_DATA Ranking[20];
    u32 sum;
};

typedef union {
    s32 dy;
    LoHi16 ry;
} PS_DY;

typedef union {
    s32 dp;
    LoHi16 rp;
} PS_DP;

typedef struct {
    u32* nmca;
    u32* dmca;
    u32* btca;
    u32* caca;
    u32* cuca;
    u32* atca;
    u32* saca;
    u32* exca;
    u32* cbca;
    u32* yuca;
    s16* stxy;
    s16* mvxy;
    OVERLAP_PARTS* ovct;
    OLC_IX* ovix;
    CatchTable* rict;
    HIT_IX* hiit;
    BODY_BOX* boda;
    ATTACK_BOX* atta;
    CAUGHT_BOX* caua;
    HOSEI_BOX* hosa;
    ATTACK_ATTR* atit;
    PARABORA_DATA* prot;
} CharInitData;

typedef struct {
    u32* nmca;
    u32* dmca;
    u32* btca;
    u32* caca;
    u32* cuca;
    u32* atca;
    u32* saca;
    u32* exca;
    u32* cbca;
    u32* yuca;
    s16* stxy;
    s16* mvxy;
    OVERLAP_PARTS* ovct;
    OLC_IX* ovix;
    CatchTable* rict;
    HIT_IX* hiit;
    BODY_BOX* boda;
    ATTACK_BOX* atta;
    CAUGHT_BOX* caua;
    HOSEI_BOX* hosa;
    ATTACK_ATTR* atit;
    s8 cgromtype;
    s16 my_cm;
    s16 my_cc;
    s16 my_pr;
    s16 my_fm;
    s16 my_ep;
} CHAR_INIT_ROM;

typedef struct {
    WORK wu;
    WORK* my_master;
    s16 master_work_id;
    s16 master_id;
    s16 master_player;
    s16 master_priority;
    s8 look_up_flag;    /* show the looked-up box set instead of the master's */
    s8 curr_ja;         /* box selected in the editor, drawn highlighted */
    u16 ja_disp_bit;    /* one bit per box to draw; 0x4000 the push box, 0x8000 the origin and floor marks */
    s16 ja[42][2];      /* screen corners, 4 per box (10 boxes: body 5, attack 3, caught, hosei), then the origin [40] and floor [41] marks */
    s16 jx[10][4];      /* box rectangles from the master's hit tables: x, w, y, h */
    union {
        s32 l;
        s16 w;
    } fade_cja;         /* highlight cycle of the selected box: .l += 0x2000 each frame, .w is the phase 0-3 */
} WORK_Other_JUDGE;

typedef struct {
    u16 se;
    u8 hits;
    u8 deff;
    u8 kezu;
    u8 fsin;
    u8 status;
    u8 quake;
    u8 dir;
    u8 col;
    u8 myhix;
    u8 emhix;
} HMDT;

typedef struct {
    u16 chix;
    s16 hx;
    s16 hy;
} EXPLEM;

typedef struct {
    s8 be;
    u8 c_mode;
    u16 total;
    u16* handle;
    s32 ixNum1st;
    u8* srcAdrs;
    u32 srcSize;
} Palette;

typedef union {
    u32 b32;
    u16 b16[2];
    u8 b8[4];
} TextureHandle;

typedef struct {
    s8 be;
    u8 flags;
    s16 arCnt;
    s16 arInit;
    u16 total;
    TextureHandle* handle;
    s32 ixNum1st;
    u16 textures;
    u16 accnum;
    u32* offset;
    u8* srcAdrs;
    size_t srcSize;
} Texture;

typedef struct {
    Texture* tex;
    Palette* pal;
} PPGDataList;

typedef struct {
    s32 x16;
    s32 x32;
    u16 x16_free[1024];
    u16 x32_free[640];
} TexturePoolFree;

typedef struct {
    s32 x16;
    s32 x32;
    u16 x16_used[1024];
    u16 x32_used[640];
} TexturePoolUsed;

typedef struct {
    u16 x16_map[4][16];
    u8 x32_map[10][8];
} PatternMap;

typedef union {
    u32 code;
    struct {
        u16 group;
        u16 offset;
    } parts;
} PatternCode;

typedef struct {
    s16 time;
    s16 state;
    PatternCode cs;
} PatternState;

typedef struct {
    s16 curr_disp;
    s16 time;
    PatternCode cg;
    s16 x16;
    s16 x32;
    PatternMap map;
} PatternInstance;

typedef struct {
    s16 kazu;
    PatternInstance* adr[64];
    PatternInstance patt[64];
} PatternCollection;

typedef struct {
    s32 mltnum16;
    s32 mltnum32;
    s32 mltnum;
    s32 mltgidx16;
    s32 mltgidx32;
    s32 mltcshtime16;
    s32 mltcshtime32;
    PatternState* mltcsh16;
    PatternState* mltcsh32;
    u8* mltbuf;
    Texture tex;
    PPGDataList texList;
    u32 attribute;
    PatternCollection* cpat;
    TexturePoolFree* tpf;
    TexturePoolUsed* tpu;
    u8 id;
    u8 ext;
    s16 mode;
} MultiTexture;

typedef struct {
    s16 hx;
    s16 hy;
    s16 hz;
    s8 sel_pri;
    s8 sel_rl;
    s16 color;
    s8 sel_col;
    s8 dspf;
    s8 ichi;
    s8 mts;
    s16 chix;
} PLEF;

typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFF08_FRAME;

typedef struct {
    u32 a;
    u32 b;
} GRID_CELL;

typedef struct {
    u32 adrs;
    u32 pad0;
    u32 dst;
    u32 row;
    s8* script_top;
    s8* script;
    u32 pattern_top;
    s8* pattern;
    s8 timer;
    u8 pad1;
    s16 col;
    s8 scr;
    s8 cols;
    s8 rows;
    u8 pad2;
} E14_WORK;

typedef struct {
    u32 pad0;
    u32 pad1;
    u32 adrs;
    u32 pad2;
} E14_SCR;

typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFF23_FRAME;

typedef struct {
    u32 a;
    u32 b;
} EFF23_CELL_REQ;

typedef struct {
    u8 order;
    u8 kind_req;
    u8 kind_cnt;
    u8 request;
    u8 contents;
    u8 timer;
    s16 pos_x;
    s16 pos_y;
    s16 pos_z;
} MessageData;

typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFF45_FRAME;

typedef struct {
    u32 a;
    u32 b;
} EFF45_CELL_REQ;

typedef const s16* ConstShortArray;

typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFF74_FRAME;

typedef struct {
    const EFF74_FRAME* frames;
    const s16* char_ix;
    s16 count;
} EFF74_ANIM;

typedef struct {
    u32 a;
    u32 b;
} CELL_REQ;

typedef struct {
    const CONN* conn;
    const u16* chr;
} EFFA6_MESSAGE;

typedef struct {
    s16 d[6];
} B6_SRC;

typedef struct {
    WORK wu;
    WORK* my_master;
    s16 pad0[4];
    s16 num;
    B6_SRC src[32];
    s16 pos[32][3];
} WORK_B6;

typedef struct {
    const CONN* conn;
    const u16* chr;
} EFFB8_MESSAGE;

typedef struct {
    u16 pos_x;          /* scroll x, 10 bits */
    u16 pos_y;          /* scroll y, 10 bits */
    u16 attr;           /* layer attribute: attr << 6 | bits */
    u16 ctrl;           /* 0x8000 layer on, 0x4000/0x2000 extra switches, 0x0C00 mode, low 10 bits line table offset */
    u16 map_adrs;       /* tile map page (low 7 bits) | line table page (bits 8-14) */
} SCROLL_CTRL;

typedef struct {
    s16 flag;
    s16 timer;
    const s16* changetbl_1p;
    const s16* changetbl_2p;
} ColorTableIndex;

typedef struct {
    s16 handle;         /* SIMM RAM block holding the layer map */
    s16 pad0;
    u32 adrs;           /* address of that block */
    s16 pos_x;          /* display position x */
    s16 pos_y;          /* display position y */
    XY xy[2];           /* scroll position x, y (16.16) */
} AKE_SCRL;

typedef struct {
    s16 dir;
    s16 limit_x_pos;
    s16 limit_y_pos;
    s16 zoom_v;
    s32 sp_x_a;
    s32 sp_x_d;
    s32 sp_y_a;
    s32 sp_y_d;
} EFFF6_ETC;

typedef struct {
    s16 hx;
    s16 hy;
    s16 hz;
    s16 chix;
} GillEffData;

typedef struct {
    u16 flag;
    s16 sour;
    s16 tm;
} I3_Data;

typedef struct {
    s16 timer;
    s16 endcode;
    const s16* adrs;
} ColorCode;

typedef union {
    u32 swi;
    struct {
        u16 h;
        u16 l;
    } sws;
    struct {
        u8 hh;
        u8 h;
        u8 l;
        u8 ll;
    } swc;
} MVSW;

typedef struct {
    u32 prep;
    s32 size;
    u32 src;
} END_BG_GFX;


typedef struct {
    s16 current;
    s16 target;
    s16 step;
    s16 mode;
} SNDRAMP;

typedef struct {
    s8 note_ceiling;
    u8 pan;
    s8 volume_bias;
    u8 reserved_03;
    u16 sample_index;
    s8 pitch_bias;
    s8 attack_curve;
    s8 decay_curve;
    u8 velocity_scale;
    s8 release_curve;
    s8 forced_release_curve;
} SNDPATCH;

typedef struct {
    u32 start;
    u32 loop;
    u32 end;
    s32 base_pitch;
} SNDSAMPLE;

typedef struct {
    void (*jmp[3])();
} GAME_TASK_JMP;

typedef struct {
    s8  type;           /* 0 letter slot this entry draws */
    s8  n_disp_flag;    /* 1 blink phase 0-2, 2 = letter hidden */
    s16 c_cnt;          /* 2 slot number matched against the cursor */
    s16 r_no_0;         /* 4 */
    s16 r_no_1;         /* 6 */
    s16 f_cnt;          /* 8 frames in the current blink phase */
} SC_NAME_WK;

typedef struct {
    s16 my_wkid;
    u16 koa;
    u8 kind_of_tama;
    u8 kage_index;
    u8 chix;
    u8 ernm;
    u8 erht;
    u8 erdf;
    u8 erex;
    u8 col_1p;
    u8 col_2p;
    u8 data00;
    u8 data01;
    u8 disp_type;
    s16 def_power;
    s16 life_time;
    s16 hos_x;
    s16 hos_y;   /* 26 bytes */
} TAMA;

typedef struct {
    void (*fn[3])();
} JMP_TBL3;

typedef struct {
    s8 r_no_0;          /* routine number of this BG layer's task */
    s8 r_no_1;          /* sub routine number */
    s8 dir;             /* scroll direction */
    s8 ctr;             /* step counter */
    s16 bg_no;          /* BG layer this task drives */
} OPBW;

typedef struct {
    s16 pos;
    s16 size;
    s16 mask;
    u16 zoom;
} SCROLL_WINDOW;

/* screen window rectangle: left, top, right, bottom */
typedef struct {
    s16 l;
    s16 t;
    s16 r;
    s16 b;
} SCREEN_WINDOW;

typedef struct {
    u16 slot;
    u16 size;
    u16 count;
    u16 cells;
} CharGfxSetHead;

typedef struct {
    u16 addr;
    s16 handle;
} CharGfxSlot;

typedef struct {
    s32 ofs;
    s32 cell;
} HUD_CELL;


typedef struct {
    s16 pos_x;
    s16 pos_y;
    s16 priority;
    s16 cg_number;
    s8 v8;
    s8 v9;
    s16 used;
    s16 cg_ctr;
    s16 dbg_val[2];
    s16 col_mode;
    s16 col_code;
    s16 olc_ix;
    s8 rl_flag;
    s8 cg_flip;
} SNAPSHOT;

typedef struct {
    const u16* slot;
    const u16* src;
} PAL_BYTE_LIST;

typedef struct {
    const CONN* conn;
    const u16* chr;
} EFFF9_MESSAGE;

typedef struct {
    s16 wait;
    s16 x;
    s16 y;
    s16 attr;
    const u8* str;
} STAFF_LINE;

typedef struct {
    volatile u16 reserved_00;
    volatile u16 sample_control;
    volatile u16 sample_start_low;
    volatile u16 sample_start_high;
    volatile u16 reserved_08;
    volatile u16 sample_loop_enable;
    volatile u16 pitch;
    volatile u16 sample_loop_low;
    volatile u16 reserved_10;
    volatile u16 sample_loop_high;
    volatile u16 sample_end_low_a;
    volatile u16 sample_end_high_a;
    volatile u16 sample_end_low_b;
    volatile u16 sample_end_high_b;
    volatile u16 volume_left;
    volatile u16 volume_right;
} SNDREGS;

typedef struct {
    s16 x_pos_num;
    s8 routine_num;
    u8 hit;
    s8 kind;
    u32 pts;
    s8 pts_flag;
    s16 move[2];
    s16 x_posnum[2];
    s16 timer[2];
} CMST_WIN_R;

typedef struct {
    s8 mode;
    s8 level;
    s8 set2;
    s8 set3;
    s8 set4;
    s8 set5;
    s8 set6;
    s8 bonus;
    s8 check[8];
} SETTINGS;

typedef struct {
    s32 ofs;
    s32 cell;
} PANEL;

typedef struct {
    s16 pad0;
    s16 pad1;
    s16 char_ix;
    s16 pad2;
    s16 prio_front;
    s16 prio_back;
} C2ROW;

typedef union {
    u32* cpl;
    u16* cps;
    u8* cpc;
} GOTCP;


typedef struct {
    void (*f[2])();
} SETTING_TBL_T;

typedef struct {
    u16 code;
    u16 attr;
} TEXT_CELL;

typedef union {
    u32 l;
    struct {
        u16 hi;
        u16 lo;
    } w;
    s8 b[4];
    struct {
        u32 volume : 8;
        u32 mode : 7;
        u32 stereo : 1;
        u32 lo : 16;
    } bit;
} SOUND_CTRL;

typedef struct SPRITE_ENTRY {
    u16 w0;
    u16 w2;
    u16 w4;
    u16 w6;
    u16 w8;
    u16 w10;
    struct SPRITE_ENTRY* next;
    u16 prio;
    s8 flag;
    u8 layer;
} SPRITE_ENTRY;

typedef struct {
    SPRITE_ENTRY rec[8];
    u32 pad0;
    s16 count;
    s16 slot;
} SPRITE_LIST;

typedef struct {
    u32 w0;
    u32 w1;
    u32 w2;
} POLY_LINE;

struct _TASK {
    void (*func_adrs)();
    void (*callback_adrs)();
    u8 r_no[4];
    u16 condition;
    s16 timer;
    u8 free[4];
};

typedef struct {
    u8* adr;
    s16 w;
    s16 pad0;
} ByteMapSrc;

typedef struct {
    u8* adr;
    u8 pad0;
    u8 limit;
    s16 pad1;
} BitmapSrc;

typedef union {
    s32 l;
    struct {
        s16 x;
        s16 y;
    } s;
} XY16;

typedef struct {
    union {
        u16 code;
        u8 frames;
    } u;
    s16 type;
    s16 param;
    s16 box;
} PATTERN_REC;

typedef struct {
    s16 x;
    s16 y;
    s16 rest[5];
} JUDGE_COLUMN;

typedef struct {
    s16 attr;
    s32 ofs;
    s32 cell;
} TILEREQ;

typedef struct {
    u32 src;
    u32 dst;
    u32 size;
} XFER;

typedef struct {
    u32 src;
    u32 size;
} XFER2;

typedef struct {
    u16 x;
    u16 y;
    u16 attr;
    u16 code;
} CELL_ENTRY;

typedef struct {
    union {
        s32 full;
        struct {
            s16 h;
            s16 l;
        } half;
    } size;
    s32 step;
} ROUND_TIMER;

typedef struct {
    s16 v0;
    s16 v2;
    s16 hoji_counter;
} COUNT_WORK;

typedef struct {
    const u16* pos;
    const u16* code;
    const u16* attr;
} CELL_SET;

typedef struct {
    u16 v[3];
} CMB_FRAME;

typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFFJ5_FRAME;

typedef struct {
    s16 no;
    u32 adrs;
} BG_ADRS;

typedef struct {
    u16 code;
    u16 attr;
} SCR_CELL;

typedef struct {
    XY set_x;
    XY cur_x;
    XY set_y;
    XY cur_y;
} SCRLPOS;

typedef struct {
    u8 state;
    s8 count;
    s8 per_credit;
    s8 credits;
    s8 timer;
    s8 lockout;
    s8 dropped;
    u8 pad;
} COINCHUTE;

typedef struct {
    s16 x;
    s16 y;
    s16 sx;
    s16 sy;
    s16 size;
    s16 attr;
    s16 pad[2];
} CHAR_SPRITE;

typedef struct {
    s16 w[8];
} GFX_CELL;

typedef union {
    u32 swi;
    struct {
        u16 h;
        u16 l;
    } sws;
    u8 swc[4];
} MVSW_BE;

typedef struct {
    u16 x;
    u16 y;
    u16 attr;
    u16 pad;
    u8* str;
} TMLINE;

typedef struct {
    u8 data[111];
    u8 flags;
    u8 pad[4];
} VOICE;

typedef struct {
    s16 x;
    s16 w[7];
} SPR16;

typedef struct {
    u16 a_lo;
    u16 a_hi;
    u16 b_lo;
    u16 b_hi;
    u16 c_lo;
    u16 c_hi;
    u16 attr;
    u16 pri;
} POLYCMD;

typedef struct {
    s16 w0;
    s16 w2;
    s16 w4;
    s16 code;
    s16 pos;
    s16 attr;
    u8 pad[4];
} SPRENTRY;

typedef struct {
    u16 code;
    const char* name;
} MoveName;

typedef struct {
    u32 src;
    u16 size;
    u16 dst;
} CharGfxChunk;

typedef struct {
    s16 code;
    s16 pal;
    s16 x;
    s16 y;
    s16 zoom;
    s16 attr;
    s16 pad[2];
} CharSpriteK;

typedef union {
    s32 l;
    struct {
        s16 x;
        s16 y;
    } s;
} XY16K;

typedef struct {
    u8 frames;
    u8 kind;
    u8 pad2[4];
    s16 param;
    u32 bits;
    u32 pad12;
} HITA_PAT;

typedef struct {
    s16 body;
    s16 w2;
    s16 hand;
    union {
        u16 both;
        u8 kind[2];
    } k;
    s16 w8;
    s16 w10;
    s16 attack;
    s16 w14;
} HITA_IX;

typedef union {
    u32 key;
    u8 ix[4];
} HITA_KEY;

typedef struct {
    s16 w[16];
} HITA_BOX;

typedef struct {
    u8 held_up;
    u8 held_down;
    u8 up;
    u8 down;
    const char* name;
} HIT_KIND;

typedef struct {
    s16 x;
    s16 y;
} GRID_POS;

typedef struct {
    s16 x;
    s16 y;
    GRID_POS hit[1];
} GRID_ROW;

typedef struct {
    u8 frames;
    u8 pad1[7];
    u32 bits;
    u32 pad12;
} GRID_REC;

typedef struct {
    s16 x;
    s16 y;
    s16 pad0[8];
} GRID9_ROW;

typedef struct {
    u16 w0;
    u16 pad2;
    u16 w4;
    u8 kind6;
    u8 kind7;
    u16 pad8[2];
    u16 w12;
    u16 pad14;
} GRID9_REC;

typedef struct {
    s16 x;
    s16 w;
    s16 y;
    s16 h;
} HITBOX;

typedef struct {
    u32 prep;
    s32 size;
    u32 src;
    u32 mode;
} BG_GFX;

typedef struct {
    s16 slot[9];
} EDIT_SLOTS;

typedef struct {
    void (*f[7])();
} ROUTINES7;

typedef struct {
    void (*f[7])();
} SEL_EXIT_TBL;

typedef struct {
    void (*f[2])();
} BG_JMP2;

typedef struct {
    u16 cell;
    u16 w;
    u16 h;
    s16 x;
    s16 y;
    s16 x2;
    s16 y2;
} NAME_PLATE;

typedef struct {
    u32 adrs;
    u32 cur;
    s16 v8;
    s16 v10;
    s16 v12;
    s16 v14;
    s16 v16;
    s16 kind;
    s16 v20;
    s16 v22;
    s16 v24;
    s8 on;
    s16 step;
} FADE_LAYER;

typedef struct {
    s16 dead_f;
    s16 routine_no1;
    s16 my_family;
    s16 my_col_code;
    s16 pos_x;
    s16 pos_y;
    s16 priority;
    s16 char_index;
    s16 hit_stop;
    s16 sync_suzi;
    s16 old_rno[3];
    s16 rl_flag;
    s16 mvxy[8];
} EFF64_DATA;

typedef struct {
    u32 a;
    u32 b;
} J5_ENTRY;

typedef struct {
    s32 size;
    u32* wr;
    u32* rd;
    s32 count;
    u32* base;
} FIFO32;

typedef struct {
    u16 x;
    u16 y;
    u16 attr;
    u16 pad;
    const s8* str;
};

typedef struct {
    u16 n;
    u16 chr;
    u16 pos;
} TONE_ENTRY;

typedef struct {
    const u16* stntbl_ptr;
    const u16* stnptbl_ptr;
    s16 cstn;
    s16 ostn;
    s16 stncol_number;
    s8 sflag;
    s8 osflag;
    s8 g_or_s;
    s8 stimer;
    s16 slen;
    s16 dotlen;
    s8 proccess_dead;
} STN_DAT;

typedef struct {
    u32 fifo[5];
} TASK_QUEUE;

typedef struct {
    void (*func)();     /* 00 routine to start as a task */
    u32 arg;            /* 04 argument handed to the task */
} TASK_REQ;

typedef struct {
    const u16* cell;
    const u16* xpos;
    const u16* attr;
    s16 cyerw;
    s16 cred;
    s16 ored;
    s16 unused;
    s16 colnum;
} VITAL_BAR;

typedef struct {
    AS as;
    s16 pad;
} AS_ROW8;

typedef struct {
    const u16* spgtbl_ptr;
    const u16* spgptbl_ptr;
    s16 current_spg;
    s16 old_spg;
    s16 spgcol_number;
    s16 spg_level;
    s16 spg_maxlevel;
    s16 spg_len;
    s16 spg_dotlen;
    s16 flag;
    s16 flag2;
    s16 timer;          /* lettering / flash duration */
    s16 timer2;         /* frames between gauge blink phases */
    s8 kind;
    s8 max;
    s8 max_old;
    s8 max_rno;
    s8 time;
    s8 time_rno;
} SPG_DAT;

typedef struct {
    s8 status;
    u8 state;
    s16 priority;
    void* parent;
    void (*entry)();
    void (*func)();
    u32* sp;
    u32* stack_top;
    u32 sr;
    u32 pad0[3];
    void* creator;
    u32 arg;
    u32 wait;
    u32 timer;
    u32 pad1[2];
} TCB;

/* provisional name: the registers the exception handlers save for the crash screen */
typedef struct {
    u32 r0;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    u32 r5;
    u32 r6;
    u32 r7;
    u32 r8;
    u32 r9;
    u32 r10;
    u32 r11;
    u32 r12;
    u32 r13;
    u32 r14;
    u32 sp;
    u32 sr;
    u32 gbr;
    u32 vbr;
    u32 mach;
    u32 macl;
    u32 pr;
    u32 pc;
} EXC_REGS;

typedef struct {
    s8  type;           /* 00 entry type, cleared when entry starts */
    s8  form;           /* 01 unused */
    s8  end_flag[4];    /* 02 letter in this slot is fixed */
    s8  dmm;            /* 06 name has been drawn on the text layer */
    s16 id;             /* 08 player 0/1 */
    s16 r_no_0;         /* 0A entry routine (Name_Jmp_scs); 6 = closing, 7 = done */
    s16 r_no_1;         /* 0C */
    s16 rank_in;        /* 0E place reached in the best ranking */
    s16 rank_status;    /* 10 status of that ranking (n_input sets 0 or 6) */
    s16 rank;           /* 12 place reached, -1 = not ranked */
    s16 rank_sub;       /* 14 place in the second ranking, -1 = not ranked */
    s16 status;         /* 16 copy of rank_status */
    s16 status_sub;     /* 18 status of the second ranking (with rank_sub) */
    s16 index;          /* 1A cursor slot 0-3 */
    s16 timer;          /* 1C entry time left (1200, +420 per letter) */
    s16 code[4];        /* 1E letter codes 0-43; 44 space, 45 back, 46 end, 47 blank */
    s16 old_code[4];    /* 26 letter codes of the previous frame */
    s16 count1[2];      /* 2E lever hold time: [0] back, [1] forward */
    s8  count2[2];      /* 32 lever auto-repeat count */
    s16 wait_cnt;       /* 34 wait after a letter is fixed */
} NAME_WK;

typedef struct {
    s8 r_no_0;          /* main routine number of the opening / ending */
    s8 r_no_1;          /* scene number, advanced as the music reaches each bar */
    s16 r_no_2;         /* step within the current scene */
    s16 index;          /* timeline index: effects run while their start..end range contains it */
    s16 mv_ctr;         /* frame counter for the current move */
    s16 free_work;      /* general timer (the wait before the title) */
    OPBW bgw[3];        /* per-BG-layer tasks, BG0..BG2 */
} OP_W;

typedef struct {
    s8 msg_state;
    s8 card_state;
    u8 pad0;
    s8 cleared;
    u8 pad1;
    s8 msg_timer;
    s8 blink;
    s8 flag;
    s16 wins;
    s16 vs_wins;
} SELPL;

typedef struct {
    u16 x;
    u16 y;
    u16 attr;
    u16 pad;
    const s8* str;
};

typedef struct {
    s16 kind;
    s16 pad;
    void* data;
} TMSCRIPT;

typedef struct {
    u8* cursor;
    u8* origin;
    SNDPATCH* patch;
    SNDSAMPLE* sample;
    s32 decoded_pitch;
    s32 target_pitch;
    s32 current_pitch;
    s32 pitch_lfo;
    s32 volume_lfo;
    s32 note_ticks;
    s32 event_ticks;
    u8* loop_cursor[4];
    u16 pitch_lfo_depth;
    u16 volume_lfo_depth;
    u16 lfo_rate;
    u16 envelope_level;
    u16 saved_portamento_step;
    u16 portamento_step;
    u16 program_index;
    u16 attack_peak;
    u16 attack_rate;
    u16 sustain_level;
    u16 decay_rate;
    u16 release_rate;
    u16 forced_release_rate;
    s16 transpose;
    s16 volume_offset;
    u8 loop_count[4];
    u8 status;
    s8 coarse_pitch_bend;
    s8 fine_pitch_control;
    u8 instrument_bank;
    u8 volume;
    u8 velocity;
    u8 expression;
    u8 loop_latch;
    u8 key_on_pending;
    u8 duration_enabled;
    u8 note_event_pending;
    u8 tie;
    u8 restart_pending;
    u8 envelope_phase;
    u8 pan_override;
    u8 lfo_phase_flags;
    u8 priority_flags;
    u8 reserved_6f;
} SNDVOICE;

typedef struct {
    void* ptr0;
    void* ptr1;
    void* ptr2;
    void* ptr3;
} SPRPTR;

typedef struct {
    PATTERN_REC rec[99];
    void* judge;
    s16 hit_ix[99][4];  /* HIT_IX is 4 halfwords, read signed by the pattern preview */
    u8* body_adrs;      /* the 4 box kinds of WORK (body, attack, caught, hosei) */
    u8* h_bod;
    u8* attack_adrs;
    u8* h_att;
    u8* caught_adrs;
    u8* h_cau;
    u8* hosei_adrs;
    u8* h_hos;
} PATTERN_BUF;

typedef struct {
    u16 reg[6];
    u16 pan;
    u16 reg7[7];
    u16 level_l;
    u16 level_r;
} SNDVOICEREG;

typedef struct {
    u16 slot;
    u16 size;
    u16 count;
    u16 cells;
    u32 prep;
    CharGfxChunk chunk[1];
} CharGfxSet;

typedef struct {
    s16 cge_free0;      /* provisional name: copied to spr.spr_free0 */
    s16 x;
    s16 y;
    s16 cge_free;       /* provisional name */
    CharGfxSet* set;
} CharGfxEntry;

typedef struct {
    u8 device_type;
    u8 data[37];
} SCSI_INQUIRY;

typedef struct {
    u32 last_block;
    u32 block_len;
} SCSI_CAPACITY;

typedef struct {
    u16 set;
    u16 cur;
} SCRN_MODE;

/* provisional names */
typedef struct {
    s16 sel[3];
    s16 rest;
    s16 sel0_max;
    s16 sel1_max;
    s16 rec_count;
    s16 frames;
    s16 row;
} DBG_SLOT;

/* One step of a colour-step table: how many frames to hold, then the colour. A timer of 0 ends the table. */
typedef struct {
    s16 timer;
    s16 color;
} ColorStep;

/* records of the tables in data/ that a module reads */

/* end_main.c */
typedef struct { s32 ofs; s32 cell; } OP_TILE;
typedef struct { OP_TILE tile[8]; } OP_TILES;
typedef struct { s16 bg; s16 x; s16 y; u8 time; u8 pad; } OP_SCRN;
typedef struct { s16 time; s16 prio; } OP_PRIO;

/* EFF30.c */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 index;
} EFF30_DATA;

/* EFF48.c */
typedef struct {
    s16 slot;
    s16 y;
    u8 timer;
} EFF48_FRAME;
typedef struct {
    s32 ofs;
    s32 page;
} EFF48_TILE;
typedef struct { EFF48_TILE t[12]; } EFF48_ROW;

/* EFFA6.c */
typedef struct { s16 x; } SCROLL_TARGET;

/* EFFH0.c */
typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 disp_flag;
    s16 direction;
    s16 char_index;
} EFFH0_DATA;

/* EFF11.c */
typedef struct {
    s16 count;
    s16 frames;
} EFF11_ANIME;
typedef struct {
    s16 page;
    s16 y;
    u8 timer;
} EFF11_FRAME;
typedef struct {
    s32 ofs;
    s32 page;
} EFF11_TILE;
typedef struct {
    EFF11_TILE t[16];
} EFF11_ROW;

/* eff12.c */
typedef struct {
    s16 page;
    s16 y;
    u8 timer;
} EFF12_FRAME;
typedef struct {
    s32 ofs;
    s32 page;
} EFF12_TILE;
typedef struct {
    EFF12_TILE t[16];
} EFF12_ROW;

/* efff8_code.c */
typedef struct {
    u8 free;
    s8 disp;
    s16 index;
} EFFF8_TYPE;

/* pow_pow.c: one attack of a damage table (provisional name) */
typedef struct {
    s16 power;
    s8 rate_col;
    u8 pad;
} DAMAGE_DATA;

/* bg_work.c: a BG layer's deformation tables, as the deff_* pointers of its BGW (provisional name) */
typedef struct {
    const s16* rl0;
    const s16* plus0;
    const s16* rl1;
    const s16* plus1;
    const s16* minus0;
    const s16* minus1;
} BG_DEFF_TBL;

#endif
