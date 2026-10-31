/*
 * PLPDM.C  Player damage process
 *
 * Runs a player who has been hit or is guarding. Player_damage dispatches Damage_00000 to
 * Damage_29000 by damage routine: standing and crouching hit and guard staggers, air hits and
 * air guard, knock-downs, blow-aways (buttobi), bounces, crumples and KO.
 * Helpers run the first flight and landing (first_flight_union, buttobi_chakuchi_cg_type_check), slide
 * with dm_step_tbl and dust (setup_smoke_type), and set screen-edge correction (set_dm_hos_flag_*).
 * subtract_dm_vital applies the damage to vitality, awarding score and super gauge and handling
 * KO; get_damage_reaction_data and get_catch_off_data look up dm_reaction_table.
 * check_bullet_damage handles projectile hits. Called from the player main routine (PLMAIN).
 * The ground guard staggers test the attacker kind inline, and the recovery-roll window is always
 * 6 frames.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "SLOWF.h"
#include "PLS02.h"
#include "PLSGAUGE.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "cmb_cont.h"
#include "EFFA7.h"
#include "effa8.h"
#include "effa9.h"
#include "EFFD9.h"
#include "EFFG6.h"
#include "EFFE2.h"
#include "PLPCA.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "PLPDM.h"
#include "fighter.h"

/* routine_no[3], Damage_00000 */
#define D00_END         1       /* run the animation to its end */
#define D00_HOLD        2       /* nothing more: the move holds here */

/* routine_no[3], Damage_01000 */
#define D01_MOVE        1       /* move and run the animation to cue 1 */
#define D01_MOVE2       2       /* move and run the animation to cue 1 */
#define D01_AIR         3       /* in the air until it lands */
#define D01_LAND        4       /* the landing */

/* routine_no[3], Damage_04000 */
#define D04_SLIDE       1       /* slide back, raising dust */
#define D04_SLIDE2      2       /* slide back */

/* routine_no[3], Damage_07000 */
#define D07_RUN         1       /* run the animation */
#define D07_AIR         2       /* in the air */
#define D07_LANDED      3       /* landed: set the slide to stop over 3/4 of the pause */
#define D07_SLIDE       4       /* slide until the pause runs out */
#define D07_END         5       /* run the rest of the animation */

/* routine_no[3], Damage_08000 */
#define D08_RUN         1       /* run the animation */
#define D08_AIR         2       /* in the air */
#define D08_LAND        3       /* the landing */

/* routine_no[3], Damage_12000 */
#define D12_SLIDE       1       /* slide back, raising dust */
#define D12_SLIDE2      2       /* slide back */

/* routine_no[3], Damage_14000 */
#define D14_NEXT        1       /* start the next animation */
#define D14_FLIGHT      2       /* the first flight */
#define D14_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_16000 */
#define D16_NEXT        1       /* start the next animation */
#define D16_FLIGHT      2       /* the first flight */
#define D16_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_17000 */
#define D17_NEXT        1       /* start the next animation */
#define D17_AIR         2       /* in the air */
#define D17_LAND        3       /* the landing */

/* routine_no[3], Damage_18000 */
#define D18_NEXT        1       /* start the next animation */
#define D18_AIR         2       /* in the air */
#define D18_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_19000 */
#define D19_NEXT        1       /* start the next animation */
#define D19_AIR         2       /* in the air */
#define D19_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_20000 */
#define D20_NEXT        1       /* start the next animation */
#define D20_AIR         2       /* in the air */
#define D20_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_21000 */
#define D21_NEXT        1       /* start the next animation */
#define D21_FLIGHT      2       /* the first flight */
#define D21_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_23000 */
#define D23_NEXT        1       /* start the next animation */
#define D23_AIR         2       /* in the air */
#define D23_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_24000 */
#define D24_SLIDE       1       /* slide back */
#define D24_SLIDE2      2       /* slide back */

/* routine_no[3], Damage_25000 */
#define D25_RUN         1       /* run the animation */

/* routine_no[3], Damage_26000 */
#define D26_NEXT        1       /* start the next animation */
#define D26_AIR         2       /* in the air */
#define D26_LANDED      3       /* land from the blow */

/* routine_no[3], Damage_27000 */
#define D27_NEXT        1       /* start the next animation */

/* routine_no[3], Damage_28000 */
#define D28_AIR         1       /* in the air */
#define D28_LANDED      2       /* land from the blow */

/* routine_no[3], Damage_29000 */
#define D29_NEXT        1       /* start the next animation */

