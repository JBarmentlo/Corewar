/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/09 16:05:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_value(t_argz argz, int k, t_token *token, t_token *last_token)
{
	int	t;

	t = argz.type;
	if (t == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((int)token_free(WRONG_REG_NUM, last_token));
	if (k < g_op_tab[token->op_type - 1].arg_nb
		&& (t & g_op_tab[token->op_type - 1].arg_types[k]) != t)
		return ((int)token_free(WRONG_TYPE_ARG, token));
	if (k >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_ARGS, token));
	return (TRUE);
}

int		check_sep(int *info, t_token *token)
{
	int	save;
	int	k;

	k = info[ARG_N];
	save = token->col;
	token->col = info[INDX];
	if (k == 0 && info[SEP] > 0)
		return ((int)token_free(TOO_MANY_SEP_B, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k > info[SEP])
		return ((int)token_free(MISSING_SEP, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k < info[SEP])
		return ((int)token_free(TOO_MANY_SEP_B, token));
	if (k == g_op_tab[token->op_type - 1].arg_nb
		&& info[SEP] >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_SEP_A, token));
	token->col = save;
	return (TRUE);
}

int	diff(char c, int mode)
{
	if (mode == SPACE)
		if (c != ' ' && c != '\t')
			return (TRUE);
	if (mode == COMM)
		if (c != '\0' && c != COMMENT_CHAR && c != ALT_COMMENT_CHAR && c != '\n')
			return (TRUE);
	if (mode == SPACE_COMM)
		if (c != '\0' && c != COMMENT_CHAR && c != ALT_COMMENT_CHAR && c != '\n'
			&& c != ' ' && c != '\t')
			return (TRUE);
	return (FALSE);
}

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

int		find_label(t_argz argz, t_label *label)
{
	int		oct_lab;
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
	token.name = ft_memalloc(sizeof(char) * ft_strlen(to_find) + 1);
	token.name = ft_strcpy(token.name, to_find);
	token.line = argz.line;
	token.col = argz.col;
	return ((int)token_free(WRONG_LABEL, &token));
}
