/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:44:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 15:25:41 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export_one(char *param, int fd)
{
	char			**ret;

	ret = NULL;
	if (ft_export_check_params(param, fd))
		return (1);
	if (check_env(param))
	{
		ret = get_name_value(param);
		(ft_unset_one(ret[0]) || 1) && (g_cmd.env_len-- || 1);
		ft_export_one(param, fd);
	}
	else
		ft_export_helper(param);
	return (1);
}

void	ft_echo(char **args)
{
	int	flag[5];
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_bzero(&flag, sizeof(int) * 5);
	iko(args, i, flag);
	if (!flag[1])
		write(1, "\n", 1);
	exit(0);
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		write(fd, pwd, ft_strlen(pwd));
		write(fd, "\n", 1);
	}
	else
	{
		perror("minishell : ");
		return (1);
	}
	if (pwd != NULL)
		free(pwd);
	return (0);
}

int	ft_export(char **names, int fd)
{
	int	i;

	i = 1;
	if (len_env(names) == 1)
	{
		ft_printenv(fd, 1);
		return (0);
	}
	while (names && names[i])
	{
		if (ft_export_one(names[i], fd) == 1)
			return (1);
		i++;
	}
	return (0);
}
