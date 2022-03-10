/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:43:11 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 12:37:46 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *name)
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
		if (env[i] == NULL)
			break ;
		else
			new_env[j++] = ft_strdup(env[i++], 0);
	}
	new_env[j] = NULL;
    ft_free_env(&g_cmd.env_p);
	g_cmd.env_p = new_env;
	return (0);
}
