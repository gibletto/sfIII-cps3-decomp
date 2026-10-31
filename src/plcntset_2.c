/*
 * PLCNTSET_2.C  Player control and fight settlement
 *
 * Runs the appear, fight and settlement phases for both players, resolves body contact
 * and push-back, and maintains the player work, super art and dizziness state.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SLOWF.h"
#include "Manage.h"
#include "manage_2.h"
void Player_move();
#include "PLS02.h"
#include "effd2.h"
#include "effd3.h"
#include "ta_sub.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "PLS01.h"
#include "PLPNM.h"
#include "PLPDM.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "EFFC9.h"
#include "PLCNTSET.h"
#include "EFF33.h"
#include "plcntset_2.h"
#include "fighter.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "HITCHECK.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "spgauge.h"
#include "sc_sub.h"
#include "sc_sub_2.h"
#include "EFFM7.h"
#include "SYS_sub.h"
#include "sc_trans.h"
#include "VITAL.h"
#include "count.h"
#include "EFF02.h"
#include "EFF00.h"
#include "EFFE5.h"
#include "CHARID.h"

/* pcon_rno[2] in settle_type_10000 */
#define DK_DOWN         0       /* until both are down */
#define DK_PAUSE        1       /* the pause */

/* pcon_rno[2] in settle_type_20000 */
#define TO_INIT         0       /* stop both players */
#define TO_FOOTWORK     1       /* until both are steady */
#define TO_DECIDE       2       /* the pause: a draw stops here, else the win and lose poses */
#define TO_POSE         3       /* until a win pose is done */
#define TO_DRAW         4       /* a draw: nothing more */

static void move_player_work(void);

void Player_control(void) {
    s16 i;
    pl_eff_disp_stop = 0;
    if ((pcon_rno[0] + pcon_rno[1]) == 0) {
        goto run;
    }
    if (!Game_pause && !EXE_flag) {
run:
        players_timer++;
        players_timer &= 0x7FFF;
        player_main_process[pcon_rno[0]]();
        check_body_touch();
        check_damage_hosei();
        set_quake(&plw[0]);
        set_quake(&plw[1]);
        if (Game_timer & 1) {
            if (plw[1].zuru_flag == 0) {
                hit_push_request(&plw[1].wu);
            }
            if (plw[0].zuru_flag == 0) {
                hit_push_request(&plw[0].wu);
            }
        } else {
            if (plw[0].zuru_flag == 0) {
                hit_push_request(&plw[0].wu);
            }
            if (plw[1].zuru_flag == 0) {
                hit_push_request(&plw[1].wu);
            }
        }
        add_next_position(&plw[0]);
        add_next_position(&plw[1]);
        check_cg_zoom();
    }
    for (i = 47; i > 0; i--) {
        zanzou_table[0][i] = zanzou_table[0][i - 1];
        zanzou_table[1][i] = zanzou_table[1][i - 1];
    }
    zanzou_table[0]->pos_x = plw[0].wu.position_x;
    zanzou_table[0]->pos_y = plw[0].wu.position_y;
    zanzou_table[0]->pos_z = plw[0].wu.position_z;
    zanzou_table[0]->cg_num = plw[0].wu.cg_number;
    zanzou_table[0]->renew = plw[0].wu.renew_attack;
    zanzou_table[0]->hit_ix = plw[0].wu.cg_hit_ix;
    zanzou_table[0]->flip = plw[0].wu.rl_flag;
    zanzou_table[0]->cg_flp = plw[0].wu.cg_flip;
    zanzou_table[0]->kowaza = plw[0].wu.at_koa;
    zanzou_table[1]->pos_x = plw[1].wu.position_x;
    zanzou_table[1]->pos_y = plw[1].wu.position_y;
    zanzou_table[1]->pos_z = plw[1].wu.position_z;
    zanzou_table[1]->cg_num = plw[1].wu.cg_number;
    zanzou_table[1]->renew = plw[1].wu.renew_attack;
    zanzou_table[1]->hit_ix = plw[1].wu.cg_hit_ix;
    zanzou_table[1]->flip = plw[1].wu.rl_flag;
    zanzou_table[1]->cg_flp = plw[1].wu.cg_flip;
    zanzou_table[1]->kowaza = plw[1].wu.at_koa;
    if (pl_eff_disp_stop == 0) {
        sort_push_request((WORK*)&plw[0]);
        sort_push_request((WORK*)&plw[1]);
    }
    spgauge_cont_main();
    stngauge_cont_main();
}

