/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:30:14 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 19:59:38 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

void	copy_code(t_arena *vm, t_champion *champ, int indx)
{
	int		i;

	i = SIZE_HEADER;
	while (i < SIZE_HEADER + 10)//champ->prog_size)
	{
		vm->memory[indx] = champ->prog[i];
		i++;
	}
	ft_printf("\n");
}

int		start_arena(t_arena *vm, t_champion *champ)
{
	int		i;
	int		s;
	int		indx;

	i = 0;
	s = 1;
	indx = 0;
	while (i < vm->nb_champs && s <= vm->nb_champs && indx < MEM_SIZE)
	{
		champ = &vm->champion_table[i];
		if (champ->number == s)
		{
			ft_printf("indx = %d\n", indx);
			ft_printf("name = [%s]\n", champ->name);
			copy_code(vm, champ, indx);
			indx += (MEM_SIZE / vm->nb_champs);
			s++;
			i = 0;
		}
		else
			i++;
	} 
	return (TRUE);
}
