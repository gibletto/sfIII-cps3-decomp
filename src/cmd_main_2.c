/*
 * CMD_MAIN_2.C  Command input
 *
 * Command input: waza_check runs for each player every frame; cmd_move steps the 48 waza (special
 * move) slots of the player's pl_CMD table through the check_* input-state routines (lever
 * sequences, charges, buttons, parries) and command_ok / command_ok_move flag completed commands.
 * cmd_init and the waza_flag clear routines reset the command work.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "Com_Pl.h"
#include "aboutspr.h"
#include "SYS_sub.h"
#include "CALDIR.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "EFFECT.h"
#include "effect_2.h"
#include "EFF00.h"
#include "EFF02.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "CHARMOVE.h"
#include "charmove_2.h"
#include "PLS01.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "fifo.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "bg000.h"
#include "HITCHECK.h"
#include "PLCNTDAT.h"
#include "plcntdat_2.h"
#include "cmd_main_2.h"
#include "cmd_data.h"
#include "cps3.h"

extern const u16 rot_lvr_tbl_r[4];    /* provisional name (06409750): 1, 8, 2, 4 */
extern const u16 rot_lvr_tbl_l[4];    /* provisional name (06409758): 1, 4, 2, 8 */



/* 02004F20 */
/* The check routines, indexed by a step's CK_* code (cmd_data.h). */
void (*chk_move_jp[CMD_END])() = {
    check_init, /* CK_INIT */
    check_0,    /* CK_LEVER */
    check_1,    /* CK_CHARGE */
    check_2,    /* CK_HOLD */
    check_3,    /* CK_SHOT_HOLD */
    check_4,    /* CK_RENDA */
    check_5,    /* CK_PRESS */
    check_6,    /* CK_TURN */
    check_7,    /* CK_SHOT_P */
    check_7,    /* CK_SHOT_K */
    check_9,    /* CK_LEVER_CHANGE */
    check_10,   /* CK_PARRY */
    check_11,   /* CK_BACK_DOWN */
    check_12,   /* CK_PARRY_CHANGE */
    check_13,   /* CK_UKEMI */
    check_14,   /* CK_RENDA3 */
    check_15,   /* CK_LEVER_COUNT */
    check_16,   /* CK_PRESS_P */
    check_16,   /* CK_PRESS_K */
    check_18,   /* CK_LEVER_REPEAT */
    check_19,   /* CK_LEVER_SET */
    check_20,   /* CK_NONE */
    check_21,   /* CK_LEVER_PRESS */
    check_22,   /* CK_ROTATE */
    check_23,   /* CK_PARRY_STRICT */
    check_24,   /* CK_LEVER_NEW */
    check_25,   /* CK_LEVER_HELD */
};


void waza_check(PLW* pl) {
    cmd_pl = pl;
    cmd_id = cmd_pl->wu.id;
    chk_pl = &t_pl_lvr[cmd_id];
    sw_pick_up();
    cmd_move();
}



void cmd_data_set(PLW* pl, s16 i) {
    u8* ptr3;
    u16* ptr4;
    (&wcp[cmd_id].reset[0])[i] = *cmd_tbl_ptr++;
    waza_work[cmd_id][i].w_dead = *cmd_tbl_ptr++;
    waza_work[cmd_id][i].w_dead2 = *cmd_tbl_ptr++;
    ptr3 = &wcp[cmd_id].waza_r[i][0];
    *ptr3++ = (s8)*cmd_tbl_ptr++;
    *ptr3++ = (s8)*cmd_tbl_ptr++;
    *ptr3++ = (s8)*cmd_tbl_ptr++;
    *ptr3++ = (s8)*cmd_tbl_ptr++;
    wcp[cmd_id].btix[i] = *cmd_tbl_ptr++;
    ptr4 = &wcp[cmd_id].exdt[i][0];
    *ptr4++ = *cmd_tbl_ptr++;
    *ptr4++ = *cmd_tbl_ptr++;
    *ptr4++ = *cmd_tbl_ptr++;
    *ptr4++ = *cmd_tbl_ptr++;
}



void cmd_init(PLW* pl) {
    s16 slot;
    s16 i;
    s16 j;
    s32* ptr;
    cmd_id = pl->wu.id;
    pl->cp = &wcp[cmd_id];
    pl->wu.routine_no[7]++;
    ptr = (s32*)waza_work[cmd_id];
    for (i = 0; i < CMD_SLOTS; i++) {
        for (j = 0; j < 6; j = j + 1) {
            *ptr++ = 0;
        }
    }
    slot = 0;
    do {
        (&wcp[cmd_id].waza_flag[0])[slot] = 0;
        j = 0;
        while (j < 4) {
            (&wcp[cmd_id].waza_r[slot][0])[j] = 0;
            j++;
            (&wcp[cmd_id].waza_r[slot][0])[j] = 0;
            j++;
        }
        slot = slot + 1;
    } while (slot < CMD_SLOTS);
    waza_compel_all_init(pl);
}



