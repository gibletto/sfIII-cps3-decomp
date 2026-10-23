#ifndef FIFO_H
#define FIFO_H

#include "structs.h"

void fifo_init();
s32 fifo_put(FIFO32* q, u32 dat);
s32 fifo_get(FIFO32* q);
void Family_Set_W();
void Family_Add_W();
void Family_Init(void);
void Family_Set_R();

#endif