void plcnt_init(void) {
    appear_initalize[appear_type]();
    move_player_work();
}

void init_app_10000(void) {
    switch (pcon_rno[1]) {
    case APP_SETUP:
        pli_0000();
        if (plw[0].wu.operator) {
            paring_ctr_vs[0][0] = paring_ctr_ori[0];
        } else {
            paring_ctr_vs[0][0] = 0;
        }
        if (plw[1].wu.operator) {
            paring_ctr_vs[0][1] = paring_ctr_ori[1];
        } else {
            paring_ctr_vs[0][1] = 0;
        }
        round_slow_flag = 0;
        dead_voice_flag = 0;
        pcon_dp_flag = 0;
        another_bg[0] = another_bg[1] = 0;
        if (plw[0].player_number == PL_ORO || plw[1].player_number == PL_ORO) {
            load_any_color(0x8B);
        }
        break;
    case APP_WAIT_READY:
        pli_1000();
        break;
    }
}

void init_app_20000(void) {
    s16 i;
    switch (pcon_rno[1]) {
    case APP_SETUP:
        pcon_rno[1]++;
        round_slow_flag = 0;
        dead_voice_flag = 0;
        pcon_dp_flag = 0;
        another_bg[0] = another_bg[1] = 0;
        reset_char_disp_work(&plw[0].wu);
        reset_char_disp_work(&plw[1].wu);
        for (i = 0; i < 8; i++) {
            plw[0].wu.routine_no[i] = plw[1].wu.routine_no[i] = 0;
        }
        setup_any_data();
        break;
    case APP_WAIT_READY:
        pli_1000();
        break;
    }
}

void init_app_30000(void) {
    s16 i;
    switch (pcon_rno[1]) {
    case APP_SETUP:
        pcon_rno[1]++;
        round_slow_flag = 0;
        dead_voice_flag = 0;
        for (i = 1; i < 8; i++) {
            plw[0].wu.routine_no[i] = plw[1].wu.routine_no[i] = 0;
        }
        plw[0].wu.routine_no[0] = plw[1].wu.routine_no[0] = PLAYER_MV_PLACE;
        another_bg[0] = another_bg[1] = 0;
        break;
    case APP_WAIT_READY:
        if (plw[0].wu.routine_no[0] != PLAYER_MV_READY || plw[1].wu.routine_no[0] != PLAYER_MV_READY) {
            return;
        }
        pcon_rno[0] = PCON_DIE;
        pcon_rno[1] = SETTLE_JUDGE;
        pcon_rno[2] = JG_WAIT;
        setup_EJG_index();
        effect_C9_init(&plw[0], 0);
        effect_C9_init(&plw[0], 1);
        effect_C9_init(&plw[0], 2);
        load_any_color(0x88);
        load_any_color(0x8A);
        load_char_gfx(0x76A8, 1);
        break;
    }
}

void pli_0000(void) {
    pcon_rno[1]++;
    round_slow_flag = 0;
    work_init_zero((s32*)&plw[0], sizeof(PLW));
    work_init_zero((s32*)&plw[1], sizeof(PLW));
    setup_base_and_other_data();
}

void pli_1000(void) {
    if ((plw[0].wu.routine_no[0] == PLAYER_MV_READY) && (plw[1].wu.routine_no[0] == PLAYER_MV_READY)) {
        if (Allow_a_battle_f) {
            pcon_rno[0] = PCON_MOVE;
            pcon_rno[1] = 0;
            plw[0].wu.routine_no[0] = PLAYER_MV_FIGHT;
            plw[1].wu.routine_no[0] = PLAYER_MV_FIGHT;
            ca_check_flag = 1;
        }
    }
}

