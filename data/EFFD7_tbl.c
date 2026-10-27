/*
 * EFFD7_TBL.C  super art plate positions and colours
 *
 * effD7_plate_pos gives, for each player side, the x and y of the three plate rows, and
 * effD7_plate_col the colour of each row's plate. Read by EFFD7.C, the super art selection
 * plates.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 effD7_plate_pos[][6];
extern const s16 effD7_plate_col[][3];

const s16 effD7_plate_pos[2][6] = {
    { 600, 104, 608, 122, 616, 140 }, { 808, 104, 800, 122, 792, 140 },
};

const s16 effD7_plate_col[2][3] = {
    { 8256, 8268, 8269 }, { 8265, 8266, 8267 },
};
