/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:11:54 by dberger           #+#    #+#             */
/*   Updated: 2019/06/19 11:05:16 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf		ft_width_u(t_printf save, int *j, unsigned long type)
{
	int				count;
	unsigned long	s;
	int				w;

	w = save.width;
	s = ft_sizenb_u(type);
	count = w - s;
	if (save.pre && w > save.pre && (int)s < save.pre)
		count = w - save.pre;
	if (save.pre && (int)s < save.pre && w <= save.pre)
		return (save);
	if (save.flags & F_PLUS)
		count--;
	if ((save.flags & F_ZERO) && !(save.pre) && !(save.flags & F_POINT)
			&& !(save.flags & F_MINUS))
	{
		while ((int)s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	if (type == 0 && !(save.pre) && save.flags & F_POINT)
		save = ft_check_add(save, j, ' ');
	while ((int)s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf		ft_pre_u(t_printf save, int *j, unsigned long type)
{
	unsigned long	s;
	int				p;

	s = ft_sizenb_u(type);
	p = save.pre;
	if ((int)s < p)
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

unsigned long	ft_modif_u(t_printf save, va_list ap)
{
	unsigned long	number;

	if (save.modif && (save.modif & M_HH))
		return (number = (unsigned char)va_arg(ap, unsigned int));
	if (save.modif && (save.modif & M_H))
		return (number = (unsigned short)va_arg(ap, unsigned int));
	if (save.modif && (save.modif & M_L))
		return (number = va_arg(ap, unsigned long));
	if (save.modif && (save.modif & M_LL))
		return (number = va_arg(ap, unsigned long long));
	if (save.modif && (save.modif & M_Z))
		return (number = va_arg(ap, ssize_t));
	if (save.modif && (save.modif & M_J))
		return (number = va_arg(ap, uintmax_t));
	return (number = va_arg(ap, unsigned int));
}

t_printf		ft_format_u(t_printf save, va_list ap, int *j)
{
	unsigned long	type;

	type = ft_modif_u(save, ap);
	if (save.width && !(save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	if (save.pre)
		save = ft_pre_u(save, j, type);
	if (save.flags & F_PLUS)
		save.flags -= F_PLUS;
	save = ft_utoa(save, j, type);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_u(save, j, type);
	return (save);
}
