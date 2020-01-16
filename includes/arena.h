/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:07:38 by dberger           #+#    #+#             */
/*   Updated: 2020/01/16 12:32:05 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

#define	TRUE					1
#define	FALSE					0
#define	FALSE2					-1
#define	INIT_NUM				-1

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
	byte		direct_size;	//indicates the amount of bytes used to encode DIR arguments;
}				t_op;


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
	int					PC;
	t_op				current_op;
	int					last_live;
	t_champion			*owner;
	struct s_process	*next;
}						t_process;

typedef	struct 				s_process_list
{
	t_process				*process;
	struct s_process_list 	*next;
}							t_process_list;


typedef struct 			s_arena
{
	byte			memory[MEM_SIZE];
//	t_process*	 	process_list;
//	t_process*		process_table[PROCESS_TABLE_SIZE]; // a init vide;
	t_champion		champion_table[MAX_PLAYERS];
	int				nb_champs;
	int				option_dump;
	int				cycle;

	//live_related_info
	
}						t_arena;

int						usage();
int						error(char *str, char *str2);
int						pars_args(int ac, char **av, t_arena *vm);
