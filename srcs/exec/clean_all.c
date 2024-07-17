/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:53:35 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/17 11:19:06 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_tab_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->utils.n_pipe)
	{
		close(cmd->tab_pipes[i][0]);
		close(cmd->tab_pipes[i][1]);
		i++;
	}
}
