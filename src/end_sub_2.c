/*
 * END_SUB_2.C  CD keep-alive checks and the staff roll
 *
 * Routines: cd_keep_spinning_tick, cd_selftest_periodic, cd_error_fatal_hang, staff_roll_skip_check,
 * staff_roll_put, staff_roll_main.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "Com_Pl.h"
#include "SYS_sub.h"
#include "VITAL.h"
#include "count.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFFH3.h"
#include "effh4.h"
#include "effh5.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "Manage.h"
#include "manage_2.h"
#include "EFFM7.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "HITCHECK.h"
#include "cmb_cont.h"
#include "SLOWF.h"
#include "Entry.h"
#include "entry_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "fifo.h"
#include "ta_sub2.h"
#include "tate00.h"
#include "ta_sub.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "cps3.h"

s16 cd_ready_flag;  /* 02028284 */
s16 cd_spin_timer;  /* 02028286 */
s16 roll_rate2;  /* 0201D734 */
s16 roll_stop;  /* 0201D736 */


/* provisional name */
s32 staff_roll_speed[10] = { 0, 0x10000, 0x20000, 0x30000, 0x40000, 0x50000, 0x60000, 0x70000, 0x80000, 0x90000 };
static s16 staff_name_ptr = 0;  /* 020067C0 */
static s32 staffroll_end = 0;  /* 020067C4 */
/* provisional name */
u32 staff_roll_cnt = 0;  /* 020067C8 */

/* provisional name */
extern const STAFF_LINE staff_roll_last[4];


s32 effect_H6_init(s16 timer, s8* str, s16 X, s16 Y, s16 Original_Color, s32 unused);

extern s32 staff_r_no;

#pragma inline(card_pl_work_clear)



/* provisional name */
void cd_keep_spinning_tick(void) {
    if (cd_ready_flag) {
        if (!cd_spin_timer) {
            scsi_start_stop_unit(1, 1);
            cd_spin_timer = 0x258;
        }
        cd_spin_timer--;
    }
}



/* provisional name */
void cd_selftest_periodic(void) {
    if (cd_ready_flag) {
        _builtin_set_imask(15);
        if (cd_check_drive_inquiry() != 0) {
            cd_error_fatal_hang(0);
        }
        if (cd_check_disc_id() != 0) {
            cd_error_fatal_hang(1);
        }
        _builtin_set_imask(1);
    }
}



/* provisional name */
void cd_error_fatal_hang(s32 kind) {
    coin_lock_set(-1);
    set_screen_mode(3);
    Scr_all_clear_Wait();
    coin_work_init();
    Cd_Error_Flag = 1;
    palette_bank_set(0);
    palette_write(0, sys_palette, 0x100);
    tilemap_chunk_copy_16b((s16*)(SS_RAM + 0x8000), (char*)sys_font_cg, 0x8C);
    clear_scroll_layer_state_and_mask();
    sound_driver_init();
    kill_tasks_by_priority(3, 1);
    switch (kind) {
    case 0:
        tilemap_print_string_attr(18, 16, 18, no_cd_drive_mes);
        break;
    case 1:
        tilemap_print_string_attr(21, 16, 18, no_cd_rom_mes);
        break;
    }
    while (1) {
    }
}



/* provisional name */
s32 staff_roll_skip_check(void) {
    u16 v;
    if (!end_no_cut) {
        if (WINNER) {
            v = p2sw_0;
        } else {
            v = p1sw_0;
        }
        if (v & 0x7F0) {
            return 1;
        }
    }
    return 0;
}



/* provisional name */
void staff_roll_put(x, y, a, b)
s32 x;
s32 y;
s32 a;
s8* b;
{
    s8* su;
    s16 xu;
    s16 yu;
    su = b;
    xu = x;
    yu = y;
    xu += bg_w.bgw[5].xy[0].disp.pos - 192;
    yu += bg_w.bgw[5].position_y;
    effect_H6_init(0, su, xu, yu, a, -1);
}




