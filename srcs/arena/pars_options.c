/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:06:36 by dberger           #+#    #+#             */
/*   Updated: 2020/01/14 17:48:43 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		number_opt(int *opt, char **av, int *i)
{
	int		nb;

	nb = 0;
	if (*opt == 1)
		return (0);
	if (av[*i + 1] == NULL || ft_atoi(av[*i + 1]) == 0)
	{
		usage();
		return (0);
	}
	*opt = 1;
	if (av[*i + 2] == NULL || ft_atoi(av[*i + 1]) == 0)
	{
		usage();
		return (0);
	}
	*i = *i + 2;
	return (1);
}

int		pars_options(int *ac, char **av, t_arena **vm)
{
	int		dump;
	int		s;
	int		i;

	dump = 0;
	s = 0;
	i = *ac;
	while (av[i] && (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-s")))
	{
		if (av[i] && !ft_strcmp(av[i], "-dump"))
		{
			if (number_opt(&dump, av, &i))
				(*vm)->option_dump = ft_atoi(av[i - 1]);
			else
				return (0);
		}
		if (av[i] && !ft_strcmp(av[i], "-s"))
		{
			if (number_opt(&s, av, &i))
				(*vm)->option_s = ft_atoi(av[i - 1]);
			else
				return (0);
		}
	}
	*ac = i;
	return (1);
}
