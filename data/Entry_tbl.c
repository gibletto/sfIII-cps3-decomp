/*
 * ENTRY_TBL.C  debug monitor and disassembler strings and opcode tables
 *
 * monitor_msg_tbl holds the text lines of the exception monitor (exception names, title and
 * register lines), and dbg_dump_title and dbg_disasm_title the memory dump and disassembly
 * headers. The sh_op_*_tbl lists give { opcode, mnemonic } pairs for each SH-2 operand form,
 * ending with 0xFFFF; sh_mn_* are the mnemonic strings and sh_str_* the monitor text. Read by
 * ENTRY_DBG.C, the debug screens. str_R0 .. str_SP are the register names, reached through
 * reg_name_tbl in WORK.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const TM_STRING monitor_msg_tbl[];
extern const TM_STRING dbg_dump_title[];
extern const TM_STRING dbg_disasm_title[];
extern const MoveName sh_op_none_tbl[];
extern const MoveName sh_op_ldm_tbl[];
extern const MoveName sh_op_n_tbl[];
extern const MoveName sh_op_nm_tbl[];
extern const MoveName sh_op_disp_m_tbl[];
extern const MoveName sh_op_disp_n_tbl[];
extern const MoveName sh_op_d8_tbl[];
extern const MoveName sh_op_imm_tbl[];
extern const MoveName sh_op_disp4_tbl[];
extern const MoveName sh_op_d12_tbl[];
extern const MoveName sh_op_pcrel_tbl[];
extern const MoveName sh_op_imm_n_tbl[];
extern const char sh_str_break[];
extern const char sh_str_rm[];
extern const char sh_str_rn[];
extern const char sh_str_undef[];
extern const char sh_str_monitor_entry[];
extern const char sh_str_illegal_inst[];
extern const char sh_str_slot_illegal_inst[];
extern const char sh_str_cpu_addr_error[];
extern const char sh_str_dma_addr_error[];
extern const char sh_str_unknown_exception[];
extern const char sh_str_monitor_title[];
extern const char sh_str_regs_r0_r2[];
extern const char sh_str_regs_r3_r5[];
extern const char sh_str_regs_r6_r8[];
extern const char sh_str_regs_r9_r11[];
extern const char sh_str_regs_r12_r14[];
extern const char sh_str_regs_sp_pc[];
extern const char sh_str_regs_pr_gbr[];
extern const char sh_str_dump_header[];
extern const char sh_str_disasm_header[];
extern const char sh_mn_clrt[];
extern const char sh_mn_nop[];
extern const char sh_mn_rts[];
extern const char sh_mn_sett[];
extern const char sh_mn_div0u[];
extern const char sh_mn_sleep[];
extern const char sh_mn_clrmac[];
extern const char sh_mn_rte[];
extern const char sh_mn_ldsl_rminc_mach[];
extern const char sh_mn_ldcl_rminc_sr[];
extern const char sh_mn_lds_rm_mach[];
extern const char sh_mn_ldc_rm_sr[];
extern const char sh_mn_ldsl_rminc_macl[];
extern const char sh_mn_ldcl_rminc_gbr[];
extern const char sh_mn_lds_rm_macl[];
extern const char sh_mn_ldc_rm_gbr[];
extern const char sh_mn_ldsl_rminc_pr[];
extern const char sh_mn_ldcl_rminc_vbr[];
extern const char sh_mn_lds_rm_pr[];
extern const char sh_mn_ldc_rm_vbr[];
extern const char sh_mn_stc_sr_rn[];
extern const char sh_mn_bsrf_rn[];
extern const char sh_mn_sts_mach_rn[];
extern const char sh_mn_stc_gbr_rn[];
extern const char sh_mn_sts_macl_rn[];
extern const char sh_mn_stc_vbr_rn[];
extern const char sh_mn_braf_rn[];
extern const char sh_mn_movt_rn[];
extern const char sh_mn_sts_pr_rn[];
extern const char sh_mn_cmp_pl_rn[];
extern const char sh_mn_cmp_pz_rn[];
extern const char sh_mn_dt_rn[];
extern const char sh_mn_tasb_atrn[];
extern const char sh_mn_rotl_rn[];
extern const char sh_mn_rotr_rn[];
extern const char sh_mn_rotcl_rn[];
extern const char sh_mn_rotcr_rn[];
extern const char sh_mn_shal_rn[];
extern const char sh_mn_shar_rn[];
extern const char sh_mn_shll_rn[];
extern const char sh_mn_shlr_rn[];
extern const char sh_mn_shll2_rn[];
extern const char sh_mn_shlr2_rn[];
extern const char sh_mn_shll8_rn[];
extern const char sh_mn_shlr8_rn[];
extern const char sh_mn_shll16_rn[];
extern const char sh_mn_shlr16_rn[];
extern const char sh_mn_jmp_atrn[];
extern const char sh_mn_jsr_atrn[];
extern const char sh_mn_stcl_sr_decrn[];
extern const char sh_mn_stcl_gbr_decrn[];
extern const char sh_mn_stcl_vbr_decrn[];
extern const char sh_mn_stsl_mach_decrn[];
extern const char sh_mn_stsl_macl_decrn[];
extern const char sh_mn_stsl_pr_decrn[];
extern const char sh_mn_movb_rm_r0rn[];
extern const char sh_mn_movw_rm_r0rn[];
extern const char sh_mn_movl_rm_r0rn[];
extern const char sh_mn_mull_rm_rn[];
extern const char sh_mn_movb_r0rm_rn[];
extern const char sh_mn_movw_r0rm_rn[];
extern const char sh_mn_movl_r0rm_rn[];
extern const char sh_mn_macl_rminc_rninc[];
extern const char sh_mn_movb_rm_atrn[];
extern const char sh_mn_movw_rm_atrn[];
extern const char sh_mn_movl_rm_atrn[];
extern const char sh_mn_movb_rm_decrn[];
extern const char sh_mn_movw_rm_decrn[];
extern const char sh_mn_movl_rm_decrn[];
extern const char sh_mn_div0s_rm_rn[];
extern const char sh_mn_tst_rm_rn[];
extern const char sh_mn_and_rm_rn[];
extern const char sh_mn_xor_rm_rn[];
extern const char sh_mn_or_rm_rn[];
extern const char sh_mn_cmp_str_rm_rn[];
extern const char sh_mn_xtrct_rm_rn[];
extern const char sh_mn_muluw_rm_rn[];
extern const char sh_mn_mulsw_rm_rn[];
extern const char sh_mn_cmp_eq_rm_rn[];
extern const char sh_mn_cmp_hs_rm_rn[];
extern const char sh_mn_cmp_ge_rm_rn[];
extern const char sh_mn_div1_rm_rn[];
extern const char sh_mn_dmulul_rm_rn[];
extern const char sh_mn_cmp_hi_rm_rn[];
extern const char sh_mn_sub_rm_rn[];
extern const char sh_mn_subc_rm_rn[];
extern const char sh_mn_subv_rm_rn[];
extern const char sh_mn_add_rm_rn[];
extern const char sh_mn_dmulsl_rm_rn[];
extern const char sh_mn_addc_rm_rn[];
extern const char sh_mn_addv_rm_rn[];
extern const char sh_mn_macw_rminc_rninc[];
extern const char sh_mn_movb_atrm_rn[];
extern const char sh_mn_movw_atrm_rn[];
extern const char sh_mn_movl_atrm_rn[];
extern const char sh_mn_mov_rm_rn[];
extern const char sh_mn_movb_rminc_rn[];
extern const char sh_mn_movw_rminc_rn[];
extern const char sh_mn_movl_rminc_rn[];
extern const char sh_mn_not_rm_rn[];
extern const char sh_mn_swapb_rm_rn[];
extern const char sh_mn_swapw_rm_rn[];
extern const char sh_mn_negc_rm_rn[];
extern const char sh_mn_neg_rm_rn[];
extern const char sh_mn_extub_rm_rn[];
extern const char sh_mn_extuw_rm_rn[];
extern const char sh_mn_extsb_rm_rn[];
extern const char sh_mn_extsw_rm_rn[];
extern const char sh_mn_movb_disprm_r0[];
extern const char sh_mn_movw_disprm_r0[];
extern const char sh_mn_movb_r0_disprn[];
extern const char sh_mn_movw_r0_disprn[];
extern const char sh_mn_bt_label[];
extern const char sh_mn_bf_label[];
extern const char sh_mn_bt_s_label[];
extern const char sh_mn_bf_s_label[];
extern const char sh_mn_movb_r0_dispgbr[];
extern const char sh_mn_movw_r0_dispgbr[];
extern const char sh_mn_movl_r0_dispgbr[];
extern const char sh_mn_movb_dispgbr_r0[];
extern const char sh_mn_movw_dispgbr_r0[];
extern const char sh_mn_movl_dispgbr_r0[];
extern const char sh_mn_mova_disppc_r0[];
extern const char sh_mn_cmp_eq_imm_r0[];
extern const char sh_mn_trapa_imm[];
extern const char sh_mn_tst_imm_r0[];
extern const char sh_mn_and_imm_r0[];
extern const char sh_mn_xor_imm_r0[];
extern const char sh_mn_or_imm_r0[];
extern const char sh_mn_tstb_imm_r0gbr[];
extern const char sh_mn_andb_imm_r0gbr[];
extern const char sh_mn_xorb_imm_r0gbr[];
extern const char sh_mn_orb_imm_r0gbr[];
extern const char sh_mn_movl_rm_disprn[];
extern const char sh_mn_movl_disprm_rn[];
extern const char sh_mn_bra_label[];
extern const char sh_mn_bsr_label[];
extern const char sh_mn_movw_disppc_rn[];
extern const char sh_mn_movl_disppc_rn[];
extern const char sh_mn_add_imm_rn[];
extern const char sh_mn_mov_imm_rn[];
extern const char str_R0[];
extern const char str_R1[];
extern const char str_R2[];
extern const char str_R3[];
extern const char str_R4[];
extern const char str_R5[];
extern const char str_R6[];
extern const char str_R7[];
extern const char str_R8[];
extern const char str_R9[];
extern const char str_R10[];
extern const char str_R11[];
extern const char str_R12[];
extern const char str_R13[];
extern const char str_R14[];
extern const char str_SP[];

/* provisional name */
const TM_STRING monitor_msg_tbl[14] = {
    { 1, 0x16, 0xE, (const s8 *)sh_str_monitor_entry },
    { 1, 0x16, 0xE, (const s8 *)sh_str_illegal_inst },
    { 1, 0x16, 0xE, (const s8 *)sh_str_slot_illegal_inst },
    { 1, 0x16, 0xE, (const s8 *)sh_str_cpu_addr_error },
    { 1, 0x16, 0xE, (const s8 *)sh_str_dma_addr_error },
    { 1, 0x16, 0xE, (const s8 *)sh_str_unknown_exception },
    { 0xC, 0, 0xE, (const s8 *)sh_str_monitor_title },
    { 0, 2, 0xE, (const s8 *)sh_str_regs_r0_r2 },
    { 0, 3, 0xE, (const s8 *)sh_str_regs_r3_r5 },
    { 0, 4, 0xE, (const s8 *)sh_str_regs_r6_r8 },
    { 0, 5, 0xE, (const s8 *)sh_str_regs_r9_r11 },
    { 0, 6, 0xE, (const s8 *)sh_str_regs_r12_r14 },
    { 0, 7, 0xE, (const s8 *)sh_str_regs_sp_pc },
    { 0, 8, 0xE, (const s8 *)sh_str_regs_pr_gbr },
};

