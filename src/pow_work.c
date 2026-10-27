/*
 * POW_WORK.C  damage work
 *
 * Damage_Data_Ptr, each player's damage table, which pow_pow.c reads: initialised work RAM (section D). It starts
 * at Damage_Power_Data for every player.
 */

#include "types.h"
#include "structs.h"

extern const DAMAGE_DATA* Damage_Data_Ptr[];
extern const DAMAGE_DATA Damage_Power_Data[];

/* 02000D3C */
/* each player's damage table (the characters' tables in CCHR), set when the character is (provisional name) */
const DAMAGE_DATA* Damage_Data_Ptr[16] = {
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
    Damage_Power_Data, Damage_Power_Data,
};
