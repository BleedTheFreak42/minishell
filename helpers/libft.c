/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:06:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 09:33:06 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int	ft_isalnum(int c)
{
	return (((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		|| (c >= '0' && c <= '9') || c == '_' || c == '?');
}

int	ft_isalnum0(int c)
{
	return (((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'));
}
