/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:00 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/02/21 02:39:50 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xmalloc.h"

void	*xmalloc(size_t bytes)
{
	g_cmd.tmp = g_cmd.g_x;
	g_cmd.g_rtn = malloc(bytes);
	if (!g_cmd.g_rtn)
		return (NULL);
	if (!g_cmd.g_x)
	{
		g_cmd.g_x = malloc(sizeof(t_link));
		if (!g_cmd.g_x)
			return (xexit(1));
		g_cmd.g_x->addr = (size_t)g_cmd.g_rtn;
		g_cmd.g_x->next = NULL;
	}
	else
	{
		while (g_cmd.tmp->next)
			g_cmd.tmp = g_cmd.tmp->next;
		g_cmd.tmp->next = malloc(sizeof(t_link));
		if (!g_cmd.tmp->next)
			return (xexit(1));
		g_cmd.tmp = g_cmd.tmp->next;
		g_cmd.tmp->addr = (size_t)g_cmd.g_rtn;
		g_cmd.tmp->next = NULL;
	}
	return (ftft());
}

int	xbrowse(void *adr)
{
	t_link	*back;

	g_cmd.tmp = g_cmd.g_x;
	while (g_cmd.tmp && g_cmd.tmp->addr != (size_t)adr)
	{
		back = g_cmd.tmp;
		if (back)
			g_cmd.tmp = g_cmd.tmp->next;
	}
	back->next = g_cmd.tmp->next;
	if (g_cmd.tmp && back->next != (void *)42)
	{
		free((void *)g_cmd.tmp->addr);
		free(g_cmd.tmp);
		return (0);
	}
	return (1);
}

void	xfree(void *adr)
{
	g_cmd.tmp = g_cmd.g_x;
	if (g_cmd.g_x && g_cmd.tmp)
	{
		if (g_cmd.tmp->addr == (size_t)adr)
		{
			free((void *)g_cmd.tmp->addr);
			g_cmd.g_x = g_cmd.tmp->next;
			free(g_cmd.tmp);
		}
		else
		{
			if (xbrowse(adr))
			{
				ft_putstr("Non user allocated pointer was being freed!\n");
				free(adr);
				return ;
			}
		}
	}
	else
	{
		ft_putstr("Non user allocated pointer was being freed!\n");
		free(adr);
	}
}

void	xflush(void)
{
	g_cmd.tmp = g_cmd.g_x;
	free(g_cmd.g_rtn);
	while (g_cmd.tmp)
	{
		free((void *)g_cmd.tmp->addr);
		g_cmd.g_x = g_cmd.tmp->next;
		free(g_cmd.tmp);
		g_cmd.tmp = g_cmd.g_x;
	}
}

void	leakcheck(void)
{
	size_t	c;

	c = 0;
	g_cmd.tmp = g_cmd.g_x;
	while (g_cmd.tmp)
	{
		c++;
		g_cmd.tmp = g_cmd.tmp->next;
	}
	printf("leak check : %zu\n", c);
}
