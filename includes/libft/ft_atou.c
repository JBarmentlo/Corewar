/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:05:06 by dberger           #+#    #+#             */
/*   Updated: 2020/01/16 14:13:33 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The flag '-1' stands for an error (no string, or not only numbers
** in the string)
*/

int		ft_atou(const char *str)
{
	long	nb;

	nb = 0;
	if (*str == '\0')
		return (-1);
	while (*str == ' ' || *str == '\f' || *str == '\t'
			|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '+')
		str++;
	while (ft_isdigit((int)*str))
	{
		nb = 10 * nb + *str - 48;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (nb);
}
