/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_node_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:54:37 by glions            #+#    #+#             */
/*   Updated: 2024/07/01 13:21:55 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node_env	*dup_node_env(t_node_env *dt)
{
	t_node_env	*new;

	if (!dt)
		return (NULL);
	new = malloc(sizeof(t_node_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(dt->name);
	if (!new->name)
		return (free(new), NULL);
	new->value = ft_strdup(dt->value);
	if (!new->value)
		return (free(new->name), free(new), NULL);
	return (new);
}
