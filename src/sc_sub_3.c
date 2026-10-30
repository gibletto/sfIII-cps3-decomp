/*
 * SC_SUB_3.C  Stun gauge control and drawing
 *
 * The gauges use attributes 2 (1P) and 0x82 (2P), the stun marks 4 and 0x84, the empty frame cell 0x10F.
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

extern const u16 stngauge_postbl_0[];
extern const u16 stngauge_postbl_0_2[];
extern const u16 stngauge_postbl_1[];
extern const u16 stngauge_postbl_1_2[];
extern const u16 stngauge_puttbl_0[];
extern const u16 stngauge_puttbl_1[];

s16 stn_number;  /* 0202407C */
s16 stn_work;  /* 0202407E */
s16 stn_offset;  /* 02024080 */
STN_DAT sdat[2];  /* 02024084 */


/* 020078E8 */
const u16* stngauge_puttbl[2] = {
    stngauge_puttbl_0,
    stngauge_puttbl_1,
};
/* 020078F0: one pair of gauge positions per Game_setting.Screen_Mode */
const u16* stngauge_postbl[4] = {
    stngauge_postbl_0,
    stngauge_postbl_1,
    stngauge_postbl_0_2,
    stngauge_postbl_1_2,
};


void stun_mark_put(s8 pl);



/* colours 18/146, gauge positions by Game_setting.Screen_Mode */
void stngauge_cont_init(void) {
    sdat[0].cstn = 0;
    sdat[0].ostn = 0;
    sdat[0].stncol_number = 2;
    sdat[0].stntbl_ptr = stngauge_puttbl[0];
    sdat[0].sflag = 0;
    sdat[0].osflag = 0;
    sdat[0].g_or_s = 0;
    sdat[0].stimer = 2;
    sdat[0].slen = piyori_type[0].genkai / 8;
    sdat[0].dotlen = piyori_type[0].genkai;
    sdat[0].proccess_dead = 0;
    sdat[1].cstn = 0;
    sdat[1].ostn = 0;
    sdat[1].stncol_number = 0x82;
    sdat[1].stntbl_ptr = stngauge_puttbl[0];
    sdat[1].sflag = 0;
    sdat[1].osflag = 0;
    sdat[1].g_or_s = 0;
    sdat[1].stimer = 2;
    sdat[1].slen = piyori_type[1].genkai / 8;
    sdat[1].dotlen = piyori_type[1].genkai;
    sdat[1].proccess_dead = 0;
    if (Game_setting.Screen_Mode == 0) {
        sdat[0].stnptbl_ptr = stngauge_postbl[0];
        sdat[1].stnptbl_ptr = stngauge_postbl[1];
    } else {
        sdat[0].stnptbl_ptr = stngauge_postbl[2];
        sdat[1].stnptbl_ptr = stngauge_postbl[3];
    }
    stun_gauge_waku_write(0);
    stun_gauge_waku_write(1);
    stun_mark_write(0, 0);
    stun_mark_write(1, 1);
}



/* no gauge_stop_flag */
void stngauge_cont_main(void) {
    if (EXE_flag == 0) {
        stngauge_control(0);
        stngauge_control(1);
    }
}



void stngauge_control(s32 player) {
    s8 pl = player;
    if (Exec_Wipe != 0) {
        sdat[pl].cstn = plw[pl].py->now.quantity.h;
        return;
    }
    if (sdat[pl].proccess_dead) {
        return;
    }
    if (plw[pl].dead_flag) {
        sdat[pl].proccess_dead = 1;
        sdat[pl].cstn = 0;
        stun_put(pl);
        return;
    }
    if ((plw[pl].wu.routine_no[1] == PLAYER_DAMAGE && plw[pl].wu.routine_no[2] == DAMAGE_STUN && plw[pl].wu.routine_no[3] != 0) ||
        plw[pl].py->flag == 1) {
        sdat[pl].sflag = 1;
        if (sdat[pl].osflag == 0) {
            sdat[pl].cstn = stun_genkai_tbl[My_char[pl] & 0x7F];
        }
        sdat[pl].stimer--;
        if (sdat[pl].g_or_s == 0) {
            if (sdat[pl].stimer == 0) {
                stun_mark_put(pl);
                sdat[pl].g_or_s = 1;
                sdat[pl].stimer = 2;
            }
        } else if (sdat[pl].stimer == 0) {
            stun_put(pl);
            sdat[pl].g_or_s = 0;
            sdat[pl].stimer = 2;
        }
        sdat[pl].osflag = sdat[pl].sflag;
        return;
    }
    sdat[pl].sflag = 0;
    if (sdat[pl].osflag == 1) {
        sdat[pl].osflag = sdat[pl].sflag;
        sdat[pl].g_or_s = 0;
        sdat[pl].stimer = 2;
        sdat[pl].cstn = plw[pl].py->now.quantity.h;
        sdat[pl].osflag = sdat[pl].sflag;
        stun_put(pl);
        return;
    }
    if (sdat[pl].cstn != plw[pl].py->now.quantity.h) {
        sdat[pl].cstn = plw[pl].py->now.quantity.h;
        stun_put(pl);
    }
}



