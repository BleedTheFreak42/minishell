/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 09:01:42 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/11 10:31:59 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell g_cmd;

static void p_error(void) {
  printf("minishell : syntax error near unexpected token\n");
  g_cmd.exit_code = 258;
}

static int ft_check_type(t_list *tokens) {
  while (tokens) {
    if (((t_token *)tokens->content)->e_type != 6)
      tokens = tokens->next;
    else
      return (1);
  }
  return (0);
}

static int syntax_checker(char *str) {
  t_list *tokens;

  (void)tokens;

  tokens = NULL;
  if (ft_check_syntax(str))
    return (1);
  tokens = ft_inittokens(str);
  if (!tokens)
    return (2);
  if (ft_check_type(tokens))
    return (3);
  if (ft_check_tokens(tokens))
    return (4);
  g_cmd.tokens = tokens;
  g_cmd.commands = get_listcmd();
  return (0);
}

static void ft_lunch(void) {
  char *str;
  t_list *tokens;
  int ret;

  (void)tokens;

  tokens = NULL;
  str = ft_strdup("", 1);
  while (!*str) {
    str = readline("minishell : ");
    add_history(str);
    ft_checkline(&str);
    ret = syntax_checker(str);
    if (ret == 2)
      continue;
    else if (ret == 0) {
      if (g_cmd.commands)
        execute(g_cmd.commands);
    } else
      p_error();
  }
  free(str);
}

int main(int argc, char const *argv[], char **envp) {
  t_list *tokens;

  (void)tokens;

  (void)argc;
  (void)argv;
  tokens = NULL;
  setup_term();
  signal_handler();
  g_cmd.env_p = add_env(envp);
  while (1) {
    ft_lunch();
  }
  xflush();
  ft_free_env(&g_cmd.env_p);
  return (0);
}
