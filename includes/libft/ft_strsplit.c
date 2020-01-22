/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:47:37 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 17:27:15 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit(char const *str, char c)
{
	int		i;
	int		k;
	int		j;
	char	**split;

	i = 0;
	k = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!(split = (char**)malloc(sizeof(char*) * (ft_word(str, c) + 1))))
		return (NULL);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		split[k] = ft_strnew(ft_sizew(i, str, c) + 1);
		while ((str[i] != c) && (str[i] != '\0'))
			split[k][j++] = str[i++];
		split[k][j] = '\0';
		j = 0;
		k++;
	}
	split[ft_word(str, c)] = 0;
	return (split);
}
