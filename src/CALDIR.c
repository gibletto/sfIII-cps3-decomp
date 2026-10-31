/*
 * CALDIR.C  Direction and trajectory calculation library
 *
 * caldir_pos_128/64/32/16/8 return the direction from one point to another in 128, 64, 32,
 * 16 or 8 steps; caldir_wk_* do the same between two works' display positions.
 * cal_move_quantity* project a work's position a number of frames ahead from its speed and
 * acceleration. The cmsd_* and cal_*_speed routines work out initial speeds and
 * accelerations so that a work reaches a given point in a given number of frames
 * (cal_all_speed_data, cal_initial_speed, cal_delta_speed, cal_initial_speed_y0), and
 * cal_top_of_position_y / cal_time_of_sign_change / cal_move_dir_forecast predict the top
 * of a jump and its timing.
 * Used by effects and stage objects that fly to target positions.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CALDIR.h"

s32 caldir_pos_256(x1, x2, y1, y2)
s16 x1;
s16 x2;
s16 y1;
s16 y2;
{
    s16 yhan;
    s16 tent = yhan = 0;
    switch (((y1 -= x1) < 0) + (((y2 -= x2) < 0) << 1)) {
    case 1:
        y1 = -y1;
        yhan = 1;
        break;
    case 2:
        y2 = -y2;
        yhan = 1;
        tent = 0x80;
        break;
    case 3:
        y1 = -y1;
        y2 = -y2;
        tent = 0x80;
        break;
    }
    if (y1 > y2) {
        while (y1 > 0x7F) {
            y1 >>= 1;
            y2 >>= 1;
        }
    } else {
        while (y2 > 0x7F) {
            y1 >>= 1;
            y2 >>= 1;
        }
    }
    tent += dir_sel_table[y1][y2];
    if (yhan) {
        tent = -tent;
        tent &= 0xFF;
    }
    return tent;
}



/* provisional name */
s16 caldir_pos_128(s16 x1, s16 x2, s16 y1, s16 y2) {
    return caldir_pos_256(x1, x2, y1, y2) >> 1;
}



s16 caldir_pos_064(s16 x1, s16 x2, s16 y1, s16 y2) {
    return (caldir_pos_256(x1, x2, y1, y2) + 2) >> 2 & 0x3F;
}



s16 caldir_pos_032(x1, x2, y1, y2)
s16 x1;
s16 x2;
s16 y1;
s16 y2;
{
    return (caldir_pos_256(x1, x2, y1, y2) + 4) >> 3 & 0x1F;
}



s16 caldir_pos_016(s16 x1, s16 x2, s16 y1, s16 y2) {
    return (caldir_pos_256(x1, x2, y1, y2) + 8) >> 4 & 0xF;
}



s16 caldir_pos_008(s16 x1, s16 x2, s16 y1, s16 y2) {
    return (caldir_pos_256(x1, x2, y1, y2) + 16) >> 5 & 7;
}



/* provisional name: unreferenced */
s32 caldir_wk_256(WORK* wk, WORK* emwk) {
    return caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos, emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos);
}



/* provisional name */
s16 caldir_wk_128(WORK* wk, WORK* emwk) {
    return caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos, emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos) >> 1;
}



s16 caldir_wk_064(WORK* wk, WORK* emwk) {
    return (caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos,
                           emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos) + 2) >> 2 & 0x3F;
}



s16 caldir_wk_032(WORK* wk, WORK* emwk) {
    return (caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos,
                           emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos) + 4) >> 3 & 0x1F;
}



s16 caldir_wk_016(WORK* wk, WORK* emwk) {
    return (caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos,
                           emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos) + 8) >> 4 & 0xF;
}



s16 caldir_wk_008(WORK* wk, WORK* emwk) {
    return (caldir_pos_256(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos,
                           emwk->xyz[0].disp.pos, emwk->xyz[1].disp.pos) + 16) >> 5 & 7;
}



/* provisional name */
void add_pos_dir_256(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction][RATE_Y] * sp) >> 8;
}



/* provisional name */
void add_pos_dir_128(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction * 2][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction * 2][RATE_Y] * sp) >> 8;
}



void add_pos_dir_064(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction * 4][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction * 4][RATE_Y] * sp) >> 8;
}



/* provisional name */
void add_pos_dir_032(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction * 8][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction * 8][RATE_Y] * sp) >> 8;
}



