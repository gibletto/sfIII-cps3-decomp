/*
 * spgauge.c  Super art gauge display
 *
 * Draws and animates the super art gauge for both players on the text layer.
 * spgauge_cont_init (and spgauge_cont_demo_init for attract mode) set each player's gauge work
 * from the chosen super art: stock count, gauge length and colour. spgauge_cont_main runs every
 * frame and calls spgauge_control per player, which follows the player's stock and gauge value,
 * plays the gauge sound and starts the stock flash (samoji_control) or, at full stock, the MAX
 * lettering (sast_control). Timed super arts show the TIME lettering (sa_time_moji_send).
 * wipe_check restores the gauge after a screen wipe, and the *_trans routines write the gauge
 * cells, frame, stock digits and lettering.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sc_clear.h"
#include "PLMAIN.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "spgauge.h"
#include "fighter.h"

/* spg_dat[pl].max_rno: the gauge flash when a stock is gained (sast_control, samoji_control) */
#define SPG_MAX_START   0       /* a stock was gained: show it and start the flash */
#define SPG_MAX_FLASH   1       /* flash the gauge for timer */
#define SPG_MAX_IDLE    2       /* nothing to do */

/* spg_dat[pl].time_rno: the gauge of a timer-type art (samoji_control) */
#define SPG_TIME_FLASH  0       /* flash until the stock changes */
#define SPG_TIME_SHOW   1       /* show the timer letters */
#define SPG_TIME_DRAIN  2       /* while the art drains the gauge */

void sc_chr_sheet_trans();
void scfont_sqput();
void scfont_fill();
void sc_celllist_put_scr(u8 ix);
void max_mark_chr_trans(s8 pl, s16 n);
void sa_stock_chr_trans(s8 pl, s16 n);
s32 tilemap_put_cell(u16 x, u16 y, u16 attr, u16 code);

extern const u16 spgauge_postbl_0[];
extern const u16 spgauge_postbl_1[];
extern const u16 spgauge_postbl_0_2[];
extern const u16 spgauge_postbl_1_2[];
extern const u16 spgauge_puttbl_0[];
extern const u16 spgauge_puttbl_1[];

s8 Old_Stop_SG;  /* 0201DB24 */
s8 Exec_Wipe_F;  /* 0201DB25 */
s8 time_clear[2];  /* 0201DB26 */
s16 spg_number;  /* 0201DB28 */
s16 spg_work;  /* 0201DB2A */
s16 spg_offset;  /* 0201DB2C */
s8 time_num;  /* 0201DB2E */
s8 time_timer;  /* 0201DB2F */
s8 time_flag;  /* 0201DB30 */
s16 col;  /* 0201DB32 */
SPG_DAT spg_dat[2];  /* 0201DB34 */


/* 020067E8 */
const u16* spgauge_puttbl[2] = {
    spgauge_puttbl_0,
    spgauge_puttbl_1,
};
/* 020067F0 */
const u16* spgauge_postbl[4] = {
    spgauge_postbl_0,
    spgauge_postbl_1,
    spgauge_postbl_0_2,
    spgauge_postbl_1_2,
};


