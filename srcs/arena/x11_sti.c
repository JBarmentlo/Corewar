/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:15:30 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:15:32 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x11(t_arena *arena, t_process *process)
{
	int	pos;

	get_val(arena, process);
	pos = (arena->args->val_read[1] + arena->args->val_read[2]) % IDX_MOD;
	mem_write_int(arena, process->pc + pos, arena->args->val_read[0]);
	mem_write_color(arena, process->pc + pos, 4, process->owner->number);
	if ((VERBOSE & STI))
	{
		ft_printf("wrote %d from register %d to mem[%d]\n",
			arena->args->val_read[0], arena->args->val[0],
			pos + process->pc);
	}
}
