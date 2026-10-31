/*
 * SE_3.C  Sound requests for the game and its objects
 *
 * The sound routines start stage BGM (Stage_BGM, bgm_fade_in_stage), initialise sound
 * (SE_All_Off) and play effects for objects: the Se_ table handlers (Se_Myself, Se_Let,
 * Se_Let_SP, ...) and Se_Shock play a code in the character's own sound bank, panned by screen
 * position (Get_Position); Se_Myself takes the voice replacement from Check_Voice_SE. Call_Se plays a fixed code;
 * Finish_SE plays the winner's finishing voice.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "bg_sub.h"
#include "bg_sub_2.h"
#include "bg_sub_3.h"
#include "bg_sub_5.h"
#include "se_3.h"
#include "cps3.h"



/* Play the BGM of the current stage. */
void Stage_BGM(void) {
    s32 code;
    u16 ix;
    if (Demo_Sound == 0 && Demo_Flag == 0) {
        return;
    }
    if (PB_Music_Off) {
        return;
    }
    ix = bg_w.stage;
    code = BGM_Stage_Data[ix];
    if (DEBUG_DISP) {
    }
    sound_request(code);
}



/* provisional name */
void bgm_fade_in_stage(s16 x) {
    if (PB_Music_Off) {
        return;
    }
    sound_fade_in_submit(BGM_Stage_Data[bg_w.stage], 0x8000 / x);
}

void Sound_SE(Code)
s16 Code;
{
    if (Demo_Sound != 0 || Demo_Flag != 0) {
        sound_request(Code);
    }
}


/* provisional name */
void sound_bgm_fade_out(s16 speed) {
    bgm_fade_out(speed);
}

void BGM_Request(bgm_code)
s16 bgm_code;
{
    if (Demo_Sound == 0 && Demo_Flag == 0) {
        return;
    }
    if (PB_Music_Off) {
        return;
    }
    sound_reg_level_set(0, 0);
    sound_request(bgm_code);
}



void BGM_Stop(void) { bgm_stop(); }



void SE_All_Off(void) {
    s16 i;
    sound_request_pan(0x78, 0x40, 0x40, 0, 2);
    for (i = 0; i < 14; i++) {
        se_voice_stop(init_fade_voice_tbl[i]);
    }
}



void Se_Dummy(WORK_Other* ewk, u16 Code) {
}



/* The voice banks are 0x200 apart, one per player. */
void Se_Shock(WORK_Other* ewk, u16 se) {
    s16 pos;
    PLW* em;
    s32 uid;
    s16 i;
    s32 ofs;

    if (Demo_Sound != 0 || Demo_Flag != 0) {
        if (ewk->wu.work_id == 1) {
            em = (PLW*)ewk->wu.target_adrs;
            uid = ewk->wu.id;
        } else {
            em = (PLW*)((PLW*)ewk->my_master)->wu.target_adrs;
            uid = ewk->master_id;
        }
        if (em->wu.work_id == 1 && em->wu.vital_new < 0) {
            i = 0;
            ofs = 0x27;
            for (; i < 7; i++) {
                if (se == SE_Shock_Data[i]) {
                    ofs = 0;
                    break;
                }
            }
            se += ofs;
        }
        se += uid * 0x200;
        pos = Get_Position((PLW*)ewk);
        sound_request_pan(se, pos, pos, 0, 2);
    }
}



/* The voice banks are 0x200 apart, one per player. */
void Se_Myself(WORK_Other* ewk, u16 Code) {
    s32 se;
    s16 pos;

    if (Demo_Sound != 0 || Demo_Flag != 0) {
        se = Check_Voice_SE(Code);
        se += ewk->wu.id * 0x200;
        pos = Get_Position((PLW*)ewk);
        sound_request_pan(se, pos, pos, 0, 2);
    }
}



