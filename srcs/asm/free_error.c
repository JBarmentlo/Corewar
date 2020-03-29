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

#include "asm.h"

void	*free_error(char *str, t_token *token)
{
	ft_printf("Error [%d:%d]: %s: [%s]\n", token->line, token->col, str, token->name);
	return (NULL);
}
