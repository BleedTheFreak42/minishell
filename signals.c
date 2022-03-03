/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:11:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/28 15:17:42 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_handler(int sig)
{
	char	*result;

	if (!*rl_line_buffer && sig)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\n", 1);
		write(1, "minishell : ", strlen("minishell : "));
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
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b", 4);
}

void	signal_handler(void)
{
	signal(SIGINT, init_handler);
	signal(SIGQUIT, quit_handler);
}
