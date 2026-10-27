/*
 * SYS_CONFIG.C  Settings storage, configuration menu and render list setup
 *
 * EEPROM settings: eeprom_config_load / save / reset / default / verify read and write the operator
 * settings record, and eeprom_config_apply puts a loaded record into effect.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "CMD_MAIN.h"
#include "cmd_main_2.h"
#include "meta_col_mem.h"
#include "meta_col_strcpy.h"
#include "meta_col_lib.h"
#include "meta_col_bcd.h"
#include "eeprom.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "cram_bank.h"
#include "game_config_main.h"
#include "sys_config_2.h"
#include "sys_config_3.h"
#include "sys_config.h"
#include "cps3.h"
/* eeprom_w is the start of the 128-byte EEPROM image; the variables up to eeprom_backup_cfg are its parts */
u8 eeprom_w[6];  /* 0206ABE0 */
u8 eeprom_saved_flip;  /* 0206ABE6 */
u8 eeprom_saved_flip_tail[25];  /* after eeprom_saved_flip; nothing refers to it by name or address */
u8 eeprom_game_cfg[16];  /* 0206AC00 */
u8 eeprom_backup_cfg[80];  /* 0206AC10 */
s16 eeprom_retry;  /* 0206AC60 */
SETTINGS Game_setting;  /* 0206AC62 */


/* provisional name */
void eeprom_config_load(void) {
    register s8 side;
    register s16 i;
    u32 tbl;
    u8* q;
    u8* p;
    eeprom_config_verify();
    tbl = sys_cfg_default_tbl[Cabinet_Type];
    if (Area_Type) {
        side = Area_Type;
    } else if (Area_Alt_Flag) {
        side = 6;
    } else {
        side = Area_Type;
    }
    p = *(u8**)(tbl + side * 4);
    if ((s8)*eeprom_w != (s8)*p) {
        eeprom_config_reset();
        return;
    }
    q = eeprom_game_cfg + 8;
    p = game_cfg_default_tbl[side];
    p = p + 8;
    for (i = 0; i < 8; i++) {
        if (*q != *p) {
            eeprom_config_reset();
            return;
        }
        q++;
        p++;
    }
    eeprom_config_apply((u32)eeprom_w);
    /* the bookkeeping counters follow the two config copies in the EEPROM image */
    book_coin_count = *(u32*)&eeprom_w[0x60];
    book_service_count = *(u32*)&eeprom_w[0x64];
    book_free_count = *(u32*)&eeprom_w[0x68];
    book_card_count = *(u32*)&eeprom_w[0x6C];
}



/* provisional name */
void eeprom_config_reset(void) {
    register s8 ix;
    register s16 k;
    register s16 j;
    u32 table;
    u8* rec;
    u8* ref;
    u8* key;
    u8* name;
    for (eeprom_retry = 10; eeprom_retry > 0; eeprom_retry--) {
        eeprom_config_default();
        if (eeprom_write(64, (u16*)(EEP_ROM + 0x80), (u16*)eeprom_w)) {
            eeprom_error_halt();
        }
        if (eeprom_read(64, (u16*)(EEP_ROM + 0x100), (u16*)eeprom_w)) {
            eeprom_error_halt();
        }
        rec = eeprom_w;
        table = sys_cfg_default_tbl[Cabinet_Type];
        if (Area_Type) {
            ix = Area_Type;
        } else if (Area_Alt_Flag) {
            ix = 6;
        } else {
            ix = Area_Type;
        }
        key = *(u8**)(table + ix * 4);
        ref = eeprom_game_cfg;
        name = game_cfg_default_tbl[ix];
        if (config_bytes_equal(rec, key, 32)) {
            if (config_bytes_equal(ref, name, 16)) {
                eeprom_config_apply(eeprom_w);
                return;
            }
        }
    }
    eeprom_error_halt();
}



/* provisional name */
s8 config_bytes_equal(u8* a, u8* b, s32 n) {
    register s32 i;
    for (i = 0; i < n; i++) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
    }
    return 1;
}



