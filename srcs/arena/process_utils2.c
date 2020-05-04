/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:09:25 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/30 09:26:29 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		free_all_processes(t_arena *arena)
{
	t_process	*it;
	t_process	*tmp;

	it = arena->process_list;
	while (it)
	{
		tmp = it->next_list;
		bzero(it, sizeof(t_process));
		free(it);
		it = tmp;
	}
}
