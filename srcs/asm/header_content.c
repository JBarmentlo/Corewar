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

int		fill_empty_line(t_s *s, char **tmp, int fd, int *j)
{
	int	ret;
	t_token	token;

	init_token(&token);
	token.line += 1;
	(*tmp)[*j] = '\n';
	*j += 1;
	ft_memdel((void**)&s->line);
	ret = get_next_line(fd, &s->line);
	if (ret <= 0 || s->line == NULL)
		return ((int)token_free(SYNTAXE_ERROR, &token));
	s->l += 1;
	s->i = 0;
	return (TRUE);
}

int	check_empty_line(t_s *s, char **tmp, int fd, int *j)
{
	if (s->line[s->i] == '\0')
	{
		if (fill_empty_line(s, tmp, fd, j) == FALSE)
			return ((int)just_free(*tmp, NULL));
		while (s->line != NULL && s->line[0] == '\0')
			if (fill_empty_line(s, tmp, fd, j) == FALSE)
				return ((int)just_free(*tmp, NULL));
	}
	return (TRUE);
}

int		check_after_quote(t_s *s, t_token *token)
{

	s->i += 1;
	while (diff(s->line[s->i], COMM))
	{
		if (diff(s->line[s->i], SPACE))
		{
			fill_token(s, 0, token);
			return ((int)token_free(SYNTAXE_ERROR, token));
		}
		s->i += 1;
	}
	ft_memdel((void**)&s->line);
	return (TRUE);
}

char	*get_header_content(int fd, t_s *s, int *type)
{
	char	*tmp;
	int	j;
	t_token	token;

	j = 0;
	init_token(&token);
	tmp = *type == 0 ? ft_memalloc(sizeof(char) * PROG_NAME_LENGTH)
			: ft_memalloc(sizeof(char) * COMMENT_LENGTH);
	if (tmp == NULL)
		return ((char*)ft_error(MALLOC_FAIL, NULL, NULL));
	*type = 0;
	if (check_empty_line(s, &tmp, fd, &j) == FALSE)
		return (FALSE);
	while (s->line && s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		tmp[j] = s->line[s->i];
		s->i += 1;
		j++;
		if (check_empty_line(s, &tmp, fd, &j) == FALSE)
			return (FALSE);
	}
	tmp[j] = '\0';
	if (check_after_quote(s, &token) == FALSE)
		return (just_free(tmp, NULL));
	return (tmp);
}

int     header_content(t_stack *stack, int fd, t_s *s)
{
	int     type;
	char	*tmp;
	int	save;
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
		return ((int)just_free(tmp, NULL));
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&s->line);
	return (TRUE);
}
