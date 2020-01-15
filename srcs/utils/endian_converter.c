#include "arena.h"
#include "stdlib.h"
#include "stdio.h"
#include "bitMasks.h"

// write bit printer to test these


//returns a pointer to switched endian value.
// the macs are little endian I believe ?
// it's malloc so free it later
byte	*endian_switch(void *vall, int size)
{
	int		i;
	byte	*out;
	byte	*val;

	i = 0;
	val = vall;
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
uint		big_endian_to_uint(void *vall, int size)
{
	byte	*tmp;
	byte	*val;

	val = vall;
	tmp = endian_switch(val, size);
	if (size == 2)
	{
		return ((uint)*((uint16_t*)tmp));
	}
	tmp = endian_switch(val, size);
	if (size == 4)
	{
		return ((uint)*((uint*)tmp));
	}
	printf("big_endian_to_int is not meant to be used with size = %d\n", size);
	return (0);
}

byte				*uint_to_big_endian(uint val, int size)
{
	return (endian_switch((byte*)&val, size));
}

void			bit_dump(void *ptrr, int size)
{
	int		i;
	byte	*ptr;

	ptr = ptrr;
	i = 0;
	while (i < size)
	{
		printf("%d", (ptr[i] & EIGHT) != 0);
		printf("%d", (ptr[i] & SEVEN) != 0);
		printf("%d", (ptr[i] & SIX) != 0);
		printf("%d", (ptr[i] & FIVE) != 0);
		printf("%d", (ptr[i] & FOUR) != 0);
		printf("%d", (ptr[i] & THREE) != 0);
		printf("%d", (ptr[i] & TWO) != 0);
		printf("%d", (ptr[i] & ONE) != 0);
		printf(" ");
		i++;
	}
}


void					memcopy(void *src, void *dest, uint16_t size)	// DOES this work for static arrays ?
{
	int		i;
	byte	*srcc;
	byte	*destt;

	srcc = src;
	destt = dest;

	i = 0;
	while (i < size)
	{
		destt[i] = srcc[i];
		i++;
	}
}

void					memcopy_endian_flip(void *src, void *dest, uint16_t size)	// DOES this work for static arrays ?
{
	int		i;
	byte	*srcc;
	byte	*destt;

	srcc = src;
	destt = dest;

	i = 0;
	while (i < size)
	{
		destt[i] = srcc[size - 1 - i];
		i++;
	}
}