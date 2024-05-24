# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 15:40:20 by sdeutsch          #+#    #+#              #
#    Updated: 2024/04/30 10:34:17 by sdeutsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra
SRC = 	main.c \
		parsing/parse.c \
		parsing/token/token.c \
		parsing/token/token_len.c \
		parsing/token/token_type.c \
		parsing/utils_parse.c \
		parsing/data/data.c \
		parsing/data/data_len.c \
		variable/variable.c \
		parsing/data/utils_data.c \
		variable/utils_variable.c \
		programme/init_free.c \
		programme/utils_init_free.c \
		chek/chek_ligne.c \
		chek/utils_chek.c \
		chek/chek_commande.c \
		built_in/built_in_cd.c \
		built_in/built_in_echo.c \
		built_in/built_in_env.c \
		built_in/built_in_exit.c \
		built_in/built_in_export.c \
		built_in/built_in_pwd.c \
		built_in/built_in_unset.c \
		built_in/utils_built_in.c \
		built_in/utils_exit.c \
		built_in/utils_cd.c \
		built_in/utils_export.c \
		execution/child_process.c \
		execution/check_and_get_files.c \
		execution/heredoc.c \
		execution/exec.c \
		execution/util_exec.c \
		execution/signal.c \
	  
OBJ = $(SRC:.c=.o)
LIBFT_OBJ = libft/*.o
LIBFT = libft/libft.a
NAME = minishell

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all