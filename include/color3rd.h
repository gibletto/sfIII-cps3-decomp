#ifndef COLOR3RD_H
#define COLOR3RD_H

#include "structs.h"

void init_color_trans_req(void);
void load_any_color_fade();
void load_any_color_attr(u16 col_no, u8 r, u8 g, u8 b);
void color_trans_dummy(void);
void load_any_color_req();
void load_player_color();

#endif
