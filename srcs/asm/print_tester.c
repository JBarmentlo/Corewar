/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:01:04 by dberger           #+#    #+#             */
/*   Updated: 2020/02/19 15:01:15 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_tester(t_stack *stack)
{
	t_argz argz;
	t_label		*label;
	t_instruct	*op;
	int			i;

	i = 0;
	label = stack->first_label;
	while (label != NULL)
	{
		ft_printf("label name = [%s], octet = [%d]\n", label->name, label->oct);
		label = label->next;
	}
	ft_printf("\n");
	label = stack->first_label;
	op = stack->first_op;
	while (op != NULL)
	{
		ft_printf("op type = [%d], nb_args = [%d]\n", op->type, op->nb_args);
		i = 0;
		while (i < (int)op->nb_args)
		{
			argz = op->argz[i];
			ft_printf("\targ n-%d: type = [%d], value = [%d], lab = [%s],  oct = [%d]\n", i, argz.type, argz.value, argz.lab, argz.oct);
			i++;
		}
		op = op->next;
	}
	op = stack->first_op;
}