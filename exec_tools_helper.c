// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_tools_helper.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/10 01:17:49 by ytaya             #+#    #+#             */
// /*   Updated: 2022/03/10 06:06:44 by ytaya            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// char	*join_path(char *path, char *bin)
// {
// 	char	*ret;
// 	int		i;
// 	int		j;

// 	ret = xmalloc(sizeof(char)
// 			*(ft_strnchr(path, 0) + ft_strnchr(bin, 0) + 2));
// 	if (!ret)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (path[j])
// 		ret[i++] = path[j++];
// 	ret[i++] = '/';
// 	j = 0;
// 	while (bin[j])
// 		ret[i++] = bin[j++];
// 	ret[i] = 0;
// 	return (ret);
// }

// int	ft_strncmp(char *s1, char *s2, int n)
// {
// 	while (--n > 0 && *s1 && *s2 && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return (*s2 - *s1);
// }

// // char	**ft_split(char *s, char sep)
// // {
// // 	char	**ret;
// // 	int		words;
// // 	int		i;
// // 	int		j;

// // 	words = 0;
// // 	j = 0;
// // 	while (s[j])
// // 		if (s[j++] == sep)
// // 			words++;
// // 	ret = xmalloc(sizeof(char *) * (words + 2));
// // 	ret[words + 1] = NULL;
// // 	i = 0;
// // 	while (i < words + 1)
// // 	{
// // 		j = 0;
// // 		while (s[j] && s[j] != sep)
// // 			j++;
// // 		ret[i++] = ft_strndup(s, j);
// // 		s = s + j + 1;
// // 	}
// // 	return (ret);
// // }

// // int	ft_strnchr(char *str, char c)
// // {
// // 	int	i;

// // 	i = 0;
// // 	if (str)
// // 	{
// // 		while (str[i] && str[i] != c)
// // 			i++;
// // 		if (str[i] == c)
// // 			return (i);
// // 	}
// // 	return (-1);
// // }

// // char	*ft_strndup(char *s, unsigned int n)
// // {
// // 	char				*ret;
// // 	unsigned int		i;

// // 	i = 0;
// // 	ret = xmalloc(sizeof(char) * (n + 1));
// // 	while (i < n)
// // 		ret[i++] = *s++;
// // 	ret[n] = 0;
// // 	return (ret);
// // }
