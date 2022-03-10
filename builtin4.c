/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:44:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 00:44:33 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(char *s)
{
	char	**var;
	char	**old_var;
	char	**env;
	int		i;

	i = 0;
	var = get_name_value(s);
	if (var == NULL)
		return (1);
	env = g_cmd.env_p;
	while (env[i])
	{
		old_var = get_name_value(env[i]);
		if (ft_comp(old_var[0], var[0])
			&& ft_strlen(old_var[0]) == ft_strlen(var[0]))
		{
			free(old_var[0]);
			free(old_var[1]);
			free(old_var);
			return (1);
		}
		i++;
		free(old_var[0]);
		free(old_var[1]);
		free(old_var);
	}
	return (0);
}
