#include "asm.h"

int	is_valid_command_start(t_s *s, int *type, t_token *token)
{
	fill_token(s, 0, token);
	if (*type == 'n')
	{
		if (ft_strncmp(s->line + s->i, NAME_CMD_STRING, 5) != 0)
			return ((int)token_free(WRONG_HEADER, token));
	}
	else if (*type == 'c')
	{
		if (ft_strncmp(s->line + s->i, COMMENT_CMD_STRING, 8) != 0)
			return ((int)token_free(WRONG_HEADER, token));
	}
	else
		return ((int)token_free(INVALID_COMMAND, token)); // token name ??
	return (TRUE);
}

int	is_valid_command_end(t_s *s, int *type, t_token *token)
{
	fill_token(s, 0, token);
	s->i += (*type == 'n' ? 5 : 8);
	while (s->line[s->i] != '\0' && s->line[s->i] != '"')
	{
		if (diff_space(s->line[s->i]) == TRUE)
			return ((int)token_free(WRONG_FORMAT, token));
		s->i += 1;
	}
	if (s->line[s->i] != '"')
		return ((int)token_free(WRONG_FORMAT, token));
	s->i += 1;
	ft_memdel((void**)&token->name);
	return (TRUE);
}

int     get_command_type(int fd, t_s *s, int *type, t_token *token)
{
	while (get_next_line(fd, &s->line) && s->line != NULL)
	{
		s->l += 1;
		s->i = 0;
		fill_token(s, 0, token);
		while ((diff_com_end(s->line[s->i]) == TRUE) && s->line[s->i] != '.')
		{
			if ((diff_space(s->line[s->i]) == TRUE) && fill_token(s, 0, token))
				return ((int)token_free(WRONG_HEADER, token));
			s->i += 1;
		}
		if (s->line[s->i] == '.')
			break ;
		ft_memdel((void**)&s->line);
		ft_memdel((void**)&token->name);
	}
	if (s->line == NULL && (token->line += 1))
		return ((int)token_free(INCOMPLETE, token));
	*type = s->line[s->i + 1];
	if (is_valid_command_start(s, type, token) == FALSE)
		return (FALSE);
	if (is_valid_command_end(s, type, token) == FALSE)
		return (FALSE);
	return (TRUE);
}
