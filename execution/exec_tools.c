/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:50:27 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getpath(char **cmd, char **envp)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	while (path && ft_strnchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strnchr(path, ':'));
		if (dir && cmd[0])
			bin = join_path(dir, cmd[0]);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strnchr(path, ':') + 1;
	}
	return (cmd[0]);
}

void	exec(char **cmd, char **envp)
{
	char	*path;

	(void)envp;
	if (ft_strnchr(cmd[0], '/') > -1)
		path = cmd[0];
	else if (*cmd[0])
		path = getpath(cmd, g_cmd.env_p);
	else
		path = cmd[0];
	execve(path, cmd, g_cmd.env_p);
	if (path)
	{
		write(STDERR, "minishell: ", 12);
		write(STDERR, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR, " ", 1);
		write(STDERR, path, ft_strnchr(path, '\0'));
		write(STDERR, "\n", 1);
	}
	exit(127);
}

void	read_input(int infd, char *esc)
{
	int		r;
	char	*buf;

	r = 42;
	buf = malloc(1025);
	g_cmd.in_herdoc = 1;
	while (r && g_cmd.in_herdoc)
	{
		write(1, "> ", 3);
		r = read(0, buf, 1024);
		if (r < 0)
			break ;
		buf[r] = '\0';
		if (((ft_strncmp(buf, esc, ft_strnchr(esc, '\0')) == 0)
				&& (ft_strnchr(esc, '\0') == ft_strnchr(buf, '\0') - 1))
			|| !g_cmd.in_herdoc)
			break ;
		if (ft_strnchr(buf, '\n') != -1 && *buf)
			write(infd, buf, ft_strnchr(buf, '\n') + 1);
	}
	g_cmd.in_herdoc = 0;
	free(buf);
}

int	here_doc(char *path, char *esc)
{
	int		infd;

	infd = open(path, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (infd < 0)
		return (-1);
	read_input(infd, esc);
	close(infd);
	return (open(path, O_RDONLY));
}

int	ft_strnchr(char *str, char c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
