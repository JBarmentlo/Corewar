#include "arena.h"

void	x09(t_arena *arena, t_process *process)
{
	if (process->carry)
		process->PC = process->PC + (arena->args->val[0] % IDX_MOD);
	printf("OXO9\n");
}