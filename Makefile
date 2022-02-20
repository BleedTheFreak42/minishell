name = minishell
SRC = main.c libft.c lexer.c tokenizer.c
all:
	gcc $(SRC) -L/usr/include -lreadline -o $(name) ; ./$(name)
clean:
	rm -rf $(name)