/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmasks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:21:47 by user42            #+#    #+#             */
/*   Updated: 2020/05/07 17:21:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMASKS_H
# define BITMASKS_H
# define ONE			1
# define TWO			2
# define THREE			4
# define FOUR			8
# define FIVE			16
# define SIX			32
# define SEVEN			64
# define EIGHT			128
# define NINE			256
# define TEN			512
# define ELEVEN			1024
# define TWELVE			2048
# define THIRTEEN		4096
# define FOURTEEN		8192
# define FIFTEEN		16384
# define SIXTEEN		32768

# define LIVE			ONE
# define LOAD			TWO
# define STORE			THREE
# define ADD			FOUR
# define SUB			FIVE
# define AND			SIX
# define OR				SEVEN
# define XOR			EIGHT
# define ZJUMP			NINE
# define LDI			TEN
# define STI			ELEVEN
# define FORK			TWELVE
# define LLD			THIRTEEN
# define LLDI			FOURTEEN
# define LFORK			FIFTEEN
# define AFF			SIXTEEN

# define TWO_LOWEST		3

# define MODULO_MASK	4095
/*
** usage : TEST_PRINT (LIVE + STORE + FORK)
*/
# define ALL			65535
# define TEST_PRINT		0
# define HEX_DUMP		0
# define VERBOSE		TEST_PRINT
# define MAX_TURNS		20
# define PRINT_VM_STATE	0
#endif
