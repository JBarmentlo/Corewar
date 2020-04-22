#include "arena.h"
#include "bitMasks.h"

void	x13(t_arena *arena, t_process *process)
{
	int	value;

	if (arena->args->type[0] == T_IND)
	{
		value = mem_read_int(arena, process->PC + arena->args->val[0]);
		reg_write_int(process, value, arena->args->val[1]);
		if ((VERBOSE & LLD))
		{
			printf("store %d from mem[%d]to register %d\n",
				value, process->PC + arena->args->val[0],
				arena->args->val[1]);
		}
	}
	else
	{
		value = arena->args->val[0];
		reg_write_int(process, value, arena->args->val[1]);
		if ((VERBOSE & LLD))
		{
			printf("store %d to register %d\n", value, arena->args->val[1]);
		}
	}
	process->carry = (value == 0);
}
