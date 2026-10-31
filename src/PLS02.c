/*
 * PLS02.C  Movement data, body push, vitality and super art gauge rules
 *
 * The movement half: setup_mvxy_data, add_to_mvxy_data, cal_mvxy_speed and the add_mvxy_speed family
 * load and apply the per-move x/y speed and acceleration data; setup_butt_own_data sets up blow-away
 * movement; remake_mvxy_PoSB, setup_air_paring_mvxy and remake_mvxy_PoGR rescale the speeds after a hit
 * (the x speed of a blow-away scales by its size through mvxy_PoSB_scale, air_paring_scale and
 * mvxy_PoGR_scale). check_body_touch and meri_case_switch push the two bodies apart;
 * set_field_hosei_flag and check_work_position clamp a player to the screen. Then the CPU random helpers
 * and the guard and attack direction calculations.
 * The gauge half: setup_vitality (vitality 160) and cal_dm_vital_gauge_hosei, the add_sp_arts_gauge_*
 * rules and add_super_arts_gauge (super art and gauge amount), get_buttobi_attlv, the blow-away type and
 * lever direction helpers and the KO voice requests.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CALDIR.h"
#include "HITCHECK.h"
#include "se_3.h"
#include "PLS01.h"
#include "PLS02.h"
#include "PLSGAUGE.h"

s32 cal_move_quantity_dummy();   /* CALDIR's empty routine; get_buttobi_attlv2 uses what it leaves in r0 */


void add_to_mvxy_data(wk, ix)
WORK *wk;
u16 ix;
{
    s16* adrs;
    s32 sp;
    wk->mvxy.index = ix;
    adrs = &wk->move_xy_table[ix * 6];
    sp = adrs[0];
    sp *= 256;
    wk->mvxy.a[0].sp += sp;
    sp = adrs[1];
    sp *= 256;
    wk->mvxy.d[0].sp += sp;
    wk->mvxy.kop[0] = adrs[2];
    sp = adrs[3];
    sp *= 256;
    wk->mvxy.a[1].sp += sp;
    sp = adrs[4];
    sp *= 256;
    wk->mvxy.d[1].sp += sp;
    wk->mvxy.kop[1] = adrs[5];
}



void setup_mvxy_data(wk, ix)
WORK *wk;
u16 ix;
{
    wk->mvxy.index = ix;
    read_adrs_store_mvxy(wk, &wk->move_xy_table[ix * 6]);
}



/* Blow-away movement from parabora_ex_table, by the attacker's character and our weight. */
void setup_butt_own_data_ex(WORK* wk, s16 ix) {
    const s16* adrs;
    s16 pn;
    wk->mvxy.index = ix;
    pn = ((PLW*)wk->target_adrs)->player_number;
    adrs = parabora_ex_table[ix][pn][wk->weight_level][wk->dm_attlv];
    read_adrs_store_mvxy(wk, adrs);
}



/* As above, by our character and the attacker's weight. */
void setup_butt_own_data_ex2(WORK* wk, s16 ix) {
    const s16* adrs;
    u8 wl;
    wk->mvxy.index = ix;
    wl = ((WORK*)wk->target_adrs)->weight_level;
    adrs = parabora_ex_table[ix][((PLW*)wk)->player_number][wl][wk->dm_attlv];
    read_adrs_store_mvxy(wk, adrs);
}



void setup_butt_own_data(WORK* wk) {
    wk->mvxy.index = wk->dm_butt_type;
    read_adrs_store_mvxy(wk, parabora_own_table[wk->dm_plnum][wk->dm_butt_type].data[wk->weight_level]);
}



void read_adrs_store_mvxy(WORK* wk, const s16* adrs) {
    wk->mvxy.a[0].sp = adrs[0];
    wk->mvxy.a[0].sp <<= 8;
    wk->mvxy.d[0].sp = adrs[1];
    wk->mvxy.d[0].sp <<= 8;
    wk->mvxy.kop[0] = adrs[2];
    wk->mvxy.a[1].sp = adrs[3];
    wk->mvxy.a[1].sp <<= 8;
    wk->mvxy.d[1].sp = adrs[4];
    wk->mvxy.d[1].sp <<= 8;
    wk->mvxy.kop[1] = adrs[5];
}



s32 get_weight_point(WORK* wk) {
    return wk->dm_weight - wk->weight_level + 3;
}