const TM_STRING dbg_dump_title[1] = {
    { 0, 0xA, 0xE, (const s8 *)sh_str_dump_header },
};

const TM_STRING dbg_disasm_title[1] = {
    { 0, 0xA, 0xE, (const s8 *)sh_str_disasm_header },
};

const MoveName sh_op_none_tbl[9] = {
    { 8, (const char *)sh_mn_clrt }, { 9, (const char *)sh_mn_nop },
    { 0xB, (const char *)sh_mn_rts }, { 0x18, (const char *)sh_mn_sett },
    { 0x19, (const char *)sh_mn_div0u }, { 0x1B, (const char *)sh_mn_sleep },
    { 0x28, (const char *)sh_mn_clrmac }, { 0x2B, (const char *)sh_mn_rte },
    { 0xFFFF, 0 },
};

const MoveName sh_op_ldm_tbl[13] = {
    { 0x4006, (const char *)sh_mn_ldsl_rminc_mach },
    { 0x4007, (const char *)sh_mn_ldcl_rminc_sr },
    { 0x400A, (const char *)sh_mn_lds_rm_mach },
    { 0x400E, (const char *)sh_mn_ldc_rm_sr },
    { 0x4016, (const char *)sh_mn_ldsl_rminc_macl },
    { 0x4017, (const char *)sh_mn_ldcl_rminc_gbr },
    { 0x401A, (const char *)sh_mn_lds_rm_macl },
    { 0x401E, (const char *)sh_mn_ldc_rm_gbr },
    { 0x4026, (const char *)sh_mn_ldsl_rminc_pr },
    { 0x4027, (const char *)sh_mn_ldcl_rminc_vbr },
    { 0x402A, (const char *)sh_mn_lds_rm_pr },
    { 0x402E, (const char *)sh_mn_ldc_rm_vbr },
    { 0xFFFF, 0 },
};

