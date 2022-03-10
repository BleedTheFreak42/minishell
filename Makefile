# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/03/10 14:06:04 by ytaya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USER = ytaya
NAME = minishell
SRC =  helpers/libft.c\
helpers/xmalloc.c\
helpers/xexit.c\
helpers/list.c\
parser/expand.c\
parser/ft_expand_helpers.c\
helpers/minishell.c\
helpers/libft1.c\
helpers/libft2.c\
helpers/libft3.c\
lexer/lexer.c\
lexer/lexer1.c\
lexer/lexer2.c\
parser/parser.c\
parser/parser1.c\
parser/parser2.c\
parser/parser3.c\
builtin/builtin.c\
builtin/builtin1.c\
builtin/builtin2.c\
builtin/builtin3.c\
builtin/builtin4.c\
execution/exec.c\
execution/exec1.c\
execution/exec_tools.c\
helpers/ft_atoi.c\
helpers/ft_itoa.c\
execution/ft_handle_file.c\
execution/exec_tools1.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = gcc

rl_line =  -lreadline -L /Users/${USER}/.brew/opt/readline/lib -I /Users/${USER}/.brew/opt/readline/include

all:$(NAME)

$(NAME): $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(SRC) signals/signals.c main.c $(rl_line) -o $(NAME)

clean:
	rm -rf $(OBJ)
fclean:clean
	rm -rf $(NAME)
re: fclean all