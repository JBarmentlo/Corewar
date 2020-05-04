/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x13_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:16:01 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:16:02 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x13(t_arena *arena, t_process *process)
{
	int	value;

	if (arena->args->type[0] == T_IND)
	{
		value = mem_read_int(arena, process->pc + arena->args->val[0]);
		reg_write_int(process, value, arena->args->val[1]);
		if ((VERBOSE & LLD))
		{
			ft_printf("store %d from mem[%d]to register %d\n",
				value, process->pc + arena->args->val[0],
				arena->args->val[1]);
		}
	}
	else
	{
		value = arena->args->val[0];
		reg_write_int(process, value, arena->args->val[1]);
		if ((VERBOSE & LLD))
		{
			ft_printf("store %d to register %d\n", value, arena->args->val[1]);
		}
	}
	process->carry = (value == 0);
}
