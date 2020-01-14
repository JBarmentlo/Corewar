#include "arena.h"
#include "stdlib.h"

int		do_we_have_a_winner(t_arena *arena)
{
	int			out;
	int			first_process_owner;
	t_process	*it;

	out = 1;
	it = arena->process_list;
	first_process_owner = it->owner->number;
	it = it->next;

	while (it != NULL)
	{
		if (it->owner->number != first_process_owner)
			return (0);
		it = it->next;
	}
	return (1);
}

void	execute_process(t_arena *arena, t_process *process)
{
	process->current_op = &g_op_tab[arena->memory[process->PC]];
	/*
	if (is_encoding_byte_ok(arena, process))
	{
		f[process->current_op](PC);
	}
	go_to_next_opcode(arena, process);
	*/
	arena++;
	process++;
}


void	execute_processes(t_arena *arena)
{
	t_process *it;

	it = arena->process_table[arena->cycle % PROCESS_TABLE_SIZE];
	while (it != NULL)
	{
		execute_process(arena, it);
		it = it->next;
	}
	//reset next pointers and clear table at index, use recusrive call to reset next pointer collapse ? too fancy ?
}

int		do_the_cycle(t_arena *arena)
{	
	if (do_we_have_a_winner(arena))
		return (0);
	execute_processes(arena);	//skip empty turns for performance
	arena->cycle += 1;
	return (1);
}