void spgauge_cont_init(void) {
    time_flag = 0;
    spg_dat[0].current_spg = 0;
    spg_dat[0].old_spg = 0;
    spg_dat[0].spgcol_number = 28;
    spg_dat[0].spgtbl_ptr = spgauge_puttbl[0];
    spg_dat[0].spg_level = 0;
    spg_dat[0].spg_maxlevel = super_arts[0].store_max;
    spg_dat[0].spg_len = super_arts[0].gauge_len / 8;
    spg_dat[0].spg_dotlen = super_arts[0].gauge_len;
    spg_dat[0].flag = 0;
    spg_dat[0].flag2 = 0;
    spg_dat[0].timer = 50;
    spg_dat[0].timer2 = 2;
    spg_dat[0].kind = 0;
    spg_dat[0].max = 0;
    spg_dat[0].max_old = 0;
    spg_dat[0].max_rno = SPG_MAX_START;
    spg_dat[0].time_rno = SPG_TIME_FLASH;
    sa_gauge_flash[0] = 0;
    if (super_arts[0].gauge_type == SA_GAUGE_TIMER) {
        spg_dat[0].time = 1;
        time_flag = 1;
    } else {
        spg_dat[0].time = 0;
    }
    spg_dat[1].current_spg = 0;
    spg_dat[1].old_spg = 0;
    spg_dat[1].spgcol_number = 156;
    spg_dat[1].spgtbl_ptr = spgauge_puttbl[0];
    spg_dat[1].spg_level = 0;
    spg_dat[1].spg_maxlevel = super_arts[1].store_max;
    spg_dat[1].spg_len = super_arts[1].gauge_len / 8;
    spg_dat[1].spg_dotlen = super_arts[1].gauge_len;
    spg_dat[1].flag = 0;
    spg_dat[1].flag2 = 0;
    spg_dat[1].timer = 50;
    spg_dat[1].timer2 = 2;
    spg_dat[1].kind = 0;
    spg_dat[1].max = 0;
    spg_dat[1].max_old = 0;
    spg_dat[1].max_rno = SPG_MAX_START;
    spg_dat[1].time_rno = SPG_TIME_FLASH;
    sa_gauge_flash[1] = 0;
    if (super_arts[1].gauge_type == SA_GAUGE_TIMER) {
        spg_dat[1].time = 1;
        time_flag = 1;
    } else {
        spg_dat[1].time = 0;
    }
    if (Game_setting.mode == 0) {
        spg_dat[0].spgptbl_ptr = spgauge_postbl[0];
        spg_dat[1].spgptbl_ptr = spgauge_postbl[1];
    } else {
        spg_dat[0].spgptbl_ptr = spgauge_postbl[2];
        spg_dat[1].spgptbl_ptr = spgauge_postbl[3];
    }
    sa_stock_trans(0, 28, 0);
    sa_stock_trans(0, 28, 1);
    sc_celllist_put_scr(4);
    sc_celllist_put_scr(5);
    sa_gauge_trans(0, 28);
    sa_gauge_trans(1, 28);
    sa_waku_trans(0, 0);
    sa_waku_trans(1, 1);
    Old_Stop_SG = 0;
    Exec_Wipe_F = 0;
    time_clear[0] = 0;
    time_clear[1] = 0;
    spg_offset = 0;
    time_num = 0;
    time_timer = 4;
    col = 0;
}

void spgauge_cont_demo_init(void) {
    time_flag = 0;
    demo_set_sa_full(&super_arts[0]);
    spg_dat[0].current_spg = super_arts[0].gauge_len;
    spg_dat[0].old_spg = super_arts[0].gauge_len;
    spg_dat[0].spgcol_number = 30;
    spg_dat[0].spgtbl_ptr = spgauge_puttbl[0];
    spg_dat[0].spg_level = super_arts[0].store;
    spg_dat[0].spg_maxlevel = super_arts[0].store_max;
    spg_dat[0].spg_len = super_arts[0].gauge_len / 8;
    spg_dat[0].spg_dotlen = super_arts[0].gauge_len;
    spg_dat[0].flag = 0;
    spg_dat[0].flag2 = 0;
    spg_dat[0].timer = 50;
    spg_dat[0].timer2 = 2;
    spg_dat[0].kind = 1;
    spg_dat[0].max = 1;
    spg_dat[0].max_old = 0;
    spg_dat[0].max_rno = SPG_MAX_IDLE;
    spg_dat[0].time_rno = SPG_TIME_FLASH;
    sa_gauge_flash[0] = 0;
    if (super_arts[0].gauge_type == SA_GAUGE_TIMER) {
        spg_dat[0].time = 1;
        time_flag = 1;
    } else {
        spg_dat[0].time = 0;
    }
    demo_set_sa_full(&super_arts[1]);
    spg_dat[1].current_spg = super_arts[1].gauge_len;
    spg_dat[1].old_spg = super_arts[1].gauge_len;
    spg_dat[1].spgcol_number = 158;
    spg_dat[1].spgtbl_ptr = spgauge_puttbl[0];
    spg_dat[1].spg_level = super_arts[1].store;
    spg_dat[1].spg_maxlevel = super_arts[1].store_max;
    spg_dat[1].spg_len = super_arts[1].gauge_len / 8;
    spg_dat[1].spg_dotlen = super_arts[1].gauge_len;
    spg_dat[1].flag = 0;
    spg_dat[1].flag2 = 0;
    spg_dat[1].timer = 50;
    spg_dat[1].timer2 = 2;
    spg_dat[1].kind = 1;
    spg_dat[1].max = 1;
    spg_dat[1].max_old = 0;
    spg_dat[1].max_rno = SPG_MAX_IDLE;
    spg_dat[1].time_rno = SPG_TIME_FLASH;
    sa_gauge_flash[1] = 0;
    if (super_arts[1].gauge_type == SA_GAUGE_TIMER) {
        spg_dat[1].time = 1;
        time_flag = 1;
    } else {
        spg_dat[1].time = 0;
    }
    if (Game_setting.mode == 0) {
        spg_dat[0].spgptbl_ptr = spgauge_postbl[0];
        spg_dat[1].spgptbl_ptr = spgauge_postbl[1];
    } else {
        spg_dat[0].spgptbl_ptr = spgauge_postbl[2];
        spg_dat[1].spgptbl_ptr = spgauge_postbl[3];
    }
    sc_celllist_put_scr(4);
    sc_celllist_put_scr(5);
    sa_gauge_trans(0, 30);
    sa_gauge_trans(1, 30);
    max_mark_chr_trans(0, spg_dat[0].spg_maxlevel);
    sa_moji_trans(0, 0, 1);
    max_mark_chr_trans(1, spg_dat[1].spg_maxlevel);
    sa_moji_trans(1, 0, 1);
    sa_waku_trans(0, 0);
    sa_waku_trans(1, 1);
    Old_Stop_SG = 0;
    Exec_Wipe_F = 0;
    time_clear[0] = 0;
    time_clear[1] = 0;
    spg_offset = 0;
    time_num = 0;
    time_timer = 4;
    col = 30;
}

