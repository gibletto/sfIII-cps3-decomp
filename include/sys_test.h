#ifndef SYS_TEST_H
#define SYS_TEST_H

#include "structs.h"

void Bg_On_W(u16 mask);
u32 simmram_large_page_addr(void);
u32 simmram_small_page_addr(void);
void Scrn_Pos_Init(void);
void Scrn_Move_Set_R(s32 n, s16 x, s16 y);
void Scrn_X_Set_W(s32 ix, s16 x);
void Scrn_Y_Set_W();
void Scrn_Move_Add(s32 n, s32 dx, s32 dy);
void clear_scroll_layer_state_and_mask(void);
void scrn_linescroll_set_now(u16 n, void* p);
void Scrn_Renew(void);
void scrn_line_set(u16 n, s16 v);
void scroll_layers_finalize_frame(void);
void scrn_flip_set(u16 n, u16 flip);
void scrn_flip_toggle(u16 n, u16 flip);
void Bg_Off_W();
void Scrn_X_Set_R();
void Scrn_Y_Set_R();
void coin_work_init(void);
void coin_lock_release(s8 chute);
void coin_lock_set();
void coin_lock_check(s8 n, s8 coil);
s32 credit_use(s8 n);
void switch_read(s8 mode);
void ext_switch_read(void);
void coin_sw_sample(void);
s8 coin_chute_check(s8 n, s32 keep);
void coin_credit_add(s8 n, s8 m);
void coin_counter_drive(s8 n);
void scrn_linescroll_set();
void switch_work_clear(char level);
void dispenser_init(void);
void scrn_line_set_now();
void Bg_Off_R();
void Bg_On_R(u16 mask);
void switch_read_six_button(void);
void coin_sw_shift(void);

#endif
