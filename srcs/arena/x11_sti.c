#include "arena.h"
#include "bitMasks.h"

void	x11(t_arena *arena, t_process *process)
{
	int	pos;

	get_val(arena, process);
	pos = (arena->args->val_read[1] + arena->args->val_read[2]) % IDX_MOD;
	mem_write_int(arena, process->PC + pos, arena->args->val_read[0]);
	mem_write_color(arena, process->PC + pos, 4, process->owner->number);
	if ((VERBOSE & STI))
	{
		printf("wrote %d from register %d to mem[%d]\n",
			arena->args->val_read[0], arena->args->val[0],
			pos + process->PC);
	}
}