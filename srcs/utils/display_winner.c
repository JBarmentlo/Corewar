/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_winner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:24:51 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:25:24 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		display_winner(t_arena *vm)
{
	int		winner;

	winner = vm->last_live_champ_number;
	if (vm->nb_live_champions <= 1)
	{
		ft_printf("Player %d (%s) won\n", winner,
			vm->champion_table[winner - 1].header.prog_name);
		return (1);
	}
	return (0);
}
