# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 09:05:54 by ytaya             #+#    #+#              #
#    Updated: 2022/03/10 11:39:46 by ael-ghem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


name = minishell
usr = ael-ghem
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
exec1.c\
exec_tools.c\
ft_atoi.c\
ft_itoa.c\
ft_handle_file.c\
exec_tools1.c

FLAGS =  -lreadline -L /Users/$(usr)/goinfre/.brew/opt/readline/lib -I /Users/$(usr)/goinfre/.brew/opt/readline/include

all:
	gcc $(SRC) main.c -Wall -Werror -Wextra  $(FLAGS) -o $(name)  -g3
#-fsanitize=address -g3
# gcc $(SRC) main.c -Wall -Werror -Wextra  $(FLAGS) -o $(name) -fsanitize=address -g3


clean:
	rm -rf $(name) minishell.dSYM