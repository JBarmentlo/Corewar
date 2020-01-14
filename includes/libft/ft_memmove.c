/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:23:31 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 10:10:42 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*source;
	char		*dest;

	source = (const char *)src;
	dest = (char *)dst;
	if (source < dest)
	{
		while (len--)
			dest[len] = source[len];
	}
	else
	{
		while (len--)
			*(dest++) = *(source++);
	}
	return (dst);
}
