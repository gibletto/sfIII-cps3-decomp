; CPS3.INC  the board's memory and registers for the assembler modules (the same names as cps3.h)

CACHE_THRU      .EQU    H'20000000    ; cache-through mirror of the address map
WORK_RAM        .EQU    H'02000000
SRAM            .EQU    H'23000000    ; byte-wide SRAM on even addresses (sram_read_byte)
SPRITE_RAM      .EQU    H'24000000
COLOR_RAM       .EQU    H'24080000
VIDEO_REG       .EQU    H'240C0000    ; video registers; +0x86 the CHARACTER RAM bank, +0x88 the SIMM bank
SOUND_REG       .EQU    H'240E0000    ; sound chip: voice registers (SNDVOICEREG), +0x200 key on
CHARACTER_RAM   .EQU    H'24100000
SIMM_WINDOW     .EQU    H'24200000    ; the graphics SIMMs, one bank at a time (VIDEO_REG + 0x88)
IO_REG          .EQU    H'25000000    ; player inputs and coin
EXT_SW          .EQU    H'25000A00    ; extra switches (exsw)
EEP_ROM         .EQU    H'25001000
SS_RAM_CACHED   .EQU    H'05040000    ; SS RAM through the cache
SS_RAM          .EQU    H'25040000    ; text and tile layer (SS) RAM
SS_REG          .EQU    H'25050000    ; SS layer registers
IRQ12_ACK       .EQU    H'25100000    ; acknowledge: vblank (interrupt level 12)
IRQ10_ACK       .EQU    H'25110000    ; acknowledge: interrupt level 10
IRQ14_ACK       .EQU    H'25120000    ; acknowledge: interrupt level 14
CD_REG          .EQU    H'25140000    ; CD-ROM (SCSI) controller: +0 register select, +2 data
SH2_TIER        .EQU    H'FFFFFE10    ; free-running timer
SH2_FTCSR       .EQU    H'FFFFFE11
SH2_FRCH        .EQU    H'FFFFFE12
SH2_FRCL        .EQU    H'FFFFFE13
SH2_OCRH        .EQU    H'FFFFFE14
SH2_OCRL        .EQU    H'FFFFFE15
SH2_VCRD        .EQU    H'FFFFFE66    ; free-running timer vector number
SH2_DRCR0       .EQU    H'FFFFFE71    ; DMA request select, channel 0
SH2_CCR         .EQU    H'FFFFFE92    ; cache control
SH2_SAR0        .EQU    H'FFFFFF80    ; DMA channel 0: source, destination, count, control
SH2_DAR0        .EQU    H'FFFFFF84
SH2_TCR0        .EQU    H'FFFFFF88
SH2_CHCR0       .EQU    H'FFFFFF8C
SH2_CHCR1       .EQU    H'FFFFFF9C
SH2_DMAOR       .EQU    H'FFFFFFB0    ; DMA operation
SH2_BCR1        .EQU    H'FFFFFFE0    ; bus control
SH2_WCR         .EQU    H'FFFFFFE8    ; wait control