void spgauge_cont_main(void) {
    if (Stop_SG) {
        wipe_check();
        Old_Stop_SG = Stop_SG;
        return;
    } else {
        if (Old_Stop_SG) {
            Old_Stop_SG = 0;
            Exec_Wipe_F = 0;
            time_clear[0] = 0;
            time_clear[1] = 0;
        }
        sa_time_moji_send();
        spgauge_control(0);
        spgauge_control(1);
    }
}

void spgauge_control(s8 Spg_Num) {
    if (plw[Spg_Num].sa->store != spg_dat[Spg_Num].spg_level || sa_gauge_flash[Spg_Num] == 1) {
        spg_dat[Spg_Num].flag = 1;
        spgauge_sound_request(Spg_Num);
        sast_color_chenge(Spg_Num);
        if (plw[Spg_Num].sa->store == plw[Spg_Num].sa->store_max) {
            spg_dat[Spg_Num].max = 1;
        } else {
            spg_dat[Spg_Num].max = 0;
        }
        spg_dat[Spg_Num].max_rno = SPG_MAX_START;
        spg_dat[Spg_Num].timer = 50;
        spg_dat[Spg_Num].timer2 = 2;
        spg_dat[Spg_Num].kind = 0;
        if (plw[Spg_Num].sa->store < spg_dat[Spg_Num].spg_level) {
            spg_dat[Spg_Num].flag2 = 1;
        } else {
            spg_dat[Spg_Num].spg_level = plw[Spg_Num].sa->store;
        }
        sa_gauge_flash[Spg_Num] = 0;
    }
    if (spg_dat[Spg_Num].max) {
        sast_control(Spg_Num);
    } else if (spg_dat[Spg_Num].flag) {
        if (spg_dat[Spg_Num].max_old) {
            sa_moji_trans(Spg_Num, 0, 0);
        }
        samoji_control(Spg_Num);
    }
    spg_dat[Spg_Num].max_old = spg_dat[Spg_Num].max;
    if (spg_dat[Spg_Num].current_spg == plw[Spg_Num].sa->gauge.s.h && spg_dat[Spg_Num].flag == 0 && spg_dat[Spg_Num].max == 0) {
        return;
    }
    if (spg_dat[Spg_Num].max) {
        spg_dat[Spg_Num].current_spg = spg_dat[Spg_Num].spg_dotlen;
        sa_color_chenge(Spg_Num, 0);
    } else {
        spg_dat[Spg_Num].current_spg = plw[Spg_Num].sa->gauge.s.h;
        if (spg_dat[Spg_Num].flag) {
            sa_color_chenge(Spg_Num, 0);
        }
    }
    sa_waku_trans(Spg_Num, Spg_Num);
}

