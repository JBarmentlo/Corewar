#include "arena.h"
#include "stdlib.h"
#include "stdio.h"



void	run_function(t_arena *arena, t_process *process)
{
	printf("running %s\n", process->current_op->name);
	print_t_args(arena->args);
}

void	check_lives(t_arena *arena)
{
	t_process	*it;
	t_process	*next;
	t_process	**prev;

	it = arena->process_list;
	prev = &arena->process_list;
	while (it)
	{
		next = it->next_list;
		if (arena->cycle - it->last_live > arena->cycle_to_die) // gt or gteq ?
			kill_process(arena, it, prev);
		it = next;
	}
	if (arena->total_live_since_check >= NBR_LIVE || arena->max_checks >= MAX_CHECKS)		//what happens when it reaches 0 or negative values?
	{
		arena->cycle_to_die -= CYCLE_DELTA;
		arena->max_checks = 0;
	}
	else
	{
		arena->max_checks += 1;		
	}
	arena->cycles_since_check = 0;
}

int		do_the_cycle(t_arena *arena)
{	
	if (arena->cycles_since_check == arena->cycle_to_die)
		check_lives(arena);
	execute_processes(arena);	//skip empty turns for performance
	arena->cycle += 1;
	return (1);
}