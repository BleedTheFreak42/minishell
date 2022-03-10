/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 09:41:31 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 13:54:23 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*fill_args(t_list **tokens, t_list *args)
{
	static int		i;

	if (!args)
		i = 0;
	if (!i)
	{
		args = ft_lstnew(((t_token *)((*tokens)->content))->value);
		i = 1;
	}
	else if (args)
		ft_lstadd_back(&args, ft_lstnew(((t_token *)
					((*tokens)->content))->value));
	return (args);
}

t_list	*fill_files(t_list **tokens, t_list *files)
{
	int				e_type;
	static int		j;

	if (!files)
		j = 0;
	if (!j)
	{
		e_type = ((t_token *)((*tokens)->content))->e_type;
		(*tokens) = (*tokens)->next;
		files = ft_lstnew(init_file(e_type, ((t_token *)
						((*tokens)->content))->value));
		j = 1;
	}
	else if (files)
	{
		e_type = ((t_token *)((*tokens)->content))->e_type;
		(*tokens) = (*tokens)->next;
		ft_lstadd_back(&files, ft_lstnew(init_file(e_type, ((t_token *)
						((*tokens)->content))->value)));
	}
	return (files);
}

t_list	*init_commands(t_list *tokens)
{
	t_list	*command;
	t_list	*args;
	t_list	*files;

	args = NULL;
	files = NULL;
	command = NULL;
	while (tokens)
	{
		if (((t_token *)(tokens->content))->e_type == 5)
			args = fill_args(&tokens, args);
		else if (((t_token *)(tokens->content))->e_type >= 1 && ((t_token *)
			(tokens->content))->e_type <= 4)
			files = fill_files(&tokens, files);
		else if (((t_token *)(tokens->content))->e_type == 0)
		{
			tokens = tokens->next;
			break ;
		}
		tokens = tokens->next;
	}
	g_cmd.tokens = tokens;
	command = ft_lstnew(init_command(files, args));
	return (command);
}

t_list	*get_listcmd(void)
{
	t_list	*commands;
	int		i;

	commands = NULL;
	i = 0;
	while (g_cmd.tokens)
	{
		if (!i)
		{
			commands = init_commands(g_cmd.tokens);
			i = 1;
		}
		else if (commands)
			ft_lstadd_back(&commands, init_commands(g_cmd.tokens));
	}
	return (commands);
}
