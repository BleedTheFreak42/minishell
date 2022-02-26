/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 09:41:31 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 13:21:34 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = xmalloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->index = 0;
	lexer->c = lexer->content[lexer->index];
	return (lexer);
}

void	lexer_to_next(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		lexer->index++;
		lexer->c = lexer->content[lexer->index];
	}
}

void	lexer_skip_space(t_lexer *lexer)
{
	while (lexer->c == 32)
		lexer_to_next(lexer);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->index < ft_strlen(lexer->content))
	{
		if (lexer->c == 32)
			lexer_skip_space(lexer);
		if (lexer->c == '|')
			return (lexer_get_token(lexer,
					init_token(TOKEN_PIPE, lexer_parse_string(lexer))));
		if (lexer->c == '<')
			return (lexer_collect_redirection(lexer, 0));
		if (lexer->c == '>')
			return (lexer_collect_redirection(lexer, 1));
		if (ft_isprint(lexer->c))
			return (lexer_collect_word(lexer));
	}
	return (NULL);
}

t_token	*lexer_collect_redirection(t_lexer *lexer, int type)
{
	char	*value;
	char	*s;

	value = xmalloc(sizeof(char) * 1);
	value[0] = '\0';
	while (lexer->c != 32 && !ft_isalnum(lexer->c) && lexer->c)
	{
		s = lexer_parse_string(lexer);
		value = ft_strjoin(value, s);
		lexer_to_next(lexer);
	}
	if (ft_strlen(value) <= 2)
	{
		if (!type && ft_strlen(value) == 1)
			return (init_token(TOKEN_LTEHN, value));
		else if (!type && ft_strlen(value) > 1)
			return (init_token(TOKEN_LHEREDOC, value));
		else if (type && ft_strlen(value) == 1)
			return (init_token(TOKEN_GTEHN, value));
		else if (type && ft_strlen(value) > 1)
			return (init_token(TOKEN_RHEREDOC, value));
	}
	return (NULL);
}
