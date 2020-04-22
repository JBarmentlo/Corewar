#include "arena.h"
#include "bitMasks.h"

void	x09(t_arena *arena, t_process *process)
{
	int	norm;

	norm = (process->PC + (arena->args->val[0] % IDX_MOD));
	if (process->carry)
		process->PC = norm & MODULO_MASK;
	if ((VERBOSE & ZJUMP))
	{
		if (process->carry == 0)
		{
			printf("no jump, carry is null\n");
		}
		else
		{
			printf("jumped %d spaces to %d\n",
				(arena->args->val[0] % IDX_MOD), norm & MODULO_MASK);
		}
	}
}
