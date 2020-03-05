/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_code_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:48:14 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 20:14:12 by dberger          ###   ########.fr       */
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
	int			i;
	size_t		k;

	i = 0;
	k = 0;
	while (k < op->nb_args)
	{
		i = i | op->argz[k].type;
		i = i << 2;
		k++;
	}
	while (k < (BITS_IN_OCTET / 2) - 1)
	{
		i = i | 0;
		i = i << 2;
		k++;
	}
	return (i);
}

int		find_label(char *to_find, t_label *label)
{
	t_label *save;
	int		oct_lab;

	save = label;
	oct_lab = 0;
	while (label != NULL)
	{
		if (!ft_strcmp(label->name, to_find))
		{
			oct_lab = label->oct;
			label = save;
			return (oct_lab);
		}
		else
			label = label->next;
	}
	label = save;
	return (FALSE);
}

int		write_op_values(t_file *out_file, int *i, t_instruct *op, t_stack stack)
{
	size_t k;
	int	to_label;
	int	oct;
	t_label	*label;

	k = 0;
	to_label = 0;
	oct = 0;
	label = stack.first_label;
	while (k < op->nb_args)
	{
		if (op->argz[k].type == T_REG)
		{
			if (op->argz[k].value > REG_NUMBER)
				return (FALSE);
			write_in_file(out_file, *i, op->argz[k].value);
			*i += 1;
		}
		else if (op->argz[k].lab == NULL)
		{
			nb_to_binary(out_file, op->argz[k].oct, *i, op->argz[k].value);
			*i += op->argz[k].oct;
		}
		else if (op->argz[k].lab != NULL)
		{
			to_label = find_label(op->argz[k].lab, label);
			if (to_label == FALSE)
				return (FALSE);
			nb_to_binary(out_file, op->argz[k].oct, *i, (to_label - op->oct));
			*i += op->argz[k].oct;
		}
		k++;
	}
	return (TRUE);
}
