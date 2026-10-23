/*
 * EFF43.C  Effect 43: a VS-screen object that slides in from one side
 *
 * effect_43_init(Side, Time) makes one per side (pattern 50 + Side of sel_pl_char_table), drawn at
 * double size. After Time frames effect_43_move shows it, slides it toward DE_X[10] + 0x2C0 while it
 * shrinks to normal size (both at the Cut_Cut_Sub speed), and counts down vs_object_count. When every
 * object has arrived it plays its pattern; the second side then waits 25 frames and lets a button
 * set Sel_Exit_Flag.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "ta_sub.h"
#include "aboutspr.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "SYS_sub.h"
#include "se_3.h"
#include "EFF43.h"

extern s8 vs_object_count;  /* provisional name (02012E75): objects of the VS screen still moving in */

void effect_43_slide();



void effect_43_move(WORK_Other* ewk) {
    u16 speed = Cut_Cut_Sub(3);
    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (--ewk->wu.dir_timer != 0) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_old + 1, 0);
        if (ewk->master_id == 0) {
            Sound_SE(104);
        }
        break;
    case 1:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 2:
        for (;;) {
            effect_43_slide(ewk, speed);
            break;
        }
        if ((ewk->wu.my_mr.size.x -= *(s16*)&ewk->wu.mvxy.a[0] * speed) <= 63) {
            ewk->wu.my_mr.size.x = 63;
        }
        if ((ewk->wu.my_mr.size.y -= *(s16*)&ewk->wu.mvxy.a[0] * speed) <= 63) {
            ewk->wu.my_mr.size.y = 63;
        }
        if (ewk->wu.my_mr.size.x <= 63 && ewk->wu.my_mr.size.y <= 63) {
            ewk->wu.routine_no[0]++;
            vs_object_count--;
            if (ewk->wu.dir_old) {
                Next_Step = 1;
            }
        }
        break;
    case 3:
        if (vs_object_count == 0) {
            char_move(&ewk->wu);
            if (ewk->wu.extra_col == 0x2066) {
                ewk->wu.routine_no[0]++;
                if (ewk->master_id == 0) {
                    Sound_SE(114);
                }
            }
        }
        break;
    case 4:
        if (ewk->master_id) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 25;
        }
        break;
    case 5:
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case 6:
        if (Cut_Cut_Cut()) {
            Sel_Exit_Flag = 1;
        }
        break;
    default:
        all_cgps_put_back(ewk);
        push_effect_work((WORK*)ewk);
        break;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request(&ewk->wu);
}



/* provisional name */
/* moves it by speed steps until it reaches its stop point */
void effect_43_slide(ewk, speed)
WORK_Other* ewk;
u16 speed;
{
    ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[1].sp * speed;
    if (ewk->wu.mvxy.a[1].sp < 0) {
        if (ewk->wu.xyz[0].disp.pos <= DE_X[10] + 0x2C0) {
            ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2C0;
        }
    } else if (ewk->wu.xyz[0].disp.pos >= DE_X[10] + 0x2C0) {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2C0;
    }
}



/* from the left or right side */
s32 effect_43_init(s16 Side, s16 Time) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 43;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_family = 3;
    ewk->wu.dir_timer = Time;
    ewk->wu.char_table[0] = sel_pl_char_table;
    ewk->wu.char_index = Side + 50;
    ewk->wu.dir_old = 0;
    ewk->master_id = Side;
    ewk->wu.position_z = 74 - Side;
    ewk->wu.my_mr_flag = 1;
    ewk->wu.my_mr.size.x = 127;
    ewk->wu.my_mr.size.y = 127;
    if (Side) {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2E0;
        ewk->wu.mvxy.a[1].sp = -0x60000;
    } else {
        ewk->wu.xyz[0].disp.pos = DE_X[10] + 0x2A0;
        ewk->wu.mvxy.a[1].sp = 0x60000;
    }
    ewk->wu.xyz[1].disp.pos = 24;
    ewk->wu.mvxy.a[0].sp = 0xC0000;
    return 0;
}
