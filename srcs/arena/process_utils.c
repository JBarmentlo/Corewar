#include "arena.h"

t_process	*process_copy(t_process *src)
{
	t_process	*out;
	int			i;

	out = malloc(sizeof(t_process));
	i = 0;
	while (i < REG_NUMBER)
	{
		out->registre[i] = src->registre[i];
		i++;
	}
	out->carry = src->carry;
	out->PC = src->PC;
	out->current_op = NULL;
	out->last_live = src->last_live;
	out->table_pos = src->table_pos;
	out->alive = src->alive;
	out->owner = src->owner;
	out->next_list = NULL;
	out->next_table = NULL;
	return (out);
}

void	remove_process_from_table(t_arena *arena, t_process *process) //wildly unchecked
{
	t_process	*it;
	t_process	**prev;

	it = arena->process_table[process->table_pos];
	prev = &it;
	while (it != process)
	{
		prev = &it->next_table;
		it = it->next_table;
	}
	*prev = it->next_table;
}

void	kill_process(t_arena *arena, t_process *it, t_process **prev)
{
	it->owner->total_process -= 1;
	arena->total_process_nb -= 1;
	*prev = it->next_list; //remove it form process_list in arena;
	remove_process_from_table(arena, it);
	free(it);
}

void	add_process_to_table(t_process *process, t_arena *arena, uint table_index)
{
	process->next_table = arena->process_table[table_index % PROCESS_TABLE_SIZE];
	arena->process_table[table_index % PROCESS_TABLE_SIZE] = process;
}


void	add_process_to_list(t_process *process, t_arena *arena)
{

	process->next_list = arena->process_list;
	arena->process_list = process;
}