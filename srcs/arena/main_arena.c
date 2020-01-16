#include "arena.h"

#include "stdio.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_arena	*arena;
	byte	bytecode;

	arena = make_vm();
	arena->memory[0] = 1;
	
	return (0);
}
