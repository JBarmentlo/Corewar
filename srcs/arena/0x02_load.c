#include "arena.h"
#include "bitMasks.h"
/*
here we assume registres start at 1
we write to process->registre[arg - 1]
*/
void	x02(t_arena *arena, t_process *process)
{
	int	value;

	if (arena->args->type[0] == T_IND)
	{
		value = mem_read_int(arena, process->PC + (arena->args->val[0] % IDX_MOD));
		reg_write_int(process, value, arena->args->val[1]);
	}
	else
	{
		value = arena->args->val[0];
		reg_write_int(process, value, arena->args->val[1]);
	}
	process->carry = (value == 0);
	if ((VERBOSE & LOAD))
	{
		printf("loaded %d to registre %d\n", value, arena->args->val[1]);
	}
}
