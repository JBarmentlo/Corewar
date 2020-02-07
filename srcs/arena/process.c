#include "arena.h"
#include "bitMasks.h"

void	process_invalid(t_process *process)
{
	process->PC++;
	process->PC = process->PC  & MODULO_MASK;
	process->current_op = NULL;	//will be made obsolete by architecture
}

void	execute_process(t_arena *arena, t_process *process)
{
	int	PC_jump;
	printf("opcode: %u\n", process->current_op->opcode);
	set_args_to_zero(arena->args);
	if (process->current_op->encoding_byte)
	{
		read_encoding_byte(arena, process);
		if (!is_valid_encoding_byte(arena, process))
		{
			process_invalid(process);		//check reinsertion inta table
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
	if (process->current_op->opcode != 9)
		process->PC += PC_jump + process->current_op->encoding_byte + 1;
	process->current_op = NULL;
	add_process_to_table(process, arena, arena->cycle + 1);

	//reinsert into table ?
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
				add_process_to_table(it, arena, arena->cycle + it->current_op->cycle_to_wait);
			}
			else
			{
				it->PC = (it->PC + 1)  & MODULO_MASK;
				add_process_to_table(it, arena, arena->cycle + 1);
			}
		}
		else
		{
			printf("cycle : %lu\n", arena->cycle);
			printf("PC:%d\n", it->PC);
			execute_process(arena, it);	
			printf("\n\n");
		}
		it = next;
	}
	arena->process_table[arena->cycle % PROCESS_TABLE_SIZE] = NULL;
}