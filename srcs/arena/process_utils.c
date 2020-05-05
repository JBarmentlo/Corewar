/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:12:30 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 19:32:02 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_process	*process_copy(t_process *src)
{
	t_process	*out;
	int			i;

	if (!(out = malloc(sizeof(t_process))))
		return (NULL);
	i = 0;
	while (i < REG_NUMBER)
	{
		out->registre[i] = src->registre[i];
		i++;
	}
	out->carry = src->carry;
	out->pc = src->pc;
	out->current_op = NULL;
	out->last_live = src->last_live;
	out->table_pos = src->table_pos;
	out->alive = src->alive;
	out->owner = src->owner;
	out->next_list = NULL;
	out->next_table = NULL;
	return (out);
}

void		remove_process_from_table(t_arena *arena, t_process *process)
{
	t_process	*it;
	int			norm;

	it = arena->process_table[process->table_pos % PROCESS_TABLE_SIZE];
	if (it == process)
	{
		norm = process->table_pos % PROCESS_TABLE_SIZE;
		arena->process_table[norm] = it->next_table;
	}
	else
	{
		while (it)
		{
			if (it->next_table == process)
			{
				it->next_table = process->next_table;
			}
			it = it->next_table;
		}
	}
}

void		kill_process(t_arena *arena, t_process *process)
{
	t_process *it;

	it = arena->process_list;
	if (arena->process_list == process)
	{
		arena->process_list = it->next_list;
		remove_process_from_table(arena, process);
		free(process);
		return ;
	}
	while (it)
	{
		if (it->next_list == process)
		{
			it->next_list = process->next_list;
			remove_process_from_table(arena, process);
			free(process);
			return ;
		}
		it = it->next_list;
	}
}

void		add_process_to_table(t_process *process, t_arena *arena, uint indx)
{
	int	norm;

	norm = indx % PROCESS_TABLE_SIZE;
	process->next_table = arena->process_table[norm];
	arena->process_table[indx % PROCESS_TABLE_SIZE] = process;
	process->table_pos = indx;
}

void		add_process_to_list(t_process *process, t_arena *arena)
{
	process->next_list = arena->process_list;
	arena->process_list = process;
}
