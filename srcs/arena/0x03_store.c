#include "arena.h"
#include "bitMasks.h"


void    x03(t_arena *arena, t_process *process)
{
    int    val;

    val = reg_read_int(process, arena->args->val[0]);
    if (arena->args->type[1] == T_REG)
    {
        reg_write_int(process, val, arena->args->val[1]);
		if (VERBOSE)
		{
			printf("store %d to register %d\n", val, arena->args->val[1]);
		}
    }
    else
    {
        mem_write_int(arena, process->PC + (arena->args->val[1] % IDX_MOD), val);
		mem_write_color(arena, process->PC + (arena->args->val[1] % IDX_MOD), 4 , process->owner->number);
		if ((VERBOSE & STORE) == STORE)
		{
			printf("store %d to mem[%d]\n", val, process->PC + (arena->args->val[1] % IDX_MOD));
		}
    }

}