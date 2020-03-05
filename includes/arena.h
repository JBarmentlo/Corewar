/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:07:38 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 16:37:46 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

#include "libft/libft.h"
#include "op.h"
#include "ft_printf/ft_printf.h"
# include "sdl_include/SDL.h"
# include "sdl_include/SDL_image.h"
# include "sdl_include/SDL_ttf.h"
# include <stdio.h>							//A SUPPRIMER

#define COREWAR					1
#define	TRUE					1
#define	FALSE					0
#define	INIT_NUM				-1
#define	NO_NB					-1
#define	PADDING					4
#define	INFO_SIZE_CODE			4
#define	SIZE_HEADER				2192
#define	SIZE_MAX_PROG			2875 // = sizeof(COREWAR_EXEC_MAGIC) + PROG_NAME_LENGTH + PADDING + INFO_SIZE_CODE + COMMENT_LENGTH + PADDING + CHAMP_MAX_SIZE + 1 //

#define	MAX_ARGS_SIZE			16
typedef unsigned int			uint;
typedef unsigned char			byte;
typedef unsigned short			uint16_t;

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
	header_t	header;
	int			number;
	int			fd;
	byte		prog[SIZE_MAX_PROG];
	int			alive;
	int			lives_since_last_check;
	int			total_memory_owned;
	int			total_process;
}						t_champion;

typedef struct			s_process
{
	int					registre[REG_NUMBER];
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
	t_process*	 		process_list;
	int					total_process_nb;
	t_process*			process_table[PROCESS_TABLE_SIZE]; // a init vide;
	t_champion			champion_table[MAX_PLAYERS];
	int					nb_champs;
	int				    option_dump;
	byte				memory[MEM_SIZE];
	byte				memory_color[MEM_SIZE];
	int					last_live_champ_number;
	int					nb_champions;
	int					nb_live_champions;
	void 				(**op_fun_tab)(struct s_arena*, t_process*);
	t_op				g_op_tab[17];

	unsigned long			cycle;
	unsigned long		total_live_since_check;
	unsigned long		cycles_since_check;
	uint				cycle_to_die;
	uint				max_checks;
	t_args				*args;	
}						t_arena;

typedef void 			(*t_fun_ptr)(t_arena*, t_process*);



int						usage(int prog);
int						ft_error(char *str, char *str2);
void					*ft_error2(char *str, char *str2);
void					*ft_error3(char *str, size_t line, size_t col);
void					*ft_error4(char *str, char *str2, size_t line, size_t col);
int						pars_num_champ(int *nb, t_arena *vm, int mode);
int						pars_args(int ac, char **av, t_arena *vm);
int						pars_header(t_champion *champ);
int						start_arena(t_arena *vm, t_champion *champ);

typedef struct			s_texte
{
	int					player;
	char*				txt;
	struct s_texte*		next;

}						t_texte;


// ADD ALWAYS INLINE

typedef struct		s_disp
{
	unsigned int	color_champ[MAX_PLAYERS + 1];
	unsigned int	delay;
	unsigned int	d_cycle;
	unsigned int	pause;
	unsigned int	step;
	int				button_status;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*img;
	SDL_Surface		*txt;
	SDL_Surface		*s_arena;
	SDL_Texture		*back;
	SDL_Texture		*title;
	SDL_Texture		*bar;
	SDL_Texture		*bar_plus;
	SDL_Texture		*bar_minus;
	SDL_Texture		*bar_pause;
	SDL_Texture		*bar_stop;
	SDL_Texture		*bar_step;
	SDL_Texture		*bar_play;
	SDL_Texture		*font;
	SDL_Texture		*tmp;
	SDL_Texture		*a_tmp;
	SDL_Texture		*b_tmp;
	SDL_Texture		*p_tmp;
	SDL_Texture		*f_tmp;
	SDL_Rect		screen;
	SDL_Rect		arena;
	SDL_Rect		players;
	SDL_Rect		process;
	SDL_Rect		mod;
	TTF_Font		*font1;
	SDL_Color		color;
}					t_disp;

// VISU


void				error(char *src, t_disp *d);
void				init_window(t_disp *d, t_arena a);
void				disp_init_var(t_disp *d);
void				disp_init_players(t_disp *d, t_arena a);
void				disp_init_info(t_disp *d);
void				events(t_disp *d, int *running, int *timeout, t_arena a);
void				event_mousemotion(t_disp *d, int *timeout, t_arena a);
void				event_mousebutton(t_disp *d, int *running, int *timeout, t_arena a);
void				disp_ttf(char *ttf, SDL_Color color, t_disp *d);
void				update_visu(t_disp *d, t_arena a);
char				*ft_itoa2(int n);
size_t				ft_nbrlen(int nbr);
//

void				bit_dump(void *ptr, int size);
byte				*int_to_big_endian(int val, int size);
byte				*endian_switch(void *val, int size);



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

int					do_the_cycle(t_arena *arena);
int					is_game_over(t_arena *arena);


void				execute_process(t_arena *arena, t_process *process);
void				process_invalid(t_process *process);
void				execute_process(t_arena *arena, t_process *process);
void				execute_processes(t_arena *arena);
void				kill_process(t_arena *arena, t_process *it, t_process **prev);
void				remove_process_from_table(t_arena *arena, t_process *process); //wildly unchecked
t_process			*process_copy(t_process *src);
void				add_process_to_table(t_process *process, t_arena *arena, uint table_index);
void				add_process_to_list(t_process *process, t_arena *arena);

// READ WRITE


int					reg_read_int(t_process *process, int reg_nb);
void				reg_write_int(t_process *process, int val, int reg_number);

int					mem_ind_to_int(t_arena *arena, t_process *process, int ind);

int					mem_read_int(t_arena *arena, int index);
void				mem_write_int(t_arena *arena, int index, int val);


//	UTILS

void				*reg_nb_to_ptr(t_process *process, int nb);
void				*ind_to_ptr_idx(t_arena *arena, int ind, int PC);
void				*ind_to_ptr_no_idx(t_arena *arena, int ind, int PC);
void				fill_fun_ptr_tab(t_arena *arena);
int					positive_modulo_memsize(int a);
int					opcode_to_mask(int opcode);

//	Display

void				mem_write_color(t_arena *arena, uint index, uint size, int champ_nb);
void				update_champion_alive(t_arena *arena);



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
