/*
 * SCRN_WORK.C  screen work
 *
 * The screen window, zoom and flip offsets that scrn_ctrl.c keeps (section B).
 */

#include "types.h"
#include "structs.h"

SCREEN_WINDOW screen_window[2];  /* 0205E124 */
SCROLL_WINDOW zoom_frame[2];  /* 0205E134 */
volatile s16 screen_disp_ctrl;  /* 0205E144 */
s16 screen_base_x;  /* 0205E146 */
s16 screen_base_y;  /* 0205E148 */
s32 screen_mode;  /* 0205E14C */
u8 zoom_req_flag;  /* 0205E150 */
u8 window_req_flag;  /* 0205E151 */
s16 zoom_adj_x;  /* 0205E152 */
s16 zoom_adj_y;  /* 0205E154 */
u16 flip_obj_ofs_x;  /* 0205E156 */
u16 flip_obj_ofs_y;  /* 0205E158 */
s16 flip_crt_ofs_x;  /* 0205E15A */
s16 flip_crt_ofs_y;  /* 0205E15C */
s16 flip_scr_ofs_x;  /* 0205E15E */
s16 flip_scr_ofs_y;  /* 0205E160 */
s16 flip_zoom_ofs_x;  /* 0205E162 */
s16 flip_zoom_ofs_y;  /* 0205E164 */
/* after flip_zoom_ofs_y: nothing refers to it by name or address */
u8 flip_zoom_ofs_y_tail[2];  /* 0205E166 */
