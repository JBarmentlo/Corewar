#include "arena.h"
#include "stdio.h"

int display_winner(t_arena *vm)
{
    int winner;

    winner = vm->last_live_champ_number;
    if (vm->nb_live_champions <= 1)
    {
        printf("Player %d (%s) won", winner, vm->champion_table[winner - 1].header.prog_name);
		return (1);
    }
	return (0);
}