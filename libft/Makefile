# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tburtin <tburtin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 16:28:11 by sdeutsch          #+#    #+#              #
#    Updated: 2024/04/29 18:03:08 by tburtin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_compare.c \
			ft_itoa.c \
			ft_memset.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_substr.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_lstadd_back.c \
			ft_lstlast.c \
			ft_lstnew.c \
			ft_lstsize.c
				
OBJ = $(SRC:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:     clean
	rm -f $(NAME)

re:   fclean all