/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:09:25 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:09:27 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	free_all(t_arena *arena)
{
	free_all_processes(arena);
	arena->process_list = NULL;
	free(arena->args);
	free(arena->op_fun_tab);
}
