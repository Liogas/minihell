/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:19:24 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/17 15:00:40 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_tmp_file(t_cmd *cmd)
{
	t_redir	*redir;
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = cmd;
	while (curr)
	{
		redir = curr->list_redirc;
		while (redir)
		{
			if (redir->type == HERE_DOC_IN && redir->name_heredoc)
			{
				if (unlink(redir->name_heredoc) == -1)
					return (0);
				i++;
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (1);
}

int	get_heredoc(t_redir *curr, int i)
{
	char	*prompt;
	char	*new1;

	new1 = ft_itoa(i);
	curr->name_heredoc = ft_strjoin(".heredoc_tmp", new1);
	free(new1);
	if (!curr->name_heredoc)
		return (0);
	curr->fd_heredoc = open(curr->name_heredoc, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (curr->fd_heredoc == -1)
		return (0);
	prompt = readline("> ");
	while (prompt && ft_strcmp(prompt, curr->name_file) != 0)
	{
		write(curr->fd_heredoc, prompt, ft_strlen(prompt));
		write(curr->fd_heredoc, "\n", 1);
		free(prompt);
		prompt = readline("> ");
	}
	if (prompt)
		free(prompt);
	close(curr->fd_heredoc);
	return (1);
}

int	exec_heredoc(t_cmd *curr)
{
	t_redir	*redir;
	int		i;

	i = 0;
	while (curr)
	{
		redir = curr->list_redirc;
		while (redir)
		{
			if (redir->type == HERE_DOC_IN)
			{
				if (!get_heredoc(redir, i))
					return (0);
				i++;
			}
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (1);
}

int	check_if_heredoc(t_cmd *cmd)
{
	int		nb;
	t_cmd	*curr;
	t_redir	*cur;

	curr = cmd;
	nb = 0;
	while (curr)
	{
		cur = curr->list_redirc;
		while (cur)
		{
			if (cur->type == HERE_DOC_IN)
				nb++;
			cur = cur->next;
		}
		curr = curr->next;
	}
	return (nb);
}
