/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:10:28 by dberger           #+#    #+#             */
/*   Updated: 2020/02/07 14:39:20 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_in_file(t_file *out_file, int indx, int n)
{
	out_file->content[indx] = n;
	out_file->total_size += 1;
}

int		count_bits(int nb)
{
	int	bits;

	bits = 0;
	while (nb != 0)
	{
		nb  = nb >> 1;
		bits += 1;
	}
	return (bits);
}

void	nb_to_binary(t_file *out_file, int octets, int indx, int nb)
{
	int n;
	int	bits;
	int	zeros;

	bits = count_bits(nb);
	zeros = ((octets * BITS_IN_OCTET) - bits) / BITS_IN_OCTET;
	n = nb;
	while (zeros > 0)
	{
		write_in_file(out_file, indx, 0);
		indx++;
		zeros--;
		octets--;
	}
	indx = indx + octets - 1;
	while (indx > 0)
	{
		n = nb & 0xff;
		write_in_file(out_file, indx, n);
		nb = nb >> BITS_IN_OCTET;
		octets--;
		indx--;
	}
}
