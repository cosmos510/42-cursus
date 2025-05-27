# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/23 10:24:32 by maximemarti       #+#    #+#              #
#    Updated: 2025/05/27 19:07:55 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

SRCS    = src/philo.c \
          src/error.c \
		  src/utils.c \
		  src/init_var.c \
		  src/safe_mutex.c \
		  src/safe_thread.c \

OBJS    = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
