/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 12:15:09 by dberger           #+#    #+#             */
/*   Updated: 2019/04/10 18:53:30 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
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
	while (ft_isdigit((int)*str))
	{
		nb = 10 * nb + *str - 48;
		str++;
	}
	return (nb * neg);
}
