#include "arena.h"

void	x11(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = ((int)arena->args->val_read[1] + (int)arena->args->val_read[2]) % IDX_MOD;
	mem_read_uint(arena, val);
	reg_write_uint(process, val, arena->args->val[0]);
	printf("OX11\n");
}