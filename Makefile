# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/22 19:37:40 by dberger           #+#    #+#              #
#    Updated: 2020/03/05 17:03:11 by jbarment         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NO_COLOR = \033[0m
YELLOW = \033[33m
GREEN = \033[32m
BLUE = \033[36m
PINK = \033[35m

INCLUDE_FOLDER=./includes
SDL_INCLUDE_FOLDER=./includes/sdl_include
OBJ_FOLDER=out

SRCS_COREWAR_FOLDER=./srcs/arena
SRCS_UTILS_FOLDER=./srcs/utils
SRCS_ASM_FOLDER=./srcs/asm

LIB_DIR= ./includes/libft
PRINTF_DIR = ./includes/ft_printf

LIB = $(PRINTF_DIR)/libftprintf.a $(LIB_DIR)/libft.a 

CC=gcc
CFLAGS= -Wall -Wextra -Werror
INCLUDE_PATH=-I $(INCLUDE_FOLDER) -I $(SDL_INCLUDE_FOLDER)

COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)
LIBS=libCorewar.a ./includes/libft/libft.a
NAME_COREWAR=corewar
NAME_ASM=asm

COREWAR_SOURCE_FILES=cycle.c \
	main_arena.c \
	args.c \
	disp.c \
	disp_init_var.c \
	disp_init_players.c \
	disp_init_info.c \
	event.c \
	event_mousebutton.c \
	event_mousemotion.c \
	update_visu.c \
	args_utils.c \
	process.c \
	process_utils.c \
	pars_args.c \
	pars_num_champ.c \
	pars_header.c \
	start_arena.c \
	0x01_live.c \
	0x02_load.c \
	0x03_store.c \
	0x04_add.c \
	0x05_sub.c \
	0x06_and.c \
	0x07_or.c \
	0x08_xor.c \
	0x09_zjump.c \
	0x10_ldi.c \
	0x11_sti.c \
	0x12_fork.c \
	0x13_lld.c \
	0x14_lldi.c \
	0x15_lfork.c \
	0x16_aff.c \
	debug.c

UTILS_SOURCE_FILES=endian_converter.c \
	op.c \
	read_write.c \
	ft_error.c \
	usage.c

ASM_SOURCE_FILES=main_asm.c \
	cor_file.c \
	asm_utils.c \
	op_code_utils.c \
	parsing_tester.c \
	print_tester.c \
	parse_header.c


INCLUDES_FILES=arena.h \
	op.h \
	bitMasks.h \

RELINK_INCUDE=$(addprefix $(INCLUDE_FOLDER)/, $(INCLUDES_FILES))
SRCS_UTILS=$(addprefix $(SRCS_UTILS_FOLDER)/, $(UTILS_SOURCE_FILES))
SRCS_ASM=$(addprefix $(SRCS_ASM_FOLDER)/, $(ASM_SOURCE_FILES))
SRCS_COREWAR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(COREWAR_SOURCE_FILES))

OUT_UTILS=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_UTILS:.c=.o)))
OUT_ASM=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_ASM:.c=.o)))
OUT_COREWAR=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_COREWAR:.c=.o)))


all: $(OBJ_FOLDER) $(LIB) libCorewar.a asm corewar

$(LIB):
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) -C $(PRINTF_DIR)

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

libCorewar.a: $(OUT_UTILS) Makefile $(RELINK_INCUDE)
	ar rc libCorewar.a $(OUT_UTILS)

$(OBJ_FOLDER)/%.o: $(SRCS_UTILS_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

asm: $(LIB) $(OUT_ASM) libCorewar.a Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_ASM) $(OUT_ASM) $(LIBS) $(LIB)
	echo "$(YELLOW)	--- $(GREEN)ASM$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_FOLDER)/%.o: $(SRCS_ASM_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

corewar: $(LIB) $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) $(LIBS)  $(LIB) -L srcs/sdl_src -l SDL2-2.0.0 -l SDL2_image -l SDL2_ttf
	echo "$(YELLOW)	--- $(GREEN)Corewar$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_FOLDER)/%.o: $(SRCS_COREWAR_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)
	rm -f libCorewar.a
	rm -f $(LIB_DIR)/*.o
	rm -f $(PRINTF_DIR)/*.o
	echo "$(BLUE)	--- Binary deleted ! ---	$(NO_COLOR)"

fclean: clean
	rm -f $(LIB_DIR)/*.a
	rm -f $(PRINTF_DIR)/*.a
	rm -f corewar
	rm -f asm
	echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

brew:
	sh brew_check.sh

re: fclean all

.SILENT:
