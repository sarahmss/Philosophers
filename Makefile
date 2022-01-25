# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 10:54:58 by smodesto          #+#    #+#              #
#    Updated: 2022/01/24 11:38:05 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR = ./

SRCS =	Philo.c

SRCS_OBJS = $(SRCS:.c=.o)

CC = gcc

C_FLAGS = -Wall -Werror -Wextra -g -pthread

all:		$(NAME)

$(NAME):	$(SRCS_OBJS)
			@$(CC) $(C_FLAGS) $(SRCS) -o $(NAME)
clean :
		@rm -rf $(SRCS_OBJS)

fclean:		clean
		@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
