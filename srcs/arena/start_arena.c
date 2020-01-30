/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:30:14 by dberger           #+#    #+#             */
/*   Updated: 2020/01/30 15:07:22 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/*
** We initiate the arena by copying the executable code of its champion in the
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

	if (!(process = malloc(sizeof(t_process))))
		return (NULL);
	process->bytecode_size = 0;
	process->carry = 0;
	process->PC = 0;
	process->current_op = NULL;
	process->last_live = 0;
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
	t_process	*save;
	t_process	*new;
	int			i;
	int			pc;

	i = 0;
	pc = 0;
	process = make_process();
	save = process;
	while (i < vm->nb_champs)
	{
		process->registre[0] = i + 1;
		// what about (-) ? //
		process->owner = &vm->champion_table[i];
		process->PC = pc;
		new = make_process();
		process->next_table = new;
		process = process->next_table;
		i++;
		pc += (MEM_SIZE / vm->nb_champs);
	}
	process = save;
	return (process);
}

t_args		*make_args(void)
{
	t_args *args;

	if (!(args = malloc(sizeof(t_args))))
		return (NULL);
	set_args_to_zero(args);
	return (args);
}

int			init_var(t_arena *vm)
{
	t_process	*process;
	t_args		*args;

	process = make_process_list(vm);
	args = make_args();
	if (process == NULL || args == NULL)
		return (FALSE);
	vm->last_live_champ_number = vm->nb_champs;
	vm->cycle = 0;
	vm->total_live_since_check = 0;
	vm->cycles_since_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->args = args;
	vm->process_list = process;
	vm->max_checks = 0;
	return (TRUE);
}

void		fill_arena(t_arena *vm, t_champion *champ, int indx)
{
	int		size;
	int		i;

	size = champ->header.prog_size - SIZE_HEADER;
	i = 0;
	while (i < MEM_SIZE / vm->nb_champs)
	{
		if (i <= size)
		{
			vm->memory[indx + i] = champ->prog[SIZE_HEADER + i];
			vm->memory_color[indx + i] = champ->number + '0';
		}
		else
		{
			vm->memory[indx + i] = '\0';
			vm->memory_color[indx + i] = '0';
		}
		i++;
	}
}

int			start_arena(t_arena *vm, t_champion *champ)
{
	int			i;
	int			s;
	int			indx;

	i = 0;
	s = 1;
	indx = 0;
	init_var(vm);
	while (i < vm->nb_champs && s <= vm->nb_champs && indx < MEM_SIZE)
	{
		champ = &vm->champion_table[i];
		if (champ->number == s)
		{
			fill_arena(vm, champ, indx);
			indx += (MEM_SIZE / vm->nb_champs);
			s++;
			i = 0;
		}
		else
			i++;
	}
	return (TRUE);
}
