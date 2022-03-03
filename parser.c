/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:05:04 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/02 16:23:01 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = xmalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_list	*ft_inittokens(char *str)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*head;

	head = NULL;
	token = (t_token *) xmalloc(sizeof(t_token));
	str = ft_expandall(str);
	lexer = init_lexer(str);
	token = lexer_next_token(lexer);
	if (!token)
		return (NULL);
	if (token)
		head = ft_lstnew(token);
	while (token)
	{
		// printf("TOKEN(%d,%s)\n", token->e_type, token->value);
		token = lexer_next_token(lexer);
		if (token)
			ft_lstadd_back(&head, ft_lstnew(token));
	}
	return (head);
}

t_files	*init_file(int type, char *value)
{
	t_files	*file;

	file = xmalloc(sizeof(t_files));
	file->e_ftype = type;
	file->value = value;
	return (file);
}

t_command	*init_command(void *files, void *args)
{
	t_command	*command;

	command = xmalloc(sizeof(t_command));
	command->file = files;
	command->args = args;
	return (command);
}

int	ft_check_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*current;
	t_token	*next;
	int i;

	i = 0;
	if (!tokens)
		return (1);
	tmp = tokens;
	while (tmp)
	{
		current = (t_token *)tmp->content;
		if (current->e_type == 0 && !i)
			return (1);
		next = NULL;
		if (tmp->next)
			next = (t_token *)tmp->next->content;
		else if (current->e_type >= 0 && current->e_type <= 4)
			return (1);
		if (current && next && current->e_type >= 0 && current->e_type <= 4)
		{
			if (current->e_type == next->e_type)
				return (1);
			if (next->e_type == 0)
				return (1);
		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}
