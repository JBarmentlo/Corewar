/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:31:05 by dberger           #+#    #+#             */
/*   Updated: 2020/02/07 15:56:00 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "arena.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>

/*
*****************
***** ERROR *****
*****************
*/

/*
**** Generic error
*/

# define NO_ERR				0x00000000
# define BAD_FORMAT			0x00000001

/*
**** name error
*/

# define NAME_ERR			0x00000010

/*
**** Rooms error
*/

# define INVALID_COORD		0x00000040
# define BAD_START_LETTER	0x00000080
# define MISS_ROOMS			0x00000100
# define SAME_NAME			0x00000200
# define SAME_COORD			0x00000400
# define START_ROOM			0x00000800
# define END_ROOM			0x00001000
# define TOO_FEW			0x00002000
# define UNKNOW_ROOM		0x00004000

/*
**** Type of errors
*/

# define ANTS_ERR			0x00010000
# define ROOMS_ERR			0x00020000
# define LINKS_ERR			0x00040000
# define PRE_PROCESS_ERR	0x00100000
# define PROCESS_ERR		0x00200000

/*
**** Critical errors
*/

# define READ_ERR			0x10000000
# define MALLOC_ERR			0x20000000
# define WRITE_ERR			0x40000000
# define FILE_ERR			0x80000000


/*
**** op_code
*/

# define LIVE 				0x01
# define LD 				0x02
# define ST 				0x03
# define ADD 				0x04
# define SUB 				0x05
# define AND				0x06
# define OR					0x07
# define XOR 				0x08
# define ZJMP 				0x09
# define LDI 				0x0a
# define STI 				0x0b
# define FORK 				0x0c
# define LLD 				0x0d
# define LLDI 				0x0e
# define LFORK 				0x0f
# define AFF 				0x10

/*
**** translation
*/

# define PROG_ASM		0
# define MAX_SIZE_FILE	2875
# define BITS_IN_OCTET	8

enum				e_state
{
	GET_NAME,
	GET_COMMENT,
	GET_PROCESS,
};
/*
typedef struct 		s_label
{
	char			*name;
	size_t			oct;
	t_list			*instruct_list;
}					t_label;
*/

typedef struct 		s_label
{
	char			*name;
	size_t			oct;
	char			**opt;
	struct s_label			*next;
}					t_label;

typedef struct 		s_instruct
{
	int				code;
}					t_instruct;

typedef struct		s_stack
{
	char			*champion_name;
	int				cur_label;
	enum e_state	state;
	char			*comment;
	t_label			*label_list;
}					t_stack;

typedef struct 		s_file
{
	int				fd;
	char			*name;
	char			*content;
	int				total_size;
	int				prog_size;
}					t_file;

int						usage(int prog);
int						ft_error(char *str, char *str2);
int						cor_file(char *source_file, t_file *out_file, int fd);
/////////////////////// asm utils   //////////////////////////
void					nb_to_binary(t_file *out_file, int octets, int indx, int nb);
int						count_bits(int nb);
void					write_in_file(t_file *out_file, int indx, int n);

#endif
