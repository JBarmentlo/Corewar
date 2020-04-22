#include "arena.h"
#include "bitMasks.h"

void	x02(t_arena *arena, t_process *process)
{
	int	value;
	int	fk_norm;

	if (arena->args->type[0] == T_IND)
	{
		fk_norm = process->PC + (arena->args->val[0] % IDX_MOD);
		value = mem_read_int(arena, fk_norm);
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
