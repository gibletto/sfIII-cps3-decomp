/*
 * EFFD6.C  Effect D6: select-screen plate driven by the scene orders
 *
 * effect_D6_init(n) (from sel_pl.c) makes plate n (sel_pl_char_table, pattern n + 1) at its height in
 * Pos_Data_D6; plate n follows Order[n]. EFFD6_WAIT waits for an order; after Order_Timer runs out,
 * EFFD6_RISE_IN raises the plate into place, EFFD6_SLIDE_IN brings it in from the side Order_Dir
 * gives, EFFD6_SLIDE_OUT takes it off the screen and frees it, EFFD6_ZOOM_SLIDE shrinks it as it
 * slides across, hands over to the plate on the other side (order 5) and frees it, and EFFD6_RESET
 * puts it straight at its side's spot. A plate clears its order when it is done.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "SYS_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "EFFD6.h"

/* routine_no[0]: index of EFFD6_Jmp_Tbl, set from Order */
#define R0_WAIT         0       /* wait for an order */

/* routine_no[1], EFFD6_RISE_IN (R1_DELAY in all four) */
#define R1_DELAY        0       /* wait for the order timer */
#define R1_RISE         1       /* (default) rise into place */

/* routine_no[1], EFFD6_SLIDE_IN */
#define R1_SLIDE        1       /* (default) slide in to the spot */

/* routine_no[1], EFFD6_SLIDE_OUT */
#define R1_OUT          1       /* slide off the screen */
#define R1_KILL         2       /* (default) put the work back */

/* routine_no[1], EFFD6_ZOOM_SLIDE */
#define R1_ZOOM         1       /* (default) shrink and slide across */

const s16 Pos_Data_D6[6] = { 288, 200, 200, 176, 192, 192 };

void (*const EFFD6_Jmp_Tbl[6])() = {
    EFFD6_WAIT,
    EFFD6_RISE_IN,
    EFFD6_SLIDE_IN,
    EFFD6_SLIDE_OUT,
    EFFD6_ZOOM_SLIDE,
    EFFD6_RESET,
};



void effect_D6_move(WORK_Other* ewk) {
    EFFD6_Jmp_Tbl[ewk->wu.routine_no[0]](ewk);
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}



void EFFD6_WAIT(WORK_Other* ewk) {
    if ((ewk->wu.routine_no[0] = Order[ewk->wu.dir_step])) {
        ewk->wu.routine_no[1] = R1_DELAY;
    }
}



void EFFD6_RISE_IN(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_DELAY:
        if (--Order_Timer[ewk->wu.dir_step]) {
            break;
        }
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2C0;
        ewk->wu.mvxy.a[1].sp = -0x100000;
        ewk->wu.hit_quake = 184;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
        break;
    default:
        ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;
        if (ewk->wu.hit_quake >= ewk->wu.xyz[1].disp.pos) {
            Order[ewk->wu.dir_step] = R0_WAIT;
            ewk->wu.routine_no[0] = R0_WAIT;
            ewk->wu.xyz[1].disp.pos = ewk->wu.hit_quake;
        }
        break;
    }
}



void EFFD6_SLIDE_IN(WORK_Other* ewk) {
    s16 ofs;
    switch (ewk->wu.routine_no[1]) {
    case R1_DELAY:
        if (--Order_Timer[ewk->wu.dir_step]) {
            break;
        }
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.position_z = 69;
        if (ewk->wu.dir_step == 3) {
            ofs = 16;
        } else {
            ofs = 0;
        }
        if (Order_Dir[ewk->wu.dir_step] == 4) {
            ewk->wu.xyz[0].disp.pos = DE_X[5] + 0x3C0;
            ewk->wu.mvxy.a[0].sp = -0x100000;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.hit_quake = DE_X[10] + 0x320;
        } else {
            ewk->wu.xyz[0].disp.pos = 0x1C0;
            ewk->wu.mvxy.a[0].sp = 0x100000;
            ewk->wu.mvxy.d[0].sp = 0x8000;
            ewk->wu.hit_quake = 0x260;
        }
        if (ewk->wu.dir_step == 0 || ewk->wu.dir_step == 3) {
            ewk->wu.hit_quake = DE_X[10] + ofs + 0x2C0;
        }
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
        break;
    default:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (0 < ewk->wu.mvxy.a[0].sp) {
            if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
                if (Order[ewk->wu.dir_step] == ewk->wu.routine_no[0]) {
                    Order[ewk->wu.dir_step] = R0_WAIT;
                }
                ewk->wu.routine_no[0] = R0_WAIT;
                ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
                ewk->wu.position_z = 70;
            }
        } else if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            if (Order[ewk->wu.dir_step] == ewk->wu.routine_no[0]) {
                Order[ewk->wu.dir_step] = R0_WAIT;
            }
            ewk->wu.routine_no[0] = R0_WAIT;
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
            ewk->wu.position_z = 70;
        }
        break;
    }
}



