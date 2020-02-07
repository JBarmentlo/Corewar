#include "arena.h"


// NEED TO ADD DEAD CHAMPS TO FILL TAB
// NEGATIVE NUMBERS ARE USED
void    x01(t_arena *arena, t_process *process)
{
	int	arg;

    printf("0x01\n");
	print_t_args(arena->args);
    process->last_live = arena->cycle;
    arena->total_live_since_check++;
	arg = (-1) * arena->args->val[0] - 1;
	if (arg < MAX_PLAYERS && arg > 0 && arena->champion_table[arg].alive)
	{
			arena->champion_table[arg].lives_since_last_check += 1;
   			arena->last_live_champ_number = arg;
	}

}