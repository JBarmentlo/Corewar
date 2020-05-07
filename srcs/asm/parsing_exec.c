/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:23:19 by dberger           #+#    #+#             */
/*   Updated: 2020/05/07 16:45:34 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** When we stock information on labels we only need there names and the current
** octet we are at. We also check if all the characters in it correspond to
** LABEL_CHARS.
*/

t_label		*is_label(t_stack *stack, t_token *token)
{
	t_label		*label;
	int			i;

	i = 0;
	if (!(label = ft_memalloc(sizeof(t_label))))
		return (ft_error(LABEL_ALLOC, NULL));
	label->oct = stack->cur_octet;
	label->next = NULL;
	while (token->name[i])
	{
		if (ft_strchr(LABEL_CHARS, (intptr_t)token->name[i]) == NULL)
		{
			ft_memdel((void**)&label);
			return (token_free(LABEL_ERROR, token));
		}
		i++;
	}
	if (!(label->name = ft_memalloc(sizeof(char) * i + 1)))
	{
		ft_memdel((void**)&label);
		return (ft_error(LABEL_ALLOC, NULL));
	}
	label->name = ft_memcpy(label->name, token->name, i);
	return (label);
}

/*
** If the lavel is valid (is_label) we add it to the list.
** Otherwise we free the two list we have created (op and labels).
*/

int			is_label_list(t_s *s, t_stack *stack, t_token *token)
{
	t_label		*label;

	label = is_label(stack, token);
	ft_memdel((void**)&token->name);
	if (label == NULL)
		return ((intptr_t)free_op_lab(stack));
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

/*
** When we find a new op, we check if it is valid, if not we need to free
** the two chained lists we have created. If not, we had the new op to
** the list (stack->op_list->next).
*/

int			is_op_list(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = is_op(s, stack, token);
	if (op == NULL)
		return ((intptr_t)free_op_lab(stack));
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

/*
** If we find a LABEL_CHAR, it corresponds to a label, otherwise to an op_code
** When we read a line, we make sure that if we encounter [#] or [;] it is like
** being at the end of a line.
*/

int			is_label_or_op(t_s *s, t_stack *stack)
{
	t_token			token;
	int				k;
	char			*str;

	init_token(&token);
	if (fill_token(s, 42, &token) == FALSE)
		return (FALSE);
	str = s->line;
	k = token.end;
	s->i = k;
	if (str[k] != '\0' && str[k] == LABEL_CHAR)
		return (is_label_list(s, stack, &token));
	else if (str[k] && (str[k] == ' ' || str[k] == '\t'
		|| str[k] == DIRECT_CHAR))
	{
		if (is_op_list(s, stack, &token) == FALSE)
			return ((intptr_t)just_free(token.name, NULL));
	}
	else if (str[k] && k > 0 && (str[k] == COMMENT_CHAR
		|| str[k] == ALT_COMMENT_CHAR))
		s->i -= 1;
	else
		return ((intptr_t)token_free(LEXICAL_ERROR, &token));
	ft_memdel((void**)&token.name);
	return (TRUE);
}

/*
** We enter parsing_exec once we have parsed and fill the header. Here we will
** need a chained list of labels and of op, contained in [stack]
** The first character we encounter can be a label or an op. We check wich one
** it is in [is_label_or_op]. If it is a label, we will be out of the function
** after the [:] char. If it is an op_code, we are out of [is_label_or_op] once
** we have read the entire line [s->i] keeps track of where we are at
** in the line.
*/

int			parsing_exec(t_stack *stack, int fd, t_s *s)
{
	stack->first_label = NULL;
	stack->label_list = NULL;
	stack->first_op = NULL;
	stack->op_list = NULL;
	while (gnl(fd, &s->line, s))
	{
		s->i = 0;
		s->l += 1;
		while (diff(s->line[s->i], COMM))
		{
			if (s->line[s->i] != '\0' && diff(s->line[s->i], SPACE))
				if (!is_label_or_op(s, stack) && !just_free(s->gnl->tab, NULL))
				{
					free_op_lab(stack);
					return ((intptr_t)just_free(s->line, s->gnl));
				}
			s->i += 1;
		}
		ft_memdel((void**)&s->line);
	}
	if (stack->first_op == NULL)
		return ((intptr_t)ft_error(MISSING_CODE, NULL));
	ft_memdel((void**)&s->line);
	just_free(s->gnl->tab, s->gnl);
	return (TRUE);
}
