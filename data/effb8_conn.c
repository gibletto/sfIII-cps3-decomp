/*
 * EFFB8_CONN.C  The cells connected to the win messages
 *
 * The arrays of message records effB8_conn_tbl points at, one per player, and the lists the records
 * name. Effect B8 picks a player's array from effB8_conn_tbl; a record names a conn list (the
 * panel's cells: x, y, colour, character) and a chr list (the number of characters to load, the
 * characters, the number of cells). An array is named after the first entry of effB8_conn_tbl
 * (player number) that points at it, its lists after the array and the index of their pointer in it
 * (record j: conn 2j, chr 2j + 1).
 */

#include "types.h"
#include "structs.h"

#pragma section CHR

extern const CONN effB8_conn_0_0[], effB8_conn_0_2[], effB8_conn_0_4[], effB8_conn_0_6[], effB8_conn_0_8[],
                  effB8_conn_0_10[];
extern const u16 effB8_conn_0_1[], effB8_conn_0_3[], effB8_conn_0_5[], effB8_conn_0_7[], effB8_conn_0_9[],
                 effB8_conn_0_11[];

/* effB8_conn_tbl[0], effB8_conn_tbl[6]: Gill's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_0[6] = {
    { effB8_conn_0_0, effB8_conn_0_1 },  /* 0 */
    { effB8_conn_0_2, effB8_conn_0_3 },  /* 1 */
    { effB8_conn_0_4, effB8_conn_0_5 },  /* 2 */
    { effB8_conn_0_6, effB8_conn_0_7 },  /* 3 */
    { effB8_conn_0_8, effB8_conn_0_9 },  /* 4 */
    { effB8_conn_0_10, effB8_conn_0_11 },  /* 5 */
};

const CONN effB8_conn_0_0[6] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6884 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A6 },
    {   48,    0,   0, 0x688E },
    {   64,    0,   0, 0x68B7 },
    {   80,    0,   0, 0x68C6 },
};

const CONN effB8_conn_0_2[9] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x689B },
    {   16,    0,   0, 0x68AE },
    {   32,    0,   0, 0x6881 },
    {   48,    0,   0, 0x6880 },
    {   64,    0,   0, 0x68B7 },
    {   80,    0,   0, 0x6894 },
    {   96,    0,   0, 0x68B3 },
    {  112,    0,   0, 0x6887 },
    {  128,    0,   0, 0x68A8 },
};

const CONN effB8_conn_0_4[7] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x689A },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A8 },
    {   48,    0,   0, 0x689B },
    {   64,    0,   0, 0x68B2 },
    {   80,    0,   0, 0x68B7 },
    {   96,    0,   0, 0x688C },
};

const CONN effB8_conn_0_6[10] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6884 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A6 },
    {   48,    0,   0, 0x6818 },
    {   64,    0,   0, 0x6A2A },
    {   80,    0,   0, 0x684B },
    {  160,    0,   0, 0x6924 },
    {  176,    0,   0, 0x6AC4 },
    {  192,    0,   0, 0x6AE8 },
    {  208,    0,   0, 0x6A73 },
};

const CONN effB8_conn_0_8[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6884 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A6 },
    {   48,    0,   0, 0x6919 },
    {   64,    0,   0, 0x684B },
    {  160,    0,   0, 0x68CC },
    {  176,    0,   0, 0x68AB },
    {  192,    0,   0, 0x68B7 },
    {  208,    0,   0, 0x6880 },
    {  224,    0,   0, 0x68B3 },
    {  240,    0,   0, 0x68CE },
};

const CONN effB8_conn_0_10[10] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6884 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A6 },
    {   48,    0,   0, 0x6818 },
    {   64,    0,   0, 0x6919 },
    {   80,    0,   0, 0x684B },
    {  160,    0,   0, 0x69F2 },
    {  176,    0,   0, 0x6AC5 },
    {  192,    0,   0, 0x680C },
    {  208,    0,   0, 0x6828 },
};

const u16 effB8_conn_0_1[3] = {
    1,  /* characters */
    0x6880,
    6,  /* cells */
};

const u16 effB8_conn_0_3[3] = {
    1,  /* characters */
    0x6880,
    9,  /* cells */
};

const u16 effB8_conn_0_5[3] = {
    1,  /* characters */
    0x6880,
    7,  /* cells */
};

const u16 effB8_conn_0_7[7] = {
    5,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6A00, 0x6A80,
    10,  /* cells */
};

const u16 effB8_conn_0_9[5] = {
    3,  /* characters */
    0x6800, 0x6880, 0x6900,
    11,  /* cells */
};

const u16 effB8_conn_0_11[7] = {
    5,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980, 0x6A80,
    10,  /* cells */
};

extern const CONN effB8_conn_1_0[], effB8_conn_1_2[], effB8_conn_1_4[], effB8_conn_1_6[], effB8_conn_1_8[],
                  effB8_conn_1_10[];
extern const u16 effB8_conn_1_1[], effB8_conn_1_3[], effB8_conn_1_5[], effB8_conn_1_7[], effB8_conn_1_9[],
                 effB8_conn_1_11[];

/* effB8_conn_tbl[1]: Alex's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_1[6] = {
    { effB8_conn_1_0, effB8_conn_1_1 },  /* 0 */
    { effB8_conn_1_2, effB8_conn_1_3 },  /* 1 */
    { effB8_conn_1_4, effB8_conn_1_5 },  /* 2 */
    { effB8_conn_1_6, effB8_conn_1_7 },  /* 3 */
    { effB8_conn_1_8, effB8_conn_1_9 },  /* 4 */
    { effB8_conn_1_10, effB8_conn_1_11 },  /* 5 */
};

const CONN effB8_conn_1_0[6] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6899 },
    {   16,    0,   0, 0x6881 },
    {   32,    0,   0, 0x68CC },
    {   48,    0,   0, 0x68B7 },
    {   64,    0,   0, 0x68CB },
    {   80,    0,   0, 0x68A0 },
};

const CONN effB8_conn_1_2[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x68C9 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A1 },
    {   48,    0,   0, 0x68A6 },
    {   64,    0,   0, 0x68AD },
    {   80,    0,   0, 0x68C9 },
    {   96,    0,   0, 0x68AA },
    {  112,    0,   0, 0x68B7 },
};

const CONN effB8_conn_1_4[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x688C },
    {   16,    0,   0, 0x688F },
    {   32,    0,   0, 0x68AD },
    {   48,    0,   0, 0x68B8 },
    {   64,    0,   0, 0x68AD },
    {  160,    0,   0, 0x689C },
    {  176,    0,   0, 0x68B3 },
    {  192,    0,   0, 0x68C6 },
    {  208,    0,   0, 0x68C7 },
    {  224,    0,   0, 0x68B3 },
    {  240,    0,   0, 0x6893 },
};

