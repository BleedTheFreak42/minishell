/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:43:11 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 15:55:14 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(char **names)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (names && names[i])
	{
		if (ft_unset_one(names[i]) == 1)
			ret = 1;
		i++;
	}
	return (ret);
}

int	ft_unset_one(char *name)
{
	char	**new_env;
	char	**old_var;
	size_t	i;
	size_t	j;

	if (!check_export_input(name)
		&& printf("minishell : unset: `%s': not a valid identifier\n", name))
		return (1);
	new_env = (char **)malloc(sizeof(char *) * (g_cmd.env_len + 1));
	i = 0;
	j = 0;
	while (g_cmd.env_p[i])
	{
		old_var = get_name_value(g_cmd.env_p[i]);
		if (ft_comp(old_var[0], name)
			&& ft_strlen(old_var[0]) == ft_strlen(name)
			&& g_cmd.env_p[++i] == NULL)
			break ;
		else
			new_env[j++] = ft_strdup(g_cmd.env_p[i++], 0);
	}
	new_env[j] = NULL;
	ft_free_env(&g_cmd.env_p);
	g_cmd.env_p = new_env;
	return (0);
}