/* provisional name */
void eeprom_config_apply(rec)
u32 rec;
{
    s32 i;
    u8* src;
    s8* dst;
    Coin_Mode = *(s8*)(rec + 1);
    Continue_Flag = *(s8*)(rec + 2);
    Chute_Mode = *(s8*)(rec + 3);
    Sound_Mode = *(s8*)(rec + 4);
    Demo_Sound = *(s8*)(rec + 5);
    Monitor_Flip = *(s8*)(rec + 6);
    Language = *(s8*)(rec + 9);
    Free_Play_Enable = *(s8*)(rec + 8);
    if (Sound_Mode == 0) {
        sound_init((u8*)snd_seq_rom_data, snd_sample_rom_tbl, snd_bank_rom_tbl, 1, 0, 1);
    } else {
        sound_init((u8*)snd_seq_rom_data, snd_sample_rom_tbl, snd_bank_rom_tbl, 1, 0, 0);
    }
    Card_Dispenser = *(s8*)(rec + 10);
    Win_Point_Com = *(s8*)(rec + 11);
    Win_Point_Human = *(s8*)(rec + 12);
    Voice_Type = *(s8*)(rec + 13);
    if (Coin_Mode > 18) {
        Coin_Mode = 8;
    }
    if (Free_Play_Enable != 0 && Coin_Mode == 18) {
        Free_Play = 1;
    } else {
        Free_Play = 0;
    }
    if (Win_Point_Com < Win_Point_Com_Min || Win_Point_Com > Win_Point_Com_Max) {
        Win_Point_Com = 2;
    }
    if (Win_Point_Human < Win_Point_Human_Min || Win_Point_Human > Win_Point_Human_Max) {
        Win_Point_Human = 2;
    }
    coin_chute1_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
    coin_chute1_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
    coin_chute2_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
    coin_chute2_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
    coin_chute3_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
    coin_chute3_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
    coin_chute4_w.per_credit = coin_rate_tbl[Coin_Mode][COIN_RATE_COINS];
    coin_chute4_w.credits = coin_rate_tbl[Coin_Mode][COIN_RATE_CREDITS];
    if (Coin_Mode != 17) {
        Two_Coin_Start = 0;
    } else {
        Two_Coin_Start = 1;
        Continue_Flag = 1;
    }
    src = eeprom_game_cfg;
    dst = (s8 *)&Game_setting;
    for (i = 0; i < 16; i++) {
        *dst = *src;
        dst++;
        src++;
    }
}



/* provisional name */
void eeprom_config_save(void) {
    register s16 k;
    register s16 j;
    u32 p;
    s8* src;
    p = (u32)eeprom_w;
    for (k = 0; k < 2; k++) {
        *(u8*)(p + 1) = Coin_Mode;
        *(u8*)(p + 2) = Continue_Flag;
        *(u8*)(p + 3) = Chute_Mode;
        *(u8*)(p + 4) = Sound_Mode;
        *(u8*)(p + 5) = Demo_Sound;
        *(u8*)(p + 6) = Monitor_Flip;
        *(u8*)(p + 9) = Language;
        *(u8*)(p + 8) = Free_Play_Enable;
        *(u8*)(p + 10) = ((s8)Card_Dispenser);
        *(u8*)(p + 11) = Win_Point_Com;
        *(u8*)(p + 12) = Win_Point_Human;
        *(u8*)(p + 13) = Voice_Type;
        if (Sound_Mode == 0) {
            sound_init((u8*)snd_seq_rom_data, snd_sample_rom_tbl, snd_bank_rom_tbl, 1, 0, 1);
        } else {
            sound_init((u8*)snd_seq_rom_data, snd_sample_rom_tbl, snd_bank_rom_tbl, 1, 0, 0);
        }
        if (Free_Play_Enable == 0) {
            *(u8*)(p + 8) = 0;
        }
        p += 32;
        src = (s8 *)&Game_setting;
        for (j = 0; j < 16; j++) {
            *(u8*)p = *src;
            p++;
            src++;
        }
    }
    if (eeprom_write(48, (u16*)(EEP_ROM + 0x80), (u16*)eeprom_w)) {
        eeprom_error_halt();
    }
    eeprom_config_apply(eeprom_w);
}



/* provisional name */
void eeprom_config_default(void) {
    register s8 ix;
    register s16 k;
    register s16 j;
    u32 table;
    u8* dst;
    u8* src;
    dst = eeprom_w;
    for (k = 0; k < 2; k++) {
        table = sys_cfg_default_tbl[Cabinet_Type];
        if (Area_Type) {
            ix = Area_Type;
        } else if (Area_Alt_Flag) {
            ix = 6;
        } else {
            ix = Area_Type;
        }
        src = *(u8**)(table + ix * 4);
        for (j = 0; j < 32; j++) {
            *dst = *src;
            dst++;
            src++;
        }
        src = game_cfg_default_tbl[ix];
        for (j = 0; j < 16; j++) {
            *dst = *src;
            dst++;
            src++;
        }
    }
    for (j = 0; j < 32; j++) {
        *dst = 0;
        dst++;
    }
}



/* provisional name */
void eeprom_config_verify(void) {
    register s16 i;
    u8* a;
    u8* b;
    eeprom_retry = 10;
    while (eeprom_retry > 0) {
        if (eeprom_read(64, (u16*)(EEP_ROM + 0x100), (u16*)eeprom_w)) {
            eeprom_error_halt();
        }
        a = eeprom_w;
        b = eeprom_backup_cfg;
        for (i = 0; i < 48; i++) {
            if (*a != *b) {
                break;
            }
            a++;
            b++;
        }
        if (i == 48) {
            return;
        }
        eeprom_retry--;
    }
    eeprom_config_reset();
}