const CONN effB8_conn_1_6[16] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A3E },
    {   16,    0,   0, 0x6841 },
    {   32,    0,   0, 0x690E },
    {   48,    0,   0, 0x6818 },
    {   64,    0,   0, 0x6AC6 },
    {   80,    0,   0, 0x6A3F },
    {   96,    0,   0, 0x684B },
    {  144,    0,   0, 0x69BD },
    {  160,    0,   0, 0x68C2 },
    {  176,    0,   0, 0x68A1 },
    {  192,    0,   0, 0x68B7 },
    {  208,    0,   0, 0x68BE },
    {  224,    0,   0, 0x682C },
    {  240,    0,   0, 0x6952 },
    {    0,  -16,   0, 0x6803 },
    {   16,  -16,   0, 0x6828 },
};

const CONN effB8_conn_1_8[18] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AC7 },
    {   16,    0,   0, 0x6807 },
    {   32,    0,   0, 0x691C },
    {   48,    0,   0, 0x6AC4 },
    {   64,    0,   0, 0x684B },
    {   80,    0,   0, 0x6908 },
    {   96,    0,   0, 0x6806 },
    {  112,    0,   0, 0x682C },
    {  128,    0,   0, 0x6A64 },
    {  144,    0,   0, 0x6821 },
    {  160,    0,   0, 0x6837 },
    {  176,    0,   0, 0x6A3E },
    {  192,    0,   0, 0x6841 },
    {  208,    0,   0, 0x682C },
    {  224,    0,   0, 0x6A6A },
    {  240,    0,   0, 0x6826 },
    {    0,  -16,   0, 0x682B },
    {   16,  -16,   0, 0x680C },
};

const CONN effB8_conn_1_10[15] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A93 },
    {   16,    0,   0, 0x680B },
    {   32,    0,   0, 0x6801 },
    {   48,    0,   0, 0x6ACD },
    {   64,    0,   0, 0x6AC9 },
    {   80,    0,   0, 0x6806 },
    {   96,    0,   0, 0x684B },
    {  160,    0,   0, 0x6986 },
    {  176,    0,   0, 0x691C },
    {  192,    0,   0, 0x682C },
    {  208,    0,   0, 0x691A },
    {  224,    0,   0, 0x6ACA },
    {  240,    0,   0, 0x6ACB },
    {    0,  -16,   0, 0x6ACC },
    {   16,  -16,   0, 0x6815 },
};

const u16 effB8_conn_1_1[3] = {
    1,  /* characters */
    0x6880,
    6,  /* cells */
};

const u16 effB8_conn_1_3[3] = {
    1,  /* characters */
    0x6880,
    8,  /* cells */
};

const u16 effB8_conn_1_5[3] = {
    1,  /* characters */
    0x6880,
    11,  /* cells */
};

const u16 effB8_conn_1_7[8] = {
    6,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980, 0x6A00, 0x6A80,
    16,  /* cells */
};

const u16 effB8_conn_1_9[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6A00, 0x6A80,
    18,  /* cells */
};

const u16 effB8_conn_1_11[7] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A80,
    15,  /* cells */
    0x0500,
};

extern const CONN effB8_conn_2_0[], effB8_conn_2_2[], effB8_conn_2_4[], effB8_conn_2_6[], effB8_conn_2_8[],
                  effB8_conn_2_10[];
extern const u16 effB8_conn_2_1[], effB8_conn_2_3[], effB8_conn_2_5[], effB8_conn_2_7[], effB8_conn_2_9[],
                 effB8_conn_2_11[];

/* effB8_conn_tbl[2]: Ryu's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_2[6] = {
    { effB8_conn_2_0, effB8_conn_2_1 },  /* 0 */
    { effB8_conn_2_2, effB8_conn_2_3 },  /* 1 */
    { effB8_conn_2_4, effB8_conn_2_5 },  /* 2 */
    { effB8_conn_2_6, effB8_conn_2_7 },  /* 3 */
    { effB8_conn_2_8, effB8_conn_2_9 },  /* 4 */
    { effB8_conn_2_10, effB8_conn_2_11 },  /* 5 */
};

const CONN effB8_conn_2_0[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x697B },
    {   16,    0,   0, 0x6A17 },
    {   32,    0,   0, 0x6907 },
    {   48,    0,   0, 0x6908 },
    {   64,    0,   0, 0x6909 },
    {  144,    0,   0, 0x6784 },
    {  160,    0,   0, 0x6783 },
    {  176,    0,   0, 0x6782 },
    {  192,    0,   0, 0x6784 },
    {  208,    0,   0, 0x6783 },
    {  224,    0,   0, 0x6782 },
    {  240,    0,   0, 0x6788 },
    {    0,  -16,   0, 0x6789 },
};

const CONN effB8_conn_2_2[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69CD },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6A8F },
    {   48,    0,   0, 0x690B },
    {  160,    0,   0, 0x6784 },
    {  176,    0,   0, 0x6783 },
    {  192,    0,   0, 0x6782 },
    {  208,    0,   0, 0x6784 },
    {  224,    0,   0, 0x6783 },
    {  240,    0,   0, 0x6788 },
    {    0,  -16,   0, 0x6789 },
};

const CONN effB8_conn_2_4[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AD5 },
    {   16,    0,   0, 0x6AE9 },
    {   32,    0,   0, 0x6907 },
    {   48,    0,   0, 0x6908 },
    {   64,    0,   0, 0x6909 },
    {  160,    0,   0, 0x6786 },
    {  176,    0,   0, 0x6785 },
    {  192,    0,   0, 0x6784 },
    {  208,    0,   0, 0x6783 },
    {  224,    0,   0, 0x6782 },
    {  240,    0,   0, 0x6788 },
    {    0,  -16,   0, 0x6789 },
};

const CONN effB8_conn_2_6[18] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6900 },
    {   16,    0,   0, 0x6818 },
    {   32,    0,   0, 0x6901 },
    {   48,    0,   0, 0x6902 },
    {   64,    0,   0, 0x6815 },
    {   80,    0,   0, 0x6903 },
    {   96,    0,   0, 0x680B },
    {  112,    0,   0, 0x680F },
    {  128,    0,   0, 0x6904 },
    {  144,    0,   0, 0x6905 },
    {  160,    0,   0, 0x6827 },
    {  176,    0,   0, 0x6906 },
    {  192,    0,   0, 0x680A },
    {  208,    0,   0, 0x6829 },
    {  224,    0,   0, 0x6828 },
    {  240,    0,   0, 0x6907 },
    {    0,  -16,   0, 0x6908 },
    {   16,  -16,   0, 0x6909 },
};

