/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x09_zjump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:15:08 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:15:10 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x09(t_arena *arena, t_process *process)
{
	int	norm;

	norm = (process->PC + (arena->args->val[0] % IDX_MOD));
	if (process->carry)
		process->PC = norm & MODULO_MASK;
	if ((VERBOSE & ZJUMP))
	{
		if (process->carry == 0)
		{
			printf("no jump, carry is null\n");
		}
		else
		{
			printf("jumped %d spaces to %d\n",
				(arena->args->val[0] % IDX_MOD), norm & MODULO_MASK);
		}
	}
}
