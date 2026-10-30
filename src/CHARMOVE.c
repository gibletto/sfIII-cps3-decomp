/*
 * CHARMOVE.C  cg script interpreter (character animation and action scripts)
 *
 * char_move advances a work's cg (character animation) script one frame: it counts down the current
 * line, loads the next cg data line with check_cgd_patdat (pattern, step move, attack number,
 * effects, sound, judgement areas) and runs any script commands. The comm_* routines are the script
 * commands: jumps and calls (comm_jsr/comm_ret and the comm_rja/comm_uja return-jump slots), loops,
 * position and speed setting, arithmetic and compares on the cmwk work registers, lever and button
 * tests, hit, super art, facing and screen-side jumps, sound, shadow and display flags.
 * set_char_move_init2 and the char_move_cm* helpers start a script at an index or a saved address;
 * decord_if_jump (relative and table jumps) and get_comm_if_* decode conditional jumps. Every player,
 * effect and stage object animates through this module.
 * set_char_move_init points a work at script "index" of character table "koc", clears the cg
 * counters, copies the two header words of the script, resets the script work registers and
 * move-origin record and sets the attack kind for attacking works. It then runs the first frame
 * with char_move. This is the standard way every object starts a new animation.
 * setup_shell_hit_stop is declared here without a prototype.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "PLSGAUGE.h"
#include "PLS02.h"
#include "effect_2.h"
#include "PLS03ATT.h"
#include "EFFF1.h"
#include "EFFF2_code.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "charmove_2.h"
#include "fighter.h"
#include "cmd_data.h"


void char_move(WORK* wk);
#pragma inline(char_move)
void setup_shell_hit_stop();


void set_char_move_init(wk, koc, index)
WORK* wk;
s16 koc;
s16 index;
{
    u32* dst;
    u32* src;
    s16 i;
    wk->now_koc = koc;
    wk->char_index = index;
    wk->set_char_ad = (u32*)wk->char_table[koc][index];
    dst = (u32*)&wk->cg_ctr;
    for (i = 0; i < 6; i++) {
        *dst++ = 0;
    }
    src = wk->set_char_ad;
    dst = (u32*)&wk->cg_ctr;
    *--dst = *--src;
    *--dst = *--src;
    wk->cg_ix = -wk->cgd_type;
    wk->cg_ctr = 1;
    wk->cg_next_ix = 0;
    wk->old_cgnum = 0;
    wk->cg_wca_ix = 0;
    wk->cmoa.koc = wk->now_koc;
    wk->cmoa.ix = wk->char_index;
    wk->cmoa.pat = 1;
    wk->cmwk[15] = 0;
    if (wk->work_id & 0xF) {
        wk->at_koa = acatkoa_table[wk->kind_of_waza];
    }
    char_move(wk);
}

void set_char_move_init2(wk, koc, index, ip, scf)
WORK* wk;
s16 koc;
s16 index;
s16 ip;
s16 scf;
{
    u32* dst;
    u32* src;
    s16 i;
    u8 pst;
    u8 kow;
    pst = wk->pat_status;
    kow = wk->kind_of_waza;
    wk->now_koc = koc;
    wk->char_index = index;
    wk->set_char_ad = (u32*)wk->char_table[koc][index];
    dst = (u32*)&wk->cg_ctr;
    for (i = 0; i < 6; i++) {
        *dst++ = 0;
    }
    src = wk->set_char_ad;
    dst = (u32*)&wk->cg_ctr;
    *--dst = *--src;
    *--dst = *--src;
    wk->cg_ix = (ip - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
    wk->cg_next_ix = 0;
    wk->old_cgnum = 0;
    wk->cg_wca_ix = 0;
    if (wk->cmoa.pat == 0) {
        wk->cmoa.koc = wk->now_koc;
        wk->cmoa.ix = wk->char_index;
        wk->cmoa.pat = 1;
    }
    if (scf) {
        wk->pat_status = pst;
        wk->kind_of_waza = kow;
    }
    if (wk->work_id & 0xF) {
        wk->at_koa = acatkoa_table[wk->kind_of_waza];
    }
    char_move(wk);
}



void exset_char_move_init(WORK* wk, s16 koc, s16 index) {
    u32* dst;
    u32* src;
    s16 i;
    u8 now_ctr;
    wk->now_koc = koc;
    wk->char_index = index;
    wk->set_char_ad = (u32*)wk->char_table[koc][index];
    now_ctr = wk->cg_ctr;
    dst = (u32*)&wk->cg_ctr;
    src = wk->set_char_ad + wk->cg_ix;
    for (i = 0; i < wk->cgd_type; i++) {
        *dst++ = *src++;
    }
    wk->cg_ctr = now_ctr;
    wk->cmoa.koc = wk->now_koc;
    wk->cmoa.ix = wk->char_index;
    wk->cmoa.pat = 1;
}



void char_move_z(WORK* wk) {
    if (test_flag) {
        wk->cg_next_ix = 0;
    }
    wk->cg_ctr = 1;
    char_move(wk);
}


/* provisional name */
void char_move_reset_ctr(WORK* wk) {
    wk->cg_next_ix = 0;
    wk->cg_ctr = 1;
}



void char_move_wca(WORK* wk) {
    wk->cg_next_ix = 0;
    wk->cg_ix = (wk->cg_wca_ix - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
    char_move(wk);
}



void char_move_wca_init(WORK* wk) {
    wk->cg_next_ix = 0;
    wk->cg_ix = (wk->cg_wca_ix - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
}



s32 comm_wca(WORK* wk, CHAR_CMD* _p1) {
    char_move_wca_init(wk);
    return 1;
}



void char_move_index(WORK* wk, s32 ix) {
    wk->cg_next_ix = 0;
    wk->cg_ix = (ix - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
    char_move(wk);
}


/* provisional name */
void char_move_index_set(WORK* wk, s16 ix) {
    wk->cg_next_ix = 0;
    wk->cg_ix = (ix - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
}


/* provisional name */
void set_cmja_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmja.koc = koc;
    wk->cmja.ix = ix;
    wk->cmja.pat = pat;
}



void char_move_cmja(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmja.koc, wk->cmja.ix, wk->cmja.pat, 0);
}


/* provisional name */
void set_cmj2_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj2.koc = koc;
    wk->cmj2.ix = ix;
    wk->cmj2.pat = pat;
}



/* provisional name */
void char_move_cmj2(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj2.koc, wk->cmj2.ix, wk->cmj2.pat, 0);
}