/* provisional name */
void add_pos_dir_016(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction * 16][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction * 16][RATE_Y] * sp) >> 8;
}



/* provisional name */
void add_pos_dir_008(WORK* wk, s16 sp) {
    wk->xyz[0].cal += (rate_256_table[wk->direction * 32][RATE_X] * sp) >> 8;
    wk->xyz[1].cal += (rate_256_table[wk->direction * 32][RATE_Y] * sp) >> 8;
}



/* provisional name */
s16 dir256_to_128(s16 dir) {
    return dir >> 1;
}



/* provisional name */
s16 dir256_to_064(s16 dir) {
    return (dir + 2) >> 2 & 0x3F;
}



/* provisional name */
s16 dir256_to_032(s16 dir) {
    return (dir + 4) >> 3 & 0x1F;
}



/* provisional name */
s16 dir256_to_016(s16 dir) {
    return (dir + 8) >> 4 & 0xF;
}



/* provisional name */
s16 dir256_to_008(s16 dir) {
    return (dir + 16) >> 5 & 7;
}



/* provisional name */
s16 cal_move_quantity(WORK* wk, s16 t) {
    XY pos[2];
    s32 time;
    if (t == 0) {
        return 0;
    }
    time = t;
    pos[0].cal = time * time / 2 * wk->mvxy.d[0].sp;
    pos[0].cal = wk->mvxy.a[0].sp * time + pos[0].cal + wk->xyz[0].cal;
    pos[1].cal = time * time / 2 * wk->mvxy.d[1].sp;
    pos[1].cal = wk->mvxy.a[1].sp * time + pos[1].cal + wk->xyz[1].cal;
    return cal_move_quantity2(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos, pos[0].disp.pos, pos[1].disp.pos);
}


s16 cal_move_quantity2(s16 x1, s16 x2, s16 y1, s16 y2) {
    s16 kakudo;
    MS ms;
    if ((y1 -= x1) < 0) {
        y1 = -y1;
    }
    if ((y2 -= x2) < 0) {
        y2 = -y2;
    }
    x1 = y1;
    x2 = y2;
    if (y1 > y2) {
        while (y1 > 0x7F) {
            y1 >>= 1;
            y2 >>= 1;
        }
    } else {
        while (y2 > 0x7F) {
            y1 >>= 1;
            y2 >>= 1;
        }
    }
    kakudo = dir_sel_table[y1][y2];
    ms.psi = x1 * rate_256_table[kakudo][RATE_X];
    ms.psi += x2 * rate_256_table[kakudo][RATE_Y];
    return ms.pss.h;
}


s16 cal_move_quantity3(WORK* wk, s16 tm) {
    s32 ltm;
    PS_DY ps;
    if (tm == 0) {
        return wk->xyz[1].disp.pos;
    }
    ltm = tm;
    ps.dy = ltm * ltm / 2 * wk->mvxy.d[1].sp;
    ps.dy = wk->mvxy.a[1].sp * ltm + ps.dy + wk->xyz[1].cal;
    return ps.ry.h;
}


/* provisional name */
void cal_move_quantity_dummy(void) {}



void cmsd_all_x_speed_data(MotionState* cc) {
    switch (cc->swx) {
    case 1:
        cmsd_swx_1(cc);
        break;
    case 2:
        cmsd_swx_2(cc);
        break;
    default:
        cmsd_swx_0(cc);
        break;
    }
}



void cmsd_all_y_speed_data(MotionState* cc) {
    switch (cc->swy) {
    case 1:
        cmsd_swy_1(cc);
        break;
    case 2:
        cmsd_swy_2(cc);
        break;
    default:
        cmsd_swy_0(cc);
        break;
    }
}



void cmsd_swx_0(MotionState* cc) {
    cc->amx = cc->x.pl % cc->timer;
    cc->spx = cc->x.pl / cc->timer;
    cc->dlx = 0;
}



void cmsd_swy_0(MotionState* cc) {
    cc->amy = cc->y.pl % cc->timer;
    cc->spy = cc->y.pl / cc->timer;
    cc->dly = 0;
}



void cmsd_swx_1(MotionState* cc) {
    cc->amx = cc->x.pl % cc->timer2;
    cc->spx = cc->dlx = cc->x.pl / cc->timer2;
}



void cmsd_swy_1(MotionState* cc) {
    cc->amy = cc->y.pl % cc->timer2;
    cc->spy = cc->dly = cc->y.pl / cc->timer2;
}



