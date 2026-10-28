/*
 * PLS03_TBL.C  attack button check tables
 *
 * shot_prio turns pressed buttons into an attack strength in priority order and shot_refresh
 * gives the button bit of each strength; catch_kos_table gives the throw strength from the
 * buttons pressed; meoshi_off_shot holds the buttons that cancel a press-and-release move, and
 * renda_status_table the postures checked for the rapid-fire cancel. Read by PLS03.C, the
 * special move, super art and normal attack command checks.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 shot_prio[][2];
extern const s16 shot_refresh[];
extern const s16 catch_kos_table[];
extern const u16 meoshi_off_shot[];
extern const u8 renda_status_table[];

const s16 shot_prio[6][2] = {
    { 128, 3 }, { 16, 0 }, { 256, 4 }, { 32, 1 }, { 512, 5 }, { 64, 2 },
};

const s16 shot_refresh[6] = {
    16, 32, 64, 128, 256, 512,
};

const s16 catch_kos_table[8] = {
    0, 0, 1, 1, 2, 2, 2, 2,
};

const u16 meoshi_off_shot[6] = {
    0x3E0, 0x3D0, 0x3B0, 0x370, 0x2F0, 0x1F0,
};

const u8 renda_status_table[4] = {
    0, 20, 32, 0,
};