const MoveName sh_op_n_tbl[36] = {
    { 2, (const char *)sh_mn_stc_sr_rn },
    { 3, (const char *)sh_mn_bsrf_rn },
    { 0xA, (const char *)sh_mn_sts_mach_rn },
    { 0x12, (const char *)sh_mn_stc_gbr_rn },
    { 0x1A, (const char *)sh_mn_sts_macl_rn },
    { 0x22, (const char *)sh_mn_stc_vbr_rn },
    { 0x23, (const char *)sh_mn_braf_rn },
    { 0x29, (const char *)sh_mn_movt_rn },
    { 0x2A, (const char *)sh_mn_sts_pr_rn },
    { 0x4015, (const char *)sh_mn_cmp_pl_rn },
    { 0x4011, (const char *)sh_mn_cmp_pz_rn },
    { 0x4010, (const char *)sh_mn_dt_rn },
    { 0x401B, (const char *)sh_mn_tasb_atrn },
    { 0x4004, (const char *)sh_mn_rotl_rn },
    { 0x4005, (const char *)sh_mn_rotr_rn },
    { 0x4024, (const char *)sh_mn_rotcl_rn },
    { 0x4025, (const char *)sh_mn_rotcr_rn },
    { 0x4020, (const char *)sh_mn_shal_rn },
    { 0x4021, (const char *)sh_mn_shar_rn },
    { 0x4000, (const char *)sh_mn_shll_rn },
    { 0x4001, (const char *)sh_mn_shlr_rn },
    { 0x4008, (const char *)sh_mn_shll2_rn },
    { 0x4009, (const char *)sh_mn_shlr2_rn },
    { 0x4018, (const char *)sh_mn_shll8_rn },
    { 0x4019, (const char *)sh_mn_shlr8_rn },
    { 0x4028, (const char *)sh_mn_shll16_rn },
    { 0x4029, (const char *)sh_mn_shlr16_rn },
    { 0x402B, (const char *)sh_mn_jmp_atrn },
    { 0x400B, (const char *)sh_mn_jsr_atrn },
    { 0x4003, (const char *)sh_mn_stcl_sr_decrn },
    { 0x4013, (const char *)sh_mn_stcl_gbr_decrn },
    { 0x4023, (const char *)sh_mn_stcl_vbr_decrn },
    { 0x4002, (const char *)sh_mn_stsl_mach_decrn },
    { 0x4012, (const char *)sh_mn_stsl_macl_decrn },
    { 0x4022, (const char *)sh_mn_stsl_pr_decrn },
    { 0xFFFF, 0 },
};

