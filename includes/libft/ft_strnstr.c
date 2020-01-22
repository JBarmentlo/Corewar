/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:06:38 by dberger           #+#    #+#             */
/*   Updated: 2019/04/09 16:08:30 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	if (str[0] == '\0')
		return (NULL);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[j])
		{
			while (str[i + j] == to_find[j] && (i + j) < len)
			{
				if (to_find[j + 1] == '\0')
					return ((char *)str + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
