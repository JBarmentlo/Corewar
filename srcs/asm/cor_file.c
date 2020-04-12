/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:11:09 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 15:55:38 by dberger          ###   ########.fr       */
/*   Updated: 2020/02/19 18:29:16 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		init_file(t_file *out_file, char *source_file)
{
	int		l;

	l = ft_strlen(source_file);
	if (l < 3 || ft_strcmp(source_file + l - 2, ".s"))
		return ((int)ft_error(WRONG_SOURCE, NULL, NULL));
	out_file->name = ft_memalloc(sizeof(char) * (l + 2));
	out_file->content = ft_memalloc(sizeof(char) * MAX_SIZE_FILE);
	if (out_file->name == NULL || out_file->content == NULL)
		return ((int)ft_error(MALLOC_FAIL, NULL, NULL));
	out_file->name = ft_memcpy(out_file->name, source_file, l - 1); 
	out_file->name = ft_stricat(out_file->name, "cor", l - 1); 
	return (TRUE);
}

int		fill_header(t_file *out_file, t_stack *stack)
{
	int	magic;

	magic = COREWAR_EXEC_MAGIC;
	nb_to_binary(out_file, sizeof(magic), out_file->total_size, magic);
	copy_string(out_file->content, stack->champion_name,  PROG_NAME_LENGTH, &(out_file->total_size));
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	out_file->prog_size = out_file->total_size;
	copy_string(out_file->content, EMPTY,  INFO_PROG, &(out_file->total_size));
	copy_string(out_file->content, stack->comment,  COMMENT_LENGTH, &(out_file->total_size));
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	ft_memdel((void**)&stack->champion_name);
	ft_memdel((void**)&stack->comment);
	return (TRUE);
}

int		fill_opcode(t_file *out_file, t_stack stack)
{
	t_instruct	*op;
	int		i;

	i = out_file->total_size;
	op = stack.first_op;
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
			return ((int)free_op_lab(&stack));
		op = op->next;
	}
	return (TRUE);
}

int		parsing_header(t_stack *stack, int fd, t_s *s)
{
	int	l_name;

	s->line = NULL;
	s->l = 0;
	s->i = 0;
	l_name = PROG_NAME_LENGTH;
	if (!(stack->champion_name = ft_memalloc(sizeof(char) * l_name + 1)))
		return ((int)ft_error(MALLOC_NAME, NULL, NULL));
	if (!(stack->comment = ft_memalloc(sizeof(char) * COMMENT_LENGTH + 1)))
		return ((int)ft_error(MALLOC_COMMENT, NULL, NULL));
	if (!header_content(stack, fd, s))
		return ((int)just_free(stack->champion_name, stack->comment));
	if (!header_content(stack, fd, s))
		return ((int)just_free(stack->champion_name, stack->comment));
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	t_stack		stack;
	int		real_prog_size;
	t_s		s;

	if (parsing_header(&stack, fd, &s) == FALSE)
		return ((int)just_free(s.line, NULL));
	if (init_file(out_file, source_file) == FALSE)
		return ((int)just_free(stack.champion_name, stack.comment));
	if (fill_header(out_file, &stack) == FALSE)
		return ((int)just_free(out_file->name, out_file->content));
	stack.cur_octet = out_file->total_size;
	if (parsing_exec(&stack, fd, &s) == FALSE)
		return ((int)just_free(out_file->name, out_file->content));
	if (fill_opcode(out_file, stack) == FALSE)
		return ((int)just_free(out_file->name, out_file->content));
	real_prog_size = out_file->total_size - SIZE_HEADER;
	nb_to_binary(out_file, INFO_PROG, out_file->prog_size, real_prog_size);
	out_file->total_size -= INFO_PROG;
	out_file->fd = open(out_file->name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	free_op_lab(&stack);
	if (out_file->fd <= 0)
	{
		ft_memdel((void**)&out_file->content);
		return ((int)ft_error(CREATE_FAIL, out_file->name, out_file->name));
	}
	return (TRUE);
}
