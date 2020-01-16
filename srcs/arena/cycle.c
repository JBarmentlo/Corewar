#include "arena.h"
#include "stdlib.h"
#include "stdio.h"



void	run_function(t_arena *arena, t_process *process)
{
	printf("running %s\n", process->current_op->name);
	print_t_args(arena->args);
}

int		do_the_cycle(t_arena *arena)
{	
	
	execute_processes(arena);	//skip empty turns for performance
	arena->cycle += 1;
	return (1);
}