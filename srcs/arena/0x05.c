#include "arena.h"

void    x05(t_arena *arena, t_process *process)
{
    int    val1;
    int    val2;

    val1 = (int)read_reg(process, arena->args->val[0]);
    val2 = (int)read_reg(process, arena->args->val[1]);
    write_uint_to_reg(process, (uint)(val1 - val2), arena->args->val[2]);
    process->carry = (val1 - val2 == 0);
    printf("0x05\n");
}