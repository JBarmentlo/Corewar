/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:44:58 by dberger           #+#    #+#             */
/*   Updated: 2019/06/13 14:26:50 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_num(t_printf save, long s, long type, int *j)
{
	int		t;
	long	ten;
	char	c;

	t = 1;
	ten = 0;
	if (type >= 10)
	{
		ten = 1;
		while (t < s)
		{
			ten = ten * 10;
			t++;
		}
	}
	while (ten >= 10)
	{
		c = (type / ten) + '0';
		type = type - ((type / ten) * ten);
		save = ft_check_add(save, j, c);
		ten = ten / 10;
	}
	c = type + '0';
	return (ft_check_add(save, j, c));
}

t_printf	ft_ltoa(t_printf save, int *j, long type)
{
	long	s;

	s = ft_sizenb_l(type);
	if (type == 0)
		return (ft_check_add(save, j, '0'));
	if (type < 0)
	{
		save = ft_check_add(save, j, '-');
		type = -type;
		s -= 1;
	}
	s--;
	return (ft_num(save, s, type, j));
}
