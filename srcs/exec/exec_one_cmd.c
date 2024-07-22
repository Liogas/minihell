/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:35:54 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/18 12:10:18 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_all_redir_out(int **fd, t_redir *redir, int i)
{
	if (redir->type == REDIR_OUT || redir->type == HERE_DOC_OUT)
	{
		if (redir->type == REDIR_OUT)
			*fd[i] = open(redir->name_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			*fd[i] = open(redir->name_file, O_CREAT | O_APPEND | O_WRONLY,
					0777);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDOUT_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	return (1);
}

int	get_all_redir(int **fd, t_redir *redir, int i)
{
	if (redir->type == REDIR_IN)
	{
		*fd[i] = open(redir->name_file, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	else if (redir->type == HERE_DOC_IN)
	{
		*fd[i] = open(redir->name_heredoc, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("dd minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	else if (redir->type == REDIR_OUT || redir->type == HERE_DOC_OUT)
		if (!get_all_redir_out(fd, redir, i))
			return (0);
	return (1);
}

void	free_fd(t_cmd *curr_cmd)
{
	int	i;
	int	n_redirc;

	n_redirc = count_redirc(curr_cmd->list_redirc);
	i = -1;
	while (++i < n_redirc)
		free(curr_cmd->tab_fd[i]);
	free(curr_cmd->tab_fd);
}

int	one_child(t_cmd *cmd, t_minish *dt)
{
	t_redir	*redir;
	int		i;
	char	*path;
	char	**env;

	i = 0;
	if (!init_tab_fd(cmd))
		return (0);
	redir = cmd->list_redirc;
	while (redir)
	{
		if (!get_all_redir(cmd->tab_fd, redir, i))
			return (free_fd(cmd), 0);
		redir = redir->next;
		i++;
	}
	if (!close_tmp_file(cmd))
		return (0);
	if (!cmd->tab_opt[0])
		(close_tab_pipes(cmd), free_cmd(cmd), free_minish(dt),
			exit(EXIT_SUCCESS));
	path = get_path(cmd, dt);
	if (!path)
		return (ft_putstr_fd(cmd->tab_opt[cmd->pos_cmd], 2),
			ft_putstr_fd(": CMD not found\n", 2), 0);
	env = gen_env(dt->env_minish);
	if (!env)
		return (ft_putstr_fd("Gen env failed\n", 2), 0);
	if (execve(path, cmd->tab_opt, (char *const *)env) == -1)
		return (perror("execve"), 0);
	return (1);
}

int	modif_env(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->tab_opt && cmd->tab_opt[i])
	{
		if ((ft_strcmp(cmd->tab_opt[i], "export") == 0) || (ft_strcmp(cmd->tab_opt[i], "unset") == 0))
			return (1);
		i++;
	}
	return (0);
}

int	exec_simple_cmd(t_cmd *cmd, t_minish *dt)
{
	int	heredoc;
	int		i;

	heredoc = check_if_heredoc(cmd);
	if (heredoc != 0)
		if (!exec_heredoc(cmd))
			return (0);
	i = 0;
	while (cmd->tab_opt && cmd->tab_opt[i])
	{
		if (ft_strcmp(cmd->tab_opt[i], "cd") == 0)
		{
			if (!change_dir(cmd, dt, i, 1))
				return (0);
			return (1);
		}
		i++;
	}
	dt->flag_env = modif_env(cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), 0);
	else if (cmd->pid == 0)
	{
		one_child(cmd, dt);
		(free_cmd(cmd), free_minish(dt), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(cmd->pid, NULL, 0); //LAISSER ICI SINON NE MARCHE PAS!!!!
		if (!parent_task(dt))
			return (0);
	}
	return (1);
}