/* provisional name */
void set_cmj3_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj3.koc = koc;
    wk->cmj3.ix = ix;
    wk->cmj3.pat = pat;
}



/* provisional name */
void char_move_cmj3(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj3.koc, wk->cmj3.ix, wk->cmj3.pat, 0);
}


/* provisional name */
void set_cmj4_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj4.koc = koc;
    wk->cmj4.ix = ix;
    wk->cmj4.pat = pat;
}



void char_move_cmj4(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj4.koc, wk->cmj4.ix, wk->cmj4.pat, 0);
}


/* provisional name */
void set_cmj5_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj5.koc = koc;
    wk->cmj5.ix = ix;
    wk->cmj5.pat = pat;
}



/* provisional name */
void char_move_cmj5(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj5.koc, wk->cmj5.ix, wk->cmj5.pat, 0);
}


/* provisional name */
void set_cmj6_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj6.koc = koc;
    wk->cmj6.ix = ix;
    wk->cmj6.pat = pat;
}



/* provisional name */
void char_move_cmj6(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj6.koc, wk->cmj6.ix, wk->cmj6.pat, 0);
}


/* provisional name */
void set_cmj7_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmj7.koc = koc;
    wk->cmj7.ix = ix;
    wk->cmj7.pat = pat;
}



/* provisional name */
void char_move_cmj7(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj7.koc, wk->cmj7.ix, wk->cmj7.pat, 0);
}



/* provisional name */
s32 char_move_cmoa(WORK* wk, CHAR_CMD* _p1) {
    set_char_move_init2(wk, wk->cmoa.koc, wk->cmoa.ix, wk->cmoa.pat, 0);
}


/* provisional name */
void set_cmms_data(WORK* wk, s16 koc, s16 ix, s16 pat) {
    wk->cmms.koc = koc;
    wk->cmms.ix = ix;
    wk->cmms.pat = pat;
}



void char_move_cmms(WORK* wk) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmms.koc, wk->cmms.ix, wk->cmms.pat, 0);
}


void char_move_cmms2(WORK* wk) {
    u32* to_ram;
    u32* dst;
    u32* src;
    s16 i;
    s16 now_cgd;
    setup_comm_back(wk);
    now_cgd = wk->cgd_type;
    wk->now_koc = wk->cmms.koc;
    wk->char_index = wk->cmms.ix;
    wk->set_char_ad = (u32*)wk->char_table[wk->now_koc][wk->char_index];
    src = wk->set_char_ad;
    dst = (u32*)&wk->cg_ctr;
    *--dst = *--src;
    *--dst = *--src;
    if (now_cgd > wk->cgd_type) {
        to_ram = (u32*)&wk->cg_wca_ix;
        for (i = 0; i < now_cgd - wk->cgd_type; i++) {
            *--to_ram = 0;
        }
    }
    wk->cg_ix = (wk->cmms.pat - 1) * wk->cgd_type - wk->cgd_type;
    wk->cg_ctr = 1;
    wk->cg_next_ix = 0;
    wk->old_cgnum = 0;
    wk->cg_wca_ix = 0;
}



void check_cm_extended_code(WORK* wk);

void char_move(WORK* wk) {
    if (--wk->cg_ctr != 0) {
        return;
    }
    check_cm_extended_code(wk);
}

void check_cm_extended_code(WORK* wk) {
    CHAR_CMD* cpc;
    if (wk->cg_next_ix) {
        wk->cg_ix = (wk->cg_next_ix - 1) * wk->cgd_type;
    } else {
        wk->cg_ix += wk->cgd_type;
    }
next:
    cpc = (CHAR_CMD*)(wk->set_char_ad + wk->cg_ix);
    if (cpc->code >= 0x100) {
        check_cgd_patdat(wk);
        return;
    } else if (comm_jmp_tbl[cpc->code]((PLW*)wk, cpc) == 0) {
        return;
    }
    wk->cg_ix += wk->cgd_type;
    goto next;
}

u32 comm_dummy(void)
{
    return 1;
}



s32 comm_roa(WORK* wk, CHAR_CMD* _p1) {
    if (wk->cmoa.pat == 0) {
        wk->cmoa.koc = wk->now_koc;
        wk->cmoa.ix = wk->char_index;
        wk->cmoa.pat = 1;
    }
    set_char_move_init2(wk, wk->cmoa.koc, wk->cmoa.ix, wk->cmoa.pat, 0);
    return 0;
}

u32 comm_end(WORK* wk, CHAR_CMD* ctc)
{

    wk->cg_ix = (ctc->pat - 2) * wk->cgd_type;
    return 1;
}

u32 comm_jmp(WORK* wk, CHAR_CMD* ctc)
{

    setup_comm_back(wk);
    set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 0);
    return 0;
}



s32 comm_jpss(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
    return 0;
}



s32 comm_jsr(WORK* wk, CHAR_CMD* ctc) {
    wk->cmsw.koc = wk->now_koc;
    wk->cmsw.ix = wk->char_index;
    wk->cmsw.pat = (wk->cg_ix / wk->cgd_type) + 2;
    set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 0);
    return 0;
}



s32 comm_ret(WORK* wk, CHAR_CMD* _p1) {
    set_char_move_init2(wk, wk->cmsw.koc, wk->cmsw.ix, wk->cmsw.pat, 0);
    return 0;
}



s32 comm_sps(WORK* wk, CHAR_CMD* ctc) {
    wk->pat_status = ctc->pat;
    return 1;
}



s32 comm_setr(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[ctc->koc] = ctc->ix;
    return 1;
}



s32 comm_addr(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[ctc->koc] += ctc->ix;
    return 1;
}



