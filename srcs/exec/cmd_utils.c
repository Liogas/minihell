/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:07:18 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/17 16:19:52 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_in(int **fd, int i, t_redir *curr_redir)
{
	if (curr_redir->type == HERE_DOC_IN)
	{
		*fd[i] = open(curr_redir->name_heredoc, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	else
	{
		*fd[i] = open(curr_redir->name_file, O_RDONLY);
		if (*fd[i] == -1)
			return (perror("minihell"), 0);
		if (dup2(*fd[i], STDIN_FILENO) == -1)
			return (0);
		close(*fd[i]);
	}
	return (1);
}

int	get_redir_out(int **fd, int i, t_redir *curr_redir)
{
	if (curr_redir->type == REDIR_OUT)
		*fd[i] = open(curr_redir->name_file, O_CREAT | O_TRUNC | O_WRONLY,
				0777);
	else
		*fd[i] = open(curr_redir->name_file, O_CREAT | O_APPEND | O_WRONLY,
				0777);
	if (*fd[i] == -1)
		return (perror("minihell"), 0);
	if (dup2(*fd[i], STDOUT_FILENO) == -1)
		return (0);
	close(*fd[i]);
	return (1);
}

int	get_redir(t_cmd *curr_cmd, int *n_redir_out, int *n_redir_in)
{
	int	i;

	i = 0;
	if (!init_tab_fd(curr_cmd))
		return (0);
	if (!curr_cmd->tab_fd)
		return (0);
	while (curr_cmd->list_redirc)
	{
		if (curr_cmd->list_redirc->type == REDIR_IN
			|| curr_cmd->list_redirc->type == HERE_DOC_IN)
		{
			if (!get_redir_in(curr_cmd->tab_fd, i, curr_cmd->list_redirc))
				return (0);
			(*n_redir_in)++;
		}
		else if (curr_cmd->list_redirc->type == REDIR_OUT
			|| curr_cmd->list_redirc->type == HERE_DOC_OUT)
		{
			if (!get_redir_out(curr_cmd->tab_fd, i, curr_cmd->list_redirc))
				return (0);
			(*n_redir_out)++;
		}
		curr_cmd->list_redirc = curr_cmd->list_redirc->next;
		i++;
	}
	return (1);
}
