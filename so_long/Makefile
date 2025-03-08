# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:19:50 by maxmarti          #+#    #+#              #
#    Updated: 2025/01/05 23:32:46 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CSRC =	main.c \
	src/check_map.c \
	src/free_map.c \
	src/is_map_solvable.c \
	src/map_utils.c \
	src/init_struct.c \
	src/init_img.c \
	src/move_it.c \
	src/utils.c \
	src/utils2.c \
	src/utils_move.c \

OSRC = $(CSRC:.c=.o)
INC = /usr/include
INCLIB = $(INC)/../lib

LFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
SANITFLAG = -g3 -fsanitize=address
GCCCMD = gcc

# Compilation rule with -Wall -Wextra -Werror flags
%.o: %.c
	$(GCCCMD) -Wall -Wextra -Werror -I/usr/include/ -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OSRC)
	@make -C libft
	@make -C mlx_linux
	@$(GCCCMD) $(OSRC) ./libft/libft.a -I./ $(LFLAGS) -o $(NAME)

clean:
	@make -C libft/ clean
	@make -C mlx_linux/ clean
	@rm -f $(OSRC)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re:
	@echo "\033[33mRecompiling so_long project...\033[0m"
	@make fclean all

.PHONY: all clean fclean re

