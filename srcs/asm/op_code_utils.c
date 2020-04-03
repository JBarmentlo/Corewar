/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_code_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:48:14 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 20:14:12 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	fill_token(t_s *s, int op_type, t_token *token)
{
	int 	l;
	int 	save;

	l = 0;
	save = s->i;
	if (token->name != NULL)
		ft_memdel((void**)&token->name);
	while (s->line != NULL && s->line[save] != '\0' && s->line[save] != ' ' && s->line[save] != '\t'
		&& s->line[save] != COMMENT_CHAR && s->line[save] != ALT_COMMENT_CHAR
		&& s->line[save] != SEPARATOR_CHAR)
	{
		if (op_type == 42 && (s->line[save] == LABEL_CHAR || s->line[save] == DIRECT_CHAR))
			break;
		l++;
		save++;
	}
	token->name = ft_memalloc(sizeof(char *) * l + 1);
	if (token->name == NULL)
		return ((int)ft_error("Can't allocate token", NULL, NULL));
	token->name = ft_strncat(token->name, s->line + s->i, l);
	token->line = s->l;
	token->col = s->i;
	token->end = s->i + l;
	token->op_type = op_type;
	return (TRUE);	
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

int		encoding_byte(t_instruct *op)
{
	int			i;
	size_t		k;

	i = 0;
	k = 0;
	while (k < op->nb_args)
	{
		i = i | op->argz[k].code;
		i = i << 2;
		k++;
	}
	while (k < (BITS_IN_OCTET / 2) - 1)
	{
		i = i | 0;
		i = i << 2;
		k++;
	}
	return (i);
}

int		find_label(char *to_find, t_label *label)
{
	int		oct_lab;

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
	return (FALSE);
}

int		write_op_values(t_file *out_file, int *i, t_instruct *op, t_stack stack)
{
	size_t	k;
	int	to_label;
	t_label	*label;

	k = 0;
	label = stack.first_label;
	while (k < op->nb_args)
	{
		if (op->argz[k].type == T_REG)
		{
			if (op->argz[k].value > REG_NUMBER)
				return (FALSE);
			write_in_file(out_file, *i, op->argz[k].value);
			*i += 1;
		}
		else if (op->argz[k].lab == NULL)
		{
			nb_to_binary(out_file, op->argz[k].oct, *i, op->argz[k].value);
			*i += op->argz[k].oct;
		}
		else if (op->argz[k].lab != NULL)
		{
			to_label = find_label(op->argz[k].lab, label);
			if (to_label == FALSE)
				return ((int)ft_error_nb(WRONG_LABEL, op->argz[k].lab, op->argz[k].line, op->argz[k].col));
			nb_to_binary(out_file, op->argz[k].oct, *i, (to_label - op->oct));
			*i += op->argz[k].oct;
		}
		k++;
	}
	return (TRUE);
}
