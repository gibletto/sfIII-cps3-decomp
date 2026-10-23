#ifndef TEXTSOUND_3_H
#define TEXTSOUND_3_H

#include "structs.h"

s32 memcmp(const u8* a, const u8* b, u32 n);
volatile u32* dma0_transfer_wait(u32 src, u32 dst, u32 count, u32 size);
void delay_cycles(s32 count);
s32 strlen(const char *s);

#endif
