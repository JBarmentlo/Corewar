/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/05/06 22:31:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Once the command is valid, and it's content has the right format, we want to
** make sure it doesn't exceed the required size.
*/

int		fill_name_com(int type, char *tmp, t_stack *stack, t_token *token)
{
	if (type == 'n')
	{
		if (ft_strlen(tmp) > PROG_NAME_LENGTH)
			return ((intptr_t)token_free(TOO_LONG_NAME, token));
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	}
	else if (type == 'c')
	{
		if (ft_strlen(tmp) > COMMENT_LENGTH)
			return ((intptr_t)token_free(TOO_LONG_COM, token));
		stack->comment = ft_strcpy(stack->comment, tmp);
	}
	return (TRUE);
}

/*
** If the first letter comming after [.] is name, the next 4 letter should be
** name, same thing withe "comment", if it is none of that, it is an invalid
** command
*/

int		is_valid_command_start(t_s *s, int *type, t_token *token)
{
	if (fill_token(s, 0, token) == FALSE)
		return (FALSE);
	if (*type == 'n')
	{
		if (ft_strncmp(s->line + s->i, NAME_CMD_STRING, 5) != 0)
			return ((intptr_t)token_free(WRONG_HEADER, token));
	}
	else if (*type == 'c')
	{
		if (ft_strncmp(s->line + s->i, COMMENT_CMD_STRING, 8) != 0)
			return ((intptr_t)token_free(WRONG_HEADER, token));
	}
	else
		return ((intptr_t)token_free(INVALID_COMMAND, token));
	return (TRUE);
}

/*
** After encounting on of the two valid commands, we should only find
** spaces or a quote.
*/

int		is_valid_command_end(t_s *s, int *type, t_token *token)
{
	if (fill_token(s, 0, token) == FALSE)
		return (FALSE);
	s->i += (*type == 'n' ? 5 : 8);
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		if (diff(s->line[s->i], SPACE) == TRUE)
		{
			if (fill_token(s, 0, token))
				return ((intptr_t)token_free(WRONG_FORMAT, token));
			return (FALSE);
		}
		s->i += 1;
	}
	if (s->line[s->i] != '"')
		return ((intptr_t)token_free(WRONG_FORMAT, token));
	s->i += 1;
	ft_memdel((void**)&token->name);
	return (TRUE);
}

/*
** We read the .s file line by line, and stock the characters in [s->line]
** A command can only be [.name] or [.comment]
** The token help us print the error if there is one. If [is_valid_start]
** is true it means the begining of the command is correct, and in
** [is_valid_end] we check if the characters comming after a command
** like [.name] are only spaces or a quote.
*/

int		get_command_type(int fd, t_s *s, int *type, t_token *token)
{
	while (gnl(fd, &s->line, s) && s->line != NULL)
	{
		s->l += 1;
		s->i = 0;
		if (fill_token(s, 0, token) == FALSE)
			return (FALSE);
		while (diff(s->line[s->i], COMM) && s->line[s->i] != '.')
		{
			if (!(fill_token(s, 0, token)))
				return (FALSE);
			if (diff(s->line[s->i], SPACE) == TRUE)
				return ((intptr_t)token_free(WRONG_HEADER, token));
			s->i += 1;
		}
		if (s->line[s->i] == '.')
			break ;
		just_free(s->line, token->name);
	}
	if (s->line == NULL && (token->line += 1))
		return ((intptr_t)token_free(INCOMPLETE, token));
	*type = s->line[s->i + 1];
	if (is_valid_command_start(s, type, token) == FALSE
		|| is_valid_command_end(s, type, token) == FALSE)
		return (FALSE);
	return (TRUE);
}
