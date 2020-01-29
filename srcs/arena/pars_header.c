/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:14:08 by dberger           #+#    #+#             */
/*   Updated: 2020/01/23 15:48:16 by dberger          ###   ########.fr       */
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
	int		min_header;

	ret = 0;
	ret = read(champ->fd, buf, SIZE_MAX_PROG);
	buf[ret] = '\0';
	champ->prog_size = ret;
	min_header = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + PADDING;
	min_header += INFO_SIZE_CODE + COMMENT_LENGTH + PADDING + 1;
	if (champ->prog_size < min_header)
		return (ft_error("The source file too small", NULL));
	ft_memcpy(champ->prog, buf, ret);
	if ((ret = read(champ->fd, buf, 2)))
		return (ft_error("The source file too big", NULL));
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

/*
** Here we stock the 'name' of the program in champ->name, we don't
** need to check what is in it, we just know it is contained in the 128 bytes
** (+4 bytes of padding) following the magic number. After the name comes the
** size of the code: it is a number, written on 4 bytes, the should indicates
** the size in octet that occupies the code section. So it is should be equal
** to the size of the entire file (prog_size) minus the size of the header.
** Finally comes the comment and it's padding that we just need to stock.
*/

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
		return (ft_error("Wrong instruction section size in header", NULL));
	i += total_name + INFO_SIZE_CODE;
	ft_memcpy(champ->comment, champ->prog + i, total_comment);
	return (TRUE);
}

/*
** In this section, we check if the info contained at the beggining of the
** binary file, called the header, are correct and we stock them, if necessary,
** in our structure t_champion.
*/

int			pars_header(t_champion *champ)
{
	int			nb;

	ft_bzero(champ->prog, SIZE_MAX_PROG);
	if (stock_file(champ) == FALSE)
		return (FALSE);
	nb = string_to_int(champ, sizeof(COREWAR_EXEC_MAGIC), 0);
	if (nb != COREWAR_EXEC_MAGIC)
		return (ft_error("The magic number isn't correct", NULL));
	if (name_size_comment(champ) == FALSE)
		return (FALSE);
	return (TRUE);
}
