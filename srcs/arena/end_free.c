#include "arena.h"
#include "bitMasks.h"

void	free_all(t_arena *arena)
{
	free_all_processes(arena);
	arena->process_list = NULL;
	free(arena->args);
	free(arena->op_fun_tab);
}