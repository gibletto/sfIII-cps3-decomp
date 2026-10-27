/*
 * SC_SUB_2.C  Palette fade control
 *
 * Routines: fade_cont_init, fade_cont_main.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "sc_trans.h"
#include "sc_sub_2.h"
#include "cps3.h"

/* fade_cont_rno: the colour fade (fade_cont_main) */
#define FADE_RUN        0       /* step each layer's colours until all are done */
#define FADE_END        1       /* wait fade_end_timer, then clear the fade */




extern const u16 fade_adrs_tbl_0[];
extern const u16 fade_adrs_tbl_1[];
extern const u16 fade_adrs_tbl_10[];
extern const u16 fade_adrs_tbl_11[];
extern const u16 fade_adrs_tbl_12[];
extern const u16 fade_adrs_tbl_13[];
extern const u16 fade_adrs_tbl_14[];
extern const u16 fade_adrs_tbl_15[];
extern const u16 fade_adrs_tbl_16[];
extern const u16 fade_adrs_tbl_17[];
extern const u16 fade_adrs_tbl_18[];
extern const u16 fade_adrs_tbl_19[];
extern const u16 fade_adrs_tbl_2[];
extern const u16 fade_adrs_tbl_20[];
extern const u16 fade_adrs_tbl_21[];
extern const u16 fade_adrs_tbl_22[];
extern const u16 fade_adrs_tbl_23[];
extern const u16 fade_adrs_tbl_25[];
extern const u16 fade_adrs_tbl_26[];
extern const u16 fade_adrs_tbl_27[];
extern const u16 fade_adrs_tbl_28[];
extern const u16 fade_adrs_tbl_3[];
extern const u16 fade_adrs_tbl_4[];
extern const u16 fade_adrs_tbl_5[];
extern const u16 fade_adrs_tbl_6[];
extern const u16 fade_adrs_tbl_7[];
extern const u16 fade_adrs_tbl_8[];
extern const u16 fade_adrs_tbl_9[];

s8 fade_layer_num;  /* 02028718 */
s16 fade_cont_rno;  /* 0202871A */
s8 fade_end_timer;  /* 0202871C */
FADE_LAYER fade_layer[7];  /* 02028720 */


/* 020069D8 */
u32 fade_adrs_tbl[29] = {
    (u32)((const u8*)fade_adrs_tbl_0),
    (u32)((const u8*)fade_adrs_tbl_1),
    (u32)((const u8*)fade_adrs_tbl_2),
    (u32)((const u8*)fade_adrs_tbl_3),
    (u32)((const u8*)fade_adrs_tbl_4),
    (u32)((const u8*)fade_adrs_tbl_5),
    (u32)((const u8*)fade_adrs_tbl_6),
    (u32)((const u8*)fade_adrs_tbl_7),
    (u32)((const u8*)fade_adrs_tbl_8),
    (u32)((const u8*)fade_adrs_tbl_9),
    (u32)((const u8*)fade_adrs_tbl_10),
    (u32)((const u8*)fade_adrs_tbl_11),
    (u32)((const u8*)fade_adrs_tbl_12),
    (u32)((const u8*)fade_adrs_tbl_13),
    (u32)((const u8*)fade_adrs_tbl_14),
    (u32)((const u8*)fade_adrs_tbl_15),
    (u32)((const u8*)fade_adrs_tbl_16),  /* Dedicated table for fade 16. */
    (u32)((const u8*)fade_adrs_tbl_17),
    (u32)((const u8*)fade_adrs_tbl_18),
    (u32)((const u8*)fade_adrs_tbl_19),
    (u32)((const u8*)fade_adrs_tbl_20),
    (u32)((const u8*)fade_adrs_tbl_21),
    (u32)((const u8*)fade_adrs_tbl_22),
    (u32)((const u8*)fade_adrs_tbl_23),
    (u32)((const u8*)fade_adrs_tbl_22),
    (u32)((const u8*)fade_adrs_tbl_25),
    (u32)((const u8*)fade_adrs_tbl_26),
    (u32)((const u8*)fade_adrs_tbl_27),
    (u32)((const u8*)fade_adrs_tbl_28),
};


void fade_cont_init(void) {
    const s16* tbl;
    const s16* dat;
    s8 i;
    s8 num;
    fade_layer_num = 0;
    fade_cont_rno = 0;
    fade_end_timer = 1;
    tbl = fade_data_tbl[Fade_Number];
    num = *tbl;
    fade_layer_num = num;
    tbl++;
    for (i = 0; i < num; i++) {
        fade_layer[i].adrs = fade_adrs_tbl[tbl[0]];
        fade_layer[i].cur = fade_layer[i].adrs;
        dat = fade_param_tbl[tbl[1]];
        fade_layer[i].count = dat[0];
        fade_layer[i].r = dat[1];
        fade_layer[i].g = fade_layer[i].r;
        fade_layer[i].b = fade_layer[i].r;
        fade_layer[i].target = dat[2];
        fade_layer[i].kind = dat[3];
        fade_layer[i].timer = dat[4];
        fade_layer[i].interval = fade_layer[i].timer;
        fade_layer[i].speed = dat[5];
        fade_layer[i].on = 1;
        switch (fade_layer[i].kind) {
        case 0:
        case 1:
            fade_layer[i].step = 64;
            break;
        case 2:
        case 3:
            fade_layer[i].step = 96;
            break;
        }
        if (0) {
            dat = fade_param_tbl[tbl[1]];
        }
        tbl += 2;
    }
}

s32 fade_cont_main(void)
{
    u16 j;
    s8 i;
    s8 done;
    FADE_LAYER* fl;

    switch (fade_cont_rno) {
    case FADE_RUN:
        for (i = 0; i < fade_layer_num; i += 1) {
            if (0) {
                fade_layer_num = 0;
            }
            if (fade_layer[i].on != 0) {
                fade_layer[i].timer--;
                if (fade_layer[i].timer == 0) {
                    fade_layer[i].timer = fade_layer[i].interval;
                    fl = &fade_layer[i];
                    for (j = 0; j < fl->count; j++) {
                        load_any_color_req(*(u32 *)fl->adrs, fl->r + fl->step, fl->g + fl->step, fl->b + fl->step);
                        fl->adrs += 4;
                    }
                    if (fade_layer[i].r == fade_layer[i].target) {
                        fade_layer[i].on = 0;
                    } else {
                        fade_layer[i].adrs = fade_layer[i].cur;
                        fade_layer[i].r += fade_layer[i].speed;
                        fade_layer[i].g = fade_layer[i].r;
                        fade_layer[i].b = fade_layer[i].r;
                        switch (fade_layer[i].kind) {
                        case 0:
                        case 2:
                            if (fade_layer[i].r < fade_layer[i].target) {
                                fl = &fade_layer[i];
                                fl->r = fl->target;
                                fl->g = fl->r;
                                fl->b = fl->r;
                            }
                            break;
                        case 1:
                        case 3:
                            fl = &fade_layer[i];
                            if (fl->r > fl->target) {
                                fl = &fade_layer[i];
                                fl->r = fl->target;
                                fl->g = fl->r;
                                fl->b = fl->r;
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
        done = 0;
        for (i = 0; i < fade_layer_num; i++) {
            if (fade_layer[i].on == 0) {
                done++;
            }
        }
        if (done == fade_layer_num) {
            fade_cont_rno = FADE_END;
        }
        break;
    case FADE_END:
        fade_end_timer--;
        if (fade_end_timer != 0) {
            break;
        }
        Fade_Flag = 0;
        Fade_Mode = 0;
        break;
    }
}
