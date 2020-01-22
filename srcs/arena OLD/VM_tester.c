#include "arena.h"
#include "stdlib.h"
#include "bitMasks.h"

t_process	*make_process(void)
{
	t_process   *process;
	int			i;

	process = malloc(sizeof(t_process));
	process->registre[0] = 1;
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

t_args		*make_args(void)
{
	t_args *args;

	args = malloc(sizeof(t_args));
	set_args_to_zero(args);
	return (args);
}

t_arena *make_vm()
{
	t_arena     *arena;
	t_args      *args;
	t_process   *process;
	int         i;

	arena = malloc(sizeof(t_arena));
	process = make_process();
	args = make_args();
	i = 0;
	while (i < MEM_SIZE)
	{
		arena->memory[i] = 0;
		i++;
	}
	arena->cycle = 0;
	arena->total_live_since_check = 0;
	arena->cycles_since_check = 0;
	arena->cycle_to_die = CYCLE_TO_DIE;
	arena->args = args;
	arena->process_list = process;
	arena->max_checks = 0;
	return (arena);
}

byte      bytecode_gen(int one, int two, int three) // 1 reg, 2 dir, 3 ind
{
	byte    out;

	out = 0;
	out = out + one * SEVEN;
	out += two * FIVE;
	out += three * THREE;

	return (out);
}

/*
int     test_all_bytecodes(byte opcode, t_arena *arena)
{
	int i;
	int j;
	int k;

	int arg_num;

	arg_num = g_op_tab[opcode].arg_nb;
	arena->memory[0] = opcode;
	i = 1;
	
	while (i < 4)
	{
		j = 1;
		while (j < 4)
		{
			k = 1;
			while (k < 4)
			{
				arena->memory[1] = bytecode_gen(i, j, k * (k < arg_num));
				k++;
			}
			j++;
		}
		i++;
	}

}
*/