void cmd_move(void) {
    s16 j;
    s16 i;
    intptr_t* adrs;
    cmd_id = cmd_pl->wu.id;
    adrs = pl_CMD[cmd_pl->player_number];
    for (j = 0; j < CMD_SLOTS; j++) {
        if (wcp[cmd_id].waza_flag[j] != -1) {
            waza_type[cmd_id] = j;
            cmd_tbl_ptr = (s16*)adrs[j];
            waza_ptr = &waza_work[cmd_id][j];
            chk_move_jp[waza_ptr->w_type]();
        }
    }
    for (i = 0; i < CMD_SLOTS; i++) {
        if (wcp[cmd_id].waza_flag[i] != -1 && wcp[cmd_id].waza_flag[i] != 0) {
            command_ok_move(i);
        }
    }
}



void check_init(void) {
    cmd_tbl_ptr += CMD_HEAD_WORDS;
    waza_ptr->w_type = *cmd_tbl_ptr++;
    waza_ptr->w_int = *cmd_tbl_ptr++;
    waza_ptr->free1 = *cmd_tbl_ptr;
    waza_ptr->free2 = *cmd_tbl_ptr++;
    waza_ptr->w_lvr = *cmd_tbl_ptr++;
    waza_ptr->w_ptr = cmd_tbl_ptr;
    waza_ptr->uni0.tame.flag = 0;
    waza_ptr->uni0.tame.shot_flag = 0;
    waza_ptr->uni0.tame.shot_flag2 = 0;
    waza_ptr->shot_ok = 0;
    waza_ptr->free3 = 0;
    chk_move_jp[waza_ptr->w_type]();
}



void check_next(void) {
    s16* next_ptr = waza_ptr->w_ptr;
    waza_ptr->w_type = *next_ptr++;
    waza_ptr->w_int = *next_ptr++;
    waza_ptr->free1 = *next_ptr;
    waza_ptr->free2 = *next_ptr++;
    waza_ptr->w_lvr = *next_ptr++;
    waza_ptr->w_ptr = next_ptr;
    if (waza_ptr->w_type != CK_LEVER_CHANGE) {
        chk_move_jp[waza_ptr->w_type]();
    }
}



void check_0(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    sw_lever = chk_pl->sw_lever & CMD_LV_MASK;
    if (dead_lvr_check() == 0) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
            if (sw_lever == sw_work) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (sw_lever == CMD_LV_NEUTRAL) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if (chk_pl->now_lvbt & CMD_LV_MASK) {
            if (sw_lever & waza_ptr->w_lvr) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        }
    }
}



void check_1(void) {
    if (dead_lvr_check() == 0) {
        sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            if (sw_work == chk_pl->sw_lever) {
                waza_ptr->free2--;
                if (waza_ptr->uni0.tame.flag) {
                    return;
                }
                if (waza_ptr->free2 < 0) {
                    waza_ptr->uni0.tame.flag = 1;
                }
            } else {
                if (waza_ptr->uni0.tame.flag) {
                    waza_ptr->uni0.tame.flag = 0;
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                    return;
                }
                waza_ptr->free2 = waza_ptr->free1;
                waza_ptr->w_int--;
                if (waza_ptr->w_int < 0) {
                    waza_ptr->w_type = 0;
                }
            }
        } else {
            if (sw_work & chk_pl->sw_lever) {
                if (waza_ptr->uni0.tame.flag) {
                    return;
                }
                waza_ptr->free1--;
                if (waza_ptr->free1 < 0) {
                    waza_ptr->uni0.tame.flag = 1;
                }
            } else {
                if (waza_ptr->uni0.tame.flag) {
                    waza_ptr->uni0.tame.flag = 0;
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                    return;
                }
                waza_ptr->free2 = waza_ptr->free1;
                waza_ptr->w_int--;
                if (waza_ptr->w_int < 0) {
                    waza_ptr->w_type = 0;
                }
            }
        }
    }
}



void check_2(void) {
    sw_work = chk_pl->sw_new & waza_ptr->w_lvr;
    if (waza_ptr->w_lvr == sw_work) {
        if (waza_ptr->uni0.tame.flag) {
            return;
        }
        waza_ptr->free2--;
        if (waza_ptr->free2 < 0) {
            waza_ptr->uni0.tame.flag = 1;
        }
    } else {
        if (waza_ptr->uni0.tame.flag) {
            if (sw_work == CMD_LV_NEUTRAL) {
                waza_ptr->uni0.tame.flag = 0;
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
                return;
            }
        }
        waza_ptr->free2 = waza_ptr->free1;
        waza_ptr->w_int--;
        if (waza_ptr->w_int < 0) {
            waza_ptr->w_type = 0;
        }
    }
}



void check_3(void) {
    s16 i;
    s16 w_flag;
    s16* shot_cnt_adrs;
    sw_work = chk_pl->sw_new & 0x7F0;
    waza_ptr->uni0.tame.shot_flag2 = waza_ptr->uni0.tame.shot_flag;
    waza_ptr->uni0.tame.shot_flag = 0;
    shot_cnt_adrs = &chk_pl->s1_cnt;
    w_flag = CMD_SW_LP;
    for (i = 0; i < 6; i++) {
        if (*shot_cnt_adrs >= waza_ptr->w_int) {
            waza_ptr->uni0.tame.shot_flag |= w_flag;
        }
        shot_cnt_adrs++;
        if (chk_pl->shot_down & w_flag) {
            if (waza_ptr->uni0.tame.shot_flag2 & w_flag) {
                waza_ptr->shot_ok++;
            }
        }
        w_flag <<= 1;
    }
    if (waza_ptr->shot_ok) {
        waza_ptr->free2--;
        if (waza_ptr->free2 < 0) {
            waza_ptr->shot_ok = 0;
            waza_ptr->free2 = waza_ptr->free1;
        }
    }
    if (waza_ptr->shot_ok >= waza_ptr->w_lvr) {
        waza_ptr->shot_ok = 0;
        waza_ptr->free2 = waza_ptr->free1;
        if (*waza_ptr->w_ptr == CMD_END) {
            command_ok();
            return;
        }
        check_next();
    }
}



