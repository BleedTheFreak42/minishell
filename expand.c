/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:10:07 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 14:16:56 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *str)
{
	int		i;
	int		j;
	char	*result[3];
	char	*from;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i >= 1)
	{
		result[0] = xmalloc(sizeof(char) * (i + 1));
		ft_strlcpy(result[0], str, i + 1);
	}
	else
		result[0] = ft_strdup("", 1);
	if (str[i++] == '$')
	{
		if (str[i] == '\0')
			result[1] = ft_strdup("$", 1);
		else if (ft_isdigit(str[i]))
		{
			j = i + 1;
			while (str[i] && str[i] != 32 && str[i] != '\"' && str[i] != 39)
				i++;
			from = ft_substr(&str[j], 0, i - j);
			result[1] = from;
		}
		else
		{
			j = i;
			while (str[i] && str[i] != 32 && str[i] != '\"'
				&& str[i] != 39 && ft_isalnum(str[i]))
				i++;
			from = ft_substr(&str[j], 0, i - j);
			result[1] = ft_getenv(g_cmd.env_p, from);
			if (ft_sepspesial(str[i - ft_strlen(from)]))
				result[1] = ft_strjoin("$", from);
		}
		result[2] = ft_strdup(&str[i], 1);
	}
	if (result[0] && result[1] && result[2])
	{
		from = ft_strjoin(ft_strjoin(result[0], result[1]), result[2]);
		return (from);
	}
	return (NULL);
}

t_list	*init_commands(t_list *tokens)
{
	t_list	*command;
	t_list	*args;
	t_list	*files;
	int		e_type;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = NULL;
	files = NULL;
	command = NULL;
	while (tokens)
	{
		if (((t_token *)(tokens->content))->e_type == 5)
		{
			if (!i)
			{
				args = ft_lstnew(((t_token *)(tokens->content))->value);
				i = 1;
			}
			else if (args)
				ft_lstadd_back(&args, ft_lstnew(((t_token *)
							(tokens->content))->value));
		}
		else if (((t_token *)(tokens->content))->e_type >= 1 && ((t_token *)
			(tokens->content))->e_type <= 4)
		{
			if (!j)
			{
				e_type = ((t_token *)(tokens->content))->e_type;
				tokens = tokens->next;
				files = ft_lstnew(init_file(e_type, ((t_token *)
								(tokens->content))->value));
				j = 1;
			}
			else if (files)
			{
				e_type = ((t_token *)(tokens->content))->e_type;
				tokens = tokens->next;
				ft_lstadd_back(&files, ft_lstnew(init_file(e_type, ((t_token *)
								(tokens->content))->value)));
			}
		}
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
