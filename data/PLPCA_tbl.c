/*
 * PLPCA_TBL.C  throw routine table
 *
 * plpca_lv_00 is the list of throw routines Catch_00000 - Catch_05000, indexed by catch
 * routine number. Read by PLPCA.C, the player catch (throwing) process.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const plpca_lv_00[])(PLW*);
extern void Catch_00000();
extern void Catch_01000();
extern void Catch_02000();
extern void Catch_03000();
extern void Catch_04000();
extern void Catch_05000();

void (*const plpca_lv_00[6])(PLW*) = {
    Catch_00000, Catch_01000, Catch_02000, Catch_03000, Catch_04000, Catch_05000,
};
