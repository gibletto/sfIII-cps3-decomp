#ifndef CHARMOVE_2_H
#define CHARMOVE_2_H

#include "structs.h"

s32 comm_rapp(WORK* wk, CHAR_CMD* ctc);
s32 comm_rapk(WORK* wk, CHAR_CMD* ctc);
s32 comm_back(WORK* wk, CHAR_CMD* ctc);
s32 comm_wcne2(WORK* wk, CHAR_CMD* ctc);
s32 comm_wclt2(WORK* wk, CHAR_CMD* ctc);
s32 comm_rapp2(WORK* wk, CHAR_CMD* ctc);
s32 comm_rapk2(WORK* wk, CHAR_CMD* ctc);
s32 get_comm_if_shot(WORK* wk);
s32 get_comm_if_lvsh(WORK* wk);
s32 get_comm_djmp_lever_dir(PLW* wk);
void check_cgd_patdat(WORK* wk);
s32 comm_asxy(WORK* wk, CHAR_CMD* ctc);
s32 comm_atmf(PLW* wk, CHAR_CMD* ctc);
s32 comm_ccch(WORK* wk, CHAR_CMD* ctc);
s32 comm_chkwf(PLW* wk, CHAR_CMD* ctc);
s32 comm_emhp(WORK* wk, CHAR_CMD* ctc);
s32 comm_epcy(WORK* wk, CHAR_CMD* ctc);
s32 comm_iflg(WORK* wk, CHAR_CMD* ctc);
s32 comm_imgc(PLW* wk, CHAR_CMD* ctc);
s32 comm_ixbw(WORK* wk, CHAR_CMD* ctc);
s32 comm_mpcy(WORK* wk, CHAR_CMD* ctc);
s32 comm_mvix(WORK* wk, CHAR_CMD* ctc);
s32 comm_myhp(WORK* wk, CHAR_CMD* ctc);
s32 comm_rv_x(WORK* wk, CHAR_CMD* ctc);
s32 comm_rv_y(WORK* wk, CHAR_CMD* ctc);
s32 comm_rvxy(WORK* wk, CHAR_CMD* ctc);
s32 comm_s123(WORK* wk, CHAR_CMD* ctc);
s32 comm_s456(WORK* wk, CHAR_CMD* ctc);
s32 comm_schx(WORK* wk, CHAR_CMD* ctc);
s32 comm_smhf(WORK* wk, CHAR_CMD* ctc);
s32 comm_stop(PLW*, CHAR_CMD*);
s32 comm_wadd(WORK* wk, CHAR_CMD* ctc);
s32 comm_wset(WORK* wk, CHAR_CMD* ctc);
s32 comm_ixfw(WORK* wk, CHAR_CMD* ctc);
s32 comm_quax(WORK* wk, CHAR_CMD* ctc);
s32 comm_quay(WORK* wk, CHAR_CMD* ctc);
s32 comm_if_s(WORK* wk, CHAR_CMD* ctc);
s32 comm_gets(WORK* wk, CHAR_CMD* ctc);
s32 comm_a123(WORK* wk, CHAR_CMD* ctc);
s32 comm_a456(WORK* wk, CHAR_CMD* ctc);
s32 comm_ngme(WORK* wk, CHAR_CMD* ctc);
s32 comm_ngem(WORK* wk, CHAR_CMD* ctc);
s32 comm_iflb(WORK* wk, CHAR_CMD* ctc);
s32 comm_schy(WORK* wk, CHAR_CMD* ctc);
s32 comm_sajp(WORK* wk, CHAR_CMD* ctc);
s32 comm_wswk(WORK* wk, CHAR_CMD* ctc);
s32 comm_wceq(WORK* wk, CHAR_CMD* ctc);
s32 comm_wcne(WORK* wk, CHAR_CMD* ctc);
s32 comm_wcgt(WORK* wk, CHAR_CMD* ctc);
s32 comm_wclt(WORK* wk, CHAR_CMD* ctc);
s32 comm_wadd2(WORK* wk, CHAR_CMD* ctc);
s32 comm_wceq2(WORK* wk, CHAR_CMD* ctc);
s32 comm_wcgt2(WORK* wk, CHAR_CMD* ctc);
s32 comm_imgs(PLW* wk, CHAR_CMD* ctc);
s32 comm_ccfl(PLW* wk, CHAR_CMD* ctc);
u32 comm_exbgs(WORK* wk, CHAR_CMD* ctc);
u32 comm_exbgc(WORK* wk);
void set_char_olc_data(WORK* wk);
s32 decord_if_jump(WORK* wk, CHAR_CMD* cpc, s16 ix);
void get_char_data_zanzou(WORK* wk);
s32 get_comm_if_lever(WORK* wk);
void set_jugde_area(WORK* wk);
void set_new_attnum(WORK* wk);
void setup_comm_back(WORK* wk);

#endif