void cal_mvxy_speed(WORK* wk) {
    s16 i;
    for (i = 0; i < 2; i++) {
        switch (wk->mvxy.kop[i]) {
        case 0:
            wk->mvxy.a[i].sp += wk->mvxy.d[i].sp;
            break;
        case 1:
            if (wk->mvxy.a[i].sp >= 0) {
                wk->mvxy.a[i].sp += wk->mvxy.d[i].sp;
                if (wk->mvxy.a[i].sp < 0) {
                    wk->mvxy.a[i].sp = wk->mvxy.d[i].sp = 0;
                }
            } else {
                wk->mvxy.a[i].sp += wk->mvxy.d[i].sp;
                if (wk->mvxy.a[i].sp >= 0) {
                    wk->mvxy.a[i].sp = wk->mvxy.d[i].sp = 0;
                }
            }
            break;
        }
    }
}



void add_mvxy_speed(WORK* wk) {
    if (wk->rl_flag) {
        wk->xyz[0].cal += wk->mvxy.a[0].sp;
    } else {
        wk->xyz[0].cal -= wk->mvxy.a[0].sp;
    }
    wk->xyz[1].cal += wk->mvxy.a[1].sp;
}



void add_mvxy_speed_no_use_rl(WORK* wk) {
    wk->xyz[0].cal += wk->mvxy.a[0].sp;
    wk->xyz[1].cal += wk->mvxy.a[1].sp;
}



void add_mvxy_speed_direct(WORK* wk, s16 sx, s16 sy) {
    s32 ax;
    s32 ay;
    ax = sx;
    ay = sy;
    ax <<= 8;
    if (wk->rl_flag) {
        wk->xyz[0].cal += ax;
    } else {
        wk->xyz[0].cal -= ax;
    }
    wk->xyz[1].cal += ay << 8;
}



void reset_mvxy_data(WORK* wk) {
    wk->mvxy.a[0].sp = wk->mvxy.d[0].sp = wk->mvxy.kop[0] = 0;
    wk->mvxy.a[1].sp = wk->mvxy.d[1].sp = wk->mvxy.kop[1] = 0;
}



/* provisional name: an empty routine the jumping attacks call on a hit */
void attack_hit_dummy(PLW* wk) {}



/* provisional name */
void remake_mvxy_dummy(void) {
    s16 sw = 0;
    switch (sw) {
    case 1:
        break;
    case 2:
        break;
    }
}



void remake_mvxy_PoSB(WORK* wk) {
    switch (((wk->mvxy.a[0].sp < 0) * 2) + (wk->mvxy.a[0].sp > 0)) {
    case 2:
        switch (((wk->mvxy.a[1].sp < 0) * 2) + (wk->mvxy.a[1].sp > 0)) {
        case 1:
            wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 70 / 100;
            break;
        default:
            wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 20 / 100;
            break;
        }
        wk->mvxy.a[0].sp = wk->mvxy.a[0].sp * 80 / 100;
        break;
    default:
        switch (((wk->mvxy.a[1].sp < 0) * 2) + (wk->mvxy.a[1].sp > 0)) {
        case 1:
            wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 70 / 100;
            break;
        default:
            wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 20 / 100;
            break;
        }
        if (*(s16*)&wk->mvxy.a[0] == 0) {
            *(s16*)&wk->mvxy.a[0] = 1;
        }
        if (*(s16*)&wk->mvxy.a[0] > 12) {
            *(s16*)&wk->mvxy.a[0] = 12;
        }
        wk->mvxy.a[0].sp = wk->mvxy.a[0].sp * mvxy_PoSB_scale[*(s16*)&wk->mvxy.a[0] - 1] / 100;
        wk->mvxy.d[0].sp = 0;
        wk->mvxy.a[0].sp = -wk->mvxy.a[0].sp;
        break;
    }
}



void setup_air_paring_mvxy(WORK* wk) {
    switch (((wk->mvxy.a[1].sp < 0) * 2) + (wk->mvxy.a[1].sp > 0)) {
    case 1:
        wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 120 / 100;
        break;
    default:
        wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 120 / 100;
        wk->mvxy.a[1].sp = -wk->mvxy.a[1].sp;
        break;
    }
    if (wk->mvxy.a[0].sp >= 0) {
        if (*(s16*)&wk->mvxy.a[0] == 0) {
            *(s16*)&wk->mvxy.a[0] = 1;
        }
        if (*(s16*)&wk->mvxy.a[0] > 12) {
            *(s16*)&wk->mvxy.a[0] = 12;
        }
        wk->mvxy.a[0].sp = wk->mvxy.a[0].sp * air_paring_scale[*(s16*)&wk->mvxy.a[0] - 1] / 100;
        wk->mvxy.d[0].sp = 0;
    }
    if (*(s16*)&wk->mvxy.a[1] > 12) {
        *(s16*)&wk->mvxy.a[1] = 12;
    }
}



