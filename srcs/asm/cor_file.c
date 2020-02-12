/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:29:48 by dberger           #+#    #+#             */
/*   Updated: 2020/02/12 16:20:14 by dberger          ###   ########.fr       */
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

int		fill_header(t_file *out_file, int fd, t_stack *stack)
{
	(void)fd;
	// write magic number//
	nb_to_binary(out_file, sizeof(COREWAR_EXEC_MAGIC), out_file->total_size, COREWAR_EXEC_MAGIC);
	// write name//
	copy_string(out_file->content, stack->champion_name,  PROG_NAME_LENGTH, &(out_file->total_size));
	// padding //
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	// Prog size  = 0 pour l'instant + indice de prog size stocke en negatif
	// pour s'assurer que c'est pas la taille du programme mais bien son indice//
	out_file->prog_size = out_file->total_size * (-1);
	copy_string(out_file->content, EMPTY,  INFO_PROG, &(out_file->total_size));
	//// write comment ///// 
	copy_string(out_file->content, stack->comment,  COMMENT_LENGTH, &(out_file->total_size));
	// padding //
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	t_stack		stack;
	int		i;

	stack.champion_name = "zork";
	stack.comment = "I'M ALIIIIVE";
	i = 0;
	while (source_file[i] && source_file[i] != '.')
		i++;
	if (source_file[i] == '\0' || source_file[i + 1] == '\0' || source_file[i + 1] != 's' || source_file[i + 2] != '\0')
		return (ft_error("Wrong source file format", NULL));
	if (init_file(out_file, source_file, i) == FALSE)
		return (FALSE);
	if (fill_header(out_file, fd, &stack) == FALSE)
		return (FALSE);
	stack.cur_octet = out_file->total_size;
	ft_printf("stack->cur_octet = %d\n", stack.cur_octet);
	parsing_tester(&stack, fd);
	ft_printf("zjump = [%d]\n", find_opcode("zjmp"));
	return (TRUE);
}