/* Plays the code itself (no Check_Voice_SE). */
void Se_Myself_Die(WORK_Other* ewk, u16 se) {
    s16 pos;

    if (Demo_Sound == 0 && Demo_Flag == 0) {
        return;
    }
    if (ewk->wu.vital_new < 0) {
        return;
    }
    se += ewk->wu.id * 0x200;
    pos = Get_Position((PLW*)ewk);
    sound_request_pan(se, pos, pos, 0, 2);
}




void Se_Let(WORK_Other* ewk, u16 Code) {
    s32 uid;
    s16 pos;

    if (Demo_Sound == 0 && Demo_Flag == 0) {
        return;
    }
    if (ewk->wu.work_id == 1) {
        uid = ewk->wu.id;
    } else {
        uid = ewk->master_id;
    }
    Code += uid * 0x200;
    pos = Get_Position((PLW*)ewk);
    sound_request_pan(Code, pos, pos, 0, 2);
}



/* The voice banks are 0x200 apart, one per player. */
void Se_Let_SP(WORK_Other* ewk, u16 Code) {
    s32 uid;
    PLW* em;
    s16 pos;

    if (Demo_Sound != 0 || Demo_Flag != 0) {
        em = (PLW*)ewk->wu.target_adrs;
        if (ewk->wu.work_id == 1) {
            uid = ewk->wu.id;
        } else {
            uid = ewk->master_id;
        }
        if (em->wu.work_id == 1 && em->wu.vital_new < 0) {
            if (Code == 0x14B) {
                Code = 0x158;
            }
            if (Code == 0x13A) {
                Code = 0x15A;
            }
        }
        Code += uid * 0x200;
        pos = Get_Position((PLW*)ewk);
        sound_request_pan(Code, pos, pos, 0, 2);
    }
}



void Call_Se(WORK_Other* ewk, u16 Code) {
    s16 pos;
    PLW* wk;
    if (Demo_Sound != 0 || Demo_Flag != 0) {
        pos = Get_Position(wk);
        sound_request_pan(Code, pos, pos, 0, 2);
    }
}

/* Sound handler: plays Code in the object's sound bank at its screen position, but stays silent while the
   object is dropping at a height of 64 or less. */
s32 Se_Term(WORK_Other* ewk, u16 Code) {
    s16 pos;

    if (Demo_Sound == 0 && Demo_Flag == 0) {
        return;
    }
    if (ewk->wu.mvxy.a[1].sp < 0 && ewk->wu.xyz[1].disp.pos <= 64) {
        return 0;
    }
    Code += ewk->wu.id * 0x200;
    pos = Get_Position((PLW*)ewk);
    sound_request_pan(Code, pos, pos, 0, 2);
}



void Finish_SE(void) {
    s32 se;
    s16 pos;

    if (Demo_Sound != 0 || Demo_Flag != 0) {
        se = Check_Finish_SE();
        if ((s16)se != -1) {
            se += plw[Winner_id].wu.id * 0x200;
            pos = Get_Position(&plw[Winner_id]);
            sound_request_pan(se, pos, pos, 0, 2);
        }
    }
}



s32 Check_Finish_SE(void) {
    s16 i;
    for (i = 0; i < 7; i++) {
        if (Finish_SE_Data[0][i] == Last_Called_SE) {
        } else {
            continue;
        }
        return Finish_SE_Data[1][i];
    }
    return -1;
}



s32 Get_Position(PLW* wk) {
    u16 pan;
    u16 center;
    pan = get_center_position();
    pan -= 0xF8;
    pan = wk->wu.position_x - pan;
    pan /= 4;
    if (pan < 0x80) {
        return pan;
    }
    center = get_center_position();
    if (center > wk->wu.xyz[0].disp.pos) {
        return 1;
    }
    return 0x7E;
}



/* provisional name */
s32 Check_Voice_SE(code)
s16 code;
{
    if (code < 0x140 || Voice_Type == 0) {
        return code;
    }
    return Voice_SE_Data[code - 0x140];
}

