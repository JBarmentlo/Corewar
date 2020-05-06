/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x05_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:14:20 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:14:22 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x05(t_arena *arena, t_process *process)
{
	int	val1;
	int	val2;

	val1 = reg_read_int(process, arena->args->val[0]);
	val2 = reg_read_int(process, arena->args->val[1]);
	reg_write_int(process, (val1 - val2), arena->args->val[2]);
	process->carry = ((val1 - val2) == 0);
	if ((VERBOSE & SUB))
	{
		ft_printf("store %d - %d to register %d\n",
			val1, val2, arena->args->val[2]);
	}
}
