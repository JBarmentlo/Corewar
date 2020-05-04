/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x15_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:16:23 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:16:25 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x15(t_arena *arena, t_process *process)
{
	t_process	*new;

	new = process_copy(process);
	new->pc = (process->pc + arena->args->val[0]) & MODULO_MASK;
	add_process_to_table(new, arena, arena->cycle + 1);
	add_process_to_list(new, arena);
	if ((VERBOSE & LFORK))
	{
		ft_printf("forked process to PC: %d with R1: %d\n",
			(process->pc + arena->args->val[0]) & MODULO_MASK,
			new->registre[0]);
	}
}
