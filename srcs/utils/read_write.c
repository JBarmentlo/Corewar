/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:29:46 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:29:49 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		positive_modulo_memsize(int a)
{
	return (a & (MEM_SIZE - 1));
}

void	print_color_state(t_arena *vm)
{
	ft_printf("total mem: %d\n", vm->champion_table[0].total_memory_owned);
}

void	mem_write_color(t_arena *arena, uint index, uint size, int champ_nb)
{
	uint	i;
	int		current_owner;

	i = 0;
	while (i < size)
	{
		current_owner = arena->memory_color[(index + i) & MODULO_MASK];
		current_owner -= '0';
		if (current_owner > 0 && current_owner <= MAX_PLAYERS)
		{
			arena->champion_table[current_owner - 1].total_memory_owned -= 1;
		}
		arena->champion_table[champ_nb - 1].total_memory_owned += 1;
		arena->memory_color[(index + i) & MODULO_MASK] = champ_nb + '0';
		i++;
	}
}

int		mem_read_int(t_arena *arena, int index)
{
	t_byte	out[REG_SIZE];
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		out[REG_SIZE - 1 - i] = arena->memory[(index + i) & MODULO_MASK];
		i++;
	}
	return (*(int*)out);
}

void	mem_write_int(t_arena *arena, int index, int val)
{
	t_byte	*value;
	int		i;

	value = (t_byte*)&val;
	i = 0;
	while (i < REG_SIZE)
	{
		arena->memory[(index + i) & MODULO_MASK] = value[REG_SIZE - 1 - i];
		i++;
	}
}
