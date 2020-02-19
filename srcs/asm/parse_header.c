/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/02/19 14:18:10 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_header_file4(char **line, int *i)
{
	*i += 1;
	while (line[0][*i] != '\0' && line[0][*i] != '#')
	{
		if (line[0][*i] != '\0' && line[0][*i] != ' ' && line[0][*i] != '\t')
			return (ft_error("Wrong header .command format : ", *line));
		*i += 1;
	}
	ft_memdel((void**)line);
	return (1);
}

char	*get_header_file3(int fd, char **line, int *i, int type)
{
	char	*tmp;
	int		j;

	j = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (type == 0 ? 128 : 2048))))
		return (NULL);
	if (line[0][*i] == '\0')
	{
		ft_memdel((void**)line);
		if (get_next_line(fd, line) <= 0 || !*line)
			return (NULL);
		*i = 0;
	}
	while (line[0][*i] != '\0' && line[0][*i] != '"')
	{
		tmp[j] = line[0][*i];
		*i += 1;
		j++;
		if (line[0][*i] == '\0')
		{
			ft_memdel((void**)line);
			if (get_next_line(fd, line) <= 0 || !*line)
				return (NULL);
			*i = 0;
		}
	}
	tmp[j] = '\0';
	get_header_file4(line, i);
	return (tmp);
}

int     get_header_file2(int fd, char **line, int *i, int *type)
{
	while (get_next_line(fd, line) && *line)
	{
		*i = 0;
		while (line[0][*i] != '\0' && line[0][*i] != '#' && line[0][*i] != '.')
		{
			if (line[0][*i] != ' ' && line[0][*i] != '\t')
				return (ft_error("Wrong header .command format : ", *line));
			*i += 1;
		}
		if (line[0][*i] == '.')
			break ;
		ft_memdel((void**)line);
	}
	*type = line[0][*i + 1];
	if (*type == 'n')
	{
		if (ft_strncmp(*line + *i, ".name", 5) < 0)
			return (ft_error("Wrong header .command format : ", *line));
	}
	else if (*type == 'c')
		if (ft_strncmp(*line + *i, ".comment", 8) < 0)
			return (ft_error("Wrong header .command format : ", *line));
	*i += (*type == 'n' ? 5 : 8);
	while (line[0][*i] != '\0' && line[0][*i] != '"')
	{
		if (line[0][*i] != ' ' && line[0][*i] != '\t')
			return (ft_error("Wrong header .command format : ", *line));
		*i += 1;
	}
	if (line[0][*i] != '"')
		return (ft_error("Wrong header .command format : ", *line));
	*i += 1;
	return (1);
}

int     get_header_file(t_stack *stack, int fd)
{
	char    *line;
	int     i;
	int     type;
	char	*tmp;

	line = NULL;
	if (!get_header_file2(fd, &line, &i, &type) || (tmp = get_header_file3(fd, &line, &i, type)) == NULL)
	{
		ft_memdel((void**)&line);
		return (0);
	}
	if (type == 'n' && ft_strlen(tmp) < PROG_NAME_LENGTH)
		stack->champion_name = ft_strcpy(stack->champion_name, tmp);
	else if (type == 'c' && ft_strlen(tmp) < COMMENT_LENGTH)
		stack->comment = ft_strcpy(stack->comment, tmp);
	else
		return (ft_error(".Command too long : ", tmp));
	ft_memdel((void**)&tmp);
	return (1);
}