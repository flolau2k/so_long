# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 11:17:07 by flauer            #+#    #+#              #
#    Updated: 2023/07/10 10:47:54 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		so_long

CC =		cc
CFLAGS =	-g 
#-Wall -Wextra -Werror

LIBFTDIR =	libft
LIBMLXDIR =	MLX42
LIBFT =		$(LIBFTDIR)/libft.a
LIBMLX =	$(LIBMLXDIR)/build/libmlx42.a
LIBS =		$(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

INCLUDES =	-I$(LIBMLXDIR)/include -I$(LIBFTDIR)/include -Iinclude

OBJDIR =	obj
SRCDIR =	src

FILES =		so_long.c

SRC =		$(addprefix $(SRCDIR)/, $(FILES))
OBJ =		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re:	fclean all

$(LIBFT):
	@git submodule update --init --recursive
	@make -C $(@D)

$(LIBMLX):
	@git submodule update --init --recursive
	@cd MLX42 && cmake -B build && cmake --build build -j4

.PHONY =	all clean fclean re
