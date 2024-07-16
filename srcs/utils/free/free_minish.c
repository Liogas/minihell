/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:41:17 by glions            #+#    #+#             */
/*   Updated: 2024/07/10 14:46:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minish(t_minish *dt)
{
	if (dt)
	{
		if (dt->env_minish)
			free_list_gl(&dt->env_minish, &free_node_env);
		if (dt->block_token)
			free_dt_elem(&dt->block_token);
		if (dt->check)
			free_check(dt->check);
		free(dt);
	}
}
