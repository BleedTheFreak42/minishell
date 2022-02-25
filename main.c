/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 09:05:52 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/25 06:49:30 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./memwatch-2.71/memwatch.h"

char *ft_expand(char *str)
{
	int i;
	int j;

	char *result[3];
	char *from;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i >= 1)
	{
		result[0] = MALLOC(sizeof(char) * (i + 1));
		ft_strlcpy(result[0],str,i + 1);
	}
	else
		result[0] = ft_strdup("", 1);
	if (str[i++] == '$')
	{

		if (str[i] == '\0')
			result[1] = ft_strdup("$",1);
		else if (ft_isdigit(str[i]))
		{
			j = i + 1;
			while (str[i] && str[i] != 32 && str[i] != '\"' && str[i] != 39)
				i++;
			from = ft_substr(&str[j],0,i - j);
			result[1] = from;
		}
		else
		{
			j = i;
			while (str[i] && str[i] != 32 && str[i] != '\"' && str[i] != 39)
				i++;
			from = ft_substr(&str[j],0,i - j);
			result[1] = ft_getenv(g_cmd.env_p,from);
			if (ft_sepspesial(str[i - ft_strlen(from)]))
				result[1] = ft_strjoin("$",from);
		}
		result[2] = ft_strdup(&str[i], 1);
	}
		
	if (result[0] && result[1] && result[2])
	{
		from = ft_strjoin(ft_strjoin(result[0],result[1]),result[2]);
		return (from);
	}
	return (NULL);
}

int get_nbdollar(char *str)
{
	int c;

	c = 0;
	str = ft_strchrq(str,'$');
	while (str)
	{
		str++;
		if ((*str == 32 || *str == '$' || *str == 34) && g_cmd.q.d_q)
			return (-1);
		else if (*str == 34 && !g_cmd.q.d_q)
		{
			str = ft_strchrq(str,'$');
			continue;
		}
		c++;
		str = ft_strchrq(str,'$');
	}
	return (c);
}

char *ft_expandall(char *str)
{
	int nb;
	char *result;

	nb = get_nbdollar(str);
	result = str;
	if (nb == -1)
		return(str);
	while (nb--)
		result = ft_expand(result);
	return (result);
}

int ft_check_syntax(char *str)
{
	unsigned int i;

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
		if(str[i] == 39)
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

static char **add_env(char **envp)
{
	unsigned int i;
	char	**ret;

	i = 0;
	while(envp[i])
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

char *ft_getenv(char **envp,char *var)
{
	int	i;
	char *ret;
	unsigned int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			while (envp[i][j] && envp[i][j] != '=')
				j++;
			ret = ft_strchr(envp[i],'=');
			if (!ret)
				return(ft_strdup("", 0));
			else if (j == ft_strlen(var))
				return (ret + 1);
		}
		i++;
	}
	return (ft_strdup("", 0));
}

void ft_free_env(char ***env_p)
{
	int i; 

	i = 0;
	while (*env_p[i])
		free(*env_p[i++]);
	free(*env_p);
}

void ft_export(char *parm)
{
	unsigned int i;
	char	**ret;

	ret = NULL;
	g_cmd.env_len++;
	ret = (char **) malloc(sizeof(char *) * (g_cmd.env_len + 2));
	i = 0;
	while (g_cmd.env_p[i])
	{
		ret[i] = ft_strdup(g_cmd.env_p[i], 0);
		i++;
	}
	ret[i] = ft_strdup(parm, 0);
	ret[++i] = NULL;
	free(g_cmd.env_p);
	g_cmd.env_p = ret;
}

void ft_printenv()
{
	int i;

	i = 0;
	while (g_cmd.env_p[i])
		printf("%s\n",g_cmd.env_p[i++]);
}

void ft_exit()
{
	free(g_cmd.env_p);
	leakcheck();
	exit(0);
}

