/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:48:39 by dberger           #+#    #+#             */
/*   Updated: 2019/09/23 15:24:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include <limits.h>
#include <float.h>
#include <stdio.h>

t_printf	ft_print(t_printf save, int *j, char *str, int i)
{
	char	nul[6];

	nul[0] = '(';
	nul[1] = 'n';
	nul[2] = 'u';
	nul[3] = 'l';
	nul[4] = 'l';
	nul[5] = ')';
	if (!str)
	{
		while ((i <= 5))
		{
			save = ft_check_add(save, j, nul[i]);
			i += 1;
		}
		return (save);
	}
	while (str[i])
	{
		save = ft_check_add(save, j, str[i]);
		i += 1;
	}
	return (save);
}

t_printf	ft_format(char c, t_printf save, va_list ap, int *j)
{
	long	d;
	int		a;
	char	*str;

	if (c == 'd')
	{
		d = va_arg(ap, long);
		save = ft_ltoa(save, j, d);
	}
	else if (c == 'c')
	{
		a = va_arg(ap, int);
		save = ft_check_add(save, j, a);
	}
	else if (c == 's')
	{
		a = 0;
		str = va_arg(ap, char*);
		save = ft_print(save, j, str, a);
	}
	return (save);
}

t_printf	ft_process(t_printf save, const char *restrict format, va_list ap)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (format[i])
	{
		while (format[i] && format[i] != '%')
		{
			save = ft_check_add(save, &j, format[i]);
			i++;
		}
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			save = ft_format(format[i + 1], save, ap, &j);
			i += 2;
		}
		if (format[i] == '%' && format[i + 1] == '\0')
			i++;
	}
	save = ft_check_add(save, &j, '\0');
	save.index = (j - 1);
	save.ret += (j - 1);
	return (save);
}

int			ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	t_printf	save;

	save.ret = 0;
	ft_bzero(save.buf, BUFF_SZ);
	save.buf[BUFF_SZ] = '\0';
	va_start(ap, format);
	save = ft_process(save, format, ap);
	write(1, save.buf, save.index);
	va_end(ap);
	return (save.ret);
}
