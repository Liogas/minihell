/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:41:45 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/18 12:07:23 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int child_process1(t_cmd *cmd, t_minish *dt)
{
	int	n_redir[2];
	char	*path;
	char	**env;

	n_redir[1] = 0;
	n_redir[0] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (0);
	if (n_redir[1] == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	printf("get path\n");
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt),
			exit(EXIT_SUCCESS));
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	env = gen_env(dt->env_minish);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 0);
	close_tab_pipes(cmd);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (perror("execve"), 0);
	return (1);
}

int child_process2(t_cmd *cmd, t_minish *dt)
{
	int	n_redir[2];
	char	*path;
	char	**env;

	n_redir[0] = 0;
	n_redir[1] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (ft_putstr_fd("Error get redir\n", 2), 0);
	if (n_redir[0] == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	if (n_redir[1] == 0)
		if (dup2(cmd->tab_pipes[cmd->id][1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 0);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt),
			exit(EXIT_SUCCESS));
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	env = gen_env(dt->env_minish);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 0);
	close_tab_pipes(cmd);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (perror("execve"), 0);
	return (1);
}

int child_process3(t_cmd *cmd, t_minish *dt)
{
	int	n_redir[2];
	char	*path;
	char	**env;

	n_redir[0] = 0;
	n_redir[1] = 0;
	if (cmd->list_redirc)
		if (!get_redir(cmd, &n_redir[1], &n_redir[0]))
			return (0);
	if (n_redir[0] == 0)
		if (dup2(cmd->tab_pipes[cmd->id - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt),
			exit(EXIT_SUCCESS));
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[0], 2), ft_putstr_fd(" : CMD not found\n", 2), 0);
	env = gen_env(dt->env_minish);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 0);
	close_tab_pipes(cmd);
	if (execve(path, cmd->tab_opt, env) == -1)
		return (perror("execve"), 0);
	return (1);
}
