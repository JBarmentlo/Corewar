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

int		empty_line(t_s *s, char **tmp, int fd, int *j)
{
	int	ret;

	tmp[0][*j] = '\n';
	*j += 1;
	ft_memdel((void**)&s->line);
	ret = get_next_line(fd, &s->line);
	if (ret <= 0 || s->line == NULL)
		return ((int)ft_error_nb(SYNTAXE_ERROR, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
	s->l += 1;
	s->i = 0;
	return (TRUE);
}

int		get_header_file4(t_s *s, char **tmp, int fd)
{
	int		j;
	t_token		token;

	j = 0;
	token.name = NULL;
	if (s->line[s->i] == '\0')
	{
		if (empty_line(s, tmp, fd, &j) == FALSE)
			return ((int)asm_free(*tmp, NULL, NULL));
		while (s->line != NULL && s->line[0] == '\0')
			if (empty_line(s, tmp, fd, &j) == FALSE)
				return ((int)asm_free(*tmp, NULL, NULL));
	}
	while (s->line && s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		tmp[0][j] = s->line[s->i];
		s->i += 1;
		j++;
		if (s->line[s->i] == '\0')
		{
			if (empty_line(s, tmp, fd, &j) == FALSE)
				return ((int)asm_free(*tmp, NULL, NULL));
			while (s->line != NULL && s->line[0] == '\0')
				if (empty_line(s, tmp, fd, &j) == FALSE)
					return ((int)asm_free(*tmp, NULL, NULL));
		}
	}
	tmp[0][j] = '\0';
	s->i += 1;
	while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
	{
		if (s->line[s->i] != '\0' && s->line[s->i] != ' ' && s->line[s->i] != '\t' && fill_token(s, 0, &token))
			return ((int)free_error(SYNTAXE_ERROR, &token, *tmp));
		s->i += 1;
	}
	ft_memdel((void**)&s->line);
	return (TRUE);
}

char	*get_header_file3(int fd, t_s *s, int *type)
{
	char *tmp;

	tmp = *type == 0 ? ft_memalloc(sizeof(char) * PROG_NAME_LENGTH) : ft_memalloc(sizeof(char) * COMMENT_LENGTH);
	if (tmp == NULL)
		return ((char*)ft_error("Can't allocate memory for [tmp]", NULL, NULL));
	*type = 0;
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
		fill_token(s, 0, token);
		while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR && s->line[s->i] != '.')
		{
			if (s->line[s->i] != ' ' && s->line[s->i] != '\t' && fill_token(s, 0, token))
				return ((int)free_error(WRONG_HEADER, token, NULL));
			s->i += 1;
		}
		if (s->line[s->i] == '.')
			break ;
		ft_memdel((void**)&s->line);
		ft_memdel((void**)&token->name);
	}
//	ft_memdel((void**)&token->name);
	if (s->line == NULL)
		return ((int)ft_error_nb(INCOMPLETE, "(null)", s->l > 0 ? s->l + 1 : 0, 0));
	*type = s->line[s->i + 1];
	fill_token(s, 0, token);
	if (*type == 'n')
	{
		if (ft_strncmp(s->line + s->i, NAME_CMD_STRING, 5) != 0)
			return ((int)free_error(WRONG_HEADER, token, NULL));
	}
	else if (*type == 'c')
	{
		if (ft_strncmp(s->line + s->i, COMMENT_CMD_STRING, 8) != 0)
			return ((int)free_error(WRONG_HEADER, token, NULL));
	}
	else
		return ((int)free_error(INVALID_COMMAND, token, NULL)); // token name ??
//	ft_memdel((void**)&token->name);
	fill_token(s, 0, token);
	s->i += (*type == 'n' ? 5 : 8);
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		if (s->line[s->i] != ' ' && s->line[s->i] != '\t')
			return ((int)free_error(WRONG_FORMAT, token, NULL));
		s->i += 1;
	}
	if (s->line[s->i] != '"')
		return ((int)free_error(WRONG_FORMAT, token, NULL));
	s->i += 1;
	ft_memdel((void**)&token->name);
	return (TRUE);
}

int     get_header_file(t_stack *stack, int fd, t_s *s)
{
	int     type;
	char	*tmp;
	int	save;
	t_token token;

	s->i = 0;
	token.name = NULL;
	if (get_header_file2(fd, s, &type, &token) == FALSE)
		return (FALSE);
	save = type;
	if (!(tmp = get_header_file3(fd, s, &type)))
		return (0);
	s->l += type;
	type = save;
	if (s->l == FALSE)
		return (0);
	if (type == 'n')
	{
		if (ft_strlen(tmp) > PROG_NAME_LENGTH)
			return ((int)free_error(TOO_LONG_NAME, &token, tmp));
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	}
	else if (type == 'c')
	{
		if (ft_strlen(tmp) > COMMENT_LENGTH)
			return ((int)free_error(TOO_LONG_COM, &token, tmp));
		stack->comment = ft_strcpy(stack->comment, tmp);
	}
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&s->line);
	return (TRUE);
}
