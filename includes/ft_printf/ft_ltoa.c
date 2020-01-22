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

t_printf	ft_neg(t_printf save, int *j, long *type, long *s)
{
	if (!(save.pre) && !(save.flags & F_POINT))
	{
		if (save.width)
			if ((save.flags & F_MINUS)
					|| (!(save.flags & F_MINUS) && !(save.flags & F_ZERO)))
				save = ft_check_add(save, j, '-');
		if (!(save.width))
			save = ft_check_add(save, j, '-');
	}
	if (*type < -9223372036854775807)
	{
		save.min = 1;
		*type += 1;
	}
	*type = -*type;
	*s -= 1;
	return (save);
}

t_printf	ft_plus(t_printf save, int *j)
{
	if (!save.width)
		save = ft_check_add(save, j, '+');
	if (save.width && !(save.flags & F_ZERO) && !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	if (save.width && (save.flags & F_MINUS))
		save = ft_check_add(save, j, '+');
	return (save);
}

t_printf	ft_num(t_printf save, long s, long type, int *j)
{
	int		t;
	long	ten;
	char	c;

	t = 1;
	ten = 0;
	if (type >= 10 && (ten = 10) == 10)
	{
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
	if (save.min == 1)
		type++;
	c = type + '0';
	return (ft_check_add(save, j, c));
}

t_printf	ft_ltoa(t_printf save, int *j, long type)
{
	long	s;
	long	ten;

	ten = 0;
	s = ft_sizenb_l(type);
	if ((save.modif & M_H))
		s = ft_sizenb_l(type);
	if (type >= 0 && !save.pre && (save.flags & F_PLUS)
			&& !(save.flags & F_POINT))
		save = ft_plus(save, j);
	if (type == 0)
	{
		if (save.pre || save.flags & F_POINT)
			return (save);
		return (ft_check_add(save, j, '0'));
	}
	if (type < 0)
		save = ft_neg(save, j, &type, &s);
	s--;
	return (ft_num(save, s, type, j));
}
