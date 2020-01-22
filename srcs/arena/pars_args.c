/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:19:32 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 12:09:49 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

/*
** Once we have a champion's number, before stocking its datas, we want to make
** sure we can open the '.cor' file where is info is stocked, and that we are
** not overlapping the maximum number of champions.
*/

int		is_champ(char *av, t_arena **vm, int n, int *i)
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
	(*vm)->champion_table[*i].number = n;
	(*vm)->champion_table[*i].fd = fd;
	(*vm)->nb_champs = (*vm)->nb_champs + 1;
	*i += 1;
	return (TRUE);
}

/*
** If there is no '-n' option, then the number associated to the champion is
** simply 'i + 1' (it's position in the parameters).
** The '-n' option should be followed by a number, not already used by
** champion in (vm->champion_table[k].number).
*/

int		champ_num(int *ac, char **av, int *nb)
{
	int k;
	int	n;

	k = 0;
	n = 0;
	if (ft_strcmp(av[*ac], "-n"))
		return (NO_NB);
	*ac += 1;
	if (av[*ac])
		n = ft_atou(av[*ac]);
	if (av[*ac] == NULL || av[*ac + 1] == NULL || n == -1)
		return (usage());
	if (n <= 0 || n > MAX_ARGS_NUMBER)
		return (error("Wrong number for a champion", NULL));
	if (nb[n - 1] == NO_NB)
		return (error("Same number for two champions", NULL));
	if (n > 0 && n != NO_NB)
		nb[n - 1] = NO_NB;
	*ac += 1;
	return (n);
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

int		number_opt(int *opt, char **av, int *ac, t_arena **vm)
{
	int		nb;

	nb = 0;
	if (*opt == 1)
		return (error("Can't have twice the option", av[*ac]));
	if (av[*ac + 1] == NULL)
		return (usage());
	nb = ft_atou(av[*ac + 1]);
	if (nb == -1 || av[*ac + 2] == NULL)
		return (usage());
	*opt = 1;
	(*vm)->option_dump = nb;
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
	int		nb[MAX_ARGS_NUMBER];

	n = 0;
	i = 0;
	d = 0;
	if (ac <= 0)
		return (error("ERROR", NULL));
	if (ac == 1)
		return (usage());
	ac = 1;
	pars_num_champ(nb, &vm, 1);
	while (av[ac])
	{
		if (!ft_strcmp(av[ac], "-dump"))
			if (number_opt(&d, av, &ac, &vm) == FALSE)
				return (FALSE);
		n = champ_num(&ac, av, nb);
		if (n == FALSE)
			return (FALSE);
		if (is_champ(av[ac], &vm, n, &i) == FALSE)
			return (FALSE);
		ac++;
	}
	if (pars_num_champ(nb, &vm, 2) == FALSE)
		return (FALSE);
	pars_num_champ(nb, &vm, 3);
	return (TRUE);
}
