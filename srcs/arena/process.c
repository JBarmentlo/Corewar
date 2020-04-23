/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deyaberger <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:11:21 by deyaberge         #+#    #+#             */
/*   Updated: 2020/04/23 13:12:19 by deyaberge        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	process_invalid(t_process *process)
{
	process->PC++;
	process->PC = process->PC & MODULO_MASK;
	process->current_op = NULL;
}

void	execute_process(t_arena *arena, t_process *process)
{
	int	pc_jump;

	set_args_to_zero(arena->args);
	if (process->current_op->encoding_byte)
	{
		read_encoding_byte(arena, process);
		if (!is_valid_encoding_byte(arena, process))
			return (process_invalid(process));
	}
	else
		no_encoding_byte(arena, process);
	copy_to_args_tmp(arena, process);
	pc_jump = read_args(arena->args, process);
	if (!is_valid_args_value(arena->args))
	{
		process_invalid(process);
		return ;
	}
	run_function(arena, process);
	if (process->current_op->opcode != 9 || process->carry == 0)
		process->PC = (process->PC + pc_jump +
			process->current_op->encoding_byte + 1) & MODULO_MASK;
	process->current_op = NULL;
	add_process_to_table(process, arena, arena->cycle + 1);
}

void	execute_processes(t_arena *arena)
{
	t_process	*it;
	t_process	*next;

	it = arena->process_table[arena->cycle % PROCESS_TABLE_SIZE];
	while (it != NULL)
	{
		next = it->next_table;
		if (it->current_op == NULL)
		{
			if (is_valid_opcode(arena->memory[it->PC]))
			{
				it->current_op = &g_op_tab[arena->memory[it->PC] - 1];
				add_process_to_table(it, arena, arena->cycle +
					it->current_op->cycle_to_wait);
			}
			else
			{
				it->PC = (it->PC + 1) & MODULO_MASK;
				add_process_to_table(it, arena, arena->cycle + 1);
			}
		}
		else
		{
			if (opcode_to_mask(it->current_op->opcode) & TEST_PRINT)
			{
				printf("\n\n");
				printf("cycle : \t%lu\n", arena->cycle);
				printf("PC:\t\t%d\n", it->PC);
			}
			execute_process(arena, it);
		}
		it = next;
	}
	arena->process_table[arena->cycle % PROCESS_TABLE_SIZE] = NULL;
}
