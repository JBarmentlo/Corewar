/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:10:28 by dberger           #+#    #+#             */
/*   Updated: 2020/03/05 12:31:21 by dberger          ###   ########.fr       */
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
//	ft_printf("nb = [%ld], bits = [%d]\n", nb, bits);
	zeros = nb != 0 ? ((octets * BITS_IN_OCTET) - bits) / BITS_IN_OCTET : 0;
	n = nb;
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
