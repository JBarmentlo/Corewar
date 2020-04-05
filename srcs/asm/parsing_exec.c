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

void		*free_label(t_label *label)
{
	t_label		*save_label;

	while (label != NULL)
	{
		save_label = label->next;
		ft_memdel((void**)&label->name);
		ft_memdel((void**)&label);
		label = save_label;
	}
	return (NULL);	
}

void		*free_op(t_instruct *op)
{
	t_instruct	*save_op;
	t_argz		argz;
	size_t		k;

	while (op != NULL)
	{
		k = 0;
		save_op = op->next;
		while (k < op->nb_args)
		{
			argz = op->argz[k];
			if (argz.lab != NULL)
				ft_memdel((void**)&argz.lab);
			k++;
		}
		ft_memdel((void**)&op);
		op = save_op;
	}
	return (NULL);
}

void		*free_op_lab(t_stack *stack)
{
	t_label		*label;
	t_instruct	*op;

	label = stack->first_label;
	op = stack->first_op;
	free_label(label);
	free_op(op);
	stack->first_op = NULL;
	stack->op_list = NULL;
	stack->first_label = NULL;
	stack->label_list = NULL;
	return (NULL);
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
	argz->lab = ft_memalloc(sizeof(char) * k);
	if (argz->lab == NULL)
		return(ft_error("Memory allocation failure for an [argz->lab]", NULL, NULL));
	argz->lab = ft_stricpy(argz->lab, s->line, save, s->i);
	while (save < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[save]) == NULL)
			return (ft_error_nb(LABEL_ERROR, NULL, s->l, save + 1)); /// FT_ERROR_NB ///
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
		numeric_value(s, argz);
	else
		if (argz_is_label(s,argz) == NULL)
			return (asm_free(argz->lab, NULL, NULL)); /// ASM_FREE ///
	if ((s->line[s->i] == '\0' || s->line[s->i] == COMMENT_CHAR || s->line[s->i] == ALT_COMMENT_CHAR) && s->i > 0)
		s->i -= 1;
	return (argz);
}

