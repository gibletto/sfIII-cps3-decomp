/*
 * EFFF7.C  Effect F7: the six sprites of the opening
 *
 * effect_F6_init makes the counter of effect F6 and effect_F7_init makes six sprites with it as the
 * master, old_rno[0] = 0-5. effect_F7_move runs each sprite's routine from the local effF7_jp
 * table: sprites 0 and 1 have their own scenes, 2-3 and 4-5 share one. Each step of the master's
 * routine_no[0] restarts the sprite (routine_no[1] = 0) and moves it from its effF7_pos_tbl
 * position for that step to the next one over old_rno[1] frames (cal_all_speed_data); some steps
 * show other patterns or free the sprite. Sprites 0 and 1 stop (routine_no[1] 2) once the master
 * sets old_rno[3].
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "ta_sub.h"
#include "CALDIR.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "efff7.h"

/* routine_no[2] */
#define R2_INIT         0       /* start the animation */
#define R2_MOVE         1       /* run the sprite's routine */

/* routine_no[1]: the sprite's state within a step */
#define R1_INIT         0       /* set up for the master's new step */
#define R1_MOVE         1       /* play the step */
#define R1_KILL         2       /* put the work back */

/* x, y of each sprite at each step of the master */
extern const s16 effF7_pos_tbl[23][6][2];



/* one of six opening sprites */
void effect_F7_move(WORK_Other* ewk) {
    void (*effF7_jp[6])(WORK_Other*) = { effF7_0000, effF7_0001, effF7_0002, effF7_0002, effF7_0003, effF7_0003 };
    switch (ewk->wu.routine_no[2]) {
    case R2_INIT:
        ewk->wu.routine_no[2]++;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;
    case R2_MOVE:
        effF7_jp[ewk->wu.old_rno[0]](ewk);
        break;
    }
}



/* provisional name */
void effF7_0000(WORK_Other* ewk) {
    WORK_Other* mwk;
    mwk = (WORK_Other*)ewk->my_master;
    if (mwk->wu.old_rno[3] && ewk->wu.routine_no[1] != R1_KILL) {
        ewk->wu.routine_no[1] = R1_KILL;
    } else if (ewk->wu.routine_no[0] != mwk->wu.routine_no[0]) {
        ewk->wu.routine_no[1] = R1_INIT;
        ewk->wu.routine_no[0] = mwk->wu.routine_no[0];
    }
    switch (mwk->wu.routine_no[0]) {
    case 16:
    case 17:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 63);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 48;
            /* fall through */
        case R1_MOVE:
            char_move(&ewk->wu);
            sort_push_request4(&ewk->wu);
            break;
        }
        break;
    case 18:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 53);
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            /* fall through */
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        }
        break;
    default:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            break;
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        case R1_KILL:
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    }
}



/* provisional name */
void effF7_0001(WORK_Other* ewk) {
    WORK_Other* mwk;
    mwk = (WORK_Other*)ewk->my_master;
    if (mwk->wu.old_rno[3] && ewk->wu.routine_no[1] != R1_KILL) {
        ewk->wu.routine_no[1] = R1_KILL;
    } else if (ewk->wu.routine_no[0] != mwk->wu.routine_no[0]) {
        ewk->wu.routine_no[1] = R1_INIT;
        ewk->wu.routine_no[0] = mwk->wu.routine_no[0];
    }
    switch (mwk->wu.routine_no[0]) {
    case 0:
        break;
    case 11:
    case 12:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 64);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos = 0x200;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos = 48;
            /* fall through */
        case R1_MOVE:
            char_move(&ewk->wu);
            sort_push_request4(&ewk->wu);
            break;
        }
        break;
    case 13:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            set_char_move_init(&ewk->wu, 0, 53);
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            /* fall through */
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        }
        break;
    default:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            break;
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        case R1_KILL:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    }
}



/* provisional name */
void effF7_0002(WORK_Other* ewk) {
    WORK_Other* mwk;
    mwk = (WORK_Other*)ewk->my_master;
    if (ewk->wu.routine_no[0] != mwk->wu.routine_no[0]) {
        ewk->wu.routine_no[1] = R1_INIT;
        ewk->wu.routine_no[0] = mwk->wu.routine_no[0];
    }
    switch (mwk->wu.routine_no[0]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    default:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            break;
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        default:
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
            break;
        }
        break;
    case 16:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* provisional name */
void effF7_0003(WORK_Other* ewk) {
    WORK_Other* mwk;
    mwk = (WORK_Other*)ewk->my_master;
    if (ewk->wu.routine_no[0] != mwk->wu.routine_no[0]) {
        ewk->wu.routine_no[1] = R1_INIT;
        ewk->wu.routine_no[0] = mwk->wu.routine_no[0];
    }
    switch (mwk->wu.routine_no[0]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        break;
    default:
        switch (ewk->wu.routine_no[1]) {
        case R1_INIT:
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 1;
            ewk->wu.xyz[0].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][0];
            ewk->wu.xyz[1].disp.pos = effF7_pos_tbl[mwk->wu.routine_no[0]][ewk->wu.old_rno[0]][1];
            cal_all_speed_data(&ewk->wu, mwk->wu.old_rno[1], effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][0],
                               effF7_pos_tbl[mwk->wu.routine_no[0] + 1][ewk->wu.old_rno[0]][1], 1, 1);
            break;
        case R1_MOVE:
            char_move(&ewk->wu);
            add_x_sub(ewk);
            add_y_sub(ewk);
            ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
            ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
            sort_push_request4(&ewk->wu);
            break;
        }
        break;
    case 20:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



/* six sprites under the master oya */
s32 effect_F7_init(WORK_Other* oya) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    for (i = 0; i < 6; i++) {
        if ((ix = pull_effect_work(3)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.id = 157;
        ewk->wu.be_flag = 1;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->my_master = (u32*)oya;
        ewk->wu.my_family = 2;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 64;
        ewk->wu.char_table[0] = etc_char_table;
        ewk->wu.old_rno[0] = i;
        ewk->wu.my_priority = ewk->wu.position_z = 50;
        ewk->wu.char_index = 53;
    }
    (void)&((WORK*)etc_char_table)->id;
    return 0;
}