void plcnt_move(void) {
    if (time_over_check() != 0) {
        return;
    }
    if (((u8)No_Death)) {
        plw[0].wu.dm_vital = plw[1].wu.dm_vital = 0;
    }
    if (Break_Into) {
        plw[0].wu.dm_vital = plw[1].wu.dm_vital = 0;
    }
    move_player_work();
    if (aiuchi_flag) {
        subtract_dm_vital_aiuchi(&plw[0]);
        subtract_dm_vital_aiuchi(&plw[1]);
        if ((plw[0].dead_flag != 0) && (plw[1].dead_flag != 0)) {
            plw[0].wu.hit_stop = plw[1].wu.hit_stop = 2;
            plw[0].wu.dm_stop = plw[1].wu.dm_stop = 0;
            plw[0].wu.hit_quake = plw[1].wu.hit_quake = 4;
            plw[0].wu.dm_quake = plw[1].wu.dm_quake = 0;
        } else if ((plw[0].dead_flag != 0) || (plw[1].dead_flag != 0)) {
            plw[0].wu.hit_stop = plw[1].wu.hit_stop = 4;
            plw[0].wu.dm_stop = plw[1].wu.dm_stop = 0;
            plw[0].wu.hit_quake = plw[1].wu.hit_quake = 8;
            plw[0].wu.dm_quake = plw[1].wu.dm_quake = 0;
        }
    }
    settle_check();
    if (pcon_rno[0] == PCON_DIE) {
        if (Round_Result & 0x180) {
            effect_D3_init();
        }
        if ((plw[0].kezurijini_flag == 1) || (plw[1].kezurijini_flag == 1)) {
            Round_Result |= RESULT_CHIP;
        }
    }
}

void plcnt_die(void) {
    plw[0].wu.dm_vital = plw[1].wu.dm_vital = 0;
    settle_process[pcon_rno[1]]();
    move_player_work();
    if (pcon_rno[1] == SETTLE_JUDGE) {
        plw[0].scr_pos_set_flag = plw[1].scr_pos_set_flag = 0;
    }
}

void settle_type_00000(void) {
    switch (pcon_rno[2]) {
    case KO_INIT:
        plw[Winner_id].wu.dir_timer = 60;
        pcon_rno[2]++;
        /* fall through */
    case KO_DOWN:
        if (nekorobi_check(Loser_id)) {
            pcon_rno[2]++;
            plw[Winner_id].wkey_flag = 1;
        }
        if (--plw[Winner_id].wu.dir_timer != 0) {
            break;
        } else {
            plw[Winner_id].wkey_flag = 1;
            break;
        }
    case KO_FOOTWORK:
        if (footwork_check(Winner_id)) {
            pcon_rno[2]++;
            plw[Winner_id].wu.routine_no[2] = NORMAL_WIN;
            plw[Winner_id].wu.routine_no[3] = RN3_START;
            plw[Loser_id].wu.routine_no[1] = PLAYER_NORMAL;
            plw[Loser_id].wu.routine_no[2] = NORMAL_LOSE;
            plw[Loser_id].wu.routine_no[3] = RN3_START;
            plw[0].wu.cg_type = plw[1].wu.cg_type = 0;
            plw[0].image_setup_flag = plw[1].image_setup_flag = 0;
            complete_victory_pause();
        }
        break;
    case KO_POSE:
        if (plw[Winner_id].wu.routine_no[3] == RN3_DONE) {
            pcon_rno[2]++;
        }
        break;
    }
}

void settle_type_10000(void) {
    switch (pcon_rno[2]) {
    case DK_DOWN:
        if (nekorobi_check(0) && nekorobi_check(1)) {
            pcon_rno[2]++;
        }
        break;
    case DK_PAUSE:
        complete_victory_pause();
        pcon_rno[2]++;
        plw[0].image_setup_flag = plw[1].image_setup_flag = 0;
        if (bg_w.stage == 8 && bg_w.area == 0) {
            plw[0].wu.routine_no[1] = PLAYER_NORMAL;
            plw[0].wu.routine_no[2] = NORMAL_LOSE;
            plw[0].wu.routine_no[3] = RN3_START;
            plw[1].wu.routine_no[1] = PLAYER_NORMAL;
            plw[1].wu.routine_no[2] = NORMAL_LOSE;
            plw[1].wu.routine_no[3] = RN3_START;
            plw[0].wu.cg_type = plw[1].wu.cg_type = 0;
        }
        break;
    }
}

