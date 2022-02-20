name = minishell
SRC = main.c libft.c lexer.c tokenizer.c xmalloc.c xexit.c
all:
	gcc $(SRC) -L/usr/include -lreadline -Wall -Wextra -Werror -o $(name) -fsanitize=address -g3 ; ./$(name)
clean:
	rm -rf $(name)