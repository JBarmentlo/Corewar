/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 08:26:32 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 14:09:37 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int length;
	int i;
	int swap;

	length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	length--;
	i = 0;
	while (i < length)
	{
		swap = str[i];
		str[i] = str[length];
		str[length] = swap;
		length--;
		i++;
	}
	return (str);
}
