#include "arena.h"
#include "bitMasks.h"
#include "stdlib.h"

t_args		*new_t_args(void)
{
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

byte		is_opcode_valid(t_arena *arena, uint16_t PC)
{
	return (arena->memory[PC] <= 16);
}

void		read_encoding_byte(t_arena *arena, t_process *process)
{
	int	i;

	arena->args->type[0] = ((arena->memory[process->PC + 1] & SEVEN) != 0) + 2 * ((arena->memory[process->PC + 1] & EIGHT) != 0);
	arena->args->type[1] = ((arena->memory[process->PC + 1] & FIVE) != 0) + 2 * ((arena->memory[process->PC + 1] & SIX) != 0);
	arena->args->type[2] = ((arena->memory[process->PC + 1] & THREE) != 0) + 2 * ((arena->memory[process->PC + 1] & FOUR) != 0);
	arena->args->type[3] = ((arena->memory[process->PC + 1] & ONE) != 0) + 2 * ((arena->memory[process->PC + 1] & TWO) != 0);

	i = 0;
	while (i < 4) //transforme REG_CODE etc en T_REG etc
	{
		if (arena->args->type[i] == 3)
		{
			arena->args->type[i] = 4;
		}
		i++;
	}
}

int			is_valid_encoding_byte(t_arena *arena, t_process *process)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (arena->args->type[i] != 0 &&  ((arena->args->type[i] & process->current_op->arg_types[i]) != arena->args->type[i]))
			return (0);
		i++;
	}
	return (1);
}

uint16_t				type_to_size(byte type, t_op *op)
{
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
	return (0);
}



uint16_t				read_args(t_arena *arena, t_process *process)
{
	uint16_t	PC_tmp;
	byte		size;
	byte		i;

	PC_tmp = 0;
	i = 0;

	while (i < MAX_ARGS_NUMBER && arena->args->type[i] != 0)
	{
		size = type_to_size(arena->args->type[i], process->current_op);
		arena->args->size[i] = size;
		arena->args->val[i] = big_endian_to_uint(&arena->memory[process->PC + 2 + PC_tmp], size);
		PC_tmp += size;
		i++;
	}


}

uint16_t		fill_args(t_arena *arena, t_process *process)
{
	if (is_opcode_valid(arena, process->PC))
	{
		//if necessary
		read_encoding_byte(arena, process);
	}
	return (0);
}