extern const s16 hissatsu_dageki_00[];
extern const s16 hissatsu_dageki_01[];
extern const s16 hissatsu_dageki_02[];
extern const s16 super_arts_nage_00[];
extern const s16 super_arts_nage_01[];
extern const s16 super_arts_nage_02[];
extern const s16 tsuujyou_dageki_00[];
extern const s16 tsuujyou_dageki_01[];
extern const s16 tsuujyou_dageki_02[];
extern const s16 tsuujyou_nage_00[];
extern const s16 tsuujyou_nage_01[];
extern const s16 tsuujyou_nage_02[];
extern const s16 hissatsu_nage_00[];
extern const s16 hissatsu_nage_01[];
extern const s16 hissatsu_nage_02[];
extern const s16 super_arts_dageki_00[];
extern const s16 super_arts_dageki_01[];
extern const s16 super_arts_dageki_02[];

/*
 * Stun time lists by attack kind: normal, special-move and super art strikes and throws. Each
 * is indexed by strength ((kind_of_waza & 7) / 2, the last two sharing a list), then at random.
 */
const s16* kizetsu_timer_table_0[4] = {
    tsuujyou_dageki_00, tsuujyou_dageki_01, tsuujyou_dageki_02, tsuujyou_dageki_02,
};
const s16* kizetsu_timer_table_1[4] = {
    hissatsu_dageki_00, hissatsu_dageki_01, hissatsu_dageki_02, hissatsu_dageki_02,
};
const s16* kizetsu_timer_table_2[4] = {
    tsuujyou_nage_00, tsuujyou_nage_01, tsuujyou_nage_02, tsuujyou_nage_02,
};
const s16* kizetsu_timer_table_3[4] = {
    hissatsu_nage_00, hissatsu_nage_01, hissatsu_nage_02, hissatsu_nage_02,
};
const s16* kizetsu_timer_table_4[4] = {
    super_arts_dageki_00, super_arts_dageki_01, super_arts_dageki_02, super_arts_dageki_02,
};
const s16* kizetsu_timer_table_5[4] = {
    super_arts_nage_00, super_arts_nage_01, super_arts_nage_02, super_arts_nage_02,
};

/* The stun time list by attack kind (kind_of_waza / 8). */
/* 02000B94 */
const s16** kizetsu_timer_table[8] = {
    kizetsu_timer_table_0,
    kizetsu_timer_table_1,
    kizetsu_timer_table_2,
    kizetsu_timer_table_3,
    kizetsu_timer_table_4,
    kizetsu_timer_table_5,
    kizetsu_timer_table_0,
    kizetsu_timer_table_0,
};


static void damage_atemi_setup(PLW* wk, PLW* ek);

#pragma inline(check_dmpat_to_dmpat)



void Player_damage(PLW* wk) {
    wk->wu.next_z = wk->wu.my_priority;
    wk->running_f = 0;
    wk->guard_flag = 3;
    wk->guard_chuu = 0;
    wk->tsukami_f = 0;
    wk->tsukamare_f = 0;
    wk->scr_pos_set_flag = 1;
    wk->dm_hos_flag = 0;
    wk->sa_stop_flag = 0;
    wk->caution_flag = 0;
    wk->sa->saeff_ok = 0;
    wk->cancel_timer = 0;
    if (wk->wu.routine_no[3] == RN3_START) {
        get_damage_reaction_data(wk);
        wk->ukemi_ok_timer = 6;
        wk->uot_cd_ok_flag = 0;
        wk->ukemi_success = 0;
        check_bullet_damage(wk);
    }
    if (wk->atemi_flag == 9) {
        wk->atemi_flag = 0;
    } else {
        plpdm_lv_00[wk->wu.routine_no[2]](wk);
    }
    set_hit_stop_hit_quake(&wk->wu);
}



void Damage_00000(PLW* wk) {
    wk->wu.next_z = 30;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        set_char_move_init(&wk->wu, 1, wk->as->char_ix);
        break;
    case D00_END:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 0xFF) {
            wk->wu.routine_no[3]++;
        }
        /* fall through */
    case D00_HOLD:
        break;
    }
}



void Damage_01000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3] = D01_MOVE;
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        reset_mvxy_data(&wk->wu);
        set_char_move_init(&wk->wu, 1, wk->as->char_ix);
        break;
    case D01_MOVE:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            add_mvxy_speed(&wk->wu);
            cal_mvxy_speed(&wk->wu);
        }
        break;
    case D01_MOVE2:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[3] = D01_AIR;
            wk->wu.cg_type = 0;
            add_mvxy_speed(&wk->wu);
        }
        break;
    case D01_AIR:
        jumping_union_process(&wk->wu, 4);
        break;
    case D01_LAND:
        char_move(&wk->wu);
        break;
    }
    if (wk->wu.cg_type == 0xFF || wk->wu.cg_type == 64) {
        wk->guard_flag = 0;
    }
}



