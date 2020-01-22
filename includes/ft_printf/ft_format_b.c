/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:02:34 by ncoursol          #+#    #+#             */
/*   Updated: 2019/05/27 17:43:55 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_len2(t_printf save, unsigned long long nb, int mode)
{
	int		i;
	int		s;

	i = 63;
	if (nb != 0)
		while (nb >> i != 1)
			i--;
	else
		i = 0;
	if (mode == 0)
		s = ((save.width - (i + 1)) < 0 ? 0 : (save.width - (i + 1)));
	else
		s = ((i < 0) ? -1 : i);
	return (s);
}

t_printf	ft_print_b(t_printf save, int *j, unsigned long long nb)
{
	int		i;
	int		c;

	c = 0;
	i = ft_len2(save, nb, 1);
	while (i > -1)
	{
		c = ((nb >> i) & 1);
		save = ft_check_add(save, j, (c + '0'));
		i--;
		c = 0;
	}
	return (save);
}

t_printf	ft_form_b(t_printf save, int *j, unsigned long long nb)
{
	int		s;

	s = ft_len2(save, nb, 0);
	if ((save.flags & F_MINUS))
		save = ft_print_b(save, j, nb);
	if (save.width != 0)
		while (s-- != 0)
			save = ft_check_add(save, j, ' ');
	if (!(save.flags & F_MINUS))
		save = ft_print_b(save, j, nb);
	return (save);
}

t_printf	ft_format_b(t_printf save, va_list ap, int *j)
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
	else
		number = va_arg(ap, unsigned int);
	if (save.flags & F_MINUS)
		save.flags -= F_ZERO;
	save = ft_form_b(save, j, number);
	return (save);
}
