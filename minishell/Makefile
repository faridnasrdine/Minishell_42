# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 14:41:13 by nafarid           #+#    #+#              #
#    Updated: 2025/07/28 11:03:11 by nafarid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c bultins/echo_cmd.c \
		bultins/cd_cmd.c bultins/pwd_cmd.c bultins/envir_utils.c bultins/cd_cmd_utils.c bultins/export_cmd.c bultins/envir.c \
		tokens/tokenizer.c tokens/tokens_utils.c parsing/parse.c parsing/parse_utils.c executing/executing_cmd.c executing/executing_cmd_utils.c env_to_lst.c \
		cleaning/lst_del.c parsing/parse_helpers.c parsing/parse_opers.c cleaning/quote_del.c change_stat.c p_expansion.c \
		argument_count.c word_split.c lstadd_front.c lstadd_back.c heredoc.c cleaning/lst_clear.c signals.c lst_new_ele.c arr_free.c tokens/toks_trim.c \
		executing/run_child.c executing/dups.c executing/executing_utils.c bultins/unset_cmd.c bultins/exit_cmd.c \
		tokens/lstadd_back_token.c env_lst_to_arr.c tokens/lst_last_token.c shell_vl.c ft_lstlast.c utils.c handle_dollar_cmd.c helpers.c \
		executing/run_child_utils.c cleaning/cleanup.c
		
OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = libft
FLAGS = -lreadline
LIB = $(LIBFT_DIR)/libft.a
all: $(NAME)

$(NAME) : $(OBJS)
	@cd $(LIBFT_DIR) && $(MAKE) -s
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGS)

.o :.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@cd $(LIBFT_DIR) && $(MAKE) -s clean
	@rm -f $(OBJS)

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