void Damage_04000(PLW* wk) {
    wk->guard_flag = 0;
    wk->guard_chuu = guard_kind[wk->wu.routine_no[2] - 4];
    if (wk->wu.dm_work_id & 1) {
        wk->dm_hos_flag = 1;
    }
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        if ((wk->wu.dm_quake /= 2) < 4) {
            wk->wu.dm_quake = 4;
        }
        set_char_move_init(&wk->wu, 1, wk->as->char_ix);
        wk->dm_step_tbl = dm_step_data[select_grd_dsd[wk->wu.dm_impact][get_weight_point(&wk->wu)]];
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D04_SLIDE:
        wk->wu.routine_no[3]++;
        setup_smoke_type(wk);
        wk->wu.cmwk[14] = guard_pause_table[0][wk->wu.dm_attlv];
        char_move_wca(&wk->wu);
        add_dm_step_tbl(wk);
        break;
    case D04_SLIDE2:
        add_dm_step_tbl(wk);
        if (--wk->wu.cmwk[14] <= 0) {
            wk->wu.routine_no[3]++;
            char_move_wca(&wk->wu);
            break;
        }
        /* fall through */
    default:
        char_move(&wk->wu);
        break;
    }
}



void Damage_07000(PLW* wk) {
    wk->guard_flag = 0;
    wk->guard_chuu = guard_kind[wk->wu.routine_no[2] - 4];
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        if ((wk->wu.dm_quake /= 2) < 4) {
            wk->wu.dm_quake = 4;
        }
        set_char_move_init(&wk->wu, 1, wk->as->char_ix);
        wk->wu.cmwk[14] = guard_pause_table[1][wk->wu.dm_attlv];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data(&wk->wu);
        } else {
            setup_butt_own_data_ex2(&wk->wu, 1);
        }
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D07_RUN:
        wk->wu.routine_no[3]++;
        char_move_wca(&wk->wu);
        break;
    case D07_AIR:
        jumping_union_process(&wk->wu, 3);
        set_dm_hos_flag_sky(wk);
        wk->wu.cmwk[14]--;
        if (wk->wu.routine_no[3] != D07_LANDED) {
            if (wk->wu.cmwk[14] <= 0) {
                wk->wu.routine_no[1] = PLAYER_NORMAL;
                wk->wu.routine_no[2] = 38;
                wk->wu.routine_no[3] = D07_RUN;
                wk->wu.cg_type = 0;
                wk->wu.cg_next_ix = 0;
                char_move_wca(&wk->wu);
            }
        } else if (wk->wu.cmwk[14] <= 0) {
            wk->wu.cmwk[14] = 1;
        }
        break;
    case D07_LANDED:
        wk->wu.routine_no[3]++;
        wk->wu.dead_f = wk->wu.cmwk[14] * 3 / 4;
        if (wk->wu.dead_f <= 0) {
            wk->wu.dead_f = 1;
        }
        wk->wu.mvxy.d[0].sp = wk->wu.mvxy.a[0].sp / wk->wu.dead_f;
        wk->wu.mvxy.d[0].sp = -wk->wu.mvxy.d[0].sp;
        wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
        wk->wu.dead_f = 0;
        /* fall through */
    case D07_SLIDE:
        cal_mvxy_speed(&wk->wu);
        add_mvxy_speed(&wk->wu);
        set_dm_hos_flag_sky(wk);
        wk->wu.cmwk[14]--;
        if (wk->wu.cmwk[14] <= 0) {
            wk->wu.routine_no[3]++;
            char_move_wca(&wk->wu);
            break;
        }
        /* fall through */
    case D07_END:
        char_move(&wk->wu);
        break;
    }
    if (wk->wu.cg_type == 0xFF || wk->wu.cg_type == 64) {
        wk->guard_flag = 0;
    }
}



void Damage_08000(PLW* wk) {
    wk->guard_flag = 1;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        set_char_move_init(&wk->wu, 1, wk->as->char_ix);
        setup_mvxy_data(&wk->wu, wk->as->data_ix);
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D08_RUN:
        char_move(&wk->wu);
        if (wk->wu.cg_type != 1) {
            break;
        }
        wk->wu.routine_no[3]++;
        /* fall through */
    case D08_AIR:
        jumping_union_process(&wk->wu, 3);
        set_dm_hos_flag_sky(wk);
        break;
    case D08_LAND:
        char_move(&wk->wu);
        break;
    }
    if (wk->wu.cg_type == 0xFF || wk->wu.cg_type == 64) {
        wk->guard_flag = 0;
    }
}



