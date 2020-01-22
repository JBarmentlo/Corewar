/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 16:44:01 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/17 17:05:19 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_zero(char *add, int size)
{
	int		i;

	i = 0;
	while (size >= 0)
	{
		if (add[i] < '0' || add[i] > '9')
			add[i] = '0';
		i++;
		size--;
	}
	return (ft_strrev(add));
}

char	*ft_check_rest2(char *add, char *tab, int *rest, int *j)
{
	tab[*j] = ((tab[*j] == '\0') ? '0' : tab[*j]);
	add[*j] = ((add[*j] == '\0' && *j == 0) ? '0' : add[*j]);
	add[*j] += *rest;
	if (((add[*j] - '0') + (tab[*j] - '0')) > 9)
	{
		*rest = (((add[*j] - '0') + (tab[*j] - '0')) / 10);
		tab[*j] = ((((add[*j] - '0') + (tab[*j] - '0')) % 10) + '0');
	}
	else if ((*rest = 0) == 0)
		tab[*j] = (((add[*j] - '0') + (tab[*j] - '0')) + '0');
	*j -= 1;
	if (*rest != 0 && *j < 0)
	{
		*j = 0;
		while (tab[*j])
			*j += 1;
		*j += 1;
		while ((*j -= 1) > 0)
			tab[*j] = tab[*j - 1];
		tab[*j] = (*rest + '0');
		*j -= 1;
	}
	return (tab);
}

char	*ft_add2(char *add, char *tab)
{
	int		j;
	int		rest;

	j = 0;
	rest = 0;
	if (tab[0] == '1' && tab[1] == '\0')
		tab[0] = '\0';
	while (add[j])
		j++;
	while (j >= 0)
		tab = ft_check_rest2(add, tab, &rest, &j);
	return (tab);
}

char	*ft_check_rest1(char *add, int *j, int *rest, int *k)
{
	if (((add[*j] - '0') * 5) + *rest > 9)
	{
		*k = *rest;
		*rest = ((((add[*j] - '0') * 5) + *rest) / 10);
		add[*j] = ((((add[*j] - '0') * 5) + *k) % 10) + '0';
	}
	else
	{
		add[*j] = (((add[*j] - '0') * 5) + *rest) + '0';
		*rest = 0;
	}
	*j -= 1;
	if (*rest != 0 && *j < 0)
	{
		*j = 0;
		while (add[*j])
			*j += 1;
		*j += 1;
		while ((*j -= 1) > 0)
			add[*j] = add[*j - 1];
		add[0] = (*rest + '0');
		*j = -1;
	}
	return (add);
}

char	*ft_mult2(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;
	int		l;

	l = i;
	ft_bzero(add, 5000);
	while (i >= 0)
	{
		j = 0;
		rest = 0;
		add[j] = (add[j] == '\0') ? '1' : add[j];
		while (add[j + 1])
			j++;
		while (j >= 0)
			add = ft_check_rest1(add, &j, &rest, &k);
		i--;
	}
	add = ft_zero(ft_strrev(add), l);
	return (ft_add2(add, tab));
}