s32 comm_if_l(WORK* wk, CHAR_CMD* ctc) {
    u16 lvdat;
    u16 my_lvdat;
    if (ctc->koc & 0x4000) {
        my_lvdat = wk->cmwk[ctc->koc & 0xF];
    } else {
        my_lvdat = ctc->koc;
    }
    lvdat = get_comm_if_lever(wk);
    if (!(my_lvdat & 0x7FFF)) {
        if (lvdat == 0) {
            return decord_if_jump(wk, ctc, ctc->ix);
        }
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    if (my_lvdat & 0x8000) {
        if (lvdat == (my_lvdat & 0xF)) {
            return decord_if_jump(wk, ctc, ctc->ix);
        }
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    if (lvdat & my_lvdat) {
        return decord_if_jump(wk, ctc, ctc->ix);
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}

s32 comm_djmp(WORK* wk, CHAR_CMD* ctc) {
    u8 ldir;
    if ((ldir = get_comm_djmp_lever_dir((PLW*)wk))) {
        if (ldir == 1) {
            return decord_if_jump(wk, ctc, ctc->ix);
        }
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return decord_if_jump(wk, ctc, ctc->koc);
}



s32 comm_for(WORK* wk, CHAR_CMD* ctc) {
    if (ctc->pat & 0x4000) {
        wk->cmlp.code = wk->cmwk[ctc->pat & 0xF];
    } else {
        wk->cmlp.code = ctc->pat;
    }
    wk->cmlp.koc = wk->now_koc;
    wk->cmlp.ix = wk->char_index;
    wk->cmlp.pat = wk->cg_ix / wk->cgd_type + 2;
    return 1;
}



s32 comm_nex(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmlp.code) {
        if (--wk->cmlp.code > 0) {
            set_char_move_init2(wk, wk->cmlp.koc, wk->cmlp.ix, wk->cmlp.pat, 1);
            return 0;
        }
    }
    return 1;
}



s32 comm_for2(WORK* wk, CHAR_CMD* ctc) {
    if (ctc->pat & 0x4000) {
        wk->cml2.code = wk->cmwk[ctc->pat & 0xF];
    } else {
        wk->cml2.code = ctc->pat;
    }
    wk->cml2.koc = wk->now_koc;
    wk->cml2.ix = wk->char_index;
    wk->cml2.pat = (wk->cg_ix / wk->cgd_type) + 2;
    return 1;
}



s32 comm_nex2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cml2.code && --wk->cml2.code > 0) {
        set_char_move_init2(wk, wk->cml2.koc, wk->cml2.ix, wk->cml2.pat, 1);
        return 0;
    }
    return 1;
}



s32 comm_rja(WORK* wk, CHAR_CMD* ctc) {
    wk->cmja.koc = ctc->koc;
    wk->cmja.ix = ctc->ix;
    wk->cmja.pat = ctc->pat;
    return 1;
}



s32 comm_uja(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmja.koc, wk->cmja.ix, wk->cmja.pat, 0);
    return 0;
}



s32 comm_rja2(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj2.koc = ctc->koc;
    wk->cmj2.ix = ctc->ix;
    wk->cmj2.pat = ctc->pat;
    return 1;
}



s32 comm_uja2(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj2.koc, wk->cmj2.ix, wk->cmj2.pat, 0);
    return 0;
}



s32 comm_rja3(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj3.koc = ctc->koc;
    wk->cmj3.ix = ctc->ix;
    wk->cmj3.pat = ctc->pat;
    return 1;
}



s32 comm_uja3(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj3.koc, wk->cmj3.ix, wk->cmj3.pat, 0);
    return 0;
}



s32 comm_rja4(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj4.koc = ctc->koc;
    wk->cmj4.ix = ctc->ix;
    wk->cmj4.pat = ctc->pat;
    return 1;
}



s32 comm_uja4(WORK* wk, CHAR_CMD* _p1) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj4.koc, wk->cmj4.ix, wk->cmj4.pat, 0);
    return 0;
}



s32 comm_rja5(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj5.koc = ctc->koc;
    wk->cmj5.ix = ctc->ix;
    wk->cmj5.pat = ctc->pat;
    return 1;
}



s32 comm_uja5(WORK* wk, CHAR_CMD* _p1) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj5.koc, wk->cmj5.ix, wk->cmj5.pat, 0);
    return 0;
}



s32 comm_rja6(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj6.koc = ctc->koc;
    wk->cmj6.ix = ctc->ix;
    wk->cmj6.pat = ctc->pat;
    return 1;
}



s32 comm_uja6(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj6.koc, wk->cmj6.ix, wk->cmj6.pat, 0);
    return 0;
}



s32 comm_rja7(WORK* wk, CHAR_CMD* ctc) {
    wk->cmj7.koc = ctc->koc;
    wk->cmj7.ix = ctc->ix;
    wk->cmj7.pat = ctc->pat;
    return 1;
}



s32 comm_uja7(WORK* wk, CHAR_CMD* ctc) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmj7.koc, wk->cmj7.ix, wk->cmj7.pat, 0);
    return 0;
}



s32 comm_rmja(WORK* wk, CHAR_CMD* ctc) {
    wk->cmms.koc = ctc->koc;
    wk->cmms.ix = ctc->ix;
    wk->cmms.pat = ctc->pat;
    return 1;
}



s32 comm_umja(WORK* wk, CHAR_CMD* _p1) {
    setup_comm_back(wk);
    set_char_move_init2(wk, wk->cmms.koc, wk->cmms.ix, wk->cmms.pat, 0);
    return 0;
}



s32 comm_mdat(WORK* wk, CHAR_CMD* ctc) {
    wk->cmmd.koc = ctc->koc;
    wk->cmmd.ix = ctc->ix;
    wk->cmmd.pat = ctc->pat;
    return 1;
}



s32 comm_ydat(WORK* wk, CHAR_CMD* ctc) {
    wk->cmyd.koc = ctc->koc;
    wk->cmyd.ix = ctc->ix;
    wk->cmyd.pat = ctc->pat;
    return 1;
}



s32 comm_mpos(WORK* wk, CHAR_CMD* ctc) {
    wk->att.hit_mark = ctc->koc;
    wk->hit_mark_x = ctc->ix;
    wk->hit_mark_y = ctc->pat;
    return 1;
}



