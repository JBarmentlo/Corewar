#include "arena.h"

int		mem_ind_to_int(t_arena *arena, t_process *process, int ind)
{
	if (process->current_op->idx_mod_applies)
		ind = ind % IDX_MOD;
	return (mem_read_int(arena, process->pc + ind));
}

void	reg_write_int(t_process *process, int val, int reg_number)
{
	memcpy(&process->registre[(reg_number - 1)], &val, REG_SIZE);
}

int		reg_read_int(t_process *process, int reg_nb)
{
	return (process->registre[(reg_nb - 1)]);
}