void check_4(void) {
    if (waza_ptr->w_lvr == CMD_SW_LP) {
        if (chk_pl->sw_now & CMD_SW_LP) {
            waza_ptr->uni0.tame.flag++;
        }
        if (chk_pl->sw_now & CMD_SW_MP) {
            waza_ptr->uni0.tame.shot_flag++;
        }
        if (chk_pl->sw_now & CMD_SW_HP) {
            waza_ptr->uni0.tame.shot_flag2++;
        }
    } else {
        if (chk_pl->sw_now & CMD_SW_LK) {
            waza_ptr->uni0.tame.flag++;
        }
        if (chk_pl->sw_now & CMD_SW_MK) {
            waza_ptr->uni0.tame.shot_flag++;
        }
        if (chk_pl->sw_now & CMD_SW_HK) {
            waza_ptr->uni0.tame.shot_flag2++;
        }
    }
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->uni0.tame.flag = 0;
        waza_ptr->uni0.tame.shot_flag = 0;
        waza_ptr->uni0.tame.shot_flag2 = 0;
        waza_ptr->w_int = waza_ptr->free1;
    }
    if (wcp[cmd_id].waza_flag[waza_type[cmd_id]]) {
        if (waza_ptr->w_int > 0) {
            if (waza_ptr->uni0.tame.shot_flag2) {
                wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                waza_ptr->uni0.tame.shot_flag2 = 0;
                waza_ptr->w_int = 9;
                return;
            }
        }
    } else if (waza_ptr->uni0.tame.shot_flag2 >= 5) {
        wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
        waza_ptr->uni0.tame.shot_flag2 = 0;
        waza_ptr->w_int = 9;
        chk_pl->waza_no = waza_type[cmd_id];
        return;
    }
    if (wcp[cmd_id].waza_flag[waza_type[cmd_id]]) {
        if (waza_ptr->w_int > 0 && waza_ptr->uni0.tame.shot_flag) {
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            waza_ptr->uni0.tame.shot_flag = 0;
            waza_ptr->w_int = 12;
            return;
        }
    } else if (waza_ptr->uni0.tame.shot_flag >= 5) {
        wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
        waza_ptr->uni0.tame.shot_flag = 0;
        waza_ptr->w_int = 12;
        chk_pl->waza_no = waza_type[cmd_id];
        return;
    }
    if (wcp[cmd_id].waza_flag[waza_type[cmd_id]]) {
        if (waza_ptr->w_int > 0 && waza_ptr->uni0.tame.flag) {
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            waza_ptr->uni0.tame.flag = 0;
            waza_ptr->w_int = 15;
            return;
        }
    } else if (waza_ptr->uni0.tame.flag >= 5) {
        wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
        waza_ptr->uni0.tame.flag = 0;
        waza_ptr->w_int = 15;
        chk_pl->waza_no = waza_type[cmd_id];
    }
}



void check_5(void) {
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr == chk_pl->sw_now) {
            if (*waza_ptr->w_ptr == CMD_END) {
                command_ok();
                return;
            }
            check_next();
        }
    }
}



/* A lever rotation (the sw_lever sequence of rot_lvr_tbl_r or rot_lvr_tbl_l, from any starting step):
 * free3 / shot_ok collect the directions met, uni0 indexes the next one, and w_int / free1 time each out
 * (reloaded from free2). */
void check_6(void) {
    s16 i;
    if (!waza_ptr->free3) {
        for (i = 0; i < 4; i++) {
            if (chk_pl->sw_lever == rot_lvr_tbl_r[i]) {
                waza_ptr->uni0.tame.flag = i + 1;
                waza_ptr->free3 |= rot_lvr_tbl_r[i];
            }
        }
    }
    if (!waza_ptr->shot_ok) {
        for (i = 0; i < 4; i++) {
            if (chk_pl->sw_lever == rot_lvr_tbl_l[i]) {
                waza_ptr->uni0.tame.shot_flag = i + 1;
                waza_ptr->shot_ok |= rot_lvr_tbl_l[i];
            }
        }
    }
    if (waza_ptr->free3) {
        waza_ptr->w_int--;
        if (waza_ptr->w_int < 0) {
            waza_ptr->w_int = waza_ptr->free2;
            waza_ptr->free3 = 0;
        } else if (chk_pl->sw_lever == (u16)rot_lvr_tbl_r[waza_ptr->uni0.tame.flag]) {
            waza_ptr->free3 |= rot_lvr_tbl_r[waza_ptr->uni0.tame.flag];
            waza_ptr->uni0.tame.flag++;
            waza_ptr->uni0.tame.flag &= 3;
            if (waza_ptr->free3 == 15) {
                command_ok();
            }
        }
    }
    if (waza_ptr->shot_ok) {
        waza_ptr->free1--;
        if (waza_ptr->free1 < 0) {
            waza_ptr->free1 = waza_ptr->free2;
            waza_ptr->shot_ok = 0;
            return;
        }
        if (chk_pl->sw_lever == (u16)rot_lvr_tbl_l[waza_ptr->uni0.tame.shot_flag]) {
            waza_ptr->shot_ok |= rot_lvr_tbl_l[waza_ptr->uni0.tame.shot_flag];
            waza_ptr->uni0.tame.shot_flag++;
            waza_ptr->uni0.tame.shot_flag &= 3;
            if (waza_ptr->shot_ok == 15) {
                command_ok();
            }
        }
    }
}



