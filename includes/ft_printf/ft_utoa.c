/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:55:17 by dberger           #+#    #+#             */
/*   Updated: 2019/05/31 14:23:55 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_plus_u(t_printf save, int *j)
{
	if (!save.width)
		save = ft_check_add(save, j, '+');
	if (save.width && !(save.flags & F_ZERO) && !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	if (save.width && (save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	return (save);
}

t_printf	ft_num_u(t_printf save, unsigned long s, unsigned long type, int *j)
{
	int				t;
	unsigned long	ten;
	char			c;

	t = 1;
	ten = 0;
	if (type >= 10 && (ten = 10) == 10)
	{
		while (t < (int)s)
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
	if (save.min == 1)
		type++;
	c = type + '0';
	return (ft_check_add(save, j, c));
}

t_printf	ft_utoa(t_printf save, int *j, unsigned long type)
{
	unsigned long	s;
	unsigned long	ten;

	ten = 0;
	s = ft_sizenb_u(type);
	if ((save.modif & M_H))
		s = ft_sizenb_u(type);
	if (!save.pre && (save.flags & F_PLUS))
		save = ft_plus_u(save, j);
	if (type == 0)
	{
		if (save.pre || save.flags & F_POINT)
			return (save);
		return (ft_check_add(save, j, '0'));
	}
	s--;
	return (ft_num_u(save, s, type, j));
}