void settle_type_20000(void) {
    switch (pcon_rno[2]) {
    case TO_INIT:
        plw[0].wkey_flag = plw[1].wkey_flag = 1;
        plw[0].image_setup_flag = plw[1].image_setup_flag = 0;
        pcon_rno[2]++;
        /* fall through */
    case TO_FOOTWORK:
        if (footwork_check(0)) {
            if (footwork_check(1)) {
                pcon_rno[2]++;
            }
        }
        break;
    case TO_DECIDE:
        complete_victory_pause();
        if (plw[0].wu.vital_new == plw[1].wu.vital_new) {
            pcon_rno[2] = TO_DRAW;
        } else {
            plw[Winner_id].wu.routine_no[2] = NORMAL_WIN;
            plw[Loser_id].wu.routine_no[2] = NORMAL_LOSE;
            plw[0].wu.routine_no[3] = plw[1].wu.routine_no[3] = RN3_START;
            plw[0].wu.cg_type = plw[1].wu.cg_type = 0;
            pcon_rno[2]++;
        }
        break;
    case TO_POSE:
        if ((plw[0].wu.routine_no[3] == RN3_DONE) && (plw[1].wu.routine_no[3] == RN3_DONE)) {
            pcon_rno[2]++;
        }
        break;
    }
}

void settle_type_30000(void) {
    switch (pcon_rno[2]) {
    case JG_IDLE:
        break;
    case JG_WAIT:
        if (Event_Judge_Gals != -1) {
            break;
        }
        if (Complete_Judgement) {
            plw[Winner_id].wu.routine_no[2] = NORMAL_WIN;
            plw[Loser_id].wu.routine_no[2] = NORMAL_LOSE;
            plw[0].wu.routine_no[3] = plw[1].wu.routine_no[3] = RN3_START;
            plw[0].wu.cg_type = plw[1].wu.cg_type = 0;
            complete_victory_pause();
            pcon_rno[2]++;
        }
        break;
    case JG_POSE:
        if ((plw[0].wu.routine_no[3] == RN3_DONE) && (plw[1].wu.routine_no[3] == RN3_DONE)) {
            pcon_rno[2]++;
        }
        break;
    }
}

static void move_P1_move_P2();
static void move_P2_move_P1();

static void move_player_work(void) {
    s16 center;
    s16 scr_r;
    s16 scr_l;
    center = get_center_position();
    if (Game_setting.Screen_Mode) {
        scr_r = center + 248;
        scr_l = center - 248;
    } else {
        scr_r = center + 192;
        scr_l = center - 192;
    }
    switch (plw[0].tsukami_f + (plw[1].tsukami_f * 2)) {
    case 1:
        move_P1_move_P2(scr_r, scr_l);
        break;
    case 2:
        move_P2_move_P1(scr_r, scr_l);
        break;
    default:
        switch (plw[0].wu.operator + (plw[1].wu.operator * 2)) {
        case 1:
            move_P1_move_P2(scr_r, scr_l);
            break;
        case 2:
            move_P2_move_P1(scr_r, scr_l);
            break;
        default:
            switch ((plw[0].wu.routine_no[1] == PLAYER_ATTACK) + ((plw[1].wu.routine_no[1] == PLAYER_ATTACK) * 2)) {
            case 1:
                move_P1_move_P2(scr_r, scr_l);
                break;
            case 2:
                move_P2_move_P1(scr_r, scr_l);
                break;
            default:
                if (Game_timer & 1) {
                    move_P1_move_P2(scr_r, scr_l);
                } else {
                    move_P2_move_P1(scr_r, scr_l);
                }
                break;
            }
            break;
        }
        break;
    }
}

static void move_P1_move_P2(scr_r, scr_l)
s16 scr_r;
s16 scr_l;
{
    Player_move(&plw[0], p1sw_0);
    if (bg_stop == 0 && bg_app == 0) {
        if (set_field_hosei_flag(&plw[0], scr_r, 1)) {
            set_field_hosei_flag(&plw[0], scr_l, 0);
        }
    }
    Player_move(&plw[1], p2sw_0);
    if (bg_stop == 0 && bg_app == 0) {
        if (set_field_hosei_flag(&plw[1], scr_r, 1)) {
            set_field_hosei_flag(&plw[1], scr_l, 0);
        }
    }
}

