#include "op.h"


#define MAX_WAIT_TIME 	1000

typedef unsigned char	byte;


typedef struct			s_process
{
	byte	registre[REG_NUMBER];
	int		PC;
	t_op	current_op;
}						t_process;

typedef struct			s_champion
{
	int		number;
	char*	comment;
	char*	name;
	//live related stuff
}						t_champion;

typedef struct 			s_vm
{
	byte		memory[MEM_SIZE];
	t_process*	process_table[MAX_WAIT_TIME + 1];
	t_champion	champion_table[MAX_PLAYERS];
	int			nb_champions;

	//live_related_info
	
}						t_vm;

