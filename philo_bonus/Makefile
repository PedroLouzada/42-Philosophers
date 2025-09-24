# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 16:43:33 by pbongiov          #+#    #+#              #
#    Updated: 2025/09/24 19:39:00 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS_FILES = philo_bonus.c initialize.c utils.c routine.c

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = objs

OBJS	=$(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

CFLAGS = -g -Iinclude #-fsanitize=thread #-Wall -Wextra -Werror
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
	@rm -rf $(NAME) $(OBJS_DIR)

re:		fclean 	all

r:
	make re && clear && ./philo_bonus 3 700 400 300

v:
	make re && clear && valgrind --tool=helgrind ./philo_bonus 3 700 400 300

.PHONY : all clean fclean re