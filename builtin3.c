/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:43:11 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 05:57:54 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *name)
{
	char	**new_env;
	char	**old_var;
	char	**env;
	size_t	i;
	size_t	j;

	env = g_cmd.env_p;
	new_env = (char **)malloc(sizeof(char *) * (g_cmd.env_len + 1));
	i = 0;
	j = 0;
	while (env[i])
	{
		old_var = get_name_value(env[i]);
		if (ft_comp(old_var[0], name)
			&& ft_strlen(old_var[0]) == ft_strlen(name))
				i++;
		free_chars(old_var[0], old_var[1], old_var);
		if (env[i] == NULL)
			break ;
		else
			new_env[j++] = ft_strdup(env[i++], 1);
	}
	new_env[j] = NULL;
	g_cmd.env_p = new_env;
}
