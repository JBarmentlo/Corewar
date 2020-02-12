#include "arena.h"

void	x11(t_arena *arena, t_process *process)
{
	int	val;
	
	get_val(arena, process);
	val = (arena->args->val_read[1] + arena->args->val_read[2]) % IDX_MOD;
	mem_read_int(arena, process->PC +val);
	mem_write_int(arena, process->PC + val, arena->args->val[0]);
	printf("val_read[1]: %d, val_read[2]: %d\n", arena->args->val_read[1], arena->args->val_read[2]);
	printf("writing %d to index %d\n", arena->args->val[0], process->PC + val);
}