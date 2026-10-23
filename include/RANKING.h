#ifndef RANKING_H
#define RANKING_H

#include "structs.h"

s32 Ranking_Main(void);
void Ranking_00(void);
void Ranking_01(void);
void Ranking_01_1st(void);
void Ranking_01_4th(void);
void Ranking_01_5th(void);
void Ranking_00_1st(void);
void Ranking_Sub(void);
void Ranking_00_2nd(void);
void Ranking_00_3rd(void);
void Ranking_00_4th(void);
void Ranking_00_5th(void);
void Ranking_00_Last(void);
void Setup_grade(void);
void Setup_Name(void);
void Name_Sub(s16 name_ix);
void Setup_Face(void);
void Setup_Score_Small(void);
void Setup_Wins(void);
void Setup_Ranking_Obj(void);
void Setup_Score_Obj(void);
void Setup_Rank_Number(s16 y);
void Setup_Rank_Head_Obj(void);
void Ranking_Init(void);
void ranking_insert_present(s16 top, s16 PL_id);

#endif
