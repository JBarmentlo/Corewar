#include "arena.h"

void    x03(t_arena *arena, t_process *process)
{
    uint    val;

    val = reg_read_uint(process, arena->args->val[0]);
    if (arena->args->type[1] == T_REG)
    {
        reg_write_uint(process, val, arena->args->val[1]);
    }
    else
    {
        mem_write_uint(arena, process->PC + (arena->args->val[1] % IDX_MOD), val);
		mem_write_color(arena, process->PC + (arena->args->val[1] % IDX_MOD), 4 , process->owner->number);
    }
    printf("0x03\n");
}