/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/05/06 20:24:15 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** The type of an argument tells us if it is a register, direct or indirect
** It's code helps us calculate the encoding byte later (01 for T_REG, 10 for
** T_DIR, 11 for T_IND).
** [argz->oct] determines the number of "space" in octet taken by this argument.
** A register takes only 1 octet in the exec_code, an indirect takes 2, and
** for direct arguments it depends (2 or 4): we need to check the op.c file, at
** the "is_direct_small" section.
*/

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

/*
** A direct or indirect argument can see it's value expressed as a label
** The label can only be written with char contained in LABEL_CHARS.
** It's numeric value can only be determine after the entire parsing is done
** If the argument is calling the label "loop", we will check at the end
** at which octet we have encountered this label and caculate the difference
** between the current op_code and the label that is called as an argument.
*/

void	*argz_is_label(t_s *s, t_argz *argz, t_token *token)
{
	s->i += 1;
	argz->col = s->i;
	init_token(token);
	if (fill_token(s, 0, token) == FALSE)
		return (NULL);
	while (diff(s->line[s->i], SPACE_COMM) && s->line[s->i] != SEPARATOR_CHAR)
		s->i += 1;
	if (s->i - argz->col == FALSE)
		return (token_free(LABEL_ERROR, token));
	if (!(argz->lab = ft_memalloc(sizeof(char) * s->i - argz->col)))
		return (ft_error(MALLOC_FAIL, NULL));
	argz->lab = ft_stricpy(argz->lab, s->line, argz->col, s->i);
	while (argz->col < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[argz->col]) == NULL)
		{
			ft_memdel((void**)&argz->lab);
			token->col = argz->col + 1;
			return (token_free(LABEL_ERROR, token));
		}
		argz->col += 1;
	}
	argz->value = 0;
	ft_memdel((void**)&token->name);
	return (argz);
}

/*
** Here we determine the type of argument that we encounter, and fill it's
** information to easily write it down later in bytecode.
** The arguments can be : register - direct - or indirect. If it is a direct
** or indirect argument, it's value can be expressed as a "label call"
*/

void	*is_argument(t_s *s, size_t inst_type, t_argz *argz, int *sep_char)
{
	t_token	token;

	if (s->line[s->i] == 'r')
		is_register(argz);
	else if (s->line[s->i] == DIRECT_CHAR)
		is_direct(argz, inst_type);
	else
		is_indirect(argz);
	if (s->line[s->i] != LABEL_CHAR && argz->type != T_IND)
		s->i += 1;
	argz->line = s->l;
	if (s->line[s->i] != '\0' && s->line[s->i] != LABEL_CHAR)
	{
		argz->col = s->i;
		ft_atolong(s, argz);
		argz->lab = NULL;
	}
	else if (argz_is_label(s, argz, &token) == NULL)
		return (just_free(argz->lab, token.name));
	if ((diff(s->line[s->i], COMM) == FALSE) && s->i > 0)
		s->i -= 1;
	if (s->line[s->i] == SEPARATOR_CHAR)
		*sep_char += 1;
	return (argz);
}
