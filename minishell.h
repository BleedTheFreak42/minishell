/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 00:21:04 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/09 06:46:59 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "lexer.h"
# include "tokenizer.h"
# include "xmalloc.h"
# include "list.h"
# include "exec.h"
# include <termios.h>

typedef struct s_link
{
	size_t				addr;
	struct s_link		*next;
}t_link;

typedef struct s_qoute
{
	int	s_q;
	int	d_q;
}t_qoute;

typedef struct s_minihsell
{
	t_link	*g_x;
	void	*g_rtn;
	t_link	*tmp;
	char	**env_p;
	size_t	env_len;
	t_list	*commands;
	t_list	*tokens;
	t_qoute	q;
	int 	is_forked;
	int 	exit_code;
    int     in_herdoc;
}t_minishell;


typedef struct s_command
{
	t_list	*args;
	t_list	*file;
}t_command;

t_minishell	g_cmd;

int				ft_isprint(int c);
char			*ft_strcat(char *destination, const char *source);
unsigned int	ft_strlen(const char *str);
int				ft_isalnum(int c);
void			*ft_realloc(void *ptr, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1, int f);
void			ft_strcpy(char *dst, const char *src);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchrq(const char *s, int c);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_getenv(char **envp, char *var);
t_token			*init_token(int type, char *value);
t_command		*init_command(void *files, void *args);
t_files			*init_file(int type, char *value);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_sepspesial(int c);
void			p_malloc(void);
void			ft_checkline(char **line);
char			*ft_expand(char *str);
int				ft_check_tokens(t_list *tokens);
char			*ft_expandall(char *str);
t_list			*ft_inittokens(char *str);
t_list			*init_commands(t_list *tokens);
t_list			*get_listcmd(void);
char			**add_env(char **envp);
int				ft_check_syntax(char *str);
void			ft_printcommads(t_list *commands);
void			ft_export(char *parm, int fd);
void			ft_printenv(int fd, int flag);
char			*ft_exapnd_if1(int i, char *str);
int				get_dollar_index(char *str);
char			*ft_expand_else3(char *s1, char *s2, char *s3);
char			*ft_expand_else2(int *i, char *str, int j);
char			*ft_expand_else1(int *i, char *str, int j);
void			signal_handler(void);
int				ft_strcmp(char *s1, char *s2);
int				ft_def(char c);
int				syntax_checker(char *str);
void			ft_unset(char *parm);
t_list			*ft_expand_tokens(t_list *tokens);
int				get_nbdollar(char *str);
int				check_env(char *s);
int				ft_comp(char *str, char *f);
void			ft_echo(char **args);
void			ft_pwd(int fd);
void			ft_cd(char **path, int fd);
void	ft_exit(char **cmds, int fd);
char			*ft_itoa(int n);
unsigned char	ft_atoi(const char *nptr);
int				ft_isalnum0(int c);
void			quit_handler(int sig);
void			setup_term(void);

#endif

