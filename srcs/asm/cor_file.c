/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:29:48 by dberger           #+#    #+#             */
/*   Updated: 2020/02/12 16:00:17 by dberger          ###   ########.fr       */
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

t_instruct		*is_instruct(char *line, int i)
{
	t_instruct	*op;
	char	*op_code;
	int		k;
	int		save;

	k = 0;
	save = i;
	ft_printf("line[%d] = [%c]\n", i, line[i]);
	op = malloc(sizeof(t_instruct));
	while (ft_isalnum(line[i]) == 1)
	{
		i++;
		k++;
	}
	op_code = malloc(sizeof(char) * k);
	op_code = ft_memcpy(op_code, line + save, k);
	ft_printf("op_code = [%s]\n", op_code);
	op->type = find_opcode(op_code);
	ft_printf("op->type = [%d]\n", op->type);
	return (op);
}

int		is_label(int fd, char *line, t_stack *stack)
{
	t_label		*label;
	t_instruct *op;	
	int			ln;
	int			i;

	(void) fd;
	i = 0;
	ln = 0;
	label = malloc(sizeof(t_label));
	label->oct = stack->cur_octet;
	label->nb_instructs= 0;
	label->op = NULL;
	label->first_op = NULL;
	if (stack->first_label == NULL && stack->label_list == NULL)
	{
		stack->first_label = label;
		stack->label_list = label;
	}
	while (line[i] != '\0')
	{
		if (ln == 0 && line[i] == ':')
		{
			label->name = (char*)malloc(sizeof(char) * i);
			label->name = ft_memcpy(label->name, line, i);
			ft_printf("label name = [%s]\n", label->name);
			ln = 1;
			i++;
		}
		if (ln == 1 && ft_isalpha(line[i]) == 1)
		{
			label->nb_instructs += 1;
			op = is_instruct(line, i);
			if (label->op == NULL && label->first_op == NULL)
			{
				label->op = op;
				label->first_op = op;
			}
			break;
		}
		i++;
	}
	
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	t_stack		stack;
	char		*line;
	int		i;

	i = 0;
	stack.first_label = NULL;
	stack.label_list = NULL;
	while (get_next_line(fd, &line))
	{
		if (i == 3)
			break;
		i++;
	}
	ft_printf("line n%d = [%s]\n", i, line);
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
	if (is_label(fd, line, &stack) == FALSE)
		return (FALSE);
	ft_printf("zjump = [%d]\n", find_opcode("zjmp"));
	return (TRUE);
}
