/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:01:42 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/03 11:41:45 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	p_error(void)
{
	printf("minishell : syntax error near unexpected token\n");
	xflush();
}

void	ft_lunch(void)
{
	char	*str;
	t_list	*tokens;
	int ret;
	

	tokens = NULL;
	str = ft_strdup("", 1);
	while (!*str)
	{
		str = readline("minishell : ");
		add_history(str);
		ft_checkline(&str);
		ret = syntax_checker(str);
		if ( ret == 2)
			continue ;
		else if (ret == 0)
		{
			if (g_cmd.commands)
				if (execute(g_cmd.commands) == -1)
				{
					printf("Error");
					exit(1);
				}
		}
		else
				p_error();
	}
	// if (str && !ft_check_syntax(str))
	// {
	// 	tokens = ft_inittokens(str);
	// 	if (ft_check_tokens(tokens))
	// 		p_error();
	// 	else
	// 	{
	// 		g_cmd.tokens = tokens;
	// 		ft_printcommads();
			// g_cmd.commands = get_listcmd();
	// 	}
	// }
	// else
	// 	p_error();
}

int ft_check_type(t_list *tokens)
{
	while (tokens)
	{
		if (((t_token *)tokens->content)->e_type != 6)
			tokens = tokens->next;
		else
			return (1);
	}
	return (0);
}

int syntax_checker(char *str)
{
	t_list *tokens;

	tokens = NULL;
	if (ft_check_syntax(str))
		return (1);
	tokens = ft_inittokens(str);
	if (!tokens)
		return (2);
	if (ft_check_type(tokens))
		return (3);
	if (ft_check_tokens(tokens))
		return (4);
	g_cmd.tokens = tokens;
	g_cmd.commands = get_listcmd();
	return (0);
}

int	main(int argc, char const *argv[], char **envp)
{
	(void) argc;
	(void) argv;
	t_list *tokens;
	
	signal_handler();
	g_cmd.env_p = add_env(envp);
	tokens = NULL;
	g_cmd.env_p = add_env(envp);
	tokens = NULL;
	signal_handler();
	while (1)
	{
		ft_lunch();
		// ft_printcommads(g_cmd.commands);
		// ft_unset(NULL);
		xflush();
	}
	return (0);
}
