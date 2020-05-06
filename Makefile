# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakefileLinux                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/22 19:37:40 by dberger           #+#    #+#              #
#    Updated: 2020/04/30 20:43:08 by deyaberge        ###   ########.fr        #
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

CC=clang
CFLAGS= -Wall -Wextra -Werror -g3
INCLUDE_PATH=-I $(INCLUDE_FOLDER) -I $(SDL_INCLUDE_FOLDER)

COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)
LIBS=libCorewar.a $(PRINTF_DIR)/libftprintf.a $(LIB_DIR)/libft.a
NAME_COREWAR=corewar
NAME_COREWAR_VISU=corewar_visu
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
	start_arena_utils.c \
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

MAIN_COR = main_arena.c

MAIN_VISU = main_visu.c

UTILS_SOURCE_FILES=endian_converter.c \
	op.c \
	read_write.c \
	ft_error.c \
	usage.c \
	mem_color.c \
	display_winner.c \
	read_write_2.c

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
	bitmasks.h 


RELINK_INCUDE=$(addprefix $(INCLUDE_FOLDER)/, $(INCLUDES_FILES))
SRCS_UTILS=$(addprefix $(SRCS_UTILS_FOLDER)/, $(UTILS_SOURCE_FILES))
SRCS_ASM=$(addprefix $(SRCS_ASM_FOLDER)/, $(ASM_SOURCE_FILES))
SRCS_COREWAR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(COREWAR_SOURCE_FILES))
SRCS_MAIN_COR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(MAIN_COR))
SRCS_VISU=$(addprefix $(SRCS_VISU_FOLDER)/, $(VISU_SOURCE_FILES))
SRCS_MAIN_VISU=$(addprefix $(SRCS_VISU_FOLDER)/, $(MAIN_VISU))

OUT_UTILS=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_UTILS:.c=.o)))
OUT_ASM=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_ASM:.c=.o)))
OUT_COREWAR=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_COREWAR:.c=.o)))
OUT_COREWAR_M=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_MAIN_COR:.c=.o)))
OUT_VISU=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_VISU:.c=.o)))
OUT_VISU_M=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_MAIN_VISU:.c=.o)))

SDLPATH= $(shell locate libSDL2.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)
SDLIMAGEPATH= $(shell locate libSDL2_image.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)
SDLTTFPATH = $(shell locate libSDL2_ttf.so | grep -m1 "" | rev | cut -d "/" -f 2- | rev)

all: $(OBJ_FOLDER) $(LIB) libCorewar.a asm corewar

$(LIB):
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) -C $(PRINTF_DIR)

$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

libCorewar.a: $(OUT_UTILS) Makefile $(RELINK_INCUDE)
	ar rc libCorewar.a $(OUT_UTILS)

$(OBJ_FOLDER)/%.o: $(SRCS_UTILS_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

asm: $(LIB) $(OUT_ASM) libCorewar.a Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_ASM) $(OUT_ASM) $(LIBS)
	echo "$(YELLOW)	--- $(GREEN)ASM$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_FOLDER)/%.o: $(SRCS_ASM_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

corewar: $(LIB) $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE) $(OUT_COREWAR_M)
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) $(OUT_COREWAR_M) $(LIBS)
	echo "$(YELLOW)	--- $(GREEN)Corewar$(YELLOW) Compiled ! ---	$(NO_COLOR)"

corewar_visu: visu $(LIB) $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE) $(OUT_VISU_M)
	$(COMPILER) -o $(NAME_COREWAR_VISU) $(OUT_COREWAR) $(OUT_VISU_M) visu.a  $(LIBS) -L $(SDLPATH) -L $(SDLIMAGEPATH) -L $(SDLTTFPATH) -l SDL2 -l SDL2_image -l SDL2_ttf
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
	rm -f corewar corewar_visu asm
	echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

brew:
	sh brew_check.sh

re: fclean
	$(MAKE)

.PHONY: re all fclean clean asm corewar
.SILENT:
