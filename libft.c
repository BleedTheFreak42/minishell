/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:06:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 10:30:10 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			|| (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'));
}

// char	*ft_strcat(char *destination, const char *source)
// {
// 	char* ptr = destination + ft_strlen(destination);

//     while (*source != '\0') {
//         *ptr++ = *source++;
//     }
//     *ptr = '\0';
//     return destination;
// }

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

// void	*ft_realloc(void *ptr,size_t size)
// {
// 	void *result;
// 		result = xmalloc(size);
// 	if (!result)
// 		return (NULL);
// 	ft_memcpy(result,ptr,sizeof(char) * ft_strlen((char *) ptr));
// 	return (result);
// }

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
