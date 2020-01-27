/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/01/27 15:43:38 by dberger          ###   ########.fr       */
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

int		ft_error(char *str, char *str2)
{
	if (str2 == NULL)
		ft_printf("Error: %s\n", str);
	else
		ft_printf("Error: %s %s\n", str, str2);
	return (FALSE);
}


int		main(int ac, char **av)
{
	t_arena		vm;
	t_disp		d;
	t_champion	*champ;
	int			i;
	int			timeout;
	int			running;
 

	i = 0;
	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE)
		return (FALSE);
	while (i < vm.nb_champs)
	{
		champ = &vm.champion_table[i];
		if (pars_header(champ) == FALSE)
			return (FALSE);
		i++;
	}
	if (start_arena(&vm, champ) == FALSE)
		return (FALSE);
	init_window(&d, vm);
	running = 1;
	while (running)
	{
		timeout = SDL_GetTicks() + d.delay;
		while (SDL_PollEvent(&d.event) || (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout) && running != 0) || (d.pause != 0 && d.step != 1))
		{
			d.step = 0;
			events(&d, &running, &timeout, vm);
		}
		update_visu(&d, vm);
		i = 0;
		while (i < MEM_SIZE)
		{
			vm.memory[i] += 1;
			vm.memory_color[i] = (vm.memory_color[i] + 1) % 4;
			i++;
		}
	}
	error("End.", &d);
	return (TRUE);
}
