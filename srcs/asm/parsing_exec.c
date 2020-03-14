/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:23:19 by dberger           #+#    #+#             */
/*   Updated: 2020/03/09 16:09:25 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_argz		is_register(t_argz argz)
{
	argz.type = T_REG;
	argz.code = REG_CODE;
	argz.oct = T_REG;
	return (argz);
}

t_argz		is_direct(t_argz argz, size_t inst_type)
{
	argz.type = T_DIR;
	argz.code = DIR_CODE;
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
	argz.code = IND_CODE;
	argz.oct = IND_SIZE;
	/////// indirect devrait etre code sur 2 octets ///
	return (argz);
}

int		ft_atolong(const char *str, t_argz *argz, int *i)
{
	long	neg;
	long	nb;
	long	bits;

	neg = 1;
	nb = 0;
	while (str[*i] == ' ' || str[*i] == '\f' || str[*i] == '\t'
			|| str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\v')
		*i += 1;
	if (str[*i] == '-')
		neg = -1;
	if (str[*i] == '-' || str[*i] == '+')
		*i += 1;
	while (ft_isdigit((long)str[*i]))
	{
		nb = 10 * nb + str[*i] - 48;
		bits = count_bits(nb);
		if (bits >= 63)
		{
			argz->value = 4294967295;
			return (TRUE);
		}
		*i += 1;
	}
	argz->value = nb * neg;
	return (TRUE);
}

t_argz		numeric_value(char *line, int *i, t_argz argz)
{
	ft_atolong(line, &argz, i);
	argz.lab = NULL;
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
	if (line[*i] != LABEL_CHAR && argz.type != T_IND)
		*i += 1;
	if (line[*i] != '\0' && line[*i] != LABEL_CHAR)
		argz = numeric_value(line, i, argz); // gesstion d'erreur??
	else
		argz = argz_is_label(line, i, argz);
	if ((line[*i] == '\0' || line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR) && *i > 0)
		*i -= 1;
	return (argz);
}

t_instruct		*check_args(char *line, int *i, t_instruct *op, t_stack *stack)
{
	int			k;
	t_argz		argz;
	int			sep_char;
	int			save;

	k = 0;
	sep_char = 0;
	while (line[*i] != '\0' && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR)
	{
		if (line[*i] != SEPARATOR_CHAR && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\0')
		{
			if (k > 0 && (k < g_op_tab[op->type - 1].arg_nb) && k > sep_char)
				return (ft_error_nb("Missing separator_char before the argument", line + *i, stack->nb_lines, *i));
			if (k > 0 && (k < g_op_tab[op->type - 1].arg_nb) && k < sep_char)
				return (ft_error_nb("Too many separator_char before the argument", line + *i, stack->nb_lines, *i));
			if (k >= g_op_tab[op->type - 1].arg_nb)
				return (ft_error_nb("Too many arguments for the op_code", op->name, stack->nb_lines, *i));
			argz = op->argz[k];
			save = *i;
			argz = is_argument(line, i, op->type, argz);
			if (argz.value == -1 && argz.type == 0)
				return (ft_error_nb("Wrong syntaxe for first argument of the op_code", op->name, stack->nb_lines, *i));
			if (argz.type == T_REG && argz.value > REG_NUMBER)
				return (ft_error_nb("A register number should be between 1 and 16", NULL, stack->nb_lines, *i));
			if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
				return (ft_error_nb("Wrong type of arguments for the op_code", op->name, stack->nb_lines, *i));
			op->argz[k] = argz;
			k++;
		}
		if (line[*i] == SEPARATOR_CHAR)
			sep_char += 1;
		*i += 1;
	}
	if (k < g_op_tab[op->type - 1].arg_nb)
		return (ft_error("Invalid parameter count for instruction", op->name));
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

t_instruct		*is_instruct(char *line, int *i, int start, t_stack *stack)
{
	t_instruct	*op;

	op = ft_memalloc(sizeof(t_instruct));
	op->name = ft_memalloc(sizeof(char) * (*i - start)); 
	op->name = ft_stricpy(op->name, line, start, *i);
	op->type = find_opcode(op->name);
	if (op->type == 0)
	{
		if (!ft_strcmp(op->name, NAME_CMD_STRING))
			return (ft_error_nb("Can't have twice the definition of the champion's name", NULL, stack->nb_lines, start + 1));
		if (!ft_strcmp(op->name, COMMENT_CMD_STRING))
			return (ft_error_nb("Can't have twice the definition of the champion's comment", NULL, stack->nb_lines, start + 1));
		return (ft_error_nb("Wrong syntaxe for the op_code", op->name, stack->nb_lines, start + 1));
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (check_args(line, i, op, stack) == NULL)
		return (NULL);
	if (*i > 0 && (line[*i - 1] == COMMENT_CHAR || line[*i - 1] == ALT_COMMENT_CHAR))
		return (op);
	update_oct(op, &stack->cur_octet, i);
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
			return (ft_error_nb("Lexical error for a label", NULL, stack->nb_lines, s + 1));
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

	op = is_instruct(line, i, start, stack);
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

int		parsing_exec(t_stack *stack, int fd)
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
		stack->nb_lines += 1;
		while (line[i] != '\0' && line[i] != COMMENT_CHAR && line[i] != ALT_COMMENT_CHAR)
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
			{
				if (is_label_or_op(line, stack, &i) == FALSE)
					return (FALSE);
			}
			i++;
		}
		ft_memdel((void**)&line);
	}
	if (stack->first_op == NULL)
		return ((int)ft_error("Missing exec_code for the champion", NULL));
	return (TRUE);
}
