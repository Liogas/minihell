/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 03:00:34 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 16:19:03 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->name_file)
			free(redir->name_file);
		if (redir->name_heredoc)
			free(redir->name_heredoc);
		free(redir);
		redir = next;
	}
}

static void	free_tab_pipes(int ***tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free((*tab)[i]);
	free(*tab);
	*tab = NULL;
}

void	free_cmd(void *param)
{
	t_cmd		*dt;
	static int	n;

	n++;
	dt = param;
	if (dt)
	{
		if (dt->list_redirc)
			free_redir(dt->list_redirc);
		if (dt->tab_opt)
			ft_split_free(dt->tab_opt);
		if (dt->tab_pipes && n == 1)
			free_tab_pipes(&dt->tab_pipes, dt->utils.n_pipe);
		if (dt->tab_fd)
			free_fd(dt);
		if (dt->next)
			free_cmd(dt->next);
		else
			n = 0;
		free(dt);
	}
}