s32 comm_cafr(WORK* wk, CHAR_CMD* ctc) {
    wk->cmcf.koc = ctc->koc;
    wk->cmcf.ix = ctc->ix;
    wk->cmcf.pat = ctc->pat;
    return 1;
}



s32 comm_care(WORK* wk, CHAR_CMD* ctc) {
    wk->cmcr.koc = ctc->koc;
    wk->cmcr.ix = ctc->ix;
    wk->cmcr.pat = ctc->pat;
    return 1;
}



s32 comm_psxy(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    switch (ctc->koc) {
    case 0:
        wk->xyz[0].disp.pos = ctc->ix;
        wk->xyz[1].disp.pos = ctc->pat;
        break;
    case 2:
        wk->xyz[0].disp.pos = ctc->ix;
        wk->xyz[1].disp.pos = ctc->pat;
    default:
        emwk = (WORK*)wk->target_adrs;
        emwk->xyz[0].disp.pos = ctc->ix;
        emwk->xyz[1].disp.pos = ctc->pat;
        break;
    }
    return 1;
}



s32 comm_ps_x(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    switch (ctc->koc) {
    case 0:
        wk->xyz[0].disp.pos = ctc->ix;
        break;
    case 2:
        wk->xyz[0].disp.pos = ctc->ix;
    default:
        emwk = (WORK*)wk->target_adrs;
        emwk->xyz[0].disp.pos = ctc->ix;
        break;
    }
    return 1;
}



s32 comm_ps_y(WORK* wk, CHAR_CMD* ctc) {
    switch (ctc->koc) {
    case 0:
        wk->xyz[1].disp.pos = ctc->pat;
        break;
    case 2:
        wk->xyz[1].disp.pos = ctc->pat;
    default:
        wk = (WORK*)wk->target_adrs;
        wk->xyz[1].disp.pos = ctc->pat;
        break;
    }
    return 1;
}



s32 comm_paxy(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    switch (ctc->koc) {
    case 0:
        if (wk->rl_flag) {
            wk->xyz[0].cal += ctc->ix << 8;
        } else {
            wk->xyz[0].cal -= ctc->ix << 8;
        }
        wk->xyz[1].cal += ctc->pat << 8;
        break;
    case 2:
        if (wk->rl_flag) {
            wk->xyz[0].cal += ctc->ix << 8;
        } else {
            wk->xyz[0].cal -= ctc->ix << 8;
        }
        wk->xyz[1].cal += ctc->pat << 8;
    default:
        emwk = (WORK*)wk->target_adrs;
        if (emwk->rl_flag) {
            emwk->xyz[0].cal += ctc->ix << 8;
        } else {
            emwk->xyz[0].cal -= ctc->ix << 8;
        }
        emwk->xyz[1].cal += ctc->pat << 8;
        break;
    }
    return 1;
}



s32 comm_pa_x(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    switch (ctc->koc) {
    case 0:
        if (wk->rl_flag) {
            wk->xyz[0].cal += ctc->ix << 8;
        } else {
            wk->xyz[0].cal -= ctc->ix << 8;
        }
        break;
    case 2:
        if (wk->rl_flag) {
            wk->xyz[0].cal += ctc->ix << 8;
        } else {
            wk->xyz[0].cal -= ctc->ix << 8;
        }
    default:
        emwk = (WORK*)wk->target_adrs;
        if (emwk->rl_flag) {
            emwk->xyz[0].cal += ctc->ix << 8;
        } else {
            emwk->xyz[0].cal -= ctc->ix << 8;
        }
        break;
    }
    return 1;
}



s32 comm_pa_y(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    switch (ctc->koc) {
    case 0:
        wk->xyz[1].cal += ctc->pat << 8;
        break;
    case 2:
        wk->xyz[1].cal += ctc->pat << 8;
    default:
        emwk = (WORK*)wk->target_adrs;
        emwk->xyz[1].cal += ctc->pat << 8;
        break;
    }
    return 1;
}



s32 comm_exec(WORK* wk, CHAR_CMD* ctc) {
    effinitjptbl[ctc->koc](wk, (u8)ctc->ix);
    return 1;
}



s32 comm_rngc(WORK* wk, CHAR_CMD* ctc) {
    s16 rngdat;
    if (wk->work_id == 1) {
        rngdat = get_em_body_range(wk);
    } else {
        rngdat = get_em_body_range((WORK*)((WORK_Other*)wk)->my_master);
    }
    if (rngdat > ctc->koc) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return decord_if_jump(wk, ctc, ctc->ix);
}



s32 comm_mxyt(WORK* wk, CHAR_CMD* ctc) {
    if (ctc->koc) {
        setup_mvxy_data(wk, ctc->koc);
    } else {
        reset_mvxy_data(wk);
    }
    return 1;
}



