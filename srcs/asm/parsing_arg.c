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

void	numeric_value(t_s *s, t_argz *argz)
{
	argz->line = s->l;
	argz->col = s->i;
	ft_atolong(s, argz);
	argz->lab = NULL;
}

void	*argz_is_label(t_s *s, t_argz *argz)
{
	int		k;
	int		save;

	k = 0;
	s->i += 1;
	save = s->i;
	argz->line = s->l;
	argz->col = save;
	while (s->line[s->i] != '\0' && s->line[s->i] != SEPARATOR_CHAR && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR && s->line[s->i] != ' ' && s->line[s->i] != '\t')
	{
		s->i += 1;
		k++;
	}
	argz->lab = ft_memalloc(sizeof(char) * k);
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
		numeric_value(s, argz);
	else
		if (argz_is_label(s,argz) == NULL)
			return (just_free(argz->lab, NULL));
	if ((s->line[s->i] == '\0' || s->line[s->i] == COMMENT_CHAR || s->line[s->i] == ALT_COMMENT_CHAR) && s->i > 0)
		s->i -= 1;
	return (argz);
}

int		check_value(t_argz argz, t_instruct *op, int k, t_s *s)
{
	if (argz.type == T_REG && (argz.value > REG_NUMBER || argz.value < 1))
		return ((int)ft_error_nb(WRONG_REG_NUM, NULL, s->l, s->i));
	if ((argz.type & g_op_tab[op->type - 1].arg_types[k]) != argz.type)
		return ((int)ft_error_nb(WRONG_TYPE_ARG, g_op_tab[op->type - 1].name, s->l, s->i));
	return (TRUE);
}

int		check_sep(int sep_char, int k, t_token *token, int indx_sep)
{
	token->col = indx_sep;
	if (k == 0 && sep_char > 0)
		return ((int)token_free(TOO_MANY_SEP_B, token, NULL));
	if (sep_char >= g_op_tab[token->op_type - 1].arg_nb)
		return ((int)token_free(TOO_MANY_SEP_A, token, NULL));
	if (k == g_op_tab[token->op_type - 1].arg_nb - 1 && sep_char < k)
		return (TRUE);
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k > sep_char)
		return ((int)token_free(MISSING_SEP, token, NULL));
	if (k > 0 && (k < g_op_tab[token->op_type - 1].arg_nb) && k < sep_char)
		return ((int)token_free(TOO_MANY_SEP_B, token, NULL));
	return (TRUE);
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
	token.name = NULL;
	last_token.name = NULL;
	while (s->line[s->i] != '\0' && s->line[s->i] != COMMENT_CHAR && s->line[s->i] != ALT_COMMENT_CHAR)
	{
		if (s->line[s->i] != ' ' && s->line[s->i] != '\t' && s->line[s->i] != '\0')
		{
			if (k >= g_op_tab[op->type - 1].arg_nb && s->line[s->i] != SEPARATOR_CHAR)
			{
				ft_memdel((void**)&token.name);
				return ((int)ft_error_nb(TOO_MANY_ARGS, g_op_tab[op->type - 1].name, s->l, s->i));
			}
			if (s->line[s->i] != SEPARATOR_CHAR)
			{
				fill_token(s, op->type, &token);
				if (check_sep(sep_char, k, &token, indx_sep) == FALSE)
					return ((int)just_free(token.name, NULL));
				argz = op->argz[k];
				if (is_argument(s, op->type, &argz) == NULL)
					return ((int)just_free(token.name, NULL));
				if (s->line[s->i] == SEPARATOR_CHAR)
					sep_char++;
				last_token = token;
				fill_token(s, op->type, &token);
				if (check_value(argz, op, k, s) == FALSE)
					return ((int)just_free(token.name, NULL));
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
	ft_memdel((void**)&token.name);
	if (k < g_op_tab[op->type - 1].arg_nb)
		return ((int)ft_error_nb(MISSING_ARG, g_op_tab[op->type - 1].name, s->l, s->i));
	return (TRUE);
}
