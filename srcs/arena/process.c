#include "arena.h"

void	process_invalid(t_process *process)
{
	process->PC++;
	process->PC = process->PC % MEM_SIZE; //manually replace by bitmask
	process->current_op = NULL;	//will be made obsolete by architecture
}
void	execute_process(t_arena *arena, t_process *process)
{
	int	PC_jump;
	set_args_to_zero(arena->args);
	if (!is_valid_opcode(arena->memory[process->PC])) //to be made redundant by archtecture
	{
		process_invalid(process);
		printf("invalid opcode\n");
		return ;
	}
	process->current_op = &g_op_tab[arena->memory[process->PC] - 1];
	if (process->current_op->encoding_byte)
	{
		bit_dump(arena->memory + 1, 1);
		read_encoding_byte(arena, process);
		if (!is_valid_encoding_byte(arena, process))
		{
			process_invalid(process);
			printf("invalid encoding_byte\n");
			return ;
		}
	}
	else
	{
		no_encoding_byte(arena, process);
	}
	copy_to_args_tmp(arena, process);
	PC_jump = read_args(arena->args, process);
	if (!is_valid_args_value(arena->args))
	{
		process_invalid(process);
		printf("invalid argument value (register > 16)\n");
		return ;
	}
	run_function(arena, process);
	process->PC += PC_jump;
	process->current_op = NULL;
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
				it->current_op = &g_op_tab[arena->memory[it->PC]];
				add_process_to_table(it, arena, arena->cycle + it->current_op->cycle_to_wait);
			}
			else
			{
				it->PC = (it->PC + 1) % MEM_SIZE;
				add_process_to_table(it, arena, arena->cycle + 1);
			}
		}
		else
		{
			execute_process(arena, it);	
		}
		it = next;
	}
	arena->process_table[arena->cycle % PROCESS_TABLE_SIZE] = NULL;
}

void	add_process_to_table(t_process *process, t_arena *arena, int cycle)
{
	process->next_table = arena->process_table[cycle % PROCESS_TABLE_SIZE];
	arena->process_table[cycle % PROCESS_TABLE_SIZE] = process;
}