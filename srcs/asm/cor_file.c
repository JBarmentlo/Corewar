/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:29:48 by dberger           #+#    #+#             */
/*   Updated: 2020/02/06 17:22:00 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		init_file(t_file *out_file, char *source_file, int i)
{
	out_file->total_size = 0;
	out_file->prog_size = 0;
	out_file->name = ft_memalloc(i + 4);
	out_file->content = ft_memalloc(MAX_SIZE_FILE);
	out_file->name = ft_memcpy(out_file->name, source_file, i + 1); 
	out_file->name = ft_stricat(out_file->name, "cor", i + 1); 
	out_file->fd = open(out_file->name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (out_file->fd <= 0)
		return (ft_error("Can't create the file", out_file->name));
	return (TRUE);
}

int		fill_header(t_file *out_file, int fd)
{
	(void)fd;
// write magic number//
	nb_to_binary(out_file, sizeof(COREWAR_EXEC_MAGIC), out_file->total_size, COREWAR_EXEC_MAGIC);
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	int		i;

	(void) fd;
	i = 0;
	while (source_file[i] && source_file[i] != '.')
		i++;
	if (source_file[i] == '\0' || source_file[i + 1] == '\0' || source_file[i + 1] != 's' || source_file[i + 2] != '\0')
		return (ft_error("Wrong source file format", NULL));
	if (init_file(out_file, source_file, i) == FALSE)
		return (FALSE);
	if (fill_header(out_file, fd) == FALSE)
		return (FALSE);
	return (TRUE);
}
