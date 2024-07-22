/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:46:36 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 16:08:05 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_doublechar(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}


void	free_check(t_check	*dt)
{
	if (dt)
	{
		if (dt->paths)
			ft_split_free(dt->paths);
		if (dt->redirct)
			free(dt->redirct);
		if (dt->oprt)
			free(dt->oprt);
		if (dt->line_cmd)
			free(dt->line_cmd);
		if (dt->bltn)
			free(dt->bltn);
		free(dt);
	}
}
