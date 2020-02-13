/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:13 by dberger           #+#    #+#             */
/*   Updated: 2020/02/13 19:33:45 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_argz		is_argument(char *line, int *i, size_t inst_type, t_argz argz)
{
	int		k;
	int		save;

	k = 0;
	if (line[*i] == 'r')
	{
		argz.type = REG_CODE;
		argz.oct = 1;
	}
	else if (line[*i] == '%')
	{
		argz.type = DIR_CODE;
		if (g_op_tab[inst_type - 1].is_direct_small == 1)
			argz.oct = 2;
		else
			argz.oct = 4;
	}
	else
	{
		argz.type = IND_CODE;
		argz.oct = 2;
	}
	*i += 1;
	if (line[*i] != ':')
	{
		argz.value = ft_atoi(line + *i);
		argz.lab = NULL;
		while (line[*i] != ',' && line[*i])
			*i += 1;
	}
	else
	{
		save = *i;
		while (line[*i] && line[*i] != ',')
		{
			*i += 1;
			k++;
		}
		argz.lab = (char*)malloc(sizeof(char) * k);
		argz.lab = ft_memcpy(argz.lab, line + save, k);
		argz.value = 0;
	}
	return (argz);
}

t_instruct		*is_instruct(char *line, int *i, int *cur_octet)
{
	t_instruct	*op;
	char		*op_code;
	int			k;
	int			w;
	int			save;
	t_argz		argz;

	k = 0;
	w = 0;
	save = *i;
	op = malloc(sizeof(t_instruct));
	while (ft_isalnum(line[*i]) == 1)
	{
		*i += 1;
		k++;
	}
	op_code = (char*)malloc(sizeof(char) * k);
	ft_bzero(op_code, k);
	while (save < *i && w < k)
	{
		op_code[w] = line[save];
		w++;
		save++;
	}
	op_code[w] = '\0';
	op->type = find_opcode(op_code);
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	k = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] != ',' && line[*i] != ' ' && line[*i] != '\0' && k < 3)
		{
			argz = op->argz[k];
			argz = is_argument(line, i, op->type, argz);
			op->argz[k] = argz;
			k++;
		}
		*i += 1;
	}
	*cur_octet = *cur_octet + 1 + g_op_tab[op->type - 1].encoding_byte;
	k = 0;
	while (k < (int)op->nb_args)
	{
		*cur_octet = *cur_octet + op->argz[k].oct;
		k++;
	}
	return (op);
}

t_label		*is_label(char *line, t_stack *stack, int *i)
{
	t_label		*label;

	label = malloc(sizeof(t_label));
	label->oct = stack->cur_octet;
	label->nb_instructs= 0;
	label->op = NULL;
	label->first_op = NULL;
	label->next = NULL;
	while (line[*i] != '\0' && line[*i] != ':')
		*i += 1;
	label->name = (char*)malloc(sizeof(char) * *i);
	label->name = ft_memcpy(label->name, line, *i);
	return (label);
}

void	print_tester(t_stack *stack)
{
	t_argz argz;
	t_label		*label;
	t_instruct	*op;
	int			i;

	i = 0;
	label = stack->first_label;
	while (label != NULL)
	{
		ft_printf("label name = [%s], nb instructs = [%d], octet = [%d]\n", label->name, label->nb_instructs, label->oct);
		op = label->first_op;
		while (op != NULL)
		{
			ft_printf("\top type = [%d], nb_args = [%d]\n", op->type, op->nb_args);
			i = 0;
			while (i < (int)op->nb_args)
			{
				argz = op->argz[i];
				ft_printf("\t\targ n-%d: type = [%d], value = [%d], lab = [%s],  oct = [%d]\n", i, argz.type, argz.value, argz.lab, argz.oct);
				i++;
			}
			op = op->next;
		}
		label = label->next;
	}
}

void	parsing_tester(t_stack *stack, int fd)
{
	char		*line;
	t_label		*label;
	t_instruct	*op;
	int			i;

	i = 0;
	label = NULL;
	stack->first_label = NULL;
	stack->label_list = NULL;
	while (get_next_line(fd, &line))
	{
		if (i == 2)
			break;
		ft_memdel((void**)&line);
		i++;
	}
	while (get_next_line(fd, &line))
	{
		if (line[0] != '\0' && line[0] != '\n')
		{
		i = 0;
		while (line[i] != '\0' && i < (int)ft_strlen(line))
		{
			if (i == 0 && ft_isalpha(line[i]))
			{
				label = is_label(line, stack, &i);
				label->oct = stack->cur_octet;
				if (stack->first_label == NULL && stack->label_list == NULL)
				{
					stack->first_label = label;
					stack->label_list = label;
				}
				else
				{
					stack->label_list->next = label;
					stack->label_list = stack->label_list->next;
				}
			}
			if (i != 0 && line[i] != '\0' && ft_isalpha(line[i]))
			{
				label->nb_instructs += 1;
				op = is_instruct(line, &i, &stack->cur_octet);
				if (label->op == NULL && label->first_op == NULL)
				{
					label->op = op;
					label->first_op = op;
				}
				else
				{
					label->op->next = op;
					label->op = label->op->next;
				}
			}
			i++;
		}
		ft_memdel((void**)&line);
		}
			else
		ft_memdel((void**)&line);
	}
}
