# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/03/03 11:43:29 by ytaya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


name = minishell
# SRC = main.c libft.c lexer.c  xmalloc.c xexit.c list.c ft_split.c
SRC =  libft.c\
libft1.c\
libft2.c\
libft3.c\
lexer.c\
lexer1.c\
lexer2.c\
xmalloc.c\
xexit.c list.c\
parser.c\
parser1.c\
expand.c\
minishell.c\
ft_expand_helpers.c\
parser2.c\
signals.c\
ft_unset.c\
exec.c\
exec_tools.c

FLAGS =  -lreadline -L /Users/ytaya/.brew/opt/readline/lib -I /Users/ytaya/.brew/opt/readline/include

all:
	gcc $(SRC) main.c -Wall -Werror -Wextra  $(FLAGS) -o $(name) -fsanitize=address -g3 && ./minishell

# all:
# 	gcc $(SRC) -L/usr/include -lreadline -o $(name)  && ./minishell

# to check memory leaks

# all:
# 	rm -rf memwatch.log && gcc $(SRC) -L/usr/include -lreadline -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c -o $(name) -fsanitize=address -g3 && ./minishell

clean:
	rm -rf $(name) minishell.dSYM