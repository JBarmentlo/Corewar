/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:35:36 by dberger           #+#    #+#             */
/*   Updated: 2020/02/05 18:30:23 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int ac, char **av)
{
	int		fd;
	t_file	out_file;

	fd = 0;
	if (ac == 0)
		return (ft_error("no arguments", NULL));
	if (ac == 1)
		usage(PROG_ASM);
	if (ac > 2)
		return (ft_error("too many arguments", NULL));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error("a problem occured while opening the source file", NULL));
	if (create_file(av[1], &out_file, fd) == FALSE)
		return (FALSE);
	if (start_content(&out_file, fd) == FALSE)
		return (FALSE);
	ft_printf("Writing output program to %s\n", out_file.name);
	return (TRUE);	
}
