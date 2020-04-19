/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/09 16:05:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** If the argument is a register, it should have a value betweem 1 and 16
** Here we also check if the type of arg (T_REG, T_DIR or T_IND) is
** corresponding to the ones listed in op.c (g_op_tab[op_type].arg_types[K]).
** [k] is the number of arguments we have found.
*/

int		check_value(t_argz argz, int k, t_token *token, t_token *last_token)
{
	int	t;

	t = argz.type;
	if (t == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((intptr_t)token_free(WRONG_REG_NUM, last_token));
	if (k < g_op_tab[token->op_type - 1].arg_nb
		&& (t & g_op_tab[token->op_type - 1].arg_types[k]) != t)
		return ((intptr_t)token_free(WRONG_TYPE_ARG, token));
	if (k >= g_op_tab[token->op_type - 1].arg_nb)
		return ((intptr_t)token_free(TOO_MANY_ARGS, token));
	return (TRUE);
}

/*
** An op_code should be followed by it's argument, each of them separated by
** only one SEP_CHAR. info[ARG_N] is the number of argument we are dealing with.
*/

int		check_sep(int *info, t_token *token)
{
	int	save;
	int	k;

	k = info[ARG];
	save = token->col;
	token->col = info[INDX];
	if (k == 0 && info[SEP] > 0)
		return ((intptr_t)token_free(TOO_MANY_SEP_B, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k > info[SEP])
		return ((intptr_t)token_free(MISSING_SEP, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k < info[SEP])
		return ((intptr_t)token_free(TOO_MANY_SEP_B, token));
	if (k == g_op_tab[token->op_type - 1].arg_nb
		&& info[SEP] >= g_op_tab[token->op_type - 1].arg_nb)
		return ((intptr_t)token_free(TOO_MANY_SEP_A, token));
	token->col = save;
	return (TRUE);
}

/*
** We often need to check if we encounter space, tabs, comment, "\n" or "\0"
** while reading a line.
*/

int		diff(char c, int mode)
{
	if (mode == SPACE)
		if (c != ' ' && c != '\t')
			return (TRUE);
	if (mode == COMM)
		if (c != '\0' && c != COMMENT_CHAR
		&& c != ALT_COMMENT_CHAR && c != '\n')
			return (TRUE);
	if (mode == SPACE_COMM)
		if (c != '\0' && c != COMMENT_CHAR && c != ALT_COMMENT_CHAR && c != '\n'
			&& c != ' ' && c != '\t')
			return (TRUE);
	return (FALSE);
}

/*
** There is only a limited list of op_code available (16) with specific names
** we can compare the name we have read with the names contains in op.c
** If we find it we return its index ("live" is at the index "0" of g_op_tab,
** so it is the op_code number 1).
*/

int		find_opcode(char *string)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(string, g_op_tab[i].name))
			return (i + 1);
		i++;
	}
	return (0);
}

/*
** Find_label is used at the end: when an argument is a "call to label" we need
** to check if this label exists or not.
** If it does we return the octet [oct_lab] of the label we found so we can
** write in our file the difference between the current op_code and this
** label's oct. If not, then it means this label doesn't exist in our
** chained list.
*/

int		find_label(t_argz argz, t_label *label)
{
	int			oct_lab;
	t_token		token;
	char		*to_find;

	to_find = argz.lab;
	token.name = NULL;
	while (label != NULL)
	{
		if (!ft_strcmp(label->name, to_find))
		{
			oct_lab = label->oct;
			return (oct_lab);
		}
		else
			label = label->next;
	}
	if (!(token.name = ft_memalloc(sizeof(char) * ft_strlen(to_find) + 1)))
		return ((intptr_t)ft_error(MALLOC_FAIL, NULL));
	token.name = ft_strcpy(token.name, to_find);
	token.line = argz.line;
	token.col = argz.col;
	return ((intptr_t)token_free(WRONG_LABEL, &token));
}
