/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 03:16:09 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/03/11 10:58:39 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H
#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define INFILE 0
#define OUTFILE 1
#define APPFILE 2

typedef struct s_files {
  enum {
    TYPE_GTHAN = 1,
    TYPE_LTHAN = 2,
    TYPE_HEREDOC = 3,
    TYPE_APPEND = 4
  } e_ftype;
  char *value;
} t_files;

typedef struct s_pipe {
  int i;
  int j;
  int infd;
  int outfd;
  int fds[2];
  int status;
  pid_t *pids;
  char **cmd;
  t_list *files;
  char **arg_head;
} t_pipe;

int ft_strnchr(char *str, char c);
char *ft_strndup(char *str, unsigned int n);
char *join_path(char *path, char *bin);
int ft_strncmp(char *str1, char *str2, int n);
int here_doc(char *path, char *esc);
void exec(char **cmd, char **envp);
int ft_strncmp(char *s1, char *s2, int n);
char *join_path(char *path, char *bin);
int execute(t_list *cmd);
#endif
