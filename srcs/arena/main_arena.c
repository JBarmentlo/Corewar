/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/02/12 13:26:29 by jbarment         ###   ########.fr       */
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

void	print_vm_state(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d\n", it->owner->header.prog_name, it->owner->number, it->registre[0]);
		it = it->next_list;
	}
}

int		main(int ac, char **av)
{
 	t_disp		d;
	int		timeout;
	int		running;
	t_arena		vm;
	t_champion	*champ;
	int			i;
 
	i = 0;
	d.d_cycle = 1000;
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
	init_window(&d, vm);
	running = 1;
	vm.total_process_nb = vm.nb_champs;
	print_vm_state(&vm);
	while (!is_game_over(&vm) && vm.cycle < 400 && running)
	{
		do_the_cycle(&vm);
    	timeout = SDL_GetTicks() + d.delay;
		i = SDL_GetTicks() + 250;
		while (SDL_PollEvent(&d.event)
		|| (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout) && running != 0)
		|| (d.pause != 0 && d.step != 1))
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
		update_visu(&d, vm);
	}
	error("End.", &d);
	return (TRUE);
}