void wipe_check(void) {
    u16 x;
    if (Old_Stop_SG) {
        if (Exec_Wipe != 0 || Exec_Wipe_F != 0) {
            return;
        }
        Exec_Wipe_F = 1;
        if (spg_dat[0].time == 1 && time_clear[0] == 1) {
            spgauge_work_clear(0);
            x = 0;
            if (Game_setting.mode != 0) {
                x = 1;
            }
            tilemap_clear_rect(x, 25, x + 3, 27);
            spgauge_wipe_write(0);
        }
        if (spg_dat[1].time == 1 && time_clear[1] == 1) {
            spgauge_work_clear(1);
            x = 44;
            if (Game_setting.mode != 0) {
                x = 57;
            }
            tilemap_clear_rect(x, 25, x + 3, 27);
            spgauge_wipe_write(1);
        }
    } else {
        if (plw[0].sa->ok == -1) {
            plw[0].sa->ok = 0;
            time_clear[0] = 1;
        }
        if (plw[1].sa->ok == -1) {
            plw[1].sa->ok = 0;
            time_clear[1] = 1;
        }
    }
}

void sa_time_moji_send(void) {
    time_timer--;
    if (time_timer == 0) {
        sc_chr_sheet_trans(sa_time_data_tbl[0][time_num], 0xBA, 3, 2);
        if (time_flag) {
            sc_chr_sheet_trans(sa_time_data_tbl[1][time_num], 0x120, 4, 2);
        }
        time_timer = 4;
        if (time_num == 5) {
            time_num = 0;
        } else {
            time_num++;
        }
    }
}

void sast_control(Stpl_Num)
s8 Stpl_Num;
{
    switch (spg_dat[Stpl_Num].max_rno) {
    case SPG_MAX_START:
        max_mark_chr_trans(Stpl_Num, spg_dat[Stpl_Num].spg_maxlevel);
        sa_moji_trans(Stpl_Num, 0, 1);
        spg_dat[Stpl_Num].max_rno = SPG_MAX_FLASH;
        break;
    case SPG_MAX_FLASH:
        spg_dat[Stpl_Num].timer--;
        if (spg_dat[Stpl_Num].timer) {
            spg_dat[Stpl_Num].timer2--;
            if (spg_dat[Stpl_Num].kind == 0) {
                if (spg_dat[Stpl_Num].timer2 == 0) {
                    sa_lv_mark_trans(Stpl_Num, 8);
                    sa_gauge_trans(Stpl_Num, 28);
                    spg_dat[Stpl_Num].kind = 1;
                    spg_dat[Stpl_Num].timer2 = 2;
                }
            } else if (spg_dat[Stpl_Num].timer2 == 0) {
                sa_lv_mark_trans(Stpl_Num, 10);
                sa_gauge_trans(Stpl_Num, 30);
                spg_dat[Stpl_Num].kind = 0;
                spg_dat[Stpl_Num].timer2 = 2;
            }
        } else {
            sa_lv_mark_trans(Stpl_Num, 10);
            sa_gauge_trans(Stpl_Num, 30);
            spg_dat[Stpl_Num].kind = 1;
            spg_dat[Stpl_Num].timer2 = 2;
            spg_dat[Stpl_Num].max_rno = SPG_MAX_IDLE;
        }
        break;
    case SPG_MAX_IDLE:
        break;
    }
}

