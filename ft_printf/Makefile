# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/30 19:03:50 by ncoursol          #+#    #+#              #
#    Updated: 2019/09/23 14:51:02 by dberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NO_COLOR = \033[0m
YELLOW = \033[33m
GREEN = \033[32m
BLUE = \033[36m
PINK = \033[35m

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIB_DIR = ../libft
OBJ_FOLDER = out

SOURCES = ft_check_add.c\
ft_printf.c\
ft_ltoa.c

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
INCLUDE = ft_printf.h

.PHONY: all clean fclean re norme

all: $(NAME) $(OBJ_FOLDER)

$(NAME): $(OBJECTS) Makefile $(INCLUDE)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) libft.a
	mkdir -p $(OBJ_FOLDER)
	mv ./*.o $(OBJ_FOLDER)
	echo "$(YELLOW)	--- $(GREEN)ft_printf$(YELLOW) Compiled ! ---	$(NO_COLOR)"

$(OBJ_FOLDER)/%.o:src/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(LIB_DIR)/*.o
	rm -rf $(OBJ_FOLDER/$(OBJECTS)
	rm -rf $(OBJ_FOLDER)
	echo "$(BLUE)	--- Binary deleted ! ---	$(NO_COLOR)"

fclean: clean
	rm -rf $(LIB_DIR)/libft.a
	rm -rf $(NAME)
	echo "$(PINK)	--- Programm deleted ! ---	$(NO_COLOR)"

re: fclean all

.SILENT:
