/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:50:00 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_comp(char *str, char *f)
{
	if (str && f)
	{
		while (*str && *f)
		{
			if (*str != *f)
				return (0);
			str++;
			f++;
		}
		if (*f == '\0')
			return (1);
	}
	return (0);
}

int	check_export_input(char *s)
{
	if (s && ft_isalpha(*s))
	{
		while (*s)
		{
			if (!ft_isalnum(*s))
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

char	*ft_getenv(char **envp, char *var)
{
	int				i;
	char			*ret;
	unsigned int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			while (envp[i][j] && envp[i][j] != '=')
				j++;
			ret = ft_strchr(envp[i], '=');
			if (!ret)
				return (ft_strdup("", 1));
			else if (j == ft_strlen(var))
				return (ret + 1);
		}
		i++;
	}
	return (ft_strdup("", 1));
}
