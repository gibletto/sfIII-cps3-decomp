/*
 * VECTORS.C  the SH-2 exception vector table
 *
 * Linked first, at 06000000 (section VECT); the CPU's VBR points here. Each entry is the address the CPU
 * jumps to for one event: resets (0-3, entry 1 the initial stack pointer), CPU errors (4-12), TRAPA
 * (32-63) and interrupts (64-71 the CPS3's interrupt levels, 64 + level / 2; the timer's are set in the SH-2's vector registers).
 * The error handlers (intr.src) store their number in exception_code, save the registers in
 * exception_regs and stop. Entries the game does not use hold 00000400, an address in the BIOS ROM.
 * 06000200-060003FF, up to the program, is no section's (holes.tsv).
 */

#include "types.h"

#define NOT_USED  ((void (*)())0x00000400)   /* the BIOS ROM */

extern void reset_entry(), exc_illegal_instr(), exc_illegal_slot(), exc_cpu_addr_err(), exc_dma_addr_err(), exc_trapa(), dma_end_intr(), vblank_frame_dispatch(), irq_spare_ack_intr(), frt_compare_intr(), frt_overflow_intr();
extern u8 boot_stack[4100];

#pragma section VECT

void (*const vector_table[128])() = {
    reset_entry,  /* 0: power-on reset: start address */
    (void (*)())&boot_stack[4100],  /* 1: power-on reset: stack pointer */
    NOT_USED,  /* 2: manual reset: start address */
    NOT_USED,  /* 3: manual reset: stack pointer */
    exc_illegal_instr,  /* 4: general illegal instruction */
    NOT_USED,  /* 5 */
    exc_illegal_slot,  /* 6: illegal slot instruction (in a delay slot) */
    NOT_USED,  /* 7 */
    NOT_USED,  /* 8 */
    exc_cpu_addr_err,  /* 9: CPU address error */
    exc_dma_addr_err,  /* 10: DMA address error */
    NOT_USED,  /* 11: NMI */
    NOT_USED,  /* 12: user break */
    NOT_USED,  /* 13 */
    NOT_USED,  /* 14 */
    NOT_USED,  /* 15 */
    NOT_USED,  /* 16 */
    NOT_USED,  /* 17 */
    NOT_USED,  /* 18 */
    NOT_USED,  /* 19 */
    NOT_USED,  /* 20 */
    NOT_USED,  /* 21 */
    NOT_USED,  /* 22 */
    NOT_USED,  /* 23 */
    NOT_USED,  /* 24 */
    NOT_USED,  /* 25 */
    NOT_USED,  /* 26 */
    NOT_USED,  /* 27 */
    NOT_USED,  /* 28 */
    NOT_USED,  /* 29 */
    NOT_USED,  /* 30 */
    NOT_USED,  /* 31 */
    exc_trapa,  /* 32: TRAPA #32 */
    NOT_USED,  /* 33: TRAPA #33 */
    NOT_USED,  /* 34: TRAPA #34 */
    NOT_USED,  /* 35: TRAPA #35 */
    NOT_USED,  /* 36: TRAPA #36 */
    NOT_USED,  /* 37: TRAPA #37 */
    NOT_USED,  /* 38: TRAPA #38 */
    NOT_USED,  /* 39: TRAPA #39 */
    NOT_USED,  /* 40: TRAPA #40 */
    NOT_USED,  /* 41: TRAPA #41 */
    NOT_USED,  /* 42: TRAPA #42 */
    NOT_USED,  /* 43: TRAPA #43 */
    NOT_USED,  /* 44: TRAPA #44 */
    NOT_USED,  /* 45: TRAPA #45 */
    NOT_USED,  /* 46: TRAPA #46 */
    NOT_USED,  /* 47: TRAPA #47 */
    NOT_USED,  /* 48: TRAPA #48 */
    NOT_USED,  /* 49: TRAPA #49 */
    NOT_USED,  /* 50: TRAPA #50 */
    NOT_USED,  /* 51: TRAPA #51 */
    NOT_USED,  /* 52: TRAPA #52 */
    NOT_USED,  /* 53: TRAPA #53 */
    NOT_USED,  /* 54: TRAPA #54 */
    NOT_USED,  /* 55: TRAPA #55 */
    NOT_USED,  /* 56: TRAPA #56 */
    NOT_USED,  /* 57: TRAPA #57 */
    NOT_USED,  /* 58: TRAPA #58 */
    NOT_USED,  /* 59: TRAPA #59 */
    NOT_USED,  /* 60: TRAPA #60 */
    NOT_USED,  /* 61: TRAPA #61 */
    NOT_USED,  /* 62: TRAPA #62 */
    NOT_USED,  /* 63: TRAPA #63 */
    NOT_USED,  /* 64 */
    NOT_USED,  /* 65 */
    NOT_USED,  /* 66 */
    NOT_USED,  /* 67 */
    NOT_USED,  /* 68 */
    dma_end_intr,  /* 69: interrupt level 10-11 */
    vblank_frame_dispatch,  /* 70: interrupt level 12-13: vblank, once a frame */
    irq_spare_ack_intr,  /* 71: interrupt level 14-15 */
    NOT_USED,  /* 72 */
    NOT_USED,  /* 73 */
    NOT_USED,  /* 74 */
    NOT_USED,  /* 75 */
    NOT_USED,  /* 76 */
    NOT_USED,  /* 77 */
    NOT_USED,  /* 78 */
    NOT_USED,  /* 79 */
    NOT_USED,  /* 80 */
    frt_compare_intr,  /* 81: on-chip: free-running timer compare match */
    frt_overflow_intr,  /* 82: on-chip: free-running timer overflow */
    NOT_USED,  /* 83 */
    NOT_USED,  /* 84 */
    NOT_USED,  /* 85 */
    NOT_USED,  /* 86 */
    NOT_USED,  /* 87 */
    NOT_USED,  /* 88 */
    NOT_USED,  /* 89 */
    NOT_USED,  /* 90 */
    NOT_USED,  /* 91 */
    NOT_USED,  /* 92 */
    NOT_USED,  /* 93 */
    NOT_USED,  /* 94 */
    NOT_USED,  /* 95 */
    NOT_USED,  /* 96 */
    NOT_USED,  /* 97 */
    NOT_USED,  /* 98 */
    NOT_USED,  /* 99 */
    NOT_USED,  /* 100 */
    NOT_USED,  /* 101 */
    NOT_USED,  /* 102 */
    NOT_USED,  /* 103 */
    NOT_USED,  /* 104 */
    NOT_USED,  /* 105 */
    NOT_USED,  /* 106 */
    NOT_USED,  /* 107 */
    NOT_USED,  /* 108 */
    NOT_USED,  /* 109 */
    NOT_USED,  /* 110 */
    NOT_USED,  /* 111 */
    NOT_USED,  /* 112 */
    NOT_USED,  /* 113 */
    NOT_USED,  /* 114 */
    NOT_USED,  /* 115 */
    NOT_USED,  /* 116 */
    NOT_USED,  /* 117 */
    NOT_USED,  /* 118 */
    NOT_USED,  /* 119 */
    NOT_USED,  /* 120 */
    NOT_USED,  /* 121 */
    NOT_USED,  /* 122 */
    NOT_USED,  /* 123 */
    NOT_USED,  /* 124 */
    NOT_USED,  /* 125 */
    NOT_USED,  /* 126 */
    NOT_USED,  /* 127 */
};
