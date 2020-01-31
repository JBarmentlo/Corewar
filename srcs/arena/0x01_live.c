#include "arena.h"


// nb or -nb ?
// if wrong arg does process-->last_live update ?
void    x01(t_arena *arena, t_process *process)
{
    printf("0x01\n");
	print_t_args(arena->args);
    process->last_live = arena->cycle;
    arena->total_live_since_check++;
    if (arena->args->val[0] == ((-1) * process->owner->number))
    {
		arena->champion_table[(-1) * arena->args->val[0] - 1].lives_since_last_check += 1;
        arena->last_live_champ_number = (-1) * arena->args->val[0];
    }
}