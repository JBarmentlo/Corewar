#include "arena.h"

void	x10(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = ((int)arena->args->val_read[0] + (int)arena->args->val_read[1]) % IDX_MOD;
	val = mem_read_uint(arena, val);
	reg_write_uint(process, val, arena->args->val[2]);
	printf("OX10\n");
}