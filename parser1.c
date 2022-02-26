/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:07:30 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 14:09:00 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checkline(char **line)
{
	if (!*line)
	{
		printf("exit\n");
		exit(0);
	}
}

void	ft_printenv(void)
{
	int	i;

	i = 0;
	while (g_cmd.env_p[i])
		printf("%s\n", g_cmd.env_p[i++]);
}

void	ft_free_env(char ***env_p)
{
	int	i;

	i = 0;
	while (*env_p[i])
		free(*env_p[i++]);
	free(*env_p);
}

void	ft_export(char *parm)
{
	unsigned int	i;
	char			**ret;

	ret = NULL;
	g_cmd.env_len++;
	ret = (char **) malloc(sizeof(char *) * (g_cmd.env_len + 2));
	i = 0;
	while (g_cmd.env_p[i])
	{
		ret[i] = ft_strdup(g_cmd.env_p[i], 0);
		i++;
	}
	ret[i] = ft_strdup(parm, 0);
	ret[++i] = NULL;
	free(g_cmd.env_p);
	g_cmd.env_p = ret;
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
				return (ft_strdup("", 0));
			else if (j == ft_strlen(var))
				return (ret + 1);
		}
		i++;
	}
	return (ft_strdup("", 0));
}