const CONN effB8_conn_2_8[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x690A },
    {   16,    0,   0, 0x690B },
    {   32,    0,   0, 0x6827 },
    {   48,    0,   0, 0x6848 },
    {   64,    0,   0, 0x6839 },
    {  160,    0,   0, 0x6888 },
    {  176,    0,   0, 0x68AD },
    {  192,    0,   0, 0x6818 },
    {  208,    0,   0, 0x690C },
    {  224,    0,   0, 0x690D },
    {  240,    0,   0, 0x690E },
};

const CONN effB8_conn_2_10[17] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6801 },
    {   16,    0,   0, 0x6805 },
    {   32,    0,   0, 0x6845 },
    {   48,    0,   0, 0x6810 },
    {   64,    0,   0, 0x682C },
    {   80,    0,   0, 0x681E },
    {   96,    0,   0, 0x6813 },
    {  112,    0,   0, 0x6801 },
    {  144,    0,   0, 0x68B8 },
    {  160,    0,   0, 0x68B7 },
    {  176,    0,   0, 0x68C6 },
    {  192,    0,   0, 0x6822 },
    {  208,    0,   0, 0x690F },
    {  224,    0,   0, 0x6806 },
    {  240,    0,   0, 0x6910 },
    {    0,  -16,   0, 0x684D },
    {   16,  -16,   0, 0x680C },
};

const u16 effB8_conn_2_1[5] = {
    3,  /* characters */
    0x6780, 0x6900, 0x6A00,
    13,  /* cells */
};

const u16 effB8_conn_2_3[6] = {
    4,  /* characters */
    0x6780, 0x6900, 0x6980, 0x6A80,
    11,  /* cells */
};

const u16 effB8_conn_2_5[5] = {
    3,  /* characters */
    0x6780, 0x6900, 0x6A80,
    12,  /* cells */
};

const u16 effB8_conn_2_7[4] = {
    2,  /* characters */
    0x6800, 0x6900,
    18,  /* cells */
};

const u16 effB8_conn_2_9[5] = {
    3,  /* characters */
    0x6800, 0x6880, 0x6900,
    11,  /* cells */
};

const u16 effB8_conn_2_11[5] = {
    3,  /* characters */
    0x6800, 0x6880, 0x6900,
    17,  /* cells */
};

extern const CONN effB8_conn_3_0[], effB8_conn_3_2[], effB8_conn_3_4[], effB8_conn_3_6[], effB8_conn_3_8[],
                  effB8_conn_3_10[];
extern const u16 effB8_conn_3_1[], effB8_conn_3_3[], effB8_conn_3_5[], effB8_conn_3_7[], effB8_conn_3_9[],
                 effB8_conn_3_11[];

/* effB8_conn_tbl[3]: Yun's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_3[6] = {
    { effB8_conn_3_0, effB8_conn_3_1 },  /* 0 */
    { effB8_conn_3_2, effB8_conn_3_3 },  /* 1 */
    { effB8_conn_3_4, effB8_conn_3_5 },  /* 2 */
    { effB8_conn_3_6, effB8_conn_3_7 },  /* 3 */
    { effB8_conn_3_8, effB8_conn_3_9 },  /* 4 */
    { effB8_conn_3_10, effB8_conn_3_11 },  /* 5 */
};

const CONN effB8_conn_3_0[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6910 },
    {   16,    0,   0, 0x6AEA },
    {   32,    0,   0, 0x6AEB },
    {   48,    0,   0, 0x6A80 },
};

const CONN effB8_conn_3_2[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AEC },
    {   16,    0,   0, 0x6A94 },
    {   32,    0,   0, 0x6889 },
    {   48,    0,   0, 0x6882 },
};

const CONN effB8_conn_3_4[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6ACA },
    {   16,    0,   0, 0x6AED },
    {   32,    0,   0, 0x6AEE },
    {   48,    0,   0, 0x694D },
};

const CONN effB8_conn_3_6[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6ACE },
    {   16,    0,   0, 0x6A17 },
    {   32,    0,   0, 0x6815 },
    {   48,    0,   0, 0x6812 },
    {   64,    0,   0, 0x6A80 },
    {   80,    0,   0, 0x6827 },
    {   96,    0,   0, 0x6815 },
    {  112,    0,   0, 0x6825 },
    {  128,    0,   0, 0x6828 },
    {  160,    0,   0, 0x6AEF },
    {  176,    0,   0, 0x6AC6 },
    {  192,    0,   0, 0x6A96 },
    {  208,    0,   0, 0x6839 },
};

const CONN effB8_conn_3_8[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69BD },
    {   16,    0,   0, 0x6806 },
    {   32,    0,   0, 0x6814 },
    {   48,    0,   0, 0x690B },
    {   64,    0,   0, 0x69DE },
    {   80,    0,   0, 0x6919 },
    {   96,    0,   0, 0x682C },
    {  112,    0,   0, 0x694F },
    {  128,    0,   0, 0x6811 },
    {  160,    0,   0, 0x69C1 },
    {  176,    0,   0, 0x69D1 },
    {  192,    0,   0, 0x6827 },
};

const CONN effB8_conn_3_10[1] = {
    /*  nx    ny  col  chr */
    {   16,    0,   0, 0x6957 },
};

const u16 effB8_conn_3_1[4] = {
    2,  /* characters */
    0x6900, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_3_3[4] = {
    2,  /* characters */
    0x6880, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_3_5[4] = {
    2,  /* characters */
    0x6900, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_3_7[5] = {
    3,  /* characters */
    0x6800, 0x6A00, 0x6A80,
    13,  /* cells */
};

const u16 effB8_conn_3_9[5] = {
    3,  /* characters */
    0x6800, 0x6900, 0x6980,
    12,  /* cells */
};

const u16 effB8_conn_3_11[4] = {
    1,  /* characters */
    0x6900,
    1,  /* cells */
    0xC42C,
};

extern const CONN effB8_conn_4_0[], effB8_conn_4_2[], effB8_conn_4_4[], effB8_conn_4_6[], effB8_conn_4_8[],
                  effB8_conn_4_10[];
extern const u16 effB8_conn_4_1[], effB8_conn_4_3[], effB8_conn_4_5[], effB8_conn_4_7[], effB8_conn_4_9[],
                 effB8_conn_4_11[];

/* effB8_conn_tbl[4]: Dudley's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_4[6] = {
    { effB8_conn_4_0, effB8_conn_4_1 },  /* 0 */
    { effB8_conn_4_2, effB8_conn_4_3 },  /* 1 */
    { effB8_conn_4_4, effB8_conn_4_5 },  /* 2 */
    { effB8_conn_4_6, effB8_conn_4_7 },  /* 3 */
    { effB8_conn_4_8, effB8_conn_4_9 },  /* 4 */
    { effB8_conn_4_10, effB8_conn_4_11 },  /* 5 */
};

const CONN effB8_conn_4_0[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x68AA },
    {   16,    0,   0, 0x6888 },
    {   32,    0,   0, 0x68B3 },
    {   48,    0,   0, 0x6893 },
    {   64,    0,   0, 0x6880 },
    {   80,    0,   0, 0x68B3 },
    {   96,    0,   0, 0x68CC },
    {  112,    0,   0, 0x68B7 },
};

const CONN effB8_conn_4_2[9] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x68AA },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A7 },
    {   48,    0,   0, 0x68AD },
    {   64,    0,   0, 0x68BA },
    {   80,    0,   0, 0x688A },
    {   96,    0,   0, 0x68AD },
    {  112,    0,   0, 0x68C2 },
    {  128,    0,   0, 0x68B7 },
};

