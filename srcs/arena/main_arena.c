#include "arena.h"
#include "bitMasks.h"
#include "stdio.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;

	t_arena		*arena;
	t_process	*process;
	byte		bytecode;
	byte		reg;
	int16_t	ind;
	int			vint;
	uint		vuint;
	uint		dir;

	arena = make_vm();
	process = arena->process_list;
	arena->memory[0] = 2;
	arena->memory[1] = bytecode_gen(2,1,0);
	dir = 12345678;
	reg = 3;
	memcopy_endian_flip(&dir, &arena->memory[2], 4);
	memcopy_endian_flip(&reg, &arena->memory[2 + 4], 1);
	//execute_process(arena, process);


	ind = -1;
	vuint = (uint)ind;
	vint = (int)vuint;
	printf("H: %d\n", vint);
	printf("H: %u\n", vuint);

	return (0);
}
