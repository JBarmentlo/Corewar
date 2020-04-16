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

#include "libft.h"

char		*ft_after_line(char *x, char *tab)
{
	char	*tmp;

	if (!(tmp = ft_strdup(x + 1)))
		return (NULL);
	free(tab);
	tab = tmp;
	return (tab);
}

int			ft_content(t_list *link, int fd, char **line)
{
	int		ret;
	char	*x;
	t_fd	*gnl;
	char	buf[BUFF_SIZE + 1];

	gnl = (t_fd*)link->content;
	ret = 0;
	while (!(x = ft_strchr(gnl->tab, '\n'))
			&& (ret = read(fd, buf, BUFF_SIZE)) && buf[0] != '\0')
	{
		buf[ret] = '\0';
		gnl->tab = ft_strjoin_f(gnl->tab, buf, 1);
	}
	if (!(ft_strlen(gnl->tab)))
		return (ret == 0 ? 0 : 1);
	if (x)
	{
		*line = ft_strsub(gnl->tab, 0, (x - gnl->tab));
		gnl->tab = ft_after_line(x, gnl->tab);
		return (1);
	}
	*line = gnl->tab;
	gnl->tab = ft_strdup("");
	return (ret == 0 && !gnl->tab ? 0 : 1);
}

t_list		*ft_search_fd(int fd, t_list **begin)
{
	t_list	*new;
	t_list	*link;
	t_fd	gnl;

	link = *begin;
	while (link && fd != ((t_fd*)link->content)->fd)
		link = link->next;
	if (link)
		return (link);
	gnl.tab = ft_strdup("");
	gnl.fd = fd;
	if (!(new = ft_lstnew(&gnl, sizeof(t_fd))))
		return (NULL);
	if (!*begin)
		*begin = new;
	else
	{
		link = *begin;
		*begin = new;
		new->next = link;
	}
	return (new);
}

void		ft_del(t_list *link, t_list **begin)
{
	t_list	*tmp;
	t_list	*prev;

	prev = 0;
	tmp = *begin;
	while (tmp && tmp != link)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (!prev)
		*begin = (*begin)->next;
	else
		prev->next = tmp->next;
	free(((t_fd*)tmp->content)->tab);
	free(((t_fd*)tmp->content));
	free(tmp);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*begin = NULL;
	t_list			*link;
	int				ret;
	t_list			buf[0];

	if (read(fd, buf, 0) == -1)
		return (-1);
	if (fd < 0 || BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!(link = ft_search_fd(fd, &begin)))
		return (-1);
	if (!(ret = ft_content(link, fd, line)))
	{
		ft_del(link, &begin);
		return (0);
	}
	return (1);
}
