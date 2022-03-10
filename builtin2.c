/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:41:28 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 00:42:49 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *parm, int fd)
{
	unsigned int	i;
	char			**ret;

	if (!parm)
	{
		ft_printenv(fd, 1);
		return ;
	}
	else
	{
		ret = get_name_value(parm);
		if (ret == NULL)
			return ;
		if (!check_export_input(ret[0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", parm);
			return ;
		}
	}
	if (check_env(parm))
	{
		ret = get_name_value(parm);
		ft_unset(ret[0]);
		g_cmd.env_len--;
		ft_export(parm, fd);
	}
	else
	{
		g_cmd.env_len++;
		ret = (char **) malloc(sizeof(char *) * (g_cmd.env_len + 2));
		i = 0;
		while (g_cmd.env_p[i])
		{
			ret[i] = ft_strdup(g_cmd.env_p[i], 1);
			i++;
		}
		ret[i] = ft_strdup(parm, 1);
		ret[++i] = NULL;
		g_cmd.env_p = ret;
	}
}
