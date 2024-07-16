/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:00:39 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:29:26 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node_env(void *env)
{
	t_node_env	*el;

	el = env;
	if (el)
	{
		if (el->name)
			free(el->name);
		if (el->value)
			free(el->value);
		free(el);
		el = NULL;
	}
}
