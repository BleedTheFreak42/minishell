/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:57:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 09:33:49 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '-' && s[i] != '+' && !(s[i] <= '9' && s[i] >= '0'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **cmds, int fd)
{
	int	i;

	i = 0;
	(void)fd;
	while (cmds[i])
	{
		i++;
		if (cmds[i] && check_arg(cmds[i]))
		{
			write(2, "exit\n", 6);
			write(2, "minishell : exit: numeric argument required\n", 45);
			xflush();
			exit(255);
		}
	}
	if (i > 2)
	{
		write(2, "exit\n", 6);
		write(2, "minishell : exit: too many arguments\n", 38);
		return (1);
	}
	write(2, "exit\n", 6);
	exit((unsigned char) ft_atoi(cmds[1]));
}

static int	check_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_set(int *a, int *b, int *c)
{
	*a = 1;
	*b = 0;
	*c = 1;
}

void	iko(char **args, int i, int *flag)
{
	while (args[++i])
	{
		flag[0] = 1;
		if (ft_comp(args[i], "-n") && !flag[3] && !flag[2])
		{
			flag[3] = check_flag((args[i]) + 2);
			if (flag[3])
			{
				if (!flag[4])
					flag[1] = 0;
				flag[0] = 1;
			}
			else
				ft_set(&flag[1], &flag[0], &flag[4]);
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
