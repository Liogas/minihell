/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:11:45 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 15:33:39 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd, int mode)
{
	t_redir	*redir;
	int		i;

	if (cmd)
	{
		redir = cmd->list_redirc;
		if (!redir)
			printf("[%d] : Ne possede pas de redirection\n", getpid());
		while (redir)
		{
			printf("[%d] : Type: %d, File: %s\n", getpid(), redir->type, redir->name_file);
			if (redir->name_heredoc)
				printf("[%d] : name_heredoc->%s\n", getpid(), redir->name_heredoc);
			redir = redir->next;
		}
		i = -1;
		while (cmd->tab_opt[++i])
			printf("[%d] : opt : %s\n", getpid(), cmd->tab_opt[i]);
		if (cmd->tab_pipes)
		{
			printf("[%d] : tab_pipes:\n", getpid());
			i = 0;
			while (i < cmd->utils.n_pipe)
			{
				printf("[%d] : pipe[%d]->%d;%d\n", getpid(), i, cmd->tab_pipes[i][0], cmd->tab_pipes[i][1]);
				i++;
			}
		}
		printf("[%d] : pid->%d ; status->%d ; pos_cmd->%d\n", getpid(), cmd->pid, cmd->status, cmd->pos_cmd);
		printf("\n");
		if (cmd->next && mode)
			print_cmd(cmd->next, 1);
	}
}