const MoveName sh_op_nm_tbl[54] = {
    { 4, (const char *)sh_mn_movb_rm_r0rn },
    { 5, (const char *)sh_mn_movw_rm_r0rn },
    { 6, (const char *)sh_mn_movl_rm_r0rn },
    { 7, (const char *)sh_mn_mull_rm_rn },
    { 0xC, (const char *)sh_mn_movb_r0rm_rn },
    { 0xD, (const char *)sh_mn_movw_r0rm_rn },
    { 0xE, (const char *)sh_mn_movl_r0rm_rn },
    { 0xF, (const char *)sh_mn_macl_rminc_rninc },
    { 0x2000, (const char *)sh_mn_movb_rm_atrn },
    { 0x2001, (const char *)sh_mn_movw_rm_atrn },
    { 0x2002, (const char *)sh_mn_movl_rm_atrn },
    { 0x2004, (const char *)sh_mn_movb_rm_decrn },
    { 0x2005, (const char *)sh_mn_movw_rm_decrn },
    { 0x2006, (const char *)sh_mn_movl_rm_decrn },
    { 0x2007, (const char *)sh_mn_div0s_rm_rn },
    { 0x2008, (const char *)sh_mn_tst_rm_rn },
    { 0x2009, (const char *)sh_mn_and_rm_rn },
    { 0x200A, (const char *)sh_mn_xor_rm_rn },
    { 0x200B, (const char *)sh_mn_or_rm_rn },
    { 0x200C, (const char *)sh_mn_cmp_str_rm_rn },
    { 0x200D, (const char *)sh_mn_xtrct_rm_rn },
    { 0x200E, (const char *)sh_mn_muluw_rm_rn },
    { 0x200F, (const char *)sh_mn_mulsw_rm_rn },
    { 0x3000, (const char *)sh_mn_cmp_eq_rm_rn },
    { 0x3002, (const char *)sh_mn_cmp_hs_rm_rn },
    { 0x3003, (const char *)sh_mn_cmp_ge_rm_rn },
    { 0x3004, (const char *)sh_mn_div1_rm_rn },
    { 0x3005, (const char *)sh_mn_dmulul_rm_rn },
    { 0x3006, (const char *)sh_mn_cmp_hi_rm_rn },
    { 0x3008, (const char *)sh_mn_sub_rm_rn },
    { 0x300A, (const char *)sh_mn_subc_rm_rn },
    { 0x300B, (const char *)sh_mn_subv_rm_rn },
    { 0x300C, (const char *)sh_mn_add_rm_rn },
    { 0x300D, (const char *)sh_mn_dmulsl_rm_rn },
    { 0x300E, (const char *)sh_mn_addc_rm_rn },
    { 0x300F, (const char *)sh_mn_addv_rm_rn },
    { 0x400F, (const char *)sh_mn_macw_rminc_rninc },
    { 0x6000, (const char *)sh_mn_movb_atrm_rn },
    { 0x6001, (const char *)sh_mn_movw_atrm_rn },
    { 0x6002, (const char *)sh_mn_movl_atrm_rn },
    { 0x6003, (const char *)sh_mn_mov_rm_rn },
    { 0x6004, (const char *)sh_mn_movb_rminc_rn },
    { 0x6005, (const char *)sh_mn_movw_rminc_rn },
    { 0x6006, (const char *)sh_mn_movl_rminc_rn },
    { 0x6007, (const char *)sh_mn_not_rm_rn },
    { 0x6008, (const char *)sh_mn_swapb_rm_rn },
    { 0x6009, (const char *)sh_mn_swapw_rm_rn },
    { 0x600A, (const char *)sh_mn_negc_rm_rn },
    { 0x600B, (const char *)sh_mn_neg_rm_rn },
    { 0x600C, (const char *)sh_mn_extub_rm_rn },
    { 0x600D, (const char *)sh_mn_extuw_rm_rn },
    { 0x600E, (const char *)sh_mn_extsb_rm_rn },
    { 0x600F, (const char *)sh_mn_extsw_rm_rn },
    { 0xFFFF, 0 },
};

const MoveName sh_op_disp_m_tbl[3] = {
    { 0x8400, (const char *)sh_mn_movb_disprm_r0 },
    { 0x8500, (const char *)sh_mn_movw_disprm_r0 },
    { 0xFFFF, 0 },
};

const MoveName sh_op_disp_n_tbl[3] = {
    { 0x8000, (const char *)sh_mn_movb_r0_disprn },
    { 0x8100, (const char *)sh_mn_movw_r0_disprn },
    { 0xFFFF, 0 },
};

const MoveName sh_op_d8_tbl[12] = {
    { 0x8900, (const char *)sh_mn_bt_label },
    { 0x8B00, (const char *)sh_mn_bf_label },
    { 0x8D00, (const char *)sh_mn_bt_s_label },
    { 0x8F00, (const char *)sh_mn_bf_s_label },
    { 0xC000, (const char *)sh_mn_movb_r0_dispgbr },
    { 0xC100, (const char *)sh_mn_movw_r0_dispgbr },
    { 0xC200, (const char *)sh_mn_movl_r0_dispgbr },
    { 0xC400, (const char *)sh_mn_movb_dispgbr_r0 },
    { 0xC500, (const char *)sh_mn_movw_dispgbr_r0 },
    { 0xC600, (const char *)sh_mn_movl_dispgbr_r0 },
    { 0xC700, (const char *)sh_mn_mova_disppc_r0 },
    { 0xFFFF, 0 },
};

