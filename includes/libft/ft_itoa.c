/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:51:00 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 17:38:14 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char	*new;
	long	nb;
	long	i;

	nb = n;
	i = ft_sizenb(nb);
	if (!(new = ft_strnew(i)))
		return (NULL);
	i--;
	if (nb == 0)
	{
		new[0] = '0';
		return (new);
	}
	if (nb < 0)
		nb = -nb;
	while (i >= 0)
	{
		new[i] = (nb % 10 + '0');
		i--;
		nb = nb / 10;
	}
	if (n < 0)
		new[0] = '-';
	return (new);
}
