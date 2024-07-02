# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 21:25:01 by ichaabi           #+#    #+#              #
#    Updated: 2024/07/02 23:10:12 by ichaabi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_B =

CC = cc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

RM = rm -f

SRC =	ft_atoi.c \
		parse_input.c \
		utils_parsing.c \
		philo.c \
		get_time.c \
		forks.c \
		routines.c \
		free_memory.c \
		threads.c \


SRC_B =

OBJ = $(SRC:.c=.o)

OBJB = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

bonus: $(OBJB)
	$(CC) $(OBJB) -o $(NAME_B)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re

