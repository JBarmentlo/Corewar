/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_num_champ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:57:38 by dberger           #+#    #+#             */
/*   Updated: 2020/01/30 13:07:55 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/*
** First we have created an integer tab, of the size of MAX_ARGS_NUMBER
** In it we will find the numbers available for a champion (so at the
** beggining all of them are available. So nb[0] = 1, nb[1] = 2 etc...
*/

void	init_tab(int *nb, int k)
{
	while (k < MAX_ARGS_NUMBER)
	{
		nb[k] = k + 1;
		k++;
	}
}

/*
** Here we check if the number assigned to a champion is correct:
** it should be between 1 and the amount of champion. We can't assign
** the number '4' to a champion if there are only 3 of them in our arena.
*/

int		check_errors_nb(int *nb, int i, int k)
{
	i = MAX_ARGS_NUMBER - 1;
	while (k > 0 && i > 0)
	{
		if (nb[i] == NO_NB)
			return ((intptr_t)ft_error(TOO_HIGH, NULL));
		k--;
		i--;
	}
	return (TRUE);
}

void	swipe_champs(t_arena *vm)
{
	t_champion		save;
	t_champion		swipe;
	int				i;
	int				k;

	i = 0;
	k = 1;
	while (i < vm->nb_champs)
	{
		if (vm->champion_table[i].number == k)
		{
			save = vm->champion_table[k - 1];
			swipe = vm->champion_table[i];
			vm->champion_table[k - 1] = swipe;
			vm->champion_table[i] = save;
			k++;
			i = 0;
		}
		i++;
	}
}

/*
** In pars_args, we have writen 'NO_NB' in our integer array when
** its number is no longer avaible [taken by a champion with the '-n' option.
** So for the champions who do not have a number assigned yet,
** (their number equals also to NO_NB), we will assign them the numbers
** available in our integer array.
*/

void	assign_nb(int *nb, t_arena *vm, int i, int k)
{
	while (i < vm->nb_champs)
	{
		if (vm->champion_table[i].number == NO_NB)
		{
			while (nb[k] == NO_NB)
				k++;
			vm->champion_table[i].number = nb[k];
			k++;
		}
		i++;
	}
	swipe_champs(vm);
}

/*
** In this function we want to check if the number next to the '-n' option
** is correct and then assign it to a champion.
*/

int		pars_num_champ(int *nb, t_arena *vm, int mode)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (mode == 1)
		init_tab(nb, k);
	k = MAX_ARGS_NUMBER - vm->nb_champs;
	if (mode == 2)
		if (check_errors_nb(nb, i, k) == FALSE)
			return (FALSE);
	k = 0;
	if (mode == 3)
		assign_nb(nb, vm, i, k);
	return (TRUE);
}
