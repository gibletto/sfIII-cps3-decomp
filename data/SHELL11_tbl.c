/*
 * SHELL11_TBL.C  tables read by SHELL11.c: the routine table of the shell patterns
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Shell11_Tbl[])(PLW*);
extern void Shell11_0000();
extern void Shell11_0001();
extern void Shell11_0002();
extern void Shell11_0003();
extern void Shell11_0004();
extern void Shell11_0005();
extern void Shell11_0006();
extern void Shell11_0007();
extern void Shell11_0008();
extern void Shell11_0009();
extern void Shell11_0010();

void (*const Shell11_Tbl[11])(PLW*) = {
    Shell11_0000, Shell11_0001, Shell11_0002, Shell11_0003, Shell11_0004, Shell11_0005, Shell11_0006, Shell11_0007,
    Shell11_0008, Shell11_0009, Shell11_0010,
};
