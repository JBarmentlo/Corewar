#include "arena.h"
#include "bitMasks.h"

void	x04(t_arena *arena, t_process *process)
{
	int	val1;
	int	val2;

	val1 = reg_read_int(process, arena->args->val[0]);
	val2 = reg_read_int(process, arena->args->val[1]);
	reg_write_int(process, (val1 + val2), arena->args->val[2]);
	if (VERBOSE & ADD)
	{
		printf("stored %d to register %d\n", val1 + val2, arena->args->val[2]);
	}
	process->carry = ((val1 + val2) == 0);
}