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
u8 eeprom_w[128];  /* 0206ABE0 */
s16 eeprom_retry;  /* 0206AC60 */
SETTINGS Game_setting;  /* 0206AC62 */


/* provisional name */
void eeprom_config_load(void) {
    register s8 side;
    register s16 i;
    const u8** tbl;
    u8* q;
    const u8* p;
    eeprom_config_verify();
    tbl = sys_cfg_default_tbl[Cabinet_Type];
    if (Area_Type) {
        side = Area_Type;
    } else if (Area_Alt_Flag) {
        side = 6;
    } else {
        side = Area_Type;
    }
    p = tbl[side];
    if ((s8)eeprom_w[EEP_VERSION] != (s8)*p) {
        eeprom_config_reset();
        return;
    }
    q = &eeprom_w[EEP_GAME + 8];
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
    book_coin_count = *(u32*)&eeprom_w[EEP_BOOK_COIN];
    book_service_count = *(u32*)&eeprom_w[EEP_BOOK_SERVICE];
    book_free_count = *(u32*)&eeprom_w[EEP_BOOK_FREE];
    book_card_count = *(u32*)&eeprom_w[EEP_BOOK_CARD];
}



/* provisional name */
void eeprom_config_reset(void) {
    register s8 ix;
    register s16 k;
    register s16 j;
    const u8** table;
    u8* rec;
    u8* ref;
    u8* key;
    const u8* name;
    for (eeprom_retry = 10; eeprom_retry > 0; eeprom_retry--) {
        eeprom_config_default();
        if (eeprom_write(64, (u16*)EEP_ROM_WRITE, (u16*)eeprom_w)) {
            eeprom_error_halt();
        }
        if (eeprom_read(64, (u16*)EEP_ROM_READ, (u16*)eeprom_w)) {
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
        key = table[ix];
        ref = &eeprom_w[EEP_GAME];
        name = game_cfg_default_tbl[ix];
        if (config_bytes_equal(rec, key, EEP_SYSTEM_SIZE)) {
            if (config_bytes_equal(ref, name, EEP_GAME_SIZE)) {
                eeprom_config_apply((u32)eeprom_w);
                return;
            }
        }
    }
    eeprom_error_halt();
}



/* provisional name */
s8 config_bytes_equal(const u8* a, const u8* b, s32 n) {
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
    Coin_Mode = *(s8*)(rec + EEP_COIN_MODE);
    Continue_Flag = *(s8*)(rec + EEP_CONTINUE);
    Chute_Mode = *(s8*)(rec + EEP_CHUTE_MODE);
    Sound_Mode = *(s8*)(rec + EEP_SOUND_MODE);
    Demo_Sound = *(s8*)(rec + EEP_DEMO_SOUND);
    Monitor_Flip = *(s8*)(rec + EEP_MONITOR_FLIP);
    Language = *(s8*)(rec + EEP_LANGUAGE);
    Free_Play_Enable = *(s8*)(rec + EEP_FREE_PLAY);
    if (Sound_Mode == 0) {
        sound_init((u8*)snd_seq_rom_data, (SNDSAMPLE*)snd_sample_rom_tbl, (u8**)snd_bank_rom_tbl, 1, 0, 1);
    } else {
        sound_init((u8*)snd_seq_rom_data, (SNDSAMPLE*)snd_sample_rom_tbl, (u8**)snd_bank_rom_tbl, 1, 0, 0);
    }
    Card_Dispenser = *(s8*)(rec + EEP_CARD_DISPENSER);
    Win_Point_Com = *(s8*)(rec + EEP_WIN_POINT_COM);
    Win_Point_Human = *(s8*)(rec + EEP_WIN_POINT_HUMAN);
    Voice_Type = *(s8*)(rec + EEP_VOICE_TYPE);
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
    src = &eeprom_w[EEP_GAME];
    dst = (s8 *)&Game_setting;
    for (i = 0; i < EEP_GAME_SIZE; i++) {
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
        *(u8*)(p + EEP_COIN_MODE) = Coin_Mode;
        *(u8*)(p + EEP_CONTINUE) = Continue_Flag;
        *(u8*)(p + EEP_CHUTE_MODE) = Chute_Mode;
        *(u8*)(p + EEP_SOUND_MODE) = Sound_Mode;
        *(u8*)(p + EEP_DEMO_SOUND) = Demo_Sound;
        *(u8*)(p + EEP_MONITOR_FLIP) = Monitor_Flip;
        *(u8*)(p + EEP_LANGUAGE) = Language;
        *(u8*)(p + EEP_FREE_PLAY) = Free_Play_Enable;
        *(u8*)(p + EEP_CARD_DISPENSER) = ((s8)Card_Dispenser);
        *(u8*)(p + EEP_WIN_POINT_COM) = Win_Point_Com;
        *(u8*)(p + EEP_WIN_POINT_HUMAN) = Win_Point_Human;
        *(u8*)(p + EEP_VOICE_TYPE) = Voice_Type;
        if (Sound_Mode == 0) {
            sound_init((u8*)snd_seq_rom_data, (SNDSAMPLE*)snd_sample_rom_tbl, (u8**)snd_bank_rom_tbl, 1, 0, 1);
        } else {
            sound_init((u8*)snd_seq_rom_data, (SNDSAMPLE*)snd_sample_rom_tbl, (u8**)snd_bank_rom_tbl, 1, 0, 0);
        }
        if (Free_Play_Enable == 0) {
            *(u8*)(p + EEP_FREE_PLAY) = 0;
        }
        p += EEP_GAME;
        src = (s8 *)&Game_setting;
        for (j = 0; j < EEP_GAME_SIZE; j++) {
            *(u8*)p = *src;
            p++;
            src++;
        }
    }
    if (eeprom_write(48, (u16*)EEP_ROM_WRITE, (u16*)eeprom_w)) {
        eeprom_error_halt();
    }
    eeprom_config_apply((u32)eeprom_w);
}



/* provisional name */
void eeprom_config_default(void) {
    register s8 ix;
    register s16 k;
    register s16 j;
    const u8** table;
    u8* dst;
    const u8* src;
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
        src = table[ix];
        for (j = 0; j < EEP_SYSTEM_SIZE; j++) {
            *dst = *src;
            dst++;
            src++;
        }
        src = game_cfg_default_tbl[ix];
        for (j = 0; j < EEP_GAME_SIZE; j++) {
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
        if (eeprom_read(64, (u16*)EEP_ROM_READ, (u16*)eeprom_w)) {
            eeprom_error_halt();
        }
        a = eeprom_w;
        b = &eeprom_w[EEP_BACKUP];
        for (i = 0; i < EEP_COPY_SIZE; i++) {
            if (*a != *b) {
                break;
            }
            a++;
            b++;
        }
        if (i == EEP_COPY_SIZE) {
            return;
        }
        eeprom_retry--;
    }
    eeprom_config_reset();
}



