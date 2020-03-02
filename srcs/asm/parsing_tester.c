/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:13 by dberger           #+#    #+#             */
/*   Updated: 2020/02/25 13:12:01 by jbarment         ###   ########.fr       */
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
		argz.oct = T_REG;
		/// pk reg size a 4 ??? ///
	}
	else if (line[*i] == DIRECT_CHAR)
	{
		argz.type = DIR_CODE;
		if (g_op_tab[inst_type - 1].is_direct_small == 1)
			argz.oct = DIR_SIZE / 2; // car DIR SIZE = 4 au lieu de 2
		else
			argz.oct = DIR_SIZE; // = a 4 pourtant reg sur 1 ?? //
		///// pour cerains arg, direct code sur 4 octets ////
	}
	else
	{
		argz.type = IND_CODE;
		argz.oct = IND_SIZE;
		/////// indirect devrait etre code sur 2 octets ///
	}
	if (line[*i] != LABEL_CHAR)
		*i += 1;
	if (line[*i] != '\0' && line[*i] != LABEL_CHAR)
	{
		argz.value = ft_atoi(line + *i);
		argz.lab = NULL;
		while (line[*i] != ',' && line[*i] != '\0')
			*i += 1;
	}
	else
	{
		*i += 1;
		save = *i;
		while (line[*i] != '\0' && line[*i] != SEPARATOR_CHAR)
		{
			*i += 1;
			k++;
		}
		argz.lab = ft_memalloc(sizeof(char) * k);
		argz.lab = ft_stricpy(argz.lab, line, save, *i);
		argz.value = 0;
	}
	return (argz);
}

t_instruct		*is_instruct(char *line, int *i, int start, int *cur_octet)
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
	op = ft_memalloc(sizeof(t_instruct));
	op_code = ft_memalloc(sizeof(char) * (*i - start)); 
	op_code = ft_stricpy(op_code, line, start, *i);
	op->type = find_opcode(op_code);
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = *cur_octet;
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
	op->next = NULL;
	if (*i > 0)
		*i -= 1;
	return (op);
}

t_label		*is_label(char *line, t_stack *stack, int s, int i)
{
	t_label		*label;
	int			save;

	label = malloc(sizeof(t_label));
	label->oct = stack->cur_octet;
	label->next = NULL;
	save = s;
	while (s < i)
	{
		if (ft_strchr(LABEL_CHARS, (int)line[s]) == NULL)
		{
			ft_error("Lexical error for a label", NULL);
			return (NULL);
		}
		s++;
	}
	label->name = ft_memalloc(sizeof(char) * s);
	label->name = ft_stricpy(label->name, line, save, i);
	return (label);
}

int		is_label_or_op(char *line, t_stack *stack, int *i)
{
	t_label		*label;
	t_instruct	*op;
	int			start;

	label = NULL;
	op = NULL;
	start = *i;
	while (line[*i] != '\0' && line[*i] != ' ' && line[*i] != LABEL_CHAR && line[*i] != COMMENT_CHAR)
		*i += 1;
	if (line[*i] == LABEL_CHAR)
	{
		label = is_label(line, stack, start, *i);
		if (label == NULL)
			return (FALSE);
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
		return (*i);
	}
	else if (line[*i] == ' ')
	{
		op = is_instruct(line, i, start, &stack->cur_octet);
		if (op == NULL)
			return (FALSE);
		if (stack->op_list == NULL && stack->first_op == NULL)
		{
			stack->first_op = op;
			stack->op_list = stack->first_op;
		}
		else
		{
			stack->op_list->next = op;
			stack->op_list = stack->op_list->next;
		}
	}
	else if (line[*i] == COMMENT_CHAR && *i > 0)
		*i -= 1;
	return (TRUE);
}

int		parsing_tester(t_stack *stack, int fd)
{
	char		*line;
	int			i;

	i = 0;
	stack->first_label = NULL;
	stack->label_list = NULL;
	stack->first_op = NULL;
	stack->op_list = NULL;
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] != '\0' && line[i] != COMMENT_CHAR)
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i])
			{
				if (is_label_or_op(line, stack, &i) == FALSE)
					return (FALSE);
			}
			i++;
		}
		ft_memdel((void**)&line);
	}
	return (TRUE);
}
