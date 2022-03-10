/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:47:57 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 08:48:44 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(char **cmds, t_pipe *p, int echo)
{
	int	pid;

	pid = 0;
	if (cmds[0])
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(p->infd, 0);
			dup2(p->outfd, 1);
			if (p->fds[0] != 0)
				close(p->fds[0]);
			if (p->infd != 0)
				close(p->infd);
			if (p->outfd != 1)
				close(p->outfd);
			if (echo)
				ft_echo(cmds);
			else
				exec(cmds, g_cmd.env_p);
		}
	}
	return (pid);
}

char	**get_cmd_args(t_list *cmd)
{
	int		j;
	char	**ret;
	t_list	*cur;

	ret = (char **)xmalloc(sizeof(char *) * (list_size(cmd) + 1));
	cur = cmd;
	j = 0;
	while (cur)
	{
		ret[j] = ft_strdup((char *)cur->content, 1);
		j++;
		cur = cur->next;
	}
	ret[j] = NULL;
	return (ret);
}

int	check_builtin(char *name)
{
	if (ft_comp(name, "echo") && ft_strlen(name) == 4)
		return (1);
	else if (ft_comp(name, "cd") && ft_strlen(name) == 2)
		return (2);
	else if (ft_comp(name, "pwd") && ft_strlen(name) == 3)
		return (3);
	else if (ft_comp(name, "env") && ft_strlen(name) == 3)
		return (4);
	else if (ft_comp(name, "export") && ft_strlen(name) == 6)
		return (5);
	else if (ft_comp(name, "unset") && ft_strlen(name) == 5)
		return (6);
	else if (ft_comp(name, "exit") && ft_strlen(name) == 4)
		return (7);
	else
		return (0);
}

void	exec_echo(char **cmds, t_pipe *p)
{
	p->pids[p->i++] = execute_cmd(cmds, p, 1);
	if (p->infd != 0)
		close(p->infd);
	if (p->outfd != 1)
		close(p->outfd);
}

int	execute_builtin_parent(char **cmds, t_pipe *p)
{
	int	i[2];

	i[0] = check_builtin(cmds[0]);
	i[1] = 0;
	if (i[0] > 1)
		g_cmd.is_forked = 2;
	if (i[0] == 1)
		exec_echo(cmds, p);
	else if (i[0] == 2)
		i[1] = ft_cd(cmds, p->outfd);
	else if (i[0] == 3)
		ft_pwd(p->outfd);
	else if (i[0] == 4)
		i[1] = ft_printenv(p->outfd, 0);
	else if (i[0] == 5)
		i[1] = ft_export(cmds[1], p->outfd);
	else if (i[0] == 6)
		i[1] = ft_unset(cmds[1]);
	else if (i[0] == 7)
		ft_exit(cmds, p->outfd);
	if (i[0] > 1)
		g_cmd.is_forked = 0;
	return ((i[1] > 0 || i[1] < 0));
}
