# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 14:41:13 by nafarid           #+#    #+#              #
#    Updated: 2025/06/11 14:31:34 by nafarid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c utils.c pars.c cheking_lexer.c test_function.c check_dolar.c utils1.c executing/bultins/echo_cmd.c \
		executing/bultins/cd_cmd.c executing/bultins/pwd_cmd.c executing/bultins/exit_cmd.c executing/bultins/unset_cmd.c\
		executing/singal_exec.c executing/executing_cmd.c executing/executing_cmd_utils.c executing/bultins/export_cmd.c\
		executing/utils.c executing/bultins/env_cmd.c
OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
FLAGS = -lreadline
LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a
all: $(NAME)

$(NAME) : $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) -s
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGS)

%.o :%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd $(LIBFT_DIR) && $(MAKE) clean -s
	rm -f $(OBJS)

fclean: clean
	cd $(LIBFT_DIR) && $(MAKE) fclean -s
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re