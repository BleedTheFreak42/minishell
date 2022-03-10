/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:41:28 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 05:57:40 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getname(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] && s[i] != '=')
			i++;
	}
	return (i);
}

int	ft_cpyto(char *s, char **name)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == '=')
				break ;
			(*name)[i] = s[i];
			i++;
		}
		(*name)[i] = '\0';
	}
	return (i);
}

char	**get_name_value(char *s)
{
	int		i;
	char	*name;
	char	*value;
	char	**ret;

	ret = NULL;
	if (s)
	{
		i = ft_getname(s);
		if (s[i] == '\0')
			return (NULL);
		name = malloc(sizeof(char) * (i + 1));
		i = ft_cpyto(s, &name);
		value = malloc(sizeof(char) * (ft_strlen(&s[++i]) + 1));
		ft_strcpy(value, &s[i]);
		ret = malloc(sizeof(char *) * 2);
		ret[0] = name;
		ret[1] = value;
	}
	return (ret);
}