void check_7(void) {
    s16 i;
    s16 w_flag;
    s16* shot_cnt_adrs;
    waza_ptr->w_int--;
    if (waza_ptr->w_type == CK_SHOT_P) {
        sw_work = chk_pl->sw_new & CMD_SW_PUNCH;
        shot_cnt_adrs = &chk_pl->s1_cnt;
        w_flag = CMD_SW_LP;
    } else {
        sw_work = chk_pl->sw_new & 0x780;
        shot_cnt_adrs = &chk_pl->s4_cnt;
        w_flag = CMD_SW_LK;
    }
    waza_ptr->uni0.tame.shot_flag2 = waza_ptr->uni0.tame.shot_flag;
    waza_ptr->uni0.tame.shot_flag = 0;
    for (i = 0; i < 3; i++) {
        if (*shot_cnt_adrs & waza_ptr->w_lvr) {
            waza_ptr->uni0.tame.shot_flag |= w_flag;
        }
        shot_cnt_adrs++;
        if (chk_pl->shot_down & w_flag) {
            if (waza_ptr->uni0.tame.shot_flag2 & w_flag) {
                waza_ptr->shot_ok++;
            }
        }
        w_flag <<= 1;
    }
    if (waza_ptr->shot_ok) {
        waza_ptr->free2--;
        if (waza_ptr->free2 < 0) {
            waza_ptr->shot_ok = 0;
            waza_ptr->free2 = waza_ptr->free1;
            waza_ptr->uni0.tame.shot_flag = 0;
        }
    }
    if (waza_ptr->shot_ok >= waza_ptr->w_lvr) {
        waza_ptr->shot_ok = 0;
        waza_ptr->free2 = waza_ptr->free1;
        if (*waza_ptr->w_ptr == CMD_END) {
            command_ok();
            return;
        }
        check_next();
    }
}



void check_9(void) {
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    if (waza_ptr->w_lvr & CMD_LV_EXACT) {
        sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
        if (waza_ptr->w_lvr == 0) {
            if (chk_pl->new_lvbt == 0) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
            if (chk_pl->sw_lever == sw_work) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            } else {
                waza_ptr->w_type = 0;
            }
        }
    } else if (waza_ptr->w_lvr == 0) {
        if (chk_pl->new_lvbt == 0) {
            if (*waza_ptr->w_ptr == CMD_END) {
                command_ok();
            } else {
                check_next();
            }
        } else if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
            waza_ptr->w_type = 0;
        }
    } else if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
        if (chk_pl->sw_lever & waza_ptr->w_lvr) {
            if (*waza_ptr->w_ptr == CMD_END) {
                command_ok();
            } else {
                check_next();
            }
        } else {
            waza_ptr->w_type = 0;
        }
    }
}



s32 paring_miss_init(void) {
    waza_ptr->free3 = 0;
    waza_ptr->w_type = 0;
    waza_ptr->uni0.tame.flag = 0;
    wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 0;
}



void check_10(void) {
    switch (waza_ptr->shot_ok) {
    case 0:
        if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
            waza_ptr->shot_ok++;
        }
        break;
    case 1:
        if (chk_pl->now_lvbt & CMD_LV_MASK) {
            if (chk_pl->sw_lever == waza_ptr->w_lvr) {
                waza_ptr->shot_ok++;
                wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                waza_ptr->free3 = wcp[cmd_id].reset[waza_type[cmd_id]] + 8;
                waza_ptr->w_int = 6;
            }
        }
        break;
    case 2:
        waza_ptr->w_int--;
        waza_ptr->free3--;
        if (waza_ptr->w_int > 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                waza_ptr->shot_ok++;
                break;
            }
            if (chk_pl->sw_lever & CMD_LV_BACK) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->shot_ok++;
            } else if (chk_pl->sw_lever != waza_ptr->w_lvr) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->w_type = 0;
            }
        } else {
            (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
            waza_ptr->shot_ok++;
        }
        break;
    case 3:
        waza_ptr->free3--;
        if (waza_ptr->free3 < 0) {
            waza_ptr->w_type = 0;
            break;
        }
        if (chk_pl->sw_now & CMD_LV_BACK || chk_pl->sw_now == waza_ptr->w_lvr) {
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 0;
            break;
        }
        if (chk_pl->sw_now & CMD_LV_MASK) {
            (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
            waza_ptr->w_type = 0;
        }
        break;
    }
}



