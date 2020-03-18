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

void	is_register(t_argz *argz)
{
	argz->type = T_REG;
	argz->code = REG_CODE;
	argz->oct = T_REG;
}

void	is_direct(t_argz *argz, size_t inst_type)
{
	argz->type = T_DIR;
	argz->code = DIR_CODE;
	if (g_op_tab[inst_type - 1].is_direct_small == 1)
		argz->oct = DIR_SIZE / 2;
	else
		argz->oct = DIR_SIZE;
}

void	is_indirect(t_argz *argz)
{
	argz->type = T_IND;
	argz->code = IND_CODE;
	argz->oct = IND_SIZE;
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

void	numeric_value(char *line, int *i, t_argz *argz)
{
	ft_atolong(line, argz, i);
	argz->lab = NULL;
}

void	*argz_is_label(char *line, int *i, t_argz *argz, int ln)
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
	argz->lab = ft_memalloc(sizeof(char) * k); // to protect
	argz->lab = ft_stricpy(argz->lab, line, save, *i);
	save = 0;
	while (save < *i)
	{
		if (ft_strchr(LABEL_CHARS, (int)line[save]) == NULL)
			return (ft_error_nb(LABEL_ERROR, NULL, ln, save + 1));
		save++;
	}
	argz->value = 0;
	return (argz);
}

void	*is_argument(char *line, int *i, size_t inst_type, t_argz *argz, int ln)
{
	if (line[*i] == 'r')
		is_register(argz);
	else if (line[*i] == DIRECT_CHAR)
		is_direct(argz, inst_type);
	else
		is_indirect(argz);
	if (line[*i] != LABEL_CHAR && argz->type != T_IND)
		*i += 1;
	if (line[*i] != '\0' && line[*i] != LABEL_CHAR)
		numeric_value(line, i, argz);  // gesstion d'erreur??
	else
	{
		if (argz_is_label(line, i, argz, ln) == NULL)
			return (NULL);
	}
	if ((line[*i] == '\0' || line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR) && *i > 0)
		*i -= 1;
	return (argz);
}

int		check_value(t_argz argz, t_instruct *op, int k, int line, int col)
{
	if (argz.type == T_REG && argz.value > REG_NUMBER)
		return ((int)ft_error_nb(WRONG_REG_NUM, NULL, line, col));
	if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
		return ((int)ft_error_nb(WRONG_TYPE_ARG, g_op_tab[op->type - 1].name, line, col));
	return (TRUE);
}

int		check_sep(int sep_char, int k, t_token token)
{
	if (sep_char >= g_op_tab[token.op_type - 1].arg_nb)
		return ((int)ft_error_nb(TOO_MANY_SEP_A, token.name, token.line, token.col));
	if (k == g_op_tab[token.op_type - 1].arg_nb - 1 && sep_char < k)
		return (TRUE);
	if (k > 0 && (k < g_op_tab[token.op_type - 1].arg_nb) && k > sep_char)
		return ((int)ft_error_nb(MISSING_SEP, token.name, token.line, token.col));
	if (k > 0 && (k < g_op_tab[token.op_type - 1].arg_nb) && k < sep_char)
		return ((int)ft_error_nb(TOO_MANY_SEP_B, token.name, token.line, token.col));
	return (TRUE);	
}

int	check_args(char *line, int *i, t_instruct *op, t_stack *stack)
{
	int		k;
	int		sep_char;
	t_argz		argz;
	t_token		token;
	t_token		last_token;
	
	k = 0;
	sep_char = 0;
	token.name = NULL;
	while (line[*i] != '\0' && line[*i] != COMMENT_CHAR && line[*i] != ALT_COMMENT_CHAR)
	{
		if (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\0')
		{
			if (k >= g_op_tab[op->type - 1].arg_nb && line[*i] != SEPARATOR_CHAR)
				return ((int)ft_error_nb(TOO_MANY_ARGS, g_op_tab[op->type - 1].name, stack->nb_lines, *i));
			if (line[*i] != SEPARATOR_CHAR)
			{
				last_token = token;
				token = fill_token(line, stack->nb_lines, i, op->type);
				if (check_sep(sep_char, k, token) == FALSE)
					return (FALSE);
				argz = op->argz[k];
				if (is_argument(line, i, op->type, &argz, stack->nb_lines) == NULL)
					return (FALSE);
				if (line[*i] == SEPARATOR_CHAR)
					sep_char++;
				last_token = token;
				token = fill_token(line, stack->nb_lines, i, op->type);
				if (check_value(argz, op, k, stack->nb_lines, *i) == FALSE)
					return (FALSE);
				op->argz[k] = argz;
				k++;
			}
			else
				sep_char += 1;
		}
		*i += 1;
	}
	if (check_sep(sep_char, k, last_token) == FALSE)
		return (FALSE);
	if (k < g_op_tab[op->type - 1].arg_nb)
		return ((int)ft_error_nb(MISSING_ARG, g_op_tab[op->type - 1].name, stack->nb_lines, *i));
	return (TRUE);
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
	char		*op_name;

	op = ft_memalloc(sizeof(t_instruct));
	op_name = ft_memalloc(sizeof(char) * (*i - start)); 
	op_name = ft_stricpy(op_name, line, start, *i);
	op->type = find_opcode(op_name);
	if (op->type == 0)
	{
		if (!ft_strcmp(op_name, NAME_CMD_STRING))
			return (ft_error_nb(TOO_MANY_NAMES, NULL, stack->nb_lines, start + 1));
		if (!ft_strcmp(op_name, COMMENT_CMD_STRING))
			return (ft_error_nb(TOO_MANY_COMMENTS, NULL, stack->nb_lines, start + 1));
		return (ft_error_nb(WRONG_SYNTAX_OP, op_name, stack->nb_lines, start + 1));
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (check_args(line, i, op, stack) == FALSE)
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
			return (ft_error_nb(LABEL_ERROR, NULL, stack->nb_lines, s + 1));
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
	t_token			token;

	start = *i;
	token = fill_token(line, stack->nb_lines, i, 0);
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
	else
		return ((int)ft_error_nb(LEXICAL_ERROR, token.name, token.line, token.col)); 
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
		return ((int)ft_error(MISSING_CODE, NULL));
	return (TRUE);
}
