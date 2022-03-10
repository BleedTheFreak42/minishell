/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:32:27 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *value, char *f(t_lexer *), t_lexer *lexter)
{
	char	*value1;

	value1 = f(lexter);
	if (value1)
		value = ft_strjoin(value, value1);
	return (value);
}

t_token	*lexer_collect_word(t_lexer *lexer)
{
	char	*value;
	char	*s;

	lexer_skip_space(lexer);
	value = xmalloc(sizeof(char) * 1);
	if (!value)
		p_malloc();
	value[0] = '\0';
	while (ft_isprint(lexer->c) && lexer->c != 32
		&& lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
	{
		if (lexer->c == 34)
			value = get_value(value, lexer_collect_dquoted, lexer);
		else if (lexer->c == 39)
			value = get_value(value, lexer_collect_squoted, lexer);
		else
		{
			s = lexer_parse_string(lexer);
			value = ft_strjoin(value, s);
			lexer_to_next(lexer);
		}
	}
	return (init_token(TOKEN_WORD, value));
}

char	*lexer_collect_dquoted(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = xmalloc(sizeof(char) * 1);
	value[0] = '\0';
	lexer_to_next(lexer);
	while (ft_isprint(lexer->c) && lexer->c != 34)
	{
		s = lexer_parse_string(lexer);
		value = ft_strjoin(value, s);
		lexer_to_next(lexer);
	}
	if (lexer->c != 34)
		return (NULL);
	else
		lexer_to_next(lexer);
	return (value);
}

char	*lexer_collect_squoted(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = ft_strdup("", 1);
	lexer_to_next(lexer);
	while (ft_isprint(lexer->c) && lexer->c != 39)
	{
		s = lexer_parse_string(lexer);
		value = ft_strjoin(value, s);
		lexer_to_next(lexer);
	}
	if (lexer->c != 39)
		return (NULL);
	else
		lexer_to_next(lexer);
	return (value);
}

t_token	*lexer_get_token(t_lexer *lexer, t_token *token)
{
	lexer_to_next(lexer);
	return (token);
}
