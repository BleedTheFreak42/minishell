/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:21:04 by ytaya             #+#    #+#             */
/*   Updated: 2022/02/21 05:06:39 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "lexer.h"
#include "tokenizer.h"
#include "xmalloc.h"
#include "parser.h"

typedef	struct	s_link
{
	size_t				addr;
	struct s_link		*next;
}				t_link;

typedef struct s_pipe
{
	struct s_command *cmd;
	int f_input;
	int f_output;
	struct s_pipe *next;
}t_pipe;

typedef struct s_args
{
	void *ptr;
	struct s_args *next;
}t_args;

typedef struct s_command
{
	char *command;
	t_args *args_list;
	t_pipe *pipe;
}t_command;


typedef struct s_minihsell
{
	t_link	*g_x;
	void			*g_rtn;
	t_link	*tmp;
	char 	**env_p;
	size_t	env_len;
	t_tokenlst *tokens;
	t_command *commands;
}t_minishell;

t_minishell g_cmd;

int	ft_isprint(int c);
char* ft_strcat(char* destination, const char* source);
unsigned int ft_strlen(const char *str);
int	ft_isalnum(int c);
void *ft_realloc(void *ptr,size_t size);
void	*ft_memcpy(void *dst, const void * src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1, int f);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchrq(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);
char *ft_getenv(char **envp,char *var);
// char	*ft_strjoin(char const *s1, char const *s2);
#endif