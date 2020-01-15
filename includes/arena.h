#ifndef ARENA_H
# define ARENA_H

# include "sdl_include/SDL.h"
# include "sdl_include/SDL_image.h"
# include "sdl_include/SDL_ttf.h"
# include <stdio.h>							//A SUPPRIMER

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


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


typedef struct	s_op
{
	char*		name;
	byte		arg_nb;
	byte		arg_types[MAX_ARGS_NUMBER];
	byte		opcode;
	uint		cycle_to_wait;
	char*		full_name;
	byte		encoding_byte; 	//indicates the presence, or not, of an argument encoding byte after the opcode;
	byte		direct_size;	//indicates the amount of bytes used to encode DIR arguments; 1 => 2  0 => 4
}				t_op;

extern	t_op			g_op_tab[17];


#define PROCESS_TABLE_SIZE 		1001
#define MAX_BYTECODE_SIZE	18


typedef struct			s_champion
{
	int		number;
	char*	comment;
	char*	name;
	//live related stuff
}						t_champion;

typedef struct			s_process
{
	byte				registre[REG_NUMBER * REG_SIZE];
	byte				bytecode[MAX_BYTECODE_SIZE];	//useless ?
	int					bytecode_size;
	int					carry;
	uint16_t			PC;
	t_op				*current_op;
	int					last_live;
	t_champion			*owner;
	struct s_process	*next;
}						t_process;

typedef	struct 				s_process_list
{
	t_process				*process;
	struct s_process_list 	*next;
}							t_process_list;

typedef struct			s_args
{
	byte				opcode;
	byte				type[MAX_ARGS_NUMBER];
	uint16_t			ind[MAX_ARGS_NUMBER];
	uint16_t			short_dir[MAX_ARGS_NUMBER];
	uint				dir[MAX_ARGS_NUMBER];
}						t_args;

typedef struct 			s_arena
{
	byte			memory[MEM_SIZE];
	t_process*	 	process_list;
	t_process*		process_table[PROCESS_TABLE_SIZE]; // a init vide;
	t_champion		champion_table[MAX_PLAYERS];
	int				nb_champions;
	int				cycle;
	t_args			*args;

	//live_related_info
	
}						t_arena;


void				bit_dump(void *ptr, int size);
byte				*uint_to_big_endian(uint val, int size);
unsigned int		big_endian_to_uint(void *val, int size);
byte				*endian_switch(void *val, int size);
void				memcopy_endian_flip(void *src, void *dest, uint16_t size);
void				memcopy(void *src, void *dest, uint16_t size);



// ADD ALWAYS INLINE

typedef struct		s_disp
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Surface		*txt;
	SDL_Texture		*back;
	SDL_Texture		*title;
	SDL_Texture		*font;
	SDL_Rect		screen;
	SDL_Rect		arena;
	SDL_Rect		players;
	SDL_Rect		process;
	SDL_Rect		mod;
	TTF_Font		*font1;
}					t_disp;

void				error(char *src, t_disp *d);
void				init_window(t_disp *d, t_arena a);
void				bit_dump(void *ptr, int size);
byte				*int_to_big_endian(int val, int size);
unsigned int		big_endian_to_int(byte *val, int size);
byte				*endian_switch(byte *val, int size);
#endif

