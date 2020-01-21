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
		if (op->is_direct_small == 1)
			return (2);
		else
			return (4);
	}
	printf("THIS SHOULD NEVER BE PRINTED type_to_size\n");
	return (0);
}

int			is_valid_encoding_byte(t_arena *arena, t_process *process)
{
	printf("%s\n",__func__);
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

int			is_valid_args_value(t_args *args)
{
	printf("%s\n",__func__);

	int	i;

	i = 0;
	while (i < MAX_ARGS_NUMBER && args->type[i] != 0)
	{
		if (args->type[i] == T_REG && (args->val[i] > REG_NUMBER || args->val[i] < 1))
			return (0);
		i++;
	}
	return (1);

}

// Assumes type[] and val[] are defined
void	get_val(t_arena *arena, t_process *process)
{
	int	i;

	i = 0;
	while (i < process->current_op->arg_nb)
	{
		if (arena->args->type[i] == T_DIR)
		{
			arena->args->val_read[i] = arena->args->val[i];
		}
		else if (arena->args->type[i] == T_IND)
		{
			arena->args->val_read[i] = ind_to_uint(arena, process, (int)arena->args->val[i]);
		}
		else if (arena->args->type[i] == T_REG)
		{
			arena->args->val_read[i] = read_reg(process, arena->args->val[i]);
		}
		i++;
	}
}