/*
 * END_SUB.C  Ending support: prize cards
 *
 * Card dispenser bookkeeping for the regions that give out cards: card_win_check counts wins per
 * player and requests a card when the required wins are reached; card_msg_disp blinks the "card won"
 * and "no cards" messages; card_work_clear / card_pl_work_clear reset the card work. The CD checks and
 * the staff roll are in end_sub_2.c.
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
#include "effh6_code.h"
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
#include "textsound_2.h"
#include "textsound_3.h"
#include "fifo.h"
#include "ta_sub2.h"
#include "tate00.h"
#include "ta_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub.h"
#include "cps3.h"

SELPL card_pl_w[2];  /* 0201D714 */
s16 card_msg_cnt;  /* 0201D72C */


#pragma inline(card_pl_work_clear)



/* provisional name */
void card_pl_work_clear(pl)
s16 pl;
{
    memset(&card_pl_w[pl], 0, 12);
}

/* provisional name */
u32 card_work_clear(void) {
    memset((u8 *)&card_pl_w[0], 0, sizeof(SELPL));
    return (u32)memset((u8 *)&card_pl_w[1], 0, sizeof(SELPL));
}

/* provisional name */
void card_win_check(s16 vs_mode) {
    s8 need;

    if (!Card_Dispenser) {
        return;
    }
    if (Country != 6 && Country != 5) {
        return;
    }
    if (Play_Type) {
        card_pl_work_clear(Loser_id);
        card_pl_w[Winner_id].vs_wins++;
        if (card_pl_w[Winner_id].cleared) {
            return;
        }
        if (card_pl_w[Winner_id].vs_wins >= Win_Point_Human) {
            card_pl_w[Winner_id].cleared++;
            card_out_req++;
            card_pl_w[Winner_id].flag = 1;
        }
    } else {
        if (vs_mode) {
            card_pl_w[Winner_id].cleared++;
            card_out_req++;
            card_pl_w[Winner_id].flag = 1;
        } else {
            need = Win_Point_Com - Continue_Coin[Winner_id];
            if (need < 0) {
                need = 1;
            }
            card_pl_w[Winner_id].wins++;
            if (!card_pl_w[Winner_id].cleared) {
                if (card_pl_w[Winner_id].wins >= need) {
                    card_pl_w[Winner_id].cleared++;
                    card_out_req++;
                    card_pl_w[Winner_id].flag = 1;
                }
            }
        }
        card_pl_work_clear(Loser_id);
    }
}


/* provisional name */
/* The card dispenser message, in text attribute 20. */
void card_msg_disp(void) {
    if (!Card_Dispenser) {
        return;
    }
    if (Country != 6 && Country != 5) {
        return;
    }
    switch (card_pl_w[Winner_id].card_state) {
    case 0:
        if (card_out_busy != 0 || card_empty_flag != -1) {
            break;
        }
        card_pl_w[Winner_id].card_state++;
        card_pl_w[Winner_id].blink = 0;
        /* fall through */
    case 1:
        switch (card_pl_w[Winner_id].blink & 0x1F) {
        case 0:
            tilemap_print_string_attr(21, Text_Page_Y + 6, 20, no_card_mes);
            break;
        case 15:
            tilemap_print_string_attr(21, Text_Page_Y + 6, 20, no_card_clr_mes);
            break;
        }
        if (card_out_busy == 0 && card_empty_flag != -1) {
            card_pl_w[Winner_id].msg_state = 0;
            card_pl_w[Winner_id].card_state = 0;
            tilemap_print_string_attr(21, Text_Page_Y + 6, 20, no_card_clr_mes);
            return;
        } else {
            card_pl_w[Winner_id].blink++;
            return;
        }
    }
    switch (card_pl_w[Winner_id].msg_state) {
    case 0:
        if (card_pl_w[Winner_id].flag == 0) {
            break;
        }
        card_pl_w[Winner_id].msg_state++;
        card_pl_w[Winner_id].msg_timer = -32;
        card_msg_cnt = -1;
        /* fall through */
    case 1:
        card_msg_cnt++;
        if (--card_pl_w[Winner_id].msg_timer == 0) {
            card_msg_cnt = 0;
            card_pl_w[Winner_id].msg_state = 0;
            tilemap_print_string_attr(18, Text_Page_Y + 6, 20, win_card_clr_mes);
            card_pl_w[Winner_id].flag = 0;
            break;
        }
        switch (card_msg_cnt & 0x3F) {
        case 0:
            tilemap_print_string_attr(18, Text_Page_Y + 6, 20, win_card_mes);
            break;
        case 31:
            tilemap_print_string_attr(18, Text_Page_Y + 6, 20, win_card_clr_mes);
            break;
        }
        break;
    }
}



