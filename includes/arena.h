#ifndef ARENA_H
# define ARENA_H

# include "sdl_include/SDL.h"
# include "sdl_include/SDL_image.h"
# include "sdl_include/SDL_ttf.h"
# include <stdio.h>							//A SUPPRIMER /!

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE
#define	MAX_ARGS_SIZE			16

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char					t_arg_type;
typedef unsigned int			uint;
typedef unsigned char			byte;
typedef unsigned short			uint16_t;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3


typedef struct		header_s
{
unsigned int		magic;
char				prog_name[PROG_NAME_LENGTH + 1];
unsigned int		prog_size;
char				comment[COMMENT_LENGTH + 1];
}					header_t;


typedef struct			s_op
{
	char*				name;
	byte				arg_nb;
	byte				arg_types[MAX_ARGS_NUMBER];
	byte				opcode;
	uint				cycle_to_wait;
	char*				full_name;
	byte				encoding_byte; 	//indicates the presence, or not, of an argument encoding byte after the opcode;
	byte				is_direct_small;	//indicates the amount of bytes used to encode DIR arguments; 1 => 2 0 => 4
	byte				idx_mod_applies;
}						t_op;

extern	t_op			g_op_tab[17];


#define PROCESS_TABLE_SIZE	1001
#define MAX_BYTECODE_SIZE	18


typedef struct			s_champion
{
	int					number;
	char*				comment;
	char*				name;
	long				last_live;
	//live related stuff	
}						t_champion;

typedef struct			s_process
{
	byte				registre[REG_NUMBER * REG_SIZE];
	byte				args_tmp[MAX_ARGS_SIZE];
	int					bytecode_size;
	int					carry;
	uint16_t			PC;
	t_op				*current_op;
	unsigned long		last_live;
	int					table_pos;
	int					alive;
	t_champion			*owner;
	struct s_process	*next_list;
	struct s_process	*next_table;
}						t_process;

typedef struct			s_args
{
	byte				opcode;
	byte				type[MAX_ARGS_NUMBER];
	byte				size[MAX_ARGS_NUMBER];
	int					val[MAX_ARGS_NUMBER];
	int					val_read[MAX_ARGS_NUMBER];
}						t_args;

typedef struct 			s_arena
{
	byte				memory[MEM_SIZE];

	t_process*	 		process_list;
	t_process*			process_table[PROCESS_TABLE_SIZE]; // a init vide;

	t_champion			champion_table[MAX_PLAYERS];
	int					last_live_champ_number;
	int					nb_champions;

	t_op				g_op_tab[17];

	unsigned long		cycle;
	unsigned long		total_live_since_check;
	unsigned long		cycles_since_check;
	uint				cycle_to_die;
	uint				max_checks;
	t_args				*args;

	//live_related_info
	
}						t_arena;




// ADD ALWAYS INLINE

typedef struct		s_disp
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Texture		*back;
	SDL_Rect		screen;
	SDL_Rect		arena;
	SDL_Rect		players;
	SDL_Rect		process;
}					t_disp;

void				error(char *src, t_disp *d);
void				init_window(t_disp *d);




// ENDIAN

byte				*uint_to_big_endian(uint val, int size);
unsigned int		big_endian_to_uint(void *val, int size);
int					big_endian_to_int(void *vall, int size);
byte				*endian_switch(void *val, int size);
void				memcopy_endian_flip(void *src, void *dest, uint16_t size);
void				memcopy(void *src, void *dest, uint16_t size);

// ARGS

void				set_args_to_zero(t_args *args);
t_args				*new_t_args(void);
int					is_valid_args_value(t_args *args);
int					is_valid_encoding_byte(t_arena *arena, t_process *process);
byte				is_valid_opcode(byte);
void				read_encoding_byte(t_arena *arena, t_process *process);
uint16_t			type_to_size(byte type, t_op *op);
uint16_t			read_args(t_args *args, t_process *process);
uint16_t			fill_args(t_arena *arena, t_process *process);
void				copy_to_args_tmp(t_arena *arena, t_process *process);
void				no_encoding_byte(t_arena *arena, t_process *process);
void				get_val(t_arena *arena, t_process *process);

// CYCLE & PROCESS

void				execute_process(t_arena *arena, t_process *process);
void				process_invalid(t_process *process);
void				execute_process(t_arena *arena, t_process *process);
void				execute_processes(t_arena *arena);
void				add_process_to_table(t_process *process, t_arena *arena, int cycle);


// READ WRITE

void				write_uint_to_reg(t_process *process, uint val, uint reg_number);
void				mem_memcopy_endian_switch(t_arena *arena, byte *src, int index, uint size);
void				mem_memcopy(t_arena *arena, byte *src, int index, uint size);
uint				read_reg(t_process *process, int reg_nb);
uint				ind_to_uint(t_arena *arena, t_process *process, int ind);
uint				mem_read_uint(t_arena *arena, int index);
void				write_uint_to_mem(t_arena *arena, int index, uint val);

//	UTILS

void				*reg_nb_to_ptr(t_process *process, int nb);
void				*ind_to_ptr_idx(t_arena *arena, int ind, int PC);
void				*ind_to_ptr_no_idx(t_arena *arena, int ind, int PC);




// OPCODE FUNCTIONS

void				run_function(t_arena *arena, t_process *process);

void				x01(t_arena *arena, t_process *process);
void				x02(t_arena *arena, t_process *process);
void				x03(t_arena *arena, t_process *process);
void				x04(t_arena *arena, t_process *process);
void				x05(t_arena *arena, t_process *process);
void				x06(t_arena *arena, t_process *process);
void				x07(t_arena *arena, t_process *process);
void				x08(t_arena *arena, t_process *process);
void				x09(t_arena *arena, t_process *process);
void				x10(t_arena *arena, t_process *process);
void				x11(t_arena *arena, t_process *process);
void				x12(t_arena *arena, t_process *process);
void				x13(t_arena *arena, t_process *process);
void				x14(t_arena *arena, t_process *process);
void				x15(t_arena *arena, t_process *process);
void				x16(t_arena *arena, t_process *process);

// 	TESTING FUNCTIONS

byte				bytecode_gen(int one, int two, int three);
t_arena 			*make_vm();
void				bit_dump(void *ptr, int size);
void				print_t_args(t_args *args);

#endif

