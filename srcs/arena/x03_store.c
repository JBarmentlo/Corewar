/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x03_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:13:51 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:13:52 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x03(t_arena *arena, t_process *process)
{
	int	val;
	int	norm;

	val = reg_read_int(process, arena->args->val[0]);
	if (arena->args->type[1] == T_REG)
	{
		reg_write_int(process, val, arena->args->val[1]);
		if (VERBOSE & STORE)
		{
			ft_printf("store %d from reg[%d] to register %d\n",
				val, arena->args->val[0], arena->args->val[1]);
		}
	}
	else
	{
		norm = process->pc + (arena->args->val[1] % IDX_MOD);
		mem_write_int(arena, norm, val);
		mem_write_color(arena, norm, 4, process->owner->number);
		if (VERBOSE & STORE)
		{
			ft_printf("store %d from reg[%d] to mem[%d]\n", val,
				arena->args->val[0], norm);
		}
	}
}