void Damage_12000(PLW* wk) {
    if (wk->wu.dm_work_id & 1) {
        wk->dm_hos_flag = 1;
    }
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init((WORK*)wk, 1, wk->dm_ix);
        wk->dm_step_tbl = dm_step_data[select_hit_dsd[wk->wu.dm_impact][get_weight_point(&wk->wu)]];
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        if (wk->wu.dm_attribute) {
            setup_accessories(wk, wk->wu.pat_status);
            if (wk->wu.dm_attribute != 2) {
                effect_D9_init(wk, (u8)wk->wu.dm_attribute);
            }
        }
        break;
    case D12_SLIDE:
        wk->wu.routine_no[3]++;
        setup_smoke_type(wk);
        if (wk->wu.pat_status == 32) {
            wk->wu.cmwk[14] = damage_pause_table[1][wk->wu.dm_attlv];
        } else {
            wk->wu.cmwk[14] = damage_pause_table[0][wk->wu.dm_attlv];
        }
        if (wk->wu.dm_jump_att_flag > 0) {
            wk->wu.cmwk[14] = damage_pause_table[2][wk->wu.dm_attlv];
        }
        char_move_wca((WORK*)wk);
        add_dm_step_tbl(wk);
        break;
    case D12_SLIDE2:
        add_dm_step_tbl(wk);
        if (--wk->wu.cmwk[14] <= 0) {
            wk->wu.routine_no[3]++;
            char_move_wca((WORK*)wk);
            break;
        }
        /* fall through */
    default:
        char_move((WORK*)wk);
        break;
    }
    if (wk->wu.cg_type == 0xFF || wk->wu.cg_type == 0x40) {
        wk->guard_flag = 0;
    }
}



void Damage_14000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.dm_rl = ((WORK*)wk->wu.dmg_adrs)->rl_flag;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 1, wk->dm_ix);
        setup_butt_own_data(&wk->wu);
        wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D14_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D14_FLIGHT:
        wk->dm_hos_flag = 1;
        first_TtktV_union(wk, 3, 4);
        break;
    case D14_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_16000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        setup_butt_own_data(&wk->wu);
        cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
        get_sky_dm_timer(wk);
        break;
    case D16_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D16_FLIGHT:
        wk->dm_hos_flag = 1;
        first_flight_union(wk, 3, 3);
        break;
    case D16_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
    if (wk->wu.cg_type == 0xFF || wk->wu.cg_type == 0x40) {
        wk->guard_flag = 0;
    }
}



void Damage_17000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data(&wk->wu);
        } else {
            setup_butt_own_data_ex(&wk->wu, 0);
        }
        cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D17_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D17_AIR:
        wk->guard_flag = 3;
        jumping_union_process(&wk->wu, 3);
        set_dm_hos_flag_sky(wk);
        if (wk->wu.routine_no[3] == D17_LAND) {
            wk->guard_flag = 0;
            wk->wu.routine_no[1] = PLAYER_NORMAL;
            wk->wu.routine_no[2] = 23;
            wk->wu.routine_no[3] = D17_AIR;
            wk->tsukamarenai_flag = 8;
        }
        break;
    case D17_LAND:
        char_move(&wk->wu);
        wk->guard_flag = 0;
        wk->wu.routine_no[1] = PLAYER_NORMAL;
        wk->wu.routine_no[2] = 23;
        wk->wu.routine_no[3] = D17_AIR;
        wk->tsukamarenai_flag = 8;
        break;
    }
}



void Damage_18000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init((WORK*)wk, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data((WORK*)wk);
        } else {
            setup_butt_own_data_ex((WORK*)wk, 0);
        }
        cal_initial_speed_y((WORK*)wk, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
        get_sky_dm_timer(wk);
        if (wk->wu.dm_attribute) {
            setup_accessories(wk, wk->wu.pat_status);
            if (wk->wu.dm_attribute != 2) {
                effect_D9_init(wk, (u8)wk->wu.dm_attribute);
            }
        }
        break;
    case D18_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init((WORK*)wk);
        /* fall through */
    case D18_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 3, 3);
        break;
    case D18_LANDED:
        char_move((WORK*)wk);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_19000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.dm_rl = ((WORK*)wk->wu.dmg_adrs)->rl_flag;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data(&wk->wu);
        } else {
            setup_butt_own_data_ex(&wk->wu, 0);
        }
        cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
        get_sky_dm_timer(wk);
        break;
    case D19_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D19_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 3, 3);
        break;
    case D19_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_20000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.dm_rl = ((WORK*)wk->wu.dmg_adrs)->rl_flag;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        setup_butt_own_data(&wk->wu);
        wk->dm_ix = wk->as->char_ix + get_buttobi_attlv(wk);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        get_sky_dm_timer(wk);
        break;
    case D20_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D20_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 3, 4);
        break;
    case D20_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_21000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.dm_rl = ((WORK*)wk->wu.dmg_adrs)->rl_flag;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 1, wk->dm_ix);
        setup_butt_own_data(&wk->wu);
        wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D21_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D21_FLIGHT:
        wk->dm_hos_flag = 1;
        first_TtktV_union(wk, 3, 2);
        break;
    case D21_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_23000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.dm_rl = ((WORK*)wk->wu.dmg_adrs)->rl_flag;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        setup_butt_own_data(&wk->wu);
        wk->dm_ix = wk->as->char_ix + get_buttobi_attlv(wk);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        get_sky_dm_timer(wk);
        break;
    case D23_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D23_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 3, 2);
        break;
    case D23_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_24000(PLW* wk) {
    s32 char_ix;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = (wk->wu.dm_rl + 1) & 1;
        wk->dm_step_tbl = dm_step_data[select_hit_dsd[wk->wu.dm_impact][get_weight_point(&wk->wu)]];
        if (wk->as->char_ix == 0x44) {
            s32 k = wk->dm_point;
            if (k == 2 || k == 3) {
                char_ix = 0x45;
                goto call;
            }
        }
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        char_ix = wk->as->char_ix;
    call:
        set_char_move_init(&wk->wu, 1, char_ix);
        break;
    case D24_SLIDE:
        wk->wu.routine_no[3]++;
        wk->wu.cmwk[14] = damage_pause_table[0][wk->wu.dm_attlv];
        char_move_wca(&wk->wu);
        add_dm_step_tbl(wk);
        break;
    case D24_SLIDE2:
        add_dm_step_tbl(wk);
        if (--wk->wu.cmwk[14] <= 0) {
            wk->wu.routine_no[3]++;
            char_move_wca(&wk->wu);
            break;
        }
        /* fall through: animate while the pause counts down */
    default:
        char_move(&wk->wu);
        if (wk->wu.cg_type == 1) {
            wk->wu.routine_no[2] = 0;
            wk->wu.routine_no[3] = D24_SLIDE;
        }
        break;
    }
}



