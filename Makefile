# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 21:25:01 by ichaabi           #+#    #+#              #
#    Updated: 2024/07/04 17:10:54 by ichaabi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

RM = rm -f

SRC =	ft_atoi.c \
		parse_input.c \
		utils_parsing_1.c \
		utils_parsing_2.c \
		utils_parsing_3.c \
		philo.c \
		get_time.c \
		forks.c \
		utils_routine.c \
		routines.c \
		initialize.c \
		threads.c \
		free_memory.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