const MoveName sh_op_imm_tbl[11] = {
    { 0x8800, (const char *)sh_mn_cmp_eq_imm_r0 },
    { 0xC300, (const char *)sh_mn_trapa_imm },
    { 0xC800, (const char *)sh_mn_tst_imm_r0 },
    { 0xC900, (const char *)sh_mn_and_imm_r0 },
    { 0xCA00, (const char *)sh_mn_xor_imm_r0 },
    { 0xCB00, (const char *)sh_mn_or_imm_r0 },
    { 0xCC00, (const char *)sh_mn_tstb_imm_r0gbr },
    { 0xCD00, (const char *)sh_mn_andb_imm_r0gbr },
    { 0xCE00, (const char *)sh_mn_xorb_imm_r0gbr },
    { 0xCF00, (const char *)sh_mn_orb_imm_r0gbr },
    { 0xFFFF, 0 },
};

const MoveName sh_op_disp4_tbl[3] = {
    { 0x1000, (const char *)sh_mn_movl_rm_disprn },
    { 0x5000, (const char *)sh_mn_movl_disprm_rn },
    { 0xFFFF, 0 },
};

const MoveName sh_op_d12_tbl[3] = {
    { 0xA000, (const char *)sh_mn_bra_label },
    { 0xB000, (const char *)sh_mn_bsr_label },
    { 0xFFFF, 0 },
};

const MoveName sh_op_pcrel_tbl[3] = {
    { 0x9000, (const char *)sh_mn_movw_disppc_rn },
    { 0xD000, (const char *)sh_mn_movl_disppc_rn },
    { 0xFFFF, 0 },
};

const MoveName sh_op_imm_n_tbl[3] = {
    { 0x7000, (const char *)sh_mn_add_imm_rn },
    { 0xE000, (const char *)sh_mn_mov_imm_rn },
    { 0xFFFF, 0 },
};

const char sh_str_break[8] = "Break:\0\x0C";

const char sh_str_rm[4] = "Rm\0\x0C";

const char sh_str_rn[4] = "Rn\0\x1A";

const char sh_str_undef[4] = "???";

const char sh_str_monitor_entry[16] = "Monitor Entry\0\x07\x0C";

const char sh_str_illegal_inst[28] = "Common Illigal Instruction\0\xC2";

const char sh_str_slot_illegal_inst[28] = "Slot Illigal Instruction\0\x06\xD0\xB7";

const char sh_str_cpu_addr_error[20] = "CPU Address Error\0\x18\xA8";

const char sh_str_dma_addr_error[20] = "DMA Address Error\0\x28\x01";

const char sh_str_unknown_exception[20] = "Unknown Exception\0\xA8\x4F";

const char sh_str_monitor_title[16] = "M O N I T O R\n\0\x4A";

const char sh_str_regs_r0_r2[48] = "R0  = 00000000 R1  = 00000000 R2  = 00000000\n\0\xAD\x47";

const char sh_str_regs_r3_r5[48] = "R3  = 00000000 R4  = 00000000 R5  = 00000000\n\0\x34\x01";

const char sh_str_regs_r6_r8[48] = "R6  = 00000000 R7  = 00000000 R8  = 00000000\n\0\x4A\x24";

const char sh_str_regs_r9_r11[48] = "R9  = 00000000 R10 = 00000000 R11 = 00000000\n\0\x4C\x08";

const char sh_str_regs_r12_r14[48] = "R12 = 00000000 R13 = 00000000 R14 = 00000000\n\0\xA8\x51";

const char sh_str_regs_sp_pc[32] = "SP  = 00000000 PC  = 00000000\n\0\x0C";

const char sh_str_regs_pr_gbr[32] = "PR  = 00000000 GBR = 00000000\0\x10\x10";

const char sh_str_dump_header[48] = "Address   +0   +2   +4   +6   +8   +A   +C   +E";

const char sh_str_disasm_header[48] = "Address  Code Nemonic                          ";

const char sh_mn_clrt[28] = "CLRT                    \0\x24\x24\xC4";

const char sh_mn_nop[28] = "NOP                     \0\x2C\x30\xB7";

const char sh_mn_rts[28] = "RTS                     \0\x02\x02\xC4";

const char sh_mn_sett[28] = "SETT                    \0\x32\x01\xC7";

const char sh_mn_div0u[28] = "DIV0U                   \0\x08\x08\xAD";

const char sh_mn_sleep[28] = "SLEEP                   \0\xC7\x1E\x01";

const char sh_mn_clrmac[28] = "CLRMAC                  \0\x4E\x16\x16";

const char sh_mn_rte[28] = "RTE                     \0\x7F\xAD\x45";

const char sh_mn_ldsl_rminc_mach[28] = "LDS.L   @Rm+,MACH       \0\x08\xAD\x47";

const char sh_mn_ldcl_rminc_sr[28] = "LDC.L   @Rm+,SR         \0\x18\xB2\x4E";

const char sh_mn_lds_rm_mach[28] = "LDS     Rm,MACH         \0\x16\x16\xC7";

const char sh_mn_ldc_rm_sr[28] = "LDC     Rm,SR           \0\xA8\x4A\x24";

const char sh_mn_ldsl_rminc_macl[28] = "LDS.L   @Rm+,MACL       \0\xB7\x49\x08";

const char sh_mn_ldcl_rminc_gbr[28] = "LDC.L   @Rm+,GBR        \0\xB7\x4E\x10";

const char sh_mn_lds_rm_macl[28] = "LDS     Rm,MACL         \0\x94\x4E\x0B";

