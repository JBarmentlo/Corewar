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

void	*asm_free(void *to_free1, void *to_free2, void *to_free3)
{
	if (to_free1 != NULL)
		ft_memdel((void**)&to_free1);
	if (to_free2 != NULL)
		ft_memdel((void**)&to_free2);
	if (to_free3 != NULL)
		ft_memdel((void**)&to_free3);
	return (NULL);
}
		
void	*token_free(char *str, t_token *token, void *to_free)
{
	if (token->name != NULL)
		ft_printf("Error [%d:%d]: %s: [%s]\n", token->line, token->col, str, token->name);
	else
		ft_printf("Error [%d:%d]: %s\n", token->line, token->col, str);
	ft_memdel((void**)&token->name);
	if (to_free != NULL)
		ft_memdel((void**)&to_free);
	return (NULL);
}
