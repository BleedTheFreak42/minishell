name = minishell
SRC = main.c libft.c lexer.c tokenizer.c xmalloc.c xexit.c parser.c
all:
	gcc $(SRC) -L/usr/include -lreadline -Wall -Wextra -Werror -o $(name) -fsanitize=address -g3 && ./minishell
clean:
	rm -rf $(name)