/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2020/01/22 18:32:59 by jbarment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
/*
typedef struct	s_op
{
	char*	name;
	int		arg_nb;
	int		arg_types;
	int		opcode;
	int		cycle_to_wait;
	char*	full_name;
	int		encoding_byte; 	//indicates the presence, or not, of an argument encoding byte after the opcode;
	int		is_direct_small;	//indicates the amount of bytes used to encode DIR arguments; 1 => 2, 0 => 4;
}				t_op;
*/

t_op    g_op_tab[17] =
{
	{"live"	, 1, {T_DIR}												, 1	, 10	, "alive"								, 0, 0, 1},
	{"ld"	, 2, {T_DIR | T_IND, T_REG}									, 2	, 5		, "load"								, 1, 0, 1},
	{"st"	, 2, {T_REG, T_IND | T_REG}									, 3	, 5		, "store"								, 1, 0, 1},
	{"add"	, 3, {T_REG, T_REG, T_REG}									, 4	, 10	, "addition"							, 1, 0, 1},
	{"sub"	, 3, {T_REG, T_REG, T_REG}									, 5	, 10	, "soustraction"						, 1, 0, 1},
	{"and"	, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}	, 6	, 6		,	"et (and  r1, r2, r3   r1&r2 -> r3"	, 1, 0, 1},
	{"or"	, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}	, 7	, 6		, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 1},
	{"xor"	, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}	, 8	, 6		,"ou (xor  r1, r2, r3   r1^r2 -> r3"	, 1, 0, 1},
	{"zjmp"	, 1, {T_DIR}												, 9	, 20	, "jump if zero"						, 0, 1, 1},
	{"ldi"	, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}			, 10, 25	, "load index"							, 1, 1, 1},
	{"sti"	, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}			, 11, 25	, "store index"							, 1, 1, 1},
	{"fork"	, 1, {T_DIR}												, 12, 800	, "fork"								, 0, 1, 1},
	{"lld"	, 2, {T_DIR | T_IND, T_REG}									, 13, 10	, "long load"							, 1, 0, 0},
	{"lldi"	, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}			, 14, 50	, "long load index"						, 1, 1, 0},
	{"lfork", 1, {T_DIR}												, 15, 1000	, "long fork"							, 0, 1, 0},
	{"aff"	, 1, {T_REG}												, 16, 2		, "aff"									, 1, 0, 1},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};