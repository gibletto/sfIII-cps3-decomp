/*
 * EFFH2_TBL.C  vote panel marker path and ending pictures
 *
 * panel_guide is the eight { x, y } offsets the H2 marker steps through around the panel, one
 * step every eight frames; read by EFFH2.C, the marker on a judge's vote panel. effH3_data_tbl
 * gives the x, y and pattern of each of the five ending pictures; read by EFFH3.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s16 panel_guide[][2];
extern const s16 effH3_data_tbl[][3];

const s16 panel_guide[8][2] = {
    { 0, 6 }, { 0, 5 }, { 0, 4 }, { 0, 2 }, { 0, 0 }, { 0, 2 }, { 0, 4 }, { 0, 5 },
};

const s16 effH3_data_tbl[5][3] = {
    { 512, 0, 0 }, { 256, 136, 2 }, { 768, 136, 2 }, { 256, 280, 2 },
    { 768, 280, 2 },
};
