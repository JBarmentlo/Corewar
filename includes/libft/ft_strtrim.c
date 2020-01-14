/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:57:19 by dberger           #+#    #+#             */
/*   Updated: 2019/04/11 16:31:37 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	int				end;

	if (!s)
		return (NULL);
	start = 0;
	end = (int)ft_strlen(s) - 1;
	while ((s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		&& s[start])
		start++;
	while ((s[end] == ' ' || s[end] == '\t' || s[end] == '\n') && s[end]
		&& end > (int)start)
		end--;
	return (ft_strsub(s, start, (end - start + 1)));
}
