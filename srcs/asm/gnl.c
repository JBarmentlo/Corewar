/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:47:44 by dberger           #+#    #+#             */
/*   Updated: 2020/05/07 16:42:24 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*after_line(char *x, char *tab, int size)
{
	char	*tmp;

	if (!(tmp = ft_memalloc(sizeof(char) * size + 1)))
	{
		ft_memdel((void**)&tab);
		return (NULL);
	}
	tmp[size] = '\0';
	tmp = ft_memcpy(tmp, x + 1, size);
	ft_memdel((void**)&tab);
	return (tmp);
}

/*
** This strjoin_f is special because it can copy "\0" in the file,
** because we use [l] (size of the current [gnl->tab], so [s1]), and [ret]
** (size of the new [buf], so s2), instead of using a [ft_strlen]
** Finally this function free s1 (since it has copied it in str).
*/

char	*strjoin_f(char const *s1, char const *s2, int l, int ret)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(*str) * (l + ret + 1))))
		return (NULL);
	str[l + ret] = '\0';
	while (i < l)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < ret)
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	ft_memdel((void**)&s1);
	return (str);
}

/*
** In content, we check if [gnl->tab] is empty or does not contain any "\n"
** If so, we call the function read and join the new characters read from
** [buf] to [gnl->tab].
** If we have encounter a "\n", [x] will corresponds to [gnl->tab] starting from
** the "\n". So the [line] we want to send is the beggining of [gnl->tab]
** to the beggining of [x] (x - gnl->tab + 1). The [+1] helps us keep the "\n"
** Then we remove the part sent in [line] from [gnl->tab] in [after_line].
*/

int		content(t_fd *gnl, int fd, char **line)
{
	int		ret;
	char	*x;
	char	buf[BUFF_SIZE + 1];

	ret = 0;
	while (!(x = ft_strchr(gnl->tab, '\n'))
			&& (ret = read(fd, buf, BUFF_SIZE)) && buf[0] != '\0')
	{
		buf[ret] = '\0';
		gnl->tab = strjoin_f(gnl->tab, buf, gnl->fd, ret);
		gnl->fd += ret;
	}
	if (!(ft_strlen(gnl->tab)))
		return (ret == 0 ? 0 : 1);
	if (x)
	{
		*line = ft_strsub(gnl->tab, 0, (x - gnl->tab + 1));
		gnl->fd -= x - gnl->tab + 1;
		if (!(gnl->tab = after_line(x, gnl->tab, gnl->fd)))
			return (0);
		return (1);
	}
	*line = gnl->tab;
	gnl->tab = ft_strdup("");
	return (ret == 0 && !gnl->tab ? 0 : 1);
}

/*
** This is a homemade gnl, that could be reused later: it sends the [line]
** wwith the "\n" at the end, and it reads "\0" and stock them in [line]
*/

int		gnl(int fd, char **line, t_s *s)
{
	int				ret;
	t_list			buf[0];
	static t_fd		*gnl = NULL;

	if (read(fd, buf, 0) == -1)
		return (-1);
	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!gnl)
	{
		if (!(gnl = ft_memalloc(sizeof(t_fd))))
			return (0);
		gnl->tab = ft_strdup("");
		gnl->fd = 0;
	}
	if (!(ret = content(gnl, fd, line)))
		return (0);
	s->gnl = gnl;
	return (1);
}
