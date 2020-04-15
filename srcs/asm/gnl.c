/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:47:44 by dberger           #+#    #+#             */
/*   Updated: 2020/01/14 11:30:50 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*after_line(char *x, char *tab, int size)
{
	char	*tmp;

	if (!(tmp = ft_memalloc(sizeof(char) * size + 1)))
		return (NULL);
	tmp[size] = '\0';
	tmp = ft_memcpy(tmp, x + 1, size);
	ft_memdel((void**)&tab);
	tab = tmp;
	return (tab);
}

char	*strjoin_f(char const *s1, char const *s2, int l, int ret)
{
	char	*str;
	int i;
	int j;

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

int			content(t_fd *gnl, int fd, char **line)
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
		gnl->tab = after_line(x, gnl->tab, gnl->fd);
		return (1);
	}
	*line = gnl->tab;
	gnl->tab = ft_strdup("");
	return (ret == 0 && !gnl->tab ? 0 : 1);
}

int			gnl(int fd, char **line)
{
	int			ret;
	t_list			buf[0];
	static 	t_fd		*gnl = NULL;

	if (read(fd, buf, 0) == -1)
		return (-1);
	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!gnl)
	{
		gnl = ft_memalloc(sizeof(t_fd));
		gnl->tab = ft_strdup("");
		gnl->fd = 0;
	}
	if (!(ret = content(gnl, fd, line)))
	{
		ft_memdel((void**)&gnl->tab);
		ft_memdel((void**)&gnl);
		return (0);
	}
	return (1);
}
