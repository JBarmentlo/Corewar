#include "arena.h"

void	x08(t_arena *arena, t_process *process)
{
	uint	val;

	get_val(arena, process);
	val = arena->args->val_read[0] ^ arena->args->val_read[1];
	reg_write_uint(process, val, arena->args->val[2]);
	process->carry = (val == 0);
	printf("OXO8\n");
}