void check_11(void) {
    if (dead_lvr_check()) {
        paring_miss_init();
        return;
    }
    switch (waza_ptr->uni0.tame.flag) {
    case 0:
        if (chk_pl->sw_lever & CMD_LV_BACK) {
            waza_ptr->uni0.tame.flag = 1;
            break;
        }
        waza_ptr->uni0.tame.flag = 0;
        break;
    case 1:
        if (chk_pl->sw_lever == CMD_LV_DOWN) {
            check_next();
            break;
        }
        if (!(chk_pl->sw_lever & CMD_LV_BACK)) {
            waza_ptr->uni0.tame.flag = 0;
        }
        break;
    }
}



void check_12(void) {
    switch (waza_ptr->shot_ok) {
    case 0:
        if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
            waza_ptr->shot_ok++;
        }
        break;
    case 1:
        if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK) && chk_pl->sw_lever == waza_ptr->w_lvr) {
            waza_ptr->shot_ok++;
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            waza_ptr->free3 = wcp[cmd_id].reset[waza_type[cmd_id]] + 8;
            waza_ptr->w_int = 6;
        }
        break;
    case 2:
        waza_ptr->w_int--;
        waza_ptr->free3--;
        if (waza_ptr->w_int > 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                waza_ptr->shot_ok++;
                break;
            }
            if (chk_pl->sw_lever & CMD_LV_FORWARD) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->shot_ok++;
            } else if (chk_pl->sw_lever != waza_ptr->w_lvr) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->w_type = 0;
            }
        } else {
            (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
            waza_ptr->shot_ok++;
        }
        break;
    case 3:
        waza_ptr->free3--;
        if (waza_ptr->free3 < 0) {
            waza_ptr->w_type = 0;
            break;
        }
        if ((chk_pl->sw_now & CMD_LV_FORWARD) || chk_pl->sw_now == waza_ptr->w_lvr) {
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 0;
            break;
        }
        if (chk_pl->sw_now & CMD_LV_MASK) {
            (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
            waza_ptr->w_type = 0;
        }
        break;
    }
}



void check_13(void) {
    u16 sw_w;
    if (waza_ptr->free3 > 0) {
        waza_ptr->free3--;
        if (waza_ptr->free3 <= 0) {
            waza_ptr->w_type = 0;
        }
    }
    if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK) && chk_pl->sw_lever == CMD_LV_DOWN) {
        wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 16 - ukemi_time_tbl[wcp[cmd_id].waza_flag[waza_type[cmd_id]]];
        waza_ptr->free3 = 16;
        chk_pl->waza_no = waza_type[cmd_id];
    }
    sw_w = (chk_pl->sw_now | chk_pl->old_now) & CMD_SW_PUNCH;
    if (sw_w == CMD_SW_PUNCH) {
        wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 16 - ukemi_time_tbl[wcp[cmd_id].waza_flag[waza_type[cmd_id]]];
        waza_ptr->free3 = 16;
        chk_pl->waza_no = waza_type[cmd_id];
    }
}



void check_14(void) {
    s16 id;
    waza_ptr->w_int--;
    if (waza_ptr->w_lvr == CMD_SW_LP) {
        if (chk_pl->sw_now & CMD_SW_PUNCH) {
            waza_ptr->uni0.tame.flag++;
        }
    } else if (chk_pl->sw_now & CMD_SW_KICK) {
        waza_ptr->uni0.tame.flag++;
    }
    id = cmd_id;
    if (wcp[id].waza_flag[waza_type[id]]) {
        if (waza_ptr->w_int <= 0) {
            if (waza_ptr->uni0.tame.flag) {
                wcp[id].waza_flag[waza_type[id]] = wcp[id].reset[waza_type[id]];
                waza_ptr->uni0.tame.flag = 0;
                if (waza_type[cmd_id] & 1) {
                    waza_ptr->w_int = 10;
                } else {
                    waza_ptr->w_int = 6;
                }
                return;
            } else {
                waza_ptr->uni0.tame.flag = 0;
                waza_ptr->w_int = waza_ptr->free1;
            }
        }
    } else if (waza_type[id] & 1) {
        if (waza_ptr->uni0.tame.flag >= 3) {
            wcp[id].waza_flag[waza_type[id]] = wcp[id].reset[waza_type[id]];
            waza_ptr->uni0.tame.flag = 0;
            waza_ptr->w_int = 10;
            chk_pl->waza_no = waza_type[cmd_id];
            return;
        } else if (waza_ptr->w_int < 0) {
            waza_ptr->uni0.tame.flag = 0;
            waza_ptr->w_int = waza_ptr->free1;
        }
    } else {
        if (waza_ptr->uni0.tame.flag >= 3) {
            wcp[id].waza_flag[waza_type[id]] = wcp[id].reset[waza_type[id]];
            waza_ptr->uni0.tame.flag = 0;
            waza_ptr->w_int = 6;
            chk_pl->waza_no = waza_type[cmd_id];
            return;
        } else if (waza_ptr->w_int < 0) {
            waza_ptr->uni0.tame.flag = 0;
            waza_ptr->w_int = waza_ptr->free1;
        }
    }
}



