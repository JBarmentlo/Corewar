/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/04/30 18:53:17 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena		init_vm(void)
{
	t_arena vm;

	vm.nb_champs = 0;
	vm.option_dump = 0;
	vm.cycle = 0;
	return (vm);
}

int		assign_champ(t_arena *vm)
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
	return (TRUE);
}

int		main(int ac, char **av)
{
	t_disp			d;
	int				timeout;
	int				running;
	t_arena			vm;
	int				i;
	unsigned int 	j;

	i = 0;
	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE
		|| assign_champ(&vm) == FALSE)
		return (FALSE);
	init_window(&d, vm);
	running = 1;
	vm.total_process_nb = vm.nb_champs;
	count_owned_space(&vm);
	while (!is_game_over(&vm) && running && ((vm.cycle < (unsigned long)vm.option_dump) || vm.option_dump == 0))
	{
		if (vm.cycle == UINT64_MAX)
		{
			printf("dude this is taking forever\n");
			break ;
		}
		timeout = SDL_GetTicks() + 100;
		i = SDL_GetTicks() + 100;
		j = 0;
		while (j < d.delay && ((vm.cycle < (unsigned long)vm.option_dump) || vm.option_dump == 0))
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
	if (vm.option_dump != 0)
		hex_dump_ugly(&vm);
	error("End.", &d);
	free_all(&vm);
	return (TRUE);
}


/*
__attribute__((destructor)) void test()
{
	while(1);
}*/
