/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:39:38 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 14:22:36 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;
	t_list	*link;

	if (!lst || !f)
		return (NULL);
	if (!(new = f(lst)))
		return (NULL);
	start = ft_lstnew(new->content, new->content_size);
	link = start;
	lst = lst->next;
	while (lst)
	{
		new = f(lst);
		link->next = ft_lstnew(new->content, new->content_size);
		link = link->next;
		lst = lst->next;
	}
	return (start);
}