void Damage_25000(PLW* wk) {
    s16 i;
    s16 hok;
    wk->guard_flag = 3;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        set_char_move_init((WORK*)wk, 1, wk->as->char_ix);
        wk->py->flag = 0;
        wk->py->time = kizetsu_timer_table[(wk->kizetsu_kow & 0xF0) / 16][(wk->kizetsu_kow & 0xF) / 2][random_16_com()];
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        work_init_zero((s32*)wk->rp, sizeof(ComboType));
        break;
    case D25_RUN:
        if ((pcon_dp_flag != 0) && (wk->py->time > 48)) {
            wk->py->time = 48;
        }
        wk->py->time -= wk->cp->lgp / 2;
        if (wk->cp->lgp > 13) {
            hok = 5;
        } else {
            hok = hok_table[wk->cp->lgp / 2];
        }
        for (i = 0; i < hok; i++) {
            char_move((WORK*)wk);
        }
        break;
    }
}



void Damage_26000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data(&wk->wu);
        } else {
            setup_butt_own_data_ex(&wk->wu, 0);
        }
        wk->wu.mvxy.d[1].sp = (wk->wu.mvxy.d[1].sp * 80) / 100;
        cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], 0);
        *(s16*)&wk->wu.mvxy.a[0] = wk->move_power;
        wk->wu.mvxy.a[0].real.l = 0;
        wk->wu.mvxy.a[0].sp *= 3;
        wk->wu.mvxy.a[0].sp /= 4;
        wk->wu.mvxy.d[0].sp = 0;
        if (*(s16*)&wk->wu.mvxy.a[0] > 4) {
            *(s16*)&wk->wu.mvxy.a[0] = 4;
        }
        if (*(s16*)&wk->wu.mvxy.a[0] < 1) {
            *(s16*)&wk->wu.mvxy.a[0] = 1;
        }
        get_sky_dm_timer(wk);
        break;
    case D26_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    case D26_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 3, 3);
        if (wk->wu.routine_no[3] == D26_LANDED && wk->player_number == PL_ELENA) {
            wk->wu.rl_flag = (wk->wu.rl_flag + 1) & 1;
        }
        break;
    case D26_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_27000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 1, wk->dm_ix);
        setup_butt_own_data(&wk->wu);
        wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
        wk->zuru_timer = 0;
        wk->zuru_ix_counter = 0;
        break;
    case D27_NEXT:
        wk->wu.routine_no[3]++;
        char_move_wca_init(&wk->wu);
        /* fall through */
    default:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_28000(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.routine_no[3]++;
        wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
        set_char_move_init(&wk->wu, 6, wk->dm_ix);
        wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        if (wk->wu.dm_butt_type) {
            setup_butt_own_data(&wk->wu);
        } else {
            setup_butt_own_data_ex(&wk->wu, 0);
        }
        cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
        get_sky_dm_timer(wk);
        break;
    case D28_AIR:
        set_dm_hos_flag_sky(wk);
        first_flight_union(wk, 2, 3);
        break;
    case D28_LANDED:
        char_move(&wk->wu);
        buttobi_chakuchi_cg_type_check(wk);
        break;
    }
}