const char sh_mn_ldc_rm_gbr[28] = "LDC     Rm,GBR          \0\x16\xC7\x5A";

const char sh_mn_ldsl_rminc_pr[28] = "LDS.L   @Rm+,PR         \0\x49\x0C\x0C";

const char sh_mn_ldcl_rminc_vbr[28] = "LDC.L   @Rm+,VBR        \0\x47\x04\x04";

const char sh_mn_lds_rm_pr[28] = "LDS     Rm,PR           \0\x47\x08\x08";

const char sh_mn_ldc_rm_vbr[28] = "LDC     Rm,VBR          \0\x4C\x08\x18";

const char sh_mn_stc_sr_rn[28] = "STC     SR,Rn           \0\xA8\x45\x16";

const char sh_mn_bsrf_rn[28] = "BSRF    Rn              \0\xC7\0\xA8";

const char sh_mn_sts_mach_rn[28] = "STS     MACH,Rn         \0\x10\x10\xB7";

const char sh_mn_stc_gbr_rn[28] = "STC     GBR,Rn          \0\x02\x02\xB2";

const char sh_mn_sts_macl_rn[28] = "STS     MACL,Rn         \0\0\x01\xD4";

const char sh_mn_stc_vbr_rn[28] = "STC     VBR,Rn          \0\x0F\x10\xA8";

const char sh_mn_braf_rn[28] = "BRAF    Rn              \0\x18\x18\xA8";

const char sh_mn_movt_rn[28] = "MOVT    Rn              \0\x18\x18\xA8";

const char sh_mn_sts_pr_rn[28] = "STS     PR,Rn           \0\x08\x08\xA8";

const char sh_mn_cmp_pl_rn[28] = "CMP/PL  Rn              \0\x10\x10\xA8";

const char sh_mn_cmp_pz_rn[28] = "CMP/PZ  Rn              \0\x18\x18\xA8";

const char sh_mn_dt_rn[28] = "DT      Rn              \0\x18\x18\xA8";

const char sh_mn_tasb_atrn[28] = "TAS.B   @Rn             \0\x08\x08\xA8";

const char sh_mn_rotl_rn[28] = "ROTL    Rn              \0\x0F\x10\xA8";

const char sh_mn_rotr_rn[28] = "ROTR    Rn              \0\xFF\x02\xC2";

const char sh_mn_rotcl_rn[28] = "ROTCL   Rn              \0\x20\x28\xB4";

const char sh_mn_rotcr_rn[28] = "ROTCR   Rn              \0\x10\x10\xB4";

const char sh_mn_shal_rn[28] = "SHAL    Rn              \0\x18\x18\xB2";

const char sh_mn_shar_rn[28] = "SHAR    Rn              \0\x10\x10\xB4";

const char sh_mn_shll_rn[28] = "SHLL    Rn              \0\x18\x18\xB2";

const char sh_mn_shlr_rn[28] = "SHLR    Rn              \0\x18\x18\xB2";

const char sh_mn_shll2_rn[28] = "SHLL2   Rn              \0\xA3\x28\x10";

const char sh_mn_shlr2_rn[28] = "SHLR2   Rn              \0\x10\x10\xC3";

const char sh_mn_shll8_rn[28] = "SHLL8   Rn              \0\x08\x08\xB4";

const char sh_mn_shlr8_rn[28] = "SHLR8   Rn              \0\x18\x28\xB4";

const char sh_mn_shll16_rn[28] = "SHLL16  Rn              \0\xC3\0\xB2";

const char sh_mn_shlr16_rn[28] = "SHLR16  Rn              \0\x08\x10\xC3";

const char sh_mn_jmp_atrn[28] = "JMP     @Rn             \0\x08\x18\xC3";

const char sh_mn_jsr_atrn[28] = "JSR     @Rn             \0\xC3\0\xB2";

const char sh_mn_stcl_sr_decrn[28] = "STC.L   SR,@-Rn         \0\x08\x08\xB4";

const char sh_mn_stcl_gbr_decrn[28] = "STC.L   GBR,@-Rn        \0\x08\x08\xB4";

const char sh_mn_stcl_vbr_decrn[28] = "STC.L   VBR,@-Rn        \0\xA3\x28\x10";

const char sh_mn_stsl_mach_decrn[28] = "STS.L   MACH,@-Rn       \0\xA3\x28\x18";

const char sh_mn_stsl_macl_decrn[28] = "STS.L   MACL,@-Rn       \0\x10\x10\xC3";

const char sh_mn_stsl_pr_decrn[28] = "STS.L   PR,@-Rn         \0\x18\x28\xB4";

const char sh_mn_movb_rm_r0rn[28] = "MOV.B   Rm,@(R0,Rn)     \0\xC4\x02\xAD";

const char sh_mn_movw_rm_r0rn[28] = "MOV.W   Rm,@(R0,Rn)     \0\xAD\x31\x60";

const char sh_mn_movl_rm_r0rn[28] = "MOV.L   Rm,@(R0,Rn)     \0\xD4\0\xFF";

const char sh_mn_mull_rm_rn[28] = "MUL.L   Rm,Rn           \0\x08\xB2\x4A";

const char sh_mn_movb_r0rm_rn[28] = "MOV.B   @(R0,Rm),Rn     \0\x0A\xB2\x4C";

const char sh_mn_movw_r0rm_rn[28] = "MOV.W   @(R0,Rm),Rn     \0\x06\x08\xB2";

