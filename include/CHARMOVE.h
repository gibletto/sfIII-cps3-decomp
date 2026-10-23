#ifndef CHARMOVE_H
#define CHARMOVE_H

#include "structs.h"

void char_move_cmms(WORK* wk);
void char_move_cmms2(WORK* wk);
s32 comm_djmp(WORK* wk, CHAR_CMD* ctc);
s32 comm_uja(WORK* wk, CHAR_CMD* ctc);
s32 comm_uja2(WORK* wk, CHAR_CMD* ctc);
s32 comm_uja3(WORK* wk, CHAR_CMD* ctc);
s32 comm_uja4(WORK* wk, CHAR_CMD* _p1);
s32 comm_uja5(WORK* wk, CHAR_CMD* _p1);
s32 comm_uja6(WORK* wk, CHAR_CMD* ctc);
s32 comm_uja7(WORK* wk, CHAR_CMD* ctc);
s32 comm_umja(WORK* wk, CHAR_CMD* _p1);
s32 comm_rngc(WORK* wk, CHAR_CMD* ctc);
s32 comm_pjmp(WORK* wk, CHAR_CMD* ctc);
void char_move(WORK* wk);
void char_move_cmj4(WORK* wk);
void char_move_cmja(WORK* wk);
void char_move_index(WORK* wk, s32 ix);   /* an int index (EFF82 effect_82_move passes a _divls quotient) */
void char_move_wca(WORK* wk);
void char_move_wca_init(WORK* wk);
void char_move_z(WORK* wk);
s32 comm_addr(WORK*, CHAR_CMD*);
s32 comm_cafr(WORK* wk, CHAR_CMD* ctc);
s32 comm_care(WORK* wk, CHAR_CMD* ctc);
s32 comm_exec(WORK* wk, CHAR_CMD* ctc);
s32 comm_for(WORK*, CHAR_CMD*);
s32 comm_for2(WORK*, CHAR_CMD*);
u32 comm_jmp(WORK* wk, CHAR_CMD* ctc);
s32 comm_jpss(WORK* wk, CHAR_CMD* ctc);
s32 comm_jsr(WORK* wk, CHAR_CMD* ctc);
s32 comm_mdat(WORK* wk, CHAR_CMD* ctc);
s32 comm_mpos(WORK* wk, CHAR_CMD* ctc);
s32 comm_mxyt(WORK* wk, CHAR_CMD* ctc);
s32 comm_nex(WORK*, CHAR_CMD*);
s32 comm_nex2(WORK*, CHAR_CMD*);
s32 comm_paxy(WORK* wk, CHAR_CMD* ctc);
s32 comm_ps_x(WORK* wk, CHAR_CMD* ctc);
s32 comm_ps_y(WORK* wk, CHAR_CMD* ctc);
s32 comm_psxy(WORK* wk, CHAR_CMD* ctc);
s32 char_move_cmoa();
s32 comm_rja(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja2(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja3(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja4(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja5(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja6(WORK* wk, CHAR_CMD* ctc);
s32 comm_rja7(WORK* wk, CHAR_CMD* ctc);
s32 comm_rmja(WORK* wk, CHAR_CMD* ctc);
s32 comm_roa(WORK*, CHAR_CMD*);
s32 comm_setr(WORK*, CHAR_CMD*);
s32 comm_sps(WORK* wk, CHAR_CMD* ctc);
s32 comm_wca(WORK* wk, CHAR_CMD* _p1);
u32 comm_end(WORK* wk, CHAR_CMD* ctc);
s32 comm_ret(WORK*, CHAR_CMD*);
s32 comm_if_l(WORK* wk, CHAR_CMD* ctc);
s32 comm_ydat(WORK* wk, CHAR_CMD* ctc);
s32 comm_pa_x(WORK* wk, CHAR_CMD* ctc);
s32 comm_pa_y(WORK* wk, CHAR_CMD* ctc);
s32 comm_hjmp(WORK* wk, CHAR_CMD* ctc);
s32 comm_hclr(WORK* wk, CHAR_CMD* _p1);
void char_move_cmj2(WORK* wk);
void char_move_cmj3(WORK* wk);
void exset_char_move_init(WORK* wk, s16 koc, s32 index);
void set_char_move_init2(WORK* wk, s16 koc, s16 index, s16 ip, s16 scf);
u32 comm_dummy(void);
void set_char_move_init();

#endif
