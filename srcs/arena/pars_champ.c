/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:40:55 by dberger           #+#    #+#             */
/*   Updated: 2020/01/20 17:52:25 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int		ft_stock_file(t_champion *champ)
{
	int		ret;
	char	buf[BUF_TOT + 1];
	int		min_header;

	ret = 0;
	ret = read(champ->fd, buf, BUF_TOT);
	buf[ret] = '\0';
	champ->size = ret;
	min_header = sizeof(COREWAR_EXEC_MAGIC);
	min_header += PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + 1;
	if (champ->size < min_header)
		return (error("ERROR: wrong file format", NULL));
	ft_memcpy(champ->file, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return (error("ERROR", NULL));
	return (TRUE);
}

int		magic_number(t_champion *champ)
{
	int		i;
	int		s;
	int32_t nb;
	int32_t n;

	i = 0;
	nb = 0;
	n = 0;
	s = sizeof(COREWAR_EXEC_MAGIC);
	while (i < s)
	{
		if (nb == 0)
			nb = champ->file[i] & 0xff;
		else
		{
			nb = nb << 8;
			n = champ->file[i] & 0xff;
			nb = nb | n;
		}
		i++;
	}
	if (nb != COREWAR_EXEC_MAGIC)
		return (FALSE);
	ft_printf("numero magique = %d, nb=%d\n", COREWAR_EXEC_MAGIC, nb);
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
