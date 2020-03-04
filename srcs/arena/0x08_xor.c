#include "arena.h"
#include "bitMasks.h"

void	x08(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = arena->args->val_read[0] ^ arena->args->val_read[1];
	reg_write_int(process, val, arena->args->val[2]);
	process->carry = (val == 0);
	if ((VERBOSE & XOR) == XOR)
	{
		printf("store %d to register %d\n", val, arena->args->val[2]);
	}
}