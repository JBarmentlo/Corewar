/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:37:41 by dberger           #+#    #+#             */
/*   Updated: 2019/06/18 10:54:44 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

t_printf	ft_w_add_f(t_printf save, int *j, int count, char *fix)
{
	long	s;
	int		w;
	long	l;

	l = ft_strlen_l(fix);
	w = save.width;
	if ((!(save.pre) && !(save.flags & F_POINT)) || (save.pre == 6))
		s = l + 7;
	else
		s = l + save.pre + 1;
	if (fix[0] == '-' && save.pre > 0 && save.pre < s && w > s)
		count++;
	if (fix[0] == '-' && (save.flags & F_ZERO) && !(save.flags & F_MINUS))
		save = ft_check_add(save, j, '-');
	if ((save.flags & F_ZERO) && !(save.flags & F_MINUS))
	{
		while (s < w && (count--) > 0)
			save = ft_check_add(save, j, '0');
		return (save);
	}
	while (s < w && (count--) > 0)
		save = ft_check_add(save, j, ' ');
	return (save);
}

t_printf	ft_width1(t_printf save, char *fix)
{
	int		count;
	long	s;
	long	l;

	l = ft_strlen_l(fix);
	s = l + save.pre + 1;
	if (!(save.pre) && !(save.flags & F_POINT))
		s = l + 7;
	if (!(save.pre) && (save.flags & F_POINT) && !(save.flags & F_HASH))
		s--;
	count = save.width - s;
	if (save.pre && save.width > save.pre && s < save.pre)
		count = save.width - save.pre;
	save.p = count;
	save.min = s;
	return (save);
}

t_printf	ft_width_f(t_printf save, int *j, char *fix, char *nb)
{
	int		count;
	long	s;

	save = ft_width1(save, fix);
	count = save.p;
	s = save.min;
	if (save.pre && save.width > save.pre && s < save.pre)
		count = save.width - save.pre;
	if (save.pre && s < save.pre && save.width <= save.pre)
		return (save);
	if (save.flags & F_PLUS && fix[0] != '-')
	{
		if ((save.flags & F_ZERO) && !(save.flags & F_MINUS) && !(save.pre))
			save = ft_check_add(save, j, '+');
		count--;
	}
	if ((fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
			|| (fix[0] == '-' && save.pre))
		count--;
	if (fix[0] == '0' && fix[1] == '\0' && nb[0] == '0' && nb[1] == '\0'
			&& !(save.pre) && (save.flags & F_POINT))
		count++;
	save = ft_w_add_f(save, j, count, fix);
	return (save);
}

void		ft_initiate(char *fix, char *nb, long double f, t_printf *save)
{
	unsigned long *var;

	ft_bzero(fix, 2048);
	ft_bzero(nb, 2048);
	ft_float(f, fix, 1);
	ft_float(f, nb, 2);
	var = (unsigned long*)&f;
	save->min = 0;
	if (fix[0] == '\0' || (fix[0] == '-' && fix[1] == '\0'))
	{
		if (((var[1] >> 15) & 1) == 1)
		{
			fix[0] = '-';
			fix[1] = '0';
			fix[2] = '\0';
		}
		else
		{
			fix[0] = '0';
			fix[1] = '\0';
		}
	}
}

t_printf	ft_format_f(t_printf save, va_list ap, int *j)
{
	long double		f;
	char			fix[2048];
	char			nb[2048];

	f = va_arg(ap, double);
	save = ft_nan_inf(save, j, f);
	if (save.min != -42)
		return (save);
	ft_initiate(fix, nb, f, &save);
	if (fix[0] != '-' && (save.flags & F_SPACE) && !(save.flags & F_PLUS))
		save = ft_check_add(save, j, ' ');
	if (save.width && !(save.flags & F_MINUS))
	{
		save.p = 1;
		save = ft_ftoa(save, j, fix, nb);
		save = ft_width_f(save, j, fix, nb);
		save.p = 0;
	}
	if (fix[0] != '-' && (save.flags & F_PLUS))
		save = ft_check_add(save, j, '+');
	save = ft_ftoa(save, j, fix, nb);
	if (save.width && (save.flags & F_MINUS))
		save = ft_width_f(save, j, fix, nb);
	return (save);
}