/* provisional name */
s32 staff_roll_main(flag)
s16 flag;
{
    s32 fx;
    s32 fy;
    s32 i;
    s16 x;
    s16 y;
    s16 attr;
    switch (staff_r_no) {
    case 0:
        staffroll_end = 0;
        bg_w.bgw[5].wxy[0].cal = bg_w.bgw[5].xy[0].cal = 0x2000000;
        bg_w.bgw[5].xy[1].cal = 0;
        bg_w.bgw[5].position_x = 0x200 - bg_w.pos_offset;
        bg_w.bgw[5].position_y = 0;
        fx = bg_w.bgw[5].position_x;
        fy = bg_w.bgw[5].position_y;
        fx = -fx & 0x3FF;
        fy = (0x300 - (fy & 0x3FF)) & 0x3FF;
        Family_Set_R(6, fx, fy);
        load_any_color(0x93);
        load_any_color(0x94);
        load_char_gfx(0x6410, 1);
        load_char_gfx(0x76B8, 1);
        roll_rate2 = 1;
        roll_stop = 0;
        staff_name_ptr = 0;
        end_w.timer = 0;
        staff_roll_cnt = 0;
        if (!flag) {
            staff_r_no++;
        } else {
            staff_r_no = 2;
            end_w.timer = 4;
        }
        break;
    case 1:
        if (staff_roll_skip_check()) {
            roll_rate2 = 8;
        } else {
            roll_rate2 = 1;
        }
        for (i = 0; i < roll_rate2; i++) {
            bg_w.bgw[5].xy[1].cal -= staff_roll_speed[1];
            staff_roll_cnt += staff_roll_speed[1];
            bg_w.bgw[5].position_x = (bg_w.bgw[5].xy[0].disp.pos & 0x3FF) - bg_w.pos_offset;
            bg_w.bgw[5].position_y = bg_w.bgw[5].xy[1].disp.pos & 0x3FF;
            fx = bg_w.bgw[5].position_x;
            fy = bg_w.bgw[5].position_y;
            fx = -fx & 0x3FF;
            fy = (0x300 - (fy & 0x3FF)) & 0x3FF;
            Family_Set_W(6, fx, fy);
            if ((staff_roll_cnt >> 16) >= end_w.timer) {
                staff_roll_cnt = 0;
                if (staff_roll_tbl[staff_name_ptr].str == 0) {
                    staff_r_no = 3;
                    end_w.timer = staff_roll_tbl[staff_name_ptr].wait;
                    roll_stop = 1;
                } else {
                    x = staff_roll_tbl[staff_name_ptr].x;
                    y = staff_roll_tbl[staff_name_ptr].y;
                    attr = staff_roll_tbl[staff_name_ptr].attr;
                    staff_roll_put(x, y, attr, staff_roll_tbl[staff_name_ptr].str);
                    end_w.timer = staff_roll_tbl[staff_name_ptr].wait;
                    staff_name_ptr++;
                }
            }
        }
        break;
    case 2:
        if (end_w.timer > 0) {
            end_w.timer--;
            break;
        }
        while (staff_roll_last[staff_name_ptr].str != 0) {
            x = staff_roll_last[staff_name_ptr].x;
            y = staff_roll_last[staff_name_ptr].y;
            attr = staff_roll_last[staff_name_ptr].attr;
            staff_roll_put(x, y, attr, staff_roll_last[staff_name_ptr].str);
            staff_name_ptr++;
        }
        end_w.timer = staff_roll_last[staff_name_ptr].wait;
        staff_r_no++;
        break;
    case 3:
        for (i = 0; i < roll_rate2; i++) {
            if (end_w.timer > 0) {
                end_w.timer--;
            } else {
                staff_r_no++;
            }
        }
        break;
    default:
        staffroll_end = 1;
        break;
    }
    return staffroll_end;
}
