#include "arena.h"
#include "bitMasks.h"

void	x01(t_arena *arena, t_process *process)
{
	int	arg;

	process->last_live = arena->cycle;
	arena->total_live_since_check++;
	arg = arena->args->val[0];
	arg = (-1) * arg;
	if (arg <= MAX_PLAYERS && arg > 0 && arena->champion_table[arg - 1].exists)
	{
		arena->champion_table[arg - 1].lives_since_last_check += 1;
		arena->last_live_champ_number = arg;
	}
	if ((VERBOSE & LIVE))
	{
		printf("live %d\n", arg);
		printf("last_live_nb : %d\n", arena->last_live_champ_number);
		if (arg <= MAX_PLAYERS && arg > 0)
			printf("total lives: %d\n",
				arena->champion_table[arg - 1].lives_since_last_check);
	}
}