/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/05/06 20:09:14 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Before freeing a label, we need to free its name
*/

void	*free_label(t_label *label)
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

/*
** Before freeing an op, we need to free the "call to label" that
** could contain one of it's arguments (argz.lab);
*/

void	*free_op(t_instruct *op)
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

/*
** While parsing the file .s, we create a chained list of labels,
** and of op_codes. We need to free them and their content.
*/

void	*free_op_lab(t_stack *stack)
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

/*
** Token_free is a function that print an error message corresponding
** to a certain token and its location. Then it frees the token.
*/

void	*token_free(char *str, t_token *token)
{
	int		l;
	int		c;
	char	*name;

	name = token->name;
	l = token->line;
	c = token->col;
	if (token->name != NULL)
		ft_printf("Error [%d:%d]: %s: [%s]\n", l, c, str, name);
	else
		ft_printf("Error [%d:%d]: %s\n", l, c, str);
	ft_memdel((void**)&token->name);
	return (NULL);
}

/*
** This is a helpful function to return (NULL) in a function and free
** what is needed at the same time.
*/

void	*just_free(void *to_free1, void *to_free2)
{
	if (to_free1 != NULL)
		ft_memdel((void**)&to_free1);
	if (to_free2 != NULL)
		ft_memdel((void**)&to_free2);
	return (NULL);
}