t_token *init_token(int type, char *value)
{
	t_token *token;

	token = MALLOC(sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_list *ft_inittokens(char *str)
{
	t_lexer *lexer;
	t_token *token;
	t_list *head;

    head = NULL;
	token = (t_token *) MALLOC(sizeof(t_token));
	str = ft_expandall(str);
	lexer = init_lexer(str);
	token = lexer_next_token(lexer);
	if (token)
		head = ft_lstnew(token);
	while (token)
	{
		// printf("TOKEN(%d,%s)\n",token->e_type,token->value);
		token = lexer_next_token(lexer);
		if (token)
			ft_lstadd_back(&head,ft_lstnew(token));
	}
	return (head);
}

t_files *init_file(int type,char *value)
{
	t_files *file;

	file = MALLOC(sizeof(t_files));
	file->e_ftype = type;
	file->value = value;
	return (file);
}

t_command *init_command(void *files, void *args)
{
	t_command *command;
	
	command = MALLOC(sizeof(t_command));
	command->file = files;
	command->args = args;
	return (command);
}

t_list *init_commands(t_list *tokens)
{
	t_list *command;
	t_list *args;
	t_list *files;
	int e_type;
	int i;
	int j;
	
	i = 0;
	j = 0;
	args = NULL;
	files = NULL;
	command = NULL;
	while (tokens)
	{
		if (((t_token *)(tokens->content))->e_type == 5)
		{
			if (!i)
			{
				args = ft_lstnew(((t_token *)(tokens->content))->value);
				i = 1;
			}
			else if (args)
				ft_lstadd_back(&args,ft_lstnew(((t_token *)(tokens->content))->value));
		}
		else if (((t_token *)(tokens->content))->e_type >= 1  && ((t_token *)(tokens->content))->e_type <= 4)
		{
			if (!j)
			{
				e_type = ((t_token *)(tokens->content))->e_type;
				tokens = tokens->next;
				files = ft_lstnew(init_file(e_type,((t_token *)(tokens->content))->value));
				j = 1;
			}
			else if (files)
			{
				e_type = ((t_token *)(tokens->content))->e_type;
				tokens = tokens->next;
				ft_lstadd_back(&files,ft_lstnew(init_file(e_type,((t_token *)(tokens->content))->value)));	
			}
		}
		else if (((t_token *)(tokens->content))->e_type == 0)
		{
			tokens = tokens->next;
			break;
		}
		tokens = tokens->next;
	}
	g_cmd.tokens = tokens;
	command = ft_lstnew(init_command(files,args));
	return (command);
}

int ft_check_tokens(t_list *tokens)
{
	t_list *tmp;
	t_token *current;
	t_token *next;

	tmp = tokens;
	while(tmp)
	{
		current = (t_token *)tmp->content;
		next = NULL;
		if (tmp->next)
			next = (t_token *)tmp->next->content;
		else if (current->e_type >= 0 && current->e_type <= 4)
			return (1);
		if (current && next && current->e_type >= 0 && current->e_type <= 4)
			if (current->e_type == next->e_type)
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int main(int argc, char const *argv[],char **envp)
{
	(void)  argc;
	(void)  argv;
	(void) envp;
	char *str;
	t_list *tokens;
	t_list *commands; 
	t_list *args;
	t_list *files;
	int i;

	args = NULL;
	commands = NULL;
	files = NULL;
	tokens = NULL;
	
	g_cmd.env_p = add_env(envp);
	while (1)
	{
		i = 0;
		str = ft_strdup("", 1);
		signal(2,ft_exit);
		while (!*str)
			str = readline("minishell : ");
		if (str && !ft_check_syntax(str))
		{
			tokens = ft_inittokens(str);
			if (ft_check_tokens(tokens))
			{
				printf("error\n");
				xflush();
				leakcheck();
				exit(0);
			}
			g_cmd.tokens = tokens;
			while (g_cmd.tokens)
			{
				if (!i)
				{
					commands = init_commands(g_cmd.tokens);
					i = 1;	
				}
				else if (commands)
					ft_lstadd_back(&commands,init_commands(g_cmd.tokens));
			}
			while (commands)
			{
				args = ((t_command *)commands->content)->args;
				while (args)
				{
					printf("Words = %s\n",(char *)args->content);
					args = args->next;
				}
				files = ((t_command *)commands->content)->file;
				while (files)
				{
					printf("type = %d\n",((t_files *)files->content)->e_ftype);
					printf("filename = %s\n",((t_files *)files->content)->value);
					files = files->next;
				}
				printf("================\n");
				commands = commands->next;
			}
		}
		else
			printf("Error\n");
		xflush();
	}
	return (0);
}