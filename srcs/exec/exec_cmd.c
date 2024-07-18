/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:29:39 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/18 12:08:19 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int which_process(t_cmd *curr_cmd, t_minish *dt)
{
	if (curr_cmd->id == 0)
		return (child_process1(curr_cmd, dt));
	else if (curr_cmd->id == curr_cmd->utils.n_cmd - 1)
		return (child_process3(curr_cmd, dt));
	else
		return (child_process2(curr_cmd, dt));
}

int exec_line(t_cmd *cmd, t_minish *dt)
{
	int		i;
	int		heredoc;

	i = 0;
	heredoc = check_if_heredoc(cmd);
	if (heredoc != 0)
		if (!exec_heredoc(cmd))
			return (0);
	while (cmd && i < cmd->utils.n_cmd)
	{
		cmd->pid = fork();
		cmd->id = i;
		if (cmd->pid == -1)
			return (perror("de fork"), 0);
		else if (cmd->pid == 0)
		{
			which_process(cmd, dt);
			close_tab_pipes(cmd);
			free_cmd(cmd);
			free_minish(dt);
			exit(EXIT_FAILURE);
		}
		cmd = cmd->next;
		i++;
	}
	return (1);
}

void	add_pipes(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		**pipes;

	tmp = (*cmd)->next;
	pipes = (*cmd)->tab_pipes;
	while (tmp)
	{
		tmp->tab_pipes = pipes;
		tmp->utils.n_pipe = (*cmd)->utils.n_pipe;
		tmp->utils.n_cmd = (*cmd)->utils.n_cmd;
		tmp = tmp->next;
	}
}

int	exec_with_pipes(t_cmd *cmd, t_minish *dt)
{
	cmd->tab_pipes = init_tab_pipes(cmd->utils.n_pipe, &cmd->tab_pipes);
	if (!cmd->tab_pipes)
		return (0);
	add_pipes(&cmd);
	if (!exec_line(cmd, dt))
		return (0);
	return (1);
}

int	exec_cmd(t_cmd *cmd, t_minish *dt)
{

	cmd->utils.n_pipe = count_pipe(cmd, &cmd->utils.n_pipe);
	cmd->utils.n_cmd = nb_cmd(cmd);
	if (cmd->utils.n_pipe != 0)
	{
		if (!exec_with_pipes(cmd, dt))
			return (0);
	}
	else
		if (!exec_simple_cmd(cmd, dt))
			return (0);
	return (1);
}
