#include "arena.h"
#include "stdlib.h"
#include "stdio.h"
#include "bitMasks.h"

// keep going ?
int		is_game_over(t_arena *arena)
{
	return (arena->process_list == NULL || (((uint)arena->option_dump == arena->cycle) && arena->cycle != 0));
}

int		opcode_to_mask(int opcode)
{
	int	o;

	o = opcode;
	if (o == 1)
	{
		return (ONE);
	}
	else if (o == 2)
	{
		return (TWO);
	}
	else if (o == 3)
	{
		return (THREE);
	}
	else if (o == 4)
	{
		return (FOUR);
	}
	else if (o == 5)
	{
		return (FIVE);
	}
	else if (o == 6)
	{
		return (SIX);
	}
	else if (o == 7)
	{
		return (SEVEN);
	}
	else if (o == 8)
	{
		return (EIGHT);
	}
	else if (o == 9)
	{
		return (NINE);
	}
	else if (o == 10)
	{
		return (TEN);
	}
	else if (o == 11)
	{
		return (ELEVEN);
	}
	else if (o == 12)
	{
		return (TWELVE);
	}
	else if (o == 13)
	{
		return (THIRTEEN);
	}
	else if (o == 14)
	{
		return (FOURTEEN);
	}
	else if (o == 15)
	{
		return (FIFTEEN);
	}
	else if (o == 16)
	{
		return (SIXTEEN);
	}
	return (0);
}

void	run_function(t_arena *arena, t_process *process)
{
	if (TEST_PRINT & opcode_to_mask(process->current_op->opcode))
	{
		printf("RUNNING : \t%s\n", process->current_op->name);
		printf("Owner: \t\t%d\n", process->owner->number);
		print_t_args(arena->args);
	}
	arena->op_fun_tab[process->current_op->opcode - 1](arena, process);
	if (HEX_DUMP && TEST_PRINT & opcode_to_mask(process->current_op->opcode))
	{
		hex_dump(arena);
	}
}

void	update_champion_alive(t_arena *arena)
{
	int			i;
	int			total_alive;
	t_process	*it;

	total_alive = 0;
	i = 0;
	while (i < arena->nb_champs)	// DUPLICATE VARIABLE !!
	{
		arena->champion_table[i].alive = 0;
		arena->champion_table[i].lives_since_last_check = 0;
		i++;
	}
	it = arena->process_list;
	while (it)
	{
		arena->champion_table[it->owner->number - 1].alive = 1;
		total_alive += 1;
		it = it->next_list;
	}
	arena->nb_live_champions = total_alive;
}

// gt or gteq ?
void	check_lives(t_arena *arena)
{
	t_process	*it;
	t_process	*next;

	it = arena->process_list;
	while (it)
	{
		next = it->next_list;
		if (arena->cycle - it->last_live > arena->cycle_to_die) // gt or gteq ?
			kill_process(arena, it);
		it = next;
	}
	if (arena->total_live_since_check >= NBR_LIVE || arena->max_checks >= MAX_CHECKS)
	{
		if (arena->cycle_to_die > CYCLE_DELTA)
			arena->cycle_to_die -= CYCLE_DELTA;
		else
		{
			arena->cycle_to_die = 1;
		}
		arena->max_checks = 0;
	}
	else
	{
		arena->max_checks += 1;
	}
	arena->cycles_since_check = 0;
}

int		do_the_cycle(t_arena *arena)
{
	if (arena->cycles_since_check == arena->cycle_to_die)
	{
		check_lives(arena);
		update_champion_alive(arena);
	}
	execute_processes(arena);	//skip empty turns for performance
	arena->cycle += 1;
	arena->cycles_since_check += 1;
	return (1);
}
