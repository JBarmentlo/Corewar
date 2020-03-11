#include "arena.h"
#include "bitMasks.h"

// will return a positive modulo
int		positive_modulo_memsize(int a)
{
	return (a & (MEM_SIZE - 1));
}

void	print_color_state(t_arena *vm)
{
	printf("total mem: %d\n", vm->champion_table[0].total_memory_owned);
}

// CHAMP NUMBER TO champion_table INDEX RELATIONSHIP unknown
void	mem_write_color(t_arena *arena, uint index, uint size, int champ_nb)
{
	uint	i;
	int		current_owner;

	i = 0;
	while (i < size)
	{
		current_owner = arena->memory_color[(index + i) & MODULO_MASK];
		current_owner -= '0';
		if (current_owner > 0 && current_owner < MAX_PLAYERS)
		{
			arena->champion_table[current_owner - 1].total_memory_owned -= 1;
		}
		arena->champion_table[champ_nb - 1].total_memory_owned += 1;
		arena->memory_color[(index + i) & MODULO_MASK] = champ_nb + '0';
		i++;
	}
}

int		mem_read_int(t_arena *arena, int index)
{
	byte	out[REG_SIZE];
	int		i;

	i = 0;
	while (i < REG_SIZE)
	{
		out[REG_SIZE - 1 - i] = arena->memory[(index + i) & MODULO_MASK];
		i++;
	}
	return (*(int*)out);
}

void	mem_write_int(t_arena *arena, int index, int val)
{
	byte	*value;
	int		i;

	value =  (byte*)&val;
	i = 0;
	while (i < REG_SIZE)
	{
		arena->memory[(index + i) & MODULO_MASK] = value[REG_SIZE - 1 - i];
		i++;
	}
}

int		mem_ind_to_int(t_arena *arena, t_process *process, int ind)
{
	if (process->current_op->idx_mod_applies)
		ind = ind % IDX_MOD;
	return (mem_read_int(arena, ind));
}

void	reg_write_int(t_process *process, int val, int reg_number)
{
	memcpy(&process->registre[(reg_number - 1)], &val, REG_SIZE);
}

int		reg_read_int(t_process *process, int reg_nb)
{
	return (process->registre[(reg_nb - 1)]);
}