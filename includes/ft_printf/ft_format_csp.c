/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 20:37:05 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/03 08:34:37 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_form_c(t_printf save, int *j, char c)
{
	int		i;

	i = 0;
	if ((save.flags & F_MINUS) == F_MINUS)
	{
		save = ft_check_add(save, j, c);
		i++;
	}
	else
		save.width--;
	while (i < save.width)
	{
		save = ft_check_add(save, j, (save.flags & F_ZERO) ? '0' : ' ');
		i++;
	}
	if ((save.flags & F_MINUS) != F_MINUS)
		save = ft_check_add(save, j, c);
	return (save);
}

t_printf	ft_print(t_printf save, int *j, char *str, int *i)
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
		while ((*i <= 5) && (*i != save.pre || !(save.flags & F_POINT)))
		{
			save = ft_check_add(save, j, nul[*i]);
			*i += 1;
		}
	}
	else
	{
		while (str[*i] && *i != save.pre)
		{
			save = ft_check_add(save, j, str[*i]);
			*i += 1;
		}
	}
	return (save);
}

t_printf	ft_form_s(t_printf save, int *j, char *str)
{
	int		i;

	i = 0;
	if (!(save.flags & F_POINT))
		save.pre = -1;
	if (save.flags & F_MINUS)
		save = ft_print(save, j, str, &i);
	i = ((!str) ? 6 : ft_strlen(str));
	if (save.pre >= 0 && i != 0)
		save.width -= (i - (i - ((save.pre > i) ? i : save.pre)));
	else
		save.width -= i;
	i = 0;
	while (i++ < save.width)
		save = ft_check_add(save, j, (((save.flags & F_ZERO)
						&& !(save.flags & F_MINUS)) ? '0' : ' '));
	i = 0;
	if (!(save.flags & F_MINUS))
		save = ft_print(save, j, str, &i);
	return (save);
}

t_printf	ft_form_p(t_printf save, int *j, void *p)
{
	int					i;
	unsigned long int	k;
	int					s;

	k = ((unsigned long int)p ? (unsigned long int)p : 0);
	i = ((unsigned long int)p ? 63 : 4);
	if ((unsigned long int)p)
		while ((k >> i | k >> (i - 1) | k >> (i - 2) | k >> (i - 3)) == 0)
			i -= 4;
	while (i % 4 != 0)
		i++;
	s = (save.width - ((i / 4) + 2) - ((save.pre && k == 0) ? save.pre : 0));
	s < 0 ? s = 0 : 0;
	i--;
	if (save.width == 0)
		save = ft_dtoh(save, j, k, i);
	if (save.width != 0 && (save.flags & F_MINUS) == F_MINUS)
		save = ft_dtoh(save, j, k, i);
	while (s-- != 0)
		save = ft_check_add(save, j, ' ');
	if (save.width != 0 && (save.flags & F_MINUS) != F_MINUS)
		save = ft_dtoh(save, j, k, i);
	return (save);
}

t_printf	ft_format_csp(t_printf save, va_list ap, int *j, char c)
{
	int		a;
	char	*str;
	void	*p;

	if (c == 'c')
	{
		a = va_arg(ap, int);
		save = ft_form_c(save, j, a);
	}
	else if (c == 's')
	{
		str = va_arg(ap, char*);
		save = ft_form_s(save, j, str);
	}
	else if (c == 'p')
	{
		p = va_arg(ap, void*);
		save = ft_form_p(save, j, p);
	}
	return (save);
}
