/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_num_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:57:38 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 12:48:26 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

void	init_tab(int *nb, int k)
{
	while (k < MAX_ARGS_NUMBER)
	{
		nb[k] = k + 1;
		k++;
	}
}

int		check_errors_nb(int *nb, int i, int k)
{
	i = MAX_ARGS_NUMBER - 1;
	if (k > 0)
	{
		while (k > 0 && i > 0)
		{
			if (nb[i] == NO_NB)
				return (error("NB higher than the amount of champions", NULL));
			k--;
			i--;
		}
	}
	return (TRUE);
}

t_arena	**assign_nb(int *nb, t_arena **vm, int i, int k)
{
	while (i < (*vm)->nb_champs)
	{
		if ((*vm)->champion_table[i].number == NO_NB)
		{
			while (nb[k] == NO_NB)
				k++;
			(*vm)->champion_table[i].number = nb[k];
			k++;
		}
		i++;
	}
	return (vm);
}

int		pars_num_champ(int *nb, t_arena **vm, int mode)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (mode == 1)
		init_tab(nb, k);
	k = MAX_ARGS_NUMBER - (*vm)->nb_champs;
	if (mode == 2)
		if (check_errors_nb(nb, i, k) == FALSE)
			return (FALSE);
	k = 0;
	if (mode == 3)
		vm = assign_nb(nb, vm, i, k);
	return (TRUE);
}
