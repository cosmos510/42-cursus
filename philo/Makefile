# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 10:15:52 by maximemarti       #+#    #+#              #
#    Updated: 2025/06/02 19:12:35 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name 	= philo
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
DEBUG_FLAGS = -DDEBUG=1

NAME    = philo

SRC     = src/philo.c src/utils.c src/cleanup.c src/monitor.c src/init_var.c src/debug.c src/dinner.c src/debug_utils.c src/init_var_utils.c src/utils_color.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug