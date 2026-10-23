/*
 * CHARSET_TBL.C  tables read by CHARMOVE.c
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 jphos_table[];
extern s32 (*const comm_jmp_tbl[])(PLW* wk, CHAR_CMD* cpc);
extern s32 (*const comm_if_jmp_tbl[])(WORK* wk, CHAR_CMD* ctc);
extern const u16 acatkoa_table[];
extern void comm_a123();
extern void comm_a456();
extern void comm_addr();
extern void comm_asxy();
extern void comm_atmf();
extern void comm_back();
extern void comm_cafr();
extern void comm_care();
extern void comm_ccch();
extern void comm_ccfl();
extern void comm_chkwf();
extern void comm_djmp();
extern void comm_dummy();
extern void comm_emhp();
extern void comm_end();
extern void comm_epcy();
extern void comm_exbgc();
extern void comm_exbgs();
extern void comm_exec();
extern void comm_for();
extern void comm_for2();
extern void comm_gets();
extern void comm_hclr();
extern void comm_hjmp();
extern void comm_if_l();
extern void comm_if_s();
extern void comm_iflb();
extern void comm_iflg();
extern void comm_imgc();
extern void comm_imgs();
extern void comm_ixbw();
extern void comm_ixfw();
extern void comm_jmp();
extern void comm_jpss();
extern void comm_jsr();
extern void comm_mdat();
extern void comm_mpcy();
extern void comm_mpos();
extern void comm_mvix();
extern void comm_mxyt();
extern void comm_myhp();
extern void comm_nex();
extern void comm_nex2();
extern void comm_ngem();
extern void comm_ngme();
extern void comm_pa_x();
extern void comm_pa_y();
extern void comm_paxy();
extern void comm_pjmp();
extern void comm_ps_x();
extern void comm_ps_y();
extern void comm_psxy();
extern void comm_quax();
extern void comm_quay();
extern void comm_rapk();
extern void comm_rapk2();
extern void comm_rapp();
extern void comm_rapp2();
extern void comm_ret();
extern void comm_rja();
extern void comm_rja2();
extern void comm_rja3();
extern void comm_rja4();
extern void comm_rja5();
extern void comm_rja6();
extern void comm_rja7();
extern void comm_rmja();
extern void comm_rngc();
extern void comm_roa();
extern void comm_rv_x();
extern void comm_rv_y();
extern void comm_rvxy();
extern void comm_s123();
extern void comm_s456();
extern void comm_sajp();
extern void comm_schx();
extern void comm_schy();
extern void comm_setr();
extern void comm_smhf();
extern void comm_sps();
extern void comm_stop();
extern void comm_uja();
extern void comm_uja2();
extern void comm_uja3();
extern void comm_uja4();
extern void comm_uja5();
extern void comm_uja6();
extern void comm_uja7();
extern void comm_umja();
extern void comm_wadd();
extern void comm_wadd2();
extern void comm_wca();
extern void comm_wceq();
extern void comm_wceq2();
extern void comm_wcgt();
extern void comm_wcgt2();
extern void comm_wclt();
extern void comm_wclt2();
extern void comm_wcne();
extern void comm_wcne2();
extern void comm_wset();
extern void comm_wswk();
extern void comm_ydat();

const s16 jphos_table[16] = {
    0, -16, -12, -8, -4, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44,
};

s32 (*const comm_jmp_tbl[102])(PLW* wk, CHAR_CMD* cpc) = {
    comm_dummy, comm_roa, comm_end, comm_jmp, comm_jpss, comm_jsr, comm_ret, comm_sps,
    comm_setr, comm_addr, comm_if_l, comm_djmp, comm_for, comm_nex, comm_for2, comm_nex2,
    comm_rja, comm_uja, comm_rja2, comm_uja2, comm_rja3, comm_uja3, comm_rja4, comm_uja4,
    comm_rja5, comm_uja5, comm_rja6, comm_uja6, comm_rja7, comm_uja7, comm_rmja, comm_umja,
    comm_mdat, comm_ydat, comm_mpos, comm_cafr, comm_care, comm_psxy, comm_ps_x, comm_ps_y,
    comm_paxy, comm_pa_x, comm_pa_y, comm_exec, comm_rngc, comm_mxyt, comm_pjmp, comm_hjmp,
    comm_hclr, comm_ixfw, comm_ixbw, comm_quax, comm_quay, comm_if_s, comm_rapp, comm_rapk,
    comm_gets, comm_s123, comm_s456, comm_a123, comm_a456, comm_stop, comm_smhf, comm_ngme,
    comm_ngem, comm_iflb, comm_asxy, comm_schx, comm_schy, comm_back, comm_mvix, comm_sajp,
    comm_ccch, comm_wset, comm_wswk, comm_wadd, comm_wceq, comm_wcne, comm_wcgt, comm_wclt,
    comm_wadd2, comm_wceq2, comm_wcne2, comm_wcgt2, comm_wclt2, comm_rapp2, comm_rapk2, comm_iflg,
    comm_mpcy, comm_epcy, comm_imgs, comm_imgc, comm_rvxy, comm_rv_x, comm_rv_y, comm_ccfl,
    comm_myhp, comm_emhp, comm_exbgs, comm_exbgc, comm_atmf, comm_chkwf,
};

s32 (*const comm_if_jmp_tbl[14])(WORK* wk, CHAR_CMD* ctc) = {
    comm_dummy, comm_ret, comm_uja, comm_uja2, comm_uja3, comm_uja4, comm_uja5, comm_uja6,
    comm_uja7, comm_umja, comm_back, comm_nex, comm_nex2, comm_wca,
};

const u16 acatkoa_table[80] = {
    4, 4, 8, 8, 8, 8, 8, 8, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