s32 comm_pjmp(WORK* wk, CHAR_CMD* ctc) {
    if (random_32_com() < ctc->koc) {
        return decord_if_jump(wk, ctc, ctc->ix);
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}



s32 comm_hjmp(WORK* wk, CHAR_CMD* ctc) {
    if (wk->meoshi_hit_flag != 0 && wk->hf.hit_flag != 0) {
        if (wk->hf.hit_flag & 0x303) {
            return decord_if_jump(wk, ctc, ctc->koc);
        }
        if (wk->hf.hit_flag & 0x3030) {
            return decord_if_jump(wk, ctc, ctc->ix);
        }
        if (wk->hf.hit_flag & 0xC0C0) {
            return decord_if_jump(wk, ctc, ctc->pat);
        }
    }
    return 1;
}



s32 comm_hclr(WORK* wk, CHAR_CMD* _p1) {
    wk->hf.hit_flag = 0;
    return 1;
}



s32 comm_ixfw(WORK* wk, CHAR_CMD* ctc) {
    wk->cg_ix += (ctc->pat - 1) * wk->cgd_type;
    return 1;
}



s32 comm_ixbw(WORK* wk, CHAR_CMD* ctc) {
    wk->cg_ix -= (ctc->pat + 1) * wk->cgd_type;
    return 1;
}



s32 comm_quax(WORK* _p0, CHAR_CMD* ctc) {
    bg_w.quake_x_index = ctc->koc;
    return 1;
}

s32 comm_quay(WORK* wk, CHAR_CMD* ctc)
{

    bg_w.quake_y_index = ctc->koc;
    return 1;
}



s32 comm_if_s(WORK* wk, CHAR_CMD* ctc) {
    u16 shdat;
    u16 my_shdat;
    if (ctc->koc & 0x4000) {
        my_shdat = wk->cmwk[ctc->koc & 0xF];
    } else {
        my_shdat = ctc->koc;
    }
    shdat = get_comm_if_shot(wk);
    if (my_shdat == shdat) {
        return decord_if_jump(wk, ctc, ctc->ix);
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}



s32 comm_rapp(WORK* wk, CHAR_CMD* ctc) {
    if (wk->work_id == 1) {
        if (wcp[wk->id].waza_flag[9]) {
            setup_comm_back(wk);
            set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
            return 0;
        }
        return 1;
    }
    if (wcp[((WORK_Other*)wk)->master_id & 1].waza_flag[9]) {
        setup_comm_back(wk);
        set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
        return 0;
    }
    return 1;
}



s32 comm_rapk(WORK* wk, CHAR_CMD* ctc) {
    if (wk->work_id == 1) {
        if (wcp[wk->id].waza_flag[11]) {
            setup_comm_back(wk);
            set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
            return 0;
        }
        return 1;
    }
    if (wcp[((WORK_Other*)wk)->master_id & 1].waza_flag[11]) {
        setup_comm_back(wk);
        set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
        return 0;
    }
    return 1;
}



s32 comm_gets(WORK* wk, CHAR_CMD* ctc) {
    u32* src = wk->set_char_ad;
    u32* dst = (u32*)&wk->cg_ctr;
    *--dst = *--src;
    *--dst = *--src;
    return 1;
}



s32 comm_s123(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[1] = ctc->koc;
    wk->routine_no[2] = ctc->ix;
    wk->routine_no[3] = ctc->pat;
    return 1;
}



s32 comm_s456(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[4] = ctc->koc;
    wk->routine_no[5] = ctc->ix;
    wk->routine_no[6] = ctc->pat;
    return 1;
}



s32 comm_a123(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[4] += ctc->koc;
    wk->routine_no[5] += ctc->ix;
    wk->routine_no[6] += ctc->pat;
    return 1;
}



s32 comm_a456(WORK* wk, CHAR_CMD* ctc) {
    wk->routine_no[4] += ctc->koc;
    wk->routine_no[5] += ctc->ix;
    wk->routine_no[6] += ctc->pat;
    return 1;
}



s32 comm_stop(PLW* wk, CHAR_CMD* ctc) {
    PLW* wk2;
    if (test_flag == 0) {
        wk->wu.dm_stop = 0;
        wk->wu.hit_stop = ctc->koc;
        wk2 = (PLW*)wk->wu.target_adrs;
        wk2->wu.hit_stop = ctc->ix;
        setup_shell_hit_stop(&wk->wu, ctc->ix, ctc->pat);
        setup_shell_hit_stop(&wk2->wu, ctc->ix, 0);
    }
    wk->sa_stop_flag = 0;
    wk2->sa_stop_flag = 2;
    return 1;
}



s32 comm_smhf(WORK* wk, CHAR_CMD* ctc) {
    wk->meoshi_hit_flag = ctc->koc;
    return 1;
}



s32 comm_ngme(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    emwk = (WORK*)wk->hit_adrs;
    emwk->routine_no[1] = PLAYER_CAUGHT;
    emwk->routine_no[2] = 1;
    emwk->routine_no[3] = 1;
    if (test_flag) {
        wk->cmyd.pat = 1;
    }
    return 1;
}



s32 comm_ngem(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk;
    emwk = (WORK*)wk->hit_adrs;
    emwk->routine_no[1] = PLAYER_CAUGHT;
    emwk->routine_no[2] = 2;
    emwk->routine_no[3] = 1;
    if (test_flag) {
        wk->cmyd.pat = 2;
    }
    return 1;
}



s32 comm_iflb(WORK* wk, CHAR_CMD* ctc) {
    u16 shdat;
    u16 my_shdat;
    if (ctc->koc & 0x4000) {
        my_shdat = wk->cmwk[ctc->koc & 0xF];
    } else {
        my_shdat = ctc->koc;
    }
    shdat = get_comm_if_lvsh(wk);
    if (my_shdat == shdat) {
        return decord_if_jump(wk, ctc, ctc->ix);
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}



s32 comm_asxy(WORK* wk, CHAR_CMD* ctc) {
    s16* from_rom2 = &wk->step_xy_table[ctc->koc];
    s32 st = *from_rom2++;
    st <<= 8;
    if (wk->rl_flag) {
        wk->xyz[0].cal += st;
    } else {
        wk->xyz[0].cal -= st;
    }
    st = *from_rom2;
    st <<= 8;
    wk->xyz[1].cal += st;
    return 1;
}



s32 comm_schx(WORK* wk, CHAR_CMD* ctc) {
    switch (ctc->koc) {
    case 0:
        wk->mvxy.a[0].sp = (wk->mvxy.a[0].sp * ctc->ix) / ctc->pat;
        break;
    case 2:
        wk->mvxy.a[0].sp = (wk->mvxy.a[0].sp * ctc->ix) / ctc->pat;
    case 1:
        wk->mvxy.d[0].sp = (wk->mvxy.d[0].sp * ctc->ix) / ctc->pat;
    default:
        break;
    }
    return 1;
}



s32 comm_schy(WORK* wk, CHAR_CMD* ctc) {
    switch (ctc->koc) {
    case 0:
        wk->mvxy.a[1].sp = (wk->mvxy.a[1].sp * ctc->ix) / ctc->pat;
        break;
    case 2:
        wk->mvxy.a[1].sp = (wk->mvxy.a[1].sp * ctc->ix) / ctc->pat;
    case 1:
        wk->mvxy.d[1].sp = (wk->mvxy.d[1].sp * ctc->ix) / ctc->pat;
    default:
        break;
    }
    return 1;
}



s32 comm_back(WORK* wk, CHAR_CMD* _p1) {
    set_char_move_init2(wk, wk->cmbk.koc, wk->cmbk.ix, wk->cmbk.pat, 0);
    return 0;
}



s32 comm_mvix(WORK* wk, CHAR_CMD* ctc) {
    wk->mvxy.index = ctc->koc;
    return 1;
}



s32 comm_sajp(WORK* wk, CHAR_CMD* ctc) {
    if (wk->work_id == 1) {
        if (((PLW*)wk)->sa->kind_of_arts == ctc->koc) {
            if (((PLW*)wk)->sa->ok == -1) {
                return decord_if_jump(wk, ctc, ctc->ix);
            }
        }
    } else {
        wk = (WORK*)((WORK_Other*)wk)->my_master;
        if (wk->work_id == 1 && ((PLW*)wk)->sa->kind_of_arts == ctc->koc && ((PLW*)wk)->sa->ok == -1) {
            return decord_if_jump(wk, ctc, ctc->ix);
        }
    }
    return 1;
}



s32 comm_ccch(WORK* wk, CHAR_CMD* ctc) {
    if (ctc->koc) {
        wk->extra_col += ctc->ix;
        wk->extra_col &= 0x2FFF;
    } else {
        wk->extra_col = ctc->ix;
    }
    return 1;
}



s32 comm_wset(WORK* wk, CHAR_CMD* ctc) {
    switch (ctc->ix) {
    case 2:
        wk->cmwk[ctc->koc & 0xF] |= ctc->pat;
        break;
    case 1:
        wk->cmwk[ctc->koc & 0xF] &= ctc->pat;
        break;
    default:
        wk->cmwk[ctc->koc & 0xF] = ctc->pat;
        break;
    }
    return 1;
}



s32 comm_wswk(WORK* wk, CHAR_CMD* ctc) {
    switch (ctc->ix) {
    case 2:
        wk->cmwk[ctc->koc & 0xF] |= wk->cmwk[ctc->pat & 0xF];
        break;
    case 1:
        wk->cmwk[ctc->koc & 0xF] &= wk->cmwk[ctc->pat & 0xF];
        break;
    default:
        wk->cmwk[ctc->koc & 0xF] = wk->cmwk[ctc->pat & 0xF];
        break;
    }
    return 1;
}



s32 comm_wadd(WORK* wk, CHAR_CMD* ctc) {
    wk->cmwk[ctc->koc & 0xF] += ctc->ix;
    wk->cmwk[ctc->koc & 0xF] &= ctc->pat;
    return 1;
}



s32 comm_wceq(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] == ctc->ix) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wcne(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] != ctc->ix) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wcgt(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] > ctc->ix) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wclt(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] < ctc->ix) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wadd2(WORK* wk, CHAR_CMD* ctc) {
    wk->cmwk[ctc->koc & 0xF] += wk->cmwk[ctc->ix & 0xF];
    wk->cmwk[ctc->koc & 0xF] &= ctc->pat;
    return 1;
}