void remake_mvxy_PoGR(WORK* wk) {
    switch (((wk->mvxy.a[0].sp < 0) * 2) + (wk->mvxy.a[0].sp > 0)) {
    case 2:
        if (wk->mvxy.d[1].sp) {
            switch (((wk->mvxy.a[1].sp < 0) * 2) + (wk->mvxy.a[1].sp > 0)) {
            case 1:
                wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 80 / 100;
                break;
            default:
                wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 30 / 100;
                break;
            }
        }
        wk->mvxy.a[0].sp = wk->mvxy.a[0].sp * 40 / 100;
        break;
    default:
        if (wk->mvxy.d[1].sp) {
            switch (((wk->mvxy.a[1].sp < 0) * 2) + (wk->mvxy.a[1].sp > 0)) {
            case 1:
                wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 80 / 100;
                break;
            default:
                wk->mvxy.a[1].sp = wk->mvxy.a[1].sp * 30 / 100;
                break;
            }
        }
        if (*(s16*)&wk->mvxy.a[0] == 0) {
            *(s16*)&wk->mvxy.a[0] = 1;
        }
        if (*(s16*)&wk->mvxy.a[0] > 12) {
            *(s16*)&wk->mvxy.a[0] = 12;
        }
        wk->mvxy.a[0].sp = wk->mvxy.a[0].sp * mvxy_PoGR_scale[*(s16*)&wk->mvxy.a[0] - 1] / 100;
        wk->mvxy.d[0].sp = 0;
        wk->mvxy.a[0].sp = -wk->mvxy.a[0].sp;
        break;
    }
}



void check_body_touch(void) {
    PLW* p1w = &plw[0];
    PLW* p2w = &plw[1];
    s16 meri;
    if (p1w->wu.h_hos->hos_box[0] != 0 && p2w->wu.h_hos->hos_box[0] != 0) {
        meri = hit_check_subroutine(&p1w->wu, &p2w->wu, &p1w->wu.h_hos->hos_box[0], &p2w->wu.h_hos->hos_box[0]);
        if (meri != 0) {
            meri = meri_case_switch(meri);
            if (check_work_position(&p1w->wu, &p2w->wu)) {
                goto one;
            }
            goto two;
        }
    }
    p1w->hos_em_flag = 0;
    p2w->hos_em_flag = 0;
    return;
one:
    p1w->wu.xyz[0].disp.pos += meri * (p1w->micchaku_flag != 1);
    p2w->wu.xyz[0].disp.pos -= meri * (p2w->micchaku_flag != 2);
    p1w->hos_em_flag = 2;
    p2w->hos_em_flag = 1;
    return;
two:
    p1w->wu.xyz[0].disp.pos -= meri * (p1w->micchaku_flag != 2);
    p2w->wu.xyz[0].disp.pos += meri * (p2w->micchaku_flag != 1);
    p1w->hos_em_flag = 1;
    p2w->hos_em_flag = 2;
}



s32 meri_case_switch(meri)
s16 meri;
{
    switch (meri & 0xFFF8) {
    case 0:
        if (meri > 3) {
            meri /= 4;
        } else {
            meri /= 2;
        }
        break;
    case 8:
        meri = (meri * 21) / 64;
        break;
    default:
        meri = (meri * 13) / 32;
        break;
    }
    return meri;
}



s32 set_field_hosei_flag(pl, pos, ix)
PLW* pl;
s16 pos;
s16 ix;
{
    s16 hami;
    if (ix != 0) {
        hami = pl->wu.xyz[0].disp.pos + satse[pl->player_number] - pos;
        if (hami) {
            if (hami < 0) {
                goto no_hosei;
            }
            pl->wu.xyz[0].disp.pos -= hami;
            pl->micchaku_flag = 1;
            pl->hos_fi_flag = 1;
            pl->hosei_amari = -hami;
        } else {
            pl->micchaku_flag = 1;
            pl->hos_fi_flag = 0;
            pl->hosei_amari = 0;
        }
    } else {
        hami = pl->wu.xyz[0].disp.pos - satse[pl->player_number] - pos;
        if (hami) {
            if (hami > 0) {
                goto no_hosei;
            }
            pl->wu.xyz[0].disp.pos -= hami;
            pl->micchaku_flag = 2;
            pl->hos_fi_flag = 2;
            pl->hosei_amari = -hami;
        } else {
            pl->micchaku_flag = 2;
            pl->hos_fi_flag = 0;
            pl->hosei_amari = 0;
        }
    }
    return 0;
no_hosei:
    pl->micchaku_flag = 0;
    pl->hos_fi_flag = 0;
    pl->hosei_amari = 0;
    return 1;
}



