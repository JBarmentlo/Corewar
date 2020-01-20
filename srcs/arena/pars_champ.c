/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:40:55 by dberger           #+#    #+#             */
/*   Updated: 2020/01/20 16:48:54 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		ft_stock_file(t_champion *champ)
{
	int		ret;
	char	buf[BUF_TOT + 1];

	ret = 0;
	ret = read(champ->fd, buf, BUF_TOT);
	buf[ret] = '\0';
	champ->size = ret;
	ft_memcpy(champ->file, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return (error("ERROR", NULL));
	return (TRUE);
}

int		magic_number(t_champion *champ)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_printf("[%x]", champ->file[i] & 0xff);
		i++;
	}
	ft_printf("\n");
	return (TRUE);
}	

int		pars_champ(t_arena *vm, int indx)
{
	t_champion	champ;

	champ = vm->champion_table[indx];
	ft_bzero(champ.file, BUF_TOT);
	if (ft_stock_file(&champ) == FALSE)
		return (FALSE);
	if (magic_number(&champ) == FALSE)
		return (FALSE); 
	return (TRUE);
}
