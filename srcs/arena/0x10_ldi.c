#include "arena.h"
#include "bitMasks.h"

void	x10(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = (arena->args->val_read[0] + arena->args->val_read[1]) % IDX_MOD;
	val = mem_read_int(arena, process->PC + val);
	reg_write_int(process, val, arena->args->val[2]);
	if ((VERBOSE & LDI))
	{
		printf("store %d from mem[%d]to register %d\n", val,
			(arena->args->val_read[0] + arena->args->val_read[1]) % IDX_MOD,
			arena->args->val[2]);
	}
}
