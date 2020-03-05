#include "arena.h"
#include "bitMasks.h"

void    x12(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->PC = (process->PC + (arena->args->val[0] % IDX_MOD)) & MODULO_MASK;
	add_process_to_table(new, arena, arena->cycle + 1);
	add_process_to_list(new, arena);
	process->owner->total_process += 1;
	arena->total_process_nb += 1;
	if ((VERBOSE & FORK) == FORK)
	{
		printf("forked process to PC: %d with R1: %d\n", (process->PC + (arena->args->val[0] % IDX_MOD)) & MODULO_MASK, new->registre[0]);
	}
}