static void move_P2_move_P1(scr_r, scr_l)
s16 scr_r;
s16 scr_l;
{
    Player_move(&plw[1], p2sw_0);
    if (bg_stop == 0 && bg_app == 0) {
        if (set_field_hosei_flag(&plw[1], scr_r, 1)) {
            set_field_hosei_flag(&plw[1], scr_l, 0);
        }
    }
    Player_move(&plw[0], p1sw_0);
    if (bg_stop == 0 && bg_app == 0) {
        if (set_field_hosei_flag(&plw[0], scr_r, 1)) {
            set_field_hosei_flag(&plw[0], scr_l, 0);
        }
    }
}

void check_damage_hosei(void) {
    switch ((plw[0].hosei_amari != 0) + ((plw[1].hosei_amari != 0) * 2)) {
    case 1:
        if (plw[0].tsukami_f | plw[0].tsukamare_f | plw[0].dm_hos_flag) {
            plw[1].wu.xyz[0].disp.pos += plw[0].hosei_amari;
        }
        plw[0].hosei_amari = 0;
        break;
    case 2:
        if (plw[1].tsukami_f | plw[1].tsukamare_f | plw[1].dm_hos_flag) {
            plw[0].wu.xyz[0].disp.pos += plw[1].hosei_amari;
        }
        plw[1].hosei_amari = 0;
        break;
    case 3:
        if (plw[0].hos_fi_flag == plw[1].hos_fi_flag) {
            if (plw[0].tsukamare_f) {
                plw[1].wu.xyz[0].disp.pos += plw[0].hosei_amari;
            }
            if (plw[1].tsukamare_f) {
                plw[0].wu.xyz[0].disp.pos += plw[1].hosei_amari;
            }
        }
        plw[0].hosei_amari = plw[1].hosei_amari = 0;
        break;
    }
}

s32 time_over_check(void) {
    if (will_die() != 0) {
        if (round_timer.size.full == 0) {
            Winner_id = 0;
            Loser_id = 1;
            if (plw[0].wu.vital_new < plw[1].wu.vital_new) {
                Winner_id = 1;
                Loser_id = 0;
            }
            Conclusion_Flag = 1;
            Conclusion_Type = CONCLUSION_TIME_OVER;
            setup_settle_rno(SETTLE_TIME_OVER);
            if (Demo_Flag) {
                request_center_message(2);
            }
            plw[0].wu.dm_vital = plw[1].wu.dm_vital = 0;
            Round_Result |= RESULT_TIME;
            return 1;
        }
    }
    return 0;
}

s32 will_die(void) {
    if (plw[0].wu.dm_vital > plw[0].wu.vital_new) {
        return 0;
    }
    if (plw[1].wu.dm_vital > plw[1].wu.vital_new) {
        return 0;
    }
    return 1;
}

void setup_settle_rno(kos)
s16 kos;
{
    pcon_rno[0] = PCON_DIE;
    pcon_rno[1] = kos;
    pcon_rno[2] = 0;
    ca_check_flag = 0;
    pcon_dp_flag = 1;
}

void settle_check(void) {
retry:
    switch (plw[0].dead_flag + plw[1].dead_flag * 2) {
    case 1:
        Winner_id = 1;
        Loser_id = 0;
        goto settle;
    case 2:
        Winner_id = 0;
        Loser_id = 1;
    settle:
        if (check_sa_resurrection(&plw[Loser_id])) {
            break;
        }
        Conclusion_Flag = 1;
        Conclusion_Type = CONCLUSION_KO;
        setup_settle_rno(SETTLE_KO);
        if (Demo_Flag) {
            request_center_message(0);
        }
        Round_Result |= plw[Loser_id].wu.dm_koa;
        break;
    case 3:
        if (check_sa_resurrection(&plw[0]) || check_sa_resurrection(&plw[1])) {
            goto retry;
        }
        Conclusion_Flag = 1;
        Conclusion_Type = CONCLUSION_DOUBLE_KO;
        setup_settle_rno(SETTLE_DOUBLE_KO);
        if (Demo_Flag) {
            request_center_message(1);
        }
        break;
    default:
        break;
    }
}

