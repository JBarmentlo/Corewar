/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/03/05 17:31:54 by jbarment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "bitMasks.h"
#include "stdio.h"

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
	t_disp		d;
	int		timeout;
	int		running;
	t_arena		vm;
	t_champion	*champ;
	int			i;
	int			visu = 0;
	unsigned int j;

	i = 0;
	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE)
		return (FALSE);
	while (i < vm.nb_champs)
	{
		champ = &vm.champion_table[i];
		if (pars_header(champ) == FALSE)
			return (FALSE);
		printf("champ.name = %s, number = [%d]\n", champ->header.prog_name, champ->number);
		i++;
	}
	if (start_arena(&vm, champ) == FALSE)
		return (FALSE);
	if (visu)
		init_window(&d, vm);
	running = 1;
	vm.total_process_nb = vm.nb_champs;
//	print_vm_state(&vm);
//	hex_dump(&vm);
printf("CYCLO TO DIE %d\n", vm.cycle_to_die);
	while (!is_game_over(&vm) && vm.cycle < 10000 && running)
	{
		do_the_cycle(&vm);
		if (visu)
		{
			timeout = SDL_GetTicks() + 100;
			i = SDL_GetTicks() + 100;
			j = 0;
			while (j < d.delay)
			{
				do_the_cycle(&vm);
				j++;
			}
			while (SDL_PollEvent(&d.event)
					|| (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout) && running != 0)
					|| (d.pause != 0 && d.step != 1))
			{
				d.step = 0;
				events(&d, &running, &timeout, vm);
				if (SDL_TICKS_PASSED(SDL_GetTicks(), i))
				{
					if (!(SDL_GetTicks() % d.d_cycle))
						do_the_cycle(&vm);
					d.step = 0;
					events(&d, &running, &timeout, vm);
					if (SDL_TICKS_PASSED(SDL_GetTicks(), i))
					{
						d.button_status = 0;
						i = SDL_GetTicks() + 200;
					}
				}
			}
			update_visu(&d, vm);
		}   
	}
	hex_dump(&vm);
	if (visu)
		error("End.", &d);
	return (TRUE);
}
