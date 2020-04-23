/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_converter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:26:34 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:28:19 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

// write bit printer to test these

//returns a pointer to switched endian value.
// the macs are little endian I believe ?
// it's malloc so free it later
t_byte		*endian_switch(void *vall, int size)
{
	int		i;
	t_byte	*out;
	t_byte	*val;

	i = 0;
	val = vall;
	out = malloc(size);
	while (i < size)
	{
		out[i] = val[size - i - 1];
		i++;
	}
	return (out);
}

// Only works for size in [1, 2, 4]
// untested
uint		big_endian_to_uint(void *vall, int size)
{
	t_byte	*tmp;
	t_byte	*val;
	uint	out;

	val = vall;
	tmp = endian_switch(val, size);
	out = 0;
	if (size == 2)
	{
		out = ((uint)*((uint16_t*)tmp));
	}
	else if (size == 4)
	{
		out = ((uint)*((uint*)tmp));
	}
	else if (size == 1)
	{
		out = ((uint)*((t_byte*)tmp));
	}
	free(tmp);
	return (out);
}

int			big_endian_to_int(void *vall, int size)
{
	t_byte	*tmp;
	t_byte	*val;
	int		out;

	val = vall;
	tmp = endian_switch(val, size);
	out = 0;
	if (size == 2)
	{
		out = ((int)*((int16_t*)tmp));
	}
	else if (size == 4)
	{
		out = ((int)*((int*)tmp));
	}
	else if (size == 1)
	{
		out = ((int)*((t_byte*)tmp));
	}
	free(tmp);
	return (out);
}

t_byte		*uint_to_big_endian(uint val, int size)
{
	return (endian_switch((t_byte*)&val, size));
}

void		bit_dump(void *ptrr, int size)
{
	int		i;
	t_byte	*ptr;

	ptr = ptrr;
	i = 0;
	while (i < size)
	{
		printf("%d", (ptr[i] & EIGHT) != 0);
		printf("%d", (ptr[i] & SEVEN) != 0);
		printf("%d", (ptr[i] & SIX) != 0);
		printf("%d", (ptr[i] & FIVE) != 0);
		printf("%d", (ptr[i] & FOUR) != 0);
		printf("%d", (ptr[i] & THREE) != 0);
		printf("%d", (ptr[i] & TWO) != 0);
		printf("%d", (ptr[i] & ONE) != 0);
		printf(" ");
		i++;
	}
	printf("\n");
}

// not safe for use on MEM
void		memcopy(void *src, void *dest, uint16_t size)	// DOES this work for static arrays ?
{
	int		i;
	t_byte	*srcc;
	t_byte	*destt;

	srcc = src;
	destt = dest;

	i = 0;
	while (i < size)
	{
		destt[i] = srcc[i];
		i++;
	}
}

// not safe for use on MEM
void		memcopy_endian_flip(void *src, void *dest, uint16_t size)
{
	int		i;
	t_byte	*srcc;
	t_byte	*destt;

	srcc = src;
	destt = dest;

	i = 0;
	while (i < size)
	{
		destt[i] = srcc[size - 1 - i];
		i++;
	}
}
