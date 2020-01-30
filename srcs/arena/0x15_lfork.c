#include "arena.h"

void    x15(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->PC = process->PC + arena->args->val[0]; 
	add_process_to_table(new, arena, arena->cycle);
	add_process_to_list(process, arena);
    printf("0x04\n");
}