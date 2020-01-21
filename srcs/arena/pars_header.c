/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:14:08 by dberger           #+#    #+#             */
/*   Updated: 2020/01/21 15:19:11 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

int			stock_file(t_champion *champ)
{
	int		ret;
	char	buf[SIZE_MAX_PROG + 1];
	int		min_header;

	ret = 0;
	ret = read(champ->fd, buf, SIZE_MAX_PROG);
	buf[ret] = '\0';
	champ->prog_size = ret;
	min_header = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + PADDING;
	min_header += INFO_SIZE_CODE + COMMENT_LENGTH + PADDING + 1;
	if (champ->prog_size < min_header)
		return (error("The source file too small", NULL));
	ft_memcpy(champ->prog, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return (error("The source file too big", NULL));
	return (TRUE);
}

int32_t		string_to_int(t_champion *champ, int size, int i)
{
	int		k;
	int32_t nb;
	int32_t n;

	k = 0;
	nb = 0;
	n = 0;
	while (k < size)
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
		k++;
	}
	return (nb);
}

int			name_size_comment(t_champion *champ)
{
	int		i;
	int		nb;
	int		total_name;
	int		total_comment;
	int		size_header;

	total_name = PROG_NAME_LENGTH + PADDING;
	total_comment = COMMENT_LENGTH + PADDING;
	i = sizeof(COREWAR_EXEC_MAGIC);
	size_header = i + total_name + INFO_SIZE_CODE + total_comment;
	ft_bzero(champ->name, total_name);
	ft_bzero(champ->comment, total_comment);
	ft_memcpy(champ->name, champ->prog + i, total_name);
	nb = string_to_int(champ, INFO_SIZE_CODE, i + total_name);
	if (nb != (champ->prog_size - size_header))
		return (error("Wrong instruction section size in header", NULL));
	i += total_name + INFO_SIZE_CODE;
	ft_memcpy(champ->comment, champ->prog + i, total_comment);
	return (TRUE);
}

int			pars_header(t_arena *vm, int indx)
{
	t_champion	champ;
	int			nb;

	champ = vm->champion_table[indx];
	ft_bzero(champ.prog, SIZE_MAX_PROG);
	if (stock_file(&champ) == FALSE)
		return (FALSE);
	nb = string_to_int(&champ, sizeof(COREWAR_EXEC_MAGIC), 0);
	if (nb != COREWAR_EXEC_MAGIC)
		return (error("The magic number isn't correct", NULL));
	if (name_size_comment(&champ) == FALSE)
		return (FALSE);
	return (TRUE);
}
