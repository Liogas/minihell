/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:41:45 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/16 13:25:43 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int child_process1(t_cmd *cmd, t_process *curr_p, t_minish *dt)
{
	int	n_redir_out;
	int	n_redir_in;
	char	*path;

	n_redir_out = 0;
	n_redir_in = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir_out, &n_redir_in))
			return (0);
	if (n_redir_out == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	if (n_redir_in == 0 && cmd->pipe_in)
		if (dup2(cmd->pipe_in[0], STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	close_process(curr_p, dt, 1, 1);
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	// printf("process[%d] : Lancement de la commande\n", getpid());
	// print_cmd(cmd);
	if (execve(path, cmd->tab_opt, NULL) == -1)
		return (perror("execve"), 0);
	return (1);
}

int child_process2(t_cmd *cmd, t_process *curr_p, t_minish *dt)
{
	int	n_redir_out;
	int n_redir_in;
	char	*path;

	n_redir_out = 0;
	n_redir_in = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir_out, &n_redir_in))
			return (0);
	if (n_redir_in == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	if (n_redir_out == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	close_process(curr_p, dt, 1, 1);
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	// printf("process[%d] : Lancement de la commande\n", getpid());
	// print_cmd(cmd);
	if (execve(path, cmd->tab_opt, NULL) == -1)
		return (perror("execve"), 0);
	return (1);
}

int child_process3(t_cmd *cmd, t_process *curr_p, t_minish *dt)
{
	int	n_redir_in;
	int	n_redir_out;
	char	*path;

	n_redir_in = 0;
	n_redir_out = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir_out, &n_redir_in))
			return (0);
	if (n_redir_in == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	if (n_redir_out == 0 && cmd->pipe_out)
		if (dup2(cmd->pipe_out[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	close_process(curr_p, dt, 1, 1);
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	// printf("process[%d] : Lancement de la commande\n", getpid());
	// print_cmd(cmd);
	if (execve(path, cmd->tab_opt, NULL) == -1)
		return (perror("execve"), 0);
	return (1);
}