void cmsd_swx_2(MotionState* cc) {
    cc->amx = cc->x.pl % cc->timer2;
    cc->dlx = cc->x.pl / cc->timer2;
    cc->spx = cc->dlx * cc->timer;
    cc->dlx = -cc->dlx;
}



void cmsd_swy_2(MotionState* cc) {
    cc->amy = cc->y.pl % cc->timer2;
    cc->dly = cc->y.pl / cc->timer2;
    cc->spy = cc->dly * cc->timer;
    cc->dly = -cc->dly;
}



void cmsd_x_initial_speed(MotionState* cc) {
    cc->amx = cc->x.pl - (cc->timer2 * cc->dlx);
    cc->spx = cc->dlx + (cc->amx / cc->timer);
    cc->amx %= cc->timer;
}



void cmsd_y_initial_speed(MotionState* cc) {
    cc->amy = cc->y.pl - cc->timer2 * cc->dly;
    cc->spy = cc->amy / cc->timer + cc->dly;
    cc->amy %= cc->timer;
}



void cmsd_x_delta_speed(MotionState* cc) {
    if (cc->spx != 0) {
        cc->amx = cc->x.pl - cc->timer * cc->spx;
        cc->dlx = cc->amx / cc->timer2;
        cc->amx %= cc->timer2;
        cc->spx += cc->dlx;
    } else {
        cmsd_all_x_speed_data(cc);
    }
}



void cmsd_y_delta_speed(MotionState* cc) {
    if (cc->spy != 0) {
        cc->amy = cc->y.pl - (cc->timer * cc->spy);
        cc->dly = cc->amy / cc->timer2;
        cc->amy %= cc->timer2;
        cc->spy += cc->dly;
    } else {
        cmsd_all_y_speed_data(cc);
    }
}



void cal_all_speed_data(wk, tm, x1, y1, xsw, ysw)
WORK* wk;
s16 tm;
s16 x1;
s16 y1;
s8 xsw;
s8 ysw;
{
    MotionState bb;
    wk->xyz[0].disp.low = wk->xyz[1].disp.low = 0;
    bb.timer = tm;
    bb.timer2 = bb.timer + bb.timer * (bb.timer - 1) / 2;
    bb.x.ps.h = x1 - wk->xyz[0].disp.pos;
    bb.y.ps.h = y1 - wk->xyz[1].disp.pos;
    bb.x.ps.l = bb.y.ps.l = 0;
    bb.swx = xsw;
    bb.swy = ysw;
    if (bb.timer == 0) {
        bb.amy = 0;
        bb.amx = 0;
        bb.dly = 0;
        bb.spy = 0;
        bb.dlx = 0;
        bb.spx = 0;
    } else {
        cmsd_all_x_speed_data(&bb);
        cmsd_all_y_speed_data(&bb);
    }
    wk->mvxy.a[0].sp = bb.spx;
    wk->mvxy.d[0].sp = bb.dlx;
    wk->mvxy.a[1].sp = bb.spy;
    wk->mvxy.d[1].sp = bb.dly;
    wk->xyz[0].cal += bb.amx;
    wk->xyz[1].cal += bb.amy;
    wk->mvxy.kop[0] = wk->mvxy.kop[1] = 0;
}



void cal_initial_speed(wk, tm, x1, y1)
WORK* wk;
s16 tm;
s16 x1;
s16 y1;
{
    MotionState bb;
    wk->xyz[0].disp.low = wk->xyz[1].disp.low = 0;
    bb.timer = tm;
    bb.timer2 = bb.timer + bb.timer * (bb.timer - 1) / 2;
    bb.x.ps.h = x1 - wk->xyz[0].disp.pos;
    bb.y.ps.h = y1 - wk->xyz[1].disp.pos;
    bb.x.ps.l = bb.y.ps.l = 0;
    bb.dlx = wk->mvxy.d[0].sp;
    bb.dly = wk->mvxy.d[1].sp;
    if (bb.timer == 0) {
        bb.amy = 0;
        bb.amx = 0;
        bb.spy = 0;
        bb.spx = 0;
    } else {
        cmsd_x_initial_speed(&bb);
        cmsd_y_initial_speed(&bb);
    }
    wk->mvxy.a[0].sp = bb.spx;
    wk->mvxy.a[1].sp = bb.spy;
    wk->xyz[0].cal += bb.amx;
    wk->xyz[1].cal += bb.amy;
}