const CONN effB8_conn_4_4[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6887 },
    {   16,    0,   0, 0x68AA },
    {   32,    0,   0, 0x688C },
    {   48,    0,   0, 0x6885 },
    {   64,    0,   0, 0x6882 },
    {   80,    0,   0, 0x68AD },
    {   96,    0,   0, 0x688F },
    {  112,    0,   0, 0x68B7 },
};

const CONN effB8_conn_4_6[18] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6899 },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68C6 },
    {   48,    0,   0, 0x689A },
    {   64,    0,   0, 0x68B3 },
    {   80,    0,   0, 0x6893 },
    {   96,    0,   0, 0x684B },
    {  112,    0,   0, 0x6986 },
    {  128,    0,   0, 0x691C },
    {  144,    0,   0, 0x682C },
    {  160,    0,   0, 0x6A54 },
    {  176,    0,   0, 0x681E },
    {  192,    0,   0, 0x684B },
    {  208,    0,   0, 0x6ACF },
    {  224,    0,   0, 0x6810 },
    {  240,    0,   0, 0x6912 },
    {    0,  -16,   0, 0x6841 },
    {   16,  -16,   0, 0x6828 },
};

const CONN effB8_conn_4_8[18] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6801 },
    {   16,    0,   0, 0x6833 },
    {   32,    0,   0, 0x680F },
    {   48,    0,   0, 0x682D },
    {   64,    0,   0, 0x6AD0 },
    {   80,    0,   0, 0x681E },
    {   96,    0,   0, 0x6803 },
    {  112,    0,   0, 0x6829 },
    {  128,    0,   0, 0x684D },
    {  144,    0,   0, 0x6AD1 },
    {  160,    0,   0, 0x6818 },
    {  176,    0,   0, 0x6AC6 },
    {  192,    0,   0, 0x6ACF },
    {  208,    0,   0, 0x684B },
    {  224,    0,   0, 0x6AD2 },
    {  240,    0,   0, 0x680A },
    {    0,  -16,   0, 0x6814 },
    {   16,  -16,   0, 0x6801 },
};

const CONN effB8_conn_4_10[18] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x68C2 },
    {   16,    0,   0, 0x68A1 },
    {   32,    0,   0, 0x68B7 },
    {   48,    0,   0, 0x68BE },
    {   64,    0,   0, 0x682C },
    {   80,    0,   0, 0x6A6A },
    {   96,    0,   0, 0x6826 },
    {  112,    0,   0, 0x6801 },
    {  128,    0,   0, 0x6814 },
    {  144,    0,   0, 0x683E },
    {  160,    0,   0, 0x6826 },
    {  176,    0,   0, 0x6822 },
    {  192,    0,   0, 0x693A },
    {  208,    0,   0, 0x69CC },
    {  224,    0,   0, 0x6818 },
    {  240,    0,   0, 0x6AD3 },
    {    0,  -16,   0, 0x6A96 },
    {   16,  -16,   0, 0x6ACF },
};

const u16 effB8_conn_4_1[3] = {
    1,  /* characters */
    0x6880,
    8,  /* cells */
};

const u16 effB8_conn_4_3[3] = {
    1,  /* characters */
    0x6880,
    9,  /* cells */
};

const u16 effB8_conn_4_5[3] = {
    1,  /* characters */
    0x6880,
    8,  /* cells */
};

const u16 effB8_conn_4_7[8] = {
    6,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980, 0x6A00, 0x6A80,
    18,  /* cells */
};

const u16 effB8_conn_4_9[4] = {
    2,  /* characters */
    0x6800, 0x6A80,
    18,  /* cells */
};

const u16 effB8_conn_4_11[9] = {
    6,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980, 0x6A00, 0x6A80,
    18,  /* cells */
    0x2B00,
};

extern const CONN effB8_conn_5_0[], effB8_conn_5_2[], effB8_conn_5_4[], effB8_conn_5_6[], effB8_conn_5_8[],
                  effB8_conn_5_10[];
extern const u16 effB8_conn_5_1[], effB8_conn_5_3[], effB8_conn_5_5[], effB8_conn_5_7[], effB8_conn_5_9[],
                 effB8_conn_5_11[];

/* effB8_conn_tbl[5]: Necro's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_5[6] = {
    { effB8_conn_5_0, effB8_conn_5_1 },  /* 0 */
    { effB8_conn_5_2, effB8_conn_5_3 },  /* 1 */
    { effB8_conn_5_4, effB8_conn_5_5 },  /* 2 */
    { effB8_conn_5_6, effB8_conn_5_7 },  /* 3 */
    { effB8_conn_5_8, effB8_conn_5_9 },  /* 4 */
    { effB8_conn_5_10, effB8_conn_5_11 },  /* 5 */
};

const CONN effB8_conn_5_0[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AF0 },
    {   16,    0,   0, 0x6AD5 },
    {   32,    0,   0, 0x6AD6 },
    {   48,    0,   0, 0x688B },
    {   64,    0,   0, 0x68B5 },
    {   80,    0,   0, 0x6893 },
    {   96,    0,   0, 0x68AA },
    {  112,    0,   0, 0x68A0 },
};

const CONN effB8_conn_5_2[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x688C },
    {   16,    0,   0, 0x68A6 },
    {   32,    0,   0, 0x68A0 },
    {   48,    0,   0, 0x6889 },
    {   64,    0,   0, 0x68AD },
    {   80,    0,   0, 0x68C7 },
    {   96,    0,   0, 0x6881 },
    {  112,    0,   0, 0x68AD },
};

const CONN effB8_conn_5_4[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x688C },
    {   16,    0,   0, 0x6897 },
    {   32,    0,   0, 0x6881 },
    {   48,    0,   0, 0x6887 },
    {   64,    0,   0, 0x6892 },
    {   80,    0,   0, 0x6881 },
    {   96,    0,   0, 0x689E },
    {  112,    0,   0, 0x68B7 },
    {  144,    0,   0, 0x689C },
    {  160,    0,   0, 0x68C8 },
    {  176,    0,   0, 0x6972 },
    {  192,    0,   0, 0x6801 },
};

