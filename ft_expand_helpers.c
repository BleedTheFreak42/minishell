/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:35:41 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/09 23:39:30 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_else1(int *i, char *str, int j)
{
	char	*ret;

	while (str[*i] && str[*i] != 32 && str[*i] != '\"' && str[*i] != 39)
		(*i)++;
	ret = ft_substr(&str[j], 0, *i - j);
	return (ret);
}

char	*ft_expand_else2(int *i, char *str, int j)
{
	char	*from;
	char	*ret;

	while (str[*i] && str[*i] != 32 && str[*i] != '\"'
		&& str[*i] != 39 && ft_isalnum(str[*i]))
		(*i)++;
	from = ft_substr(&str[j], 0, *i - j);
	ret = ft_getenv(g_cmd.env_p, from);
	if (ft_sepspesial(str[*i - ft_strlen(from)]))
		ret = ft_strjoin("$", from);
	return (ret);
}

char	*ft_expand_else3(char *s1, char *s2, char *s3)
{
	return (ft_strjoin(ft_strjoin(s1, s2), s3));
}

int	get_dollar_index(char *str)
{
	int	i;

	i = 0;
	g_cmd.q.s_q = 0;
	g_cmd.q.d_q = 0;
	while (str[i])
	{
		if (str[i] == 34 && !g_cmd.q.d_q)
			g_cmd.q.d_q = 1;
		else if (str[i] == 34 && g_cmd.q.d_q)
			g_cmd.q.d_q = 0;
		if (str[i] == 39 && !g_cmd.q.s_q)
			g_cmd.q.s_q = 1;
		else if (str[i] == 39 && g_cmd.q.s_q)
			g_cmd.q.s_q = 0;
		if (str[i] == '$' && !g_cmd.q.s_q)
			break ;
		else if (str[i] == '$' && g_cmd.q.d_q && g_cmd.q.s_q)
			break ;
		i++;
	}
	return (i);
}

char	*ft_exapnd_if1(int i, char *str)
{
	char	*ret;

	if (i >= 1)
	{
		ret = xmalloc(sizeof(char) * (i + 1));
		ft_strlcpy(ret, str, i + 1);
	}
	else
		ret = ft_strdup("", 1);
	return (ret);
}
