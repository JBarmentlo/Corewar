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

int		get_header_file4(char **line, int *i, char **tmp, int fd)
{
	int		j;

	j = 0;
	while (line[0][*i] != '\0' && line[0][*i] != '"')
	{
		tmp[0][j] = line[0][*i];
		*i += 1;
		j++;
		if (line[0][*i] == '\0')
		{
			tmp[0][j] = '\n';
			j++;
			ft_memdel((void**)line);
			if (get_next_line(fd, line) <= 0 || !*line)
				return (0);
			*i = 0;
		}
	}
	tmp[0][j] = '\0';
	*i += 1;
	while (line[0][*i] != '\0' && line[0][*i] != COMMENT_CHAR && line[0][*i] != ALT_COMMENT_CHAR)
	{
		if (line[0][*i] != '\0' && line[0][*i] != ' ' && line[0][*i] != '\t')
			return ((int)ft_error("6 Wrong header .command format : ", *line));
		*i += 1;
	}
	ft_memdel((void**)line);
	return (1);
}

char	*get_header_file3(int fd, char **line, int *i, int *type)
{
	char	*tmp;

	tmp = (*type == 0 ? ft_memalloc(sizeof(char) * PROG_NAME_LENGTH) : ft_memalloc(sizeof(char) * COMMENT_LENGTH));
	*type = 0;
	if (line[0][*i] == '\0')
	{
		ft_memdel((void**)line);
		if (get_next_line(fd, line) <= 0 || !*line)
			return (NULL);
		*type += 1;
		*i = 0;
	}
	if (get_header_file4(line, i, &tmp, fd) == FALSE)
		return (NULL);
	return (tmp);
}

size_t     get_header_file2(int fd, char **line, int *i, int *type)
{
	size_t		lines;

	lines = 0;
	while (get_next_line(fd, line) && *line)
	{
		lines += 1;
		*i = 0;
		while (line[0][*i] != '\0' && line[0][*i] != COMMENT_CHAR && line[0][*i] != ALT_COMMENT_CHAR && line[0][*i] != '.')
		{
			if (line[0][*i] != ' ' && line[0][*i] != '\t')
				return ((int)ft_error("5 Wrong header .command format : ", *line));
			*i += 1;
		}
		if (line[0][*i] == '.')
			break ;
		ft_memdel((void**)line);
	}
	*type = line[0][*i + 1];
	if (*type == 'n')
	{
		if (ft_strncmp(*line + *i, NAME_CMD_STRING, 5) < 0)
			return ((int)ft_error("4 Wrong header .command format : ", *line));
	}
	else if (*type == 'c')
		if (ft_strncmp(*line + *i, COMMENT_CMD_STRING, 8) < 0)
			return ((int)ft_error("3 Wrong header .command format : ", *line));
	*i += (*type == 'n' ? 5 : 8);
	while (line[0][*i] != '\0' && line[0][*i] != '"')
	{
		if (line[0][*i] != ' ' && line[0][*i] != '\t')
			return ((int)ft_error("2 Wrong header .command format : ", *line));
		*i += 1;
	}
	if (line[0][*i] != '"')
		return ((int)ft_error("1 Wrong header .command format : ", *line));
	*i += 1;
	return (lines);
}

int     get_header_file(t_stack *stack, int fd)
{
	char    *line;
	int     i;
	int     type;
	char	*tmp;
	int		save;

	line = NULL;
	stack->nb_lines = 1;
	stack->nb_lines += get_header_file2(fd, &line, &i, &type);
	if (stack->nb_lines == FALSE)
		return (FALSE);
	save = type;
	tmp = get_header_file3(fd, &line, &i, &type);
	if (tmp == NULL)
	{
		ft_memdel((void**)&line);
		return (0);
	}
	stack->nb_lines += type;
	type = save;
	if (stack->nb_lines == FALSE)
	{
		ft_memdel((void**)&line);
		return (0);
	}
	if (type == 'n' && ft_strlen(tmp) < PROG_NAME_LENGTH)
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	else if (type == 'c' && ft_strlen(tmp) < COMMENT_LENGTH)
		stack->comment = ft_strcpy(stack->comment, tmp);
	else
		return ((int)ft_error(".Command too long", NULL));
	ft_memdel((void**)&tmp);
	return (1);
}
