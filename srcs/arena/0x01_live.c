#include "arena.h"


// nb or -nb ?
// if wrong arg does process-->last_live update ?
void    x01(t_arena *arena, t_process *process)
{
    printf("0x01\n");
	print_t_args(arena->args);
//	printf("PROC adress; %p\n", process);
//	printf("OWNER name: %s\n", process->owner->header.prog_name);

    process->last_live = arena->cycle;
    arena->total_live_since_check++;
//    printf("b\n");
//	printf("args->val[0]: \%d\n",arena->args->val[0]);
//	printf("p->o->number: %d \n", process->owner->number);
    if (arena->args->val[0] == ((-1) * process->owner->number))
    {
//	    printf("c\n");

		arena->champion_table[(-1) * arena->args->val[0] - 1].lives_since_last_check += 1;
//		printf("d\n");

        arena->last_live_champ_number = (-1) * arena->args->val[0];
//		printf("e\n");

    }
//		printf("e\n");

}