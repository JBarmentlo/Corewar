#include "arena.h"
#include "stdlib.h"
#include "stdio.h"
#include "bitMasks.h"

// write bit printer to test these


//returns a pointer to switched endian value.
// the macs are little endian I believe ?
// it's malloc so free it later
byte	*endian_switch(byte *val, int size)
{
	int		i;
	byte	*out;

	i = 0;
	out = malloc(size);
	while (i < size)
	{
		out[i] = val[size - i - 1];
		i++;
	}
	return (out);
}

// Only works for size in [2, 4]
// untested
unsigned int		big_endian_to_int(byte *val, int size)
{
	byte	*tmp;

	tmp = endian_switch(val, size);
	if (size == 2)
	{
		return ((unsigned int)*((uint16_t*)tmp));
	}
	tmp = endian_switch(val, size);
	if (size == 4)
	{
		return ((unsigned int)*((uint32_t*)tmp));
	}

	printf("big_endian_to_int is not meant to be used with size = %d\n", size);
}

byte				*int_to_big_endian(int val, int size)
{
	return (endian_switch(&val, size));
}

void			bit_dump(byte *ptr, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		printf("%d", (ptr[i] & ONE) != 0);
		printf("%d", (ptr[i] & TWO) != 0);
		printf("%d", (ptr[i] & THREE) != 0);
		printf("%d", (ptr[i] & FOUR) != 0);
		printf("%d", (ptr[i] & FIVE) != 0);
		printf("%d", (ptr[i] & SIX) != 0);
		printf("%d", (ptr[i] & SEVEN) != 0);
		printf("%d", (ptr[i] & EIGHT) != 0);
		i++;
	}
}