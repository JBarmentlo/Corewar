/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x16_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:16:41 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:16:43 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	x16(t_arena *arena, t_process *process)
{
	uint	val;

	val = reg_read_int(process, arena->args->val[0]);
	ft_printf("%c", val);
	if ((VERBOSE & AFF) == AFF)
	{
		ft_printf("printed %c\n", val);
	}
}
