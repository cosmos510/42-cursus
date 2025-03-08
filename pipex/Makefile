# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 20:41:57 by cosmos            #+#    #+#              #
#    Updated: 2025/01/14 11:18:25 by cosmos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = pipex

CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -rf

SRCS            = src/pipex.c \
				  src/path_utils.c \
				  src/free_it.c \
				  src/commande_utils.c \
				  src/execute.c \

BONUS_SRCS      = bonus/pipex_bonus.c \
				  src/path_utils.c \
				  src/free_it.c \
				  src/commande_utils.c \
				  bonus/execute_bonus.c \
				  bonus/utils_bonus.c \

OBJS            = $(SRCS:.c=.o)
BONUS_OBJS      = $(BONUS_SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus:          $(NAME).bonus

$(NAME).bonus:  $(LIBFT) $(BONUS_OBJS)
				@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)
				@touch $(NAME).bonus

$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS) $(BONUS_OBJS) $(NAME).bonus

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all
