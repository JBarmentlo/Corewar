/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:50:41 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/01 22:25:36 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		ft_bin_hexa(int a, int b, int c, int d)
{
	int		res;

	a &= 1;
	b &= 1;
	c &= 1;
	d &= 1;
	res = ((a << 3) | (b << 2) | (c << 1) | (d << 0));
	return (res);
}

int			ft_len4(int i)
{
	int		a;

	a = 0;
	while (i >= 0)
	{
		a++;
		i -= 4;
	}
	return (a);
}

t_printf	ft_dtoh(t_printf save, int *j, unsigned long int k, int i)
{
	char	c;

	save = ft_check_add(save, j, '0');
	save = ft_check_add(save, j, 'x');
	if (save.pre != 0)
	{
		while ((save.pre - ft_len4(i)) > 0)
		{
			save = ft_check_add(save, j, '0');
			save.pre--;
		}
	}
	if (!(save.flags & F_POINT) || save.pre != 0)
	{
		while (i >= 0)
		{
			c = ft_bin_hexa(k >> i, k >> (i - 1), k >> (i - 2), k >> (i - 3));
			if (c >= 10)
				save = ft_check_add(save, j, ((c - 10) + 'a'));
			else
				save = ft_check_add(save, j, (c + '0'));
			i -= 4;
		}
	}
	return (save);
}
