# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 17:02:33 by smodesto          #+#    #+#              #
#    Updated: 2022/03/15 20:18:29 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRC_PATH		= ./source/
INCLUDES_PATH	= ./includes/
OBJS_PATH		= ./objects/

SRCS_FILES =	root/Philo.c			\
				root/states.c			\
				root/eating.c			\
				root/creating_philos.c	\
				root/dining.c			\
				utils/ut_lft.c			\
				utils/ut_error_manager.c\
				utils/ut_philos_lst.c	\
				utils/ut_time.c			\
				utils/ut_check.c


SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

OBJS_FILES	= $(patsubst %.c, %.o, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_FILES))

HEADER_FILES	=	Philosophers.h		\
					utils.h				\
					structures.h

HEADERS = $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))

CC			= gcc
FLAGS		= -Wall -Wextra -g -pthread
INCLUDES	= -I$(INCLUDES_PATH)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(FLAGS) $(INCLUDES) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
			@mkdir -p objects
			@mkdir -p objects/root
			@mkdir -p objects/utils
			$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
			@rm -f $(OBJS)
			echo cleaned!
fclean:		clean
			@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
