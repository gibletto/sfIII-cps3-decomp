#ifndef N_INPUT_H
#define N_INPUT_H

#include "structs.h"

s32 Name_Input(s16 pl_id);
void Name_Input_init(void);
s32 name_slang_check(void);
void define_name_input(void);
void ranking_state_check(void);
void ranking_name_entry(void);
void name_work_init();
void all_name_display(void);
void start_cut_check();
void Name_Input_wait(void);
void Name_Scs_Finish(void);
void Scs_char_move(void);
void Name_Input_end(void);
void Name_Scs_Input_init(void);
void Name_Input_comm(void);
void Name_Finish(void);
void Name_Scs_Input_comm(void);
void rank_display_set(s16 pl_id, s16 pos_y);
s32 Name_Input_sub(void);
s32 Scs_move_sub(void);
void current_sc_move2(void);
void Name_Scs_Input_end(void);
s32 auto_n_check();

#endif
