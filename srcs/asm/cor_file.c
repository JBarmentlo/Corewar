/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:29:48 by dberger           #+#    #+#             */
/*   Updated: 2020/02/11 15:08:54 by dberger          ###   ########.fr       */
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
	int		i;

	(void) fd;
	//////////////////////////NICO MODIFICATIONS///////////////////////////
	t_stack		stack;
	t_label		*save;

	save = stack.label_list;
	stack.champion_name = "zork";
	stack.comment = "I'M ALIIIIVE";
	stack.label_list->name = "l2";
	stack.label_list->opt = (char**)malloc(sizeof(char*) * 2);
	stack.label_list->opt[0] = (char*)malloc(sizeof(char) * 19);
	stack.label_list->opt[0] = "sti r1, %:live, %1\0";
	stack.label_list->opt[1] = (char*)malloc(sizeof(char) * 15);
	stack.label_list->opt[1] = "and r1, %0, r1\0";
	stack.label_list = stack.label_list->next;
	stack.label_list->name = "live";
	stack.label_list->opt = (char**)malloc(sizeof(char*) * 2);
	stack.label_list->opt[0] = (char*)malloc(sizeof(char) * 8);
	stack.label_list->opt[0] = "live %1\0";
	stack.label_list->opt[1] = (char*)malloc(sizeof(char) * 12);
	stack.label_list->opt[1] = "zjmp %:live\0";
	stack.label_list = save;
	//////////////////////////////////////////////////////////////////////
	i = 0;
	while (source_file[i] && source_file[i] != '.')
		i++;
	if (source_file[i] == '\0' || source_file[i + 1] == '\0' || source_file[i + 1] != 's' || source_file[i + 2] != '\0')
		return (ft_error("Wrong source file format", NULL));
	if (init_file(out_file, source_file, i) == FALSE)
		return (FALSE);
	if (fill_header(out_file, fd, &stack) == FALSE)
		return (FALSE);
	ft_printf("zjump = [%d]\n", find_opcode("zjmp"));

	/*
	** CODE
	*/
/*
	while (a.label_list)
	{
	
		a.label_list
	}
*/	///////////////////////////////////////////////////////////////////////
	return (TRUE);
}
