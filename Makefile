INCLUDE_FOLDER=./includes
OBJ_FOLDER=out

SRCS_COREWAR_FOLDER=./srcs/arena
SRCS_UTILS_FOLDER=./srcs/utils
SRCS_ASM_FOLDER=./srcs/asm

CC=gcc
CFLAGS=-Wall -Wextra -Werror
INCLUDE_PATH=-I$(INCLUDE_FOLDER)
COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)
LIBS=libcorewar.a
NAME_COREWAR=corewar

COREWAR_SOURCE_FILES=cycle.c \
	main_arena.c \
	op.c \
	args.c \
	disp.c

UTILS_SOURCE_FILES=endian_converter.c \

ASM_SOURCE_FILES=main.c

INCLUDES_FILES=arena.h \
	bitMasks.h \

RELINK_INCUDE=$(addprefix $(INCLUDE_FOLDER)/, $(INCLUDES_FILES))
SRCS_UTILS=$(addprefix $(SRCS_UTILS_FOLDER)/, $(UTILS_SOURCE_FILES))
SRCS_ASM=$(addprefix $(SRCS_ASM_FOLDER)/, $(ASM_SOURCE_FILES))
SRCS_COREWAR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(COREWAR_SOURCE_FILES))

OUT_UTILS=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_UTILS:.c=.o)))
OUT_ASM=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_ASM:.c=.o)))
OUT_COREWAR=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_COREWAR:.c=.o)))


all: $(OBJ_FOLDER) libCorewar.a asm corewar

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

libCorewar.a: $(OUT_UTILS) Makefile $(RELINK_INCUDE)
	ar rc libCorewar.a $(OUT_UTILS)

$(OBJ_FOLDER)/%.o: $(SRCS_UTILS_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

asm: $(OUT_ASM) libCorewar.a Makefile $(RELINK_INCUDE)
	$(COMPILER) -o asm $(OUT_ASM) $(LIBS)

$(OBJ_FOLDER)/%.o: $(SRCS_ASM_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

corewar: $(OUT_COREWAR) libCorewar.a Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) $(LIBS) -L srcs/sdl_src -l SDL2-2.0.0 -l SDL2_image -l SDL2_ttf

$(OBJ_FOLDER)/%.o: $(SRCS_COREWAR_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)
	rm -f libCorewar.a

fclean: clean
	rm -f corewar
	rm -f asm

brew:
	sh brew_check.sh

re: fclean all