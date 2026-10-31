/*
 * EFFECT.C  Effect work manager
 *
 * All effect objects live in 128 work blocks (frw) taken from a free queue and linked into one of
 * eight execution lists. effect_work_init builds the queue; pull_effect_work (or
 * effect_work_pull_link, to insert beside a given work) takes a block for a list, and
 * push_effect_work unlinks, clears and returns it. move_effect_work runs one list per call, calling
 * each work's move routine through effmovejptbl by id; a timing stamp stops a work pulled during the
 * pass from running twice. effect_work_quick_init / _quick_clear and the list walkers free whole
 * lists, effect_work_kill marks works dead and search_effect_index finds a work by id. Also here:
 * work_init_zero, the per-player shell list helpers (write/erase/get/clear_my_shell_ix,
 * setup_shell_hit_stop) and small setters called from character move data (status, caution,
 * extra-BG, meoshi hit, step move: exec_char_asxy).
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "aboutspr.h"
#include "effect_2.h"
#include "EFFECT.h"

u32 frw[128][512];  /* 0201DE04 */
u8 frw_tail[4];  /* after frw; nothing refers to it by name or address */
s16 frwque[128];  /* 0205DE08 */
s16 frwctr;  /* 0205DF08 */
s16 head_ix[8];  /* 0205DF0A */
s16 tail_ix[8];  /* 0205DF1A */
s16 exec_tm[8];  /* 0205DF2A */


void move_effect_work(s16 index) {
    s16 curr_ix;
    s16 next_ix;
    WORK* c_addr;
    exec_tm[index]++;
    curr_ix = head_ix[index];
    while (curr_ix != -1) {
        c_addr = (WORK*)frw[curr_ix];
        next_ix = c_addr->behind;
        if (c_addr->timing != exec_tm[index]) {
            c_addr->timing = exec_tm[index];
            effmovejptbl[c_addr->id](c_addr);
        }
        curr_ix = next_ix;
    }
}


void effect_work_init(void) {
    WORK* c_addr;
    s16 i;
    work_init_zero((s32*)frw, sizeof(frw));
    for (i = 0; i < 128; i++) {
        frwctr = (128 - 1) - i;
        c_addr = (WORK*)frw[frwctr];
        frwque[i] = c_addr->myself = frwctr;
        c_addr->before = c_addr->behind = -1;
    }
    frwctr = 128;
    for (i = 0; i < 8; i++) {
        *(s16*)&head_ix[i] = tail_ix[i] = -1;
        exec_tm[i] = 0;
    }
}


void effect_work_quick_init(void) {
    s16 i;
    for (i = 0; i < 8; i += 1) {
        effect_work_list_release(i, -1);
    }
}


/* provisional name */
void effect_work_quick_clear(void) {
    s16 i;
    for (i = 0; i < 8; i += 1) {
        effect_work_list_init(i, -1);
    }
}


/* provisional name */
void effect_work_list_release(lix, iid)
s16 lix;
s16 iid;
{
    WORK* c_addr;
    s16 curr_ix;
    s16 next_ix;
    curr_ix = head_ix[lix];
    if (iid == -1) {
        while (curr_ix != -1) {
            c_addr = (WORK*)frw[curr_ix];
            next_ix = c_addr->behind;
            all_cgps_put_back((WORK_Other*)c_addr);
            push_effect_work(c_addr);
            curr_ix = next_ix;
        }
        exec_tm[lix] = 0;
    } else {
        while (curr_ix != -1) {
            c_addr = (WORK*)frw[curr_ix];
            next_ix = c_addr->behind;
            if (c_addr->id == iid) {
                all_cgps_put_back((WORK_Other*)c_addr);
                push_effect_work(c_addr);
            }
            curr_ix = next_ix;
        }
    }
}


void effect_work_list_init(lix, iid)
s16 lix;
s16 iid;
{
    WORK* c_addr;
    s16 curr_ix;
    s16 next_ix;

    curr_ix = head_ix[lix];
    if (iid == -1) {
        while (curr_ix != -1) {
            c_addr = (WORK*)frw[curr_ix];
            next_ix = c_addr->behind;
            push_effect_work(c_addr);
            curr_ix = next_ix;
        }
        exec_tm[lix] = 0;
    } else {
        while (curr_ix != -1) {
            c_addr = (WORK*)frw[curr_ix];
            next_ix = c_addr->behind;
            if (c_addr->id == iid) {
                push_effect_work(c_addr);
            }
            curr_ix = next_ix;
        }
    }
}


/* Takes an effect work from the free queue and links it into list `index`; returns its slot index, -1 when none is free. */
s32 pull_effect_work(index)
s16 index;
{
    s16 qix;
    s16* ixp;
    WORK* tadr;
    WORK* wrk;
    if (frwctr < 1) {
        return -1;
    }
    qix = frwque[--frwctr];
    tadr = (WORK*)frw[qix];
    if (head_ix[index] == -1) {
        ixp = &head_ix[index];
        tail_ix[index] = qix;
        *ixp = qix;
    } else {
        ixp = &tail_ix[index];
        wrk = (WORK*)frw[*ixp];
        wrk->behind = qix;
        tadr->before = *ixp;
        *ixp = qix;
    }
    tadr->timing = exec_tm[index];
    tadr->listix = index;
    return qix;
}


/* provisional name */
s32 effect_work_pull_link(s16 index, s16 before, s16 aix) {
    s16 qix;
    WORK* tadr;
    WORK* wrk;
    if (aix == -1) {
        return pull_effect_work(index);
    }
    if (frwctr < 1) {
        return -1;
    }
    qix = frwque[--frwctr];
    tadr = (WORK*)&frw[qix];
    wrk = (WORK*)&frw[aix];
    if (before != 0) {
        if ((tadr->before = wrk->before) == -1) {
            head_ix[index] = qix;
        }
        tadr->behind = aix;
        wrk->before = qix;
    } else {
        if ((tadr->behind = wrk->behind) == -1) {
            tail_ix[index] = qix;
        }
        tadr->before = aix;
        wrk->behind = qix;
    }
    tadr->timing = exec_tm[index];
    tadr->listix = index;
    return qix;
}


s32 search_effect_index(index, flag, tid)
s16 index;
s16 flag;
s16 tid;
{
    WORK* c_addr;
    s16 aix;
    if (flag) {
        aix = tail_ix[index];
        while (aix != -1) {
            c_addr = (WORK*)frw[aix];
            if (c_addr->id == tid) {
                break;
            }
            aix = c_addr->before;
        }
    } else {
        aix = head_ix[index];
        while (aix != -1) {
            c_addr = (WORK*)frw[aix];
            if (c_addr->id == tid) {
                break;
            }
            aix = c_addr->behind;
        }
    }
    return aix;
}


/* Unlinks an effect work and returns it to the free queue; returns its slot index. */
s32 push_effect_work(WORK* wkhd) {
    WORK* c_addr;
    WORK* c_addr2;
    s16 qix;
    s16 lix;
    lix = wkhd->listix;
    qix = wkhd->myself;
    c_addr = (WORK*)frw[qix];
    switch ((head_ix[lix] == qix) + (tail_ix[lix] == qix) * 2) {
    case 0:
        c_addr2 = (WORK*)frw[c_addr->before];
        c_addr2->behind = c_addr->behind;
        c_addr2 = (WORK*)frw[c_addr->behind];
        c_addr2->before = c_addr->before;
        break;
    case 1:
        head_ix[lix] = c_addr->behind;
        c_addr2 = (WORK*)frw[c_addr->behind];
        c_addr2->before = -1;
        break;
    case 2:
        c_addr2 = (WORK*)frw[c_addr->before];
        c_addr2->behind = -1;
        tail_ix[lix] = c_addr->before;
        break;
    default:
        head_ix[lix] = tail_ix[lix] = -1;
        break;
    }
    work_init_zero((s32*)frw[qix], sizeof(frw[0]));
    c_addr->before = c_addr->behind = -1;
    c_addr->myself = frwque[frwctr++] = qix;
}


