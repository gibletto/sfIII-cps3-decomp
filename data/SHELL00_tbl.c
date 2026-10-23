/*
 * SHELL00_TBL.C  tables read by SHELL00.c: the routine table of the shell patterns
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Shell00_Tbl[])(PLW*);
extern void Shell00_0000();
extern void Shell00_0001();
extern void Shell00_0002();
extern void Shell00_0003();
extern void Shell00_0004();
extern void Shell00_0005();
extern void Shell00_0006();
extern void Shell00_0007();
extern void Shell00_0008();
extern void Shell00_0009();
extern void Shell00_0010();

void (*const Shell00_Tbl[11])(PLW*) = {
    Shell00_0000, Shell00_0001, Shell00_0002, Shell00_0003, Shell00_0004, Shell00_0005, Shell00_0006, Shell00_0007,
    Shell00_0008, Shell00_0009, Shell00_0010,
};
