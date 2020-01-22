/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:49:16 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/18 15:31:21 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_print_col(t_printf save, int *j, char *col)
{
	int		i;
	int		cmpt;

	i = 0;
	cmpt = 0;
	while (i < *j)
	{
		write(1, &save.buf[i], 1);
		i++;
	}
	*j = 0;
	cmpt = ft_printf("%s", col);
	save.ret += cmpt;
	return (save);
}

t_printf	ft_color2(const char *format, int *size, t_printf save, int *j)
{
	if (!ft_strncmp(format, "{pink}", (*size = 6)))
		save = ft_print_col(save, j, PF_PINK);
	else if (!ft_strncmp(format, "{grey}", (*size = 6)))
		save = ft_print_col(save, j, PF_GREY);
	else if (!ft_strncmp(format, "{green}", (*size = 7)))
		save = ft_print_col(save, j, PF_GREEN);
	else if (!ft_strncmp(format, "{cyan}", (*size = 6)))
		save = ft_print_col(save, j, PF_CYAN);
	else if (!ft_strncmp(format, "{black}", (*size = 7)))
		save = ft_print_col(save, j, PF_BLACK);
	else if (!ft_strncmp(format, "{blue}", (*size = 6)))
		save = ft_print_col(save, j, PF_BLUE);
	else if (!ft_strncmp(format, "{bold}", (*size = 6)))
		save = ft_print_col(save, j, PF_BOLD);
	else if (!ft_strncmp(format, "{highl}", (*size = 7)))
		save = ft_print_col(save, j, PF_HIGHL);
	else if (!ft_strncmp(format, "{blink}", (*size = 7)))
		save = ft_print_col(save, j, PF_BLINK);
	else if (!ft_strncmp(format, "{line}", (*size = 6)))
		save = ft_print_col(save, j, PF_LINE);
	else if (!ft_strncmp(format, "{eoc}", (*size = 5)))
		save = ft_print_col(save, j, PF_EOC);
	else
		*size = 0;
	return (save);
}

t_printf	ft_color(const char *format, t_printf save, int *j, int *i)
{
	int		size;
	int		k;

	k = 0;
	size = 1;
	while (format[k] == '{' && size != 0)
	{
		if (!ft_strncmp(&format[k], "{red}", (size = 5)))
			save = ft_print_col(save, j, PF_RED);
		else if (!ft_strncmp(&format[k], "{yellow}", (size = 8)))
			save = ft_print_col(save, j, PF_YELLOW);
		else
			save = ft_color2(&format[k], &size, save, j);
		*i += size;
		k += size;
		if (format[k + 1] == '{' && size == 0)
		{
			k++;
			size = 1;
			save = ft_check_add(save, j, '{');
			*i += 1;
		}
	}
	return (save);
}
