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

int	diff_com_end(char c)
{
	if (c != '\0' && c != COMMENT_CHAR && c != ALT_COMMENT_CHAR)
		return (TRUE);
	return (FALSE);
}

int	diff_space(char c)
{
	if (c != ' ' && c != '\t')
		return (TRUE);
	return (FALSE);
}

void	init_token(t_token *token)
{
	token->name = NULL;
	token->line = 0;
	token->col = 0;
}

int	fill_token(t_s *s, int op_type, t_token *token)
{
	int 	save;

	save = s->i;
	if (token->name != NULL)
		ft_memdel((void**)&token->name);
	while (s->line != NULL && diff_com_end(s->line[save])
		&& diff_space(s->line[save]) && s->line[save] != SEPARATOR_CHAR)
	{
		if (op_type == 42
		&& (s->line[save] == LABEL_CHAR || s->line[save] == DIRECT_CHAR))
			break;
		save++;
	}
	token->name = ft_memalloc(sizeof(char *) * (save - s->i + 1));
	if (token->name == NULL)
		return ((int)ft_error(MALLOC_FAIL, NULL, NULL));
	token->name = ft_strncat(token->name, s->line + s->i, (save - s->i));
	token->line = s->l;
	token->col = s->i;
	token->end = save;
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

int		big_number(t_s *s, t_argz *argz, char *str)
{
	argz->value = 4294967295;
	while (ft_isdigit((long)str[s->i]) && diff_com_end(str[s->i])
		&& diff_space(str[s->i]))
		s->i += 1;
	if (s > 0)
		s->i -= 1;
	return (TRUE);
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
			return (big_number(s, argz, str));
		s->i += 1;
	}
	argz->value = nb * neg;
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
