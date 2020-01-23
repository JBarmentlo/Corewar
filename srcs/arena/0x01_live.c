#include "arena.h"


// nb or -nb ?
// n fkin clue how its suppose to act with wrong arg
void    x01(t_arena *arena, t_process *process)
{
    printf("0x01\n");
    process->last_live = arena->cycle;
    arena->total_live_since_check++;
    if (arena->args->val[0] == (-1) * process->owner->number) // should it be nb or -nb
    {
		arena->champion_table[(-1) * arena->args->val[0]].lives_since_last_check += 1;
        arena->last_live_champ_number = (-1) * arena->args->val[0];
    }
}