void samoji_control(Stpl_Num)
s8 Stpl_Num;
{
    if (spg_dat[Stpl_Num].time) {
        switch (spg_dat[Stpl_Num].time_rno) {
        case SPG_TIME_FLASH:
            if (plw[Stpl_Num].sa->store == spg_dat[Stpl_Num].spg_level) {
                spg_dat[Stpl_Num].timer2--;
                if (spg_dat[Stpl_Num].kind == 0) {
                    if (spg_dat[Stpl_Num].timer2 == 0) {
                        sa_stock_trans(spg_dat[Stpl_Num].spg_level, 28, Stpl_Num);
                        sa_gauge_trans(Stpl_Num, 28);
                        spg_dat[Stpl_Num].kind = 1;
                        spg_dat[Stpl_Num].timer2 = 2;
                    }
                } else if (spg_dat[Stpl_Num].timer2 == 0) {
                    sa_stock_trans(spg_dat[Stpl_Num].spg_level, 30, Stpl_Num);
                    sa_gauge_trans(Stpl_Num, 30);
                    spg_dat[Stpl_Num].kind = 0;
                    spg_dat[Stpl_Num].timer2 = 2;
                }
            } else {
                spg_dat[Stpl_Num].time_rno++;
            }
            break;
        case SPG_TIME_SHOW:
            sa_moji_trans(Stpl_Num, 1, 1);
            spg_dat[Stpl_Num].time_rno++;
        case SPG_TIME_DRAIN:
            if (spg_dat[Stpl_Num].current_spg > 0 && plw[Stpl_Num].sa->ok == -1) {
                spg_dat[Stpl_Num].timer2--;
                if (spg_dat[Stpl_Num].kind == 0) {
                    if (spg_dat[Stpl_Num].timer2 == 0) {
                        spg_dat[Stpl_Num].kind = 1;
                        spg_dat[Stpl_Num].timer2 = 2;
                    }
                } else if (spg_dat[Stpl_Num].timer2 == 0) {
                    spg_dat[Stpl_Num].kind = 0;
                    spg_dat[Stpl_Num].timer2 = 2;
                }
            } else {
                sa_moji_trans(Stpl_Num, 1, 0);
                sast_color_chenge(Stpl_Num);
                spg_dat[Stpl_Num].spg_level = plw[Stpl_Num].sa->store;
                sa_stock_trans(spg_dat[Stpl_Num].spg_level, col, Stpl_Num);
                sa_gauge_trans(Stpl_Num, col);
                sa_waku_trans(Stpl_Num, Stpl_Num);
                spg_dat[Stpl_Num].flag = 0;
                spg_dat[Stpl_Num].time_rno = SPG_TIME_FLASH;
                spg_dat[Stpl_Num].flag2 = 0;
            }
            break;
        }
    } else if (spg_dat[Stpl_Num].flag2 == 0) {
        spg_dat[Stpl_Num].timer--;
        if (spg_dat[Stpl_Num].timer) {
            spg_dat[Stpl_Num].timer2--;
            if (spg_dat[Stpl_Num].kind == 0) {
                if (spg_dat[Stpl_Num].timer2 == 0) {
                    sa_stock_trans(spg_dat[Stpl_Num].spg_level, 28, Stpl_Num);
                    sa_gauge_trans(Stpl_Num, 28);
                    spg_dat[Stpl_Num].kind = 1;
                    spg_dat[Stpl_Num].timer2 = 2;
                }
            } else if (spg_dat[Stpl_Num].timer2 == 0) {
                sa_stock_trans(spg_dat[Stpl_Num].spg_level, 30, Stpl_Num);
                sa_gauge_trans(Stpl_Num, 30);
                spg_dat[Stpl_Num].kind = 0;
                spg_dat[Stpl_Num].timer2 = 2;
            }
        } else {
            sast_color_chenge(Stpl_Num);
            spg_dat[Stpl_Num].spg_level = plw[Stpl_Num].sa->store;
            sa_stock_trans(spg_dat[Stpl_Num].spg_level, col, Stpl_Num);
            sa_gauge_trans(Stpl_Num, col);
            sa_waku_trans(Stpl_Num, Stpl_Num);
            spg_dat[Stpl_Num].flag = 0;
        }
    } else if (plw[Stpl_Num].sa->store == spg_dat[Stpl_Num].spg_level) {
        spg_dat[Stpl_Num].timer2--;
        if (spg_dat[Stpl_Num].kind == 0) {
            if (spg_dat[Stpl_Num].timer2 == 0) {
                sa_stock_trans(spg_dat[Stpl_Num].spg_level, 28, Stpl_Num);
                sa_gauge_trans(Stpl_Num, 28);
                spg_dat[Stpl_Num].kind = 1;
                spg_dat[Stpl_Num].timer2 = 2;
            }
        } else if (spg_dat[Stpl_Num].timer2 == 0) {
            sa_stock_trans(spg_dat[Stpl_Num].spg_level, 30, Stpl_Num);
            sa_gauge_trans(Stpl_Num, 30);
            spg_dat[Stpl_Num].kind = 0;
            spg_dat[Stpl_Num].timer2 = 2;
        }
    } else {
        sast_color_chenge(Stpl_Num);
        spg_dat[Stpl_Num].spg_level = plw[Stpl_Num].sa->store;
        sa_stock_trans(spg_dat[Stpl_Num].spg_level, col, Stpl_Num);
        sa_gauge_trans(Stpl_Num, col);
        sa_waku_trans(Stpl_Num, Stpl_Num);
        spg_dat[Stpl_Num].flag = 0;
        spg_dat[Stpl_Num].flag2 = 0;
    }
}

