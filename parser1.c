/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:07:30 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/08 22:51:41 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checkline(char **line)
{
	if (!*line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	ft_printenv(int fd)
{
	int	i;

	i = 0;
	while (g_cmd.env_p[i])
	{
		write(fd, g_cmd.env_p[i], ft_strlen(g_cmd.env_p[i]));
		write(fd, "\n", 1);
		i++;
	}
}

void	ft_free_env(char ***env_p)
{
	int	i;

	i = 0;
	while (*env_p[i])
		free(*env_p[i++]);
	free(*env_p);
}

char	**get_name_value(char *s)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	char	**ret;

	ret = NULL;
	i = 0;
	if (s)
	{
		while (s[i] && s[i] != '=')
			i++;
		name = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (s[i])
		{
			if (s[i] == '=')
				break ;
			name[i] = s[i];
			i++;
		}
		name[i] = '\0';
		value = malloc(sizeof(char) * (ft_strlen(&s[++i]) + 1));
		j = 0;
		while (s[i])
			value[j++] = s[i++];
		value[j] = '\0';
		ret = malloc(sizeof(char *) * 2);
		ret[0] = name;
		ret[1] = value;
	}
	return (ret);
}

int	ft_comp(char *str, char *f)
{
	if (str && f)
	{
		while (*str && *f)
		{
			if (*str != *f)
				return (0);
			str++;
			f++;
		}
		if (*f == '\0')
			return (1);
	}
	return (0);
}

int	check_env(char *s)
{
	char	**var;
	char	**old_var;
	char	**env;
	int		i;

	i = 0;
	var = get_name_value(s);
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
		free(old_var[0]);
		free(old_var[1]);
		free(old_var);
		if (env[i] == NULL)
			break ;
		else
			new_env[j] = ft_strdup(env[i], 1);
		i++;
		j++;
	}
	new_env[j] = NULL;
	g_cmd.env_p = new_env;
}

int	check_export_input(char *s)
{
	if (s && ft_isalpha(*s))
	{
		while (*s)
		{
			if (!ft_isalnum(*s))
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

void	ft_export(char *parm, int fd)
{
	unsigned int	i;
	char			**ret;

	if (!parm)
	{
		ft_printenv(fd);
		return ;
	}
	else
	{
		ret = get_name_value(parm);
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

static	int	ft_numberlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_fill(int len, unsigned int n, char *number, int sign)
{
	number[len--] = '\0';
	while (len >= 0)
	{
		number[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == -1)
		number[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*number;
	int				len;
	unsigned int	nbr;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		nbr = (unsigned int) n * (-1);
		len = ft_numberlen(nbr) + 1;
		sign = -1;
	}
	else
	{
		len = ft_numberlen(n);
		nbr = (unsigned int) n;
	}
	number = (char *) malloc(sizeof(char) * len + 1);
	if (number)
		ft_fill(len, nbr, number, sign);
	return (number);
}

char	*ft_getenv(char **envp, char *var)
{
	int				i;
	char			*ret;
	unsigned int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			while (envp[i][j] && envp[i][j] != '=')
				j++;
			ret = ft_strchr(envp[i], '=');
			if (!ret)
				return (ft_strdup("", 0));
			else if (j == ft_strlen(var))
				return (ret + 1);
		}
		i++;
	}
	return (ft_strdup("", 0));
}
