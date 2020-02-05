/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:11:01 by dberger           #+#    #+#             */
/*   Updated: 2020/02/05 18:34:35 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		start_content(t_file *out_file, int fd)
{
	t_stack stack;

	// test //
	(void) fd;
	stack.champion_name = ft_strdup("zork");
	stack.comment = ft_strdup("I'M ALIIIIVE");
	// 		//
	out_file->content = ft_memalloc(MAX_SIZE_FILE);	
	ft_printf("magic = [%x]\n", COREWAR_EXEC_MAGIC);
	return (TRUE);
}
