/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:19:32 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 15:28:05 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

/*
** Once we have a champion's number, before stocking its datas, we want to make
** sure we can open the '.cor' file where is info is stocked, and that we are
** not overlapping the maximum number of champions.
*/

int		is_champ(char *av, t_arena *vm, int n, int *i)
{
	int		fd;
	int		l;

	l = ft_strlen(av);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (error("Can't read source file", av));
	if (l <= 4 || ft_strcmp(av + (l - 4), ".cor"))
		return (error("The source file should be a '.cor' file", av));
	if (*i == MAX_PLAYERS)
		return (error("Too many champions", NULL));
	vm->champion_table[*i].number = n;
	vm->champion_table[*i].fd = fd;
	vm->nb_champs = vm->nb_champs + 1;
	*i += 1;
	return (TRUE);
}

/*
** If there is no '-n' option, then the number associated to the champion is
** simply 'i + 1' (it's position in the parameters).
** The '-n' option should be followed by a number, not already used by
** champion in (vm->champion_table[k].number).
*/

int		champ_num(int *ac, char **av, int *nb, int *n)
{
	int k;

	k = 0;
	*n = 0;
	if (ft_strcmp(av[*ac], "-n"))
	{
		*n = NO_NB;
		return (TRUE);
	}
	*ac += 1;
	if (av[*ac])
		*n = ft_atou(av[*ac]);
	if (av[*ac] == NULL || av[*ac + 1] == NULL || *n == -1)
		return (usage());
	if (*n <= 0 || *n > MAX_PLAYERS)
		return (error("Wrong number for a champion", NULL));
	if (nb[*n - 1] == NO_NB)
		return (error("Same number for two champions", NULL));
	if (*n > 0 && *n != NO_NB)
		nb[*n - 1] = NO_NB;
	*ac += 1;
	return (TRUE);
}

int		usage(void)
{
	int		fd;
	char	*line;

	fd = 0;
	line = NULL;
	fd = open("./usage.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_printf("%s\n", line);
		ft_memdel((void **)&(line));
	}
	return (FALSE);
}

/*
** In number_opt, we stock the number write after an option like -dump
** the function ft_atou, converts a string into a positiv number. If the
** string is a negative number or contains letters, ft_atou returns -1.
*/

int		option_nb(int *opt, char **av, int *ac, t_arena *vm)
{
	int		nb;

	nb = 0;
	if (ft_strcmp(av[*ac], "-dump"))
		return (TRUE);
	if (*opt == 1)
		return (error("Can't have twice the option", av[*ac]));
	if (av[*ac + 1] == NULL)
		return (usage());
	nb = ft_atou(av[*ac + 1]);
	if (nb == -1 || av[*ac + 2] == NULL)
		return (usage());
	*opt = 1;
	vm->option_dump = nb;
	*ac = *ac + 2;
	return (TRUE);
}

/*
** While reading the arguments, we need to know if it is an
** option for the vm (-dump N) or the champions (-n N) - stock these
** info and then make sure the champions files (.cor) are correct.
*/

int		pars_args(int ac, char **av, t_arena *vm)
{
	int		n;
	int		d;
	int		i;
	int		nb[MAX_PLAYERS];

	n = 0;
	i = 0;
	d = 0;
	if (ac <= 1)
		return (ac == 1 ? usage() : error("can't read the arguments", NULL));
	ac = 1;
	pars_num_champ(nb, vm, 1);
	while (av[ac])
	{
		if (option_nb(&d, av, &ac, vm) != FALSE
		&& champ_num(&ac, av, nb, &n) != FALSE
		&& is_champ(av[ac], vm, n, &i) != FALSE)
			ac++;
		else
			return (FALSE);
	}
	if (pars_num_champ(nb, vm, 2) == FALSE)
		return (FALSE);
	pars_num_champ(nb, vm, 3);
	return (TRUE);
}