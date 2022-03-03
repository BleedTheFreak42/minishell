/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:27:34 by ytaya             #+#    #+#             */
/*   Updated: 2022/03/02 16:41:27 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **ft_unset(char *parm)
// {
// 	char **result;
// 	char **envp;
// 	int i;
// 	int j;
	
// 	i = 0;
// 	result = (char **) malloc(sizeof (char *) * g_cmd.env_len - 1);
// 	envp = g_cmd.env_p;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], parm, ft_strlen(parm)))
// 		{
// 			continue ;
// 			g_cmd.env_len--;
// 		}
// 		result[i] = envp[i];
// 		i++;
// 	}
// 	result[i] = NULL;
// 	return (result);
// }