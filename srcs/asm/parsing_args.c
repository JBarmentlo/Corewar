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

/*
** Here we check if each argument is separated by only one separator_char and
** if the value and amount of arguments  is correct (direct, indirect or register)
*/

int	get_arg(t_token *token, t_s *s, t_instruct *op, int *info)
{
	t_argz argz;

	argz = op->argz[info[ARG_N]];
	fill_token(s, op->type, token);
	if (check_sep(info, token) == FALSE
		|| is_argument(s, op->type, &argz, &info[SEP]) == NULL)
	{
		op->argz[info[ARG_N]] = argz;
		op->next = NULL;
		return(FALSE);
	}
	op->argz[info[ARG_N]] = argz;
	op->next = NULL;
	return (TRUE);
}

/*
** In final check we have already read all the line: we need to check if there is sufficient
** arguments (by comparing info[ARG_N] to the number of args necessary according to op.c
** Then we check if there is not too many separator char after the last argument
*/

int	final_check(t_token *token, t_token *last_token, int *info, t_instruct *op)
{
	if (info[ARG_N] < g_op_tab[op->type - 1].arg_nb)
		return ((int)token_free(MISSING_ARG, token));
	if (check_sep(info, last_token) == FALSE)
		return(FALSE);
	just_free(token->name, last_token->name);
	return (TRUE);
}

/*
** The function [diff(char c, COMM)] check if we don't encounter "\0", "\n", "#" or ";"
** The function [diff(char c, SPACE)] check if we don't encounter " " or "\t".
** In [info] we have the number of arguments we have found [ARG_N], the number of SEPARATOR_CHAR
** in [info[SEP]] and the index where is this separator_char in info[INDX].
** We need two token: the current one and the last one, to have error message more understandable.
*/

int	read_line(t_s *s, t_instruct *op, t_token *t, t_token *last_t)
{
	int		info[3];
	
	info[ARG_N] = 0;
	update_sep(&info[SEP], &info[INDX], INIT);
	while (diff(s->line[s->i], COMM) == TRUE)
	{
		if (s->line[s->i] != '\0' && (diff(s->line[s->i], SPACE) == TRUE))
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

/*
** When we arrive in parsing_args, we already have a valid op_code
** We need to check if on the same line (read_line) there is all the necessary
** types of arguments. And finally we want to make sure that any line, so any
** instruction ends with a "\n" (END_INPUT).
*/

int	parsing_args(t_s *s, t_instruct *op)
{
	t_token		token;
	t_token		last_token;

	init_token(&token);
	init_token(&last_token);
	if (read_line(s, op, &token, &last_token) == FALSE)
		return ((int)just_free(token.name, last_token.name));
	token.name = NULL;
	token.col = s->i;
	token.line = s->l;
	if (s->line[s->i] == COMMENT_CHAR || s->line[s->i] == ALT_COMMENT_CHAR)
		while (s->line[s->i] != '\0' && s->line[s->i] != '\n')
			s->i += 1;
	if (s->line[s->i] != '\n')
		return ((int)token_free(END_INPUT, &token));
	return (TRUE);
}
