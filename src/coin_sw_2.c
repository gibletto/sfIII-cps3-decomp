/*
 * COIN_SW_2.C  Card dispenser control
 *
 * dispenser_init clears the card request and, with a card dispenser fitted (Card_Dispenser), the busy
 * state and the dispenser's output latch bit (set again if the dispenser reports a card under way).
 * dispenser_control runs every frame: it notes an empty dispenser (card_empty_flag), counts a card when
 * the dispenser reports it out (bookkeep_card_count) and starts the next requested card (card_out_req)
 * when the dispenser is ready.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "sys_config.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "cps3.h"



s16 card_out_req;  /* 0206AAC4 */
u16 card_out_busy;  /* 0206AAC6 */
u8 card_out_busy_tail[128];  /* after card_out_busy; nothing refers to it by name or address */


s32 card_empty_flag = 0;  /* 02007D3C */


/* provisional name */
void dispenser_init(void) {
    card_out_req = 0;
    if (Card_Dispenser != 0) {
        card_out_busy = 0;
        coin_out_latch &= ~4;
        if (card_sw_0 & 4) {
            card_out_busy = 4;
            coin_out_latch |= 4;
        }
    }
}



/* provisional name */
void dispenser_control(void) {
    if (Card_Dispenser == 0) {
        return;
    }
    if ((card_sw_0 & 0x20) == 0) {
        card_empty_flag = -1;
    } else {
        card_empty_flag = 0;
    }
    if (card_out_busy == 4) {
        if ((~card_sw_1 & card_sw_0) & 0x40) {
            bookkeep_card_count();      /* Count a completed card output. */
            card_out_busy = 0;
            coin_out_latch &= ~4;
        }
    } else {
        if (card_empty_flag == -1) {
            return;
        }
        if (card_out_req == 0) {
            return;
        }
        if (card_sw_0 & 1) {
            return;
        }
        card_out_req--;
        card_out_busy = 4;
        coin_out_latch |= 4;
    }
}
