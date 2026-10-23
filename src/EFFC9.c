/*
 * EFFC9.C  Effect C9: the judge girls
 *
 * Effect C9 is one of the judges who appear for a judgement decision. effect_C9_init (called
 * from plcntset_2.c) chooses the judge's character set for the stage, round and slot from
 * ag_sel_table, with colour and character table from ag_cc_table / ag_char_table.
 * effect_C9_move places her at app_pos_hosei relative to the screen centre with a shadow from
 * judge_gals_kage_tbl,
 * then when Event_Judge_Gals is raised plays her judging patterns and spawns the effect 37 flag
 * for the player she votes for (EJG_index). setup_EJG_index fills EJG_index: all votes go to the
 * winner when the round scores differ by more than 10000, otherwise from sel_ejg_ix_table.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLS02.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "aboutspr.h"
#include "EFF03.h"
#include "EFF37.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "EFFC9.h"



extern const u32 ag_char_table_0[], ag_char_table_1[], ag_char_table_2[], ag_char_table_3[], ag_char_table_4[],
                 ag_char_table_5[], ag_char_table_6[];

u32* ag_char_table[7] = {
    (u32*)ag_char_table_0,
    (u32*)ag_char_table_1,
    (u32*)ag_char_table_2,
    (u32*)ag_char_table_3,
    (u32*)ag_char_table_4,
    (u32*)ag_char_table_5,
    (u32*)ag_char_table_6,
};


/* case 0 records stage8_base_y, and the stage-8 fall waits for it to change */
void effect_C9_move(WORK_Other* ewk) {
    s16 scrc;
    switch (ewk->wu.routine_no[0]) {
    case 0:
        ++ewk->wu.routine_no[0];
        ewk->wu.disp_flag = 1;
        scrc = get_center_position();
        ewk->wu.xyz[0].disp.pos = app_pos_hosei[ewk->wu.type][0] + scrc;
        ewk->wu.xyz[1].disp.pos = app_pos_hosei[ewk->wu.type][1];
        ewk->wu.xyz[2].disp.pos = app_pos_hosei[ewk->wu.type][2] + 32;
        ewk->wu.kage_flag = 1;
        ewk->wu.kage_hx = judge_gals_kage_tbl[ewk->wu.charset_id][0];
        ewk->wu.kage_hy = judge_gals_kage_tbl[ewk->wu.charset_id][1];
        ewk->wu.kage_prio = judge_gals_kage_tbl[ewk->wu.charset_id][2];
        ewk->wu.kage_char = judge_gals_kage_tbl[ewk->wu.charset_id][3];
        if (ewk->wu.type == 1) {
            ewk->wu.kage_hy -= 2;
        }
        set_char_move_init(&ewk->wu, 0, 0);
        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
        ewk->wu.position_z = ewk->wu.xyz[2].disp.pos;
        ewk->wu.old_pos[1] = stage8_base_y;
        sort_push_request(&ewk->wu);
        break;
    case 1:
        if (ewk->wu.dead_f == 1) {
            ewk->wu.routine_no[0] = 3;
            break;
        }
        if (EXE_flag == 0) {
            if (!Game_pause) {
                char_move(&ewk->wu);
                switch (ewk->wu.routine_no[1]) {
                case 0:
                    if (Event_Judge_Gals) {
                        ewk->wu.routine_no[1] += 1;
                        set_char_move_init(&ewk->wu, 0, 1);
                    }
                    break;
                case 1:
                    if (ewk->wu.cg_type == 0xFF) {
                        ewk->wu.routine_no[1] += 1;
                        set_char_move_init(&ewk->wu, 0, 2);
                        effect_37_init(&ewk->wu, ewk->wu.charset_id, EJG_index[ewk->wu.type]);
                    }
                    break;
                case 2:
                    if (ewk->wu.cg_type == 0xFF) {
                        ewk->wu.routine_no[1] += 1;
                        Event_Judge_Gals -= 1;
                    }
                    break;
                case 3:
                    if (Event_Judge_Gals < 0) {
                        ewk->wu.routine_no[1] += 1;
                    }
                case 4:
                    if (bg_w.stage == 8 && Round_num == 0) {
                        ewk->wu.routine_no[1] += 1;
                        ewk->wu.routine_no[2] = 0;
                    } else {
                        ewk->wu.routine_no[1] += 9;
                    }
                    break;
                case 5:
                    switch (ewk->wu.routine_no[2]) {
                    case 0:
                        if (ewk->wu.old_pos[1] != stage8_base_y) {
                            ewk->wu.mvxy.d[0].sp = 0;
                            ewk->wu.mvxy.a[0].sp = 0;
                            ewk->wu.mvxy.a[1].sp = 0;
                            ewk->wu.mvxy.d[1].sp = -0x3800;
                            ewk->wu.mvxy.kop[0] = ewk->wu.mvxy.kop[1] = 0;
                            ewk->wu.kage_flag = 0;
                            ewk->wu.routine_no[2]++;
                        }
                        break;
                    case 1:
                        add_mvxy_speed(&ewk->wu);
                        cal_mvxy_speed(&ewk->wu);
                        if (ewk->wu.mvxy.a[1].sp < -0x100000) {
                            ewk->wu.mvxy.d[1].sp = 0;
                        }
                        ewk->wu.position_x = ewk->wu.xyz[0].disp.pos;
                        ewk->wu.position_y = ewk->wu.xyz[1].disp.pos;
                        break;
                    }
                    break;
                }
            }
        }
        sort_push_request(&ewk->wu);
        break;
    case 2:
    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}



s32 effect_C9_init(PLW* arg0, u8 data) {
    WORK_Other* ewk;
    s16 ix;
    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }
    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 129;
    ewk->wu.work_id = 16;
    ewk->wu.type = data;
    ewk->wu.charset_id = ag_sel_table[bg_w.stage][Round_num & 3][data];
    ewk->wu.cgromtype = 1;
    ewk->wu.my_family = 2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.my_col_code = ag_cc_table[ewk->wu.charset_id];
    ewk->wu.char_table[0] = ag_char_table[ewk->wu.charset_id];
    return 0;
}



/* Compare the round scores in Score[x][2]; a gap above 10000 gives all votes to the winner. */
void setup_EJG_index(void) {
    s16 i;
    u32 gra;
    if (Score[0][2] < Score[1][2]) {
        gra = Score[1][2] - Score[0][2];
    } else {
        gra = Score[0][2] - Score[1][2];
    }
    if (gra > 10000) {
        if (Winner_id) {
            EJG_index[0] = 1;
            EJG_index[1] = 1;
            EJG_index[2] = 1;
            EJG_index[3] = 0xFF;
        } else {
            EJG_index[0] = 0;
            EJG_index[1] = 0;
            EJG_index[2] = 0;
            EJG_index[3] = 0xFF;
        }
    } else {
        for (i = 0; i < 4; i++) {
            (&EJG_index[0])[i] = sel_ejg_ix_table[Winner_id][Game_timer & 1][i];
        }
    }
}
