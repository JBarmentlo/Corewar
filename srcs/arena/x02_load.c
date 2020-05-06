/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x02_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:13:36 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:13:38 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x02(t_arena *arena, t_process *process)
{
	int	value;
	int	fk_norm;

	if (arena->args->type[0] == T_IND)
	{
		fk_norm = process->pc + (arena->args->val[0] % IDX_MOD);
		value = mem_read_int(arena, fk_norm);
		reg_write_int(process, value, arena->args->val[1]);
	}
	else
	{
		value = arena->args->val[0];
		reg_write_int(process, value, arena->args->val[1]);
	}
	process->carry = (value == 0);
	if ((VERBOSE & LOAD))
	{
		if (arena->args->type[0] == T_IND)
			ft_printf("loaded %d from mem[%d + %d] to registre %d\n",
			value, process->pc, fk_norm - process->pc, arena->args->val[1]);
		else
			ft_printf("loaded %d to registre %d\n", value, arena->args->val[1]);
	}
}