void Damage_29000(PLW* wk) {
    PLW* twk = (PLW*)wk->wu.target_adrs;
    const s16* datadrs;
    switch (wk->wu.routine_no[3]) {
    case RN3_START:
        wk->wu.dm_rl = twk->wu.rl_flag;
        if (wk->dm_point > 2) {
            wk->wu.routine_no[2] = wk->as->data_ix;
            plpdm_lv_00[wk->wu.routine_no[2]](wk);
            break;
        }
        wk->wu.routine_no[3]++;
        datadrs = exdm_ix_data[wk->wu.dm_exdm_ix][wk->player_number];
        if (twk->wu.rl_flag) {
            wk->wu.xyz[0].disp.pos = twk->wu.xyz[0].disp.pos - datadrs[0];
        } else {
            wk->wu.xyz[0].disp.pos = twk->wu.xyz[0].disp.pos + datadrs[0];
        }
        wk->wu.xyz[1].disp.pos = twk->wu.xyz[1].disp.pos + datadrs[1];
        wk->wu.rl_flag = (wk->wu.dm_rl + datadrs[2]) & 1;
        wk->wu.cg_olc_ix = datadrs[3];
        wk->wu.cg_olc = wk->wu.olc_ix_table[wk->wu.cg_olc_ix];
        wk->wu.cg_number = datadrs[4];
        wk->wu.cg_ctr = 0xFA;
        wk->wu.cg_flip = 0;
        wk->wu.cg_type = 0;
        break;
    case D29_NEXT:
        wk->wu.routine_no[2] = wk->as->data_ix;
        wk->wu.routine_no[3]++;
        if (wk->wu.routine_no[2] == 18) {
            wk->dm_ix = wk->as->char_ix + wk->wu.dm_attlv;
            set_char_move_init(&wk->wu, 6, wk->dm_ix);
            char_move_wca_init(&wk->wu);
            wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
            if (wk->wu.dm_butt_type) {
                setup_butt_own_data(&wk->wu);
            } else {
                setup_butt_own_data_ex(&wk->wu, 0);
            }
            cal_initial_speed_y(&wk->wu, buttobi_time_table[wk->dm_ix], wk->wu.xyz[1].disp.pos);
        } else {
            setup_butt_own_data(&wk->wu);
            wk->dm_ix = wk->as->char_ix + get_buttobi_attlv(wk);
            set_char_move_init(&wk->wu, 6, wk->dm_ix);
            char_move_wca_init(&wk->wu);
            wk->wu.xyz[1].disp.pos += buttobi_add_y_table[wk->dm_ix];
        }
        get_sky_dm_timer(wk);
        plpdm_lv_00[wk->wu.routine_no[2]](wk);
        break;
    }
}



/* provisional name */
void set_dm_char_dummy(void) {}



void first_flight_union(PLW* wk, s16 num, s16 dv) {
    jumping_union_process(&wk->wu, num);
    if (wk->wu.routine_no[3] != num) {
        return;
    }
    wk->wu.mvxy.a[0].sp /= dv;
    wk->wu.mvxy.d[0].sp = wk->wu.mvxy.kop[0] = 0;
    wk->wu.mvxy.a[1].sp = wk->wu.mvxy.d[1].sp = wk->wu.mvxy.kop[1] = 0;
    if (wk->ukemi_ok_timer) {
        wk->uot_cd_ok_flag = 1;
    } else {
        wk->uot_cd_ok_flag = 0;
    }
    subtract_cu_vital(wk);
    effect_A7_init(wk);
    buttobi_chakuchi_cg_type_check(wk);
    if (wk->ukemi_ok_timer != 0 && wk->ukemi_success == 0) {
        wk->uot_cd_ok_flag = 1;
    }
}



void first_TtktV_union(PLW* wk, s16 num, s16 dv) {
    char_move(&wk->wu);
    if (wk->wu.cg_type) {
        wk->wu.routine_no[3] = num;
        wk->wu.mvxy.a[0].sp /= dv;
        wk->wu.mvxy.d[0].sp = wk->wu.mvxy.kop[0] = 0;
        if (wk->ukemi_ok_timer) {
            wk->uot_cd_ok_flag = 1;
        } else {
            wk->uot_cd_ok_flag = 0;
        }
        subtract_cu_vital(wk);
        effect_A7_init(wk);
        buttobi_chakuchi_cg_type_check(wk);
        if (wk->ukemi_ok_timer != 0 && wk->ukemi_success == 0) {
            wk->uot_cd_ok_flag = 1;
        }
    } else {
        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);
    }
}



void buttobi_chakuchi_cg_type_check(PLW* wk) {
    switch (wk->wu.cg_type) {
    case 9:
        break;
    case 1:
        add_mvxy_speed(&wk->wu);
        break;
    case 2:
        if (*(s16*)&wk->wu.mvxy.a[0] > 0) {
            add_mvxy_speed_direct(&wk->wu, 96, 0);
            break;
        }
        if (*(s16*)&wk->wu.mvxy.a[0] < 0) {
            add_mvxy_speed_direct(&wk->wu, -96, 0);
        }
        break;
    case 5:
        if (wk->ukemi_success && (wk->dead_flag == 0) && (wk->py->flag == 0) && (wk->wu.vital_new > 0) &&
            (pcon_dp_flag == 0)) {
            wk->wu.routine_no[2] = oki_select_table2[(wk->wu.rl_flag * 2) + wk->wu.rl_waza];
            wk->wu.routine_no[3] = RN3_START;
        }
        if (*(s16*)&wk->wu.mvxy.a[0] > 0) {
            add_mvxy_speed_direct(&wk->wu, 48, 0);
            break;
        }
        if (*(s16*)&wk->wu.mvxy.a[0] < 0) {
            add_mvxy_speed_direct(&wk->wu, -48, 0);
        }
        break;
    }
}



