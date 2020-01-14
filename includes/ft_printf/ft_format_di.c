/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:17:49 by dberger           #+#    #+#             */
/*   Updated: 2019/06/19 10:30:30 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_w_add(t_printf save, long type, int *j, int count)
{
	int		w;
	int		f;

	f = save.flags;
	w = save.width;
	if (type < 0 && save.pre > 0 && save.pre < ft_sizenb_l(type)
			&& w > ft_sizenb_l(type))
		count++;
	if (type < 0 && (save.flags & F_ZERO) && !(save.flags & F_MINUS)
			&& !(save.pre) && !(save.flags & F_POINT))
		save = ft_check_add(save, j, '-');
	if ((save.flags & F_ZERO) && !(save.pre) && !(save.flags & F_MINUS)
			&& !(save.flags & F_POINT))
	{
		while (ft_sizenb_l(type) < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	if (type == 0 && !(save.pre) && save.flags & F_POINT
			&& (w != 1 || (w == 1 && f != 44 && f != 37 && f != 56
					&& f != 49 && f != 40 && f != 33 && f != 41 && f != 61)))
		save = ft_check_add(save, j, ' ');
	while (ft_sizenb_l(type) < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_width_di(t_printf save, int *j, long type)
{
	int		count;
	long	s;
	int		w;

	w = save.width;
	s = ft_sizenb_l(type);
	count = w - s;
	if (save.pre && w > save.pre && s < save.pre)
		count = w - save.pre;
	if (save.pre && s < save.pre && w <= save.pre)
		return (save);
	if (save.flags & F_PLUS && type >= 0)
	{
		if (save.flags & F_ZERO && !(save.flags & F_MINUS) && !(save.pre)
				&& !(save.flags & F_POINT))
			save = ft_check_add(save, j, '+');
		count--;
	}
	if ((type >= 0 && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
			|| (type < 0 && save.pre))
		count--;
	save = ft_w_add(save, type, j, count);
	return (save);
}

t_printf	ft_pre_di(t_printf save, int *j, long type)
{
	long	s;
	int		p;

	s = ft_sizenb_l(type);
	p = save.pre;
	if (type >= 0 && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	if (type < 0)
	{
		save = ft_check_add(save, j, '-');
		type = -type;
		s--;
	}
	if (s < p)
	{
		while (p - s > 0)
		{
			save = ft_check_add(save, j, '0');
			p--;
		}
	}
	if (type == 0 && save.pre > 0)
		save = ft_check_add(save, j, '0');
	return (save);
}

long		ft_modif_di(t_printf save, va_list ap)
{
	long	type;

	type = 0;
	if (save.modif && (save.modif & M_HH) && !(save.modif & M_L)
			&& !(save.modif & M_LL))
		type = (char)va_arg(ap, int);
	if (save.modif && (save.modif & M_H) && !(save.modif & M_L)
			&& !(save.modif & M_LL))
		type = (short)va_arg(ap, int);
	if (save.modif && (save.modif & M_L))
		type = va_arg(ap, long);
	if (save.modif && (save.modif & M_LL))
		type = va_arg(ap, long long);
	if (save.modif && (save.modif & M_Z))
		type = va_arg(ap, size_t);
	if (save.modif && (save.modif & M_J))
		type = va_arg(ap, intmax_t);
	else if (!save.modif)
		type = va_arg(ap, int);
	return (type);
}

t_printf	ft_format_di(t_printf save, va_list ap, int *j)
{
	long	type;

	type = ft_modif_di(save, ap);
	if (type >= 0 && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		save = ft_check_add(save, j, ' ');
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	if (save.pre || (save.flags & F_POINT))
		save = ft_pre_di(save, j, type);
	save = ft_ltoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_di(save, j, type);
	return (save);
}
