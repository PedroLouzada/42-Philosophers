# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 17:41:20 by pbongiov          #+#    #+#              #
#    Updated: 2025/08/26 15:24:27 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_FILES = philo.c utils.c initialize.c

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = objs

OBJS	=$(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

CFLAGS = -g -Iinclude #-Wall -Wextra -Werror
CC = cc

all:	$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@rm -rf $(OBJS)

fclean:		clean
	@rm -rf $(NAME)

re:		fclean 	all

r:
	make re && clear && ./philo 3 2 3 4

v:
	make re && clear && valgrind ./philo 10 2 3 4

.PHONY : all clean fclean re