/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_block_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:07:36 by glions            #+#    #+#             */
/*   Updated: 2024/07/10 20:13:45 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_block_child_pipe(t_block_child *curr, int after)
{
	if (curr->pipe_in != -1)
		curr->redir += 2;
	if (after)
	{
		curr->redir += 1;
		curr->pipe_out = malloc(sizeof(int) * 2);
		if (!curr->pipe_out)
			return (0);
		if (pipe(curr->pipe_out) == -1)
			return (0);
	}
	return (1);
}
