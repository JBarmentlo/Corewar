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

void	write_in_file(t_file *out_file, int indx, int n)
{
	out_file->content[indx] = n;
	out_file->total_size += 1;
}

void	copy_string(char *dest, char *src, int size, int *indx)
{
	int		l;
	int		i;

	i = 0;
	l = (int)ft_strlen(src);
	while (i < size)
	{
		if (i < l)
			dest[*indx] = src[i];
		else
			dest[*indx] = 0;
		*indx = *indx + 1;
		i++;
	}
}

long		count_bits(long nb)
{
	long	bits;

	bits = 0;
	if (nb < 0)
	{
		while (nb != 0)
		{
			nb  = nb << 1;
			bits += 1;
		}
		return (bits);
	}
	while (nb != 0)
	{
		nb  = nb >> 1;
		bits += 1;
	}
	return (bits);
}

void	nb_to_binary(t_file *out_file, int octets, int indx, long nb)
{
	long	n;
	long	bits;
	long	zeros;

	bits = nb != 0 ? count_bits(nb) : 0;
	zeros = nb != 0 ? ((octets * BITS_IN_OCTET) - bits) / BITS_IN_OCTET : 0;
	while (zeros > 0)
	{
		write_in_file(out_file, indx, 0);
		indx++;
		zeros--;
		octets--;
	}
	indx = indx + octets - 1;
	while (octets > 0)
	{
		n = nb & 0xff;
		write_in_file(out_file, indx, n);
		nb = nb >> BITS_IN_OCTET;
		octets--;
		indx--;
	}
}

int		find_label(char *to_find, t_label *label)
{
	int		oct_lab;

	while (label != NULL)
	{
		if (!ft_strcmp(label->name, to_find))
		{
			oct_lab = label->oct;
			return (oct_lab);
		}
		else
			label = label->next;
	}
	return (FALSE);
}

int		write_op_values(t_file *out_file, int *i, t_instruct *op, t_stack stack)
{
	size_t	k;
	int	to_label;
	t_label	*label;

	k = 0;
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
				return ((int)ft_error_nb(WRONG_LABEL, op->argz[k].lab, op->argz[k].line, op->argz[k].col));
			nb_to_binary(out_file, op->argz[k].oct, *i, (to_label - op->oct));
			*i += op->argz[k].oct;
		}
		k++;
	}
	return (TRUE);
}