s32 check_sa_resurrection(PLW* wk) {
    if (check_sa_type_rebirth(wk) == 0) {
        return 0;
    }
    wk->dead_flag = 0;
    return 1;
}

s32 check_sa_type_rebirth(PLW* wk) {
    if (wk->sa->gauge_type != SA_GAUGE_REBIRTH) {
        return 0;
    }
    if (wk->sa->ok != 1) {
        return 0;
    }
    return 1;
}

s32 nekorobi_check(char pl) {
    s16 result;
    result = 0;
    if (plw[pl].wu.routine_no[1] == PLAYER_DAMAGE) {
        if (plw[pl].wu.routine_no[2] == 0) {
            if (plw[pl].wu.routine_no[3] > 2) {
                result = 1;
            }
        }
    }
    return result;
}

s32 footwork_check(char pl) {
    s16 result;
    result = 0;
    if (plw[pl].wu.routine_no[1] == PLAYER_NORMAL) {
        if (plw[pl].wu.routine_no[2] == NORMAL_STAND) {
            result = 1;
        }
    }
    return result;
}

/* provisional name */
void reset_char_disp_work(WORK* wk) {
    s16 i;
    for (i = 0; i < 4; i++) {
        wk->spr.gfx_blk10[i] = wk->spr.gfx_blk40[i] = 0;
    }
    wk->old_cgnum = 0;
    wk->spr.gfx_ofs = 0;
    wk->spr.gfx_cells = 0;
}

void set_quake(PLW* wk) {
    if (wk->wu.hit_quake) {
        wk->wu.hit_quake--;
        wk->wu.next_x = quake_table[wk->wu.hit_quake];
        if (wk->wu.rl_flag) {
            wk->wu.next_x = -wk->wu.next_x;
        }
    } else {
        wk->wu.next_x = 0;
    }
    wk->wu.next_y = 0;
}

void add_next_position(PLW* wk) {
    wk->wu.position_x = wk->wu.xyz[0].disp.pos + wk->wu.next_x;
    wk->wu.position_y = wk->wu.xyz[1].disp.pos + wk->wu.next_y;
    wk->wu.position_z = wk->wu.next_z;
}

/* provisional name */
void debug_player_change(void) {
    u16 sw;
    const s8* data;
    if ((sw = exsw_1) & 0x4000) {
        sw = sw & 0xFF;
        if ((data = plid_data)[sw & 0xF]) {
            My_char[0] = sw & 0xF;
        }

        if (*(const s8*)((u32)data + (sw & 0xF0) / 16)) {
            My_char[1] = (sw & 0xF0) / 16;
        }
    }
}

void setup_base_and_other_data(void) {
    set_base_data(&plw[0], 0);
    set_base_data(&plw[1], 1);
    plw[0].sa = &super_arts[0];
    plw[1].sa = &super_arts[1];
    plw[0].py = &piyori_type[0];
    plw[1].py = &piyori_type[1];
    setup_other_data(&plw[0]);
    setup_other_data(&plw[1]);
    effect_E5_init(&plw[0]);
    effect_E5_init(&plw[1]);
    if (plw[0].wu.my_priority == plw[1].wu.my_priority) {
        plw[0].the_same_players = plw[1].the_same_players = 1;
    }
}

void setup_any_data(void) {
    set_base_data_tiny(&plw[0]);
    set_base_data_tiny(&plw[1]);
    setup_other_data(&plw[0]);
    setup_other_data(&plw[1]);
    effect_E5_init(&plw[0]);
    effect_E5_init(&plw[1]);
    if (plw[0].wu.my_priority == plw[1].wu.my_priority) {
        plw[0].the_same_players = plw[1].the_same_players = 1;
    }
}

