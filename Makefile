# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/02/26 11:09:49 by ael-ghem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = minishell
# SRC = main.c libft.c lexer.c  xmalloc.c xexit.c list.c ft_split.c
SRC = main.c libft.c lexer.c  xmalloc.c xexit.c list.c exec_tools.c
FLAGS =  -lreadline  -I /Users/$(USER)/.brew/opt/readline/include

all:
	gcc $(SRC) -Wall -Werror -Wextra  $(FLAGS) -o $(name) -fsanitize=address -g3 && ./minishell

# all:
# 	gcc $(SRC) -L/usr/include -lreadline -o $(name)  && ./minishell

# to check memory leaks

# all:
# 	rm -rf memwatch.log && gcc $(SRC) -L/usr/include -lreadline -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c -o $(name) -fsanitize=address -g3 && ./minishell

clean:
	rm -rf $(name) minishell.dSYM