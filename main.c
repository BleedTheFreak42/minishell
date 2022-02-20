#include "minishell.h"

char *ft_expand(char *str)
{
	int i;
	int j;

	char *result[3];
	char *from;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i >= 1)
	{
		printf("%d\n",i);
		result[0] = MALLOC(sizeof(char) * i);
		ft_strlcpy(result[0],str,i + 1);
	}
	else
		result[0] = ft_strdup("");
	if (str[i++] == '$')
	{
		j = i;
		while (str[i] && str[i] != 32 && str[i] != '\"' && str[i] != 39)
			i++;
		from = ft_substr(&str[j],0,i - j);
		result[1] = ft_strdup(getenv(from));
		if (!result[1])
			return (str);
		result[2] = ft_strdup(&str[i]);
	}
	if (result[0] && result[1] && result[2])
	{
		from = ft_strjoin(ft_strjoin(result[0],result[1]),result[2]);
		return (from);
	}
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

int ft_check_syntax(char *str)
{
	unsigned int i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] != 34)
				return (-1);
		}
		if(str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] != 39)
				return (-1);	
		}
		i++;
	}
	return (0);
}

int main(int argc, char const *argv[])
{
	(void)  argc;
	(void)  argv;

	char *str;
	t_lexer *lexer;
	t_token *token;

	while (1)
	{
		str = readline("minishell : ");
		if (str && !ft_check_syntax(str))
		{
			str = ft_expandall(str);
			lexer = init_lexer(str);
			while ((token = lexer_next_token(lexer)))
				printf("TOKEN(%d,%s)\n",token->e_type,token->value);
		}
		else
			printf("Error\n");
		xflush();
	}
}