s32 check_work_position(WORK* p1, WORK* p2) {
    s16 r;
    s16 d = p1->xyz[0].disp.pos - p2->xyz[0].disp.pos;
    if (d) {
        if (d > 0) {
            r = 1;
        } else {
            r = 0;
        }
    } else if ((p1->rl_flag + p2->rl_flag) & 1) {
        if (p1->rl_flag) {
            r = 0;
        } else {
            r = 1;
        }
    } else {
        switch ((p1->xyz[1].disp.pos == 0) + (p2->xyz[1].disp.pos == 0) * 2) {
        case 1:
            if (p1->rl_flag) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        case 2:
            if (p2->rl_flag) {
                r = 0;
            } else {
                r = 1;
            }
            break;
        default:
            r = 0;
            break;
        }
    }
    return r;
}



s32 random_32_com(void) {
    Random_ix32_com++;
    Random_ix32_com &= 0x7F;
    return random_tbl_32_com[Random_ix32_com];
}



s32 random_16_com(void) {
    Random_ix16_com++;
    Random_ix16_com &= 0x3F;
    return random_tbl_16_com[Random_ix16_com];
}



/* Next value from the CPU's 32-entry extra random table. */
s32 random_32_ex_com(void) {
    Random_ix32_ex_com++;
    Random_ix32_ex_com &= 0x1F;
    return random_tbl_32_ex[Random_ix32_ex_com];
}



/* Next value from the CPU's 16-entry extra random table. */
s32 random_16_ex_com(void) {
    Random_ix16_ex_com++;
    Random_ix16_ex_com &= 0xF;
    return random_tbl_16_ex_com[Random_ix16_ex_com];
}



s32 get_guard_direction(WORK* as, WORK* ds) {
    s16 result;
    s8 num;
    if (as->work_id == 1) {
        result = as->xyz[0].disp.pos - ds->xyz[0].disp.pos;
        if (result) {
            if (result < 0) {
                if (ds->rl_flag) {
                    num = 1;
                } else {
                    num = 2;
                }
            } else if (ds->rl_flag) {
                num = 2;
            } else {
                num = 1;
            }
        } else {
            num = 3;
        }
    } else if (as->rl_flag + ds->rl_flag & 1) {
        num = 2;
    } else {
        num = 1;
    }
    return num;
}



s32 cal_attdir(WORK* wk) {
    s16 resdir = wk->att.dir;
    if (wk->rl_flag) {
        resdir = dir16_rl_conv[resdir];
    }
    return resdir;
}



s32 get_kind_of_head_dm(s16 dir, char rl) {
    if (rl == 0) {
        dir = dir16_rl_conv[dir];
    }
    return dir16_hddm[dir];
}



s32 get_kind_of_trunk_dm(s16 dir, char rl) {
    if (rl == 0) {
        dir = dir16_rl_conv[dir];
    }
    return dir16_trdm[dir];
}



void setup_vitality(WORK* wk, s16 pno) {
    s16 ix;
    if (wk->operator == 0) {
        ix = Game_setting.Difficulty + CC_Value[1];
    } else {
        ix = 2;
    }
    wk->original_vitality = Com_Vital_Unit_Data[pno][Game_setting.Damage_Level][ix];
    wk->dmcal_m = 32;
    wk->dmcal_d = wk->original_vitality * 32 / 160;
    wk->vitality = wk->vital_new = wk->vital_old = 160;
    wk->dm_vital = 0;
}



void cal_dm_vital_gauge_hosei(PLW* wk) {
    wk->wu.dm_vital = wk->wu.dm_vital * wk->wu.dmcal_m / wk->wu.dmcal_d;
    if (wk->wu.dm_vital <= 0) {
        wk->wu.dm_vital = 1;
    }
}



s16 get_sa_gauge_len(s16 id) {
    return plw[id].sa->gauge_len;
}



