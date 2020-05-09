/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/05/07 16:46:17 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Once we have encountered our second quote, we want to make sure the
** rest of the line is empty or is a comment [#][;].
*/

int		check_after_quote(t_s *s, t_token *token)
{
	s->i += 1;
	while (diff(s->line[s->i], COMM))
	{
		if (diff(s->line[s->i], SPACE))
		{
			if (fill_token(s, 0, token))
				return ((intptr_t)token_free(SYNTAXE_ERROR, token));
			return (FALSE);
		}
		s->i += 1;
	}
	ft_memdel((void**)&s->line);
	return (TRUE);
}

int		fill_empty_line(t_s *s, int fd)
{
	int		ret;
	t_token	token;

	token.name = NULL;
	token.line = s->l;
	token.col = s->i;
	ft_memdel((void**)&s->line);
	ret = gnl(fd, &s->line, s);
	if (ret <= 0 || s->line == NULL)
		return ((intptr_t)token_free(MISSING_QUOTE, &token));
	s->l += 1;
	s->i = 0;
	return (TRUE);
}

/*
** Everytime we encounter a '\0' we need to call get_next_line again to see if
** there is any character left to read.
*/

int		check_empty_line(t_s *s, char **tmp, int fd)
{
	if (s->line[s->i] == '\0')
	{
		if (fill_empty_line(s, fd) == FALSE)
			return ((intptr_t)just_free(*tmp, NULL));
		while (s->line != NULL && s->line[0] == '\0')
			if (fill_empty_line(s, fd) == FALSE)
				return ((intptr_t)just_free(*tmp, NULL));
	}
	return (TRUE);
}

/*
** In [get_header_content] we are reading a line after encounting a valid
** command, and it's first quote. We are accepting content of commands with
** ["\n"] in it, which is why we have a special function [check_empty_line]
** to keep calling [get_next_line] in case we still haven't encountered the
** second quote ["].
*/

char	*get_header_content(int fd, t_s *s, int *type)
{
	char	*tmp;
	int		j;
	t_token	token;

	j = 0;
	init_token(&token);
	tmp = *type == 0 ? ft_memalloc(sizeof(char) * PROG_NAME_LENGTH)
			: ft_memalloc(sizeof(char) * COMMENT_LENGTH);
	if (tmp == NULL)
		return ((char*)ft_error(MALLOC_FAIL, NULL));
	*type = 0;
	if (check_empty_line(s, &tmp, fd) == FALSE)
		return (FALSE);
	while (s->line && s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		tmp[j] = s->line[s->i];
		s->i += 1;
		j++;
		if (check_empty_line(s, &tmp, fd) == FALSE)
			return (FALSE);
	}
	tmp[j] = '\0';
	if (check_after_quote(s, &token) == FALSE)
		return (just_free(tmp, NULL));
	return (tmp);
}

/*
** In [get_command_type] we are parsing the command type: if it is [.name] or
** [.comment] of none of that.
** Once we have a valid type of command, we can parse it's content [tmp]. It
** should start and end with quotes ["].
** In fill_name_com we check if this content does not overcome the size
** established in [op.h]: PROG_NAME_LENGTH or COMMENT_LENGTH.
*/

int		header_content(t_stack *stack, int fd, t_s *s)
{
	char	*tmp;
	int		type;
	int		save;
	t_token token;

	s->i = 0;
	tmp = NULL;
	init_token(&token);
	if (get_command_type(fd, s, &type, &token) == FALSE)
		return (FALSE);
	save = type;
	if (!(tmp = get_header_content(fd, s, &type)))
		return (FALSE);
	s->l += type;
	type = save;
	if (s->l == FALSE)
		return (FALSE);
	if (fill_name_com(type, tmp, stack, &token) == FALSE)
		return ((intptr_t)just_free(tmp, NULL));
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&s->line);
	return (TRUE);
}
