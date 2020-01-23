/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:30:14 by dberger           #+#    #+#             */
/*   Updated: 2020/01/23 15:48:29 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		start_arena(t_arena *vm, t_champion *champ)
{
	int		i;
	int		s;
	int 	size;
	int		indx;

	i = 0;
	s = 1;
	indx = 0;
	size = 0;
	while (i < vm->nb_champs && s <= vm->nb_champs && indx < MEM_SIZE)
	{
		champ = &vm->champion_table[i];
		size = champ->prog_size - SIZE_HEADER;
		if (champ->number == s)
		{
			ft_memcpy(vm->memory + indx, champ->prog + SIZE_HEADER, size);
			indx += (MEM_SIZE / vm->nb_champs);
			s++;
			i = 0;
		}
		else
			i++;
	} 
	return (TRUE);
}
