/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/03/11 17:18:45 by jbarment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "bitMasks.h"
#include "stdio.h"
#include "limits.h"

t_arena		init_vm()
{
	t_arena vm;

	vm.nb_champs = 0;
	vm.option_dump = 0;
	vm.cycle = 0;
	return (vm);
}

int		main(int ac, char **av)
{
	t_arena		vm;
	t_champion	champ;
    t_champion *campo;
	int		i;

	i = 0;
	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE)
		return (FALSE);
	while (i < vm.nb_champs)
	{
		campo = &vm.champion_table[i];
		if (pars_header(campo) == FALSE)
			return (FALSE);
		i++;
	}
    i = 0;
    if (start_arena(&vm, &champ) == FALSE)
		return (FALSE);
	vm.total_process_nb = vm.nb_champs;
	count_owned_space(&vm);
	hex_dump(&vm);
	while (!is_game_over(&vm) && ((vm.cycle < (unsigned long)vm.option_dump) || vm.option_dump == 0))
	{
		if (vm.cycle == UINT64_MAX)
		{
			printf("dude this is taking forever\n");
			break ;
		}
		do_the_cycle(&vm);
	}
	if (vm.option_dump != 0)
		hex_dump(&vm);
	free_all(&vm);
	return (TRUE);
}


/*
__attribute__((destructor)) void test()
{
	while(1);
}*/
