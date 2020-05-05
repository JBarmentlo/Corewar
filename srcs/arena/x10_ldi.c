/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x10_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:15:21 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:15:22 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x10(t_arena *arena, t_process *process)
{
	int	val;

	get_val(arena, process);
	val = (arena->args->val_read[0] + arena->args->val_read[1]) % IDX_MOD;
	val = mem_read_int(arena, process->pc + val);
	reg_write_int(process, val, arena->args->val[2]);
	if ((VERBOSE & LDI))
	{
		ft_printf("store %d from mem[%d]to register %d\n", val,
			(arena->args->val_read[0] + arena->args->val_read[1]) % IDX_MOD,
			arena->args->val[2]);
	}
}
