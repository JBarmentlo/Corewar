/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:48:14 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 20:14:12 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** When we write something in the out_file, we need to update the current size
** of the file (helps us allocate sufficient memory).
*/

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

long	count_bits(long nb)
{
	long	bits;

	bits = 0;
	if (nb < 0)
	{
		while (nb != 0)
		{
			nb = nb << 1;
			bits += 1;
		}
		return (bits);
	}
	while (nb != 0)
	{
		nb = nb >> 1;
		bits += 1;
	}
	return (bits);
}

/*
** To write a number in octet we need to check how many bits it contains,
** if it is more thant "needed" then it will be filled with zeros. Finally
** in the last "while" we fill the necessary number, bit by bit.
*/

int		nb_to_binary(t_file *out_file, int octets, int indx, long nb)
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
	return (TRUE);
}

/*
** Here we have parsed almost everything, except if the arguments that are
** calling a label, are calling an existing one.
** If the argument is a label we write the difference between the current label
** and the label that we have "called" (to_label - op->oct).
*/

int		write_op_values(t_file *out_file, int *i, t_instruct *op, t_stack stack)
{
	size_t	k;
	int		to_label;

	k = 0;
	while (k < op->nb_args)
	{
		if (op->argz[k].type == T_REG)
			write_in_file(out_file, *i, op->argz[k].value);
		else if (op->argz[k].lab == NULL)
			nb_to_binary(out_file, op->argz[k].oct, *i, op->argz[k].value);
		else if (op->argz[k].lab != NULL)
		{
			to_label = find_label(op->argz[k], stack.first_label);
			if (to_label == FALSE)
				return (FALSE);
			nb_to_binary(out_file, op->argz[k].oct, *i, (to_label - op->oct));
		}
		*i += op->argz[k].oct;
		k++;
	}
	return (TRUE);
}
