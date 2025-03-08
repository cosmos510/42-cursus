# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 18:15:25 by maximemarti       #+#    #+#              #
#    Updated: 2024/10/12 14:07:39 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = libftprintf.a
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -rf
SRCS            = ft_printf.c \
					print_cs.c \
					print_di.c \
					print_x.c \
					print_ptr.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				cp $(LIBFT) $(NAME)
				ar rcs $(NAME) $(OBJS)

$(LIBFT):
				make bonus -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS)

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all