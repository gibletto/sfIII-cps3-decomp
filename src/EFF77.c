/*
 * EFF77.C  Effect 77: the stage character of the perfect-victory scene
 *
 * effect_77_init (from effect 82) places the character at (320, 52) and creates its companions
 * (effects 78, 79 and 80). In the first area, while the effect 82 controller waits, it plays its idle
 * pattern and reacts (pattern 1) when a character 7 player attacks (eff94_pl_attack_check). When the
 * controller moves to state 1 it runs its scene (eff77_0100 to eff77_0106): it jumps away out of
 * sight, reappears 144 dots in front of the losing player, flies to where the player stands and plays
 * its last pattern once the player's pattern status is 38. It is freed in the controller's state 2.
 * In the later areas it only plays pattern 4 in place.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "PLS02.h"
#include "bg_sub_5.h"
#include "fighter.h"

/* routine_no[2] */
#define R2_WATCH        0       /* watch for an attack */
#define R2_START        1       /* start the reaction */
#define R2_PLAY         2       /* play it, then idle again */

/* routine_no[0], later areas */
#define R0_INIT         0       /* show in place */
#define R0_MOVE         1       /* animate */

extern const u32 eff77_char_table[];
void eff77_0000(WORK_Other* ewk);
void eff77_0001(WORK_Other* ewk);
void eff77_0100(WORK_Other* ewk);
void eff77_0101(WORK_Other* ewk);
void eff77_0102(WORK_Other* ewk);
void eff77_0103(WORK_Other* ewk);
void eff77_0104(WORK_Other* ewk);
void eff77_0105(WORK_Other* ewk);
void eff77_0106(WORK_Other* ewk);
void eff77_area1(WORK_Other* ewk);
void eff77_area0(WORK_Other* ewk);
s32 effect_78_init(WORK_Other* mwk);
s32 effect_80_init(WORK_Other* mwk);
s32 effect_79_init(WORK_Other* mwk);

void (*eff77_jp_tbl[2])(WORK_Other*) = { eff77_0000, eff77_0001 };
void (*eff77_jp_tbl2[7])(WORK_Other*) = {
    eff77_0100, eff77_0101, eff77_0102, eff77_0103, eff77_0104, eff77_0105, eff77_0106,
};

void effect_77_move(WORK_Other* ewk) {
    if (bg_w.area) {
        eff77_area1(ewk);
    } else {
        eff77_area0(ewk);
    }
}

void eff77_area0(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    switch (mwk->wu.routine_no[0]) {
    case 0:
        if (!EXE_flag && !Game_pause) {
            eff77_jp_tbl[ewk->wu.routine_no[0]](ewk);
        }
        disp_pos_trans_entry_r(ewk);
        break;
    case 1:
        if (!EXE_flag && !Game_pause) {
            eff77_jp_tbl2[ewk->wu.routine_no[1]](ewk);
        }
        disp_pos_trans_entry_r(ewk);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
}

void eff77_0000(WORK_Other* ewk) {
    ewk->wu.routine_no[0]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init(&ewk->wu, 0, 0);
}

s32 eff94_pl_attack_check(PLW* wk) {
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE && wk->wu.routine_no[2] > 11) {
        return 1;
    }
    return 0;
}

void eff77_0001(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case R2_WATCH:
        if (plw[0].player_number == PL_IBUKI) {
            if (eff94_pl_attack_check(&plw[0])) {
                ewk->wu.routine_no[2]++;
                break;
            }
        }
        if (plw[1].player_number == PL_IBUKI) {
            if (eff94_pl_attack_check(&plw[1])) {
                ewk->wu.routine_no[2]++;
                break;
            }
        }
        break;
    case R2_START:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, 1);
        break;
    case R2_PLAY:
        char_move(&ewk->wu);
        if (ewk->wu.cg_type) {
            set_char_move_init(&ewk->wu, 0, 0);
            ewk->wu.routine_no[2] = R2_WATCH;
        }
        break;
    default:
        break;
    }
}

void eff77_0100(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    set_char_move_init(&ewk->wu, 0, 2);
    ewk->wu.my_priority = ewk->wu.position_z = 68;
}

void eff77_0101(WORK_Other* ewk) {
    char_move(&ewk->wu);
    if (ewk->wu.cg_type) {
        ewk->wu.routine_no[1]++;
        ewk->wu.mvxy.a[0].sp = 0x68000;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.mvxy.a[1].sp = 0x88000;
        ewk->wu.mvxy.d[1].sp = 0x1200;
        ewk->wu.old_rno[2] = 24;
    }
}

void eff77_0102(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    add_x_sub(ewk);
    add_y_sub(ewk);
    char_move(&ewk->wu);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 32;
        ewk->wu.old_rno[0] = plw[mwk->master_id].wu.position_x;
        ewk->wu.old_rno[1] = 40;
    }
}

void eff77_0103(WORK_Other* ewk) {
    WORK_Other* mwk = (WORK_Other*)ewk->my_master;
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.old_rno[2] = 40;
        ewk->wu.rl_flag = plw[mwk->master_id].wu.rl_flag;
        if (ewk->wu.rl_flag) {
            ewk->wu.xyz[0].disp.pos = plw[mwk->master_id].wu.xyz[0].disp.pos - 144;
        } else {
            ewk->wu.xyz[0].disp.pos = plw[mwk->master_id].wu.xyz[0].disp.pos + 144;
        }
        cal_all_speed_data(&ewk->wu, ewk->wu.old_rno[2], ewk->wu.old_rno[0], ewk->wu.old_rno[1], 1, 1);
        set_char_move_init(&ewk->wu, 0, 3);
    }
}

void eff77_0104(WORK_Other* ewk) {
    add_mvxy_speed_no_use_rl(&ewk->wu);
    cal_mvxy_speed(&ewk->wu);
    ewk->wu.old_rno[2]--;
    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.routine_no[1]++;
    }
}

void eff77_0105(WORK_Other* ewk) {
    WORK_Other* mwk;
    char_move(&ewk->wu);
    if (ewk->wu.cg_type == 255) {
        mwk = (WORK_Other*)ewk->my_master;
        if (plw[mwk->master_id].wu.pat_status == 38) {
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 5);
        }
    }
}

void eff77_0106(WORK_Other* ewk) {
    char_move(&ewk->wu);
}

void eff77_area1(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_INIT:
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, 4);
        ewk->wu.xyz[0].disp.pos = 320;
        ewk->wu.xyz[1].disp.pos = 52;
        ewk->wu.my_priority = ewk->wu.position_z = 70;
        break;
    case R0_MOVE:
        char_move(&ewk->wu);
        disp_pos_trans_entry_r(ewk);
        break;
    default:
        break;
    }
}

s32 effect_77_init(WORK_Other* mwk) {
    WORK_Other* ewk;
    s16* rno;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->my_master = (u32*)mwk;
    ewk->wu.be_flag = 1;
    ewk->wu.id = 77;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.sync_suzi = 0;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2051;
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 320;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 52;
    *ewk->wu.char_table = eff77_char_table;
    ewk->wu.my_priority = ewk->wu.position_z = 70;
    rno = ewk->wu.routine_no;
    rno[1] = rno[2] = 0;
    rno[0] = 0;
    suzi_offset_set(&ewk->wu);
    effect_78_init(ewk);
    effect_79_init(ewk);
    effect_80_init(ewk);
    return 0;
}