s32 comm_wceq2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] == wk->cmwk[ctc->ix & 0xF]) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wcne2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] != wk->cmwk[ctc->ix & 0xF]) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wcgt2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] > wk->cmwk[ctc->ix & 0xF]) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_wclt2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->cmwk[ctc->koc & 0xF] < wk->cmwk[ctc->ix & 0xF]) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_rapp2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->work_id == 1) {
        if (wcp[wk->id].waza_flag[8]) {
            setup_comm_back(wk);
            set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
            return 0;
        }
        return 1;
    }
    if (wcp[((WORK_Other*)wk)->master_id & 1].waza_flag[8]) {
        setup_comm_back(wk);
        set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
        return 0;
    }
    return 1;
}



s32 comm_rapk2(WORK* wk, CHAR_CMD* ctc) {
    if (wk->work_id == 1) {
        if (wcp[wk->id].waza_flag[10]) {
            setup_comm_back(wk);
            set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
            return 0;
        }
        return 1;
    }
    if (wcp[((WORK_Other*)wk)->master_id & 1].waza_flag[10]) {
        setup_comm_back(wk);
        set_char_move_init2(wk, ctc->koc, ctc->ix, ctc->pat, 1);
        return 0;
    }
    return 1;
}



s32 comm_iflg(WORK* wk, CHAR_CMD* ctc) {
    if (ctc->koc == 0) {
        if (wk->cmwk[11] < ctc->ix) {
            return 1;
        }
        return decord_if_jump(wk, ctc, ctc->pat);
    } else {
        if (((WORK*)wk->target_adrs)->cmwk[11] < ctc->ix) {
            return 1;
        }
        return decord_if_jump(wk, ctc, ctc->pat);
    }
}



