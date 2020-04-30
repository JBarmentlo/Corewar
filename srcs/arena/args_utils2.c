/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:27:47 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 18:27:49 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		is_valid_args_value(t_args *args)
{
	int	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER && args->type[i] != 0)
	{
		if (args->type[i] == T_REG
		&& (args->val[i] > REG_NUMBER || args->val[i] < 1))
			return (0);
		i++;
	}
	return (1);
}

void	get_val(t_arena *arena, t_process *process)
{
	int	i;

	i = 0;
	while (i < process->current_op->arg_nb)
	{
		if (arena->args->type[i] == T_DIR)
		{
			arena->args->val_read[i] = arena->args->val[i];
		}
		else if (arena->args->type[i] == T_IND)
		{
			arena->args->val_read[i] = mem_ind_to_int(arena, process,
			(int)arena->args->val[i]);
		}
		else if (arena->args->type[i] == T_REG)
		{
			arena->args->val_read[i] = reg_read_int(process,
			arena->args->val[i]);
		}
		i++;
	}
}

int		splice(int o)
{
	if (o == 8)
		return (EIGHT);
	else if (o == 9)
		return (NINE);
	else if (o == 10)
		return (TEN);
	else if (o == 11)
		return (ELEVEN);
	else if (o == 12)
		return (TWELVE);
	else if (o == 13)
		return (THIRTEEN);
	else if (o == 14)
		return (FOURTEEN);
	else if (o == 15)
		return (FIFTEEN);
	else if (o == 16)
		return (SIXTEEN);
	return (0);
}

int		opcode_to_mask(int o)
{
	if (o == 1)
		return (ONE);
	else if (o == 2)
		return (TWO);
	else if (o == 3)
		return (THREE);
	else if (o == 4)
		return (FOUR);
	else if (o == 5)
		return (FIVE);
	else if (o == 6)
		return (SIX);
	else if (o == 7)
		return (SEVEN);
	return (splice(o));
}
