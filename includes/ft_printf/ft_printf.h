/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:04:24 by dberger           #+#    #+#             */
/*   Updated: 2019/12/05 16:52:18 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdarg.h>

# define BUFF_SZ 71

typedef struct		s_printf
{
	int				index;
	int				ret;
	char			buf[BUFF_SZ + 1];
}					t_printf;

char				*ft_check_rest(char *add, char *tab, int *rest, int *j);
t_printf			ft_check_add(t_printf save, int *j, char c);
t_printf			ft_ltoa(t_printf save, int *j, long type);
int					ft_printf(const char *restrict format, ...);

#endif
