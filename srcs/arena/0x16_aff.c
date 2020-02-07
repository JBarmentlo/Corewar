#include "arena.h"

void    x16(t_arena *arena, t_process *process)
{
	uint	val;

	val = reg_read_int(process, arena->args->val[0]);
	printf("%c", (char)val);
    printf("0x04\n");
}