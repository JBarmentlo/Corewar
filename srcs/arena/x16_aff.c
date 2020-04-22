#include "arena.h"
#include "bitMasks.h"

void	x16(t_arena *arena, t_process *process)
{
	uint	val;

	val = reg_read_int(process, arena->args->val[0]);
	printf("%c", (char)val);
	if ((VERBOSE & AFF) == AFF)
	{
		printf("printed %c\n", val);
	}
}
