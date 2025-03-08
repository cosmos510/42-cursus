# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxmarti <maxmarti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 11:19:50 by maxmarti          #+#    #+#              #
#    Updated: 2024/12/19 08:15:06 by maxmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = push_swap
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -rf
SRCS            = main.c \
				  check_args.c \
				  initialize_stack.c \
				  instructions.c \
				  instructions_2.c \
				  helper_instructions.c \
				  sort_it.c \
				  free_struct.c \
				  utils.c \
				  utils2.c \

OBJS            = $(SRCS:.c=.o)

LIBFT_PATH      = ./libft
LIBFT           = $(LIBFT_PATH)/libft.a

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

all:            $(NAME)

$(NAME):        $(LIBFT) $(OBJS)
				cp $(LIBFT) $(NAME)
				@${CC} ${CFLAGS} ${OBJS} libft/libft.a -o ${NAME}


$(LIBFT):
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				$(RM) $(OBJS)

fclean:         clean
				make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:             fclean all