void set_base_data(PLW* wk, s16 ix) {
    wk->wu.be_flag = 1;
    wk->wu.disp_flag = 0;
    wk->wu.blink_timing = ix;
    wk->wu.id = ix;
    wk->wu.work_id = 1;
    wk->wu.operator = Operator_Status[ix];
    wk->wu.charset_id = plid_data[My_char[ix]];
    wk->wkey_flag = wk->dead_flag = 0;
    set_char_base_data(&wk->wu);
    wk->wu.target_adrs = (u32*)&plw[(ix + 1) & 1];
    wk->player_number = My_char[ix];
    cmd_init(wk);
    wk->cb = &combo_type[ix];
    wk->rp = &remake_power[ix];
    if (ix) {
        wk->wu.my_col_code |= 0x10;
    }
    wk->spmv_ng_flag = spmv_ng_table[wk->player_number];
    wk->wu.weight_level = weight_lv_table[wk->player_number];
    set_player_shadow(wk);
}

void set_base_data_tiny(PLW* wk) {
    wk->wu.be_flag = 1;
    wk->wu.disp_flag = 0;
    wk->wkey_flag = wk->dead_flag = 0;
    cmd_init(wk);
    set_player_shadow(wk);
}

void set_player_shadow(PLW* wk) {
    wk->wu.kage_flag = 1;
    wk->wu.kage_prio = 68;
    wk->wu.kage_hx = kage_base[wk->player_number][0];
    wk->wu.kage_char = kage_base[wk->player_number][1];
}

void setup_other_data(PLW* wk) {
    load_player_color(wk->player_number, wk->wu.id, Player_Color[wk->wu.id]);
    effect_01_init((WORK*)wk, 0);
    effect_01_init((WORK*)wk, 1);
    effect_01_init((WORK*)wk, 2);
    effect_01_init((WORK*)wk, 3);
}

void set_kizetsu_status(ix)
s16 ix;
{
    s16 plnum = My_char[ix];
    piyori_type[ix].flag = 0;
    piyori_type[ix].time = 0;
    piyori_type[ix].now.timer = 0;
    piyori_type[ix].store = 0;
    piyori_type[ix].genkai = pl_piyo_tbl[plnum];
    piyori_type[ix].recover = pl_nr_piyo_tbl[plnum];
}

void clear_kizetsu_point(PLW* wk) {
    wk->py->flag = 0;
    wk->py->time = 0;
    wk->py->now.timer = 0;
    wk->py->store = 0;
}

void set_super_arts_status(s16 pl) {
    const SA_DATA *data;

    data = super_arts_data[My_char[pl]] + Super_Arts[pl];
    super_arts[pl].kind_of_arts = Super_Arts[pl];
    super_arts[pl].nmsa_g_ix = data->nmsa_g_ix;
    super_arts[pl].gauge_type = data->gauge_type;
    super_arts[pl].gauge_len = data->gauge_len;
    super_arts[pl].store_max = data->store_max;
    super_arts[pl].dtm = data->dtm;
    super_arts[pl].store = 0;
    super_arts[pl].gauge.s.h = 0;
    super_arts[pl].gauge.s.l = -1;
    super_arts[pl].sa_rno = 0;
    super_arts[pl].ok = 0;
}

void clear_super_arts_point(PLW* wk) {
    wk->sa->gauge.s.h = 0;
    wk->sa->gauge.s.l = -1;
    wk->sa->sa_rno = 0;
    wk->sa->ok = 0;
}

s32 check_combo_end(ix)
s16 ix;
{
    s16 rnum;
    if (plw[ix].py->flag) {
        return 1;
    }
    if (plw[ix].tsukamare_f) {
        return 1;
    }
    if (pcon_rno[0] == PCON_DIE && pcon_rno[1] == SETTLE_KO && pcon_rno[2] == KO_FOOTWORK) {
        return 0;
    }
    if (plw[ix].wu.cg_ja.boix == 0 && plw[ix].wu.cg_ja.cuix == 0 && plw[ix].wu.pat_status == 38) {
        return 0;
    }
    if (plw[ix].zuru_flag) {
        return 0;
    }
    if (plw[ix].wu.routine_no[1] != PLAYER_DAMAGE && plw[ix].wu.routine_no[1] != PLAYER_CAUGHT) {
        return 0;
    }
    if (plw[ix].old_gdflag != plw[ix].guard_flag) {
        if (plw[ix].guard_flag == 0) {
            rnum = 0;
        } else {
            rnum = 1;
        }
    } else if (plw[ix].guard_flag == 0) {
        rnum = 0;
    } else {
        rnum = 1;
    }
    return rnum;
}
