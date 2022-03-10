/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:06:10 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 09:49:51 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "tokenizer.h"

typedef struct s_lexer
{
	char			c;
	unsigned int	index;
	char			*content;
}t_lexer;

t_lexer	*init_lexer(char *content);
void	lexer_to_next(t_lexer *lexer);
void	lexer_skip_space(t_lexer *lexer);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*lexer_collect_word(t_lexer *lexer);
char	*lexer_collect_dquoted(t_lexer *lexer);
char	*lexer_collect_squoted(t_lexer *lexer);
char	*lexer_parse_string(t_lexer *lexer);
t_token	*lexer_get_token(t_lexer *lexer, t_token *token);
t_token	*lexer_collect_redirection(t_lexer *lexer, int type);
#endif