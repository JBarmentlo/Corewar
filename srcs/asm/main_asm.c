/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:35:36 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 13:06:44 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int ac, char **av)
{
	int		fd;
	t_file	out_file;

	fd = 0;
	if (ac == 0)
		return (ft_error("No arguments", NULL));
	if (ac == 1)
		return (usage(PROG_ASM));
	if (ac > 2)
		return (ft_error("Too many arguments", NULL));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("A problem occured while opening the source file:", av[1]));
	if (cor_file(av[1], &out_file, fd) == FALSE)
		return (FALSE);
	write(out_file.fd, out_file.content, out_file.total_size);
	ft_printf("Writing output program to %s\n", out_file.name);
	return (TRUE);	
}
