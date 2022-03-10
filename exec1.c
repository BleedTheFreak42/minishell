/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 06:00:28 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 06:00:53 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_handler(t_list *cmd, t_pipe *p)
{
	while (cmd)
	{
		p->cmd = get_cmd_args(((t_command *)cmd->content)->args);
		p->files = ((t_command *)cmd->content)->file;
		if (cmd->next != NULL && !pipe(p->fds))
			p->outfd = p->fds[1];
		else
		{
			p->fds[0] = 0;
			p->outfd = 1;
		}
		handle_files(p->files, &p->infd, &p->outfd);
		if (!check_builtin(p->cmd[0]))
			p->pids[p->i++] = execute_cmd(p->cmd, p, 0);
		else
			execute_builtin_parent(p->cmd, p);
		if (p->outfd != 1)
			close(p->outfd);
		if (p->infd != 0)
			close(p->infd);
		p->infd = p->fds[0];
		cmd = cmd->next;
	}
	return (0);
}

int	execute(t_list *cmd)
{
	t_pipe	p;

	g_cmd.is_forked = 1;
	bzero(&p, sizeof(t_pipe));
	p.pids = (pid_t *)xmalloc(sizeof(pid_t) * list_size(cmd) + 1);
	if (pipe_handler(cmd, &p) == -1)
		return (-1);
	while (p.j < p.i)
	{
		if (p.pids[p.j] == -1)
			printf("minishell: fork: Resource temporarily unavailable");
		waitpid(p.pids[p.j++], &p.status, 0);
		if (WTERMSIG(p.status) == SIGQUIT)
			write(2, "Quit : 3\n", 9);
	}
	if (g_cmd.is_forked == 1)
		g_cmd.exit_code = WEXITSTATUS(p.status);
	g_cmd.is_forked = 0;
	return (0);
}
