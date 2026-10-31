#ifndef CMB_WIN_H
#define CMB_WIN_H

#include "structs.h"

void sc_vram_to_ram(void);
void combo_window_all_clear(void);
void combo_message_set(s8 pl, s8 kind);
void combo_hitnum_set(s8 pl, s8 kind, u16 hits);
s16 combo_pts_set(s8 PL, u32 pts);
void combo_window_slide(s8 pl, s16 x, s16 y, s16 n);
void combo_window_erase(s8 col, s8 kind, s16 row);

#endif
