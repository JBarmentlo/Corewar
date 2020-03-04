/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:16:00 by dberger           #+#    #+#             */
/*   Updated: 2019/11/27 16:38:59 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	neg;
	long	nb;

	neg = 1;
	nb = 0;
	while (*str == ' ' || *str == '\f' || *str == '\t'
			|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit((long)*str))
	{
		nb = 10 * nb + *str - 48;
		str++;
	}
	return (nb * neg);
}
