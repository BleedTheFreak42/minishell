/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:10:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/27 10:40:46 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *str)
{
	int		i;
	int		j;
	char	*result[3];

	i = get_dollar_index(str);
	result[0] = ft_exapnd_if1(i, str);
	if (str[i++] == '$')
	{
		if (str[i] == '\0')
			result[1] = ft_strdup("$", 1);
		else if (ft_isdigit(str[i]))
		{
			j = i + 1;
			result[1] = ft_expand_else1(&i, str, j);
		}
		else
		{
			j = i;
			result[1] = ft_expand_else2(&i, str, j);
		}
		result[2] = ft_strdup(&str[i], 1);
	}
	if (result[0] && result[1] && result[2])
		return (ft_expand_else3(result[0], result[1], result[2]));
	return (NULL);
}
