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

t_label		*is_label(t_stack *stack, t_token *token)
{
	t_label			*label;
	int			i;

	i = 0;
	label = ft_memalloc(sizeof(t_label));
	if (label == NULL)
		return(ft_error("Memory allocation failure for a label", NULL, NULL));
	label->oct = stack->cur_octet;
	label->next = NULL;
	while (token->name[i])
	{
		if (ft_strchr(LABEL_CHARS, (int)token->name[i]) == NULL)
			return (token_free(LABEL_ERROR, token, label));
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
		return ((int)free_op_lab(stack));
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

t_instruct		*is_op(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = ft_memalloc(sizeof(t_instruct));
	op->next = NULL;
	op->type = find_opcode(token->name);
	if (op->type == 0)
	{
		if (!ft_strcmp(token->name, NAME_CMD_STRING) || !ft_strcmp(token->name, COMMENT_CMD_STRING))
			return (token_free(COMMAND_TWICE, token, op));
		return (token_free(WRONG_SYNTAX_OP, token, op));
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (check_args(s, op) == FALSE)
		return (free_op(op)); // token to free ??
	if (s->i > 0 && (s->line[(s->i) - 1] == COMMENT_CHAR || s->line[(s->i) - 1] == ALT_COMMENT_CHAR))
		return (op);
	update_oct(op, &stack->cur_octet, s);
	return (op);
}

int		is_op_list(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = is_op(s, stack, token);
	if (op == NULL)
		return ((int)free_op_lab(stack));
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
		if (is_op_list(s, stack, &token) == FALSE)
			return ((int)just_free(token.name, NULL));
	}
	else if (str[k] && k > 0 && (str[k] == COMMENT_CHAR || str[k] == ALT_COMMENT_CHAR))
		s->i -= 1;
	else
		return ((int)token_free(LEXICAL_ERROR, &token, NULL)); 
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
					free_op_lab(stack);
					return ((int)just_free(s->line, NULL));
				}
			s->i += 1;
		}
		ft_memdel((void**)&s->line);
	}
	if (stack->first_op == NULL)
		return ((int)ft_error(MISSING_CODE, NULL, NULL));
	ft_memdel((void**)&s->line);
	return (TRUE);
}
