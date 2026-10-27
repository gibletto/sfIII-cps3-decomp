/*
 * EFF13_TBL.C  projectile process and shadow tables
 *
 * kind_of_tama_process is the jump table of the four shell processes kotp_00000 .. kotp_03000,
 * picked by a shell's kind of tama, and kage_tbl gives the shadow offset, priority and pattern
 * of each shadow index. Read by EFF13.C, the projectiles.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const kind_of_tama_process[])(WORK_Other* ewk, TAMA* twk);
extern const s16 kage_tbl[][4];
extern void kotp_00000();
extern void kotp_01000();
extern void kotp_02000();
extern void kotp_03000();

void (*const kind_of_tama_process[4])(WORK_Other* ewk, TAMA* twk) = {
    kotp_00000, kotp_01000, kotp_02000, kotp_03000,
};

const s16 kage_tbl[6][4] = {
    { 0, 0, 71, 0 }, { 0, 0, 71, 3 }, { 0, 0, 71, 4 }, { 0, 0, 71, 9 },
    { 0, 0, 71, 1 }, { 0, 0, 71, 0 },
};