void setup_smoke_type(PLW* wk) {
    const s8* step_tbl;
    u8 ix;
    s16 i;
    s16 total;
    total = 0;
    step_tbl = wk->dm_step_tbl;
    for (i = 0; i < 32; i++) {
        total += *step_tbl++;
    }
    if (total < 0) {
        total = -total;
    }
    if (total >= 32) {
        ix = 0;
        if (total < 48) {
            goto set;
        }
        ix = 1;
        if (total < 64) {
            goto set;
        }
        ix = 2;
        if (total >= 80) {
            ix = 3;
        }
set:
        effect_G6_init((WORK*)wk, ix);
    }
}



void add_dm_step_tbl(PLW* wk) {
    if (wk->wu.dm_rl) {
        wk->wu.xyz[0].disp.pos += *wk->dm_step_tbl++;
    } else {
        wk->wu.xyz[0].disp.pos -= *wk->dm_step_tbl++;
    }
}


void check_dmpat_to_dmpat(PLW* wk) {}



void set_dm_hos_flag_sky(PLW* wk) {
    s16 disx;
    WORK* dwk = (WORK*)wk->wu.dmg_adrs;
    if (dwk->work_id & 3) {
        disx = wk->wu.xyz[0].disp.pos - ((WORK*)wk->wu.target_adrs)->xyz[0].disp.pos;
        if (disx < 0) {
            disx = -disx;
        }
        if (wk->wu.mvxy.a[1].real.h <= 0) {
            if (disx > 64) {
                return;
            }
        } else if (disx > 128) {
            return;
        }
        wk->dm_hos_flag = 1;
    }
}



void set_dm_hos_flag_grd(PLW* wk) {
    s16 disx;
    if (((WORK*)wk->wu.dmg_adrs)->work_id == 1) {
        disx = wk->wu.xyz[0].disp.pos - ((WORK*)wk->wu.target_adrs)->xyz[0].disp.pos;
        if (disx < 0) {
            disx = -disx;
        }
        if (disx <= 160) {
            wk->dm_hos_flag = 1;
        }
    }
}



void get_sky_dm_timer(PLW* wk) {
    if (wk->wu.dm_zuru == 7) {
        wk->zuru_ix_counter = 0;
    } else {
        wk->zuru_ix_counter += sky_dm_zuru_ix[wk->wu.dm_zuru];
    }
    if (wk->zuru_ix_counter > 15) {
        wk->zuru_ix_counter = 15;
    }
    wk->zuru_timer = sky_dm_zuru_table[wk->zuru_ix_counter];
}



void subtract_dm_vital(PLW* wk) {
    if (wk->dead_flag == 0) {
        if (wk->wu.dm_vital != 0) {
            if (wk->wu.routine_no[1] != PLAYER_DAMAGE || wk->wu.routine_no[2] > 11 || wk->wu.routine_no[3] != 0) {
                Additinal_Score_DM((WORK_Other*)wk->wu.dmg_adrs, wk->wu.dm_ten_ix);
            }
        }
        add_sp_arts_gauge_hit_dm(wk);
        if (wk->atemi_flag) {
            wk->dm_vital_backup = wk->wu.dm_vital;
        } else {
            wk->dm_vital_backup = 0;
        }
        wk->wu.vital_new -= wk->wu.dm_vital;
        if (wk->wu.dm_guard_success == -1 && wk->wu.vital_old > 0 && wk->wu.vital_new < 0 && wk->wu.vital_new > -3) {
            wk->wu.vital_new = 0;
        }
        if (wk->wu.dm_nodeathattack && wk->wu.vital_new < 0) {
            wk->wu.vital_new = 0;
        }
        if (wk->wu.vital_new < 0) {
            wk->wu.vital_new = -1;
            wk->dead_flag = 1;
            dead_voice_flag = 1;
            if (wk->wu.dm_guard_success != -1) {
                wk->kezurijini_flag = 1;
            }
            if (round_slow_flag == 0) {
                set_conclusion_slow();
                round_slow_flag = 1;
            }
        } else if (wk->py->flag == 0) {
            wk->py->now.quantity.h += wk->wu.dm_piyo;
            if (wk->py->now.quantity.h >= wk->py->genkai) {
                wk->py->now.timer = 0;
                wk->py->flag = 1;
            }
        }
    }
    wk->wu.dm_vital = 0;
    wk->wu.dm_piyo = 0;
}



