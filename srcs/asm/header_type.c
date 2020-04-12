/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/09 16:05:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	fill_name_com(int type, char *tmp, t_stack *stack, t_token *token)
{
	if (type == 'n')
	{
		if (ft_strlen(tmp) > PROG_NAME_LENGTH)
			return ((int)token_free(TOO_LONG_NAME, token));
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	}
	else if (type == 'c')
	{
		if (ft_strlen(tmp) > COMMENT_LENGTH)
			return ((int)token_free(TOO_LONG_COM, token));
		stack->comment = ft_strcpy(stack->comment, tmp);
	}
	return (TRUE);
}

int	is_valid_command_start(t_s *s, int *type, t_token *token)
{
	fill_token(s, 0, token);
	if (*type == 'n')
	{
		if (ft_strncmp(s->line + s->i, NAME_CMD_STRING, 5) != 0)
			return ((int)token_free(WRONG_HEADER, token));
	}
	else if (*type == 'c')
	{
		if (ft_strncmp(s->line + s->i, COMMENT_CMD_STRING, 8) != 0)
			return ((int)token_free(WRONG_HEADER, token));
	}
	else
		return ((int)token_free(INVALID_COMMAND, token));
	return (TRUE);
}

int	is_valid_command_end(t_s *s, int *type, t_token *token)
{
	fill_token(s, 0, token);
	s->i += (*type == 'n' ? 5 : 8);
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		if (diff(s->line[s->i], SPACE) == TRUE)
			return ((int)token_free(WRONG_FORMAT, token));
		s->i += 1;
	}
	if (s->line[s->i] != '"')
		return ((int)token_free(WRONG_FORMAT, token));
	s->i += 1;
	ft_memdel((void**)&token->name);
	return (TRUE);
}

int     get_command_type(int fd, t_s *s, int *type, t_token *token)
{
	while (get_next_line(fd, &s->line) && s->line != NULL)
	{
		s->l += 1;
		s->i = 0;
		fill_token(s, 0, token);
		while ((diff(s->line[s->i], COMM) == TRUE)
			&& s->line[s->i] != '.')
		{
			if ((diff(s->line[s->i], SPACE) == TRUE)
				&& fill_token(s, 0, token))
				return ((int)token_free(WRONG_HEADER, token));
			s->i += 1;
		}
		if (s->line[s->i] == '.')
			break ;
		ft_memdel((void**)&s->line);
		ft_memdel((void**)&token->name);
	}
	if (s->line == NULL && (token->line += 1))
		return ((int)token_free(INCOMPLETE, token));
	*type = s->line[s->i + 1];
	if (is_valid_command_start(s, type, token) == FALSE)
		return (FALSE);
	if (is_valid_command_end(s, type, token) == FALSE)
		return (FALSE);
	return (TRUE);
}
