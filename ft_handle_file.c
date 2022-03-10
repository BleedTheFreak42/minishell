/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 04:18:30 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 04:32:20 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_file_if1(t_files *file)
{
	write(STDERR, "minishell : ", 12);
	write(STDERR, file->value, ft_strnchr(file->value, 0));
	write(STDERR, ": No such file or directory\n", 28);
	return (-1);
}

int	handle_file_if2(t_files *file, int *out)
{
	if (*out != 1)
		close(*out);
	*out = open(file->value, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (*out);
}

int	handle_file_if3(t_files *file, int *out)
{
	if (*out != 1)
		close(*out);
	*out = open(file->value, O_CREAT | O_WRONLY | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (*out);
}

int	handle_file_if4(t_files *file, int *in)
{
	if (*in != 0)
		close(*in);
	*in = here_doc("/tmp/heredoc420", file->value);
	return (*in);
}

int	handle_files(t_list *files, int *in, int *out)
{
	t_files	file;

	while (files)
	{
		file.value = ((t_files *)files->content)->value;
		file.e_ftype = ((t_files *)files->content)->e_ftype;
		if (file.e_ftype == TYPE_LTHAN)
		{
			if (access(file.value, F_OK))
				return (handle_file_if1(&file));
			if (*in != 0)
				close(*in);
			*in = open(file.value, O_RDONLY);
		}
		else if (file.e_ftype == TYPE_GTHAN)
			*out = handle_file_if2(&file, out);
		else if (file.e_ftype == TYPE_APPEND)
			*out = handle_file_if3(&file, out);
		else if (file.e_ftype == TYPE_HEREDOC)
			*in = handle_file_if4(&file, in);
		files = files->next;
	}
	if (*in == -1 || *out == -1)
		return (-1);
	return (0);
}
