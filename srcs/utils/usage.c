/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:21:51 by dberger           #+#    #+#             */
/*   Updated: 2020/01/30 15:48:00 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		usage(int prog)
{
	int		fd;
	char	*line;

	line = NULL;
	if (prog == COREWAR)
		fd = open("./srcs/utils/usage_corewar.txt", O_RDONLY);
	else
		fd = open("./srcs/utils/usage_asm.txt", O_RDONLY);
	if (fd >= 0)
	{
		while (get_next_line(fd, &line))
		{
			ft_printf("%s\n", line);
			ft_memdel((void **)&(line));
		}
	}
	return (FALSE);
}
