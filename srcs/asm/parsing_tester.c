/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:13 by dberger           #+#    #+#             */
/*   Updated: 2020/02/12 18:34:36 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		is_argument(char *line, int *i, t_argz *argz, size_t inst_type)
{
	int		k;
	int		save;

	k = 0;
	ft_printf("arg = [%s]\n", line + *i);
	if (line[*i] == 'r')
	{
		argz->type = T_REG;
		argz->oct = 1;
	}
	else if (line[*i] == '%')
	{
		argz->type = T_DIR;
		if (g_op_tab[inst_type - 1].is_direct_small == 1)
			argz->oct = 2;
		else
			argz->oct = 4;
	}
	else
	{
		argz->type = T_IND;
		argz->oct = 2;
	}
	*i += 1;
	if (line[*i] != ':')
	{
		argz->value = ft_atoi(line + *i);
		argz->lab = NULL;
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
		argz->lab = (char*)malloc(sizeof(char) * k);
		argz->lab = ft_memcpy(argz->lab, line + save, k);
	}
}

t_instruct		*is_instruct(char *line, int *i)
{
	t_instruct	*op;
	char	*op_code;
	int		k;
	int		save;
	t_argz	argz;

	k = 0;
	save = *i;
	op = malloc(sizeof(t_instruct));
	while (ft_isalnum(line[*i]) == 1)
	{
		*i += 1;
		k++;
	}
	op_code = malloc(sizeof(char) * k);
	op_code = ft_memcpy(op_code, line + save, k);
	op->type = find_opcode(op_code);
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	argz = malloc(sizeof(t_argz) * op->nb_args);
	k = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] != ',' && line[*i] != ' ' && line[*i] != '\0')
		{
			argz[k] = is_argument(line, i, argz[k], op->type);
			k++;
		}
		*i += 1;
	}
	return (op);
}

t_label		*is_label(char *line, t_stack *stack)
{
	t_label		*label;
	int			i;

	i = 0;
	label = malloc(sizeof(t_label));
	label->oct = stack->cur_octet;
	label->nb_instructs= 0;
	label->op = NULL;
	label->first_op = NULL;
	label->next = NULL;
	while (line[i] != '\0' && line[i] != ':')
		i++;
	label->name = (char*)malloc(sizeof(char) * i);
	label->name = ft_memcpy(label->name, line, i);
	return (label);
}

void	parsing_tester(t_stack *stack, int fd)
{
	char		*line;
	t_label		*label;
	t_instruct	*op;
	int			i;

	i = 0;
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
			printf(" //////////// line = [%s]\n", line);
		i = 0;
		while (line[i] != '\0')
		{
			if (i == 0 && ft_isalpha(line[i]))
			{
				label = is_label(line, stack);
				ft_printf("********label name = [%s]\n", label->name);
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
				op = is_instruct(line, &i);
				ft_printf("op->type  = [%d], nb args = [%d]\n", op->type, op->nb_args);
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
