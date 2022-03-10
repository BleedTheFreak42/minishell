/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:44:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/10 05:58:03 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_chars(char *a, char *b, char **c)
{
	free(a);
	free(b);
	free(c);
}

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
			free_chars(old_var[0], old_var[1], old_var);
			return (1);
		}
		i++;
		free_chars(old_var[0], old_var[1], old_var);
	}
	return (0);
}

void	ft_cd(char **path, int fd)
{
	int	result;

	if (!path[1])
	{
		if (!ft_strlen(ft_getenv(g_cmd.env_p, "HOME")))
			printf("minishell : cd: HOME not set\n");
		else
		{
			ft_export(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
			chdir(ft_getenv(g_cmd.env_p, "HOME"));
			ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), fd);
		}
		return ;
	}
	result = chdir(path[1]);
	if (access(path[1], F_OK) == 0 && result == -1)
		printf("minishell : cd: %s: Not a directory\n", path[1]);
	else if (result == -1)
		printf("minishell : cd: %s: No such file or directory\n", path[1]);
	else
	{
		ft_export(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
		ft_export(ft_strjoin("PWD=", getcwd(NULL, 0)), fd);
	}
}
