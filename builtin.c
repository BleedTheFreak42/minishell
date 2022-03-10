/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:57:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 12:11:30 by ael-ghem         ###   ########.fr       */
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
	//xflush();
    system("leaks minishell");
	exit(r);
}

int	ft_echoif1(char c, int *flag3)
{
	if (c != 'n')
	{
		*flag3 = 1;
		return (1);
	}
	else
		return (0);
}

void	iko(char **args, int i, int j, int *flag)
{
	while (args[++i])
	{
		flag[0] = 1;
		if (ft_comp(args[i], "-n") && !flag[2] && !flag[3])
		{
			flag[0] = 0;
			flag[1] = 1;
			j = 1;
			while (args[i][j])
				if (ft_echoif1(args[i][j++], &flag[3]))
					break ;
			if (flag[3])
				flag[0] = 1;
			if (!flag[1] && !flag[3])
				flag[1] = 0;
		}
		if (flag[0] || flag[2])
		{
			if (flag[2] == 1)
				write(1, " ", 1);
			write(1, args[i], ft_strlen(args[i]));
			flag[2] = 1;
		}
	}
}

void	ft_echo(char **args)
{
	int	flag[4];
	int	i;
	int	j;

	i = 0;
	j = 0;
	bzero(&flag, sizeof(int) * 4);
	iko(args, i, j, flag);
	if (flag[1] == 0)
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
