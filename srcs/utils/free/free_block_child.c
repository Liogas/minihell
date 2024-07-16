/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_block_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:19:41 by glions            #+#    #+#             */
/*   Updated: 2024/07/12 19:48:32 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_block_child(void *dt)
{
	t_block_child	*block;

	block = dt;
	if (block)
	{
		if (block->env)
			free_list_gl(&block->env, &free_node_env);
		if (block->child)
			free_list_gl(&block->child, &free_block_child);
		if (block->cmds)
			free_list_gl(&block->cmds, &free_cmd);
		if (block->pipe_out)
			free(block->pipe_out);
		free(block);
	}
	block = NULL;
}
