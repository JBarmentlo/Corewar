/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:34:43 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/19 11:08:20 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_print_ox(t_printf save, int *j, int nb, int mode)
{
	if (nb == 0)
		return (save);
	if ((save.flags & F_HASH) == F_HASH)
	{
		save = ft_check_add(save, j, '0');
		save = ft_check_add(save, j, (23 + mode));
	}
	return (save);
}

int			ft_len(t_printf save, unsigned long long nb, int mode)
{
	int		i;
	int		s;
	int		k;

	i = 63;
	if (nb != 0)
		while ((nb >> i | nb >> (i - 1) | nb >> (i - 2) | nb >> (i - 3)) == 0)
			i -= 4;
	while (i % 4 != 0)
		i++;
	if (nb == 0)
		i = ((save.pre == 0 && (save.flags & F_POINT)) ? -1 : 4);
	if (mode == 0)
	{
		k = ((save.pre - (i / 4)) < 0 ? 0 : save.pre - (i / 4));
		s = ((save.width - ((i / 4) + k)) < 0 ? 0 : save.width - ((i / 4) + k));
		s = (save.pre == 0 && (save.flags & F_POINT) && !save.width)
			|| (save.flags & F_HASH && nb != 0) ? s - 2 : s;
	}
	else if (mode == 1)
		s = ((save.pre - (i / 4)) < 0 ? 0 : save.pre - (i / 4));
	else
		s = (((i - 1) < 0) ? -1 : (i - 1));
	return (s);
}

t_printf	ft_print_h(t_printf save, int *j, unsigned long long nb, int mode)
{
	int		i;
	int		c;
	int		s2;

	c = 0;
	s2 = ft_len(save, nb, 1);
	if (save.pre != 0)
		while (s2-- != 0)
			save = ft_check_add(save, j, '0');
	i = ft_len(save, nb, 2);
	while (i > -1)
	{
		c = c | (((nb >> i) & 1) << 3);
		c = c | (((nb >> (i - 1)) & 1) << 2);
		c = c | (((nb >> (i - 2)) & 1) << 1);
		c = c | (((nb >> (i - 3)) & 1) << 0);
		if (c >= 10)
			save = ft_check_add(save, j, ((c - 10) + mode));
		else
			save = ft_check_add(save, j, (c + '0'));
		i -= 4;
		c = 0;
	}
	return (save);
}

t_printf	ft_form_xx(t_printf save, int *j, unsigned long long nb, int mode)
{
	int		s;

	if ((s = ft_len(save, nb, 0)) < 0)
		s = 0;
	if ((save.flags & F_MINUS))
	{
		save = ft_print_ox(save, j, nb, mode);
		save = ft_print_h(save, j, nb, mode);
	}
	if (save.width != 0 && !(save.flags & F_ZERO))
		while (s-- != 0)
			save = ft_check_add(save, j, ' ');
	if (!(save.flags & F_MINUS))
	{
		save = ft_print_ox(save, j, nb, mode);
		if (save.width != 0 && (save.flags & F_ZERO))
			while (s-- != 0)
				save = ft_check_add(save, j, '0');
		save = ft_print_h(save, j, nb, mode);
	}
	return (save);
}

t_printf	ft_format_xx(t_printf save, va_list ap, int *j, char c)
{
	unsigned long long	number;

	if (save.modif && (save.modif & M_HH))
		number = (unsigned char)va_arg(ap, int);
	else if (save.modif && (save.modif & M_H))
		number = (unsigned short)va_arg(ap, int);
	else if (save.modif && (save.modif & M_L))
		number = va_arg(ap, unsigned long);
	else if (save.modif && (save.modif & M_LL))
		number = va_arg(ap, unsigned long long);
	else if (save.modif && (save.modif & M_Z))
		number = va_arg(ap, ssize_t);
	else if (save.modif && (save.modif & M_J))
		number = va_arg(ap, uintmax_t);
	else
		number = va_arg(ap, unsigned int);
	if ((save.flags & F_MINUS || save.flags & F_POINT) && (save.flags & F_ZERO))
		save.flags -= F_ZERO;
	if (c == 'x')
		save = ft_form_xx(save, j, number, (int)'a');
	else if (c == 'X')
		save = ft_form_xx(save, j, number, (int)'A');
	return (save);
}
