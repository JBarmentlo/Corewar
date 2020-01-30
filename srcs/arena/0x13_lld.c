#include "arena.h"

void    x13(t_arena *arena, t_process *process)
{
	int	value;

	if (arena->args->type[0] == T_IND)
	{
		value = mem_ind_to_int(arena, process, arena->args->val[0]);
		reg_write_int(process, value, arena->args->val[1]);
	}
	else
	{
		value = arena->args->val[0];
		reg_write_int(process, value, arena->args->val[1]);
	}
	process->carry = (value == 0);
	printf("0x02\n");
}