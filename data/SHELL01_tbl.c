/*
 * SHELL01_TBL.C  tables read by SHELL01.c: the routine table of the shell patterns
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern void (*const Shell01_Tbl[])(PLW*);
extern void Shell01_0000();
extern void Shell01_0001();
extern void Shell01_0002();
extern void Shell01_0003();
extern void Shell01_0004();
extern void Shell01_0005();
extern void Shell01_0006();
extern void Shell01_0007();
extern void Shell01_0008();
extern void Shell01_0009();

void (*const Shell01_Tbl[10])(PLW*) = {
    Shell01_0000, Shell01_0001, Shell01_0002, Shell01_0003, Shell01_0004, Shell01_0005, Shell01_0006, Shell01_0007,
    Shell01_0008, Shell01_0009,
};
