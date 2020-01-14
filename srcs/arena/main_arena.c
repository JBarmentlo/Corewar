#include "arena.h"
#include "stdio.h"

int		main()
{

	uint a;

	a = 2;
	bit_dump(endian_switch(&a, sizeof(a)), sizeof(a));
	printf("%d",big_endian_to_uint(endian_switch(&a, sizeof(a)), sizeof(a)));
	return (0);
}