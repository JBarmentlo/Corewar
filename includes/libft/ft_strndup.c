/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:38:45 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 15:07:40 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t k)
{
	char	*dup;

	if (!(dup = (char*)malloc(sizeof(*dup) * (k + 1))))
		return (NULL);
	ft_strncpy(dup, src, k);
	dup[k] = '\0';
	return (dup);
}
