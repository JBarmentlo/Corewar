#include "arena.h"

void	x11(t_arena *arena, t_process *process)
{
	int	pos;
	
	get_val(arena, process);
	pos = (arena->args->val_read[1] + arena->args->val_read[2]) % IDX_MOD;
	mem_write_int(arena, process->PC + pos, arena->args->val_read[0]);
	printf("val_read[1]: %d, val_read[2]: %d\n", arena->args->val_read[1], arena->args->val_read[2]);
	printf("writing %d to index %d\n", arena->args->val_read[0], process->PC + pos);
}