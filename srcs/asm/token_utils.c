/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:23:19 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 16:09:25 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** The last token takes the info of the current token, and the current token
** takes the name of the op_code (usefull for error_messages).
*/

void	*save_token(t_token *token, t_token *last_token, char *str_op, t_s *s)
{
	int	dif;

	dif = token->end - token->col;
	last_token->line = token->line;
	last_token->col = token->col;
	last_token->end = token->end;
	last_token->op_type = token->op_type;
	if (last_token->name != NULL)
		ft_memdel((void**)&last_token->name);
	if (!(last_token->name = ft_memalloc(sizeof(char) * dif + 1)))
		return (NULL);
	last_token->name = ft_strcpy(last_token->name, token->name);
	ft_memdel((void**)&token->name);
	if (!(token->name = ft_memalloc(sizeof(char) * ft_strlen(str_op))))
		return (NULL);
	token->name = ft_strcpy(token->name, str_op);
	token->line = s->l;
	token->col = s->i;
	return (token);
}

void	init_token(t_token *token)
{
	token->name = NULL;
	token->line = 0;
	token->col = 0;
}

/*
** Here we free the token to then update it. it corresponds to the characters
** we are currently reading (s->i) until we find a space or tab, or comment,
** or end of file The option "42" is a special one for labels or direct
** arguments (we don't want the token to contain the LABEL_CHAR of the
** DIRECT_CHAR).
*/

int		fill_token(t_s *s, int op_type, t_token *token)
{
	int	save;

	save = s->i;
	if (token->name != NULL)
		ft_memdel((void**)&token->name);
	while (s->line != NULL && diff(s->line[save], SPACE_COMM)
		&& s->line[save] != SEPARATOR_CHAR)
	{
		if (op_type == 42
		&& (s->line[save] == LABEL_CHAR || s->line[save] == DIRECT_CHAR))
			break ;
		save++;
	}
	if (save - s->i > 0)
	{
		if (!(token->name = ft_memalloc(sizeof(char *) * (save - s->i + 1))))
			return ((intptr_t)ft_error(MALLOC_FAIL, NULL));
		token->name = ft_strncat(token->name, s->line + s->i, (save - s->i));
	}
	token->line = s->l;
	token->col = s->i;
	token->end = save;
	token->op_type = op_type;
	return (TRUE);
}
