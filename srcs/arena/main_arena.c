/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/01/27 12:10:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "bitMasks.h"
#include "stdio.h"

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
	t_champion	*champ;
	int			i;

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
	return (TRUE);
}

/*
int		main(int ac, char **av)
{
	t_disp		d;
	t_arena		a;
	int			running;
	int			timeout;
  
	/////////////////////////////////////
	a.nb_champions = 4;
	int		i = 0;
	int 	j = 0;
	while (i < MEM_SIZE)
	{
		a.memory[i] = 'B';
		a.memory_color[i] = j;
		j++;
		if (j > 3)
			j = 0;
		i++;
	}
	//////////////////////////////////////
	init_window(&d, a);
	running = 1;
	while (running)
	{
		timeout = SDL_GetTicks() + d.delay;
		while (SDL_PollEvent(&d.event) || (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout) && running != 0) || (d.pause != 0 && d.step != 1))
		{
			d.step = 0;
			events(&d, &running, &timeout, a);
		}
		update_visu(&d, a);
		i = 0;
		while (i < MEM_SIZE)
		{
			a.memory[i] += 1;
			a.memory_color[i] = (a.memory_color[i] + 1) % 4;
			i++;
		}
	}
	error("End.", &d);
	return (0);
}
