/*
 * ENTRY_DBG.C  Debug screens
 *
 * cpu_hang_forever is where a fatal exception ends (its register monitor is behind an endless loop),
 * dbg_memory_dump_rows and dbg_disasm_rows print memory rows, and disasm_sh_opcode turns an SH-2
 * instruction word into its mnemonic from the opcode tables.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "EFFA2_MAIN.h"
#include "win_2.h"
#include "continue.h"
#include "pow_pow.h"
#include "n_input.h"
#include "SYS_sub.h"
#include "cmb_win.h"
#include "eff87.h"
#include "eff88.h"
#include "eff89.h"
#include "eff90.h"
#include "eff91.h"
#include "eff92_code.h"
#include "Eff93.h"
#include "sys_test.h"
#include "sys_test_2.h"
#include "sys_test_2b.h"
#include "sys_test_2c.h"
#include "sys_test_3.h"
#include "sys_test_4.h"
#include "sys_test_5.h"
#include "eeprom.h"
#include "SE.h"
#include "se_2.h"
#include "se_3.h"
#include "end_sub.h"
#include "end_sub_2.h"
#include "color3rd.h"
#include "end_sub_8.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "sc_trans.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "entry_2.h"
#include "Entry.h"
#include "cps3.h"



extern void (*const vector_table[])();
/* 02000098 */
/* the date and time the program was built (__DATE__, __TIME__); nothing in the program reads them
   (provisional names) */
char build_date[] = "Feb 04 1997";
char build_time[] = "17:33:12";


void vector_restart();



/*
 * provisional name: the crash screen. The exception handlers come here after saving the registers
 * in exception_regs. The endless loop at the top is all that ever runs; behind it is the
 * monitor that printed the break label, the saved registers in three columns and the code at the
 * saved pc, waited for the input word and restarted the program.
 */
void cpu_hang_forever(void) {
    while (1) {
    }
    do {
    } while (*(volatile u16*)IO_REG == 0xFFFF);
    tilemap_print_string_attr(30, 22, 14, sh_str_break);
    tilemap_print_string_attr(37, 22, 14, (const s8*)current_task->timer);
    tilemap_print_string(1, 0, 0xFFFF, &monitor_msg_tbl[6]);
    tilemap_print_hex_block(7, 2, 14, exception_regs.r0, 8, 0);
    tilemap_print_hex_block(22, 2, 14, exception_regs.r1, 8, 0);
    tilemap_print_hex_block(37, 2, 14, exception_regs.r2, 8, 0);
    tilemap_print_hex_block(7, 3, 14, exception_regs.r3, 8, 0);
    tilemap_print_hex_block(22, 3, 14, exception_regs.r4, 8, 0);
    tilemap_print_hex_block(37, 3, 14, exception_regs.r5, 8, 0);
    tilemap_print_hex_block(7, 4, 14, exception_regs.r6, 8, 0);
    tilemap_print_hex_block(22, 4, 14, exception_regs.r7, 8, 0);
    tilemap_print_hex_block(37, 4, 14, exception_regs.r8, 8, 0);
    tilemap_print_hex_block(7, 5, 14, exception_regs.r9, 8, 0);
    tilemap_print_hex_block(22, 5, 14, exception_regs.r10, 8, 0);
    tilemap_print_hex_block(37, 5, 14, exception_regs.r11, 8, 0);
    tilemap_print_hex_block(7, 6, 14, exception_regs.r12, 8, 0);
    tilemap_print_hex_block(22, 6, 14, exception_regs.r13, 8, 0);
    tilemap_print_hex_block(37, 6, 14, exception_regs.r14, 8, 0);
    tilemap_print_hex_block(7, 7, 14, exception_regs.sp, 8, 0);
    tilemap_print_hex_block(22, 7, 14, exception_regs.pc, 8, 0);
    tilemap_print_hex_block(7, 8, 14, exception_regs.pr, 8, 0);
    tilemap_print_hex_block(22, 8, 14, exception_regs.gbr, 8, 0);
    dbg_disasm_rows((u16*)(exception_regs.pc & ~1));
    while (*(volatile u16*)IO_REG != 0xCFFF) {
    }
    vector_restart(vector_table);
}



/* provisional name */
void dbg_memory_dump_rows(u16* tbl) {
    long row;
    long col;
    tilemap_print_string(1, 0, 0xFFFF, dbg_dump_title);
    for (row = 0; row < 8; row++) {
        tilemap_print_hex_block(1, row + 11, 14, (s32)tbl, 8, 0);
        for (col = 0; col < 8; col++) {
            tilemap_print_hex_block(col * 5 + 10, row + 11, 14, *tbl, 4, 0);
            tbl++;
        }
    }
}



