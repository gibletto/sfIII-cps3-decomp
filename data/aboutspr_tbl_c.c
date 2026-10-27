/*
 * ABOUTSPR_TBL_C.C  character sprite cell tables
 *
 * char_cell_flip_tbl picks the cell flip routine by the flip a cell set was built with and the
 * flip wanted; make_char_cells_tbl lists the cell builders for each sprite flip
 * (make_char_cells_n/x/y/xy); cell_size_tbl and flip_attr_tbl give the sprite size and flip
 * attribute codes; judge_area_code_tbl is the cell code of each hit and hurt box kind drawn by
 * the judge-area display; zoom_up_tbl and zoom_down_tbl the zoom divisors above and below
 * normal size, and cell_zoom_tbl the zoom lookup of get_cell_zoom. Read by ABOUTSPR.C.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern s32 (*const char_cell_flip_tbl[][4])(WORK* wk);
extern void (*const make_char_cells_tbl[])();
extern const s16 cell_size_tbl[];
extern const u16 flip_attr_tbl[];
extern const s16 judge_area_code_tbl[];
extern const s16 zoom_down_tbl[];
extern const s16 zoom_up_tbl[];
extern const s16 cell_zoom_tbl[][128];
extern void char_cell_flip_none();
extern void char_cell_flip_x();
extern void char_cell_flip_xy();
extern void char_cell_flip_y();
extern void char_cell_unflip_xy();
extern void char_cell_unflip_y();
extern void make_char_cells_n();
extern void make_char_cells_x();
extern void make_char_cells_xy();
extern void make_char_cells_y();

s32 (*const char_cell_flip_tbl[4][4])(WORK* wk) = {
    { char_cell_flip_none, char_cell_flip_x, char_cell_flip_y, char_cell_flip_xy },
    { char_cell_flip_x, char_cell_flip_none, char_cell_flip_xy, char_cell_flip_y },
    { char_cell_unflip_y, char_cell_unflip_xy, char_cell_flip_none, char_cell_flip_x },
    { char_cell_unflip_xy, char_cell_unflip_y, char_cell_flip_x, char_cell_flip_none },
};

void (*const make_char_cells_tbl[4])() = {
    make_char_cells_n, make_char_cells_x, make_char_cells_y, make_char_cells_xy,
};

const s16 cell_size_tbl[16] = {
    1792, 1807, 1823, 1855, 3840, 3855, 3871, 3903, 7936, 7951, 7967, 7999, 16128, 16143, 16159, 16191,
};

const u16 flip_attr_tbl[4] = {
    0, 0x1000, 0x800, 0x1800,
};

const s16 judge_area_code_tbl[12] = {
    0, 0, 8, 8, 16, 24, 32, 32, 40, 48, 56, 58,
};

const s16 zoom_down_tbl[64] = {
    0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

const s16 zoom_up_tbl[64] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

const s16 cell_zoom_tbl[4][128] = {
    {
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9,
        10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11,
        12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13,
        14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15,
    },
    {
        0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
        4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7,
        8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11,
        12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15,
        16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19,
        20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23,
        24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27,
        28, 28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 31,
    },
    {
        0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
        8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15,
        16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23,
        24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31,
        32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39,
        40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47,
        48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55,
        56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63,
    },
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
        96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    },
};
