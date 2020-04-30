#include "arena.h"

void		free_all_processes(t_arena *arena)
{
	t_process	*it;
	t_process	*tmp;

	it = arena->process_list;
	while (it)
	{
		tmp = it->next_list;
		bzero(it, sizeof(t_process));
		free(it);
		it = tmp;
	}
}
