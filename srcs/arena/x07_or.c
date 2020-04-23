/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x07_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:14:47 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:14:49 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x07(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = arena->args->val_read[0] | arena->args->val_read[1];
	reg_write_int(process, val, arena->args->val[2]);
	process->carry = (val == 0);
	if ((VERBOSE & OR))
	{
		printf("store %d to register %d\n", val, arena->args->val[2]);
	}
}
