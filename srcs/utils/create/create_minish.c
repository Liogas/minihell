/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_minish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:02:37 by glions            #+#    #+#             */
/*   Updated: 2024/07/09 10:29:38 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minish	*create_minish(char **envp)
{
	t_minish	*new;
	int			i;

	new = malloc(sizeof(t_minish));
	if (!new)
		return (NULL);
	new->block_token = NULL;
	new->env_minish = NULL;
	i = -1;
	while (envp && envp[++i])
		ft_export(envp[i], &new->env_minish);
	if (!new->env_minish)
		return (free(new), NULL);
	new->check = create_check();
	if (!new->check)
		return (free(new), NULL);
	return (new);
}
