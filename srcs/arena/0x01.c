#include "arena.h"

void    x01(t_arena *arena, t_process *process)
{
    printf("0x01\n");
    process->last_live = arena->cycle;
    if (arena->args->val[0] == process->owner->number) // should it be nb or -nb
    {
        process->owner->last_live = arena->cycle;
    }
}