const char sh_mn_movl_r0rm_rn[28] = "MOV.L   @(R0,Rm),Rn     \0\x15\x17\xA8";

const char sh_mn_macl_rminc_rninc[28] = "MAC.L   @Rm+,@Rn+       \0\x07\x07\xA8";

const char sh_mn_movb_rm_atrn[28] = "MOV.B   Rm,@Rn          \0\x08\x18\xB2";

const char sh_mn_movw_rm_atrn[28] = "MOV.W   Rm,@Rn          \0\x09\x0E\xAF";

const char sh_mn_movl_rm_atrn[28] = "MOV.L   Rm,@Rn          \0\x4D\x0D\x18";

const char sh_mn_movb_rm_decrn[28] = "MOV.B   Rm,@-Rn         \0\x4A\x10\x19";

const char sh_mn_movw_rm_decrn[28] = "MOV.W   Rm,@-Rn         \0\x49\x08\x08";

const char sh_mn_movl_rm_decrn[28] = "MOV.L   Rm,@-Rn         \0\x51\x0C\x18";

const char sh_mn_div0s_rm_rn[28] = "DIV0S   Rm,Rn           \0\x4E\x03\x03";

const char sh_mn_tst_rm_rn[28] = "TST     Rm,Rn           \0\x4C\x07\x08";

const char sh_mn_and_rm_rn[28] = "AND     Rm,Rn           \0\x51\x03\x03";

const char sh_mn_xor_rm_rn[28] = "XOR     Rm,Rn           \0\x51\x08\x08";

const char sh_mn_or_rm_rn[28] = "OR      Rm,Rn           \0\x0A\x16\xC3";

const char sh_mn_cmp_str_rm_rn[28] = "CMP/STR Rm,Rn           \0\xAD\x4C\x16";

const char sh_mn_xtrct_rm_rn[28] = "XTRCT   Rm,Rn           \0\x81\x40\x06";

const char sh_mn_muluw_rm_rn[28] = "MULU.W  Rm,Rn           \0\x45\x03\x03";

const char sh_mn_mulsw_rm_rn[28] = "MULS.W  Rm,Rn           \0\x40\xB2\x4C";

const char sh_mn_cmp_eq_rm_rn[28] = "CMP/EQ  Rm,Rn           \0\x1E\x02\xC8";

const char sh_mn_cmp_hs_rm_rn[28] = "CMP/HS  Rm,Rn           \0\x08\x0C\xB7";

const char sh_mn_cmp_ge_rm_rn[28] = "CMP/GE  Rm,Rn           \0\x18\xC3";

const char sh_mn_div1_rm_rn[28] = "DIV1    Rm,Rn           \0\x4C\x0C\x18";

const char sh_mn_dmulul_rm_rn[28] = "DMULU.L Rm,Rn           \0\x48\x10\x10";

const char sh_mn_cmp_hi_rm_rn[28] = "CMP/HI  Rm,Rn           \0\x47\x21\x32";

const char sh_mn_sub_rm_rn[28] = "SUB     Rm,Rn           \0\x4C\x08\x0C";

const char sh_mn_subc_rm_rn[28] = "SUBC    Rm,Rn           \0\xB2\x4E\x0D";

const char sh_mn_subv_rm_rn[28] = "SUBV    Rm,Rn           \0\xB2\x49\x06";

const char sh_mn_add_rm_rn[28] = "ADD     Rm,Rn           \0\xB2\x49\x09";

const char sh_mn_dmulsl_rm_rn[28] = "DMULS.L Rm,Rn           \0\xB7\x4E\x0A";

const char sh_mn_addc_rm_rn[28] = "ADDC    Rm,Rn           \0\xB2\x4C\x08";

const char sh_mn_addv_rm_rn[28] = "ADDV    Rm,Rn           \0\xA8\x4E\x03";

const char sh_mn_macw_rminc_rninc[28] = "MAC.W   @Rm+,@Rn+       \0\xAD\x51\x10";

const char sh_mn_movb_atrm_rn[28] = "MOV.B   @Rm,Rn          \0\xB7\x51\x05";

const char sh_mn_movw_atrm_rn[28] = "MOV.W   @Rm,Rn          \0\xAD\x53\x06";

const char sh_mn_movl_atrm_rn[28] = "MOV.L   @Rm,Rn          \0\x18\xAD\x4A";

const char sh_mn_mov_rm_rn[28] = "MOV     Rm,Rn           \0\x45\xB7\x4A";

const char sh_mn_movb_rminc_rn[28] = "MOV.B   @Rm+,Rn         \0\x18\xC8\x3C";

const char sh_mn_movw_rminc_rn[28] = "MOV.W   @Rm+,Rn         \0\xA5\x40\x03";

const char sh_mn_movl_rminc_rn[28] = "MOV.L   @Rm+,Rn         \0\x04\x0D\xBC";

const char sh_mn_not_rm_rn[28] = "NOT     Rm,Rn           \0\xAD\x39\x10";

const char sh_mn_swapb_rm_rn[28] = "SWAP.B  Rm,Rn           \0\xAD\x3B\x08";

const char sh_mn_swapw_rm_rn[28] = "SWAP.W  Rm,Rn           \0\x03\x30\xB7";

const char sh_mn_negc_rm_rn[28] = "NEGC    Rm,Rn           \0\x08\x18\xBC";

const char sh_mn_neg_rm_rn[28] = "NEG     Rm,Rn           \0\x3D\x10\x10";

