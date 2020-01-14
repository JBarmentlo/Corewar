/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 15:33:24 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/19 11:21:10 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_flags(char *str, t_printf save, int *i)
{
	while (str[*i] && (str[*i] == '#' || str[*i] == '0' || str[*i] == '+'
				|| str[*i] == ' ' || str[*i] == '-'))
	{
		if (str[*i] == '#')
			save.flags = save.flags | F_HASH;
		else if (str[*i] == '0')
			save.flags = save.flags | F_ZERO;
		else if (str[*i] == '+')
			save.flags = save.flags | F_PLUS;
		else if (str[*i] == ' ')
			save.flags = save.flags | F_SPACE;
		else if (str[*i] == '-')
			save.flags = save.flags | F_MINUS;
		*i += 1;
	}
	return (save);
}

int			ft_width(char *str, t_printf *save, int *i)
{
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			save->width = (save->width * 10) + (str[*i] - '0');
			*i += 1;
		}
	}
	if (str[*i] == '.')
	{
		save->flags |= F_POINT;
		*i += 1;
		while (str[*i] && str[*i] >= '0' && str[*i] <= '9')
		{
			save->pre = (save->pre * 10) + (str[*i] - '0');
			*i += 1;
		}
		if (str[*i - 1] == '.' || (str[*i - 1] == '0' && str[*i - 2] == '.'))
			save->pre = 0;
	}
	if (!ft_check_char(str, *i, 1))
		return (0);
	return (1);
}

t_printf	ft_modif2(char *str, t_printf *save, int *i)
{
	if (str[*i] == 'l' && str[*i + 1] != 'l')
		save->modif = save->modif | M_L;
	else if (str[*i] == 'L')
		save->modif = save->modif | M_BIGL;
	else if (str[*i] == 'z')
		save->modif = save->modif | M_Z;
	else if (str[*i] == 'j')
		save->modif = save->modif | M_J;
	return (*save);
}

int			ft_modif(char *str, t_printf *save, int *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
	{
		save->modif = save->modif | M_HH;
		*i += 1;
	}
	else if (str[*i] == 'h' && str[*i + 1] != 'h')
		save->modif = save->modif | M_H;
	else if (str[*i] == 'l' || str[*i] == 'L'
			|| str[*i] == 'z' || str[*i] == 'j')
		*save = ft_modif2(str, save, i);
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
	{
		save->modif = save->modif | M_LL;
		*i += 1;
	}
	if (str[*i] == 'h' || str[*i] == 'l' || str[*i] == 'L'
		|| str[*i] == 'z' || str[*i] == 'j')
		*i += 1;
	if (!ft_check_char(str, *i, 1))
		return (0);
	return (1);
}

t_printf	ft_convert(t_printf save, char *str, int *i, int *s)
{
	while (str[*i] && !ft_check_char(str, *i, 1))
	{
		if (!ft_check_char(str, *i, 2) && (*s = 1) == 1)
		{
			save.index = save.index + *i;
			return (save);
		}
		*s = *i;
		save = ft_flags(str, save, i);
		ft_width(str, &save, i);
		ft_modif(str, &save, i);
		*i = ((*i == *s) ? (*i + 1) : *i);
	}
	if (ft_width(str, &save, i) == 0 && ft_modif(str, &save, i) == 0)
	{
		*i = 0;
		while (!(ft_check_char(str, *i, 3)))
		{
			save.index++;
			*i += 1;
		}
		return ((*s = 1) == 1 ? save : save);
	}
	return ((*s = 2) == 2 ? save : save);
}
