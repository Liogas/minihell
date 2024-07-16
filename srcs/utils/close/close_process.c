/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:18:41 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 11:51:20 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->tab_pipes)
		close_tab_pipes(cmd->tab_pipes, cmd->utils.n_pipe);
	if (cmd->pipe_out)
		(close(cmd->pipe_out[1]));
	if (cmd->utils.close_in && cmd->pipe_in)
		close(cmd->pipe_in[0]);
}

void	close_cmds(t_process *curr_p)
{
	t_list_gl	*el;
	t_cmd		*cmd;

	el = curr_p->cmds;
	while (el)
	{
		cmd = el->content;
		close_cmd(cmd);
		el = el->next;
	}
}

static void	close_childs(t_process *curr_p, t_minish *minish)
{
	t_list_gl	*el;
	t_process	*tmp;

	el = curr_p->childs;
	while (el)
	{
		tmp = el->content;
		close_process(tmp, minish, 0, 1);
		el = el->next;
	}
}

void	close_process(t_process *curr_p, t_minish *minish, int mode, int close_out)
{
	t_process	*main;

	(void)minish;
	if (curr_p)
	{
		// printf("process[%d] : je cherche a close\n", getpid());
		main = curr_p;
		if (mode)
			while (main && main->parent)
				main = main->parent;
		if (curr_p->pipe_out && close_out)
			(close(curr_p->pipe_out[0]), close(curr_p->pipe_out[1]));
		if (curr_p->utils.close_in && curr_p->pipe_in)
			close(curr_p->pipe_in[0]);
		close_cmds(main);
		close_childs(main, minish);
	}
}
