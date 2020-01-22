/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nan_inf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:32:26 by dberger           #+#    #+#             */
/*   Updated: 2019/06/17 18:45:09 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_begin_inf(t_printf save, int *j, char **str)
{
	int		f;

	f = save.flags;
	if (*str[0] == 'i' && (f & F_SPACE) && save.width <= (int)ft_strlen(*str)
			&& !(f & F_MINUS) && !(save.min))
		save = ft_check_add(save, j, ' ');
	if (*str[0] == 'i' && (f & F_PLUS) && !(save.min))
		*str = "+inf";
	if (*str[0] == 'i' && (save.min))
		*str = "-inf";
	if (!(f & F_POINT))
		save.pre = -1;
	return (save);
}

t_printf	ft_print_infnan(t_printf save, int *j, char *str)
{
	int		i;
	int		f;

	f = save.flags;
	i = 0;
	save = ft_begin_inf(save, j, &str);
	if ((str[0] == 'i') && (f & F_SPACE) && (f & F_MINUS) && (save.width))
	{
		save = ft_check_add(save, j, ' ');
		save.width -= 1;
	}
	if (f & F_MINUS)
		while (str[i])
			save = ft_check_add(save, j, str[i++]);
	i = ((!str) ? 6 : ft_strlen(str));
	save.width -= i;
	i = 0;
	while (i++ < save.width)
		save = ft_check_add(save, j, ' ');
	i = 0;
	if (!(f & F_MINUS))
		while (str[i])
			save = ft_check_add(save, j, str[i++]);
	return (save);
}

t_printf	ft_nan_inf(t_printf save, int *j, long double f)
{
	char			fix[2048];
	unsigned long	*var;

	var = (unsigned long*)&f;
	ft_bzero(fix, 2048);
	if (0xC000000000000000 == var[0])
	{
		fix[0] = 'n';
		fix[1] = 'a';
		fix[2] = 'n';
		fix[3] = '\0';
		return (save = ft_print_infnan(save, j, fix));
	}
	if ((var[0] == 0x8000000000000000) && ((var[1] & 0x7FF) == 0x7FF))
	{
		if (f < 0)
			save.min = 1;
		fix[0] = 'i';
		fix[1] = 'n';
		fix[2] = 'f';
		fix[3] = '\0';
		return (save = ft_print_infnan(save, j, fix));
	}
	save.min = -42;
	return (save);
}
