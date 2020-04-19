/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:29:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/09 16:05:13 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** On octet is on 4 bits. if the arguments are a register, a direct and
** an indirect: the encoding byte will be 01-10-11, so in binary 00011011
** which is in decimal: 27 (the number we need to write on this octet).
*/

int			encoding_byte(t_instruct *op)
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

int			big_number(t_s *s, t_argz *argz, char *str)
{
	argz->value = 4294967295;
	while (ft_isdigit((long)str[s->i]) && diff(str[s->i], SPACE_COMM))
		s->i += 1;
	if (s->i > 0)
		s->i -= 1;
	return (TRUE);
}

/*
** This atolong is special: if we overcome the 63 bits for a number we imitate
** the behavior of the zaz_vm (the number becomes automatically 0xffff)
*/

int			ft_atolong(t_s *s, t_argz *argz)
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

/*
** An op_code takes : 1 octet to write its type, then 1 octet if there is
** an encoding_byte need, then finally the octet taken by its arguments
** (it can be 1, 2 or 4 according to their types).
*/

void		update_oct(t_instruct *op, int *cur_octet, t_s *s)
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

/*
** Here we have found a character that is not a label (so not ending with [:])
** Now we need to see if it is a correct op_code (find_op_code).
** Then we need to check if its argument are valid [parsing_args].
** Finally in update_oct we calculate how many octet we would move forward
** if we were writing this in the final .cor file
*/

t_instruct	*is_op(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	if (!(op = ft_memalloc(sizeof(t_instruct))))
		return (NULL);
	op->next = NULL;
	op->type = find_opcode(token->name);
	if (op->type == 0)
	{
		ft_memdel((void**)&op);
		if (!ft_strcmp(token->name, NAME_CMD_STRING)
			|| !ft_strcmp(token->name, COMMENT_CMD_STRING))
			return (token_free(COMMAND_TWICE, token));
		return (token_free(WRONG_SYNTAX_OP, token));
	}
	op->nb_args = g_op_tab[op->type - 1].arg_nb;
	op->oct = stack->cur_octet;
	if (parsing_args(s, op) == FALSE)
		return (free_op(op));
	update_oct(op, &stack->cur_octet, s);
	return (op);
}
