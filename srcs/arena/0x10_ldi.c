#include "arena.h"

// CHECK GET_VAL
void	x10(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = (arena->args->val_read[0] + arena->args->val_read[1]) % IDX_MOD;
	val = mem_read_int(arena, val);
	reg_write_int(process, val, arena->args->val[2]);
	printf("OX10\n");
}