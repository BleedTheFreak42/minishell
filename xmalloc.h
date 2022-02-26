/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:42:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/02/26 10:02:44 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XMALLOC_H
# define XMALLOC_H
// # define MALLOC xmalloc
// # define FREE xfree
// # define FLUSH xflush
// # define EXIT xexit
# include "minishell.h"

void			xflush(void);
void			*xmalloc(size_t bytes);
void			xfree(void *adr);
void			*xexit(int x);
void			ft_putstr(char *str);
void			*ftft(void);
void			leakcheck(void);

#endif
