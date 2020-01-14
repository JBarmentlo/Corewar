/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/01/14 16:24:03 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

t_arena		init_vm()
{
	t_arena vm;

	vm.nb_champs = 0;
	vm.option_dump = 0;
	vm.option_s = 0;
	vm.cycle = 0;
	return (vm);
}

int		main(int ac, char **av)
{
	t_arena vm;

	vm = init_vm();
	if (pars_args(ac, av, &vm) == 0)
		return (0);
	//parsing options
//	ac++;
//	av++;
	/*
	while(No_winner)
	{
		do_the_cycle(vm);
		display(vm);
	}
	*/
	return (0);
}
