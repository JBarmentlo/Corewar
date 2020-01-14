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
# include <stdarg.h>

# define BUFF_SZ 71

# define F_SPACE	0
# define F_HASH		0
# define F_MINUS	0
# define F_PLUS		0
# define F_ZERO		0
# define F_POINT	0

# define M_HH		0
# define M_H		0
# define M_L		0
# define M_BIGL		0
# define M_LL		0
# define M_Z		0
# define M_J		0

# define PF_BLACK	"\033[30m"
# define PF_RED		"\033[31m"
# define PF_GREEN	"\033[32m"
# define PF_YELLOW	"\033[33m"
# define PF_BLUE	"\033[34m"
# define PF_PINK	"\033[35m"
# define PF_CYAN	"\033[36m"
# define PF_GREY	"\033[37m"

# define PF_EOC		"\033[0m"
# define PF_BOLD	"\033[1m"
# define PF_LINE	"\033[4m"
# define PF_BLINK	"\033[5m"
# define PF_HIGHL	"\033[7m"

typedef struct		s_printf
{
	int				flags;
	int				width;
	int				pre;
	int				modif;
	int				index;
	int				ret;
	int				min;
	int				p;
	char			buf[BUFF_SZ + 1];
}					t_printf;

int					ft_check_char(char *str, int i, int mode);
char				*ft_check_rest(char *add, char *tab, int *rest, int *j);
t_printf			ft_check_add(t_printf save, int *j, char c);
int					ft_printf(const char *restrict format, ...);
t_printf			ft_convert(t_printf save, char *str, int *i, int *s);
t_printf			ft_print_float(t_printf save, int *j, char *str, char *nb);
t_printf			ft_ltoa(t_printf save, int *j, long type);
t_printf			ft_ftoa(t_printf save, int *j, char *fix, char *nb);
t_printf			ft_utoa(t_printf save, int *j, unsigned long type);
t_printf			ft_dtoh(t_printf save, int *j, unsigned long int k, int i);
t_printf			ft_format_di(t_printf save, va_list ap, int *j);
t_printf			ft_format_csp(t_printf save, va_list ap, int *j, char c);
t_printf			ft_format_xx(t_printf save, va_list ap, int *j, char c);
t_printf			ft_color(const char *format, t_printf save, int *j, int *i);
t_printf			ft_format_f(t_printf save, va_list ap, int *j);
t_printf			ft_nan_inf(t_printf save, int *j, long double f);
t_printf			ft_format_u(t_printf save, va_list ap, int *j);
t_printf			ft_format_o(t_printf save, va_list ap, int *j);
t_printf			ft_format_pct(t_printf save, int *j);
t_printf			ft_format_b(t_printf save, va_list ap, int *j);
char				*ft_mult2(int i, char *tab, char *add);
void				ft_float(long double f, char *tab, int m);
#endif
