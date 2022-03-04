/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:11:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/03 12:28:21 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_handler(int sig)
{
	char	*result;

	(void) sig;
	if (g_cmd.is_forked)
	{
		rl_on_new_line();
		rl_replace_line("",0);
		write(1, "\n", 1);
	}
	else
	{
		rl_on_new_line();
		result = ft_strjoin("minishell : ", rl_line_buffer);
		rl_replace_line("", 0);
		result = ft_strjoin(result, "  ");
		write(1, result, ft_strlen(result));
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	quit_handler(int sig)
{
	(void) sig;
	
	if (g_cmd.is_forked)
		write(1, "Quit\n", 5);
	else
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}

void	signal_handler(void)
{
	signal(SIGINT, init_handler);
	signal(SIGQUIT, quit_handler);
}
