#include "arena.h"

void Ox07(t_arena *arena, t_process *process)
{
	uint	val;

	get_val(arena, process);
	val = arena->args->val_read[0] | arena->args->val_read[1];
	write_uint_to_reg(process, val, arena->args->val[2]);
	process->carry = (val == 0);
	printf("OXO7\n");
}