const CONN effB8_conn_5_6[10] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69BC },
    {   16,    0,   0, 0x682C },
    {   32,    0,   0, 0x6AD4 },
    {   48,    0,   0, 0x6801 },
    {   64,    0,   0, 0x69AA },
    {   80,    0,   0, 0x6820 },
    {  160,    0,   0, 0x6AD5 },
    {  176,    0,   0, 0x6AD6 },
    {  192,    0,   0, 0x6818 },
    {  208,    0,   0, 0x6AD1 },
};

const CONN effB8_conn_5_8[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A3E },
    {   16,    0,   0, 0x6841 },
    {   32,    0,   0, 0x690E },
    {   48,    0,   0, 0x6818 },
    {   64,    0,   0, 0x6889 },
    {   80,    0,   0, 0x68AD },
    {   96,    0,   0, 0x68CB },
    {  112,    0,   0, 0x684B },
    {  160,    0,   0, 0x69BD },
    {  176,    0,   0, 0x68C2 },
    {  192,    0,   0, 0x68A1 },
    {  208,    0,   0, 0x68B7 },
    {  224,    0,   0, 0x68BE },
};

const CONN effB8_conn_5_10[16] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6902 },
    {   16,    0,   0, 0x682C },
    {   32,    0,   0, 0x6AD7 },
    {   48,    0,   0, 0x6828 },
    {   64,    0,   0, 0x6AD5 },
    {   80,    0,   0, 0x69C5 },
    {   96,    0,   0, 0x684B },
    {  112,    0,   0, 0x6986 },
    {  128,    0,   0, 0x691C },
    {  160,    0,   0, 0x6818 },
    {  176,    0,   0, 0x6908 },
    {  192,    0,   0, 0x6806 },
    {  208,    0,   0, 0x682C },
    {  224,    0,   0, 0x6A64 },
    {  240,    0,   0, 0x6821 },
    {    0,  -16,   0, 0x6828 },
};

const u16 effB8_conn_5_1[4] = {
    2,  /* characters */
    0x6880, 0x6A80,
    8,  /* cells */
};

const u16 effB8_conn_5_3[3] = {
    1,  /* characters */
    0x6880,
    8,  /* cells */
};

const u16 effB8_conn_5_5[5] = {
    3,  /* characters */
    0x6800, 0x6880, 0x6900,
    12,  /* cells */
};

const u16 effB8_conn_5_7[5] = {
    3,  /* characters */
    0x6800, 0x6980, 0x6A80,
    10,  /* cells */
};

const u16 effB8_conn_5_9[7] = {
    5,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980, 0x6A00,
    13,  /* cells */
};

const u16 effB8_conn_5_11[8] = {
    5,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A00, 0x6A80,
    16,  /* cells */
    0x1111,
};

extern const CONN effB8_conn_7_0[], effB8_conn_7_2[], effB8_conn_7_4[], effB8_conn_7_6[], effB8_conn_7_8[],
                  effB8_conn_7_10[];
extern const u16 effB8_conn_7_1[], effB8_conn_7_3[], effB8_conn_7_5[], effB8_conn_7_7[], effB8_conn_7_9[],
                 effB8_conn_7_11[];

/* effB8_conn_tbl[7]: Ibuki's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_7[6] = {
    { effB8_conn_7_0, effB8_conn_7_1 },  /* 0 */
    { effB8_conn_7_2, effB8_conn_7_3 },  /* 1 */
    { effB8_conn_7_4, effB8_conn_7_5 },  /* 2 */
    { effB8_conn_7_6, effB8_conn_7_7 },  /* 3 */
    { effB8_conn_7_8, effB8_conn_7_9 },  /* 4 */
    { effB8_conn_7_10, effB8_conn_7_11 },  /* 5 */
};

const CONN effB8_conn_7_0[3] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A92 },
    {   16,    0,   0, 0x69D8 },
    {   32,    0,   0, 0x6AF1 },
};

const CONN effB8_conn_7_2[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AF2 },
    {   16,    0,   0, 0x6AF3 },
    {   32,    0,   0, 0x6978 },
    {   48,    0,   0, 0x680B },
};

const CONN effB8_conn_7_4[7] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A7F },
    {   16,    0,   0, 0x684E },
    {   32,    0,   0, 0x6A80 },
    {   48,    0,   0, 0x6827 },
    {   64,    0,   0, 0x6AF9 },
    {   80,    0,   0, 0x6AF4 },
    {   96,    0,   0, 0x6AFA },
};

const CONN effB8_conn_7_6[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A80 },
    {   16,    0,   0, 0x6827 },
    {   32,    0,   0, 0x6813 },
    {   48,    0,   0, 0x691C },
    {   64,    0,   0, 0x6AD8 },
    {   80,    0,   0, 0x6A2A },
    {   96,    0,   0, 0x6818 },
    {  160,    0,   0, 0x6907 },
    {  176,    0,   0, 0x6ACB },
    {  192,    0,   0, 0x6AF5 },
    {  208,    0,   0, 0x6A96 },
};

const CONN effB8_conn_7_8[15] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6924 },
    {   16,    0,   0, 0x6AD9 },
    {   32,    0,   0, 0x6818 },
    {   48,    0,   0, 0x69F5 },
    {   64,    0,   0, 0x69AD },
    {   80,    0,   0, 0x6801 },
    {   96,    0,   0, 0x6805 },
    {  112,    0,   0, 0x6826 },
    {  160,    0,   0, 0x697D },
    {  176,    0,   0, 0x6ACF },
    {  192,    0,   0, 0x682C },
    {  208,    0,   0, 0x6905 },
    {  224,    0,   0, 0x6827 },
    {  240,    0,   0, 0x6906 },
    {    0,  -16,   0, 0x680C },
};

const CONN effB8_conn_7_10[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x680C },
    {   16,    0,   0, 0x684D },
    {   32,    0,   0, 0x6823 },
    {   48,    0,   0, 0x6801 },
    {   64,    0,   0, 0x6A7F },
    {   80,    0,   0, 0x6ADA },
    {   96,    0,   0, 0x684B },
    {  160,    0,   0, 0x6ADB },
    {  176,    0,   0, 0x6ADC },
    {  192,    0,   0, 0x680C },
    {  208,    0,   0, 0x6828 },
};

const u16 effB8_conn_7_1[4] = {
    2,  /* characters */
    0x6980, 0x6A80,
    3,  /* cells */
};