void check_15(void) {
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
        return;
    }
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
            if (chk_pl->sw_lever == sw_work) {
                waza_ptr->shot_ok++;
                if (waza_ptr->shot_ok >= waza_ptr->free1) {
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                waza_ptr->shot_ok++;
                if (waza_ptr->shot_ok >= waza_ptr->free1) {
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                }
            }
        } else if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
            if (chk_pl->sw_lever & waza_ptr->w_lvr) {
                waza_ptr->shot_ok++;
                if (waza_ptr->shot_ok >= waza_ptr->free1) {
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                }
            }
        }
    }
}



void check_16(void) {
    s16 i;
    u16 w_flag;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
        waza_ptr->shot_ok = 0;
        return;
    }
    if (waza_ptr->w_type == CK_PRESS_P) {
        sw_work = chk_pl->sw_now & CMD_SW_PUNCH;
        w_flag = CMD_SW_LP;
    } else {
        sw_work = chk_pl->sw_now & CMD_SW_KICK;
        w_flag = CMD_SW_LK;
    }
    waza_ptr->uni0.tame.shot_flag2 = waza_ptr->uni0.tame.shot_flag;
    waza_ptr->uni0.tame.shot_flag = 0;
    for (i = 0; i < 3; i++) {
        if (sw_work & w_flag) {
            waza_ptr->shot_ok++;
        }
        w_flag <<= 1;
    }
    if (waza_ptr->shot_ok >= waza_ptr->w_lvr) {
        waza_ptr->shot_ok = 0;
        if (*waza_ptr->w_ptr == CMD_END) {
            command_ok();
        } else {
            check_next();
        }
    }
}



void check_18(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
        return;
    }
    sw_lever = chk_pl->sw_lever & CMD_LV_MASK;
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
                sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
                if (sw_lever == sw_work) {
                    waza_ptr->w_int = waza_ptr->free1;
                    (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                waza_ptr->w_int = waza_ptr->free1;
                wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            }
        } else if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK)) {
            if (sw_lever & waza_ptr->w_lvr) {
                waza_ptr->w_int = waza_ptr->free1;
                wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            }
        }
    }
}



void check_19(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    sw_lever = chk_pl->sw_lever & CMD_LV_MASK;
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            if (chk_pl->now_lvbt & CMD_LV_MASK) {
                sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
                if (sw_lever == sw_work) {
                    (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                    check_next();
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                check_next();
            }
        } else if (chk_pl->now_lvbt & CMD_LV_MASK) {
            if (sw_lever & waza_ptr->w_lvr) {
                wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
                check_next();
            }
        }
    }
}



void check_20(void) {
}



void check_21(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    sw_lever = chk_pl->sw_lever & CMD_LV_MASK;
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
            if (sw_work == CMD_LV_NEUTRAL) {
                if (sw_lever == CMD_LV_NEUTRAL) {
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                }
            } else if (chk_pl->now_lvbt & CMD_LV_MASK) {
                if (sw_lever == sw_work) {
                    if (*waza_ptr->w_ptr == CMD_END) {
                        command_ok();
                    } else {
                        check_next();
                    }
                }
            }
        } else if (!waza_ptr->w_lvr) {
            if (sw_lever == CMD_LV_NEUTRAL) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if (chk_pl->now_lvbt & CMD_LV_MASK) {
            if (sw_lever & waza_ptr->w_lvr) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        }
    }
}



void check_22(void) {
    s16 i;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_int = waza_ptr->free2;
        waza_ptr->free3 = 0;
    }
    for (i = 0; i < 8; i++) {
        if (chk_pl->sw_lever == chk22_tbl[i]) {
            waza_ptr->free3 |= 1 << i;
        }
    }
    if (waza_ptr->free3 == 0xFF) {
        command_ok();
    }
}



void check_23(void) {
    switch (waza_ptr->shot_ok) {
    case 0:
        if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
            waza_ptr->shot_ok++;
            break;
        }
        break;
    case 1:
        if ((chk_pl->old_lvbt & CMD_LV_MASK) != (chk_pl->new_lvbt & CMD_LV_MASK) && chk_pl->sw_lever == waza_ptr->w_lvr) {
            waza_ptr->shot_ok++;
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
            waza_ptr->free3 = (s16)(wcp[cmd_id].reset[waza_type[cmd_id]] + 3);
            waza_ptr->w_int = 6;
        }
        break;
    case 2:
        waza_ptr->w_int--;
        waza_ptr->free3--;
        if (waza_ptr->w_int > 0) {
            if (chk_pl->sw_lever == CMD_LV_NEUTRAL) {
                waza_ptr->shot_ok++;
                break;
            }
            if (chk_pl->sw_lever & CMD_LV_BACK) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->shot_ok++;
                break;
            }
            if (chk_pl->sw_lever != waza_ptr->w_lvr) {
                (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
                waza_ptr->w_type = 0;
            }
            break;
        }
        (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
        waza_ptr->shot_ok++;
        break;
    case 3:
        waza_ptr->free3--;
        if (waza_ptr->free3 < 0) {
            waza_ptr->w_type = 0;
            break;
        }
        if (chk_pl->sw_now & CMD_LV_BACK || chk_pl->sw_now == waza_ptr->w_lvr) {
            wcp[cmd_id].waza_flag[waza_type[cmd_id]] = 0;
            break;
        }
        if (chk_pl->sw_now & CMD_LV_MASK) {
            (&wcp[cmd_id].waza_flag[0])[waza_type[cmd_id]] = 0;
            waza_ptr->w_type = 0;
        }
        break;
    }
}


