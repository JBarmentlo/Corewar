#include "op.h"
#include "arena.h"
#include "stdlib.h"

byte	*endian_switch(byte *val, int size)
{
	int		i;
	byte	*out;

	i = 0;
	out = malloc(size);
	while (i < size)
	{
		out[i] = ptval[size - i - 1];
		i++;
	}
	return (out);
}
