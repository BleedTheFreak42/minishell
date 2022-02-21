/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:53 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/02/21 09:06:41 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmalloc.h"

// extern void		*g_rtn;

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

// void	xerror(int x)
// {
// 	x == 1 ? perror("") : 0;
// 	x == 2 ? perror("") : 0;
// 	x == 3 ? perror("") : 0;
// 	x == 4 ? perror("") : 0;
// 	x == 5 ? perror("") : 0;
// 	x == 6 ? perror("") : 0;
// }

void	*xexit(int x)
{
	xflush();
	exit(x);
	return ((void *)0);
}
