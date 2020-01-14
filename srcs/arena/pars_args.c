/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 15:19:32 by dberger           #+#    #+#             */
/*   Updated: 2020/01/14 17:48:57 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		ischamp(char *av, t_arena **vm, int n, int i)
{
	int		k;
	char	*name;

	k = ft_strlen(av);
	name = NULL;
	if (k <= 4)
		return (0);
	name = ft_memalloc(k);
	k = 0;
	while (av[k] != '.' && av[k])
	{
		name[k] = av[k];
		k++;
	}
	name[k] = '\0';
	if (av[k] == '\0' || ft_strcmp(".cor", av + k))
		return (0);
	(*vm)->champion_table[i].name = name;
	(*vm)->champion_table[i].number = n;
	(*vm)->nb_champs = (*vm)->nb_champs + 1;
	ft_printf("i = %d, name = %s, n = %d\n", i, (*vm)->champion_table[i].name, (*vm)->champion_table[i].number);
	return (1);
}

int		champ_num(int ac, char **av, int i)
{
	if (ft_strcmp(av[ac], "-n"))
		return (FALSE);
	ac++;
	if (av[ac] && ft_atoi(av[ac]) == 0 && ft_strcmp(av[ac], "0"))
		return (FALSE);
	return (ft_atoi(av[ac]));
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
	return (1);
}

int		pars_args(int ac, char **av, t_arena *vm)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	if (ac <= 0 || ac > 21)
		return (0);
	if (ac == 1)
		usage();
	ac = 1;
	if (pars_options(&ac, av, &vm) == 0)
		return (0);
	while (av[ac])
	{
		if (!ft_strcmp(av[ac], "-n"))
		{
			n = champ_num(ac, av, i);
			if (n != FALSE)
			{
				ac += 2;
				if (ischamp(av[ac], &vm, n, i) == 0)
					return (0);
			}
			else
				return (0);
		}
		else
			if (ischamp(av[ac], &vm, i + 1, i) == 0)
				return (0);
		ac++;
		i++;
	}
	ft_printf("nb champs = %d, vm dump = %d, vm option_s= %d\n", vm->nb_champs, vm->option_dump, vm->option_s);
	ft_printf("good!\n");
	return (1);
}
