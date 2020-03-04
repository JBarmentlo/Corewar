#include "arena.h"
#include "bitMasks.h"

void	x14(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = (arena->args->val_read[0] + arena->args->val_read[1]);
	val = mem_read_int(arena, process->PC + val);
	reg_write_int(process, val, arena->args->val[2]);
	process->carry = !val;
	if ((VERBOSE & LLDI) == LLDI)
	{
		printf("store %d from mem[%d]to register %d\n", val, (arena->args->val_read[0] + arena->args->val_read[1]), arena->args->val[2]);
	}
}