void sast_color_chenge(pl)
s8 pl;
{
    if (plw[pl].sa->store) {
        col = 30;
        if (pl == 0) {
            spg_dat[0].spgcol_number = 30;
        } else {
            spg_dat[1].spgcol_number = 158;
        }
    } else {
        col = 28;
        if (pl == 0) {
            spg_dat[0].spgcol_number = 28;
        } else {
            spg_dat[1].spgcol_number = 156;
        }
    }
}

void sa_color_chenge(pl, step)
s8 pl;
s8 step;
{
    SPG_DAT* p0;
    SPG_DAT* p1;
    s16 twice;
    p0 = &spg_dat[0],
        p0 = &spg_dat[0],
        twice = step * 2,
        p1 = &spg_dat[1];
    if (spg_dat[pl].kind) {
        if (pl == 0) {
            p0->spgcol_number = twice + 28;
        } else {
            p1->spgcol_number = twice + 156;
        }
    } else {
        if (pl == 0) {
            p0->spgcol_number = 30 - twice;
        } else {
            p1->spgcol_number = 158 - twice;
        }
    }
}

void sa_stock_trans(n, ix, pl)
s16 n;
s16 ix;
s8 pl;
{
    u16 x;
    if (pl == 0) {
        sa_stock_chr_trans(0, n);
        x = 2;
        if (Game_setting.mode != 0) {
            x = 3;
        }
        tilemap_put_cell(x, 25, ix - 20, 0xD0);
        tilemap_put_cell(x + 1, 25, ix - 20, 0xD1);
        tilemap_put_cell(x, 26, ix - 20, 0xD2);
        tilemap_put_cell(x + 1, 26, ix - 20, 0xD3);
        sa_gauge_end_trans(pl, x, ix);
    } else {
        sa_stock_chr_trans(1, n);
        x = 44;
        if (Game_setting.mode != 0) {
            x = 57;
        }
        tilemap_put_cell(x, 25, ix - 20, 0xE0);
        tilemap_put_cell(x + 1, 25, ix - 20, 0xE1);
        tilemap_put_cell(x, 26, ix - 20, 0xE2);
        tilemap_put_cell(x + 1, 26, ix - 20, 0xE3);
        sa_gauge_end_trans(pl, x, ix);
    }
}

void sa_moji_trans(Stpl_Num, Kind, OnOff)
s8 Stpl_Num;
s8 Kind;
s8 OnOff;
{
    u16 x;
    if (Stpl_Num == 0) {
        x = 2 - Kind;
        if (Game_setting.mode != 0) {
            x++;
        }
    } else {
        x = 43;
        if (Game_setting.mode != 0) {
            x = 56;
        }
    }
    switch (Kind) {
    case 0:
        if (OnOff) {
            scfont_sqput(x, 26, 3, 2, 8, 0xBA);
            scfont_fill(x, 25, 4, 1, 8, 32);
            sa_lv_mark_put(Stpl_Num, x, 10);
        } else if (Stpl_Num == 0) {
            tilemap_clear_rect(x - 2, 25, x + 2, 27);
        } else {
            tilemap_clear_rect(x, 25, x + 4, 27);
        }
        break;
    case 1:
    default:
        if (OnOff) {
            scfont_sqput(x, 26, 4, 2, 8, 0x120);
            scfont_fill(x + 1, 25, 2, 1, 8, 32);
        } else {
            tilemap_clear_rect(x, 26, x + 3, 27);
        }
        break;
    }
}