const u16 effB8_conn_7_3[5] = {
    3,  /* characters */
    0x6800, 0x6900, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_7_5[5] = {
    3,  /* characters */
    0x6800, 0x6A00, 0x6A80,
    7,  /* cells */
};

const u16 effB8_conn_7_7[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6A00, 0x6A80,
    11,  /* cells */
};

const u16 effB8_conn_7_9[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A80,
    15,  /* cells */
};

const u16 effB8_conn_7_11[6] = {
    3,  /* characters */
    0x6800, 0x6A00, 0x6A80,
    11,  /* cells */
    0x7777,
};

extern const CONN effB8_conn_8_0[], effB8_conn_8_2[], effB8_conn_8_4[], effB8_conn_8_6[], effB8_conn_8_8[],
                  effB8_conn_8_10[];
extern const u16 effB8_conn_8_1[], effB8_conn_8_3[], effB8_conn_8_5[], effB8_conn_8_7[], effB8_conn_8_9[],
                 effB8_conn_8_11[];

/* effB8_conn_tbl[8]: Elena's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_8[6] = {
    { effB8_conn_8_0, effB8_conn_8_1 },  /* 0 */
    { effB8_conn_8_2, effB8_conn_8_3 },  /* 1 */
    { effB8_conn_8_4, effB8_conn_8_5 },  /* 2 */
    { effB8_conn_8_6, effB8_conn_8_7 },  /* 3 */
    { effB8_conn_8_8, effB8_conn_8_9 },  /* 4 */
    { effB8_conn_8_10, effB8_conn_8_11 },  /* 5 */
};

const CONN effB8_conn_8_0[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6893 },
    {   16,    0,   0, 0x68A8 },
    {   32,    0,   0, 0x6897 },
    {   48,    0,   0, 0x6881 },
    {   64,    0,   0, 0x68C6 },
    {   80,    0,   0, 0x6886 },
    {   96,    0,   0, 0x68B3 },
    {  112,    0,   0, 0x6887 },
};

const CONN effB8_conn_8_2[7] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6881 },
    {   16,    0,   0, 0x68A7 },
    {   32,    0,   0, 0x68B5 },
    {   48,    0,   0, 0x68B7 },
    {   64,    0,   0, 0x68BE },
    {   80,    0,   0, 0x68B6 },
    {   96,    0,   0, 0x68AD },
};

const CONN effB8_conn_8_4[5] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x689A },
    {   16,    0,   0, 0x68B7 },
    {   32,    0,   0, 0x68A7 },
    {   48,    0,   0, 0x68AD },
    {   64,    0,   0, 0x68BA },
};

const CONN effB8_conn_8_6[11] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6912 },
    {   16,    0,   0, 0x6ADE },
    {   32,    0,   0, 0x681C },
    {   48,    0,   0, 0x6ADD },
    {   64,    0,   0, 0x6ADE },
    {   80,    0,   0, 0x681C },
    {  160,    0,   0, 0x6886 },
    {  176,    0,   0, 0x68B3 },
    {  192,    0,   0, 0x6887 },
    {  208,    0,   0, 0x6818 },
    {  224,    0,   0, 0x6AD1 },
};

const CONN effB8_conn_8_8[1] = {
    /*  nx    ny  col  chr */
    {   16,    0,   0, 0x6957 },
};

const CONN effB8_conn_8_10[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69BD },
    {   16,    0,   0, 0x6902 },
    {   32,    0,   0, 0x6818 },
    {   48,    0,   0, 0x6919 },
    {   64,    0,   0, 0x682C },
    {   80,    0,   0, 0x6ADF },
    {   96,    0,   0, 0x6827 },
    {  112,    0,   0, 0x6812 },
    {  160,    0,   0, 0x69F2 },
    {  176,    0,   0, 0x6AC5 },
    {  192,    0,   0, 0x680C },
    {  208,    0,   0, 0x6828 },
};

const u16 effB8_conn_8_1[3] = {
    1,  /* characters */
    0x6880,
    8,  /* cells */
};

const u16 effB8_conn_8_3[3] = {
    1,  /* characters */
    0x6880,
    7,  /* cells */
};

const u16 effB8_conn_8_5[3] = {
    1,  /* characters */
    0x6880,
    5,  /* cells */
};

const u16 effB8_conn_8_7[6] = {
    4,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6A80,
    11,  /* cells */
};

const u16 effB8_conn_8_9[3] = {
    1,  /* characters */
    0x6900,
    1,  /* cells */
};

const u16 effB8_conn_8_11[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A80,
    12,  /* cells */
};

extern const CONN effB8_conn_9_0[], effB8_conn_9_2[], effB8_conn_9_4[], effB8_conn_9_6[], effB8_conn_9_8[],
                  effB8_conn_9_10[];
extern const u16 effB8_conn_9_1[], effB8_conn_9_3[], effB8_conn_9_5[], effB8_conn_9_7[], effB8_conn_9_9[],
                 effB8_conn_9_11[];

/* effB8_conn_tbl[9]: Oro's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_9[6] = {
    { effB8_conn_9_0, effB8_conn_9_1 },  /* 0 */
    { effB8_conn_9_2, effB8_conn_9_3 },  /* 1 */
    { effB8_conn_9_4, effB8_conn_9_5 },  /* 2 */
    { effB8_conn_9_6, effB8_conn_9_7 },  /* 3 */
    { effB8_conn_9_8, effB8_conn_9_9 },  /* 4 */
    { effB8_conn_9_10, effB8_conn_9_11 },  /* 5 */
};

const CONN effB8_conn_9_0[5] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6886 },
    {   16,    0,   0, 0x688B },
    {   32,    0,   0, 0x68AD },
    {   48,    0,   0, 0x68A7 },
    {   64,    0,   0, 0x6886 },
};

const CONN effB8_conn_9_2[6] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A23 },
    {   16,    0,   0, 0x6A18 },
    {  144,    0,   0, 0x681D },
    {  160,    0,   0, 0x6802 },
    {  176,    0,   0, 0x6845 },
    {  192,    0,   0, 0x6806 },
};

const CONN effB8_conn_9_4[3] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A65 },
    {   16,    0,   0, 0x6A6D },
    {   32,    0,   0, 0x6A02 },
};

const CONN effB8_conn_9_6[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x691A },
    {   16,    0,   0, 0x69AD },
    {   32,    0,   0, 0x6924 },
    {   48,    0,   0, 0x6A69 },
    {   64,    0,   0, 0x6837 },
    {  160,    0,   0, 0x6A9F },
    {  176,    0,   0, 0x6919 },
    {  192,    0,   0, 0x684B },
    {  208,    0,   0, 0x6AE0 },
    {  224,    0,   0, 0x6806 },
    {  240,    0,   0, 0x6811 },
    {    0,  -16,   0, 0x6808 },
    {   16,  -16,   0, 0x6828 },
};

const CONN effB8_conn_9_8[14] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AE1 },
    {   16,    0,   0, 0x6AE2 },
    {   32,    0,   0, 0x684B },
    {   48,    0,   0, 0x6910 },
    {   64,    0,   0, 0x684F },
    {   80,    0,   0, 0x691A },
    {   96,    0,   0, 0x69AD },
    {  112,    0,   0, 0x6801 },
    {  128,    0,   0, 0x690F },
    {  160,    0,   0, 0x682C },
    {  176,    0,   0, 0x6ACF },
    {  192,    0,   0, 0x6810 },
    {  208,    0,   0, 0x6906 },
    {  224,    0,   0, 0x680C },
};

