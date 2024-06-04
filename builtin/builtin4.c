/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 00:44:09 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 10:44:09 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_env(char *s) {
  char **var;
  char **old_var;
  char **env;
  int i;

  i = 0;
  var = get_name_value(s);
  if (var == NULL)
    return (1);
  env = g_cmd.env_p;
  while (env[i]) {
    old_var = get_name_value(env[i]);
    if (ft_comp(old_var[0], var[0]) &&
        ft_strlen(old_var[0]) == ft_strlen(var[0]))
      return (1);
    i++;
  }
  return (0);
}

static int ft_home_unset(char *pwd, int fd) {
  (void)pwd;
  int result;
  char new[1025];

  result = chdir(ft_getenv(g_cmd.env_p, "HOME"));
  ft_export_one(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
  if (!result)
    pwd = getcwd(new, 1024);
  ft_export_one(ft_strjoin("PWD=", new), fd);
  return (result);
}

int ft_cd(char **path, int fd) {
  static int result;
  char pwd[1025];

  if (!path[1]) {
    if (!ft_strlen(ft_getenv(g_cmd.env_p, "HOME")))
      printf("minishell : cd: HOME not set\n");
    else
      result = ft_home_unset(getcwd(pwd, 1024), fd);
    return (result);
  }
  result = chdir(path[1]);
  if (!result) {
    getcwd(pwd, 1024);
    ft_export_one(ft_strjoin("OLDPWD=", ft_getenv(g_cmd.env_p, "PWD")), fd);
  }
  if (access(path[1], F_OK) == 0 && result == -1)
    printf("minishell : cd: %s: Not a directory\n", path[1]);
  else if (result == -1)
    printf("minishell : cd: %s: No such file or directory\n", path[1]);
  else if (ft_getenv(g_cmd.env_p, "PWD"))
    ft_export_one(ft_strjoin("PWD=", pwd), fd);
  return (result);
}
