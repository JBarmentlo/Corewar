/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_code_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:48:14 by dberger           #+#    #+#             */
/*   Updated: 2020/02/13 19:44:22 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_opcode(char *string)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(string, g_op_tab[i].name))
			return (i + 1);
		i++;
	}
	return (0);
}

int		encoding_byte(t_instruct *op)
{
	int		i;
	size_t		k;

	i = 0;
	k = 0;
	/// T_IND = 4 ??? //// 
	while (k < op->nb_args)
	{
		i = i | op->argz[k].type;
		i = i << 2;
		k++;
	}
	return (i);
}

int		write_op_values(t_file *out_file, int *i, t_instruct *op)
{
	size_t k;
	int	to_label;
	int	oct;

	k = 0;
	to_label = 0;
	oct = 0;
	(void) out_file,
	(void) i;
	(void) op;
	while (k < op->nb_args)
	{
		if (op->argz[k].type == REG_CODE)
		{
			if (op->argz[k].value > 16)
				return (FALSE);
			write_in_file(out_file, *i, op->argz[k].value);
			*i += 1;
		}/*
		else if (op->argz[k].type = DIR_CODE)
		{
		}*/
		k++;
	}
	return (TRUE);
}
