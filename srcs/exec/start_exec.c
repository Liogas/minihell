/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:29 by glions            #+#    #+#             */
/*   Updated: 2024/07/22 18:42:06 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_exec(t_minish *dt_minish)
{
	t_cmd		*cmd;
	t_cmd		*head;

	print_dt_elem(dt_minish->block_token);
	if (!init_cmd(dt_minish->block_token, &cmd, dt_minish))
		return (0);
	if (!exec_cmd(cmd, dt_minish))
		return (free_cmd(cmd), 0);
	head = cmd;
	close_tab_pipes(cmd);
	while (cmd)
	{
		waitpid(cmd->pid, &dt_minish->status, 0);
		cmd = cmd->next;
	}
	free_cmd(head);
	return (1);
}
