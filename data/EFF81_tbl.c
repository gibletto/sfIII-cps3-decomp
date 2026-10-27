/*
 * EFF81_TBL.C  placements of the effect 81 companions
 *
 * eff81_data_tbl gives each of the three companions its pattern, priority and x and y offset
 * from the target it flies to. Read by EFF81.C, the companions of the effect 77 stage
 * character, whose effect_81_init nothing calls.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff81_data_tbl[][4];

const s16 eff81_data_tbl[3][4] = {
    { 0, 69, -112, 36 }, { 1, 20, -152, -16 }, { 2, 10, 160, -16 },
};
