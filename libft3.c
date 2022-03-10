/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:09:15 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 00:17:40 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_def(char c)
{
	return (c != 32 && c != 34 && c != 39 && c != '|');
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", 1));
	else if (len >= ft_strlen(s) - start)
		substring = (char *) xmalloc(sizeof(char) * ft_strlen(s) - start + 1);
	else
		substring = (char *) xmalloc(sizeof(char) * len + 1);
	if (!substring)
		return (0);
	i = 0;
	while (s[i] && i < len && start < ft_strlen(s))
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = 0;
	return (substring);
}