const char sh_mn_extub_rm_rn[28] = "EXTU.B  Rm,Rn           \0\x3B\x02\x02";

const char sh_mn_extuw_rm_rn[28] = "EXTU.W  Rm,Rn           \0\xC6\x24\x01";

const char sh_mn_extsb_rm_rn[28] = "EXTS.B  Rm,Rn           \0\xA8\x4D\x14";

const char sh_mn_extsw_rm_rn[28] = "EXTS.W  Rm,Rn           \0\x18\x18\xA8";

const char sh_mn_movb_disprm_r0[28] = "MOV.B   @(disp,Rm),R0   \0\xA8\x45\x20";

const char sh_mn_movw_disprm_r0[28] = "MOV.W   @(disp,Rm),R0   \0\xB2\x43\x18";

const char sh_mn_movb_r0_disprn[28] = "MOV.B   R0,@(disp,Rn)   \0\xB7\x4F\x06";

const char sh_mn_movw_r0_disprn[28] = "MOV.W   R0,@(disp,Rn)   \0\xA8\x48\x48";

const char sh_mn_bt_label[28] = "BT      label           \0\x07\x10\xA8";

const char sh_mn_bf_label[28] = "BF      label           \0\x07\x0C\xB2";

const char sh_mn_bt_s_label[28] = "BT/S    label           \0\x06\x06\xD4";

const char sh_mn_bf_s_label[28] = "BF/S    label           \0\x06\x67\x07";

const char sh_mn_movb_r0_dispgbr[28] = "MOV.B   R0,@(disp,GBR)  \0\xBC\x4C\x16";

const char sh_mn_movw_r0_dispgbr[28] = "MOV.W   R0,@(disp,GBR)  \0\xBC\x4F\x16";

const char sh_mn_movl_r0_dispgbr[28] = "MOV.L   R0,@(disp,GBR)  \0\xBC\x4D\x24";

const char sh_mn_movb_dispgbr_r0[28] = "MOV.B   @(disp,GBR),R0  \0\xBC\x4A\x18";

const char sh_mn_movw_dispgbr_r0[28] = "MOV.W   @(disp,GBR),R0  \0\xBC\x4C\x30";

const char sh_mn_movl_dispgbr_r0[28] = "MOV.L   @(disp,GBR),R0  \0\xBC\x4A\x0A";

const char sh_mn_mova_disppc_r0[28] = "MOVA    @(disp,PC),R0   \0\xBC\x4D\x18";

const char sh_mn_cmp_eq_imm_r0[28] = "CMP/EQ  #imm,R0         \0\xBC\x4A\x0C";

const char sh_mn_trapa_imm[28] = "TRAPA   #imm            \0\x01\x43\xC7";

const char sh_mn_tst_imm_r0[28] = "TST     #imm,R0         \0\xBC\x35\x5E";

const char sh_mn_and_imm_r0[28] = "AND     #imm,R0         \0\xC7\x7F\xBC";

const char sh_mn_xor_imm_r0[28] = "XOR     #imm,R0         \0\x5E\x60\xC7";

const char sh_mn_or_imm_r0[28] = "OR      #imm,R0         \0\0\x01\xC4";

const char sh_mn_tstb_imm_r0gbr[28] = "TST.B   #imm,@(R0,GBR)  \0\x18\xC7\x60";

const char sh_mn_andb_imm_r0gbr[28] = "AND.B   #imm,@(R0,GBR)  \0\x4C\x0C\x18";

const char sh_mn_xorb_imm_r0gbr[28] = "XOR.B   #imm,@(R0,GBR)  \0\x7F\xBC\x54";

const char sh_mn_orb_imm_r0gbr[28] = "OR.B    #imm,@(R0,GBR)  \0\x18\xC7\x20";

const char sh_mn_movl_rm_disprn[28] = "MOV.L   Rm,@(disp,Rn)   \0\x53\x0C\x18";

const char sh_mn_movl_disprm_rn[28] = "MOV.L   @(disp,Rm),Rn   \0\x40\xBC\x56";

const char sh_mn_bra_label[28] = "BRA     label           \0\x24\xC7\x20";

const char sh_mn_bsr_label[28] = "BSR     label           \0\x56\x0C\x18";

const char sh_mn_movw_disppc_rn[28] = "MOV.W   @(disp,PC),Rn   \0\0\xBC\x4C";

const char sh_mn_movl_disppc_rn[28] = "MOV.L   @(disp,PC),Rn   \0\x18\xC7\x60";

const char sh_mn_add_imm_rn[28] = "ADD     #imm,Rn         \0\x4F\x0C\x18";

const char sh_mn_mov_imm_rn[28] = "MOV     #imm,Rn         \0\x40\xBC\x4F";

const char str_R0[4] = "R0\0\x20";

const char str_R1[4] = "R1\0\x18";

const char str_R2[4] = "R2\0\x4F";

const char str_R3[4] = "R3\0\x20";

const char str_R4[4] = "R4\0\x18";

const char str_R5[4] = "R5\0\x53";

const char str_R6[4] = "R6\0\x60";

const char str_R7[4] = "R7\0\x18";

const char str_R8[4] = "R8\0\x54";

const char str_R9[4] = "R9\0\x60";

const char str_R10[4] = "R10";

const char str_R11[4] = "R11";

const char str_R12[4] = "R12";

const char str_R13[4] = "R13";

const char str_R14[4] = "R14";

const char str_SP[4] = "SP\0\xC6";
