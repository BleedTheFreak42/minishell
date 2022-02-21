/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:05:40 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/21 09:12:39 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *init_command(t_token *token)
{
	if (token->e_type == 1)
		;
	else if(token->e_type == 2)
		;
	else if(token->e_type == 3)
		;
	else if(token->e_type == 4)
		;	
	else if(token->e_type == 5)
		;
	return (NULL);
}