#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include "op.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "sdl_include/SDL.h"
# include "sdl_include/SDL_image.h"
# include "sdl_include/SDL_ttf.h"

# define	TRUE		1
# define	FALSE		0
# define	PADDING		4
# define	SIZE_HEADER	2192
#define		SIZE_MAX_PROG	2875

typedef unsigned int		uint;
typedef unsigned char		byte;
typedef unsigned short		uint16_t;

typedef struct			s_op
{
	char*			name;
	byte			arg_nb;
	byte			arg_types[MAX_ARGS_NUMBER];
	byte			opcode;
	uint			cycle_to_wait;
	char*			full_name;
	byte			encoding_byte; 	//indicates the presence, or not, of an argument encoding byte after the opcode;
	byte			is_direct_small;	//indicates the amount of bytes used to encode DIR arguments; 1 => 2 0 => 4
	byte			idx_mod_applies;
}				t_op;

extern	t_op			g_op_tab[17];

int				usage(int prog);
void				*ft_error(char *str, char *str2);
void				*ft_error_nb(char *str, char *str2, int line, int col);

#endif
