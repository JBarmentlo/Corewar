# include "asm.h"

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
	while (s->line != NULL && diff(s->line[save], SPACE_COMM)
		&& s->line[save] != SEPARATOR_CHAR)
	{
		if (op_type == 42
		&& (s->line[save] == LABEL_CHAR || s->line[save] == DIRECT_CHAR))
			break;
		save++;
	}
	token->name = ft_memalloc(sizeof(char *) * (save - s->i + 1));
	if (token->name == NULL)
		return ((int)ft_error(MALLOC_FAIL, NULL));
	token->name = ft_strncat(token->name, s->line + s->i, (save - s->i));
	token->line = s->l;
	token->col = s->i;
	token->end = save;
	token->op_type = op_type;
	return (TRUE);
}
