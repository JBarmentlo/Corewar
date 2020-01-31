#include "arena.h"
#include "bitMasks.h"
#include "stdlib.h"

void		read_encoding_byte(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);

	int		i;
	byte	mask;
	byte	val;

	val = arena->memory[(process->PC + 1) & MODULO_MASK];
	mask = 3;
	i = 4;
	while (i)
	{
		arena->args->type[i - 1] = val & mask;
		val = val >> 2;
		if (arena->args->type[i - 1] == 3)
		{
			arena->args->type[i - 1] = 4;
		}
		arena->args->size[i - 1] = type_to_size(arena->args->type[i - 1], process->current_op);
		i--;
	}
}

void		no_encoding_byte(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < process->current_op->arg_nb)
	{
		arena->args->size[i] = type_to_size(process->current_op->arg_types[i], process->current_op);
		arena->args->type[i] = process->current_op->arg_types[i];
		i++;
	}
}

void		copy_to_args_tmp(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < MAX_ARGS_SIZE)
	{
		process->args_tmp[i] = arena->memory[(process->PC + 1 + process->current_op->encoding_byte + i) & MODULO_MASK];
		i++;
	}
}

uint16_t	read_args(t_args *args, t_process *process)
{
	printf("%s\n",__func__);

	uint16_t	PC_tmp;
	byte		size;
	byte		i;

	PC_tmp = 0;
	i = 0;
	while (i < MAX_ARGS_NUMBER && args->type[i] != 0)
	{
		size = args->size[i];
		args->val[i] = big_endian_to_int(process->args_tmp + PC_tmp, size);
		PC_tmp += size;
		i++;
	}
	return (PC_tmp);
}

void		print_t_args(t_args *args)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER && args->type[i])
	{
		if (args->type[i] == T_IND)
			printf("T_IND");
		if (args->type[i] == T_DIR)
			printf("T_DIR");
		if (args->type[i] == T_REG)
			printf("T_REG");
		printf("\t val: %d \t size: %d \n", args->val[i], args->size[i]);
		i++;
	} 
}