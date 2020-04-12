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
	while (diff(s->line[s->i], SPACE_COMM) && s->line[s->i] != SEPARATOR_CHAR)
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
	if ((diff(s->line[s->i], COMM) == FALSE) && s->i > 0)
		s->i -= 1;
	if (s->line[s->i] == SEPARATOR_CHAR)
		*sep_char += 1;
	return (argz);
}
