#include "minishell.h"

// char *copyto(char *from,char *to)
// {
// 	int i;
// 	char *result;

// 	result = (char *) malloc(sizeof(to -from + 1) * sizeof(char));
// 	i = 0;

// 	while (from[i] != *to)
// 	{
// 		result[i] = from[i];
// 		i++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

char *ft_expand(char *str)
{
	int i;
	int j;

	char *result[3];
	char *from;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	result[0] = malloc(sizeof(char) * i);
	ft_strlcpy(result[0],str,i + 1);
	if (str[i++] == '$')
	{
		//check => $"PWD"
		j = i;
		while (str[i] && str[i] != 32 && str[i] != '\"' && str[i] != 39)
			i++;
		from = ft_substr(&str[j],0,i - j);
		result[1] = getenv(from);
		if (!result[1])
			return (str);
		result[2] = ft_strdup(&str[i]);
	}
	if (result[0] && result[1] && result[2])
		return (ft_strjoin(ft_strjoin(result[0],result[1]),result[2]));
	return (NULL);
}

int get_nbdollar(char *str)
{
	int c;

	c = 0;
	str = ft_strchrq(str,'$');
	while (str)
	{
		str++;
		if (*str == 32 || *str == '$')
			return (-1);
		c++;
		str = ft_strchrq(str,'$');
	}
	return (c);
}

char *ft_expandall(char *str)
{
	int nb;
	char *result;

	nb = get_nbdollar(str);
	result = str;
	if (nb == -1)
		return(NULL);
	while (nb--)
		result = ft_expand(result);
	return (result);
}

int main(int argc, char const *argv[])
{
	char *str;
	t_lexer *lexer;

	// str = "\"$PWD\" $HOME $? '    $PWD    '";

	// printf("before : %s\n",str);
	// printf("%d\n",get_nbdollar(str));
	// str = ft_expandall(str);
	// printf("after : %s\n",str);
	while (1)
	{
		str = readline("minishell : ");
		str = ft_expandall(str);
		lexer = init_lexer(str);
		t_token *token;
		while ((token = lexer_next_token(lexer)))
			printf("TOKEN(%d,%s)\n",token->e_type,token->value);
	}

	// str = getenv("_");
	printf("%s\n",str);
	// return 0;
}