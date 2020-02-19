/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:11:09 by dberger           #+#    #+#             */
/*   Updated: 2020/02/19 14:28:59 by ncoursol         ###   ########.fr       */
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
	// Prog size  = 0 pour l'instant + indice de prog size stocke
	// pour s'assurer que c'est pas la taille du programme mais bien son indice//
	out_file->prog_size = out_file->total_size;
	copy_string(out_file->content, EMPTY,  INFO_PROG, &(out_file->total_size));
	//// write comment ///// 
	copy_string(out_file->content, stack->comment,  COMMENT_LENGTH, &(out_file->total_size));
	// padding //
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	return (TRUE);
}

int		fill_opcode(t_file *out_file, t_stack stack)
{
	t_label 	*label;
	t_instruct	*op;
	int			i;

	i = out_file->total_size;
	label = stack.first_label;
	while (label != NULL)
	{
		op = label->first_op;
		while (op != NULL)
		{
			write_in_file(out_file, i, op->type);
			if (g_op_tab[op->type - 1].encoding_byte != 0)
			{
				i++;
				write_in_file(out_file, i, encoding_byte(op));
			}
			i++;
			if (write_op_values(out_file, &i, op, stack) == FALSE)
				return (FALSE);
			op = op->next;
		}
		label = label->next;
	}
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	t_stack		stack;
	int		real_prog_size;
	int		i;

	real_prog_size = 0;
	///////////////////////////////////////////////////////////////////////////
	if (!(stack.champion_name = (char*)malloc(sizeof(char) * PROG_NAME_LENGTH)))
		return (ft_error("\"stack.champion_name\" allocation fail.", NULL));
	if (!(stack.comment = (char*)malloc(sizeof(char) * COMMENT_LENGTH)))
		return (ft_error("\"stack.comment\" allocation fail.", NULL));
	stack.champion_name[PROG_NAME_LENGTH] = '\0';
	stack.comment[COMMENT_LENGTH] = '\0';
	if (!get_header_file(&stack, fd))
		return (ft_error("Bad Header in .s file", NULL));
	if (!get_header_file(&stack, fd))
		return (ft_error("Bad Header in .s file", NULL));
	printf("name : [%s]\n", stack.champion_name);
	printf("comment : [%s]\n", stack.comment);
	///////////////////////////////////////////////////////////////////////////
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
////// to delete: /////// 
	parsing_tester(&stack, fd);
//	print_tester(&stack);
///////////////////////// 
	if (fill_opcode(out_file, stack) == FALSE)
		return (FALSE);
	real_prog_size = out_file->total_size - SIZE_HEADER;
	nb_to_binary(out_file, INFO_PROG, out_file->prog_size, real_prog_size);
	out_file->total_size -= INFO_PROG;
	return (TRUE);
}
