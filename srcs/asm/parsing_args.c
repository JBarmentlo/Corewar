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

int	parsing_args(t_s *s, t_instruct *op)
{
	t_token		token;
	t_token		last_token;

	init_token(&token);
	init_token(&last_token);
	if (read_line(s, op, &token, &last_token) == FALSE)
		return ((int)just_free(token.name, last_token.name));
	return (TRUE);
}
