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

int		ft_atolong(t_s *s, t_argz *argz)
{
	long	neg;
	long	nb;
	long	bits;
	char	*str;

	neg = 1;
	nb = 0;
	str = s->line;
	while (str[s->i] == ' ' || str[s->i] == '\f' || str[s->i] == '\t'
			|| str[s->i] == '\n' || str[s->i] == '\r' || str[s->i] == '\v')
		s->i += 1;
	if (str[s->i] == '-')
		neg = -1;
	if (str[s->i] == '-' || str[s->i] == '+')
		s->i += 1;
	while (ft_isdigit((long)str[s->i]))
	{
		nb = 10 * nb + str[s->i] - 48;
		bits = count_bits(nb);
		if (bits >= 63)
		{
			argz->value = 4294967295;
			while (ft_isdigit((long)str[s->i]) && str[s->i] != ' ' && str[s->i] != '\t' && str[s->i] != COMMENT_CHAR && str[s->i] != ALT_COMMENT_CHAR && str[s->i] != '\0')
				s->i += 1;
			if (s > 0)
				s->i -= 1;
			return (TRUE);
		}
		s->i += 1;
	}
	argz->value = nb * neg;
	return (TRUE);
}

void	numeric_value(t_s *s, t_argz *argz)
{
	argz->line = s->l;
	argz->col = s->i;
	ft_atolong(s, argz);
	argz->lab = NULL;
}

void	*argz_is_label(t_s *s, t_argz *argz)
{
	int		k;
	int		save;

	k = 0;
	s->i += 1;
	save = s->i;
	argz->line = s->l;
	argz->col = save;
	while (s->line[s->i] != '\0' && s->line[s->i] != SEPARATOR_CHAR && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR && s->line[s->i] != ' ' && s->line[s->i] != '\t')
	{
		s->i += 1;
		k++;
	}
	argz->lab = ft_memalloc(sizeof(char) * k); // to protect
	argz->lab = ft_stricpy(argz->lab, s->line, save, s->i);
	while (save < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[save]) == NULL)
			return (ft_error_nb(LABEL_ERROR, NULL, s->l, save + 1));
		save++;
	}
	argz->value = 0;
	return (argz);
}

void	*is_argument(t_s *s, size_t inst_type, t_argz *argz)
{
	if (s->line[s->i] == 'r')
		is_register(argz);
	else if (s->line[s->i] == DIRECT_CHAR)
		is_direct(argz, inst_type);
	else
		is_indirect(argz);
	if (s->line[s->i] != LABEL_CHAR && argz->type != T_IND)
		s->i += 1;
	if (s->line[s->i] != '\0' && s->line[s->i] != LABEL_CHAR)
		numeric_value(s, argz); // gestion d'erreur ?
	else
	{
		if (argz_is_label(s,argz) == NULL)
			return (NULL);
	}
	if ((s->line[s->i] == '\0' || s->line[s->i] == COMMENT_CHAR || s->line[s->i] == ALT_COMMENT_CHAR) && s->i > 0)
		s->i -= 1;
	return (argz);
}

int		check_value(t_argz argz, t_instruct *op, int k, t_s *s)
{
	if (argz.type == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((int)ft_error_nb(WRONG_REG_NUM, NULL, s->l, s->i));
	if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
		return ((int)ft_error_nb(WRONG_TYPE_ARG, g_op_tab[op->type - 1].name, s->l, s->i));
	return (TRUE);
}

int		check_sep(int sep_char, int k, t_token token, int indx_sep)
{
	if (k == 0 && sep_char > 0)
		return ((int)ft_error_nb(TOO_MANY_SEP_B, token.name, token.line, indx_sep));
	if (sep_char >= g_op_tab[token.op_type - 1].arg_nb)
		return ((int)ft_error_nb(TOO_MANY_SEP_A, token.name, token.line, indx_sep));
	if (k == g_op_tab[token.op_type - 1].arg_nb - 1 && sep_char < k)
		return (TRUE);
	if (k > 0 && (k < g_op_tab[token.op_type - 1].arg_nb) && k > sep_char)
		return ((int)ft_error_nb(MISSING_SEP, token.name, token.line, token.col));
	if (k > 0 && (k < g_op_tab[token.op_type - 1].arg_nb) && k < sep_char)
		return ((int)ft_error_nb(TOO_MANY_SEP_B, token.name, token.line, indx_sep));
	return (TRUE);	
}

int	check_args(t_s *s, t_instruct *op)
{
	int		k;
	int		indx_sep;
	int		sep_char;
	t_argz		argz;
	t_token		token;
	t_token		last_token;
	
	k = 0;
	sep_char = 0;
	indx_sep = 0;
	token.name = NULL;
	while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
	{
		if (s->line[s->i] != ' ' && s->line[s->i] != '\t' && s->line[s->i] != '\0')
		{
			if (k >= g_op_tab[op->type - 1].arg_nb && s->line[s->i] != SEPARATOR_CHAR)
				return ((int)ft_error_nb(TOO_MANY_ARGS, g_op_tab[op->type - 1].name, s->l, s->i));
			if (s->line[s->i] != SEPARATOR_CHAR)
			{
				last_token = token;
				token = fill_token(s, op->type);
				if (check_sep(sep_char, k, token, indx_sep) == FALSE)
					return (FALSE);
				argz = op->argz[k];
				if (is_argument(s, op->type, &argz) == NULL)
					return (FALSE);
				if (s->line[s->i] == SEPARATOR_CHAR)
					sep_char++;
				last_token = token;
				token = fill_token(s, op->type);
				if (check_value(argz, op, k, s) == FALSE)
					return (FALSE);
				op->argz[k] = argz;
				k++;
			}
			else
			{
				sep_char += 1;
				indx_sep = s->i;
			}
		}
		s->i += 1;
	}
	if (check_sep(sep_char, k, last_token, indx_sep) == FALSE)
		return (FALSE);
	if (k < g_op_tab[op->type - 1].arg_nb)
		return ((int)ft_error_nb(MISSING_ARG, g_op_tab[op->type - 1].name, s->l, s->i));
	return (TRUE);
}

void	update_oct(t_instruct *op, int *cur_octet, t_s *s)
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
	if (s->i > 0)
		s->i -= 1;
}

