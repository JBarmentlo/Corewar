#include "arena.h"

void	print_champions(t_arena *arena)
{
	int	i;

	printf("champions: \n");
	i = 0;
	printf("arena->nb_champs: %d \n", arena->nb_champs);
	while (i < arena->nb_champs)
	{
		printf("nb %d, name %s\n", arena->champion_table[i].number,
			arena->champion_table[i].header.prog_name);
		i++;
	}
}

void	print_vm_state(t_arena *arena)
{
	t_process	*it;
	int			i;

	it = arena->process_list;
	printf("cycle:%lu\n", arena->cycle);
	printf("process list : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d, R2:%d\n",
			it->owner->header.prog_name, it->owner->number,
			it->registre[0], it->registre[1]);
		it = it->next_list;
	}
	it = arena->process_table[arena->cycle % PROCESS_TABLE_SIZE];
	printf("process table : \n");
	while (it)
	{
		printf("Owner: %s, owner.nb: %d, R1:%d\n", it->owner->header.prog_name,
			it->owner->number, it->registre[0]);
		it = it->next_table;
	}
	print_champions(arena);
}

void	printf_process_pc(t_arena *arena)
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
			printf("\n");
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
			printf("\n\n%zu", i);
		}
		else
		{
			offset++;
		}
		i++;
	}
}

void	check_negative_pc(t_arena *arena)
{
	t_process	*it;

	it = arena->process_list;
	while (it)
	{
		if ((int16_t)it->PC < 0)
			printf("YOOOOOOOOOOSEF NEGATIV PC BRO \n  JHABSDFKJHBSEF\n");
		it = it->next_list;
	}
}

void	hex_dump_ugly(t_arena *arena)
{
	size_t		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			printf("\n");
		printf("%02x", arena->memory[i]);
		i++;
	}
}

void	dump_color(t_arena *arena)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 50 == 0)
		{
			printf("\n");
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
