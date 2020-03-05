/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:04:34 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 16:39:03 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	*ft_error4(char *str, char *str2, size_t line, size_t col)
{
	ft_printf("Error [%d:%d]: %s: [%s]\n", line, col, str, str2);
	return (NULL);
}

void	*ft_error3(char *str, size_t line, size_t col)
{
	ft_printf("Error [%d:%d]: %s\n", line, col, str);
	return (NULL);
}

void	*ft_error2(char *str, char *str2)
{
	if (str2 == NULL)
		ft_printf("Error: %s\n", str);
	else
		ft_printf("Error: %s %s\n", str, str2);
	return (NULL);
}

int		ft_error(char *str, char *str2)
{
	if (str2 == NULL)
		ft_printf("Error: %s\n", str);
	else
		ft_printf("Error: %s %s\n", str, str2);
	return (FALSE);
}
