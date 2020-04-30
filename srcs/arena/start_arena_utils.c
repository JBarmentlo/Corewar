/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arena_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:03:53 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 19:30:04 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			fill_fun_ptr_tab(t_arena *arena)
{
	if (!(arena->op_fun_tab = malloc(17 * sizeof(t_fun_ptr))))
		return (FALSE);
	arena->op_fun_tab[0] = &x01;
	arena->op_fun_tab[1] = &x02;
	arena->op_fun_tab[2] = &x03;
	arena->op_fun_tab[3] = &x04;
	arena->op_fun_tab[4] = &x05;
	arena->op_fun_tab[5] = &x06;
	arena->op_fun_tab[6] = &x07;
	arena->op_fun_tab[7] = &x08;
	arena->op_fun_tab[8] = &x09;
	arena->op_fun_tab[9] = &x10;
	arena->op_fun_tab[10] = &x11;
	arena->op_fun_tab[11] = &x12;
	arena->op_fun_tab[12] = &x13;
	arena->op_fun_tab[13] = &x14;
	arena->op_fun_tab[14] = &x15;
	arena->op_fun_tab[15] = &x16;
	return (TRUE);
}

void		fill_arena(t_arena *vm, t_champion *champ, int indx)
{
	int		size;
	int		i;

	size = champ->header.prog_size;
	i = 0;
	while (i < MEM_SIZE / vm->nb_champs)
	{
		if (i <= size)
		{
			vm->memory[indx + i] = champ->prog[SIZE_HEADER + i];
			vm->memory_color[indx + i] = champ->number + '0';
		}
		else
		{
			vm->memory[indx + i] = '\0';
			vm->memory_color[indx + i] = '0';
		}
		i++;
	}
}
