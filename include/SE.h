#ifndef SE_H
#define SE_H

#include "structs.h"

void wipe_pattern_or_cols(s16 kind, s16 row);
void wipe_pattern_restore_cols(s16 kind, s16 row);
void mix_or_512(void);
void mix_put_512(void);
void wipe_pattern_set(s16 kind, s16 row, s16 mix);

#endif