void check_24(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    sw_lever = chk_pl->now_lvbt & CMD_LV_MASK;
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
            if (sw_lever == sw_work) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (sw_lever == CMD_LV_NEUTRAL) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else {
            if (sw_lever & waza_ptr->w_lvr) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        }
    }
}


void check_25(void) {
    u16 sw_lever;
    waza_ptr->w_int--;
    if (waza_ptr->w_int < 0) {
        waza_ptr->w_type = 0;
    }
    sw_lever = chk_pl->sw_lever & CMD_LV_MASK;
    if (!dead_lvr_check()) {
        if (waza_ptr->w_lvr & CMD_LV_EXACT) {
            sw_work = waza_ptr->w_lvr & CMD_LV_MASK;
            if (sw_lever == sw_work) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else if (waza_ptr->w_lvr == 0) {
            if (sw_lever == CMD_LV_NEUTRAL) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        } else {
            if (sw_lever & waza_ptr->w_lvr) {
                if (*waza_ptr->w_ptr == CMD_END) {
                    command_ok();
                } else {
                    check_next();
                }
            }
        }
    }
}



void command_ok(void) {
    wcp[cmd_id].waza_flag[waza_type[cmd_id]] = wcp[cmd_id].reset[waza_type[cmd_id]];
    if (waza_ptr->w_type != CK_UKEMI) {
        waza_ptr->w_type = 0;
        chk_pl->waza_no = waza_type[cmd_id];
    }
}



void command_ok_move(s16 waza_num) {
    wcp[cmd_id].waza_flag[waza_num]--;
}



s8 dead_lvr_check(void) {
    WAZA_WORK* wk = waza_ptr;
    T_PL_LVR* pl = chk_pl;
    if (wk->w_dead != 0) {
        if (wk->w_dead == pl->sw_new) {
            goto dead;
        }
    }
    if (wk->w_dead2 != 0) {
        if (wk->w_dead2 == pl->sw_new) {
            goto dead;
        }
    }
    return 0;
dead:
    wk->w_type = 0;
    return 1;
}



void pl_lvr_set(void) {
    u16 sw_work;
    u16 work2;
    u16 sw_0;
    sw_0 = wcp[cmd_id].sw_lvbt;
    if (cmd_pl->wu.rl_waza) {
        work2 = sw_0 & 0xC;
        if (work2) {
            sw_0 &= 0x7F3;
            work2 ^= 0xC;
            sw_0 |= work2;
        }
    }
    wcp[cmd_id].old_now = chk_pl->sw_now;
    chk_pl->old_now = chk_pl->sw_now;
    chk_pl->old_lvbt = chk_pl->new_lvbt;
    chk_pl->new_lvbt = wcp[cmd_id].sw_lvbt;
    chk_pl->sw_old = chk_pl->sw_new;
    chk_pl->sw_new = sw_0;
    chk_pl->sw_now = sw_0 & ~chk_pl->sw_old;
    chk_pl->now_lvbt = wcp[cmd_id].sw_lvbt & ~chk_pl->old_lvbt;
    chk_pl->sw_chg = chk_pl->sw_now | (chk_pl->sw_old & ~sw_0);
    chk_pl->sw_lever = sw_0 & CMD_LV_MASK;
    chk_pl->shot_up = chk_pl->sw_now & CMD_SW_SHOT;
    chk_pl->shot_down = chk_pl->sw_old & ~sw_0 & CMD_SW_SHOT;
    chk_pl->shot_ud = chk_pl->shot_up | chk_pl->shot_down;
    sw_work = wcp[cmd_id].old_now | chk_pl->sw_now;
    if ((sw_work & (CMD_SW_LP | CMD_SW_LK)) == (CMD_SW_LP | CMD_SW_LK)) {
        wcp[cmd_id].ca14 = 1;
    } else {
        wcp[cmd_id].ca14 = 0;
    }
    if ((sw_work & (CMD_SW_MP | CMD_SW_MK)) == (CMD_SW_MP | CMD_SW_MK)) {
        wcp[cmd_id].ca25 = 1;
    } else {
        wcp[cmd_id].ca25 = 0;
    }
    if ((sw_work & (CMD_SW_HP | CMD_SW_HK)) == (CMD_SW_HP | CMD_SW_HK)) {
        wcp[cmd_id].ca36 = 1;
    } else {
        wcp[cmd_id].ca36 = 0;
    }
    wcp[cmd_id].lgp = lever_gacha_tbl[cmd_pl->cp->sw_now & CMD_LV_MASK] * 4;
    wcp[cmd_id].lgp += lever_gacha_tbl[cmd_pl->cp->sw_off & CMD_LV_MASK] * 2;
    wcp[cmd_id].lgp += lever_gacha_tbl[(cmd_pl->cp->sw_now / 16) & 7] * 2;
    wcp[cmd_id].lgp += lever_gacha_tbl[(cmd_pl->cp->sw_now / 128) & 7];
}



void sw_pick_up(void) {
    s16 i;
    s16* cnt_address1;
    pl_lvr_set();
    sw_work = CMD_LV_UP;
    cnt_address1 = &chk_pl->up_cnt;
    for (i = 0; i < 10; i++) {
        if (chk_pl->sw_new & sw_work) {
            (*cnt_address1)++;
        } else {
            *cnt_address1 = 0;
        }
        cnt_address1++;
        sw_work <<= 1;
    }
    for (i = 0; i < 4; i++) {
        if (lvr_chk_tbl[0][i] & chk_pl->sw_new) {
            (*cnt_address1)++;
        } else {
            *cnt_address1 = 0;
        }
        cnt_address1++;
    }
    wcp[cmd_id].sw_new = chk_pl->sw_new;
    wcp[cmd_id].sw_old = chk_pl->sw_old;
    wcp[cmd_id].sw_chg = chk_pl->sw_chg;
    wcp[cmd_id].sw_now = chk_pl->sw_now;
    wcp[cmd_id].sw_off = chk_pl->shot_down;
    /* lever_dir 1: forward, 2: back, from the raw left (4) and right (8) bits */
    if ((i = wcp[cmd_id].sw_lvbt & LEVER_LR)) {
        if (cmd_pl->wu.rl_flag) {
            if (i & LEVER_RIGHT) {
                wcp[cmd_id].lever_dir = LVDIR_FORWARD;
            } else {
                wcp[cmd_id].lever_dir = LVDIR_BACK;
            }
        } else if (i & LEVER_LEFT) {
            wcp[cmd_id].lever_dir = LVDIR_FORWARD;
        } else {
            wcp[cmd_id].lever_dir = LVDIR_BACK;
        }
    } else {
        wcp[cmd_id].lever_dir = LVDIR_NEUTRAL;
    }
    if (chk_pl->left_cnt != 0 && chk_pl->left_cnt < 12) {
        wcp[cmd_id].calf = 1;
    } else {
        wcp[cmd_id].calf = 0;
    }
    if (chk_pl->right_cnt != 0 && chk_pl->right_cnt < 12) {
        wcp[cmd_id].calr = 1;
    } else {
        wcp[cmd_id].calr = 0;
    }
}



void dash_flag_clear(s16 pl_id) {
    intptr_t* adrs;
    adrs = pl_CMD[plw[pl_id].player_number];
    waza_compel_init(pl_id, 0, adrs);
    waza_compel_init(pl_id, 1, adrs);
}



void hi_jump_flag_clear(s16 pl_id) {
    waza_compel_init(pl_id, 2, pl_CMD[plw[pl_id].player_number]);
}



/* provisional name */
void basic_waza_flag_clear(s16 pl_id) {
    intptr_t* adrs = pl_CMD[plw[pl_id].player_number];
    waza_compel_init(pl_id, 0, adrs);
    waza_compel_init(pl_id, 1, adrs);
    waza_compel_init(pl_id, 3, adrs);
    waza_compel_init(pl_id, 4, adrs);
    waza_compel_init(pl_id, 5, adrs);
    waza_compel_init(pl_id, 6, adrs);
}



void waza_compel_init(pl_id, num, adrs)
s16 pl_id;
s16 num;
intptr_t* adrs;
{
    WAZA_WORK* w_ptr;
    s16* ptr;
    ptr = (s16*)adrs[num];
    ptr += 11;
    w_ptr = &waza_work[pl_id][num];
    w_ptr->w_type = *ptr++;
    w_ptr->w_int = *ptr++;
    w_ptr->free1 = *ptr;
    w_ptr->free2 = *ptr++;
    w_ptr->w_lvr = *ptr++;
    w_ptr->w_ptr = ptr;
    w_ptr->uni0.tame.flag = 0;
    w_ptr->uni0.tame.shot_flag = 0;
    w_ptr->uni0.tame.shot_flag2 = 0;
    w_ptr->shot_ok = 0;
    w_ptr->free3 = 0;
    wcp[pl_id].waza_flag[num] = 0;
}



void waza_compel_all_init(PLW* pl) {
    s16 i;
    intptr_t* adrs;
    adrs = pl_CMD[pl->player_number];
    for (i = 0; i < pl_cmd_num[pl->player_number][0]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][0]; i < 16; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 16; i < pl_cmd_num[pl->player_number][1]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][1]; i < 22; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 22; i < pl_cmd_num[pl->player_number][2]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][2]; i < 30; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 30; i < pl_cmd_num[pl->player_number][3]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][3]; i < 33; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 33; i < pl_cmd_num[pl->player_number][4]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][4]; i < 37; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 37; i < pl_cmd_num[pl->player_number][5]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][5]; i < 43; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 43; i < pl_cmd_num[pl->player_number][6]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][6]; i < 46; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
    for (i = 46; i < pl_cmd_num[pl->player_number][7]; i++) {
        cmd_tbl_ptr = (s16*)adrs[i];
        cmd_data_set(pl, i);
    }
    for (i = pl_cmd_num[pl->player_number][7]; i < CMD_SLOTS; i++) {
        (&wcp[cmd_id].waza_flag[0])[i] = -1;
    }
}


void waza_compel_all_init2(PLW* pl) {
    s16 j;
    for (j = 0; j < CMD_SLOTS; j++) {
        if (wcp[pl->wu.id].waza_flag[j] != -1) {
            waza_work[pl->wu.id][j].w_type = 0;
        }
    }
}

