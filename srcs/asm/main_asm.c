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

int	fill_out_file(char *source_file, t_file *out_file, int fd)
{
	out_file->fd = 0;
	out_file->name = NULL;
	out_file->content = NULL;
	out_file->total_size = 0;
	out_file->prog_size = 0;
	if (cor_file(source_file, out_file, fd) == FALSE)
		return (FALSE);
	write(out_file->fd, out_file->content, out_file->total_size);
	ft_printf("Writing output program to %s\n", out_file->name);
	just_free(out_file->name, out_file->content);
	return (TRUE);
}

int	main(int ac, char **av)
{
	int		fd;
	t_file		out_file;

	if (ac == 0)
		return ((int)ft_error(NO_ARGS, NULL, NULL));
	if (ac == 1)
		return (usage(PROG_ASM));
	if (ac > 2)
		return ((int)ft_error(TOO_MUCH_ARGS, NULL, NULL));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return ((int)ft_error(OPEN_FAIL, av[1], NULL));
	if (fill_out_file(av[1], &out_file, fd) == FALSE)
		return (FALSE);
	return (TRUE);	
}

/*
__attribute__((destructor)) void test()
{
	while(1);
}*/
