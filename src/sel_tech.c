/*
 * SEL_TECH.C  "SELECT TECHNIQUE" screen
 *
 * A three-step screen run through its own step counter and returning Sel_Tech_X: the first step clears text
 * page 0 and prints SELECT TECHNIQUE at the operator text position, the second waits 30 frames, and the third
 * sets Sel_Tech_X once either player presses a button. Nothing in the game calls Select_Technique.
 */

#include "structs.h"
#include "work.h"
#include "SYS_sub.h"
#include "demo00.h"
#include "textsound.h"

s16 Select_Technique(void);
void Select_Technique_1st(void);
void Select_Technique_2nd(void);
void Select_Technique_3rd(void);

extern s16 Sel_Tech_No;      /* provisional name: the screen's step */
extern s16 Sel_Tech_Timer;   /* provisional name */
extern s16 Sel_Tech_X;       /* provisional name: set once a button is pressed */


/* provisional name */
s16 Select_Technique(void) {
    void (*Tech_Tbl[3])() = { Select_Technique_1st, Select_Technique_2nd, Select_Technique_3rd };
    Sel_Tech_X = 0;
    Tech_Tbl[Sel_Tech_No]();
    return Sel_Tech_X;
}



/* provisional name */
void Select_Technique_1st(void) {
    s16 x;
    Sel_Tech_No++;
    Sel_Tech_Timer = 30;
    scfont_page0_fill(0, 32);
    Set_Mode_Pos(&x, 8, 16);
    tilemap_print_string_attr(x, 8, 14, "SELECT TECHNIQUE");
}



/* provisional name */
void Select_Technique_2nd(void) {
    if (--Sel_Tech_Timer == 0) {
        Sel_Tech_No++;
    }
}



/* provisional name */
void Select_Technique_3rd(void) {
    if ((p1sw_0 & 0x7F0) | (p2sw_0 & 0x7F0)) {
        Sel_Tech_X = 1;
    }
}
