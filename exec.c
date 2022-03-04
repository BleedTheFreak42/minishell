/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:47:57 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/04 08:46:19 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t list_size(t_list *list)
{
	t_list *head;
	int     i;

	head = list;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int     execute_cmd(char **cmds, int in, int out, int fds[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		if (fds[0] != 0)
			close(fds[0]);
		if (in != 0)
			close(in);
		if (out != 1)
			close(out);
		exec(cmds, g_cmd.env_p);
	}
	return (pid);
}

int handle_files(t_list *files, int *in, int *out)
{
	t_files	file;

	while (files)
	{
		file.value = ((t_files *)files->content)->value;
		file.e_ftype = ((t_files *)files->content)->e_ftype;
		if (file.e_ftype == TYPE_LTHAN)
		{
			if (access(file.value, F_OK))
			{
				write(STDERR, "Minishell: ", 12);
				write(STDERR, file.value, ft_strnchr(file.value, 0));
				write(STDERR, ": No such file or directory\n", 28);
				return (-1);
			}
			*in = open(file.value, O_RDONLY);
		}
		else if (file.e_ftype == TYPE_GTHAN)
			*out = open(file.value, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		else if (file.e_ftype == TYPE_APPEND)
			*out = open(file.value, O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		else if (file.e_ftype == TYPE_HEREDOC)
			*in = here_doc("/tmp/heredoc420", file.value);
		files = files->next;
	}
	if (*in == -1 || *out == -1)
		return (-1);
	return (0);
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

int	pipe_handler(t_list *cmd, t_pipe *p)
{
	while (cmd)
	{
		p->cmd = get_cmd_args(((t_command *)cmd->content)->args);
		p->files = ((t_command *)cmd->content)->file;
		if (cmd->next != NULL)
		{
			pipe(p->fds);
			p->outfd = p->fds[1];
		}
		else
		{
			p->fds[0] = 0;
			p->outfd = 1;
		}
		if (handle_files(p->files, &p->infd, &p->outfd) == -1)
			return (-1);
		p->pids[p->i++] = execute_cmd(p->cmd, p->infd, p->outfd, p->fds);
		if (p->outfd != 1)
			close(p->outfd);
		if (p->infd != 0)
			close(p->infd);
		p->infd = p->fds[0];
		cmd = cmd->next;
	}
	return (0);
}

int execute(t_list *cmd)
{
	t_pipe	p;
	
	g_cmd.is_forked = 1;
	bzero(&p, sizeof(t_pipe));
	p.pids = (pid_t *)xmalloc(sizeof(pid_t) * list_size(cmd) + 1);
	if (pipe_handler(cmd, &p) == -1)
		return (-1);
	while (p.j < p.i)
		waitpid(p.pids[p.j++], &p.status, 0);
	g_cmd.is_forked = 0;
	return (0);
}