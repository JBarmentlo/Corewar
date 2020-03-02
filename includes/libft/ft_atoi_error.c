/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:50:31 by dberger           #+#    #+#             */
/*   Updated: 2020/03/02 16:51:17 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_error(const char *str)
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
	if (*str != '\0')
		return (-1);
	return (nb * neg);
}
