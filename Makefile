# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 17:41:20 by pbongiov          #+#    #+#              #
#    Updated: 2025/08/19 18:09:14 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_FILES = plátōn.c

SRCS_DIR = srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

OBJS_DIR = objs

OBJS	=$(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

CFLAGS = -g -Wall -Wextra -Werror
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
	make re && clear && ./philo

.PHONY : all clean fclean re