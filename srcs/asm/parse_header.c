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

int		get_header_file4(t_s *s, char **tmp, int fd)
{
	int		j;
	t_token		token;
	int ret;

	j = 0;
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		tmp[0][j] = s->line[s->i];
		s->i += 1;
		j++;
		if (s->line[s->i] == '\0')
		{
			tmp[0][j] = '\n';
			j++;
			ft_memdel((void**)&s->line);
			ret = get_next_line(fd, &s->line);
			if (ret <= 0 || s->line == NULL)
				return ((int)ft_error_nb(SYNTAXE_ERROR, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
			s->l += 1;
			s->i = 0;
			if (ret == 1 && s->line != NULL && s->line[0] == '\0')
			{
				tmp[0][j] = '\n';
				j++;
				ft_memdel((void**)&s->line);
				ret = get_next_line(fd, &s->line);
				if (ret <= 0 || s->line == NULL)
					return ((int)ft_error_nb(SYNTAXE_ERROR, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
				s->l += 1;
			}
		}
	}
	tmp[0][j] = '\0';
	s->i += 1;
	while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
	{
		if (s->line[s->i] != '\0' && s->line[s->i] != ' ' && s->line[s->i] != '\t')
		{
			token = fill_token(s, 0);
			ft_memdel((void**)&s->line);
			return ((int)ft_error_nb(SYNTAXE_ERROR, token.name, token.line, token.col));
		}
		s->i += 1;
	}
	ft_memdel((void**)&s->line);
	return (TRUE);
}

char	*get_header_file3(int fd, t_s *s, int *type)
{
	char	*tmp;

	tmp = (*type == 0 ? ft_memalloc(sizeof(char) * PROG_NAME_LENGTH) : ft_memalloc(sizeof(char) * COMMENT_LENGTH));
	*type = 0;
	if (s->line[s->i] == '\0')
	{
		ft_memdel((void**)&s->line);
		if (get_next_line(fd, &s->line) <= 0 || !s->line[s->i])
		{
			ft_memdel((void**)&s->line);
			return ((char *)ft_error_nb(INCOMPLETE, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
		}
		*type += 1;
		s->i = 0;
	}
	if (get_header_file4(s, &tmp, fd) == FALSE)
		return (NULL);
	return (tmp);
}

int     get_header_file2(int fd, t_s *s, int *type, t_token *token)
{
	while (get_next_line(fd, &s->line) && s->line != NULL)
	{
		s->l += 1;
		s->i = 0;
		*token = fill_token(s, 0);
		while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR && s->line[s->i] != '.')
		{
			if (s->line[s->i] != ' ' && s->line[s->i] != '\t')
			{
				ft_memdel((void**)&s->line);
				return ((int)ft_error_nb(WRONG_HEADER, token->name, token->line, token->col));
			}
			s->i += 1;
		}
		if (s->line[s->i] == '.')
			break ;
		ft_memdel((void**)&s->line);
	}
	if (s->line == NULL)
	{
		ft_memdel((void**)&s->line);
		return ((int)ft_error_nb(INCOMPLETE, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
	}
	*type = s->line[s->i + 1];
	*token = fill_token(s, 0);
	if (*type == 'n')
	{
		if (ft_strncmp(s->line + s->i, NAME_CMD_STRING, 5) < 0)
		{	
			ft_memdel((void**)&s->line);
			return ((int)ft_error_nb(WRONG_HEADER, token->name, token->line, token->col));
		}
	}
	else if (*type == 'c')
	{
		if (ft_strncmp(s->line + s->i, COMMENT_CMD_STRING, 8) < 0)
		{
			ft_memdel((void**)&s->line);
			return ((int)ft_error_nb(WRONG_HEADER, token->name, token->line, token->col));
		}
	}
	*token = fill_token(s, 0);
	s->i += (*type == 'n' ? 5 : 8);
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		if (s->line[s->i] != ' ' && s->line[s->i] != '\t')
		{
			ft_memdel((void**)&s->line);
			return ((int)ft_error_nb(WRONG_FORMAT, token->name, token->line, token->col));
		}
		s->i += 1;
	}
	if (s->line[s->i] != '"')
	{
		ft_memdel((void**)&s->line);
		return ((int)ft_error_nb(WRONG_FORMAT, token->name, token->line, token->col));
	}
	s->i += 1;
	return (TRUE);
}

int     get_header_file(t_stack *stack, int fd, t_s *s)
{
	int     type;
	char	*tmp;
	int	save;
	t_token token;

	stack->nb_lines = 0;
	s->i = 0;
	if (get_header_file2(fd, s, &type, &token) == FALSE)
		return (FALSE);
	stack->nb_lines += s->l;
	save = type;
	tmp = get_header_file3(fd, s, &type);
	if (tmp == NULL)
		return (0);
	stack->nb_lines += type;
	s->l += type;
	type = save;
	if (stack->nb_lines == FALSE)
		return (0);
	if (type == 'n')
	{
		if (ft_strlen(tmp) > PROG_NAME_LENGTH)
		{
			ft_memdel((void**)&s->line);
			ft_memdel((void**)&tmp);
			return ((int)ft_error("Command [.name] too long", NULL));
		}
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	}
	else if (type == 'c')
	{
		if (ft_strlen(tmp) > COMMENT_LENGTH)
		{
			ft_memdel((void**)&s->line);
			ft_memdel((void**)&tmp);
			return ((int)ft_error("Command [.comment] too long", NULL));
		}
		stack->comment = ft_strcpy(stack->comment, tmp);
	}
	else
	{
		ft_memdel((void**)&s->line);
		ft_memdel((void**)&tmp);
		return ((int)ft_error_nb(INVALID_COMMAND, token.name, token.line, token.col));
	}
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&s->line);
	return (1);
}
