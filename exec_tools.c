/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 02:50:27 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/03/09 02:28:19 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (ft_strnchr(cmd[0], '/') > -1)
		path = cmd[0];
	else if (*cmd[0])
		path = getpath(cmd, envp);
	else
		path = cmd[0];
	execve(path, cmd, envp);
	if (path)
	{
		write(STDERR, "minishell: ", 12);
		write(STDERR, "command not found: ", 19);
		write(STDERR, path, ft_strnchr(path, '\0'));
		write(STDERR, "\n", 1);
	}
	exit(127);
}

int	here_doc(char *path, char *esc)
{
	int		infd;
	char	*buf;
	int		r;

	r = 42;
	buf = malloc(1025);
	infd = open(path, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (infd < 0)
		return (-1);
	g_cmd.in_herdoc = infd;
	while (r && g_cmd.in_herdoc)
	{
		write(1, "> ", 3);
		if (g_cmd.in_herdoc == infd)
			r = read(0, buf, 1024);
		buf[r] = '\0';
		if (((ft_strncmp(buf, esc, ft_strnchr(esc, '\0')) == 0)
			&& (ft_strnchr(esc, '\0') == ft_strnchr(buf, '\0') - 1)) || !g_cmd.in_herdoc)
			break ;
		if (ft_strnchr(buf, '\n') != -1 && *buf)
			write(infd, buf, ft_strnchr(buf, '\n') + 1);
	}
	close(infd);
	g_cmd.in_herdoc = 0;
	free(buf);
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

char	*ft_strndup(char *s, unsigned int n)
{
	char				*ret;
	unsigned int		i;

	i = 0;
	ret = malloc(sizeof(char) * (n + 1));
	while (i < n)
		ret[i++] = *s++;
	ret[n] = 0;
	return (ret);
}

char	*join_path(char *path, char *bin)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char)
			*(ft_strnchr(path, 0) + ft_strnchr(bin, 0) + 2));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (path[j])
		ret[i++] = path[j++];
	ret[i++] = '/';
	j = 0;
	while (bin[j])
		ret[i++] = bin[j++];
	ret[i] = 0;
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	while (--n > 0 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 - *s1);
}

char	**ft_split(char *s, char sep)
{
	char	**ret;
	int		words;
	int		i;
	int		j;

	words = 0;
	j = 0;
	while (s[j])
		if (s[j++] == sep)
			words++;
	ret = malloc(sizeof(char *) * (words + 2));
	ret[words + 1] = NULL;
	i = 0;
	while (i < words + 1)
	{
		j = 0;
		while (s[j] && s[j] != sep)
			j++;
		ret[i++] = ft_strndup(s, j);
		s = s + j + 1;
	}
	return (ret);
}
