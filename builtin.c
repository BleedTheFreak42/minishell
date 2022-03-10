/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:57:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/09 23:35:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmds, int fd)
{
	int	r;
	int	i;

	r = 0;
	i = 0;
	while (cmds[i])
		i++;
	write(fd, "exit\n", 5);
	if (i > 1 && ft_atoi(cmds[1]) != 255)
	{
		write(2, "minishell : exit: too many arguments\n",
			ft_strlen("minishell : exit: too many arguments\n"));
		r = 1;
	}
	else if (i > 1 && ft_atoi(cmds[1]) == 255)
	{
		r = 255;
		write(2, "minishell : exit: numeric argument required\n",
			ft_strlen("minishell : exit: numeric argument required\n"));
	}
	xflush();
	exit(r);
}

void	ft_echo(char **args)
{
	int	flag[3];
	int	i;
	int	j;

	flag[1] = 1;
	flag[2] = 0;
	i = 1;
	while (args[i])
	{
		flag[0] = 1;
		if (ft_comp(args[i], "-n") && flag[2] == 0)
		{
			flag[0] = 0;
			flag[1] = 0;
			j = 1;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
				{
					flag[0] = 1;
					flag[1] = 1;
					break ;
				}
				j++;
			}
			if (!args[i][j])
			{
				flag[0] = 0;
				flag[1] = 0;
			}
		}
		if (flag[0] || flag[2])
		{
			if (flag[2] == 1)
				write(1, " ", 1);
			write(1, args[i], ft_strlen(args[i]));
			flag[2] = 1;
		}
		i++;
	}
	if (flag[1])
		write(1, "\n", 1);
	exit(0);
}

void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	else
		perror("error\n");
	free(pwd);
}

void	ft_cd(char **path, int fd)
{
	int	result;

	if (!path[1])
	{
		if (!ft_strlen(ft_getenv(g_cmd.env_p, "HOME")))
			printf("minishell : cd: HOME not set\n");
		else
		{
			ft_export(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
			chdir(ft_getenv(g_cmd.env_p, "HOME"));
			ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), fd);
		}
		return ;
	}
	result = chdir(path[1]);
	if (access(path[1], F_OK) == 0 && result == -1)
		printf("minishell : cd: %s: Not a directory\n", path[1]);
	else if (result == -1)
		printf("minishell : cd: %s: No such file or directory\n", path[1]);
	else
	{
		ft_export(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
		ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), fd);
	}
}