int		check_value(t_argz argz, t_instruct *op, int k, t_s *s)
{
	if (argz.type == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((int)ft_error_nb(WRONG_REG_NUM, NULL, s->l, s->i)); /// FT_ERROR_NB ///
	if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
		return ((int)ft_error_nb(WRONG_TYPE_ARG, g_op_tab[op->type - 1].name, s->l, s->i)); /// FT_ERROR_NB ///
	return (TRUE);
}

int		check_sep(int sep_char, int k, t_token *token, int indx_sep)
{
	token->col = indx_sep;
	if (k == 0 && sep_char > 0)
		return ((int)token_free(TOO_MANY_SEP_B, token, NULL));    //// TOKEN_FREE //// 
	if (sep_char >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_SEP_A, token, NULL));    //// TOKEN_FREE ////
	if (k == g_op_tab[token->op_type - 1].arg_nb - 1 && sep_char < k)
		return (TRUE);
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k > sep_char)
		return ((int)token_free(MISSING_SEP, token, NULL));   //// TOKEN_FREE ////
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k < sep_char) 
	{
		ft_printf("test99\n");
		return ((int)token_free(TOO_MANY_SEP_B, token, NULL));   //// TOKEN_FREE ////
	}
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
	last_token.name = NULL;
	while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
	{
		if (s->line[s->i] != ' ' && s->line[s->i] != '\t' && s->line[s->i] != '\0')
		{
			if (k >= g_op_tab[op->type - 1].arg_nb && s->line[s->i] != SEPARATOR_CHAR)
			{
				ft_printf("test16\n");
				ft_memdel((void**)&token.name);
				return ((int)ft_error_nb(TOO_MANY_ARGS, g_op_tab[op->type - 1].name, s->l, s->i));
			}
			if (s->line[s->i] != SEPARATOR_CHAR)
			{
				fill_token(s, op->type, &token);
				if (check_sep(sep_char, k, &token, indx_sep) == FALSE)
				{
					ft_printf("test15\n");
					return ((int)asm_free(token.name, NULL, NULL));
				}
				argz = op->argz[k];
				if (is_argument(s, op->type, &argz) == NULL)
				{
					ft_printf("test1478\n");
					return ((int)asm_free(token.name, NULL, NULL));
				}
				if (s->line[s->i] == SEPARATOR_CHAR)
					sep_char++;
				last_token = token;
				fill_token(s, op->type, &token);
				if (check_value(argz, op, k, s) == FALSE)
				{
					ft_printf("test14\n");
					return ((int)asm_free(token.name, NULL, NULL));
				}
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
	if (check_sep(sep_char, k, &last_token, indx_sep) == FALSE)
	{
		ft_printf("test13\n");
		return ((int)asm_free(token.name, NULL, NULL));
	}
	ft_memdel((void**)&token.name);
	if (k < g_op_tab[op->type - 1].arg_nb)
	{
		ft_printf("test12\n");
		return ((int)ft_error_nb(MISSING_ARG, g_op_tab[op->type - 1].name, s->l, s->i));
	}
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

t_instruct		*is_instruct(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = ft_memalloc(sizeof(t_instruct));
	op->next = NULL;
	op->type = find_opcode(token->name);
	if (op->type == 0)
	{
		if (!ft_strcmp(token->name, NAME_CMD_STRING) || !ft_strcmp(token->name, COMMENT_CMD_STRING))
		{
			ft_printf("test11\n");
			return (token_free(COMMAND_TWICE, token, op)); // to free op_name
		}
		ft_printf("test10\n");
		return (token_free(WRONG_SYNTAX_OP, token, op)); // to_free op_name
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (check_args(s, op) == FALSE)
	{
		ft_printf("test9\n");
		//		ft_memdel((void**)&token->name);
		return (free_op(op));
	}
	if (s->i > 0 && (s->line[(s->i) - 1] == COMMENT_CHAR || s->line[(s->i) - 1] == ALT_COMMENT_CHAR))
		return (op);
	update_oct(op, &stack->cur_octet, s);
	return (op);
}

t_label		*is_label(t_stack *stack, t_token *token)
{
	t_label			*label;
	int			i;

	i = 0;
	label = ft_memalloc(sizeof(t_label));
	if (label == NULL)
	{
		ft_printf("test8\n");
		return(ft_error("Memory allocation failure for a label", NULL, NULL));
	}
	label->oct = stack->cur_octet;
	label->next = NULL;
	while (token->name[i])
	{
		if (ft_strchr(LABEL_CHARS, (int)token->name[i]) == NULL)
		{
			ft_printf("test7\n");
			return (token_free(LABEL_ERROR, token, label));
		}
		i++;
	}
	label->name = ft_memalloc(sizeof(char) * i + 1);
	label->name = ft_memcpy(label->name, token->name, i);
	ft_memdel((void**)&token->name);
	return (label);
}


int		is_label_list(t_s *s, t_stack *stack, t_token *token)
{
	t_label		*label;

	label = is_label(stack, token);
	if (label == NULL)
	{
		ft_printf("test6\n");
		return ((int)free_op_lab(stack));
	}
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

int		is_op(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = is_instruct(s, stack, token);
	if (op == NULL)
	{
		ft_printf("test5\n");
		return ((int)free_op_lab(stack));
	}
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
	t_token			token;
	int			k;
	char			*str;

	token.name = NULL;
	fill_token(s, 42, &token); // OP TYPE TO FILL
	str = s->line;
	k = token.end;
	s->i = k;
	if (str[k] != '\0' && str[k] == LABEL_CHAR)
		return (is_label_list(s, stack, &token));
	else if (str[k] && (str[k] == ' ' || str[k] == '\t' || str[k] == DIRECT_CHAR))
	{
		if (is_op(s, stack, &token) == FALSE)
		{
			ft_printf("test4\n");
			return ((int)asm_free(token.name, NULL, NULL));
		}
	}
	else if (str[k] && k > 0 && (str[k] == COMMENT_CHAR || str[k] == ALT_COMMENT_CHAR))
		s->i -= 1;
	else
	{
		ft_printf("test3\n");
		return ((int)token_free(LEXICAL_ERROR, &token, NULL)); 
	}
	ft_memdel((void**)&token.name);
	return (TRUE);
}

int		parsing_exec(t_stack *stack, int fd, t_s *s)
{
	s->i = 0;
	stack->first_label = NULL;
	stack->label_list = NULL;
	stack->first_op = NULL;
	stack->op_list = NULL;
	while (get_next_line(fd, &s->line))
	{
		s->i = 0;
		s->l += 1;
		while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
		{
			if (s->line[s->i] != ' ' && s->line[s->i] != '\t' && s->line[s->i] != '\0')
				if (is_label_or_op(s, stack) == FALSE)
				{
					ft_printf("test2\n");
					free_op_lab(stack);
					return ((int)asm_free(s->line, NULL, NULL));
				}
			s->i += 1;
		}
		ft_memdel((void**)&s->line);
	}
	if (stack->first_op == NULL)
	{
		ft_printf("test1\n");
		return ((int)ft_error(MISSING_CODE, NULL, NULL));
	}
	ft_memdel((void**)&s->line);
	return (TRUE);
}
