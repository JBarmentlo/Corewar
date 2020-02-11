#include "arena.h"

void    x12(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->PC = process->PC + (arena->args->val[0] % IDX_MOD); 
	add_process_to_table(new, arena, arena->cycle);
	add_process_to_list(process, arena);
	process->owner->total_process += 1;
	arena->total_process_nb += 1;
    printf("0x04\n");
}