/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:14:08 by dberger           #+#    #+#             */
/*   Updated: 2020/04/28 09:37:13 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/*
**	This function is a type of 'get_next_line' adapted: we read the necessary
** 	ammount of octets (we know a file should not exceed the size of a header
**	plus the CHAMP_MAX_SIZE). If the file is bigger than this amount or smaller
** 	than a header, it is an error. if not we will copy it in a string called
**	'prog'.
*/

int			stock_file(t_champion *champ)
{
	int		ret;
	char	buf[SIZE_MAX_PROG + 1];
	uint	min_header;

	ret = read(champ->fd, buf, SIZE_MAX_PROG);
	buf[ret] = '\0';
	min_header = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + PADDING;
	min_header += INFO_SIZE_CODE + COMMENT_LENGTH + PADDING + 1;
	champ->header.prog_size = ret - min_header + 1;
	if ((uint)ret < min_header)
		return ((intptr_t)ft_error(TOO_SMALL, NULL));
	ft_memcpy(champ->prog, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return ((intptr_t)ft_error(TOO_BIG, NULL));
	return (TRUE);
}

/*
** This function allows us to transform 4 bytes of a string who's ascii
** number in hexadecimal correspond to (for example): [00][ea][83][f3],
** into a number equals to 00ea83f3.
*/

int32_t		string_to_int(t_champion *champ, int size, int i)
{
	int		k;
	int32_t nb;
	int32_t n;

	k = 0;
	nb = 0;
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

/*
** Here we stock the 'name' of the program in champ->name, we don't
** need to check what is in it, we just know it is contained in the 128 bytes
** (+4 bytes of padding) following the magic number. After the name comes the
** size of the code: it is a number, written on 4 bytes, the should indicates
** the size in octet that occupies the code section. So it is should be equal
** to the size of the entire file (prog_size) minus the size of the header.
** Finally comes the comment and its padding that we just need to stock.
*/

int			name_size_comment(t_champion *champ)
{
	int		i;
	uint	nb;
	int		total_name;
	int		total_comment;

	total_name = PROG_NAME_LENGTH + PADDING;
	total_comment = COMMENT_LENGTH + PADDING;
	i = sizeof(COREWAR_EXEC_MAGIC);
	ft_bzero(champ->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(champ->header.comment, COMMENT_LENGTH + 1);
	ft_memcpy(champ->header.prog_name, champ->prog + i, total_name);
	nb = string_to_int(champ, INFO_SIZE_CODE, i + total_name);
	if (nb != champ->header.prog_size)
		return ((intptr_t)ft_error(WRONG_PROG_SIZE, NULL));
	i += total_name + INFO_SIZE_CODE;
	ft_memcpy(champ->header.comment, champ->prog + i, total_comment);
	return (TRUE);
}

/*
** In this section, we check if the info contained at the beggining of the
** binary file, called the header, are correct and we stock them, if necessary,
** in our structure t_champion.
*/

int			pars_header(t_champion *champ)
{
	int		nb;

	ft_bzero(champ->prog, SIZE_MAX_PROG);
	if (stock_file(champ) == FALSE)
		return (FALSE);
	nb = string_to_int(champ, sizeof(COREWAR_EXEC_MAGIC), 0);
	if (nb != COREWAR_EXEC_MAGIC)
		return ((intptr_t)ft_error(WRONG_MAGIC_NB, NULL));
	else
		champ->header.magic = nb;
	if (name_size_comment(champ) == FALSE)
		return (FALSE);
	champ->alive = 1;
	champ->exists = 1;
	champ->total_process = 1;
	return (TRUE);
}
