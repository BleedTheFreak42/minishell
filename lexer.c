#include "minishell.h"

t_lexer *init_lexer(char *content)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->index = 0;
	lexer->c = lexer->content[lexer->index];
	return (lexer);
}

void lexer_to_next(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		lexer->index++;
		lexer->c = lexer->content[lexer->index];
	}
}

void lexer_skip_space(t_lexer *lexer)
{
	while (lexer->c == 32)
		lexer_to_next(lexer);
}

t_token *lexer_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		if (lexer->c == 32)
			lexer_skip_space(lexer);
		if (lexer->c == '|')
			return (lexer_get_token(lexer,init_token(TOKEN_PIPE,lexer_parse_string(lexer))));
		if (lexer->c == '<')
			return(lexer_collect_redirection(lexer,0));
			// return (lexer_get_token(lexer,init_token(TOKEN_LTEHN,lexer_parse_string(lexer))));
		if (lexer->c == '>')
			return(lexer_collect_redirection(lexer,1));
		// 	return (lexer_get_token(lexer,init_token(TOKEN_GTEHN,lexer_parse_string(lexer))));
		// if (ft_isprint(lexer->c))
			return (lexer_collect_word(lexer));
	}
	return (NULL);
}

t_token *lexer_collect_redirection(t_lexer *lexer, int type)
{
	char* value;
	char* s;

	value = malloc(sizeof(char) * 1);
    value[0] = '\0';
	while (lexer->c != 32 && !ft_isalnum(lexer->c) && lexer->c)
	{
		s = lexer_parse_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		lexer_to_next(lexer);
	}
	if (ft_strlen(value) > 2)
		return (NULL);
	if (!type && ft_strlen(value) == 1)
		return (init_token(TOKEN_LTEHN,value));
	else if (!type && ft_strlen(value) > 1)
		return (init_token(TOKEN_LHEREDOC,value));
	else if (type && ft_strlen(value) == 1)
		return (init_token(TOKEN_GTEHN,value));
	else if (type && ft_strlen(value) > 1)
		return (init_token(TOKEN_RHEREDOC,value));
	else
		return (NULL);
}

t_token *lexer_collect_word(t_lexer *lexer)
{
	char* value;
	char* value1;
	char* s;

	lexer_skip_space(lexer);
	value = malloc(sizeof(char) * 1);
    value[0] = '\0';
	while (ft_isprint(lexer->c) && lexer->c != 32 && lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
	{
		if (lexer->c == 34)
		{
			value1 = lexer_collect_dquoted(lexer);
			if (value1)
        		ft_strcat(value, value1);
			else
			{
				printf("syntax Error\n");
				return (NULL);
			}
		}
		else if (lexer->c == 39)
		{
			value1 = lexer_collect_squoted(lexer);
			if (value1)
        		ft_strcat(value, value1);
			else
			{
				printf("syntax Error\n");
				return (NULL);
			}
		}
		else
		{
			s = lexer_parse_string(lexer);
			value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
			ft_strcat(value, s);
			lexer_to_next(lexer);
		}
	}
	return (init_token(TOKEN_WORD,value));
}

char *lexer_collect_dquoted(t_lexer *lexer)
{
	char* value;
	char* s;

	value = malloc(sizeof(char) * 1);
    value[0] = '\0';
	lexer_to_next(lexer);	
	while (ft_isprint(lexer->c) && lexer->c != 34)
	{
		s = lexer_parse_string(lexer);
        value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
        ft_strcat(value, s);
        lexer_to_next(lexer);
	}
	if (lexer->c != 34 )
		return (NULL);
	else
		lexer_to_next(lexer);
	return (value);
}

char *lexer_collect_squoted(t_lexer *lexer)
{
	char* value;
	char* s;

	value = malloc(sizeof(char) * 1);
    value[0] = '\0';
	lexer_to_next(lexer);	
	while (ft_isprint(lexer->c) && lexer->c != 39)
	{
		s = lexer_parse_string(lexer);
        value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
        ft_strcat(value, s);
        lexer_to_next(lexer);
	}
	if (lexer->c != 39)
		return (NULL);
	else
		lexer_to_next(lexer);
	return (value);
}

t_token *lexer_get_token(t_lexer *lexer,t_token *token)
{
	lexer_to_next(lexer);
	return (token);
}

char *lexer_parse_string(t_lexer *lexer)
{
	char *str;

	str = malloc(2 * sizeof(char));
	str[0] = lexer->c; 
	str[1] = '\0'; 
	return (str);
}