void subtract_dm_vital_aiuchi(PLW* wk) {
    if (wk->dead_flag == 0) {
        if (wk->wu.dm_vital != 0) {
            if (wk->wu.routine_no[1] != PLAYER_DAMAGE || wk->wu.routine_no[2] > 11 || wk->wu.routine_no[3] != 0) {
                Additinal_Score_DM((WORK_Other*)wk->wu.dmg_adrs, wk->wu.dm_ten_ix);
            }
        }
        if (wk->atemi_flag) {
            wk->dm_vital_backup = wk->wu.dm_vital;
        } else {
            wk->dm_vital_backup = 0;
        }
        wk->wu.vital_new -= wk->wu.dm_vital;
        if (wk->wu.dm_guard_success == -1 && wk->wu.vital_old > 0 && wk->wu.vital_new < 0 && wk->wu.vital_new > -3) {
            wk->wu.vital_new = 0;
        }
        if (wk->wu.dm_nodeathattack && wk->wu.vital_new < 0) {
            wk->wu.vital_new = 0;
        }
        if (wk->wu.vital_new < 0) {
            wk->wu.vital_new = -1;
            wk->dead_flag = 1;
            dead_voice_flag = 1;
            if (wk->wu.dm_guard_success != -1) {
                wk->kezurijini_flag = 1;
            }
            if (round_slow_flag == 0) {
                set_conclusion_slow();
                round_slow_flag = 1;
            }
        } else if (wk->py->flag == 0) {
            wk->py->now.quantity.h += wk->wu.dm_piyo;
            if (wk->py->now.quantity.h >= wk->py->genkai) {
                wk->py->now.timer = 0;
                wk->py->flag = 1;
            }
        }
    }
    wk->wu.dm_vital = 0;
    wk->wu.dm_piyo = 0;
}



void get_damage_reaction_data(PLW* wk) {
    if (wk->atemi_flag == 2) {
        wk->wu.dm_vital = 0;
        damage_atemi_setup(wk, (PLW*)wk->wu.dmg_adrs);
        return;
    }
    subtract_dm_vital(wk);
    if (wk->wu.routine_no[2] == 88) {
        wk->wu.routine_no[2] = check_buttobi_type(wk);
    }
    if (wk->py->flag && wk->wu.routine_no[2] == 88) {
        wk->wu.routine_no[2] = 91;
    }
    if (wk->dead_flag) {
        wk->wu.routine_no[2] = dd_convert[wk->wu.routine_no[2]][wk->wu.dm_attlv];
        if (wk->wu.routine_no[2] > 19 && wk->wu.routine_no[2] < 88) {
            if (wk->wu.routine_no[2] != 70) {
                wk->wu.routine_no[2] = check_buttobi_type2(&wk->wu);
            }
        }
    }
    if (wk->atemi_flag == 1) {
        damage_atemi_setup(wk, (PLW*)wk->wu.dmg_adrs);
        return;
    }
    wk->as = (AS*)&dm_reaction_table[wk->wu.routine_no[2]];
    wk->wu.routine_no[2] = wk->as->r_no;
    if (wk->wu.dm_stop) {
        if (wk->wu.dm_stop > 0) {
            wk->wu.dm_stop--;
        }
        if (wk->wu.dm_stop < 0) {
            wk->wu.dm_stop++;
        }
    }
}



static void damage_atemi_setup(PLW* wk, PLW* ek) {
    wk->wu.routine_no[1] = wk->wu.cmmd.koc;
    wk->wu.routine_no[2] = wk->wu.cmmd.ix;
    wk->wu.routine_no[3] = wk->wu.cmmd.pat;
    char_move_cmms(&wk->wu);
    wk->atemi_flag = 9;
    wk->wu.dm_stop = wk->wu.dm_quake = 0;
    wk->wu.hit_stop = wk->wu.hit_quake = 0;
    ek->wu.dm_stop = ek->wu.dm_quake = 0;
    ek->wu.hit_stop = wk->wu.att.hs_you;
    ek->wu.hit_quake = wk->wu.att.hs_you / 2;
}



s32 setup_kuzureochi(PLW* wk) {
    if (wk->wu.vital_new >= 0) {
        return 0;
    }
    wk->wu.routine_no[1] = PLAYER_DAMAGE;
    wk->wu.routine_no[2] = 0;
    wk->wu.routine_no[3] = 1;
    wk->zuru_timer = 0;
    wk->zuru_ix_counter = 0;
    set_char_move_init(&wk->wu, 1, 73);
    wk->wu.dm_stop = wk->wu.hit_stop = 0;
    wk->wu.dm_quake = wk->wu.hit_quake = 0;
    return 1;
}



void get_catch_off_data(PLW* wk, s16 ix) {
    wk->as = (const AS*)&dm_reaction_table[ix];
}



void check_bullet_damage(PLW* wk) {
    WORK* tk = (WORK*)wk->wu.dmg_adrs;
    if (tk->work_id != 1 && tk->id == 13) {
        if (tama_select[tk->type] != 0) {
            wk->bullet_hcnt += tama_select[tk->type];
            wk->bhcnt_timer = 800;
        }
    }
}
