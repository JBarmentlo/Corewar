/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 23:29:32 by ncoursol          #+#    #+#             */
/*   Updated: 2019/07/05 11:51:27 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(const char *s1, const char *s2, int *a)
{
	if (*a == 1 || *a == 3)
		free((char*)s1);
	if (*a == 2 || *a == 3)
		free((char*)s2);
}

char	*ft_strjoin_f(char const *s1, char const *s2, int a)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	ft_free(s1, s2, &a);
	return (str);
}
