# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/22 19:37:40 by dberger           #+#    #+#              #
#    Updated: 2020/04/28 10:00:39 by user42           ###   ########.fr        #
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
SRCS_VISU_FOLDER=./srcs/visu

LIB_DIR= ./includes/libft
PRINTF_DIR = ./includes/ft_printf

LIB = $(PRINTF_DIR)/libftprintf.a $(LIB_DIR)/libft.a 

SCANNER=/Users/dberger/static_analyzer/bin/scan-build
CC=clang
CFLAGS= -Wall -Wextra -Werror -g3
INCLUDE_PATH=-I $(INCLUDE_FOLDER) -I $(SDL_INCLUDE_FOLDER)

COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)
LIBS=libCorewar.a ./includes/libft/libft.a
NAME_COREWAR=corewar
NAME_ASM=asm

VISU_SOURCE_FILES=disp.c \
	disp_init_var.c \
	disp_init_players.c \
	disp_init_info.c \
	event.c \
	event_mousebutton.c \
	event_mousemotion.c \
	update_visu.c \
	update_info_op.c \
	update_info_players.c \
	update_info_global.c \
	update_info_arena.c \

COREWAR_SOURCE_FILES=cycle.c \
	args.c \
	args_utils.c \
	args_utils2.c \
	process.c \
	process_utils.c \
	process_utils2.c \
	pars_args.c \
	pars_num_champ.c \
	pars_header.c \
	start_arena.c \
	x01_live.c \
	x02_load.c \
	x03_store.c \
	x04_add.c \
	x05_sub.c \
	x06_and.c \
	x07_or.c \
	x08_xor.c \
	x09_zjump.c \
	x10_ldi.c \
	x11_sti.c \
	x12_fork.c \
	x13_lld.c \
	x14_lldi.c \
	x15_lfork.c \
	x16_aff.c \
	debug.c \
	end_free.c 

UTILS_SOURCE_FILES=endian_converter.c \
	op.c \
	read_write.c \
	ft_error.c \
	usage.c \
	mem_color.c \
	display_winner.c

ASM_SOURCE_FILES=main_asm.c \
	gnl.c \
	cor_file.c \
	header_content.c \
	header_type.c \
	parsing_exec.c \
	parsing_args.c \
	token_utils.c \
	op_utils.c \
	arg_utils.c \
	parsing_utils.c \
	writing_utils.c \
	asm_free.c 

INCLUDES_FILES= utils.h\
	op.h \
	asm.h \
	arena.h \
	bitMasks.h 


RELINK_INCUDE=$(addprefix $(INCLUDE_FOLDER)/, $(INCLUDES_FILES))
SRCS_UTILS=$(addprefix $(SRCS_UTILS_FOLDER)/, $(UTILS_SOURCE_FILES))
SRCS_ASM=$(addprefix $(SRCS_ASM_FOLDER)/, $(ASM_SOURCE_FILES))
SRCS_COREWAR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(COREWAR_SOURCE_FILES))
SRCS_VISU=$(addprefix $(SRCS_VISU_FOLDER)/, $(VISU_SOURCE_FILES))

OUT_VISU=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_VISU:.c=.o)))
OUT_UTILS=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_UTILS:.c=.o)))
OUT_ASM=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_ASM:.c=.o)))
OUT_COREWAR=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_COREWAR:.c=.o)))

SDLPATH= $(shell locate libSDL2.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)
SDLIMAGEPATH= $(shell locate libSDL2_image.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)
SDLTTFPATH = $(shell locate libSDL2_ttf.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)

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

corewar: $(LIB) $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE) srcs/arena/main_no_visu.c
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) srcs/arena/main_no_visu.c $(LIBS) $(LIB)
	echo "$(YELLOW)	--- $(GREEN)Corewar$(YELLOW) Compiled ! ---	$(NO_COLOR)"

corewar_visu: visu $(LIB) $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE) srcs/arena/main_arena.c
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) srcs/arena/main_arena.c visu.a  $(LIBS) $(LIB) -L $(SDLPATH) -L $(SDLIMAGEPATH) -L $(SDLTTFPATH) -l SDL2 -l SDL2_image -l SDL2_ttf
	echo "$(YELLOW)	--- $(GREEN)corewar_visu$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_FOLDER)/%.o: $(SRCS_COREWAR_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

visu: $(OBJ_FOLDER) $(OUT_VISU) $(RELINK_INCUDE)
	ar cr visu.a $(OUT_VISU)

$(OBJ_FOLDER)/%.o: $(SRCS_VISU_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)
	rm -f libCorewar.a
	rm -f $(LIB_DIR)/*.o
	rm -f $(PRINTF_DIR)/*.o
	rm -f visu.a
	echo "$(BLUE)	--- Binary deleted ! ---	$(NO_COLOR)"

fclean: clean
	$(RM) log
	rm -f $(LIB_DIR)/*.a
	rm -f $(PRINTF_DIR)/*.a
	rm -f corewar
	rm -f asm
	echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

brew:
	sh brew_check.sh

re: fclean
	$(MAKE)

.PHONY: re all fclean clean asm corewar
.SILENT:
scan=/Users/ncoursol/Documents/corewar/static_analyzer/bin/scan-build
