# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 11:22:18 by maximemarti       #+#    #+#              #
#    Updated: 2024/09/22 11:57:52 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file

CC = gcc 
CFLAGS = -Wall -Wextra -Werror

HEADERS = ft_display_file.h

SRCS=$(wildcard ./*.c)

OBJ=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
