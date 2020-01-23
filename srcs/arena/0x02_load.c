#include "arena.h"


//here we assume registres start at 1
//we write to process->registre[arg - 1]
void    x02(t_arena *arena, t_process *process)
{
	int	value;

	if (arena->args->type[0] == T_IND)
	{
		value = (int)mem_ind_to_uint(arena, process, arena->args->val[0]);
		reg_write_uint(process, value, arena->args->val[1]);
	}
	else
	{
		value = arena->args->val[0];
		reg_write_uint(process, value, arena->args->val[1]);
	}
	process->carry = (value == 0);
	printf("0x02\n");
}