s32 comm_mpcy(WORK* wk, CHAR_CMD* ctc) {
    s16 ans = 0;
    switch (ctc->ix) {
    case 1:
        if (wk->xyz[1].disp.pos > ctc->koc) {
            ans = 1;
        }
        break;
    case 2:
        if (wk->xyz[1].disp.pos < ctc->koc) {
            ans = 1;
        }
        break;
    default:
        if (wk->xyz[1].disp.pos == ctc->koc) {
            ans = 1;
        }
        break;
    }
    if (ans == 0) {
        return 1;
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}



s32 comm_epcy(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk = (WORK*)wk->target_adrs;
    s16 ans = 0;
    switch (ctc->ix) {
    case 1:
        if (emwk->xyz[1].disp.pos > ctc->koc) {
            ans = 1;
        }
        break;
    case 2:
        if (emwk->xyz[1].disp.pos < ctc->koc) {
            ans = 1;
        }
        break;
    default:
        if (emwk->xyz[1].disp.pos == ctc->koc) {
            ans = 1;
        }
        break;
    }
    if (ans == 0) {
        return 1;
    }
    return decord_if_jump(wk, ctc, ctc->pat);
}



s32 comm_imgs(PLW* wk, CHAR_CMD* ctc) {
    PLW* tk;
    if (test_flag == 0) {
        tk = (PLW*)wk->wu.target_adrs;
        switch (ctc->koc) {
        case 0:
            if (wk->image_setup_flag) {
                break;
            }
            wk->image_setup_flag = 1;
            wk->image_data_index = ctc->ix;
            break;
        default:
            if (wk->image_setup_flag == 0) {
                wk->image_setup_flag = 1;
                wk->image_data_index = ctc->ix;
            }
        case 1:
            if (tk->image_setup_flag) {
                break;
            }
            tk->image_setup_flag = 1;
            tk->image_data_index = ctc->ix;
            break;
        }
    }
    return 1;
}



s32 comm_imgc(PLW* wk, CHAR_CMD* ctc) {
    PLW* tk = (PLW*)wk->wu.target_adrs;
    switch (ctc->koc) {
    case 0:
        wk->image_setup_flag = 0;
        break;
    default:
        wk->image_setup_flag = 0;
    case 1:
        tk->image_setup_flag = 0;
        break;
    }
    return 1;
}



s32 comm_rvxy(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk = (WORK*)wk->target_adrs;
    switch (ctc->koc) {
    case 0:
        if (wk->rl_flag) {
            wk->xyz[0].cal = emwk->xyz[0].cal + (ctc->ix << 8);
        } else {
            wk->xyz[0].cal = emwk->xyz[0].cal - (ctc->ix << 8);
        }
        wk->xyz[1].cal = emwk->xyz[1].cal + (ctc->pat << 8);
        break;
    case 2:
        if (wk->rl_flag) {
            wk->xyz[0].cal = emwk->xyz[0].cal + (ctc->ix << 8);
        } else {
            wk->xyz[0].cal = emwk->xyz[0].cal - (ctc->ix << 8);
        }
        wk->xyz[1].cal = emwk->xyz[1].cal + (ctc->pat << 8);
    default:
        if (wk->rl_flag) {
            emwk->xyz[0].cal = wk->xyz[0].cal + (ctc->ix << 8);
        } else {
            emwk->xyz[0].cal = wk->xyz[0].cal - (ctc->ix << 8);
        }
        emwk->xyz[1].cal = wk->xyz[1].cal + (ctc->pat << 8);
        break;
    }
    return 1;
}



s32 comm_rv_x(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk = (WORK*)wk->target_adrs;
    switch (ctc->koc) {
    case 0:
        if (wk->rl_flag) {
            wk->xyz[0].cal = emwk->xyz[0].cal + (ctc->ix << 8);
        } else {
            wk->xyz[0].cal = emwk->xyz[0].cal - (ctc->ix << 8);
        }
        break;
    case 2:
        if (wk->rl_flag) {
            wk->xyz[0].cal = emwk->xyz[0].cal + (ctc->ix << 8);
        } else {
            wk->xyz[0].cal = emwk->xyz[0].cal - (ctc->ix << 8);
        }
    default:
        if (wk->rl_flag) {
            emwk->xyz[0].cal = wk->xyz[0].cal + (ctc->ix << 8);
        } else {
            emwk->xyz[0].cal = wk->xyz[0].cal - (ctc->ix << 8);
        }
        break;
    }
    return 1;
}



s32 comm_rv_y(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk = (WORK*)wk->target_adrs;
    switch (ctc->koc) {
    case 0:
        wk->xyz[1].cal = emwk->xyz[1].cal + (ctc->pat << 8);
        break;
    case 2:
        wk->xyz[1].cal = emwk->xyz[1].cal + (ctc->pat << 8);
    default:
        emwk->xyz[1].cal = wk->xyz[1].cal + (ctc->pat << 8);
        break;
    }
    return 1;
}



s32 comm_ccfl(PLW* wk, CHAR_CMD* _p1) {
    wk->caution_flag = 0;
    return 1;
}



s32 comm_myhp(WORK* wk, CHAR_CMD* ctc) {
    s16 num = 0;
    switch (ctc->koc) {
    case 1:
        if (wk->vital_new > ctc->ix) {
            num = 1;
        }
        break;
    case 2:
        if (wk->vital_new < ctc->ix) {
            num = 1;
        }
        break;
    default:
        if (wk->vital_new == ctc->ix) {
            num = 1;
        }
        break;
    }
    if (num) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}



s32 comm_emhp(WORK* wk, CHAR_CMD* ctc) {
    WORK* emwk = (WORK*)wk->target_adrs;
    s16 num = 0;
    switch (ctc->koc) {
    case 1:
        if (emwk->vital_new > ctc->ix) {
            num = 1;
        }
        break;
    case 2:
        if (emwk->vital_new < ctc->ix) {
            num = 1;
        }
        break;
    default:
        if (emwk->vital_new == ctc->ix) {
            num = 1;
        }
        break;
    }
    if (num) {
        return decord_if_jump(wk, ctc, ctc->pat);
    }
    return 1;
}

u32 comm_exbgs(WORK* wk, CHAR_CMD* ctc) {
    effect_F1_init(wk, (u8)ctc->koc);
    return 1;
}

u32 comm_exbgc(WORK* wk)
{

    another_bg[wk->id] = 0;
    return 1;
}



s32 comm_atmf(PLW* wk, CHAR_CMD* ctc) {
    wk->atemi_flag = ctc->koc;
    wk->atemi_point = ctc->ix;
    return 1;
}



s32 comm_chkwf(PLW* wk, CHAR_CMD* ctc) {
    if (wk->cp->waza_flag[ctc->koc] == 0 || wk->cp->waza_flag[ctc->koc] == -1) {
        return decord_if_jump(&wk->wu, ctc, ctc->pat);
    }
    return decord_if_jump(&wk->wu, ctc, ctc->ix);
}



s32 decord_if_jump(WORK* wk, CHAR_CMD* cpc, s16 ix) {
    if (ix & 0xC000) {
        if (ix & 0x4000) {
            wk->cg_ix += ((ix & 0x3FFF) - 1) * wk->cgd_type;
        } else {
            wk->cg_ix -= ((ix & 0x3FFF) + 1) * wk->cgd_type;
        }
        return 1;
    }
    return comm_if_jmp_tbl[ix](wk, cpc);
}



s32 get_comm_if_lever(WORK* wk) {
    u16 num;
    if (wk->work_id == 1) {
        num = wcp[wk->id].sw_new & CMD_LV_MASK;
    } else {
        num = wcp[((WORK_Other*)wk)->master_id & 1].sw_new & CMD_LV_MASK;
    }
    return num;
}



s32 get_comm_if_shot(WORK* wk) {
    u16 num;
    if (wk->work_id == 1) {
        num = wcp[wk->id].sw_new & CMD_SW_SHOT;
    } else {
        num = wcp[(s16)(((WORK_Other*)wk)->master_id & 1)].sw_new & CMD_SW_SHOT;
    }
    return num;
}



s32 get_comm_if_lvsh(WORK* wk) {
    u16 num;
    if (wk->work_id == 1) {
        num = wcp[wk->id].sw_new & CMD_LVSW_ALL;
    } else {
        num = wcp[(s16)(((WORK_Other*)wk)->master_id & 1)].sw_new & CMD_LVSW_ALL;
    }
    return num;
}



s32 get_comm_djmp_lever_dir(PLW* wk) {
    u8 num;
    if (wk->wu.work_id == 1) {
        if (wk->py->flag == 0) {
            num = wcp[wk->wu.id].lever_dir;
        } else {
            num = 0;
        }
    } else {
        num = wcp[((WORK_Other*)wk)->master_id & 1].lever_dir;
    }
    return num;
}



void setup_comm_back(WORK* wk) {
    wk->cmbk.koc = wk->now_koc;
    wk->cmbk.ix = wk->char_index;
    wk->cmbk.pat = (wk->cg_ix / wk->cgd_type) + 2;
}



void check_cgd_patdat(WORK* wk) {
    s32 st;
    u32* dst;
    u32* src;
    s16 i;
    s16* from_rom2;
    src = wk->set_char_ad + wk->cg_ix;
    dst = (u32*)&wk->cg_ctr;
    for (i = 0; i < wk->cgd_type; i++) {
        *dst++ = *src++;
    }
    switch (wk->cgd_type) {
    case 6:
        if (wk->cg_add_xy) {
            from_rom2 = wk->step_xy_table + wk->cg_add_xy;
            st = *from_rom2++;
            st <<= 8;
            if (wk->rl_flag) {
                wk->xyz[0].cal += st;
            } else {
                wk->xyz[0].cal -= st;
            }
            st = *from_rom2;
            st <<= 8;
            wk->xyz[1].cal += st;
        }
        if (wk->cg_status & 0x80) {
            wk->pat_status = wk->cg_status & 0x7F;
        }
    case 4:
        if (wk->cg_att_ix) {
            set_new_attnum(wk);
        }
        if (wk->cg_effect) {
            effinitjptbl[wk->cg_effect](wk, wk->cg_eftype);
        }
    }
    wk->cg_jphos = jphos_table[wk->cg_olc_ix & 0xF];
    wk->cg_olc_ix >>= 4;
    wk->cg_flip = wk->cg_se & 3;
    wk->cg_prio = (wk->cg_se & 0xF) >> 2;
    wk->cg_se >>= 4;
    if (wk->cg_se) {
        sound_effect_request[wk->cg_se](wk, wk->cg_se);
    }
    if (wk->work_id == 1) {
        if (wk->cg_rival == 0) {
            wk->curr_rca = 0;
        } else {
            wk->curr_rca = wk->rival_catch_tbl + (wk->cg_rival - 16 + ((PLW*)wk)->tsukami_num);
        }
    }
    wk->cg_olc = wk->olc_ix_table[wk->cg_olc_ix];
    wk->cg_ja = wk->hit_ix_table[wk->cg_hit_ix];
    set_jugde_area(wk);
    if (wk->cg_type != 0xFF) {
        if (wk->cg_type & 0x80) {
            wk->cg_wca_ix = wk->cg_type & 0x7F;
            wk->cg_type = 0;
        }
    }
}



void set_new_attnum(WORK* wk) {
    s16 aag_sw;
    static u16 att_req;
    wk->renew_attack = wk->cg_att_ix;
    att_req = ++att_req & 0x7FFF;
    aag_sw = 0;
    if (wk->cg_att_ix < 0) {
        wk->cg_att_ix = -wk->cg_att_ix;
        wk->attack_num = att_req;
        wk->att_hit_ok = 1;
        wk->meoshi_hit_flag = 0;
        aag_sw = 1;
        if (wk->work_id == 1) {
            ((PLW*)wk)->caution_flag = 1;
        }
    }
    wk->att = *(wk->att_ix_table + wk->cg_att_ix);
    wk->zu_flag = wk->att.reaction & 1;
    wk->at_attribute = wk->att.reaction & 0xE;
    wk->at_attribute >>= 1;
    wk->kezuri_pow = wk->att.reaction & 0xF0;
    wk->kezuri_pow >>= 4;
    wk->att.reaction >>= 8;
    wk->add_arts_point = wk->att.piyo >> 4;
    wk->att.piyo &= 0xF;
    wk->buttobi_type = wk->att.guard >> 6;
    wk->att.guard &= 0x3F;
    wk->no_death_attack = wk->buttobi_type & 1;
    wk->buttobi_type >>= 1;
    wk->att_zuru = wk->att.dipsw >> 4;
    wk->att.dipsw &= 0xF;
    wk->vs_id = wk->att.dir >> 4;
    wk->att.dir &= 0xF;
    wk->dir_atthit = cal_attdir(wk);
    if (aag_sw) {
        add_sp_arts_gauge_init((PLW*)wk);
    }
}



void set_jugde_area(WORK* wk) {
    wk->h_bod = wk->body_adrs + wk->cg_ja.boix;
    wk->h_att = wk->attack_adrs + wk->cg_ja.atix;
    wk->h_cau = wk->caught_adrs + wk->cg_ja.cuix;
    wk->h_hos = wk->hosei_adrs + wk->cg_ja.hoix;
}

/* provisional name */
void set_char_olc_data(WORK* wk) {
    wk->cg_olc = wk->olc_ix_table[wk->cg_olc_ix];
}



void get_char_data_zanzou(WORK* wk) {
    if (wk->cg_att_ix) {
        set_new_attnum(wk);
    }
    wk->cg_ja = wk->hit_ix_table[wk->cg_hit_ix];
    set_jugde_area(wk);
}
