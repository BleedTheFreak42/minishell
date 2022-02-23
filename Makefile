# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/02/23 09:10:20 by ytaya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = minishell
SRC = main.c libft.c lexer.c  xmalloc.c xexit.c list.c

all:
	gcc $(SRC) -L/usr/include -lreadline  -o $(name) -fsanitize=address -g3 && ./minishell

# all:
# 	gcc $(SRC) -L/usr/include -lreadline -Wall -Wextra -Werror -o $(name)  && ./minishell

# to check memory leaks

# all:
# 	rm -rf memwatch.log && gcc $(SRC) -L/usr/include -lreadline -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c -o $(name) -fsanitize=address -g3 && ./minishell

clean:
	rm -rf $(name) minishell.dSYM