/* provisional name: the MAX level marks beside the stock digit, in the given colour */
void sa_lv_mark_trans(pl, attr)
s8 pl;
s16 attr;
{
    u16 x;
    if (pl == 0) {
        x = 2;
        if (Game_setting.mode != 0) {
            x = 3;
        }
    } else {
        x = 43;
        if (Game_setting.mode != 0) {
            x = 56;
        }
    }
    sa_lv_mark_put(pl, x, attr);
}

/* provisional name */
void sa_lv_mark_put(pl, x, attr)
s8 pl;
s8 x;
s16 attr;
{
    if (pl == 0) {
        tilemap_put_cell(x - 2, 25, attr, 0xD0);
        tilemap_put_cell(x - 1, 25, attr, 0xD1);
        tilemap_put_cell(x - 2, 26, attr, 0xD2);
        tilemap_put_cell(x - 1, 26, attr, 0xD3);
        tilemap_put_cell(x - 2, 27, attr, 0xD4);
        tilemap_put_cell(x - 1, 27, attr, 0xD5);
    } else {
        tilemap_put_cell(x + 3, 25, attr, 0xE0);
        tilemap_put_cell(x + 4, 25, attr, 0xE1);
        tilemap_put_cell(x + 3, 26, attr, 0xE2);
        tilemap_put_cell(x + 4, 26, attr, 0xE3);
        tilemap_put_cell(x + 3, 27, attr, 0xE4);
        tilemap_put_cell(x + 4, 27, attr, 0xE5);
    }
}

/* provisional name: the gauge end cells next to the stock digit (flipped for player 2) */
void sa_gauge_end_trans(pl, x, attr)
s8 pl;
s8 x;
s16 attr;
{
    if (pl == 0) {
        tilemap_put_cell(x, 27, attr, 0x124);
        tilemap_put_cell(x + 1, 27, attr, 0x125);
        tilemap_put_cell(x + 2, 27, attr, 0x125);
        tilemap_put_cell(x + 2, 25, attr, 32);
        tilemap_put_cell(x + 2, 26, attr, 0x12C);
    } else {
        tilemap_put_cell(x + 1, 27, attr + 0x80, 0x124);
        tilemap_put_cell(x - 1, 27, attr + 0x80, 0x125);
        tilemap_put_cell(x, 27, attr + 0x80, 0x125);
        tilemap_put_cell(x - 1, 25, attr + 0x80, 32);
        tilemap_put_cell(x - 1, 26, attr + 0x80, 0x12C);
    }
}

void sa_waku_trans(s8 pl_kind, s8 pl) {
    s8 i;
    s16 len;
    const u16* sa_char_ptr;
    SPG_DAT* spg;
    spg_work = 0;
    spg_number = 0;
    sa_char_ptr = spgauge_puttbl[0];
    if (Game_setting.mode == 0) {
    }
    len = super_arts[pl_kind].gauge_len / 8;
    i = 0;
    spg = &spg_dat[pl_kind];
    for (; i < len; i++) {
        spg_work += 8;
        if (spg_work >= spg->current_spg) {
            if (spg->current_spg >= (spg_work - 8)) {
                spg_offset = spg->current_spg - (i * 8);
                tilemap_put_cell((&spg->spgptbl_ptr[spg_number])[16 - len],
                                 26,
                                 spg->spgcol_number - 20,
                                 sa_char_ptr[spg_offset]);
            } else {
                tilemap_put_cell(
                    (&spg->spgptbl_ptr[spg_number])[16 - len], 26, spg->spgcol_number - 20, sa_char_ptr[0]);
            }
        } else {
            tilemap_put_cell((&spg_dat[pl_kind].spgptbl_ptr[spg_number])[16 - len], 26, spg_dat[pl_kind].spgcol_number - 20, sa_char_ptr[8]);
        }
        spg_number++;
    }
}

void spgauge_sound_request(Stpl_Num)
s8 Stpl_Num;
{
    if (plw[Stpl_Num].sa->store > spg_dat[Stpl_Num].spg_level) {
        Sound_SE(Stpl_Num + 107);
    }
}

