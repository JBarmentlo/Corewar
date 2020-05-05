/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:09:00 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:09:03 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	print_vm_state(t_arena *arena)
{
	t_process	*it;
	int			i;

	it = arena->process_list;
	ft_printf("cycle:%lu\n process list : \n", arena->cycle);
	while (it)
	{
		ft_printf("Owner: %s, owner.nb: %d, R1:%d, R2:%d\n",
			it->owner->header.prog_name, it->owner->number,
			it->registre[0], it->registre[1]);
		it = it->next_list;
	}
	i = 0;
	ft_printf("champions: \n arena->nb_champs: %d \n", arena->nb_champs);
	while (i < arena->nb_champs)
	{
		ft_printf("nb %d, name %s\n", arena->champion_table[i].number,
			arena->champion_table[i].header.prog_name);
		i++;
	}
}

void	ft_printf_process_pc(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	ft_printf("process list : \n");
	while (it)
	{
		ft_printf("owner: %d PC: %d\n", it->owner->number, it->pc);
		it = it->next_list;
	}
}

void	hex_dump_ugly(t_arena *arena)
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			printf("\n");
		printf("%02hhx ", arena->memory[i]);
		i++;
	}
	printf("\n");
}

void	dump_color(t_arena *arena)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 50 == 0)
		{
			ft_printf("\n");
		}
		if (arena->memory_color[i] != '0')
		{
			ft_printf("%02x ", arena->memory_color[i] - '0');
		}
		else
		{
			ft_printf(" . ");
		}
		i++;
	}
}
