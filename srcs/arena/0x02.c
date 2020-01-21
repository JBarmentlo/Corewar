#include "arena.h"


//here we assume registres start at 1
//we write to process->registre[arg - 1]
void    x02(t_arena *arena, t_process *process)
{
	uint	value;

	if (arena->args->type[0] == T_IND)
	{
		
		value = big_endian_to_uint(&arena->memory[(process->PC + (arena->args->val[0] % IDX_MOD)) % MEM_SIZE], DIR_SIZE);
		memcopy(&value, &process->registre[(arena->args->val[1] - 1) * 4], REG_SIZE);
	}
	else
	{
		memcpy(&process->registre[(arena->args->val[1] - 1) * 4], &arena->args->val[0], T_DIR);
	}
	process->carry = (value == 0);
	printf("0x02\n");
}