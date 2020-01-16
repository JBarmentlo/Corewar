#include "arena.h"
#include "stdlib.h"
#include "stdio.h"

int		do_we_have_a_winner(t_arena *arena)
{
	int			first_process_owner;
	t_process	*it;

	it = arena->process_list;
	first_process_owner = it->owner->number;
	it = it->next;

	while (it != NULL)
	{
		if (it->owner->number != first_process_owner)
			return (0);
		it = it->next;
	}
	return (1);
}

void	process_invalid(t_process *process)
{
	process->PC++;
	process->PC = process->PC % MEM_SIZE; //manually replace by bitmask
	process->current_op = NULL;	//will be made obsolete by architecture
}

void	run_function(t_arena *arena, t_process *process)
{
	printf("running %s\n", process->current_op->name);
	print_t_args(arena->args);
}

void	execute_process(t_arena *arena, t_process *process)
{
	//if current op == NULL: read opcode and add;
	int	PC_jump;
	set_args_to_zero(arena->args);
	if (!is_valid_opcode(arena->memory[process->PC])) //to be made redundant by archtecture
	{
		process_invalid(process);
		printf("invalid opcode\n");
		return ;
	}
	process->current_op = &g_op_tab[arena->memory[process->PC] - 1];
	printf("current opcode %d\n", arena->memory[process->PC]);
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
		next = it->next;
		if (it->current_op == NULL)
		{
			if (is_valid_opcode(arena->memory[it->PC]))
			{
				it->current_op = &g_op_tab[arena->memory[it->PC]];
			}
			else
			{
				it->PC = (it->PC + 1) % MEM_SIZE;
			}
			}
		else
		{
			execute_process(arena, it);	
		}
		it = next;
	}
	//reset next pointers and clear table at index, use recusrive call to reset next pointer collapse ? too fancy ?
}

int		do_the_cycle(t_arena *arena)
{	
	
	execute_processes(arena);	//skip empty turns for performance
	arena->cycle += 1;
	return (1);
}