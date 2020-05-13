/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/05/13 20:47:42 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** [out_file] contains the info on the .cor file : it's name and content
** It's name is the same as the .s file
*/

int			init_file(t_file *out_file, char *source_file)
{
	int		l;

	l = ft_strlen(source_file);
	if (l < 2 || ft_strcmp(source_file + l - 2, ".s"))
		return ((intptr_t)ft_error(WRONG_SOURCE, NULL));
	if (!(out_file->name = ft_memalloc(sizeof(char) * (l + 2))))
		return ((intptr_t)ft_error(MALLOC_FAIL, NULL));
	if (!(out_file->content = ft_memalloc(sizeof(char) * SIZE_MAX_PROG)))
	{
		ft_memdel((void**)&out_file->name);
		return ((intptr_t)ft_error(MALLOC_FAIL, NULL));
	}
	out_file->name = ft_memcpy(out_file->name, source_file, l - 1);
	out_file->name = ft_stricat(out_file->name, "cor", l - 1);
	return (TRUE);
}

/*
** A header should contain the name of the champion and it's comment
** We have decided that they could be declared in every order possible.
** The function [header_content] can parse both of those commands
** (name and comment)
** [s->line] will contain the line read by get_next_line
** [s->l] will correspond to the number of line read
** [s->i] will correspond to the number of character read in one line
** [s->l] & [s->i] will help us print detailed error messages
*/

int			parsing_header(t_stack *stack, int fd, t_s *s)
{
	int		l_name;

	s->line = NULL;
	s->l = 0;
	s->i = 0;
	l_name = PROG_NAME_LENGTH;
	if (!(stack->champion_name = ft_memalloc(sizeof(char) * l_name + 1)))
		return ((intptr_t)ft_error(MALLOC_NAME, NULL));
	if (!(stack->comment = ft_memalloc(sizeof(char) * COMMENT_LENGTH + 1)))
	{
		ft_memdel((void**)&stack->champion_name);
		return ((intptr_t)ft_error(MALLOC_COMMENT, NULL));
	}
	if (!header_content(stack, fd, s) && !just_free(s->line, s->gnl->tab))
	{
		ft_memdel((void**)&s->gnl);
		return ((intptr_t)just_free(stack->champion_name, stack->comment));
	}
	if (!header_content(stack, fd, s) && !just_free(s->line, s->gnl->tab))
	{
		ft_memdel((void**)&s->gnl);
		return ((intptr_t)just_free(stack->champion_name, stack->comment));
	}
	s->i = 0;
	return (TRUE);
}

/*
** Once the header is parsed and valid, we can write in [out_file->content]
** the header: the magic number + the champion_name + the padding + the size
** of the exec_code (we don't know it yet so we leave it empty)
** + the champion's comment + the padding
*/

void		fill_header(t_file *out_file, t_stack *stack)
{
	int		ts;
	int		magic;
	char	*name;
	char	*comm;

	magic = COREWAR_EXEC_MAGIC;
	name = stack->champion_name;
	comm = stack->comment;
	nb_to_binary(out_file, sizeof(magic), out_file->total_size, magic);
	ts = out_file->total_size;
	copy_string(out_file->content, name, PROG_NAME_LENGTH, &ts);
	copy_string(out_file->content, EMPTY, PADDING, &ts);
	out_file->prog_size = ts;
	copy_string(out_file->content, EMPTY, INFO_PROG, &ts);
	copy_string(out_file->content, comm, COMMENT_LENGTH, &ts);
	copy_string(out_file->content, EMPTY, PADDING, &ts);
	out_file->total_size = ts;
	ft_memdel((void**)&stack->champion_name);
	ft_memdel((void**)&stack->comment);
}

/*
** Once we have also parsed the exec code, we can write it in
** [out_file->content]. We need to write the [type of the op],
** then it's [encoding byte] if there is one, and finally the
** [value of its arguments] one by one.
*/

int			fill_opcode(t_file *out_file, t_stack stack)
{
	t_instruct	*op;
	int			i;

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
			return ((intptr_t)free_op_lab(&stack));
		op = op->next;
	}
	return (TRUE);
}

/*
** In cor_file: we initialize the content and name of the .cor file,
** parse the header then fill its content in it, parse the exec code,
** then fill the content, and finally we go back to the header to fill
** the program size now that we know the [out_file->total_size].
** Only once the content is valid, we can create the .cor file, and write in
** it in the main function.
*/

int			cor_file(char *source_file, t_file *out_file, int fd)
{
	t_stack		stack;
	int			real_prog_size;
	t_s			s;

	if (init_file(out_file, source_file) == FALSE)
		return (FALSE);
	if (parsing_header(&stack, fd, &s) == FALSE)
		return ((intptr_t)just_free(out_file->name, out_file->content));
	fill_header(out_file, &stack);
	stack.cur_octet = out_file->total_size;
	if (parsing_exec(&stack, fd, &s) == FALSE)
		return ((intptr_t)just_free(out_file->name, out_file->content));
	if (fill_opcode(out_file, stack) == FALSE)
		return ((intptr_t)just_free(out_file->name, out_file->content));
	real_prog_size = out_file->total_size - SIZE_HEADER;
	nb_to_binary(out_file, INFO_PROG, out_file->prog_size, real_prog_size);
	out_file->total_size -= INFO_PROG;
	out_file->fd = open(out_file->name,
					O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	free_op_lab(&stack);
	if (out_file->fd <= 0 && !(ft_error(CREATE_FAIL, out_file->name)))
		return ((intptr_t)just_free(out_file->name, out_file->content));
	return (TRUE);
}
