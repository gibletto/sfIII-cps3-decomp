/*
 * EFF71_DATA.C  character weights of the watching stage object
 *
 * eff71_char_tbl gives each character number a weight (0 to 2): the object watches the fighter
 * with the higher weight, or follows the stage scroll when the weights are equal. Read by
 * EFF71.C, the stage object that watches the fighters.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 eff71_char_tbl[];

const s16 eff71_char_tbl[16] = {
    0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0,
};
