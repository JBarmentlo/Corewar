/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x14_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:16:12 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:16:14 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x14(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = (arena->args->val_read[0] + arena->args->val_read[1]);
	val = mem_read_int(arena, process->pc + val);
	reg_write_int(process, val, arena->args->val[2]);
	process->carry = !val;
	if ((VERBOSE & LLDI))
	{
		ft_printf("store %d from mem[%d]to register %d\n", val,
			(arena->args->val_read[0] + arena->args->val_read[1]),
			arena->args->val[2]);
	}
}
