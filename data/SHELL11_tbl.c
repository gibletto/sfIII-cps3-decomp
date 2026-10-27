/*
 * SHELL11_TBL.C  CPU anti-projectile pattern table 11 (Ken and the shared set)
 *
 * Shell11_Tbl lists the pattern scripts Shell11_0000 .. Shell11_0010 run when the opponent
 * fires a projectile, indexed by Pattern_Index. Read by SHELL11.C, which Com_VS_Shell in
 * COM_PL.C calls for Ken and for every character without a table of its own (Gill, Ryu, Necro,
 * Ibuki, Elena, Oro).
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
