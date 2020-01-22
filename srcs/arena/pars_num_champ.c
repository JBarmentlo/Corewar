/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_num_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:57:38 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 12:13:31 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		pars_num_champ(int *nb, t_arena **vm, int mode)
{
	int		k;
	int		i;

	k = 0;
	while (mode == 1 && k < MAX_ARGS_NUMBER)
	{
		nb[k] = k + 1;
		k++;
	}
	k = MAX_ARGS_NUMBER - (*vm)->nb_champs;
	i = MAX_ARGS_NUMBER - 1;
	if (mode == 2 && k > 0)
	{
		while (k > 0 && i > 0)
		{
			if (nb[i] == NO_NB)
				return (error("'-n' option not corresponding to the amount of champions", NULL));
			k--;
			i--;
		}
	}
	else if (mode == 3)
	{
		i = 0;
		k = 0;
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
	}
	return (TRUE);
}
