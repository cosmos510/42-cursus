# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/21 22:36:52 by maximemarti       #+#    #+#              #
#    Updated: 2024/09/22 12:19:31 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC =  gcc -Wall -Wextra -Werror

HEADERS  = ./includes
SRCDIR = srcs

SRCS = $(SRCDIR)/ft_putchar.c \
	   $(SRCDIR)/ft_putstr.c \
	   $(SRCDIR)/ft_strcmp.c \
	   $(SRCDIR)/ft_strlen.c \
	   $(SRCDIR)/ft_swap.c

OBJ = ft_putchar.o ft_putstr.o ft_strcmp.o ft_strlen.o ft_swap.o

all:	$(NAME)

$(NAME):
		$(CC) -c $(SRCS) -I $(HEADERS)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all
		