#include "arena.h"


// nb or -nb ?
void    x01(t_arena *arena, t_process *process)
{
    printf("0x01\n");
    process->last_live = arena->cycle;
    arena->total_live_since_check++;
    if (arena->args->val[0] == (-1) * process->owner->number) // should it be nb or -nb
    {
        arena->last_live_champ_number = (-1) * arena->args->val[0];
    }
}