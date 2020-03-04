#include "arena.h"

void	print_vm_state(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	printf("process list : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d, R2:%d\n", it->owner->header.prog_name, it->owner->number, it->registre[0], it->registre[1]);
		it = it->next_list;
	}
	it = arena->process_table[0];
	printf("process table : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d\n", it->owner->header.prog_name, it->owner->number, it->registre[0]);
		it = it->next_table;
	}
}

void	printf_process_PC(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	printf("process list : \n");
	while (it)
	{
		printf("owner: %d PC: %d\n", it->owner->number, it->PC);
		it = it->next_list;
	}
}

void	hex_dump(t_arena *arena)
{
	size_t		i;
	int			zeroes;
	int			offset;

	zeroes = 0;
	offset = 0;
	i = 0;
	while (i < MEM_SIZE)
	{	
		if (i && offset % 50 == 0)
			printf ("\n");
		if (arena->memory[i])
		{
			printf("%02x ", arena->memory[i]);
			zeroes = 0;

		}
		if (!arena->memory[i])
		{
			zeroes += 1;
			if (i % 10 == 0)
			{
				printf(" ! ");
			}
			else
				printf(" . ");
		}
		if (zeroes > 100)
		{
			printf("skip");
			while (i < MEM_SIZE && arena->memory[i] == 0)
			{
				i++;
			}
			i--;
			zeroes = 0;
		}

		if ((i + 1) % (MEM_SIZE / arena->nb_champs) == 0)
		{
			offset = 0;
			printf ("\n\n%zu",i);
		}
		else
		{
			offset++;
		}
		i++;
	}
}

void	dump_color(t_arena *arena)
{
	int	i = 0;

	while (i < MEM_SIZE)
	{
		if (i % 50 == 0)
		{
			printf ("\n");
		}
		if (arena->memory_color[i] != '0')
		{
			printf("%02x ", arena->memory_color[i] - '0');
		}
		else
		{
			printf(" . ");
		}
	
		i++;
	}
}