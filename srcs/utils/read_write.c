#include "arena.h"



void	*reg_nb_to_ptr(t_process *process, int nb)
{
	return (&process->registre[((nb - 1) * 4)]);
}

void	*ind_to_ptr_idx(t_arena *arena, int ind, int PC)
{
	return (&arena->memory[(PC + (ind % IDX_MOD)) % MEM_SIZE]);
}

void	*ind_to_ptr_no_idx(t_arena *arena, int ind, int PC)
{
	return (&arena->memory[(PC + ind) % MEM_SIZE]);
}

void	mem_memcopy(t_arena *arena, byte *src, int index, uint size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arena->memory[(index + i) % MEM_SIZE] = src[i];
		i++;
	}
}

void	mem_memcopy_endian_switch(t_arena *arena, byte *src, int index, uint size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arena->memory[(index + i) % MEM_SIZE] = src[size - i - 1];
		i++;
	}
}

uint	mem_read_uint(t_arena *arena, int index)
{
	byte	out[REG_SIZE];
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		out[REG_SIZE - 1 - i] = arena->memory[(index + i) % MEM_SIZE];
		i++;
	}
	return ((uint)*(uint*)out);
}

void	write_uint_to_mem(t_arena *arena, int index, uint val)
{
	byte	*value;
	int		i;

	value =  (byte*)&val;
	i = 0;
	while (i < REG_SIZE)
	{
		arena->memory[(index + i) % MEM_SIZE] = value[REG_SIZE - 1 - i];
		i++;
	}
}

uint	ind_to_uint(t_arena *arena, t_process *process, int ind)
{
	if (process->current_op->idx_mod_applies)
		ind = ind % IDX_MOD;
	return (mem_read_uint(arena, ind));
}

void	write_uint_to_reg(t_process *process, uint val, uint reg_number)
{
	memcpy(&process->registre[(reg_number - 1) * 4], &val, REG_SIZE);
}

uint	read_reg(t_process *process, int reg_nb)
{
	return ((uint)*((uint*)(&process->registre[(reg_nb - 1) * 4])));
}