/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:37:21 by ncoursol          #+#    #+#             */
/*   Updated: 2019/09/23 15:23:52 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_printf	ft_check_add(t_printf save, int *j, char c)
{
	if (*j == BUFF_SZ && (*j = 0) == 0)
	{
		save.ret = save.ret + BUFF_SZ;
		write(1, &save.buf, BUFF_SZ);
	}
	save.buf[*j] = c;
	*j += 1;
	return (save);
}
