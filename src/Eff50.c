/*
 * EFF50.C  Effect 50: the opponent candidate panels
 *
 * effect_50_init(player) (from sel_pl.c) makes six panels in two rows of three for the player's
 * opponent course (EM_Candidate_Data by character and EM_Course): the character's face where
 * Break_Com marks it, a blank panel otherwise. They slide in from the side, staggered unless the cut
 * button is held, and flash (Flash_Violent). Once Exit_No reaches 4 the panel at the player's
 * VS_Index turns over to show the next opponent and then lets the others slide out (eff50_slide_out).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "aboutspr.h"
#include "CHARMOVE.h"
#include "SYS_sub.h"
#include "Eff50.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the delay down, then show */
#define R0_IN_LEFT      1       /* slide in to the left */
#define R0_IN_RIGHT     2       /* slide in to the right */
#define R0_LAND         3       /* in place, step on */
#define R0_FLASH        4       /* colour flash */
#define R0_READY        5       /* wait for the opponent to be decided */
#define R0_NARROW       6       /* turn over: narrow to nothing */
#define R0_WIDEN        7       /* turn back with the next opponent */
#define R0_PAUSE        8       /* pause, then let the others go */
#define R0_SLIDE_OUT    9       /* slide out when told */
#define R0_KILL         10      /* (default) put the work back */

#define EFF50_PANEL_COUNT 6

extern u16 EM_Course[2];
extern u8 eff50_slide_out;
s32 Flash_Violent();

void effect_50_move(WORK_Other* ewk) {
    u16 cut;
    s32 slide;
    cut = Cut_Cut_Sub(3);
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer) {
            return;
        }
        if (ewk->wu.mvxy.a[0].sp < 0) {
            ewk->wu.routine_no[0] = R0_IN_LEFT;
        } else {
            ewk->wu.routine_no[0] = R0_IN_RIGHT;
        }
        ewk->wu.disp_flag = 1;
        ewk->wu.dir_timer = 5;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R0_IN_LEFT:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp * cut;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp * cut;
        if (ewk->wu.hit_quake >= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0] = R0_LAND;
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
        }
        break;
    case R0_IN_RIGHT:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp += ewk->wu.mvxy.d[0].sp;
        if (ewk->wu.hit_quake <= ewk->wu.xyz[0].disp.pos) {
            ewk->wu.routine_no[0]++;
            ewk->wu.xyz[0].disp.pos = ewk->wu.hit_quake;
        }
        break;
    case R0_LAND:
        if (--ewk->wu.dir_timer) {
            ewk->wu.routine_no[0]++;
        }
        break;
    case R0_FLASH:
        if (Flash_Violent(ewk, 1)) {
            ewk->wu.routine_no[0]++;
        }
        if (ewk->wu.vitality) {
            set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        }
        break;
    case R0_READY:
        if (Exit_No < 4) {
            break;
        }
        if (VS_Index[Player_id] != ewk->master_id) {
            ewk->wu.routine_no[0] = R0_SLIDE_OUT;
            break;
        }
        ewk->wu.routine_no[0]++;
        break;
    case R0_NARROW:
        if ((ewk->wu.my_mr.size.x -= 6) > 0) {
            break;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.my_mr.size.x = 0;
        ewk->wu.dir_step = EM_Candidate_Data[My_char[Player_id]][(s8)EM_Course[Player_id]][VS_Index[Player_id]] + 28;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R0_WIDEN:
        if ((ewk->wu.my_mr.size.x += 6) < 63) {
            break;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.dir_timer = 2;
        ewk->wu.my_mr.size.x = 63;
        break;
    case R0_PAUSE:
        if (--ewk->wu.dir_timer) {
            break;
        }
        ewk->wu.routine_no[0]++;
        eff50_slide_out = 1;
        break;
    case R0_SLIDE_OUT:
        if (!(slide = eff50_slide_out)) {
            break;
        }
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        if (Ck_Range_Out_S(ewk, 2, 32)) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
        }
        break;
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        return;
    }
    ewk->wu.position_x = ewk->wu.xyz[0].disp.pos & 0x3FF;
    ewk->wu.position_y = ewk->wu.xyz[1].disp.pos & 0x3FF;
    sort_push_request4(&ewk->wu);
}

s32 effect_50_init(s16 player) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    s16 j;
    s16 x;
    s16 dx;
    s16 delay;
    s16 extra;
    s16 col;
    s16 chars[EFF50_PANEL_COUNT];
    const s8* data;
    s32 speed;
    s32 accel;
    eff50_slide_out = 0;
    if (COM_id) {
        x = DE_X[10] + 1008;
        speed = -0x140000;
        accel = -0x8000;
        dx = -256;
    } else {
        x = 304;
        speed = 0x140000;
        accel = 0x8000;
        dx = 256;
    }
    data = EM_Candidate_Data[My_char[Player_id]][(s8)EM_Course[Player_id]];
    for (j = 0; j < EFF50_PANEL_COUNT; j++) {
        if (Break_Com[Player_id][data[j]]) {
            chars[j] = data[j] + 42;
        } else {
            chars[j] = 57;
        }
    }
    (void)&((WORK*)EFF50_PANEL_COUNT)->be_flag;
    (void)&((WORK*)Break_Com)->be_flag;
    delay = 1;
    if (Cut_Cut_Cut()) {
        extra = 0;
    } else {
        extra = 2;
    }
    for (i = 0; i < EFF50_PANEL_COUNT; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }
        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 50;
        ewk->wu.work_id = 16;
        ewk->wu.cgromtype = 1;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.my_col_code = 0x2040;
        ewk->wu.my_family = 3;
        ewk->wu.position_z = 78;
        ewk->wu.hit_quake = (ewk->wu.xyz[0].disp.pos = x) + dx;
        ewk->wu.dir_timer = delay;
        ewk->wu.char_index = 0;
        ewk->wu.dir_step = chars[i];
        *ewk->wu.char_table = sel_pl_char_table;
        ewk->master_id = i;
        ewk->wu.mvxy.a[0].sp = speed;
        ewk->wu.mvxy.d[0].sp = accel;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        ewk->wu.routine_no[2] = 1;
        ewk->wu.routine_no[3] = 2;
        ewk->wu.routine_no[4] = 6;
        ewk->wu.vitality = 0;
        if (chars[i] == 57) {
            col = 14;
        } else {
            col = 38;
        }
        ewk->wu.vital_new = 0x2065 - col;
        ewk->wu.vital_old = 0x2040;
        if (i < 3) {
            ewk->wu.xyz[1].disp.pos = 136;
        } else {
            ewk->wu.xyz[1].disp.pos = 88;
        }
        delay += extra;
        if (i != 2) {
            x += 44;
        } else {
            if (COM_id) {
                x = DE_X[10] + 1008;
            } else {
                x = 304;
            }
        }
    }
    return 0;
}