void stun_put(pl)
s8 pl;
{
    s8 i;
    stn_work = 0;
    stn_number = 0;
    for (i = 0; i < sdat[pl].slen; i++) {
        stn_work += 8;
        if (stn_work >= sdat[pl].cstn) {
            if (sdat[pl].cstn >= stn_work - 8) {
                stn_offset = sdat[pl].cstn - i * 8;
                tilemap_put_cell((s16)sdat[pl].stnptbl_ptr[stn_number], 3, sdat[pl].stncol_number, (s16)sdat[pl].stntbl_ptr[stn_offset]);
            } else {
                tilemap_put_cell((s16)sdat[pl].stnptbl_ptr[stn_number], 3, sdat[pl].stncol_number, (s16)sdat[pl].stntbl_ptr[0]);
            }
        } else {
            tilemap_put_cell((s16)sdat[pl].stnptbl_ptr[stn_number], 3, sdat[pl].stncol_number, *(s16*)(sdat[pl].stntbl_ptr + 8));
        }
        stn_number++;
    }
}



/* attributes 4 and 132; the Game_setting.Screen_Mode test has empty arms */
void stun_mark_write(s8 pl, s8 kind) {
    const u16* cells;
    s16 attr;
    PiyoriType* pt;
    STN_DAT* g;
    s8 i;
    stn_work = 0;
    stn_number = 0;
    if (pl == 1 && kind == 0) {
        ToneDown(7);
    }
    attr = 4;
    if (kind == 2) {
        cells = stngauge_puttbl[1];
    } else {
        cells = stngauge_puttbl[pl - kind];
    }
    if (kind == 1 && pl == 1) {
        attr = 132;
    }
    if (Game_setting.Screen_Mode == 0) {
    } else {
    }
    pt = &piyori_type[pl];
    g = &sdat[pl];
    for (i = 0; i < pt->genkai / 8; i++) {
        stn_work += 8;
        if (stn_work >= g->cstn) {
            if (g->cstn >= stn_work - 8) {
                stn_offset = g->cstn - i * 8;
                tilemap_put_cell(g->stnptbl_ptr[stn_number], 3, attr, cells[stn_offset]);
            } else {
                tilemap_put_cell(g->stnptbl_ptr[stn_number], 3, attr, cells[0]);
            }
        } else {
            tilemap_put_cell(g->stnptbl_ptr[stn_number], 3, attr, cells[8]);
        }
        stn_number++;
    }
}



/* frame by Game_setting.Screen_Mode, attribute 34, no end cell */
void stun_gauge_waku_write(s8 pl) {
    s8 i;
    if (Game_setting.Screen_Mode == 0) {
        if (pl == 0) {
            for (i = 0; i < 9 - sdat[0].slen; i++) {
                tilemap_put_cell(i + 12, 3, 2, 0x10F);
            }
        } else {
            for (i = 0; i < 9 - sdat[1].slen; i++) {
                tilemap_put_cell(35 - i, 3, 0x82, 0x10F);
            }
        }
    } else {
        if (pl == 0) {
            for (i = 0; i < 9 - sdat[0].slen; i++) {
                tilemap_put_cell(i + 19, 3, 2, 0x10F);
            }
        } else {
            for (i = 0; i < 9 - sdat[1].slen; i++) {
                tilemap_put_cell(42 - i, 3, 0x82, 0x10F);
            }
        }
    }
}



void stngauge_work_clear(void) {
    sdat[0].cstn = 0;
    sdat[0].ostn = 0;
    sdat[0].sflag = 0;
    sdat[0].osflag = 0;
    sdat[0].g_or_s = 0;
    sdat[0].stimer = 2;
    sdat[0].proccess_dead = 0;
    stun_mark_write(0, 0);
    sdat[1].cstn = 0;
    sdat[1].ostn = 0;
    sdat[1].sflag = 0;
    sdat[1].osflag = 0;
    sdat[1].g_or_s = 0;
    sdat[1].stimer = 2;
    sdat[1].proccess_dead = 0;
    stun_mark_write(1, 1);
}
