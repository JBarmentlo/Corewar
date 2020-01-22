
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/01/22 16:32:19 by dberger          ###   ########.fr       */
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
	t_champion	champ;
	int			i;

	i = 0;
	vm = init_vm();
	if (pars_args(ac, av, &vm) == FALSE)
		return (FALSE);
	while (i < vm.nb_champs)
	{
		champ = vm.champion_table[i];
		if (pars_header(&champ) == FALSE)
			return (FALSE);
		i++;
	}
	if (start_arena(&vm, &champ) == FALSE)
		return (FALSE);
	
}
/*
int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_disp		d;
	t_arena		a;
	int			running;
  
	a.nb_champions = 3;
	a.champion_table[3].name = "Tpillot";
	a.champion_table[2].name = "Jbarment";
	a.champion_table[1].name = "Ncoursol";
	a.champion_table[0].name = "Dberger";
	int		i = 0;
	while (i < MEM_SIZE)
	{
		a.memory[i] = '0';
		i++;
	}
	init_window(&d, a);
	running = 1;
	while (running)

	{
		while (SDL_PollEvent(&d.event))
			events(&d, &running, a);
	}
	ft_error("End.", &d);

	t_arena		*arena;
	t_process	*process;
	byte		bytecode;
	byte		reg;
	int16_t	ind;
	int			vint;
	uint		vuint;
	uint		dir;

	arena = make_vm();
	process = arena->process_list;
	arena->memory[0] = 2;
	arena->memory[1] = bytecode_gen(2,1,0);
	dir = 12345678;
	reg = 3;
	memcopy_endian_flip(&dir, &arena->memory[2], 4);
	memcopy_endian_flip(&reg, &arena->memory[2 + 4], 1);
	//execute_process(arena, process);


	ind = -1;
	vuint = (uint)ind;
	vint = (int)vuint;
	printf("H: %d\n", vint);
	printf("H: %u\n", vuint);

	return (0);
}
*/
