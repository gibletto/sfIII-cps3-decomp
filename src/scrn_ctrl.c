/*
 * SCRN_CTRL.C  Screen mode, window and zoom registers
 *
 * set_screen_mode and screen_flip_offsets_set choose normal or wide screen; screen_window_regs_update
 * and zoom_regs_update write the window and zoom registers in vblank; Zoomf_Init_X/Y, Frame_Up/Down
 * and Frame_Adgjust handle screen zoom.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "cps3.h"

void Frame_Adgjust(u16 pos_x, u16 pos_y);

extern s16 flip_crt_ofs_x;
extern s16 flip_crt_ofs_y;

#define WINDOW_ROW(m) ((const s16*)((const u8*)screen_window_tbl + (u8)((m) * sizeof(screen_window_tbl[0]))))


s8 Monitor_Flip_Old = 0;


/* provisional name */
void screen_flip_offsets_set(void) {
    const s16* p;
    zoom_req_flag = 1;
    if (Monitor_Flip) {
        p = screen_flip_ofs_tbl[screen_mode];
        flip_obj_ofs_x = p[0];
        flip_obj_ofs_y = p[1];
        flip_crt_ofs_x = p[2];
        flip_crt_ofs_y = p[3];
        flip_scr_ofs_x = p[4];
        flip_scr_ofs_y = p[5];
        flip_zoom_ofs_x = p[6];
        flip_zoom_ofs_y = p[7];
    } else {
        flip_obj_ofs_x = 0;
        flip_obj_ofs_y = 0;
        flip_crt_ofs_x = 0;
        flip_crt_ofs_y = 0;
        flip_scr_ofs_x = 0;
        flip_scr_ofs_y = 0;
        flip_zoom_ofs_x = 0;
        flip_zoom_ofs_y = 0;
    }
}



/* provisional name */
void set_screen_mode(mode)
s32 mode;
{
    window_req_flag = 1;
    screen_mode = mode;
    screen_base_x = screen_origin_tbl[mode][0];
    screen_base_y = screen_origin_tbl[mode][1];
    screen_window[0].l = WINDOW_ROW(mode)[0];
    screen_window[0].t = WINDOW_ROW(mode)[1];
    screen_window[0].r = WINDOW_ROW(mode)[2];
    screen_window[0].b = WINDOW_ROW(mode)[3];
    screen_window[1].l = WINDOW_ROW(mode)[4];
    screen_window[1].t = WINDOW_ROW(mode)[5];
    screen_window[1].r = WINDOW_ROW(mode)[6];
    screen_window[1].b = WINDOW_ROW(mode)[7];
    *(s16*)&screen_disp_ctrl = WINDOW_ROW(mode)[8];
    Monitor_Flip_Old = Monitor_Flip;
    screen_flip_offsets_set();
}



static void screen_mode_disp(s32 mode) {}

/* provisional name */
void screen_window_regs_update(void) {
    u16 ctrl;
    u16 t;
    if (Monitor_Flip != Monitor_Flip_Old) {
        Monitor_Flip_Old = Monitor_Flip;
        screen_flip_offsets_set();
    } else {
        if (window_req_flag == 0) {
            return;
        }
        window_req_flag = 0;
    }
    *(u16*)(VIDEO_REG + 0x60) = screen_window[0].l;
    *(u16*)(VIDEO_REG + 0x62) = screen_window[0].t;
    *(u16*)(VIDEO_REG + 0x64) = screen_window[0].r;
    *(u16*)(VIDEO_REG + 0x66) = screen_window[0].b;
    *(u16*)(VIDEO_REG + 0x70) = screen_window[1].l;
    *(u16*)(VIDEO_REG + 0x72) = screen_window[1].t;
    *(u16*)(VIDEO_REG + 0x74) = screen_window[1].r;
    *(u16*)(VIDEO_REG + 0x76) = screen_window[1].b;
    screen_mode_disp(screen_mode);
    ctrl = screen_disp_ctrl;
    if (Monitor_Flip) {
        *(u16*)(VIDEO_REG + 0x80) = ctrl | 24;
    } else {
        *(u16*)(VIDEO_REG + 0x80) = ctrl;
    }
    t = screen_window[0].l;
    *(u16*)SS_REG = t;
    *(u16*)(SS_REG + 0x2) = screen_disp_reg_tbl[screen_mode][0];
    *(u16*)(SS_REG + 0x4) = screen_disp_reg_tbl[screen_mode][1];
    *(u16*)(SS_REG + 0x6) = screen_disp_reg_tbl[screen_mode][2];
    *(u16*)(SS_REG + 0x8) = screen_disp_reg_tbl[screen_mode][3];
    t = screen_window[0].b;
    *(u16*)(SS_REG + 0xA) = t;
    *(u16*)(SS_REG + 0xC) = t >> 8;
    t = screen_window[1].l;
    *(u16*)(SS_REG + 0x12) = t;
    t = screen_window[1].t;
    *(u16*)(SS_REG + 0x14) = t;
    *(u16*)(SS_REG + 0x16) = t >> 8;
    t = screen_window[1].r;
    t = t + 2;
    *(u16*)(SS_REG + 0x18) = t;
    *(u16*)(SS_REG + 0x1A) = t >> 8;
    t = screen_window[1].b;
    *(u16*)(SS_REG + 0x1C) = t;
    *(u16*)(SS_REG + 0x1E) = t >> 8;
    t = screen_disp_ctrl & 7;
    *(u16*)(SS_REG + 0x26) = t;
    if (Monitor_Flip) {
        *(u16*)(SS_REG + 0x28) = 3;
    } else {
        *(u16*)(SS_REG + 0x28) = 0;
    }
}