t_instruct		*is_instruct(t_s *s, int start, t_stack *stack)
{
	t_instruct	*op;
	char		*op_name;

	op = ft_memalloc(sizeof(t_instruct));
	op_name = ft_memalloc(sizeof(char) * (s->i - start)); 
	op_name = ft_stricpy(op_name, s->line, start, s->i);
	op->type = find_opcode(op_name);
	if (op->type == 0)
	{
		if (!ft_strcmp(op_name, NAME_CMD_STRING))
			return (ft_error_nb(TOO_MANY_NAMES, NULL, s->l, start + 1));
		if (!ft_strcmp(op_name, COMMENT_CMD_STRING))
			return (ft_error_nb(TOO_MANY_COMMENTS, NULL, s->l, start + 1));
		return (ft_error_nb(WRONG_SYNTAX_OP, op_name, s->l, start + 1));
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (check_args(s, op) == FALSE)
		return (NULL);
	if (s->i > 0 && (s->line[(s->i) - 1] == COMMENT_CHAR || s->line[(s->i) - 1] == ALT_COMMENT_CHAR))
		return (op);
	update_oct(op, &stack->cur_octet, s);
	return (op);
}

t_label		*is_label(t_s *s, t_stack *stack, int start)
{
	t_label		*label;
	int			save;

	label = malloc(sizeof(t_label));
	label->oct = stack->cur_octet;
	label->next = NULL;
	save = start;
	while (start < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[start]) == NULL)
		{
			return (ft_error_nb(LABEL_ERROR, NULL, s->l, start + 1));
		}
		start++;
	}
	label->name = ft_memalloc(sizeof(char) * start);
	label->name = ft_stricpy(label->name, s->line, save, s->i);
	return (label);
}

int		is_label_list(t_s *s, t_stack *stack, int start)
{
	t_label		*label;

	label = is_label(s, stack, start);
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
	return (s->i);
}

int		is_op(t_s *s, t_stack *stack, int start)
{
	t_instruct	*op;

	op = is_instruct(s, start, stack);
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

int		is_label_or_op(t_s *s, t_stack *stack)
{
	int			start;
	t_token			token;

	start = s->i;
	token = fill_token(s, 0); // OP TYPE TO FILL
	while (s->line[s->i] != '\0' && s->line[s->i] != ' ' && s->line[s->i] != '\t' && s->line[s->i] != LABEL_CHAR && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR && s->line[s->i] != DIRECT_CHAR)
		s->i += 1;
	if (s->line[s->i] == LABEL_CHAR)
		return (is_label_list(s, stack, start));
	else if (s->line[s->i] == ' ' || s->line[s->i] == '\t' || s->line[s->i] == DIRECT_CHAR)
	{
		if (is_op(s, stack, start) == FALSE)
			return (FALSE);
	}
	else if ((s->line[s->i] == COMMENT_CHAR || s->line[s->i] == ALT_COMMENT_CHAR) && s->i > 0)
		s->i -= 1;
	else
		return ((int)ft_error_nb(LEXICAL_ERROR, token.name, token.line, token.col)); 
	return (TRUE);
}

int		parsing_exec(t_stack *stack, int fd)
{
	t_s		s;

	s.i = 0;
	s.l = stack->nb_lines;
	stack->first_label = NULL;
	stack->label_list = NULL;
	stack->first_op = NULL;
	stack->op_list = NULL;
	while (get_next_line(fd, &s.line))
	{
		s.i = 0;
		stack->nb_lines += 1;
		s.l += 1;
		while (s.line[s.i] != '\0' && s.line[s.i] != COMMENT_CHAR && s.line[s.i] != ALT_COMMENT_CHAR)
		{
			if (s.line[s.i] != ' ' && s.line[s.i] != '\t' && s.line[s.i] != '\0')
			{
				if (is_label_or_op(&s, stack) == FALSE)
					return (FALSE);
			}
			s.i += 1;
		}
		ft_memdel((void**)&(s.line));
	}
	if (stack->first_op == NULL)
		return ((int)ft_error(MISSING_CODE, NULL));
	return (TRUE);
}
