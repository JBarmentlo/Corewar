/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:29:20 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:29:22 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	count_color(t_champion *champ, t_arena *arena)
{
	int	i;

	i = 0;
	if (champ == NULL)
		return ;
	while (i < MEM_SIZE)
	{
		if (arena->memory_color[i] - '0' == champ->number)
			champ->total_memory_owned++;
		i++;
	}
}

void	count_owned_space(t_arena *arena)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		count_color(&arena->champion_table[i], arena);
		i++;
	}
}
