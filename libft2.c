/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:29:29 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/27 09:15:02 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (haystack == needle || (len == 0 && *needle == '\0'))
		return ((char *) haystack);
	while (haystack[i] && i < len && haystack[i] != '=')
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& haystack[i + j] == needle[j] && (i + j) < len)
			j++;
		if (!needle[j])
			return ((char *) &haystack[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	if (s)
	{
		while (*s)
		{
			if (*s == (char)c)
				return ((char *) s);
			s++;
		}
		if (c == '\0')
			return ((char *) s);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_' || c == '-');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_sepspesial(int c)
{
	return (!ft_isalnum(c) && !ft_isdigit(c) && c != '_'
		&& c != 39 && c != 34 && c != '?');
}
