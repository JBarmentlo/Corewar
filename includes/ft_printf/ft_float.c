/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 10:26:09 by ncoursol          #+#    #+#             */
/*   Updated: 2019/06/17 19:02:42 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_add(char *add, char *tab)
{
	int		j;
	int		k;
	int		rest;

	j = 0;
	k = 0;
	rest = 0;
	while (add[k + 1])
		k++;
	while (j <= k)
	{
		tab = ft_check_rest(add, tab, &rest, &j);
		if (rest != 0 && j > k)
		{
			j = 0;
			while (tab[j])
				j++;
			tab[j] = (rest + '0');
			j = k + 1;
		}
	}
	return (ft_strrev(tab));
}

char	*ft_check_rest3(char *add, int *rest, int *j, int *k)
{
	if (((add[*j] - '0') * 2) + *rest > 9)
	{
		*k = *rest;
		*rest = ((((add[*j] - '0') * 2) + *rest) / 10);
		add[*j] = ((((add[*j] - '0') * 2) + *k) % 10) + '0';
	}
	else
	{
		add[*j] = (((add[*j] - '0') * 2) + *rest) + '0';
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

char	*ft_mult(int i, char *tab, char *add)
{
	int		rest;
	int		k;
	int		j;

	ft_bzero(add, 5000);
	while (i > 0)
	{
		j = 0;
		rest = 0;
		add[j] = (add[j] == '\0') ? '1' : add[j];
		while (add[j + 1])
			j++;
		while (j >= 0)
			add = ft_check_rest3(add, &rest, &j, &k);
		i--;
	}
	add[0] = (add[0] == '\0') ? '1' : add[0];
	return (ft_add(ft_strrev(add), ft_strrev(tab)));
}

char	*ft_float2(unsigned long long bin, char *tab, int size, int m)
{
	char				add[5000];
	int					i;
	int					j;

	i = 0;
	j = (m == 1) ? -1 : size;
	if (m == 1)
	{
		while (j++ < size)
		{
			if (((bin >> j) & 1) == 1)
				tab = ft_mult(j, tab, add);
			ft_bzero(add, 5000);
		}
		j = -1;
	}
	while (j >= 0)
	{
		if (((bin >> j) & 1) == 1)
			tab = ft_mult2(i, tab, add);
		ft_bzero(add, 5000);
		i++;
		j--;
	}
	return (tab);
}

void	ft_float(long double f, char *tab, int m)
{
	unsigned long long	*nb;
	unsigned long long	ent;
	unsigned long long	vir;
	int					p;

	nb = (unsigned long long*)&f;
	p = (nb[1] & 0x7FFF) - 16382;
	ent = nb[0] >> (64 - p);
	vir = (p < 0) ? ent : nb[0] << p;
	if (m == 1)
		tab = ft_float2(ent, tab, p + 1, 1);
	else
		tab = ft_float2(vir, tab, 63, 2);
	if (f < 0 && m == 1)
	{
		p = 0;
		while (tab[p])
			p++;
		while (p > 0)
		{
			tab[p] = tab[p - 1];
			p--;
		}
		tab[0] = '-';
	}
}
