/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/01/20 15:33:37 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

t_arena		init_vm()
{
	t_arena vm;

	vm.nb_champs = 0;
	vm.option_dump = 0;
	vm.cycle = 0;
	return (vm);
}

int		error(char *str, char *str2)
{
	if (str2 == NULL)
		ft_printf("%s\n", str);
	else
		ft_printf("%s %s\n", str, str2);
	return (FALSE);
}

int		main(int ac, char **av)
{
	t_arena vm;

	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE)
		return (FALSE);
	pars_champ(&vm, 0);
	/*
	while(No_winner)
	{
		do_the_cycle(vm);
		display(vm);
	}
	*/
	return (0);
}
