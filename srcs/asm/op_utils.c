# include "asm.h"

int		encoding_byte(t_instruct *op)
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

int		big_number(t_s *s, t_argz *argz, char *str)
{
	argz->value = 4294967295;
	while (ft_isdigit((long)str[s->i]) && diff(str[s->i], SPACE_COMM))
		s->i += 1;
	if (s > 0)
		s->i -= 1;
	return (TRUE);
}


int		ft_atolong(t_s *s, t_argz *argz)
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

void	update_oct(t_instruct *op, int *cur_octet, t_s *s)
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

t_instruct		*is_op(t_s *s, t_stack *stack, t_token *token)
{
	t_instruct	*op;

	op = ft_memalloc(sizeof(t_instruct));
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
