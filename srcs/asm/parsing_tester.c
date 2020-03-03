/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:14:13 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 13:37:15 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_argz		is_register(t_argz argz)
{
	argz.type = T_REG;
	argz.oct = T_REG;
	return (argz);
}

t_argz		is_direct(t_argz argz, size_t inst_type)
{
	argz.type = T_DIR;
	if (g_op_tab[inst_type - 1].is_direct_small == 1)
		argz.oct = DIR_SIZE / 2; // car DIR SIZE = 4 au lieu de 2
	else
		argz.oct = DIR_SIZE; // = a 4 pourtant reg sur 1 ?? //
	///// pour cerains arg, direct code sur 4 octets ////
	return (argz);
}

t_argz		is_indirect(t_argz argz)
{
	argz.type = T_IND;
	argz.oct = IND_SIZE;
	/////// indirect devrait etre code sur 2 octets ///
	return (argz);
}

t_argz		numeric_value(char *line, int *i, t_argz argz)
{
	argz.value = ft_atoi(line + *i);
	if (argz.type == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return (argz);
	argz.lab = NULL;
	if (line[*i] == '-')
		*i += 1;
	while (line[*i] != ',' && line[*i] != '\0' && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR)
	{
		if (ft_isdigit(line[*i]) == 0 && line[*i] != ' ' && line[*i] != '\t')
		{
			argz.value = -1;
			argz.type = 0;
			return (argz);
		}
		*i += 1;
	}
	return (argz);
}

t_argz		argz_is_label(char *line, int *i, t_argz argz)
{
	int		k;
	int		save;

	k = 0;
	*i += 1;
	save = *i;
	while (line[*i] != '\0' && line[*i] != SEPARATOR_CHAR && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR && line[*i] != ' ' && line[*i] != '\t')
	{
		*i += 1;
		k++;
	}
	argz.lab = ft_memalloc(sizeof(char) * k);
	argz.lab = ft_stricpy(argz.lab, line, save, *i);
	argz.value = 0;
	return (argz);
}

t_argz		is_argument(char *line, int *i, size_t inst_type, t_argz argz)
{
	if (line[*i] == 'r')
		argz = is_register(argz);
	else if (line[*i] == DIRECT_CHAR)
		argz = is_direct(argz, inst_type);
	else
		argz = is_indirect(argz);
	if (line[*i] != LABEL_CHAR)
		*i += 1;
	if (line[*i] != '\0' && line[*i] != LABEL_CHAR)
		argz = numeric_value(line, i, argz); // gesstion d'erreur??
	else
		argz = argz_is_label(line, i, argz);
	if ((line[*i] == '\0' || line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR) && *i > 0)
		*i -= 1;
	return (argz);
}

t_instruct		*check_args(char *line, int *i, t_instruct *op, char *op_code)
{
	int			k;
	t_argz		argz;
	int			sep_char;

	k = 0;
	sep_char = 0;
	while (line[*i] != '\0' && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR)
	{
		if (line[*i] != SEPARATOR_CHAR && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\0')
		{
			if (k > 0 && (k < g_op_tab[op->type - 1].arg_nb) && k > sep_char)
				return (ft_error2("Missing separator_char for the op_code:", op_code));
			if (k > 0 && (k < g_op_tab[op->type - 1].arg_nb) && k < sep_char)
				return (ft_error2("Too many separator_char for the op_code:", op_code));
			if (k >= g_op_tab[op->type - 1].arg_nb)
				return (ft_error2("Too many arguments for the op_code:", op_code));
			argz = op->argz[k];
			argz = is_argument(line, i, op->type, argz);
			if (argz.value == -1 && argz.type == 0)
				return (ft_error2("Wrong syntaxe for an argument of the op_code:", op_code));
			if (argz.type == T_REG && argz.value > REG_NUMBER)
				return (ft_error2("A register number should be between 1 and 16", NULL));
			if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
				return (ft_error2("Wrong type of arguments for the op_code:", op_code));
			op->argz[k] = argz;
			k++;
		}
		if (line[*i] == SEPARATOR_CHAR)
			sep_char += 1;
		*i += 1;
	}
	if (k < g_op_tab[op->type - 1].arg_nb)
		return (ft_error2("Unsuficiant number of arguments for the op_code:", op_code));
	return (op);
}

void	update_oct(t_instruct *op, int *cur_octet, int *i)
{
	int	k;

	k = 0;
	*cur_octet = *cur_octet + 1 + g_op_tab[op->type - 1].encoding_byte;
	while (k < (int)op->nb_args)
	{
		*cur_octet = *cur_octet + op->argz[k].oct;
		k++;
	}
	op->next = NULL;
	if (*i > 0)
		*i -= 1;
}

t_instruct		*is_instruct(char *line, int *i, int start, int *cur_octet)
{
	t_instruct	*op;
	char		*op_code;
	int			k;
	int			w;

	k = 0;
	w = 0;
	op = ft_memalloc(sizeof(t_instruct));
	op_code = ft_memalloc(sizeof(char) * (*i - start)); 
	op_code = ft_stricpy(op_code, line, start, *i);
	op->type = find_opcode(op_code);
	if (op->type == 0)
		return (ft_error2("Wrong syntaxe for an op_code", NULL));
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = *cur_octet;
	if (check_args(line, i, op, op_code) == NULL)
		return (NULL);
	if (*i > 0 && (line[*i - 1] == COMMENT_CHAR || line[*i - 1] == ALT_COMMENT_CHAR))
		return (op);
	update_oct(op, cur_octet, i);
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

int		is_label_list(char *line, t_stack *stack, int *i, int start)
{
	t_label		*label;

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

int		is_op(char *line, t_stack *stack, int *i, int start)
{
	t_instruct	*op;

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
	return (TRUE);
}

int		is_label_or_op(char *line, t_stack *stack, int *i)
{
	int			start;

	start = *i;
	while (line[*i] != '\0' && line[*i] != ' ' && line[*i] != '\t' && line[*i] != LABEL_CHAR && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR)
		*i += 1;
	if (line[*i] == LABEL_CHAR)
		return (is_label_list(line, stack, i, start));
	else if (line[*i] == ' ' || line[*i] == '\t')
	{
		if (is_op(line, stack, i, start) == FALSE)
			return (FALSE);
	}
	else if ((line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR) && *i > 0)
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
		while (line[i] != '\0' && line[i] != COMMENT_CHAR && line[i] != ALT_COMMENT_CHAR)
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
