#ifndef BG_SUB_H
#define BG_SUB_H

#include "structs.h"

void Bg_Family_Set_2(void);
void ake_Family_Set(void);
void bg_pos_hosei_sub3(s32 bg);
void ake_cell_write(s8 map, s32 ofs, s32 cell, u32 src);
void akebono_cell_fill(void);
void bg_scr_clear_all(void);
void compel_bg_init_position(void);
void bg_work_clear(void);
void blit_16x16_xflip(u16* src, s16 code, u16* dst, s16 attr);
void blit_16x16_tile(u16* src, s16 code, u16* dst, s16 attr);
void bg_cell_write(s16 bg, s32 ofs, s32 cell, u32 src, s32 u5, s16 attr);
void bg_cell_write_xyflip(u16 bg, s32 ofs, s32 cell, u32 src, u16 u5, s16 attr);
void blit_8x16_tile(u16* src, s16 code, u16* dst, s16 attr);
void bg_scr_write(void);
s16 get_center_position(void);
void akebono_scr_write(void);
void bg_etc_scr_write(s16 type);
void bg_pos_hosei_sub2(s32 bg_no);
s32 get_height_position(void);
void bg_pos_hosei2(void);

#endif
