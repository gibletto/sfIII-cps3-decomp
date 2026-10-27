/*
 * EXCHANGE.C  tables read by HITCHECK.c: the combo damage reduction (cal_combo_waribiki)
 *
 * Its tables lie between code objects in P, so units.txt builds it with incode (its constant data in a section of
 * the code's name).
 */

#include "types.h"
#include "structs.h"

extern const POWER* const exchange_pow_pl03_sa3[];
extern const POWER* const exchange_pow[];
extern const POWER exchange_pow_data_0[];
extern const POWER exchange_pow_data_1[];
extern const POWER exchange_pow_data_2[];
extern const KOATT* const exchange_koa[];
extern const KOATT exchange_koa_data_0[];
extern const KOATT exchange_koa_data_1[];
extern const KOATT exchange_koa_data_2[];
extern const KOATT exchange_koa_data_3[];
extern const KOATT exchange_koa_data_4[];
extern const KOATT exchange_koa_data_5[];
extern const KOATT exchange_koa_data_6[];
extern const KOATT exchange_koa_data_7[];
extern const KOATT exchange_koa_data_8[];
extern const KOATT exchange_koa_data_9[];

const POWER* const exchange_pow_pl03_sa3[40] = {
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
    exchange_pow_data_2, exchange_pow_data_2,
};

const POWER* const exchange_pow[40] = {
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_1, exchange_pow_data_1,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
    exchange_pow_data_0, exchange_pow_data_0,
};

const POWER exchange_pow_data_0[2] = {
    {
        {
            32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
            16, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8,
        },
    },
    {
        {
            32, 31, 30, 28, 26, 23, 20, 16, 16, 16, 15, 15, 15, 14, 14, 14,
            13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 10, 9, 9, 9, 8,
        },
    },
};

const POWER exchange_pow_data_1[1] = {
    {
        {
            32, 30, 28, 26, 24, 23, 22, 21, 20, 19, 18, 17, 16, 16, 15, 15,
            14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7,
        },
    },
};

const POWER exchange_pow_data_2[1] = {
    {
        {
            32, 31, 30, 28, 26, 24, 21, 18, 15, 13, 11, 10, 9, 8, 7, 6,
            5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        },
    },
};

const KOATT* const exchange_koa[40] = {
    exchange_koa_data_0, exchange_koa_data_1,
    exchange_koa_data_2, exchange_koa_data_2,
    exchange_koa_data_3, exchange_koa_data_3,
    exchange_koa_data_3, exchange_koa_data_3,
    exchange_koa_data_4, exchange_koa_data_4,
    exchange_koa_data_4, exchange_koa_data_4,
    exchange_koa_data_5, exchange_koa_data_5,
    exchange_koa_data_5, exchange_koa_data_5,
    exchange_koa_data_6, exchange_koa_data_6,
    exchange_koa_data_6, exchange_koa_data_6,
    exchange_koa_data_7, exchange_koa_data_7,
    exchange_koa_data_7, exchange_koa_data_7,
    exchange_koa_data_8, exchange_koa_data_8,
    exchange_koa_data_8, exchange_koa_data_8,
    exchange_koa_data_9, exchange_koa_data_9,
    exchange_koa_data_9, exchange_koa_data_9,
    exchange_koa_data_0, exchange_koa_data_1,
    exchange_koa_data_2, exchange_koa_data_2,
    exchange_koa_data_0, exchange_koa_data_1,
    exchange_koa_data_2, exchange_koa_data_2,
};

const KOATT exchange_koa_data_0[1] = {
    {
        {
            { 2048, 256, 256, 256 }, { 512, 512, 512, 512 },
            { 256, 256, 256, 256 }, { 768, 768, 768, 768 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 1536, 0, 0, 0 }, { 1536, 0, 0, 0 },
        },
    },
};

const KOATT exchange_koa_data_1[1] = {
    {
        {
            { 256, 1792, 256, 256 }, { 512, 512, 512, 512 },
            { 256, 256, 256, 256 }, { 768, 768, 768, 768 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 0, 1280, 0, 0 }, { 0, 1280, 0, 0 },
        },
    },
};

const KOATT exchange_koa_data_2[1] = {
    {
        {
            { 256, 256, 1536, 1536 }, { 512, 512, 512, 512 },
            { 256, 256, 256, 256 }, { 768, 768, 768, 768 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 0, 0, 1024, 1024 }, { 0, 0, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_3[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 256, 256, 256, 256 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_4[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_5[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 768, 768, 768, 768 },
            { 512, 512, 512, 512 }, { 256, 256, 256, 256 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_6[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 1024, 1024, 1024, 1024 },
            { 768, 768, 768, 768 }, { 1280, 1280, 1280, 1280 },
            { 256, 256, 256, 256 }, { 512, 512, 512, 512 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_7[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 1024, 1024, 1024, 1024 },
            { 768, 768, 768, 768 }, { 1280, 1280, 1280, 1280 },
            { 512, 512, 512, 512 }, { 256, 256, 256, 256 },
            { 1024, 1024, 1024, 1024 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_8[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 1024, 1024, 1024, 1024 },
            { 768, 768, 768, 768 }, { 1280, 1280, 1280, 1280 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 256, 256, 256, 256 }, { 1280, 1280, 1280, 1280 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};

const KOATT exchange_koa_data_9[1] = {
    {
        {
            { 512, 768, 1024, 1024 }, { 1024, 1024, 1024, 1024 },
            { 768, 768, 768, 768 }, { 1280, 1280, 1280, 1280 },
            { 512, 512, 512, 512 }, { 768, 768, 768, 768 },
            { 1024, 1024, 1024, 1024 }, { 256, 256, 256, 256 },
            { 512, 768, 1024, 1024 }, { 512, 768, 1024, 1024 },
        },
    },
};
