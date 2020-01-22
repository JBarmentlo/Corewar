/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:54:24 by dberger           #+#    #+#             */
/*   Updated: 2019/04/24 13:55:53 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	int		i;
	int		j;

	if (!s || !(tab = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = start;
	j = 0;
	while (i < ((int)start + (int)len))
	{
		tab[j] = s[i];
		i++;
		j++;
	}
	tab[j] = '\0';
	return (tab);
}
