/*
 * COM_SUB_TBL.C  the computer player's step helper tables
 *
 * cancel_shot_tbl gives the button bit of a cancel shot, picked by bits 4-6 of the cg effect
 * type; YAGYOU_Data holds the random term numbers YAGYOU_Check picks for the Yagyou super art;
 * Rolling_Lv_Data the lever sequence of a rolling command and the button added by power level;
 * Meoshi_Lever_Data the lever for each low cg effect type of a meoshi attack (0x8000 and
 * 0x8001 for a guard lever); and PL_Status, by the opponent's routine number, whether only the
 * shell check is made. Exit_Term_Tbl and ETC_Term_Tbl are the jump tables of the Exit_Term_*
 * and ETC_Term_* routines. Read by COM_SUB.C, the pattern step library.
 */

#include "types.h"
#include "structs.h"
#include "work.h"

#pragma section TBL

extern const u16 cancel_shot_tbl[][8];
extern const u8 YAGYOU_Data[];
extern const u16 Rolling_Lv_Data[][5];
extern const u16 Meoshi_Lever_Data[];
extern const s8 PL_Status[];
extern const Term_Tbl_t Exit_Term_Tbl[];
extern const Term_Tbl_t ETC_Term_Tbl[];
extern void ETC_Term_0000();
extern void ETC_Term_0001();
extern void ETC_Term_0002();
extern void ETC_Term_0003();
extern void ETC_Term_0004();
extern void Exit_Term_0000();
extern void Exit_Term_0001();
extern void Exit_Term_0002();
extern void Exit_Term_0003();
extern void Exit_Term_0004();
extern void Exit_Term_0005();
extern void Exit_Term_0006();
extern void Exit_Term_0007();

const u16 cancel_shot_tbl[7][8] = {
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_LP },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_LP },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_MP },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_HP },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_LK },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_MK },
    { BUTTON_LP, BUTTON_MP, BUTTON_HP, BUTTON_LK, BUTTON_MK, BUTTON_HK, 0xFFFF, BUTTON_HK },
};

const u8 YAGYOU_Data[16] = {
    0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
};

const u16 Rolling_Lv_Data[2][5] = {
    { LEVER_LEFT, LEVER_UP, LEVER_RIGHT, LEVER_DOWN, 0xFFFF },
    { BUTTON_LP | BUTTON_LK, BUTTON_MP | BUTTON_MK, BUTTON_HP | BUTTON_HK, BUTTON_SHOTS, 0xFFFF },
};

const u16 Meoshi_Lever_Data[16] = {
    0, 1, 2, 0, 0x8000, 0, 0, 0,
    0x8001, 0, 0, 0, 0, 0, 0, 0,
};

const s8 PL_Status[12] = {
    1, 0, 0, 0, 1, 1, 0, 0, 0, 0, -117, 1,
};

const Term_Tbl_t Exit_Term_Tbl[8] = {
    (const Term_Tbl_t)Exit_Term_0000, (const Term_Tbl_t)Exit_Term_0001,
    (const Term_Tbl_t)Exit_Term_0002, (const Term_Tbl_t)Exit_Term_0003,
    (const Term_Tbl_t)Exit_Term_0004, (const Term_Tbl_t)Exit_Term_0005,
    (const Term_Tbl_t)Exit_Term_0006, (const Term_Tbl_t)Exit_Term_0007,
};

const Term_Tbl_t ETC_Term_Tbl[5] = {
    (const Term_Tbl_t)ETC_Term_0000, (const Term_Tbl_t)ETC_Term_0001,
    (const Term_Tbl_t)ETC_Term_0002, (const Term_Tbl_t)ETC_Term_0003,
    (const Term_Tbl_t)ETC_Term_0004,
};