const CONN effB8_conn_9_10[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6A6D },
    {   16,    0,   0, 0x6A02 },
    {   32,    0,   0, 0x6818 },
    {   48,    0,   0, 0x6AE3 },
    {   64,    0,   0, 0x69C2 },
    {  160,    0,   0, 0x6AF5 },
    {  176,    0,   0, 0x6A96 },
    {  192,    0,   0, 0x6919 },
    {  208,    0,   0, 0x682C },
    {  224,    0,   0, 0x6A6E },
    {  240,    0,   0, 0x6AE4 },
    {    0,  -16,   0, 0x6839 },
};

const u16 effB8_conn_9_1[3] = {
    1,  /* characters */
    0x6880,
    5,  /* cells */
};

const u16 effB8_conn_9_3[4] = {
    2,  /* characters */
    0x6800, 0x6A00,
    6,  /* cells */
};

const u16 effB8_conn_9_5[3] = {
    1,  /* characters */
    0x6A00,
    3,  /* cells */
};

const u16 effB8_conn_9_7[7] = {
    5,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A00, 0x6A80,
    13,  /* cells */
};

const u16 effB8_conn_9_9[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A80,
    14,  /* cells */
};

const u16 effB8_conn_9_11[7] = {
    5,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A00, 0x6A80,
    12,  /* cells */
};

extern const CONN effB8_conn_10_0[], effB8_conn_10_2[], effB8_conn_10_4[], effB8_conn_10_6[], effB8_conn_10_8[],
                  effB8_conn_10_10[];
extern const u16 effB8_conn_10_1[], effB8_conn_10_3[], effB8_conn_10_5[], effB8_conn_10_7[], effB8_conn_10_9[],
                 effB8_conn_10_11[];

/* effB8_conn_tbl[10]: Yang's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_10[6] = {
    { effB8_conn_10_0, effB8_conn_10_1 },  /* 0 */
    { effB8_conn_10_2, effB8_conn_10_3 },  /* 1 */
    { effB8_conn_10_4, effB8_conn_10_5 },  /* 2 */
    { effB8_conn_10_6, effB8_conn_10_7 },  /* 3 */
    { effB8_conn_10_8, effB8_conn_10_9 },  /* 4 */
    { effB8_conn_10_10, effB8_conn_10_11 },  /* 5 */
};

const CONN effB8_conn_10_0[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6910 },
    {   16,    0,   0, 0x6AEA },
    {   32,    0,   0, 0x6AEB },
    {   48,    0,   0, 0x6A80 },
};

const CONN effB8_conn_10_2[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AEC },
    {   16,    0,   0, 0x6A94 },
    {   32,    0,   0, 0x6889 },
    {   48,    0,   0, 0x6882 },
};

const CONN effB8_conn_10_4[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6ACA },
    {   16,    0,   0, 0x6AED },
    {   32,    0,   0, 0x6AEE },
    {   48,    0,   0, 0x694D },
};

const CONN effB8_conn_10_6[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6ACE },
    {   16,    0,   0, 0x6A17 },
    {   32,    0,   0, 0x6815 },
    {   48,    0,   0, 0x6812 },
    {   64,    0,   0, 0x6A80 },
    {   80,    0,   0, 0x6827 },
    {   96,    0,   0, 0x6815 },
    {  112,    0,   0, 0x6825 },
    {  128,    0,   0, 0x6828 },
    {  160,    0,   0, 0x6AEF },
    {  176,    0,   0, 0x6AC6 },
    {  192,    0,   0, 0x6A96 },
    {  208,    0,   0, 0x6839 },
};

const CONN effB8_conn_10_8[12] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69BD },
    {   16,    0,   0, 0x6806 },
    {   32,    0,   0, 0x6814 },
    {   48,    0,   0, 0x690B },
    {   64,    0,   0, 0x69DE },
    {   80,    0,   0, 0x6919 },
    {   96,    0,   0, 0x682C },
    {  112,    0,   0, 0x694F },
    {  128,    0,   0, 0x6811 },
    {  160,    0,   0, 0x69C1 },
    {  176,    0,   0, 0x69D1 },
    {  192,    0,   0, 0x6827 },
};

const CONN effB8_conn_10_10[1] = {
    /*  nx    ny  col  chr */
    {   16,    0,   0, 0x6957 },
};

const u16 effB8_conn_10_1[4] = {
    2,  /* characters */
    0x6900, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_10_3[4] = {
    2,  /* characters */
    0x6880, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_10_5[4] = {
    2,  /* characters */
    0x6900, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_10_7[5] = {
    3,  /* characters */
    0x6800, 0x6A00, 0x6A80,
    13,  /* cells */
};

const u16 effB8_conn_10_9[5] = {
    3,  /* characters */
    0x6800, 0x6900, 0x6980,
    12,  /* cells */
};

const u16 effB8_conn_10_11[4] = {
    1,  /* characters */
    0x6900,
    1,  /* cells */
    0x4444,
};

extern const CONN effB8_conn_11_0[], effB8_conn_11_2[], effB8_conn_11_4[], effB8_conn_11_6[], effB8_conn_11_8[],
                  effB8_conn_11_10[];
extern const u16 effB8_conn_11_1[], effB8_conn_11_3[], effB8_conn_11_5[], effB8_conn_11_7[], effB8_conn_11_9[],
                 effB8_conn_11_11[];

/* effB8_conn_tbl[11]: Ken's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_11[6] = {
    { effB8_conn_11_0, effB8_conn_11_1 },  /* 0 */
    { effB8_conn_11_2, effB8_conn_11_3 },  /* 1 */
    { effB8_conn_11_4, effB8_conn_11_5 },  /* 2 */
    { effB8_conn_11_6, effB8_conn_11_7 },  /* 3 */
    { effB8_conn_11_8, effB8_conn_11_9 },  /* 4 */
    { effB8_conn_11_10, effB8_conn_11_11 },  /* 5 */
};

const CONN effB8_conn_11_0[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69CD },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6A8F },
    {   48,    0,   0, 0x690B },
};

const CONN effB8_conn_11_2[3] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69C4 },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6909 },
};

const CONN effB8_conn_11_4[3] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AF6 },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6909 },
};

