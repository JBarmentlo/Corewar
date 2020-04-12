#include "asm.h"

void	*free_label(t_label *label)
{
	t_label		*save_label;

	while (label != NULL)
	{
		save_label = label->next;
		ft_memdel((void**)&label->name);
		ft_memdel((void**)&label);
		label = save_label;
	}
	return (NULL);
}

void	*free_op(t_instruct *op)
{
	t_instruct	*save_op;
	t_argz		argz;
	size_t		k;

	while (op != NULL)
	{
		k = 0;
		save_op = op->next;
		while (k < op->nb_args)
		{
			argz = op->argz[k];
			if (argz.lab != NULL)
				ft_memdel((void**)&argz.lab);
			k++;
		}
		ft_memdel((void**)&op);
		op = save_op;
	}
	return (NULL);
}

void	*free_op_lab(t_stack *stack)
{
	t_label		*label;
	t_instruct	*op;

	label = stack->first_label;
	op = stack->first_op;
	free_label(label);
	free_op(op);
	stack->first_op = NULL;
	stack->op_list = NULL;
	stack->first_label = NULL;
	stack->label_list = NULL;
	return (NULL);
}

void	*token_free(char *str, t_token *token)
{
	char 	*name;
	int	l;
	int	c;
	

	name = token->name;
	l = token->line;
	c = token->col;
	if (token->name != NULL)
		ft_printf("Error [%d:%d]: %s: [%s]\n", l, c, str, name);
	else
		ft_printf("Error [%d:%d]: %s\n", l, c, str);
	ft_memdel((void**)&token->name);
	return (NULL);
}

void	*just_free(void *to_free1, void *to_free2)
{
	if (to_free1 != NULL)
		ft_memdel((void**)&to_free1);
	if (to_free2 != NULL)
		ft_memdel((void**)&to_free2);
	return (NULL);
}
