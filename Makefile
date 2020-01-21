INCLUDE_FOLDER=./includes
OBJ_FOLDER=out

SRCS_COREWAR_FOLDER=./srcs/arena
SRCS_UTILS_FOLDER=./srcs/utils
SRCS_ASM_FOLDER=./srcs/asm

CC=gcc
CFLAGS=
INCLUDE_PATH=-I$(INCLUDE_FOLDER)
COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)
LIBS=libCorewar.a
NAME_COREWAR=corewar

COREWAR_SOURCE_FILES=cycle.c \
	main_arena.c \
	args.c \
	VM_tester.c \
	args_utils.c \
	process.c \
	0x01.c \
	0x02.c \
	0x03.c \
	0x04.c \
	0x05.c \
	0x06.c \
	0x07.c \
	0x08.c \
	0x09.c \
	0x10.c \
	0x11.c \
	0x12.c \
	0x13.c \
	0x14.c \
	0x15.c \
	0x16.c \


UTILS_SOURCE_FILES=endian_converter.c \
	op.c \
	read_write.c \


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
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) $(LIBS)

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
