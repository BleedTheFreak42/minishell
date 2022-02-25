/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:06:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/25 06:31:31 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int ft_strlen(const char *str)
{
	int i;

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
			|| (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'));
}

char* ft_strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + ft_strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

void	*ft_memcpy(void *dst, const void * src, size_t n)
{
	const unsigned char	*ptrsrc;
	unsigned char		*ptrdest;
	size_t				i;

	if (!dst && !src)
		return (0);
	ptrsrc = src;
	ptrdest = dst;
	if (!(*ptrdest) && !(*ptrsrc))
		return ("");
	i = 0;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}

void *ft_realloc(void *ptr,size_t size)
{
	void *result;
	
		result = MALLOC(size);
	if (!result)
		return (NULL);
	ft_memcpy(result,ptr,sizeof(char) * ft_strlen((char *) ptr));
	// free(ptr);
	return (result);
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
		substring = (char *) MALLOC(sizeof(char) * ft_strlen(s) - start + 1);
	else
		substring = (char *) MALLOC(sizeof(char) * len + 1);
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

char	*ft_strdup(const char *s1, int f)
{
	int		len;
	int		i;
	char	*ret;

	len = 0;
	ret = NULL;
	if (s1)
	{
		while (s1[len])
			len++;
		if (f)
			ret = MALLOC(sizeof(char) * (len + 1));
		else
			ret = malloc(sizeof(char) * (len + 1));
		if (ret)
		{
			i = 0;
			while (s1[i])
			{
				ret[i] = s1[i];
				i++;
			}
			ret[i] = '\0';
		}
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
		MALLOC(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
	// int i;

	if(s)
	{
	    g_cmd.q.s_q = 0;
		while (*s)
		{
			if (*s == 39 && !g_cmd.q.s_q)
				g_cmd.q.s_q = 1;
			else if (*s == 39 && g_cmd.q.s_q)
				g_cmd.q.s_q = 0;
			else if (*s == 34)
            {
				s++;
                g_cmd.q.d_q = 0;
            }
            else if (*s == 34 && !g_cmd.q.d_q)
                g_cmd.q.d_q = 1;
			if (*s == (char)c && !g_cmd.q.s_q)
				return ((char *) s);
			s++;
		}
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}

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

// int	ft_isalnum(int c)
// {
// 	return (((c >= 'a' && c <= 'z')
// 			|| (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'));
// }

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '-');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_sepspesial(int c)
{
	return (!ft_isalnum(c) && !ft_isdigit(c) && c != '_' && c != 39 && c != 34);
}