const CONN effB8_conn_11_6[16] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69CD },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6909 },
    {   48,    0,   0, 0x682C },
    {   64,    0,   0, 0x6AC6 },
    {   80,    0,   0, 0x6A3F },
    {   96,    0,   0, 0x680B },
    {  112,    0,   0, 0x6812 },
    {  160,    0,   0, 0x6905 },
    {  176,    0,   0, 0x6827 },
    {  192,    0,   0, 0x6906 },
    {  208,    0,   0, 0x680C },
    {  224,    0,   0, 0x693A },
    {  240,    0,   0, 0x69CC },
    {    0,  -16,   0, 0x6818 },
    {   16,  -16,   0, 0x690E },
};

const CONN effB8_conn_11_8[16] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69CD },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6818 },
    {   48,    0,   0, 0x692D },
    {   64,    0,   0, 0x6A97 },
    {   80,    0,   0, 0x682C },
    {   96,    0,   0, 0x69F2 },
    {  112,    0,   0, 0x698B },
    {  160,    0,   0, 0x6919 },
    {  176,    0,   0, 0x6815 },
    {  192,    0,   0, 0x6837 },
    {  208,    0,   0, 0x690B },
    {  224,    0,   0, 0x69DE },
    {  240,    0,   0, 0x6919 },
    {    0,  -16,   0, 0x6AFB },
    {   16,  -16,   0, 0x6AFC },
};

const CONN effB8_conn_11_10[15] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6924 },
    {   16,    0,   0, 0x6ACF },
    {   32,    0,   0, 0x6818 },
    {   48,    0,   0, 0x6881 },
    {   64,    0,   0, 0x68AD },
    {   80,    0,   0, 0x68CC },
    {   96,    0,   0, 0x6887 },
    {  112,    0,   0, 0x6893 },
    {  128,    0,   0, 0x6815 },
    {  160,    0,   0, 0x6961 },
    {  176,    0,   0, 0x6A96 },
    {  192,    0,   0, 0x6919 },
    {  208,    0,   0, 0x682C },
    {  224,    0,   0, 0x6969 },
    {  240,    0,   0, 0x6AA9 },
};

const u16 effB8_conn_11_1[5] = {
    3,  /* characters */
    0x6900, 0x6980, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_11_3[4] = {
    2,  /* characters */
    0x6900, 0x6980,
    3,  /* cells */
};

const u16 effB8_conn_11_5[5] = {
    3,  /* characters */
    0x6900, 0x6980, 0x6A80,
    3,  /* cells */
};

const u16 effB8_conn_11_7[7] = {
    5,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A00, 0x6A80,
    16,  /* cells */
};

const u16 effB8_conn_11_9[6] = {
    4,  /* characters */
    0x6800, 0x6900, 0x6980, 0x6A80,
    16,  /* cells */
};

const u16 effB8_conn_11_11[7] = {
    4,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6A80,
    15,  /* cells */
    0x8811,
};

extern const CONN effB8_conn_12_0[], effB8_conn_12_2[], effB8_conn_12_4[], effB8_conn_12_6[], effB8_conn_12_8[],
                  effB8_conn_12_10[];
extern const u16 effB8_conn_12_1[], effB8_conn_12_3[], effB8_conn_12_5[], effB8_conn_12_7[], effB8_conn_12_9[],
                 effB8_conn_12_11[];

/* effB8_conn_tbl[12]: Sean's cells connected to the win messages */
const EFFB8_MESSAGE effB8_conn_12[6] = {
    { effB8_conn_12_0, effB8_conn_12_1 },  /* 0 */
    { effB8_conn_12_2, effB8_conn_12_3 },  /* 1 */
    { effB8_conn_12_4, effB8_conn_12_5 },  /* 2 */
    { effB8_conn_12_6, effB8_conn_12_7 },  /* 3 */
    { effB8_conn_12_8, effB8_conn_12_9 },  /* 4 */
    { effB8_conn_12_10, effB8_conn_12_11 },  /* 5 */
};

const CONN effB8_conn_12_0[4] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x69CD },
    {   16,    0,   0, 0x69CE },
    {   32,    0,   0, 0x6A8F },
    {   48,    0,   0, 0x690B },
};

const CONN effB8_conn_12_2[5] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6AF7 },
    {   16,    0,   0, 0x6AF8 },
    {   32,    0,   0, 0x6A92 },
    {   48,    0,   0, 0x69D8 },
    {   64,    0,   0, 0x69DD },
};

const CONN effB8_conn_12_4[5] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x697B },
    {   16,    0,   0, 0x6A17 },
    {   32,    0,   0, 0x6907 },
    {   48,    0,   0, 0x6908 },
    {   64,    0,   0, 0x6909 },
};

const CONN effB8_conn_12_6[8] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x6888 },
    {   16,    0,   0, 0x68AD },
    {   32,    0,   0, 0x6982 },
    {   48,    0,   0, 0x6987 },
    {   64,    0,   0, 0x6818 },
    {   80,    0,   0, 0x693A },
    {   96,    0,   0, 0x69CC },
    {  112,    0,   0, 0x690E },
};

const CONN effB8_conn_12_8[13] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x693F },
    {   16,    0,   0, 0x69F5 },
    {   32,    0,   0, 0x69AD },
    {   48,    0,   0, 0x6801 },
    {   64,    0,   0, 0x6805 },
    {   80,    0,   0, 0x6826 },
    {   96,    0,   0, 0x6910 },
    {  112,    0,   0, 0x684E },
    {  128,    0,   0, 0x69AA },
    {  144,    0,   0, 0x681F },
    {  160,    0,   0, 0x6998 },
    {  176,    0,   0, 0x69D8 },
    {  192,    0,   0, 0x69DD },
};

const CONN effB8_conn_12_10[9] = {
    /*  nx    ny  col  chr */
    {    0,    0,   0, 0x68A7 },
    {   16,    0,   0, 0x68B5 },
    {   32,    0,   0, 0x6882 },
    {   48,    0,   0, 0x6982 },
    {   64,    0,   0, 0x6987 },
    {   80,    0,   0, 0x6818 },
    {   96,    0,   0, 0x693A },
    {  112,    0,   0, 0x69CC },
    {  128,    0,   0, 0x690E },
};

const u16 effB8_conn_12_1[5] = {
    3,  /* characters */
    0x6900, 0x6980, 0x6A80,
    4,  /* cells */
};

const u16 effB8_conn_12_3[4] = {
    2,  /* characters */
    0x6980, 0x6A80,
    5,  /* cells */
};

const u16 effB8_conn_12_5[4] = {
    2,  /* characters */
    0x6900, 0x6A00,
    5,  /* cells */
};

const u16 effB8_conn_12_7[6] = {
    4,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980,
    8,  /* cells */
};

const u16 effB8_conn_12_9[5] = {
    3,  /* characters */
    0x6800, 0x6900, 0x6980,
    13,  /* cells */
};

const u16 effB8_conn_12_11[6] = {
    4,  /* characters */
    0x6800, 0x6880, 0x6900, 0x6980,
    9,  /* cells */
};
