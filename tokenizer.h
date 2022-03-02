/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:06:32 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/02 16:48:01 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct s_token
{
	enum
	{
		TOKEN_PIPE,
		TOKEN_GTHAN,
		TOKEN_LTHAN,
		TOKEN_LHEREDOC,
		TOKEN_RHEREDOC,
		TOKEN_WORD
	}e_type;
	char *value;
}t_token;

#endif