void spgauge_work_clear(s8 Stpl_Num) {
    SPG_DAT* spg;
    plw[Stpl_Num].sa->gauge.i = 0;
    spg = &spg_dat[Stpl_Num];
    spg->current_spg = 0;
    spg->old_spg = 0;
    spg->spgcol_number = 28;
    spg->spg_level = 0;
    spg->flag = 0;
    spg->flag2 = 0;
    spg->timer = 50;
    spg->timer2 = 2;
    spg->kind = 0;
    spg->max = 0;
    spg->max_old = 0;
    spg->max_rno = SPG_MAX_START;
    spg->time_rno = SPG_TIME_FLASH;
    sa_gauge_flash[Stpl_Num] = 0;
    sa_color_chenge(Stpl_Num, 1);
}

void satime_stock_clear(void) {
    if (spg_dat[0].time == 1 && plw[0].sa->ok == -1) {
        sa_stock_chr_trans(0, 0);
    }
    if (spg_dat[1].time == 1 && plw[1].sa->ok == -1) {
        sa_stock_chr_trans(1, 0);
    }
}

void spgauge_wipe_write(s8 Stpl_Num) {
    u16 x;
    if (Stpl_Num == 0) {
        x = 0;
        if (Game_setting.mode != 0) {
            x = 1;
        }
        tilemap_put_cell(x, 25, 8, 32);
        tilemap_put_cell(x + 1, 25, 8, 32);
        tilemap_put_cell(x, 26, 8, 32);
        tilemap_put_cell(x + 1, 26, 8, 32);
        tilemap_put_cell(x + 2, 25, 8, 0xD0);
        tilemap_put_cell(x + 3, 25, 8, 0xD1);
        tilemap_put_cell(x + 2, 26, 8, 0xD2);
        tilemap_put_cell(x + 3, 26, 8, 0xD3);
        sa_gauge_end_trans(Stpl_Num, x + 2, 28);
    } else {
        x = 44;
        if (Game_setting.mode != 0) {
            x = 57;
        }
        tilemap_put_cell(x, 25, 8, 0xE0);
        tilemap_put_cell(x + 1, 25, 8, 0xE1);
        tilemap_put_cell(x, 26, 8, 0xE2);
        tilemap_put_cell(x + 1, 26, 8, 0xE3);
        tilemap_put_cell(x + 2, 25, 8, 32);
        tilemap_put_cell(x + 3, 25, 8, 32);
        tilemap_put_cell(x + 2, 26, 8, 32);
        tilemap_put_cell(x + 3, 26, 8, 32);
        sa_gauge_end_trans(Stpl_Num, x, 28);
    }
    sa_waku_trans(Stpl_Num, Stpl_Num);
    sa_gauge_trans(Stpl_Num, 28);
}

void sa_gauge_trans(Stpl_Num, Spg_Col)
s8 Stpl_Num;
s16 Spg_Col;
{
    s8 lpy;
    if (Stpl_Num == 0) {
        for (lpy = 0; lpy < 5; lpy++) {
            tilemap_put_cell(DE_X[13] + lpy + 5, 27, Spg_Col, lpy + 0x126);
        }
        for (lpy = 0; lpy < spg_dat[0].spg_len - 5; lpy++) {
            tilemap_put_cell(DE_X[13] + lpy + 10, 27, Spg_Col, 0x12B);
        }
        tilemap_put_cell(DE_X[13] + lpy + 10, 26, Spg_Col, 0xB9);
        tilemap_put_cell(DE_X[13] + lpy + 10, 27, Spg_Col, 0xC9);
    } else {
        for (lpy = 0; lpy < 5; lpy++) {
            tilemap_put_cell(DE_X[12] - lpy + 42, 27, Spg_Col + 0x80, lpy + 0x126);
        }
        for (lpy = 0; lpy < spg_dat[1].spg_len - 5; lpy++) {
            tilemap_put_cell(DE_X[12] - lpy + 37, 27, Spg_Col + 0x80, 0x12B);
        }
        tilemap_put_cell(DE_X[12] - lpy + 37, 26, Spg_Col + 0x80, 0xB9);
        tilemap_put_cell(DE_X[12] - lpy + 37, 27, Spg_Col + 0x80, 0xC9);
    }
}