void effect_work_kill(s16 index, s16 kill_id) {
    s16 aix;
    WORK* c_addr;
    aix = head_ix[index];
    if (kill_id == -1) {
        for (; aix != -1; aix = c_addr->behind) {
            c_addr = (WORK*)frw[aix];
            c_addr->dead_f = 1;
        }
    } else {
        for (; aix != -1; aix = c_addr->behind) {
            c_addr = (WORK*)frw[aix];
            if (c_addr->id == kill_id) {
                c_addr->dead_f = 1;
            }
        }
    }
}


/* provisional name */
s16 get_frwctr(void) {
    return frwctr;
}


void work_init_zero(s32* adrs_int, s32 xx) {
    s32 i;
    s32 surr;
    s8* adrs_char;
    surr = (u32)xx % 4;
    xx /= 4;
    for (i = 0; i < xx; i++) {
        *adrs_int++ = 0;
    }
    if (surr != 0) {
        adrs_char = (s8*)adrs_int;
        for (i = 0; i < surr; i++) {
            *adrs_char++ = 0;
        }
    }
}


void write_my_shell_ix(WORK* wk, s16 ix) {
    s32 i;
    if ((i = 7) >= 1) {
        do {
            *(i + wk->shell_ix) = wk->shell_ix[i - 1];
            i--;
        } while (i > 0);
    }
    wk->shell_ix[0] = ix;
}


s32 erase_my_shell_ix(WORK* wk, s16 ix) {
    s32 i;
    s32 j;
    for (i = 0; i < 8; i++) {
        if (wk->shell_ix[i] != ix) {
            continue;
        }
        goto ok;
    }
    return 0;
ok:
    for (j = i; j < 7; j++) {
        wk->shell_ix[j] = wk->shell_ix[j + 1];
    }
    wk->shell_ix[7] = -1;
    return 1;
}


s32 get_my_shell_ix(wk, ix, tmw)
WORK* wk;
s16 ix;
WORK** tmw;
{
    if (wk->shell_ix[ix] == -1) {
        return 0;
    }
    *tmw = (WORK*)frw[wk->shell_ix[ix]];
    if ((*tmw)->be_flag) {
        return 1;
    }
    return 0;
}


void clear_my_shell_ix(WORK* wk) {
    s32 i;
    for (i = 0; i < 8; i++) {
        wk->shell_ix[i] = -1;
    }
}


void setup_shell_hit_stop(WORK* wk, s16 tm, s16 fl) {
    WORK* tmw;
    s32 i;
    for (i = 0; i < 8; i++) {
        if (get_my_shell_ix(wk, i, &tmw) != 0 && (fl == 0 || tmw->id != 0x29)) {
            if (tmw->hit_stop < 0) {
                tmw->hit_stop = -tmw->hit_stop;
            }
            tmw->hit_stop += tm;
        }
    }
}


/* Clear the player's caution (guard-warning) flag. */
void clear_caution_flag(PLW* wk) {
    wk->caution_flag = 0;
}

/* Set the player's caution (guard-warning) flag. */
void set_caution_flag(PLW* wk) {
    wk->caution_flag = 1;
}


void setup_status_flag(WORK* wk, u8 status) {
    wk->pat_status = status;
}


void reset_extra_bg_flag(WORK* wk) {
    another_bg[wk->id] = 0;
}

void flip_my_rl_flag(WORK* wk) {
    wk->rl_flag = ((u8)wk->rl_flag + 1U) & 1;
}


void setup_meoshi_hit_flag(WORK* wk, u8 flag) {
    wk->meoshi_hit_flag = flag;
}

s32 exec_char_asxy(WORK* wk, u8 data) {
    s16* from_rom2;
    s32 st;
    s16 ix = data;
    ix *= 2;
    from_rom2 = &wk->step_xy_table[ix];
    st = *from_rom2++;
    st *= 256;
    if (wk->rl_flag) {
        wk->xyz[0].cal += st;
    } else {
        wk->xyz[0].cal -= st;
    }
    st = *from_rom2;
    st *= 256;
    wk->xyz[1].cal += st;
}
