/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:01:42 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/27 10:41:57 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_error(void)
{
	printf("$> Syntax error\n");
	xflush();
}

void	ft_lunch(void)
{
	char	*str;
	t_list	*tokens;

	tokens = NULL;
		str = ft_strdup("", 1);
	while (!*str)
	{
		str = readline("minishell : ");
		ft_checkline(&str);
	}
	if (str && !ft_check_syntax(str))
	{
		tokens = ft_inittokens(str);
		if (ft_check_tokens(tokens))
			p_error();
		else
		{
			g_cmd.tokens = tokens;
			ft_printcommads();
		}
	}
	else
		p_error();
}

int	main(int argc, char const *argv[], char **envp)
{
	(void) argc;
	(void) argv;
	g_cmd.env_p = add_env(envp);
	while (1)
	{
		ft_lunch();
		xflush();
	}
	return (0);
}
