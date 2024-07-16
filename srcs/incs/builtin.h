/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:49:59 by glions            #+#    #+#             */
/*   Updated: 2024/06/11 14:34:17 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_echo
{
	int		mode;
	char	*str_end;
	pid_t	pid_child;
	int		nb_simple;
	int		nb_double;
	int		parenthese;
}			t_echo;

// FT_ECHO
int			ft_unset(t_list_gl **list, char *name);
void		ft_env(t_list_gl *list);
int			ft_export(char *str, t_list_gl **list);

#endif