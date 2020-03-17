/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:04:34 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 16:02:55 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_error_nb(char *str, char *str2, size_t line, size_t col)
{
	if (str2 == NULL)
		ft_printf("Error [%d:%d]: %s\n", line, col, str);
	else
		ft_printf("Error [%d:%d]: %s: [%s]\n", line, col, str, str2);
	return (NULL);
}

void	*ft_error(char *str, char *str2)
{
	if (str2 == NULL)
		ft_printf("Error: %s\n", str);
	else
		ft_printf("Error: %s %s\n", str, str2);
	return (NULL);
}