void set_hit_stop_hit_quake(WORK* wk) {
    if (wk->dm_stop) {
        wk->hit_stop = wk->dm_stop;
        wk->dm_stop = 0;
    }
    if (wk->dm_quake) {
        wk->hit_quake = wk->dm_quake;
        wk->dm_quake = 0;
    }
}



void add_sp_arts_gauge_init(PLW* wk) {
    PLW* mwk;
    s16 asag;
    if (wk->wu.work_id != 1) {
        mwk = (PLW*)wk->cp;
        if (mwk->wu.work_id == 1) {
            asag = add_arts_gauge[mwk->player_number][wk->wu.add_arts_point][0];
            add_super_arts_gauge(mwk->sa, asag);
        }
    } else {
        asag = add_arts_gauge[wk->player_number][wk->wu.add_arts_point][0];
        add_super_arts_gauge(wk->sa, asag);
    }
}



void add_sp_arts_gauge_guard(PLW* wk) {
    PLW* mwk;
    s16 asag;
    if (wk->wu.work_id != 1) {
        mwk = (PLW*)wk->cp;
        if (mwk->wu.work_id == 1) {
            asag = add_arts_gauge[mwk->player_number][wk->wu.add_arts_point][1];
            add_super_arts_gauge(mwk->sa, asag);
        }
    } else {
        asag = add_arts_gauge[wk->player_number][wk->wu.add_arts_point][1];
        add_super_arts_gauge(wk->sa, asag);
    }
}



void add_sp_arts_gauge_hit_dm(PLW* wk) {
    PLW* emwk;
    s16 asag;
    if (wk->wu.work_id != 1) {
        return;
    }
    emwk = (PLW*)wk->wu.target_adrs;
    asag = add_arts_gauge[emwk->player_number][wk->wu.dm_arts_point][2];
    if (asag != 0) {
        add_super_arts_gauge(wk->sa, asag / 4);
        if (emwk->wu.operator == 0) {
            if (Country & 2) {
                asag += asagh_zuru2[Game_setting.Difficulty];
            } else {
                asag += asagh_zuru[Game_setting.Difficulty];
            }
        }
        if (asag <= 0) {
            asag = 1;
        }
        add_super_arts_gauge(emwk->sa, asag);
    }
    wk->wu.dm_arts_point = 0;
}



/* provisional name */
void add_sp_arts_gauge_hit(PLW* wk) {
    PLW* mwk;
    s16 asag;
    if (wk->wu.work_id != 1) {
        mwk = (PLW*)wk->cp;
        if (mwk->wu.work_id == 1) {
            asag = add_arts_gauge[mwk->player_number][wk->wu.add_arts_point][2];
            add_super_arts_gauge(mwk->sa, asag);
        }
    } else {
        asag = add_arts_gauge[wk->player_number][wk->wu.add_arts_point][2];
        if (asag == 0) {
            return;
        }
        if (wk->wu.operator == 0) {
            if (Country & 2) {
                asag += asagh_zuru2[Game_setting.Difficulty];
            } else {
                asag += asagh_zuru[Game_setting.Difficulty];
            }
        }
        if (asag <= 0) {
            asag = 1;
        }
        add_super_arts_gauge(wk->sa, asag);
    }
}



void add_sp_arts_gauge_paring(PLW* wk) {
    PLW* emwk;
    s16 asag;
    if (wk->wu.work_id != 1) {
        return;
    }
    emwk = (PLW*)wk->wu.target_adrs;
    asag = add_arts_gauge[emwk->player_number][wk->wu.dm_arts_point][3];
    if (asag != 0) {
        if (wk->wu.operator == 0) {
            if (Country & 2) {
                asag += asagh_zuru2[Game_setting.Difficulty];
            } else {
                asag += asagh_zuru[Game_setting.Difficulty];
            }
        }
        if (asag <= 0) {
            asag = 1;
        }
        add_super_arts_gauge(wk->sa, asag);
    }
    wk->wu.dm_arts_point = 0;
}



s32 add_super_arts_gauge(wk, asag)
SA_WORK *wk;
s16 asag;
{
    if (!test_flag) {
        if (wk->ok == -1) {
            return 0;
        }
        if (pcon_dp_flag) {
            return 0;
        }
        if (wk->store == wk->store_max) {
            return 0;
        }
        if (Game_setting.Battle_Number == 0) {
            asag = asag * 150 / 100;
        }
        wk->gauge.s.h += asag;
        wk->gauge.s.l = -1;
        if (wk->gauge.s.h > wk->gauge_len) {
            wk->store += 1;
            if (wk->store < wk->store_max) {
                wk->gauge.s.h -= wk->gauge_len;
            } else {
                wk->store = wk->store_max;
                wk->gauge.i = 0;
            }
        }
    }
}



