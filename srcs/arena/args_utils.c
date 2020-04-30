/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:08:16 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 19:37:33 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_args		*new_t_args(void)
{
	t_args	*out;
	int		i;

	i = 0;
	if (!(out = malloc(sizeof(t_args))))
		return (NULL);
	while (i < MAX_ARGS_NUMBER)
	{
		out->type[i] = 0;
		out->size[i] = 0;
		out->val[i] = 0;
		i++;
	}
	return (out);
}

void		set_args_to_zero(t_args *args)
{
	int i;

	i = 0;
	args->opcode = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		args->type[i] = 0;
		args->size[i] = 0;
		args->val[i] = 0;
		i++;
	}
}

t_byte		is_valid_opcode(t_byte opcode)
{
	if (opcode <= 16 && opcode > 0)
	{
		return (1);
	}
	return (0);
}

uint16_t	type_to_size(t_byte type, t_op *op)
{
	if (type == 0)
	{
		return (0);
	}
	if (type == T_REG)
		return (1);
	if (type == T_IND)
		return (2);
	if (type == T_DIR)
	{
		if (op->is_direct_small == 1)
			return (2);
		else
			return (4);
	}
	return (0);
}

int			is_valid_encoding_byte(t_arena *arena, t_process *process)
{
	int	i;

	i = 0;
	while (i < process->current_op->arg_nb)
	{
		if (arena->args->type[i] == 0 || ((arena->args->type[i]
		& process->current_op->arg_types[i]) != arena->args->type[i]))
			return (0);
		i++;
	}
	return (1);
}
