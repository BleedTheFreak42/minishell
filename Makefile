# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/03/10 00:49:16 by ytaya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


name = minishell
usr = ytaya
SRC =  libft.c\
xmalloc.c\
xexit.c list.c\
expand.c\
ft_expand_helpers.c\
minishell.c\
signals.c\
libft1.c\
libft2.c\
libft3.c\
lexer.c\
lexer1.c\
lexer2.c\
parser.c\
parser1.c\
parser2.c\
parser3.c\
builtin.c\
builtin1.c\
builtin2.c\
builtin3.c\
builtin4.c\
exec.c\
exec_tools.c\
ft_atoi.c\
ft_itoa.c

FLAGS =  -lreadline -L /Users/$(usr)/.brew/opt/readline/lib -I /Users/$(usr)/.brew/opt/readline/include

all:
	gcc $(SRC) main.c -Wall -Werror -Wextra  $(FLAGS) -o $(name) -fsanitize=address -g3


clean:
	rm -rf $(name) minishell.dSYM