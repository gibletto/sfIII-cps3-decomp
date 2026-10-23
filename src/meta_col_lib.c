/*
 * meta_col_lib.c  strstr
 */

#include "structs.h"
#include "work.h"
#include "romdata.h"
#include "extern.h"
#include "textsound.h"
#include "textsound_2.h"
#include "textsound_3.h"
#include "meta_col_lib.h"
#include "cps3.h"



/* provisional name */
char* strstr(char* s, const char* sub) {
    u32 sublen = strlen(sub);
    s32 n = strlen(s) - sublen + 1;
    u32 i;
    if (n > 0 && sublen > 0) {
            for (i = 0; i < n; i++) {
                if (memcmp((const u8*)(s + i), (const u8*)sub, sublen) == 0) {
                    return s + i;
                }
            }
        }
    return 0;
}
