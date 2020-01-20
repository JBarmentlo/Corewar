/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:40:55 by dberger           #+#    #+#             */
/*   Updated: 2020/01/20 19:43:37 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"
#include <stdio.h>

int		ft_stock_file(t_champion *champ)
{
	int		ret;
	char	buf[BUF_TOT + 1];
	int		min_header;

	ret = 0;
	ret = read(champ->fd, buf, BUF_TOT);
	buf[ret] = '\0';
	champ->prog_size = ret;
	min_header = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH;
	min_header +=  PADDING + 4 + COMMENT_LENGTH + PADDING + 1;
	if (champ->prog_size < min_header)
		return (error("ERROR: file too small", NULL));
	ft_memcpy(champ->prog, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return (error("ERROR: file too big", NULL));
	return (TRUE);
}

int		magic_number(t_champion *champ)
{
	int		i;
	int		s;
	uint32_t nb;
	int32_t n;

	i = 0;
	nb = 0;
	n = 0;
	s = sizeof(COREWAR_EXEC_MAGIC);
/*	nb =*(uint32_t*)champ->prog;
	while (i < 4)
	{
		printf("[%02hhx] ", ((char*)&nb)[i]);
		i++;
	}
	ft_printf("BEFORE numero magique = %d, nb=%d\n", COREWAR_EXEC_MAGIC, nb);
	printf("\n");
	i = 0;
	n = COREWAR_EXEC_MAGIC;
	printf("\n");
	while (i < 4)
	{
		printf("[%02hhx] ", ((char*)&n)[i]);
		i++;
	}
	n = 0;
	i = 0;*/
	while (i < s)
	{
		if (nb == 0)
			nb = champ->prog[i] & 0xff;
		else
		{
			nb = nb << 8;
			n = champ->prog[i] & 0xff;
			nb = nb | n;
		}
		i++;
	}
	if (nb != COREWAR_EXEC_MAGIC)
		return (FALSE);
	ft_printf("numero magique = %d, nb=%d\n", COREWAR_EXEC_MAGIC, nb);
	return (TRUE);
}

void	champ_name_comment(t_champion *champ)
{
	int		i;

	i = sizeof(COREWAR_EXEC_MAGIC);
	ft_bzero(champ->name, PROG_NAME_LENGTH + PADDING);
	ft_bzero(champ->comment, COMMENT_LENGTH + PADDING);
	ft_memcpy(champ->name, champ->prog + i, PROG_NAME_LENGTH + PADDING); 
	i += PROG_NAME_LENGTH + PADDING + 4;
	ft_memcpy(champ->comment, champ->prog + i, COMMENT_LENGTH + PADDING); 
}

int		pars_champ(t_arena *vm, int indx)
{
	t_champion	champ;

	champ = vm->champion_table[indx];
	ft_bzero(champ.prog, BUF_TOT);
	if (ft_stock_file(&champ) == FALSE)
		return (FALSE);
	if (magic_number(&champ) == FALSE)
		return (FALSE); 
	champ_name_comment(&champ);
	ft_printf("name = [%s]\n", champ.name);
	ft_printf("comment = [%s]\n", champ.comment);
	return (TRUE);
}
