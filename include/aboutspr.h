#ifndef ABOUTSPR_H
#define ABOUTSPR_H

#include "structs.h"

void init_char_gfx_tables(void);
void setup_kage_cells(void);
void setup_hit_mark_cells(void);
void setup_GILL_exsa_obj(void);
s32 get_cg_slot_addr();
s32 purge_char_gfx();
s32 check_cg_data();
s32 char_cell_push_block();
s32 char_cell_flip_y(WORK* wk);
s32 char_cell_unflip_y(WORK* wk);
s32 char_cell_flip_xy(WORK* wk);
s32 char_cell_unflip_xy(WORK* wk);
void count_conn_cells(WORK_Other_CONN* ewk);
s32 make_conn_cells(WORK_Other_CONN* ewk);
void release_char_cell_blocks(WORK* wk);
void push_char_sprite(WORK* wk, SPRITE_ENTRY* spr, s16 y_ofs);
s32 sort_push_request8(WORK* wk);
s16 get_kage_width();
void char_sprite_zoom_cells(WORK* wk);
s32 zoom_cell_position();
s32 get_cell_zoom();
s32 char_cell_flip_none(WORK* wk);
s32 char_cell_flip_x(WORK* wk);
void make_char_cells_n(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y);
void make_char_cells_x(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y);
void make_char_cells_y(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y);
void make_char_cells_xy(WORK* wk, CHAR_CELL* cell, CHAR_SPRITE* spr, u16 count, s16 x, s16 y);
s32 trans_char_cells(WORK* wk);
u32 get_cg_slot_no();
s32 sort_push_request4(WORK* wk);
s32 sort_push_request(WORK* wk);
void shadow_drawing(WORK* wk, s16 y_ofs);
s32 disp_seraph_cells(WORK* wk);
s32 load_char_gfx();
void all_cgps_put_back();
s32 set_conn_sprite(WORK_Other_CONN* wk);
s32 set_judge_area_sprite();
s32 sort_push_request2(WORK_Other* wk);
s32 sort_push_request3(WORK* wk);

#endif
