/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:35:36 by dberger           #+#    #+#             */
/*   Updated: 2020/05/07 16:56:19 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** We create a .cor that will be filled only once all the parsing has been done
** [source_file] is the argument containing the .s file to read
** [out_file] will have the content, name and info on the .cor file
*/

int		fill_out_file(char *source_file, t_file *out_file, int fd)
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

int		main(int ac, char **av)
{
	int		fd;
	t_file	out_file;

	if (ac == 0)
		return ((intptr_t)ft_error(NO_ARGS, NULL));
	if (ac == 1)
		return (usage(PROG_ASM));
	if (ac > 2)
		return ((intptr_t)ft_error(TOO_MUCH_ARGS, NULL));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return ((intptr_t)ft_error(OPEN_FAIL, av[1]));
	if (fill_out_file(av[1], &out_file, fd) == FALSE)
		return (FALSE);
	return (TRUE);
}

/*
**__attribute__((destructor)) void test()
**{
**  while(1);
**}
*/