void EFFD6_SLIDE_OUT(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_DELAY:
        if (--Order_Timer[ewk->wu.dir_step]) {
            break;
        }
        ewk->wu.routine_no[1]++;
        if (Order_Dir[ewk->wu.dir_step] == 4) {
            ewk->wu.mvxy.a[0].sp = -0x100000;
            ewk->wu.mvxy.d[0].sp = -0x8000;
        } else {
            ewk->wu.mvxy.a[0].sp = 0x100000;
            ewk->wu.mvxy.d[0].sp = 0x8000;
        }
        break;
    case R1_OUT:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (Ck_Range_Out_S(ewk, 2, 128)) {
            ewk->wu.routine_no[1]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



void EFFD6_ZOOM_SLIDE(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case R1_DELAY:
        if (--Order_Timer[ewk->wu.dir_step]) {
            break;
        }
        ewk->wu.routine_no[1]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        ewk->wu.mvxy.a[1].sp = 0x40000;
        ewk->wu.dir_timer = ewk->wu.xyz[1].disp.pos + 16;
        if (Order_Dir[ewk->wu.dir_step] == 4) {
            ewk->wu.mvxy.a[0].sp = -0x100000;
            ewk->wu.mvxy.d[0].sp = -0x8000;
            ewk->wu.hit_quake = 0x260;
        } else {
            ewk->wu.mvxy.a[0].sp = 0x100000;
            ewk->wu.mvxy.d[0].sp = 0x8000;
            ewk->wu.hit_quake = DE_X[10] + 0x320;
        }
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
        break;
    default:
        if ((ewk->wu.my_mr.size.x -= 4) <= 44) {
            ewk->wu.my_mr.size.x = 44;
        }
        if ((ewk->wu.my_mr.size.y -= 4) <= 44) {
            ewk->wu.my_mr.size.y = 44;
        }
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;
        if (ewk->wu.dir_timer <= ewk->wu.xyz[1].disp.pos) {
            ewk->wu.xyz[1].disp.pos = ewk->wu.dir_timer;
        }
        if (0 < ewk->wu.mvxy.a[0].sp) {
            if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
                if (ewk->wu.dir_step == 0) {
                    Order[2] = 5;
                } else {
                    Order[5] = 5;
                }
                ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
                all_cgps_put_back(&ewk->wu);
                push_effect_work(&ewk->wu);
            }
        } else if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            if (ewk->wu.dir_step == 0) {
                Order[1] = 5;
            } else {
                Order[4] = 5;
            }
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
            all_cgps_put_back(&ewk->wu);
            push_effect_work(&ewk->wu);
        }
        break;
    }
}



void EFFD6_RESET(WORK_Other* ewk) {
    if (ewk->wu.dir_step == 5 || ewk->wu.dir_step == 2) {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x320;
    } else {
        ewk->wu.xyz[0].disp.pos = 0x260;
    }
    ewk->wu.disp_flag = 1;
    Order[ewk->wu.dir_step] = R0_WAIT;
    ewk->wu.routine_no[0] = R0_WAIT;
    set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
}



s32 effect_D6_init(s16 dir_old) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 136;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = 0x2040;
    ewk->wu.my_family = 3;
    *ewk->wu.char_table = sel_pl_char_table;
    ewk->wu.char_index = 12;
    ewk->wu.dir_old = dir_old;
    ewk->wu.xyz[1].disp.pos = Pos_Data_D6[dir_old];
    ewk->wu.position_z = 70;
    ewk->wu.dir_step = dir_old;
}
