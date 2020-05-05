/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x12_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:15:51 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 19:36:48 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x12(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->pc = (process->pc + (arena->args->val[0] % IDX_MOD)) & MODULO_MASK;
	add_process_to_table(new, arena, arena->cycle + 1);
	add_process_to_list(new, arena);
	process->owner->total_process += 1;
	arena->total_process_nb += 1;
	if ((VERBOSE & FORK))
	{
		ft_printf("forked process to PC: %d with R1: %d\n",
			(process->pc + (arena->args->val[0] % IDX_MOD)) & MODULO_MASK,
			new->registre[0]);
	}
}
