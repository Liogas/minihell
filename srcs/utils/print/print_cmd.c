/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:11:45 by glions            #+#    #+#             */
/*   Updated: 2024/07/15 20:04:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	int		i;

	if (cmd)
	{
		redir = cmd->list_redirc;
		if (!redir)
			printf("Ne possede pas de redirection\n");
		while (redir)
		{
			printf("Type: %d, File: %s\n", redir->type, redir->name_file);
			redir = redir->next;
		}
		i = -1;
		while (cmd->tab_opt[++i])
			printf("opt : %s\n", cmd->tab_opt[i]);
		if (cmd->tab_pipes)
		{
			printf("tab_pipes:\n");
			i = 0;
			while (i < cmd->utils.n_pipe)
			{
				printf("pipe[%d]->%d;%d\n", i, cmd->tab_pipes[i][0], cmd->tab_pipes[i][1]);
				i++;
			}
		}
		else
			printf("Possede pas de tab_pipes\n");
		if (cmd->pipe_in)
			printf("pipe_in->[%d;%d]\n", cmd->pipe_in[0], cmd->pipe_out[1]);
		else
			printf("Ne possède pas de pipe_in\n");
		if (cmd->pipe_out)
			printf("pipe_out->[%d, %d]\n", cmd->pipe_out[0], cmd->pipe_out[1]);
		else
			printf("Ne possede pas de pipe_out\n");
		printf("pid->%d ; status->%d\n", cmd->pid, cmd->status);
		printf("\n");
		if (cmd->next)
			print_cmd(cmd->next);
	}
}