/* provisional name: the blow-away level whose flight time still lands */
s32 get_buttobi_attlv(PLW* wk) {
    s16 lv;
    s16 tm;
    for (lv = 3; lv > 0; lv--) {
        tm = cal_move_quantity3(&wk->wu, buttobi_time_table[wk->as->char_ix + lv]);
        if (tm < 0) {
        } else {
            break;
        }
    }
    return lv;
}



/* provisional name: as get_buttobi_attlv by cal_move_quantity_dummy; nothing calls it */
s32 get_buttobi_attlv2(PLW* wk) {
    s16 lv;
    s16 tm;
    if ((tm = cal_move_quantity_dummy(wk)) == 0) {
        return 0;
    }
    for (lv = 3; lv > 0; lv--) {
        if (tm >= buttobi_time_table[wk->as->char_ix + lv]) {
            break;
        }
    }
    return lv;
}



s16 check_buttobi_type(PLW* wk) {
    s16 rn;
    setup_butt_own_data(&wk->wu);
    rn = dir32_skydm[cal_move_dir_forecast(&wk->wu, 5)];
    return rn;
}



s32 check_buttobi_type2(WORK* wk) {
    s16 rn;
    setup_butt_own_data(wk);
    rn = dir32_grddm[cal_move_dir_forecast(wk, 5)];
    return rn;
}



void dead_voice_request(void) {
    if (dead_voice_flag) {
        if (plw[0].dead_flag) {
            dead_voice_request2(&plw[0]);
        }
        if (plw[1].dead_flag) {
            dead_voice_request2(&plw[1]);
        }
    }
    dead_voice_flag = 0;
}



void dead_voice_request2(PLW* wk) {
    s16 secd1;
    s16 secd2;
    secd1 = dead_voice_table[wk->player_number][0];
    secd2 = dead_voice_table[wk->player_number][1];
    if (wk->wu.routine_no[1] == PLAYER_DAMAGE && atsagct[wk->wu.routine_no[2]] & 0x10) {
        sound_effect_request[secd2](wk, secd2);
    } else {
        sound_effect_request[secd1](wk, secd1);
    }
}



/* provisional name: a player voice by kind with a 1 in 64 variant; nothing calls it */
void pl_voice_request(s8 pl, u8 kind) {
    s16 code;
    if (kind > 9) {
        code = voice_select_table[plw[pl].player_number][2];
    } else {
        code = voice_select_table[plw[pl].player_number][0];
    }
    code += (random_16_com() == 8);
    code = Check_Voice_SE(code);
    Sound_SE(code);
}



void setup_saishin_lvdir(ds, gddir)
PLW* ds;
s8 gddir;
{
    s32 gc;
    if ((ds->sa_stop_flag) == 1) {
        if (ds->wu.rl_flag) {
            ds->saishin_lvdir = convert_saishin_lvdir[1][ds->sa_stop_lvdir & 0xC];
        } else {
            ds->saishin_lvdir = convert_saishin_lvdir[0][ds->sa_stop_lvdir & 0xC];
        }
    } else if (ds->wu.rl_flag) {
        ds->saishin_lvdir = convert_saishin_lvdir[1][ds->cp->sw_lvbt & LEVER_LR];
    } else {
        ds->saishin_lvdir = convert_saishin_lvdir[0][ds->cp->sw_lvbt & LEVER_LR];
    }
    gc = ds->guard_chuu;
    if (gc && gc < 5) {
        ds->saishin_lvdir = gddir;
    }
}



void setup_lvdir_after_autodir(PLW* wk) {
    const u8* p = convert_saishin_lvdir[0];
    if (wk->wu.rl_flag) {
        p += wk->cp->sw_lvbt & LEVER_LR;
        p += 16;
        wk->cp->lever_dir = *p;
    } else {
        p += wk->cp->sw_lvbt & LEVER_LR;
        wk->cp->lever_dir = *p;
    }
}



s16 gauge_rank_value(s16 v) {
    s16 i;

    for (i = 0; i < 5; i++) {
        if (v >= gauge_rank_table[i][0]) {
            break;
        }
    }
    return gauge_rank_table[i][1];
}


