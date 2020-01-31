#include "arena.h"

void	mem_write_color(t_arena *arena, uint index, uint size, int champ_nb)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arena->memory_color[(index + i)  & MODULO_MASK] = champ_nb;
		i++;
	}
}