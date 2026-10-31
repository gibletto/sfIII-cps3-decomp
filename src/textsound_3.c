/*
 * TEXTSOUND_3.C  memcmp and strlen
 *
 * The library helpers memcmp and strlen.
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "sound_voice.h"
#include "sound_voice_2.h"
#include "textsound_3.h"
#include "cps3.h"



s32 errno;  /* 0206CDF0 */


s32 memcmp(const u8* a, const u8* b, u32 n) {
    u32 i;
    const u8* p = a;
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (*p++ != *b++) {
            break;
        }
    }
    return p[-1] - b[-1];
}



s32 strlen(const char *s) {
    s32 n = 0;
    while (*s++ != 0) {
        n++;
    }
    return n;
}
