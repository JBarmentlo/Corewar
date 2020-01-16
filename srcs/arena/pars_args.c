/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:19:32 by dberger           #+#    #+#             */
/*   Updated: 2020/01/16 12:36:29 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		is_champ(char *av, t_arena **vm, int n, int i)
{
	int		fd;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (error("Can't read source file", av));
	(*vm)->champion_table[i].number = n;
	ft_printf("AVANT i = %d, nb champs = %d\n", i, (*vm)->nb_champs);
	if ((*vm)->nb_champs == 4)
		return(error("Too many champions", NULL));
	(*vm)->nb_champs = (*vm)->nb_champs + 1;
	ft_printf("APRES i = %d, nb champs = %d\n", i, (*vm)->nb_champs);
	return (TRUE);
}

int		champ_num(int *ac, char **av, t_arena *vm)
{
	int k;
	int	n;
	
	k = 0;
	n = 0;
	*ac += 1;
	if (av[*ac] == NULL || (ft_atoi(av[*ac]) == 0 && ft_strcmp(av[*ac], "0")))
		return (usage());
	n = ft_atoi(av[*ac]);
	while (k < MAX_PLAYERS)
	{
		if (vm->champion_table[k].number == n)
			return (error("Can't have twice the same number of champion", NULL));
		k++;
	}
	if (av[*ac + 1] == NULL)
		return (usage());
	*ac += 1;
	return (n);
}

int		usage()
{
	int fd;
	char	*line;

	fd = 0;
	line = NULL;
	fd = open("./usage.txt", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_printf("%s\n", line);
		ft_memdel((void **)&(line));
	}
	return (FALSE2);
}

int		number_opt(int *opt, char **av, int *ac)
{
	int		nb;

	nb = 0;
	if (*opt == 1)
		return(error("Can't have twice the option", av[*ac]));
	if (av[*ac + 1] == NULL || (ft_atoi(av[*ac + 1]) == 0 && ft_strcmp(av[*ac], "0")))
		return (usage());
	*opt = 1;
	if (av[*ac + 2] == NULL)
		return (usage());
	*ac = *ac + 2;
	return (TRUE);
}

int		pars_args(int ac, char **av, t_arena *vm)
{
	int		n;
	int		d;
	int		i;

	n = 0;
	i = 0;
	d = 0;
	if (ac <= 0)
		return(error("ERROR", NULL));
	if (ac == 1)
		return (usage() == FALSE2 ? FALSE : FALSE);
	ac = 1;
	while (av[ac] && vm->nb_champs <= 4)
	{
		if (!ft_strcmp(av[ac], "-dump"))
		{
			if (number_opt(&d, av, &ac) == FALSE2)
				return(0);
			vm->option_dump = ft_atoi(av[ac - 1]);
		}
		if (!ft_strcmp(av[ac], "-n"))
		{
			n = champ_num(&ac, av, vm);
			if (n == FALSE2 || is_champ(av[ac], &vm, n, i) == FALSE)
					return (FALSE);
		}
		else
		{
			ft_printf("champ n: %d\n", i);
			if (is_champ(av[ac], &vm, i + 1, i) == FALSE)
				return (FALSE);
			i++;
		}
		ac++;
	}
	ft_printf("nb champs = %d, vm dump = %d\n", vm->nb_champs, vm->option_dump);
	ft_printf("good!\n");
	return (1);
}