void cal_initial_speed_y(WORK* wk, s16 tm, s16 y1) {
    MotionState bb;
    wk->xyz[1].disp.low = 0;
    bb.timer = tm + 0;
    bb.timer2 = bb.timer + bb.timer * (bb.timer - 1) / 2;
    bb.y.ps.h = y1 - wk->xyz[1].disp.pos;
    bb.y.ps.l = 0;
    bb.dly = wk->mvxy.d[1].sp;
    if (bb.timer == 0) {
        bb.amy = 0;
        bb.spy = 0;
    } else {
        cmsd_y_initial_speed(&bb);
    }
    wk->mvxy.a[1].sp = bb.spy;
    wk->xyz[1].cal += bb.amy;
}



void cal_delta_speed(wk, tm, x1, y1, xsw, ysw)
WORK* wk;
s16 tm;
s16 x1;
s16 y1;
s8 xsw;
s8 ysw;
{
    MotionState bb;
    wk->xyz[0].disp.low = wk->xyz[1].disp.low = 0;
    bb.timer = tm + 0;
    bb.timer2 = bb.timer + bb.timer * (bb.timer - 1) / 2;
    bb.x.ps.h = x1 - wk->xyz[0].disp.pos;
    bb.y.ps.h = y1 - wk->xyz[1].disp.pos;
    bb.x.ps.l = bb.y.ps.l = 0;
    bb.swx = xsw;
    bb.swy = ysw;
    bb.spx = wk->mvxy.a[0].sp;
    bb.spy = wk->mvxy.a[1].sp;
    if (bb.timer == 0) {
        bb.amy = 0;
        bb.amx = 0;
        bb.dly = 0;
        bb.dlx = 0;
    } else {
        cmsd_x_delta_speed(&bb);
        cmsd_y_delta_speed(&bb);
    }
    wk->mvxy.a[0].sp = bb.spx;
    wk->mvxy.d[0].sp = bb.dlx;
    wk->mvxy.a[1].sp = bb.spy;
    wk->mvxy.d[1].sp = bb.dly;
    wk->xyz[0].cal += bb.amx;
    wk->xyz[1].cal += bb.amy;
}



/* provisional name */
void cal_initial_speed_y0(WORK* wk, s16 tm) {
    MotionState bb;
    wk->xyz[0].disp.low = wk->xyz[1].disp.low = 0;
    bb.timer = tm;
    bb.timer2 = bb.timer + bb.timer * (bb.timer - 1) / 2;
    bb.y.ps.h = 0;
    bb.y.ps.l = 0;
    bb.dly = wk->mvxy.d[1].sp;
    if (bb.timer) {
        cmsd_y_initial_speed(&bb);
    } else {
        bb.spy = 0;
    }
    wk->mvxy.a[1].sp = bb.spy;
}



s16 cal_top_of_position_y(WORK* wk) {
    register s32 num;
    s32 num2;
    PS_UNI ps_uni;
    if ((num = cal_time_of_sign_change(wk)) == 0) {
        return wk->xyz[1].disp.pos;
    }
    num2 = num * (num - 1) / 2 + num;
    ps_uni.psy = num * wk->mvxy.a[1].sp + num2 * wk->mvxy.d[1].sp + wk->xyz[1].cal;
    return ps_uni.psys.h;
}



s32 cal_time_of_sign_change(WORK* wk) {
    s16 num;

    if (wk->mvxy.d[1].sp != 0) {
        num = wk->mvxy.a[1].sp / -wk->mvxy.d[1].sp;
        return num;
    }
    return 0;
}



s32 cal_move_dir_forecast(WORK* wk, s16 tm) {
    PS_DP ps[2];
    s32 time;
    s16 direction;
    if (tm == 0) {
        return 0;
    }
    time = tm;
    ps[0].dp = time * time / 2 * wk->mvxy.d[0].sp;
    ps[0].dp = wk->mvxy.a[0].sp * time + ps[0].dp + wk->xyz[0].cal;
    ps[1].dp = time * time / 2 * wk->mvxy.d[1].sp;
    ps[1].dp = wk->mvxy.a[1].sp * time + ps[1].dp + wk->xyz[1].cal;
    direction = caldir_pos_032(wk->xyz[0].disp.pos, wk->xyz[1].disp.pos, ps[0].rp.h, ps[1].rp.h);
    return direction;
}

