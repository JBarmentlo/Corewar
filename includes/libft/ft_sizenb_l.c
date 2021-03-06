/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizenb_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:43:07 by dberger           #+#    #+#             */
/*   Updated: 2019/05/29 12:51:08 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_sizenb_l(long n)
{
	long	i;
	long	nb;

	i = 0;
	nb = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}
