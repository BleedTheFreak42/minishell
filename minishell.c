/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:05:52 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/26 14:43:19 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbdollar(char *str)
{
	int	c;

	c = 0;
	str = ft_strchrq(str, '$');
	while (str)
	{
		str++;
		if ((*str == 32 || *str == '$') && g_cmd.q.d_q)
			return (-1);
		else if (*str == 34 && !g_cmd.q.d_q)
			continue ;
		c++;
		str = ft_strchrq(str, '$');
	}
	return (c);
}

char	*ft_expandall(char *str)
{
	int		nb;
	char	*result;

	nb = get_nbdollar(str);
	result = str;
	if (nb == -1)
		return (str);
	while (nb--)
		result = ft_expand(result);
	return (result);
}

int	ft_check_syntax(char *str)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] != 34)
				return (-1);
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] != 39)
				return (-1);
		}
		i++;
	}
	return (0);
}

static char	**add_env(char **envp)
{
	unsigned int	i;
	char			**ret;

	i = 0;
	while (envp[i])
		i++;
	g_cmd.env_len = i;
	ret = (char **) malloc(sizeof(char *) * (g_cmd.env_len + 1));
	i = 0;
	while (envp[i])
	{
		ret[i] = ft_strdup(envp[i], 0);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

// void	ft_printcommads()
// {
// 	t_list *commands; 
// 	t_list *args;
// 	t_list *files;
// 	int i;
// 	args = NULL;
// 	commands = NULL;
// 	files = NULL;
// 	i = 0;
// 	while (g_cmd.tokens)
// 	{
// 		if (!i)
// 		{
// 			commands = init_commands(g_cmd.tokens);
// 			i = 1;	
// 		}
// 		else if (commands)
// 			ft_lstadd_back(&commands,init_commands(g_cmd.tokens));
// 	}
// 	while (commands)
// 	{
// 		args = ((t_command *)commands->content)->args;
// 		while (args)
// 		{
// 			printf("Words = %s\n",(char *)args->content);
// 			args = args->next;
// 		}
// 		files = ((t_command *)commands->content)->file;
// 		while (files)
// 		{
// 			printf("type = %d\n",((t_files *)files->content)->e_ftype);
// 			printf("filename = %s\n",((t_files *)files->content)->value);
// 			files = files->next;
// 		}
// 		printf("================\n");
// 		commands = commands->next;
// 	}
// }

int	main(int argc, char const *argv[], char **envp)
{
	char	*str;
	t_list	*tokens;

	(void) argc;
	(void) argv;
	tokens = NULL;
	g_cmd.env_p = add_env(envp);
	while (1)
	{
		str = ft_strdup("", 1);
		while (!*str)
		{
			str = readline("minishell : ");
			ft_checkline(&str);
		}
		if (str && !ft_check_syntax(str))
		{
			tokens = ft_inittokens(str);
			if (ft_check_tokens(tokens))
			{
				printf("$> Syntax error\n");
				xflush();
			}
			g_cmd.tokens = tokens;
		}
		else
			printf("$> Syntax error\n");
		xflush();
	}
	return (0);
}
