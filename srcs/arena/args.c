#include "arena.h"
#include "stdlib.h"

t_args		*new_t_args(void)
{
	t_args	*out;
	out = malloc(sizeof(t_args));
	return (out);
}

uint16_t		fill_args(t_arena *arena, t_process *process)
{
	if (is_opcode_valid(arena, process->PC))

}

byte		is_opcode_valid(t_arena *arena, uint16_t PC)
{
	return (arena->memory[PC] <= 16);
}

void		read_encoding_byte(t_arena *arena, t_process *process)
{

}