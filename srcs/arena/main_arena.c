/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:58:17 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 19:19:36 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena		init_vm(void)
{
	t_arena	vm;

	vm.nb_champs = 0;
	vm.option_dump = -1;
	vm.cycle = 0;
	return (vm);
}

int			assign_champ(t_arena *vm)
{
	int			i;
	t_champion	*champ;

	i = 0;
	while (i < vm->nb_champs)
	{
		champ = &vm->champion_table[i];
		if (pars_header(champ) == FALSE)
			return (FALSE);
		i++;
	}
	if (start_arena(vm) == FALSE)
		return (FALSE);
	vm->total_process_nb = vm->nb_champs;
	count_owned_space(vm);
	return (TRUE);
}

void		run_game(t_arena *vm)
{
	while (!is_game_over(vm) && ((vm->cycle < (unsigned long)vm->option_dump)
			|| vm->option_dump < 0))
	{
		if (vm->cycle == UINT64_MAX)
		{
			ft_printf("dude this is taking forever\n");
			break ;
		}
		do_the_cycle(vm);
		if (PRINT_VM_STATE == 1)
		{
			print_vm_state(vm);
			ft_printf("\n");
		}
	}
	if (vm->option_dump >= 0)
		hex_dump_ugly(vm);
}

int			main(int ac, char **av)
{
	t_arena		vm;

	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE
		|| assign_champ(&vm) == FALSE)
		return (-1);
	run_game(&vm);
	display_winner(&vm);
	free_all(&vm);
	return (0);
}
/*
**__attribute__((destructor)) void test()
**{
**	while(1);
**}
*/
