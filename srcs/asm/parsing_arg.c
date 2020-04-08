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
	while (diff_com_end(s->line[s->i]) && diff_space(s->line[s->i]) && s->line[s->i] != SEPARATOR_CHAR)
		s->i += 1;
	if (s->i - save == FALSE)
		return(ft_error_nb(LABEL_ERROR, NULL, s->l, s->i));
	argz->lab = ft_memalloc(sizeof(char) * s->i - save);
	if (argz->lab == NULL)
		return(ft_error("Memory allocation failure for an [argz->lab]", NULL, NULL));
	argz->lab = ft_stricpy(argz->lab, s->line, save, s->i);
	while (save < s->i)
	{
		if (ft_strchr(LABEL_CHARS, (int)s->line[save]) == NULL)
			return (ft_error_nb(LABEL_ERROR, NULL, s->l, save + 1));
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
	return (argz);
}

int	check_value(t_argz argz, int k, t_token *token, t_token *last_token)
{
	if (argz.type == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((int)token_free(WRONG_REG_NUM, last_token));
	if (k < g_op_tab[token->op_type - 1].arg_nb
		&& (argz.type & g_op_tab[token->op_type - 1].arg_types[k]) != argz.type)
		return ((int)token_free(WRONG_TYPE_ARG, token));
	if (k >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_ARGS, token));
	return (TRUE);
}

int		check_sep(int sep_char, int k, t_token *token, int indx_sep)
{
	int	save;

	save = token->col;
	token->col = indx_sep;
	if (k == 0 && sep_char > 0)
		return ((int)token_free(TOO_MANY_SEP_B, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k > sep_char)
		return ((int)token_free(MISSING_SEP, token));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k < sep_char)
		return ((int)token_free(TOO_MANY_SEP_B, token));
	if (k == g_op_tab[token->op_type - 1].arg_nb && sep_char >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_SEP_A, token));
	token->col = save;
	return (TRUE);
}

void	save_token(t_token *token, t_token *last_token, char *str_op, t_s *s)
{
	last_token->line = token->line;
	last_token->col = token->col;
	last_token->end = token->end;
	last_token->op_type = token->op_type;
	if (last_token->name != NULL)
		ft_memdel((void**)&last_token->name);
	last_token->name = ft_memalloc(sizeof(char) * (token->end - token->col) + 1);
	last_token->name = ft_strcpy(last_token->name, token->name);
	ft_memdel((void**)&token->name);
	token->name = ft_memalloc(sizeof(char) * ft_strlen(str_op));
	token->name = ft_strcpy(token->name, str_op);
	token->line = s->l;
	token->col = s->i;
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
	init_token(&token);
	init_token(&last_token);
	while (diff_com_end(s->line[s->i]) == TRUE)
	{
		if (s->line[s->i] != '\0' && (diff_space(s->line[s->i]) == TRUE))
		{
			if (s->line[s->i] != SEPARATOR_CHAR)
			{
				fill_token(s, op->type, &token);
				if (check_sep(sep_char, k, &token, indx_sep) == FALSE)
					return ((int)just_free(last_token.name, NULL));
				argz = op->argz[k];
				if (is_argument(s, op->type, &argz) == NULL)
					return ((int)just_free(token.name, last_token.name));
				if (s->line[s->i] == SEPARATOR_CHAR)
					sep_char++;
				save_token(&token, &last_token, g_op_tab[op->type - 1].name, s);
				if (check_value(argz, k, &token, &last_token) == FALSE)
					return ((int)just_free(token.name, last_token.name));
				if (s->line[s->i] != SEPARATOR_CHAR)
					if (check_value(argz, k, &token, &last_token) == FALSE)
						return ((int)just_free(token.name, last_token.name));
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
		return ((int)just_free(token.name, NULL));
	ft_memdel((void**)&last_token.name);
	if (k < g_op_tab[op->type - 1].arg_nb)
		return ((int)token_free(MISSING_ARG, &token));
	ft_memdel((void**)&token.name);
	return (TRUE);
}
