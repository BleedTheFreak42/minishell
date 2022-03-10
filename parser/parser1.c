/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:07:30 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_checkline(char **line)
{
	if (!*line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

int	ft_printenv(int fd, int flag)
{
	int	i;

	i = 0;
	while (g_cmd.env_p[i])
	{
		if (flag)
			(write(fd, "declare -x ", 12))
				&& write(fd, g_cmd.env_p[i], ft_strlen(g_cmd.env_p[i]));
		else
			write(fd, g_cmd.env_p[i], ft_strlen(g_cmd.env_p[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}

void	ft_free_env(char ***env_p)
{
	size_t	i;

	i = 0;
	while (env_p[0][i])
	{
		if (env_p[0][i])
			free(env_p[0][i]);
		i++;
	}
	free(env_p[0]);
}
