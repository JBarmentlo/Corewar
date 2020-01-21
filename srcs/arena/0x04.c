#include "arena.h"


// here we  assume values in Registers to be SIGNED
void    x04(t_arena *arena, t_process *process)
{
    int    val1;
    int    val2;

    val1 = (int)reg_read_uint(process, arena->args->val[0]);
    val2 = (int)reg_read_uint(process, arena->args->val[1]);
    reg_write_uint(process, (uint)(val1 + val2), arena->args->val[2]);
    process->carry = (val1 + val2 == 0);
    printf("0x04\n");
}