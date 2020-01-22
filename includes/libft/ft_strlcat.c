/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:32:27 by dberger           #+#    #+#             */
/*   Updated: 2019/04/10 12:06:08 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*new;
	const char	*tab;
	size_t		n;
	size_t		len;

	new = dst;
	tab = src;
	n = size;
	while (*new && n-- != 0)
		new++;
	len = new - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(src));
	while (*tab)
	{
		if (n != 1)
		{
			*new++ = *tab;
			n--;
		}
		tab++;
	}
	*new = '\0';
	return (len + (tab - src));
}
