/*
 * RESET.C  Power-on start
 *
 * reset_entry is the program start: it clears the uninitialised data area and copies the initialised
 * data into RAM (INITSCT), sets up the free-running timer and its interrupt, takes the free play and
 * area settings, sets the sound banks, starts the boot task, resets the coin lock, game mode, scroll,
 * family work, coins and render lists, and enters the task kernel through main_thunk.
 */

#include "types.h"
#include "structs.h"
#include "work.h"
#include "Entry.h"
#include "textsound_2.h"
#include "sys_test.h"
#include "Com_Pl.h"
#include "fifo.h"
#include "romdata.h"
#include "sys_config_3.h"
#include "cps3.h"

extern int *B_BGN, *B_END, *D_BGN, *D_END, *D_ROM;
extern const s8 boot_setting_defaults[4];
extern const s32 region_area_tbl[8];
extern u8 bios_area_code;
extern void main_thunk(void);

#pragma inline(INITSCT)
static void INITSCT(void) {
    int *p, *q;

    for (p = B_BGN; p < B_END; p++) {
        *p = 0;
    }
    for (p = D_BGN, q = D_ROM; p < D_END; p++, q++) {
        *p = *q;
    }
}

void reset_entry(void) {
    u16 w;
    s16 area;

    INITSCT();

    w = *(u16*)SH2_VCRD;
    w &= 0x7F00;
    w |= 0x51;
    *(u16*)SH2_VCRD = w;
    w = *(u16*)SH2_IPRB;
    w &= 0xF000;
    w |= 0x0F00;
    *(u16*)SH2_IPRB = w;
    w = *(u8*)SH2_TOCR;
    w &= 0xFC;
    *(u8*)SH2_TOCR = w;
    *(u8*)SH2_OCRH = 0x33;
    *(u8*)SH2_OCRL = 0x33;
    *(u8*)SH2_FTCSR = 1;
    *(u8*)SH2_TIER = 9;
    *(u16*)SPRITE_DMA_REG = 9;

    Free_Play_Enable = boot_setting_defaults[0];
    Area_Type = boot_setting_defaults[1];
    Area_Alt_Flag = boot_setting_defaults[2];
    area = bios_area_code;
    Area_Type = region_area_tbl[area & 7];

    sound_sample_bank_set(0);
    sound_init((u8*)&snd_seq_rom_data, (SNDSAMPLE*)&snd_sample_rom_tbl, (u8**)&snd_bank_rom_tbl, 1, 0, 1);
    sound_sample_bank_set(64);
    sound_init((u8*)&snd_seq_rom_data, (SNDSAMPLE*)&snd_sample_rom_tbl, (u8**)&snd_bank_rom_tbl, 1, 0, 1);
    init_task_stacks();
    create_task(boot_task, 0, &task_tbl[5], 0, 0);
    coin_lock_set(-1);
    set_screen_mode(3);
    clear_scroll_layer_state_and_mask();
    Scrn_Pos_Init();
    Family_Init();
    Zoomf_Init();
    coin_work_init();
    init_render_lists();
    Cd_Error_Flag = 1;
    Cabinet_Type = 0;
    system_ctrl_flag = 0x80;
    main_thunk();
}
