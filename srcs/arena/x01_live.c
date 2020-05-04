/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x01_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:13:02 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:13:04 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x01(t_arena *arena, t_process *process)
{
	int	arg;

	process->last_live = arena->cycle;
	arena->total_live_since_check++;
	arg = arena->args->val[0];
	arg = (-1) * arg;
	if (arg <= MAX_PLAYERS && arg > 0 && arena->champion_table[arg - 1].exists)
	{
		arena->champion_table[arg - 1].lives_since_last_check += 1;
		arena->last_live_champ_number = arg;
		printf("un processus dit que le joueur %d(%s) est en vie\n",
			arg, arena->champion_table[arg - 1].header.prog_name);
	}
	if ((VERBOSE & LIVE))
	{
		ft_printf("live %d\n", arg);
		ft_printf("last_live_nb : %d\n", arena->last_live_champ_number);
		if (arg <= MAX_PLAYERS && arg > 0)
			ft_printf("total lives: %d\n",
				arena->champion_table[arg - 1].lives_since_last_check);
	}
}
