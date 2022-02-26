/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:53 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/02/26 14:02:03 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmalloc.h"

void	*ftft(void)
{
	void	*tmp;

	tmp = g_cmd.g_rtn;
	g_cmd.g_rtn = NULL;
	return (tmp);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	*xexit(int x)
{
	xflush();
	exit(x);
	return ((void *)0);
}

void	p_malloc(void)
{
	write(2, "malloc failed\n", ft_strlen("malloc failed\n"));
	exit(0);
}
