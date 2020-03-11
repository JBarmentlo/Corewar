#include "arena.h"
#include "bitMasks.h"

void    x15(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->PC = (process->PC + arena->args->val[0]) & MODULO_MASK;
	add_process_to_table(new, arena, arena->cycle + 1);
	add_process_to_list(new, arena);
	if ((VERBOSE & LFORK))
	{
		printf("forked process to PC: %d with R1: %d\n", (process->PC + arena->args->val[0]) & MODULO_MASK, new->registre[0]);
	}
}
