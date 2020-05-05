/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:30:14 by dberger           #+#    #+#             */
/*   Updated: 2020/04/30 19:30:16 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/*
** We initialize the arena by copying the executable code of its champion in the
** arena. The code of the champion number 1, will be copied from the beggining
** of the VM (index 0). Then for the 2nd champion, we move to the index:
** (0 + MEM_SIZE / number of champions). If there are, for instance,
** 3 champions, the code of the 2nd champion will be copied in the array
** 'memory' at the index 1365, the 3rd will start at the index 2730.
*/

t_process	*make_process(void)
{
	t_process	*process;
	int			i;

	if (!(process = ft_memalloc(sizeof(t_process))))
		return (NULL);
	process->bytecode_size = 0;
	process->carry = 0;
	process->pc = 0;
	process->current_op = NULL;
	process->last_live = -123456798;
	process->table_pos = 0;
	process->alive = 1;
	process->owner = NULL;
	process->next_list = NULL;
	process->next_table = NULL;
	i = 0;
	while (i < REG_NUMBER)
	{
		process->registre[i] = 0;
		i++;
	}
	return (process);
}

t_process	*make_process_list(t_arena *vm)
{
	t_process	*process;
	int			i;
	int			pc;

	i = 0;
	pc = 0;
	while (i < vm->nb_champs)
	{
		if (!(process = make_process()))
			return (NULL);
		process->owner = &vm->champion_table[i];
		process->registre[0] = -process->owner->number;
		process->pc = pc;
		add_process_to_list(process, vm);
		add_process_to_table(process, vm, 0);
		i++;
		pc += (MEM_SIZE / vm->nb_champs);
	}
	return (process);
}

t_args		*make_args(void)
{
	t_args *args;

	if (!(args = ft_memalloc(sizeof(t_args))))
		return (NULL);
	set_args_to_zero(args);
	return (args);
}

int			init_var(t_arena *vm)
{
	t_process	*process;
	t_args		*args;

	if (!(process = make_process_list(vm)))
		return (FALSE);
	if (!(args = make_args()))
	{
		ft_memdel((void**)&process);
		return (FALSE);
	}
	vm->last_live_champ_number = vm->nb_champs;
	vm->cycle = 0;
	vm->total_live_since_check = 0;
	vm->cycles_since_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->args = args;
	vm->process_list = process;
	vm->max_checks = 0;
	if (fill_fun_ptr_tab(vm) == FALSE)
		return (FALSE);
	return (TRUE);
}

int			start_arena(t_arena *vm)
{
	int			i;
	int			s;
	int			indx;
	t_champion	champ;

	i = 0;
	s = 1;
	indx = 0;
	init_var(vm);
	while (i < vm->nb_champs && s <= vm->nb_champs && indx < MEM_SIZE)
	{
		champ = vm->champion_table[i];
		if (champ.number == s)
		{
			fill_arena(vm, &champ, indx);
			indx += (MEM_SIZE / vm->nb_champs);
			s++;
			i = 0;
		}
		else
			i++;
	}
	return (TRUE);
}