/* provisional name */
void dbg_disasm_rows(u16* tbl) {
    u16 y;
    long i;
    s8 buf[128];
    tilemap_print_string(1, 0, 0xFFFF, dbg_disasm_title);
    for (i = 0; i < 10; i++) {
        tilemap_print_hex_block(1, y = i + 11, 14, (s32)tbl, 8, 0);
        tilemap_print_hex_block(10, y, 14, *tbl, 4, 0);
        disasm_sh_opcode(*tbl, buf);
        tilemap_print_string_attr(15, y, 14, buf);
        tbl++;
    }
}



/* provisional name */
void disasm_sh_opcode(u16 code, char* str) {
    char buf[128];
    const MoveName* p;
    char* mark;
    char* tail;
    char* mark2;
    *str = 0;
    if ((code & 0xFF00) == 0) {
        for (p = sh_op_none_tbl; p->name != 0; p++) {
            if (code == p->code) {
                strcpy(str, p->name);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0x4000) {
        for (p = sh_op_ldm_tbl; p->name != 0; p++) {
            if ((code & 0xF0FF) == p->code) {
                strcpy(buf, p->name);
                mark = strstr(buf, sh_str_rm);
                *mark = 0;
                strcpy(str, buf);
                strcat(str, reg_name_tbl[(code & 0xF00) >> 8]);
                strcat(str, mark + 2);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0 || (code & 0xF000) == 0x4000) {
        for (p = sh_op_n_tbl; p->name != 0; p++) {
            if ((code & 0xF0FF) == p->code) {
                strcpy(buf, p->name);
                mark = strstr(buf, sh_str_rn);
                *mark = 0;
                strcpy(str, buf);
                strcat(str, reg_name_tbl[(code & 0xF00) >> 8]);
                strcat(str, mark + 2);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0 || (code & 0xF000) == 0x2000 || (code & 0xF000) == 0x3000 ||
        (code & 0xF000) == 0x4000 || (code & 0xF000) == 0x6000) {
        for (p = sh_op_nm_tbl; p->name != 0; p++) {
            if ((code & 0xF00F) == p->code) {
                strcpy(buf, p->name);
                mark = strstr(buf, sh_str_rm);
                *mark = 0;
                strcpy(str, buf);
                strcat(str, reg_name_tbl[(code & 0xF0) >> 4]);
                tail = mark + 2;
                mark2 = strstr(tail, sh_str_rn);
                *mark2 = 0;
                strcat(str, tail);
                strcat(str, reg_name_tbl[(code & 0xF00) >> 8]);
                strcat(str, mark2 + 2);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0x8000) {
        for (p = sh_op_disp_m_tbl; p->name != 0; p++) {
            if ((code & 0xFF00) == p->code) {
                strcpy(str, p->name);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0x8000) {
        for (p = sh_op_disp_n_tbl; p->name != 0; p++) {
            if ((code & 0xFF00) == p->code) {
                strcpy(str, p->name);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0x8000 || (code & 0xF000) == 0xC000) {
        for (p = sh_op_d8_tbl; p->name != 0; p++) {
            if ((code & 0xFF00) == p->code) {
                strcpy(str, p->name);
                return;
            }
        }
    }
    if ((code & 0xF000) == 0x8000 || (code & 0xF000) == 0xC000) {
        for (p = sh_op_imm_tbl; p->name != 0; p++) {
            if ((code & 0xFF00) == p->code) {
                strcpy(str, p->name);
                return;
            }
        }
    }
    for (p = sh_op_disp4_tbl; p->name != 0; p++) {
        if ((code & 0xF000) == p->code) {
            strcpy(str, p->name);
            return;
        }
    }
    for (p = sh_op_d12_tbl; p->name != 0; p++) {
        if ((code & 0xF000) == p->code) {
            strcpy(str, p->name);
            return;
        }
    }
    for (p = sh_op_pcrel_tbl; p->name != 0; p++) {
        if ((code & 0xF000) == p->code) {
            strcpy(str, p->name);
            return;
        }
    }
    for (p = sh_op_imm_n_tbl; p->name != 0; p++) {
        if ((code & 0xF000) == p->code) {
            strcpy(str, p->name);
            return;
        }
    }
    if (*str == 0) {
        strcpy(str, sh_str_undef);
    }
}

