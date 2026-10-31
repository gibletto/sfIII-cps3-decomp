/*
 * EFF59.C  Effect 59: country name letters
 *
 * effect_59_init lays out the letters of the Battle_Country name from eff59_name_tbl, one effect 59 per
 * letter, each starting a frame after the one before; effect_59_move waits that delay, opens the
 * letter horizontally, waits 40 frames and sets bg_w.stage to Battle_Country (area 0),
 * closes it and, unless Break_Into, sets Next_Step from the first letter until Suicide.
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
#include "color3rd.h"
#include "ta_sub.h"
#include "bg_sub_5.h"
#include "Eff59.h"

/* routine_no[0] */
#define R0_WAIT         0       /* count the start delay down */
#define R0_OPEN         1       /* widen the letter */
#define R0_HOLD         2       /* hold, then set the stage */
#define R0_CLOSE        3       /* narrow the letter away */
#define R0_NEXT         4       /* wait out a break-in, then go on */
#define R0_DONE         5       /* ask for the next step until told to die */
#define R0_KILL         6       /* (default) put the work back */

/* eff59_country_tbl columns */
#define COUNTRY_NAME    0       /* row of eff59_name_tbl */
#define COUNTRY_LEN     1       /* number of letters */

extern const u8 eff59_country_tbl[13][2];
extern const s16 eff59_name_x_tbl[10];
extern const u8 eff59_name_tbl[10][39];

void effect_59_move(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[0]) {
    case R0_WAIT:
        if (--ewk->wu.dir_timer) {
            return;
        }
        ewk->wu.routine_no[0]++;
        ewk->wu.disp_flag = 1;
        set_char_move_init2(&ewk->wu, 0, ewk->wu.char_index, ewk->wu.dir_step + 1, 0);
        break;
    case R0_OPEN:
        if ((ewk->wu.my_mr.size.x += 6) >= 63) {
            ewk->wu.routine_no[0]++;
            ewk->wu.dir_timer = 40;
            ewk->wu.my_mr.size.x = 63;
        }
        break;
    case R0_HOLD:
        if (Break_Into) {
            break;
        }
        if (--ewk->wu.dir_timer == 0) {
            ewk->wu.routine_no[0]++;
            bg_w.stage = Battle_Country;
            bg_w.area = 0;
        }
        break;
    case R0_CLOSE:
        if ((ewk->wu.my_mr.size.x -= 6) < 0) {
            ewk->wu.routine_no[0]++;
            ewk->wu.disp_flag = 0;
            ewk->wu.my_mr.size.x = 0;
        }
        break;
    case R0_NEXT:
        if (Break_Into) {
            break;
        }
        ewk->wu.routine_no[0]++;
        if (ewk->master_id) {
            Next_Step = 1;
        }
        break;
    case R0_DONE:
        if (ewk->master_id) {
            Next_Step = 1;
        }
        if (Suicide == 1) {
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


/* Create one effect 59 letter for each character of the Battle_Country name. */
s32 effect_59_init(s16 timer) {
    WORK_Other* ewk;
    s16 ix;
    s16 i;
    s16 x;
    u16 no;
    u16 num;
    s32 n;
    const u8* name;
    const u8* p;
    no = eff59_country_tbl[Battle_Country][COUNTRY_NAME];
    num = eff59_country_tbl[Battle_Country][COUNTRY_LEN];
    x = eff59_name_x_tbl[no];
    n = num * 2;
    i = 0;
    name = eff59_name_tbl[no];
    for (; i < n; i += 2) {
        if (name[i] == 27) {
            x += 8;
        } else {
            if ((ix = pull_effect_work(4)) == -1) {
                return -1;
            }
            ewk = (WORK_Other*)frw[ix];
            ewk->wu.be_flag = 1;
            ewk->wu.id = 59;
            ewk->wu.work_id = 16;
            ewk->wu.cgromtype = 1;
            ewk->wu.rl_flag = 0;
            ewk->wu.my_col_mode = 0x4200;
            ewk->wu.my_col_code = 0x207C;
            ewk->wu.my_family = 3;
            ewk->wu.my_priority = 68;
            ewk->wu.position_z = 68;
            ewk->wu.xyz[0].disp.pos = DE_X[5] / 2 + x;
            ewk->wu.xyz[1].disp.pos = 67;
            ewk->wu.dir_timer = timer;
            ewk->wu.char_index = 4;
            p = &eff59_name_tbl[no][i];
            ewk->wu.dir_step = p[0];
            x += p[1];
            ewk->wu.char_table[0] = sel_pl_char_table;
            if (i == 0) {
                ewk->master_id = 1;
            } else {
                ewk->master_id = 0;
            }
            timer++;
            ewk->wu.my_mr_flag = 1;
            ewk->wu.my_mr.size.y = 63;
            ewk->wu.my_mr.size.x = 0;
        }
    }
    load_any_color(7);
    return 0;
}
