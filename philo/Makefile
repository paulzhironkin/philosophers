# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 16:18:28 by latahbah          #+#    #+#              #
#    Updated: 2022/06/20 15:53:32 by latahbah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIST =	philo.c			data_init.c		free_data.c \
		utils.c			life_funcs.c	simulation.c \
		death_checker.c	


OBJ = $(patsubst %.c,%.o,$(LIST))

D_FILES = $(patsubst %.c,%.d,$(LIST))

OPTFLAGS = -O2
FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OPTFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	gcc $(FLAGS) $(OPTFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean:
	@rm -f $(OBJ) $(D_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean	all

.PHONY: all clean fclean re bonus
