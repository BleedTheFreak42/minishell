name = minishell
SRC = main.c libft.c lexer.c tokenizer.c xmalloc.c xexit.c parser.c

all:
	gcc $(SRC) -L/usr/include -lreadline -Wall -Wextra -Werror -o $(name) -fsanitize=address -g3 && ./minishell

# to check memory leaks

# all:
# 	rm -rf memwatch.log && gcc $(SRC) -L/usr/include -lreadline -w -DMEMWATCH -DMW_STDIO memwatch-2.71/memwatch.c -o $(name) -fsanitize=address -g3 && ./minishell

clean:
	rm -rf $(name) minishell.dSYM