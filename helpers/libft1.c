/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 10:09:15 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:24 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(const char *s1, int f)
{
	int		len;
	char	*ret;

	len = 0;
	ret = NULL;
	if (s1)
	{
		while (s1[len])
			len++;
		if (f)
			ret = xmalloc(sizeof(char) * (len + 1));
		else
			ret = malloc(sizeof(char) * (len + 1));
		if (ret)
			ft_strcpy(ret, s1);
	}
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;

	i = 0;
	if (!(s1) || !(s2))
		return (NULL);
	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup("\0", 1));
	string = (char *)
		xmalloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (string)
	{
		while (*s1)
			string[i++] = *(s1++);
		while (*s2)
			string[i++] = *(s2++);
		string[i] = '\0';
	}
	return (string);
}

char	*ft_strchrq(const char *s, int c)
{
	g_cmd.q.s_q = 0;
	g_cmd.q.d_q = 0;
	while (s && *s)
	{
		if (*s == 39 && !g_cmd.q.s_q)
			g_cmd.q.s_q = 1;
		else if (*s == 39 && g_cmd.q.s_q)
			g_cmd.q.s_q = 0;
		else if (*s == 34)
		{
			s++;
			g_cmd.q.d_q = 1;
		}
		else if (*s == 34 && g_cmd.q.d_q)
			g_cmd.q.d_q = 0;
		if (*s == (char)c && !g_cmd.q.s_q)
			return ((char *) s);
		if (*s)
			s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}
