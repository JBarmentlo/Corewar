#include "arena.h"
#include "bitMasks.h"
#include "stdlib.h"

t_args		*new_t_args(void)
{
	printf("%s\n",__func__);
	t_args	*out;
	int		i;

	i = 0;
	out = malloc(sizeof(t_args));
	while (i < MAX_ARGS_NUMBER)
	{
		out->type[i] = 0;
		out->size[i] = 0;
		out->val[i] = 0;
		i++;
	}
	return (out);
}

void		set_args_to_zero(t_args *args)
{
	printf("%s\n",__func__);

	int i;
	i = 0;
	args->opcode = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		args->type[i] = 0;
		args->size[i] = 0;
		args->val[i] = 0;
		i++;
	}
}

byte		is_valid_opcode(byte opcode)
{
	printf("%s\n",__func__);

	return (opcode <= 16);
}

uint16_t	type_to_size(byte type, t_op *op)
{
	printf("%s\n",__func__);

	if (type == 0)
	{
		return (0);
	}
	if (type == T_REG)
		return (1);
	
	if (type == T_IND)
		return (2);

	if (type == T_DIR)
	{
		if (op->direct_size == 1)
			return (2);
		else
			return (4);
	}
	printf("THIS SHOULD NEVER BE PRINTED type_to_size\n");
	return (0);
}

void		read_encoding_byte(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);

	int		i;
	int		encoding_byte_addr;
	byte	mask;
	byte	val;

	val = arena->memory[(process->PC + 1) % MEM_SIZE];
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

int			is_valid_encoding_byte(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);
/*
	printf("arena->args->type :\n");
	bit_dump(arena->args->type, 4);
	printf("curremnt_op->arg_types : \n");
	bit_dump(process->current_op->arg_types, 4);
*/
	int	i;

	i = 0;
	while (i < process->current_op->arg_nb)
	{
		if (arena->args->type[i] == 0 ||  ((arena->args->type[i] & process->current_op->arg_types[i]) != arena->args->type[i]))
			return (0);
		i++;
	}
	return (1);
}

void		copy_to_args_tmp(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < MAX_ARGS_SIZE)
	{
		process->args_tmp[i] = arena->memory[(process->PC + 1 + process->current_op->encoding_byte + i) % MEM_SIZE];
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
		args->val[i] = big_endian_to_uint(process->args_tmp + PC_tmp, size);
		PC_tmp += size;
		i++;
	}
	return (PC_tmp);
}

int			is_valid_args_value(t_args *args)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER && args->type[i] != 0)
	{
		if (args->type[i] == T_REG && args->val[i] > REG_NUMBER)
			return (0);
		i++;
	}
	return (1);

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