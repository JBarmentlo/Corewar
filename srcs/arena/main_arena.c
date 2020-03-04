/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:24:17 by dberger           #+#    #+#             */
/*   Updated: 2020/03/04 13:33:18 by ncoursol         ###   ########.fr       */
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
	printf("process list : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d, R2:%d\n", it->owner->header.prog_name, it->owner->number, it->registre[0], it->registre[1]);
		it = it->next_list;
	}
	it = arena->process_table[0];
	printf("process table : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d\n", it->owner->header.prog_name, it->owner->number, it->registre[0]);
		it = it->next_table;
	}
}

void	printf_process_PC(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	printf("process list : \n");
	while (it)
	{
		printf("owner: %d PC: %d\n", it->owner->number, it->PC);
		it = it->next_list;
	}
}

void	hex_dump(t_arena *arena)
{
	size_t		i;
	int			zeroes;
	int			offset;

	zeroes = 0;
	offset = 0;
	i = 0;
	while (i < MEM_SIZE)
	{	
		if (i && offset % 50 == 0)
			printf ("\n");
		if (arena->memory[i])
		{
			printf("%02x ", arena->memory[i]);
			zeroes = 0;

		}
		if (!arena->memory[i])
		{
			zeroes += 1;
			if (i % 10 == 0)
			{
				printf(" ! ");
			}
			else
				printf(" . ");
		}
		if (zeroes > 100)
		{
			printf("skip");
			while (i < MEM_SIZE && arena->memory[i] == 0)
			{
				i++;
			}
			i--;
			zeroes = 0;
		}

		if ((i + 1) % (MEM_SIZE / arena->nb_champs) == 0)
		{
			offset = 0;
			printf ("\n\n%zu",i);
		}
		else
		{
			offset++;
		}
		i++;
	}
}

void	dump_color(t_arena *arena)
{
	int	i = 0;

	while (i < MEM_SIZE)
	{
		if (i % 50 == 0)
		{
			printf ("\n");
		}
		if (arena->memory_color[i] != '0')
		{
			printf("%02x ", arena->memory_color[i] - '0');
		}
		else
		{
			printf(" . ");
		}
	
		i++;
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
	int			visu = 1;
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
	print_vm_state(&vm);
	hex_dump(&vm);
	while (!is_game_over(&vm) /*&& vm.cycle < 20000*/ && running)
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
