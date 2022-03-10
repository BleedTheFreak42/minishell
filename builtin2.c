/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:41:28 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 05:57:46 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_check_params(char *param, int fd, char ***ret)
{
	if (!param)
	{
		ft_printenv(fd, 1);
		return (1);
	}
	else
	{
		*ret = get_name_value(param);
		if (*ret == NULL)
			return (1);
		if (!check_export_input((*ret)[0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", param);
			return (1);
		}
	}
	return (0);
}

void	ft_export(char *param, int fd)
{
	unsigned int	i;
	char			**ret;

	if (ft_export_check_params(param, fd, &ret))
		return ;
	if (check_env(param))
	{
		ret = get_name_value(param);
		ft_unset(ret[0]);
		g_cmd.env_len--;
		ft_export(param, fd);
	}
	else
	{
		g_cmd.env_len++;
		ret = (char **) xmalloc(sizeof(char *) * (g_cmd.env_len + 2));
		i = -1;
		while (g_cmd.env_p[++i])
			ret[i] = ft_strdup(g_cmd.env_p[i], 1);
		ret[i] = ft_strdup(param, 1);
		ret[++i] = NULL;
		g_cmd.env_p = ret;
	}
}
