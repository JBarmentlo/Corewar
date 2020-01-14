/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:33:00 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 16:50:35 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word(const char *str, char c)
{
	int	i;
	int k;
	int word;

	i = 0;
	word = 0;
	k = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if ((str[i] != c) && word == 0)
		{
			word = 1;
			k++;
		}
		if (str[i] == c)
			word = 0;
		i++;
	}
	if (k == 0)
		return (0);
	return (k);
}
