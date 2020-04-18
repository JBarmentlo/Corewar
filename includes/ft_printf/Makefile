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

SOURCES = ft_printf.c\
ft_check_add.c\
ft_ltoa.c

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
INCLUDE = ft_printf.h

.PHONY: all clean fclean re norme

all: $(NAME)

$(NAME): $(OBJECTS) Makefile $(INCLUDE)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o:src/%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SILENT:
