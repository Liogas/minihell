/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:53:35 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/14 20:38:42 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_tab_pipes(int **tab_pipes, int n_pipe)
{
	int	i;

	i = 0;
	while (i < n_pipe)
	{
		close(tab_pipes[i][0]);
		close(tab_pipes[i][1]);
		i++;
	}
}

// void	free_fork(int **tab_fork, int n_cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n_cmd) // enlever - 1
// 	{
// 		free(tab_fork[i]);
// 		i++;
// 	}
// 	free(tab_fork);
// }



// void	free_pipes(int **tab, int len)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < len)
// 		free(tab[i]);
// 	free(tab);
// }

// int	free_all(int **tab_pipes, int len, pid_t **f, t_cmd *cmd)
// {
// 	t_cmd	*curr;
// 	t_redir	*redir;

// 	if (f)
// 		free_fork(f, len);
// 	if (tab_pipes)
// 		free_pipes(tab_pipes, len);
// 	if (cmd)
// 	{
// 		curr = cmd;
// 		while (curr)
// 		{
// 			if (cmd->list_redirc)
// 			{
// 				redir = cmd->list_redirc;
// 				while (redir)
// 				{
// 					if (redir->name_heredoc)
// 						free(redir->name_heredoc);
// 					redir = redir->next;
// 				}
// 				if (!close_tmp_file(cmd))
// 					return (0);
// 			}
// 			curr = curr->next;
// 		}
// 	}
// 	return (1);
// }
