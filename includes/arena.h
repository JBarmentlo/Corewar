#include "op.h"


#define MAX_WAIT_TIME 		1000
#define MAX_BYTECODE_SIZE	18


typedef unsigned char	byte;


typedef struct			s_process
{
	byte	registre[REG_NUMBER * REG_SIZE];
	byte	bytecode[MAX_BYTECODE_SIZE];	//useless ?
	int		bytecode_size;
	int		carry;
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

typedef	struct 			s_process_list
{
	t_process				*process;
	struct s_process_list 	*next;
}						t_process_list;


typedef struct 			s_arena
{
	byte			memory[MEM_SIZE];
	t_process_list 	process_list;
	t_process*		process_table[MAX_WAIT_TIME + 1]; // a init vide;
	t_champion		champion_table[MAX_PLAYERS];
	int				nb_champions;

	//live_related_info
	
}						t_arena;