/* provisional name */
void Zoomf_Init(void) {
    zoom_frame[0].pos = 0;
    zoom_frame[0].size = 0;
    zoom_frame[0].mask = 1023;
    zoom_frame[0].zoom = 64;
    zoom_frame[1].pos = 0;
    zoom_frame[1].size = 0;
    zoom_frame[1].mask = 1023;
    zoom_frame[1].zoom = 64;
    zoom_adj_x = 0;
    zoom_adj_y = 0;
    zoom_req_flag = 1;
    if (Monitor_Flip) {
        screen_flip_offsets_set();
    }
}



/* provisional name */
void Zoomf_Init_X(void) {
    zoom_frame[0].pos = 0;
    zoom_frame[0].size = 0;
    zoom_frame[0].mask = 0x3FF;
    zoom_frame[0].zoom = 64;
    zoom_adj_x = 0;
    zoom_req_flag = 1;
    if (Monitor_Flip) {
        screen_flip_offsets_set();
    }
}



/* provisional name */
void Zoomf_Init_Y(void) {
    zoom_frame[1].pos = 0;
    zoom_frame[1].size = 0;
    zoom_frame[1].mask = 0x3FF;
    zoom_frame[1].zoom = 64;
    zoom_adj_y = 0;
    zoom_req_flag = 1;
    if (Monitor_Flip) {
        screen_flip_offsets_set();
    }
}



/* Zooms the frame in. */
s32 Frame_Up(u16 x, u16 y, u16 add_x, u16 add_y) {
    zoom_frame[0].zoom -= add_x;
    zoom_frame[1].zoom -= add_y;
    Frame_Adgjust(x, y);
    zoom_req_flag = 1;
}



/* Zooms the frame out. */
s32 Frame_Down(u16 x, u16 y, u16 add_x, u16 add_y) {
    zoom_frame[0].zoom += add_x;
    zoom_frame[1].zoom += add_y;
    Frame_Adgjust(x, y);
    zoom_req_flag = 1;
}



/* Recomputes the zoom frame offsets, keeping a vertical offset of -32 at -31. */
void Frame_Adgjust(u16 pos_x, u16 pos_y) {
    u16 buff;
    if (Monitor_Flip) {
        pos_y = 0xD0 - pos_y;
        flip_zoom_ofs_x = 0x80;
    }
    if (zoom_frame[0].zoom >= 0x40) {
        buff = zoom_frame[0].zoom;
        buff -= 0x40;
        buff *= pos_x;
        buff >>= 6;
        buff &= 0x1FF;
        zoom_adj_x = -buff;
        if (Monitor_Flip) {
            flip_zoom_ofs_x = 0x80 - buff * 2;
        }
    } else {
        buff = 0x40;
        buff -= zoom_frame[0].zoom;
        buff *= pos_x;
        buff >>= 6;
        buff &= 0x1FF;
        if (Monitor_Flip) {
            zoom_adj_x = -buff;
        } else {
            zoom_adj_x = buff;
        }
    }
    if (zoom_frame[1].zoom >= 0x40) {
        buff = zoom_frame[1].zoom;
        buff -= 0x40;
        buff *= pos_y + 0x21;
        buff >>= 6;
        buff &= 0x1FF;
        if (Monitor_Flip == 0) {
            zoom_adj_y = -buff;
        } else {
            zoom_adj_y = buff;
        }
        if (zoom_adj_y == -0x20) {
            zoom_adj_y = zoom_adj_y + 1;
        }
    } else {
        buff = 0x40;
        buff -= zoom_frame[1].zoom;
        buff *= pos_y + 0x21;
        buff >>= 6;
        buff &= 0x1FF;
        if (Monitor_Flip != 0) {
            zoom_adj_y = -buff;
        } else {
            zoom_adj_y = buff;
        }
        if (zoom_adj_y == -0x20) {
            zoom_adj_y = zoom_adj_y + 1;
        }
    }
}



/* provisional name */
void zoom_regs_update(void) {
    if (zoom_req_flag) {
        zoom_req_flag = 0;
        *(s16*)(VIDEO_REG + 0x68) = (zoom_frame[0].pos + flip_zoom_ofs_x) & 0x3FF;
        *(s16*)(VIDEO_REG + 0x6A) = zoom_frame[0].size;
        *(s16*)(VIDEO_REG + 0x6C) = zoom_frame[0].mask;
        *(s16*)(VIDEO_REG + 0x6E) = zoom_frame[0].zoom;
        *(s16*)(VIDEO_REG + 0x78) = (zoom_frame[1].pos + flip_zoom_ofs_y) & 0x3FF;
        *(s16*)(VIDEO_REG + 0x7A) = zoom_frame[1].size;
        *(s16*)(VIDEO_REG + 0x7C) = zoom_frame[1].mask;
        *(s16*)(VIDEO_REG + 0x7E) = zoom_frame[1].zoom;
    }
}
