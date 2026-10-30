/*
 * PLCNT_TBL.C  player control routine tables and per-character base data
 *
 * player_main_process (init, move, die), appear_initalize (start-of-round set-ups) and
 * settle_process (the four settlement types) are the routine tables of player control, and
 * quake_table the shake offsets by quake value. By character: plid_data (character set),
 * weight_lv_table (weight level), spmv_ng_table (the spmv_ng_flag value), kage_base (shadow
 * offset and pattern) and super_arts_data (12 bytes per super art). Read by PLCNTSET_2.C, the
 * player control and fight settlement.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const player_main_process[])(void);
extern void (*const appear_initalize[])(void);
extern void (*const settle_process[])();
extern const s8 plid_data[];
extern const s8 weight_lv_table[];
extern const s16 quake_table[];
extern const u32 spmv_ng_table[];
extern const s16 kage_base[][2];
extern const SA_DATA super_arts_data[][4];
extern void init_app_10000();
extern void init_app_20000();
extern void init_app_30000();
extern void plcnt_die();
extern void plcnt_init();
extern void plcnt_move();
extern void settle_type_00000();
extern void settle_type_10000();
extern void settle_type_20000();
extern void settle_type_30000();

void (*const player_main_process[3])(void) = {
    plcnt_init, plcnt_move, plcnt_die,
};

void (*const appear_initalize[4])(void) = {
    init_app_10000, init_app_10000, init_app_20000, init_app_30000,
};

void (*const settle_process[4])() = {
    settle_type_00000, settle_type_10000, settle_type_20000, settle_type_30000,
};

const s8 plid_data[16] = {
    6, 3, 5, 1, 2, 9, 7, 4, 10, 8, 12, 13, 14, 0, 0, 0,
};

const s8 weight_lv_table[16] = {
    2, 2, 1, 0, 1, 2, 3, 0, 1, 0, 0, 1, 1, 0, 0, 0,
};

const s16 quake_table[42] = {
    1, -1, 1, -1, 1, -1, 1, -2, 1, -2, 1, -2, 1, -2, 1, -2,
    1, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2,
    2, -2, 2, -2, 2, -2, 2, -2, 2, -2,
};

const u32 spmv_ng_table[16] = {
    0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023,
    0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023, 0x10023,
};

const s16 kage_base[16][2] = {
    { 0, 21 },  /* Gill */
    { 0, 30 },  /* Alex */
    { 0, 21 },  /* Ryu */
    { -4, 16 },  /* Yun */
    { 4, 21 },  /* Dudley */
    { 6, 20 },  /* Necro */
    { -4, 26 },  /* Hugo */
    { -4, 20 },  /* Ibuki */
    { 0, 25 },  /* Elena */
    { -3, 22 },  /* Oro */
    { -4, 15 },  /* Yang */
    { 0, 21 },  /* Ken */
    { 0, 21 },  /* Sean */
    { 0, 0 },  /* 13 */
    { 0, 0 },  /* 14 */
    { 0, 0 },  /* 15 */
};

const SA_DATA super_arts_data[16][4] = {
    {  /* Gill */
        { 16, SA_GAUGE_REBIRTH, 128, 1, 0, 0x10000 },
        { 17, SA_GAUGE_REBIRTH, 128, 1, 0, 0x10000 },
        { 18, SA_GAUGE_REBIRTH, 128, 1, 0, 0x10000 },
        { 0, SA_GAUGE_REBIRTH, 64, 1, 0, 0x10000 },
    },
    {  /* Alex */
        { 16, SA_GAUGE_STOCK, 128, 1, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 64, 2, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 80, 1, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 0, 0, 0, 0x10000 },
    },
    {  /* Ryu */
        { 16, SA_GAUGE_STOCK, 104, 1, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 120, 1, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 88, 1, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 0, 0, 0, 0x10000 },
    },
    {  /* Yun */
        { 18, SA_GAUGE_STOCK, 112, 2, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 88, 3, 0, 0x10000 },
        { 16, SA_GAUGE_TIMER, 64, 1, 0, 0x4000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Dudley */
        { 16, SA_GAUGE_STOCK, 88, 2, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 112, 1, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 80, 3, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Necro */
        { 16, SA_GAUGE_STOCK, 96, 2, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 96, 1, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 64, 2, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Hugo */
        { 16, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
        { 17, SA_GAUGE_TIMER, 64, 1, 0, 0x444 },
        { 18, SA_GAUGE_STOCK2, 64, 1, 0, 0x10000 },
        { 0, SA_GAUGE_REBIRTH, 64, 1, 0, 0x10000 },
    },
    {  /* Ibuki */
        { 33, SA_GAUGE_STOCK, 72, 2, 0, 0x10000 }, { 17, SA_GAUGE_STOCK, 96, 1, 0, 0x10000 },
        { 16, SA_GAUGE_STOCK, 64, 2, 0, 0x10000 }, { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Elena */
        { 16, SA_GAUGE_STOCK, 64, 2, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 96, 1, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 120, 1, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Oro */
        { 18, SA_GAUGE_TIMER, 112, 1, 0, 0x5555 },
        { 17, SA_GAUGE_STOCK, 88, 3, 0, 0x10000 },
        { 16, SA_GAUGE_TIMER, 96, 1, 0, 0x2000 },
        { 0, SA_GAUGE_STOCK, 64, 0, 0, 0x10000 },
    },
    {  /* Yang */
        { 18, SA_GAUGE_STOCK, 112, 2, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 88, 3, 0, 0x10000 },
        { 16, SA_GAUGE_TIMER, 64, 1, 0, 0x4000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Ken */
        { 16, SA_GAUGE_STOCK, 104, 1, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 112, 2, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 80, 2, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* Sean */
        { 16, SA_GAUGE_STOCK, 72, 3, 0, 0x10000 },
        { 17, SA_GAUGE_STOCK, 96, 3, 0, 0x10000 },
        { 18, SA_GAUGE_STOCK, 112, 2, 0, 0x10000 },
        { 0, SA_GAUGE_STOCK, 64, 1, 0, 0x10000 },
    },
    {  /* 13 */
        { 16, SA_GAUGE_STOCK, 64, 9, 0, 0x10000 },
        { 17, SA_GAUGE_TIMER, 64, 1, 0, 0x444 },
        { 18, SA_GAUGE_STOCK2, 64, 1, 0, 0x10000 },
        { 0, SA_GAUGE_REBIRTH, 64, 1, 0, 0x10000 },
    },
    {  /* 14 */
        { 16, SA_GAUGE_STOCK, 64, 9, 0, 0x10000 },
        { 17, SA_GAUGE_TIMER, 64, 1, 0, 0x444 },
        { 18, SA_GAUGE_STOCK2, 64, 1, 0, 0x10000 },
        { 0, SA_GAUGE_REBIRTH, 64, 1, 0, 0x10000 },
    },
    {  /* 15 */
        { 16, SA_GAUGE_STOCK, 64, 9, 0, 0x10000 },
        { 17, SA_GAUGE_TIMER, 64, 1, 0, 0x444 },
        { 18, SA_GAUGE_STOCK2, 64, 1, 0, 0x10000 },
        { 0, SA_GAUGE_REBIRTH, 64, 1, 0, 0x10000 },
    },
};
