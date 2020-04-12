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

void	*argz_is_label(t_s *s, t_argz *argz)
{
	int		save;

	s->i += 1;
	save = s->i;
	argz->line = s->l;
	argz->col = save;
	while (diff_com_end(s->line[s->i]) && diff_space(s->line[s->i])
		&& s->line[s->i] != SEPARATOR_CHAR)
		s->i += 1;
	if (s->i - save == FALSE)
		return(ft_error_nb(LABEL_ERROR, NULL, s->l, s->i));
	if (!(argz->lab = ft_memalloc(sizeof(char) * s->i - save)))
		return(ft_error(MALLOC_FAIL, NULL, NULL));
	argz->lab = ft_stricpy(argz->lab, s->line, save, s->i);
	while (save < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[save]) == NULL)
		{
			ft_memdel((void**)&argz->lab);
			return (ft_error_nb(LABEL_ERROR, NULL, s->l, save + 1));
		}
		save++;
	}
	argz->value = 0;
	return (argz);
}

void	*is_argument(t_s *s, size_t inst_type, t_argz *argz, int *sep_char)
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
	{
		argz->line = s->l;
		argz->col = s->i;
		ft_atolong(s, argz);
		argz->lab = NULL;
	}
	else
		if (argz_is_label(s,argz) == NULL)
			return (just_free(argz->lab, NULL));
	if ((diff_com_end(s->line[s->i]) == FALSE) && s->i > 0)
		s->i -= 1;
	if (s->line[s->i] == SEPARATOR_CHAR)
		*sep_char += 1;
	return (argz);
}

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

void	save_token(t_token *token, t_token *last_token, char *str_op, t_s *s)
{
	int	dif;

	dif = token->end - token->col;
	last_token->line = token->line;
	last_token->col = token->col;
	last_token->end = token->end;
	last_token->op_type = token->op_type;
	if (last_token->name != NULL)
		ft_memdel((void**)&last_token->name);
	last_token->name = ft_memalloc(sizeof(char) * dif + 1);
	last_token->name = ft_strcpy(last_token->name, token->name);
	ft_memdel((void**)&token->name);
	token->name = ft_memalloc(sizeof(char) * ft_strlen(str_op));
	token->name = ft_strcpy(token->name, str_op);
	token->line = s->l;
	token->col = s->i;
}

void	update_sep(int *sep_char, int *indx_sep, int i)
{
	if (i == INIT)
	{
		*sep_char = 0;
		*indx_sep = 0;
	}	
	else
	{
		*sep_char += 1;
		*indx_sep = i;
	}
}

int	get_arg(t_token *token, t_s *s, t_instruct *op, int *info)
{
	fill_token(s, op->type, token);
	if (check_sep(info, token) == FALSE
		|| is_argument(s, op->type, &op->argz[info[ARG_N]], &info[SEP]) == NULL)
		return(FALSE);
	return (TRUE);
}

int	final_check(t_token *token, t_token *last_token, int *info, t_instruct *op)
{
	if (info[ARG_N] < g_op_tab[op->type - 1].arg_nb)
		return ((int)token_free(MISSING_ARG, token));
	if (check_sep(info, last_token) == FALSE)
		return(FALSE);
	just_free(token->name, last_token->name);
	return (TRUE);
}

int	read_line(t_s *s, t_instruct *op, t_token *t, t_token *last_t)
{
	int		info[3];
	
	info[ARG_N] = 0;
	update_sep(&info[SEP], &info[INDX], INIT);
	while (diff_com_end(s->line[s->i]) == TRUE)
	{
		if (s->line[s->i] != '\0' && (diff_space(s->line[s->i]) == TRUE))
		{
			if (s->line[s->i] != SEPARATOR_CHAR)
			{
				if (get_arg(t, s, op, info) == FALSE)
					return(FALSE);
				save_token(t, last_t, g_op_tab[op->type - 1].name, s);
				if (!(check_value(op->argz[info[ARG_N]], info[ARG_N], t, last_t)))
					return(FALSE);
				if (s->line[s->i] != SEPARATOR_CHAR)
					if (!(check_value(op->argz[info[ARG_N]], info[ARG_N], t, last_t)))
						return(FALSE);
				info[ARG_N] += 1;
			}
			else
				update_sep(&info[SEP], &info[INDX], s->i);
		}
		s->i += 1;
	}
	return (final_check(t, last_t, info, op) == FALSE ? FALSE : TRUE);
}

int	check_args(t_s *s, t_instruct *op)
{
	t_token		token;
	t_token		last_token;

	init_token(&token);
	init_token(&last_token);
	if (read_line(s, op, &token, &last_token) == FALSE)
		return ((int)just_free(token.name, last_token.name));
	return (TRUE);
}
