/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:34:40 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*lexer_parse_string(t_lexer *lexer)
{
	char	*str;

	str = xmalloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
