/*
 * CPS3.H  the board's memory and registers, as the program addresses them
 *
 * The program reaches the video, sound and I/O hardware through the SH-2's cache-through mirror (the
 * address with 0x20000000 set), so the bases below carry it. The RAM names are the ones the test menu
 * prints (WORK RAM, SPRITE RAM, COLOR RAM, CHARACTER RAM, SS RAM, EEP ROM). The SH-2's own registers
 * (FFFFFE00 on) have the names of the SH7604 manual. cps3.inc has the same names for the assembler.
 */

#ifndef CPS3_H
#define CPS3_H

#define CACHE_THRU      0x20000000      /* cache-through mirror of the address map */

#define WORK_RAM        0x02000000
#define SRAM            0x23000000      /* byte-wide SRAM on even addresses (sram_read_byte) */
#define SPRITE_RAM      0x24000000
#define COLOR_RAM       0x24080000
#define VIDEO_REG       0x240C0000      /* video registers; +0x86 the CHARACTER RAM bank, +0x88 the SIMM bank */
#define SOUND_REG       0x240E0000      /* sound chip: voice registers (SNDVOICEREG), +0x200 key on */
#define CHARACTER_RAM   0x24100000
#define SIMM_WINDOW     0x24200000      /* the graphics SIMMs, one bank at a time (VIDEO_REG + 0x88) */
#define IO_REG          0x25000000      /* player inputs and coin */
#define EXT_SW          0x25000A00      /* extra switches (exsw) */
#define EEP_ROM         0x25001000
#define SS_RAM_CACHED   0x05040000      /* SS RAM through the cache */
#define SS_RAM          0x25040000      /* text and tile layer (SS) RAM */
#define SS_REG          0x25050000      /* SS layer registers */
#define IRQ12_ACK       0x25100000      /* acknowledge: vblank (interrupt level 12) */
#define IRQ10_ACK       0x25110000      /* acknowledge: interrupt level 10 */
#define IRQ14_ACK       0x25120000      /* acknowledge: interrupt level 14 */
#define CD_REG          0x25140000      /* CD-ROM (SCSI) controller: +0 register select, +2 data */

/* SH-2 on-chip registers */
#define SH2_TIER        0xFFFFFE10      /* free-running timer */
#define SH2_FTCSR       0xFFFFFE11
#define SH2_FRCH        0xFFFFFE12
#define SH2_FRCL        0xFFFFFE13
#define SH2_OCRH        0xFFFFFE14
#define SH2_OCRL        0xFFFFFE15
#define SH2_VCRD        0xFFFFFE66      /* free-running timer vector number */
#define SH2_DRCR0       0xFFFFFE71      /* DMA request select, channel 0 */
#define SH2_CCR         0xFFFFFE92      /* cache control */
#define SH2_SAR0        0xFFFFFF80      /* DMA channel 0: source, destination, count, control */
#define SH2_DAR0        0xFFFFFF84
#define SH2_TCR0        0xFFFFFF88
#define SH2_CHCR0       0xFFFFFF8C
#define SH2_CHCR1       0xFFFFFF9C
#define SH2_DMAOR       0xFFFFFFB0      /* DMA operation */
#define SH2_BCR1        0xFFFFFFE0      /* bus control */
#define SH2_WCR         0xFFFFFFE8      /* wait control */

#endif
