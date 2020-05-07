/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:31:05 by dberger           #+#    #+#             */
/*   Updated: 2020/05/07 17:22:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdint.h>
# include "op.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "sdl_include/SDL.h"
# include "sdl_include/SDL_image.h"
# include "sdl_include/SDL_ttf.h"

# define TRUE				1
# define FALSE				0
# define PADDING			4
# define SIZE_HEADER		2192
# define SIZE_MAX_PROG		2875

typedef unsigned char		t_byte;

/*
** is_direct_small : indicates the amount of bytes used to encode
** DIR arguments
** if == 1: 2 bytes, if == 0: 4 bytes.
** encoding_byte indicates the presence (if == 1) of an argument
** encoding byte after the opcode;
*/

typedef struct				s_op
{
	char					*name;
	t_byte					arg_nb;
	t_byte					arg_types[MAX_ARGS_NUMBER];
	t_byte					opcode;
	uint					cycle_to_wait;
	char					*full_name;
	t_byte					encoding_byte;
	t_byte					is_direct_small;
	t_byte					idx_mod_applies;
}							t_op;

extern	t_op				g_op_tab[17];

int							usage(int prog);
void						*ft_error(char *str, char *str2);

#endif
