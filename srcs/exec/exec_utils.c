/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbegliom <lbegliom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:51:28 by lbegliom          #+#    #+#             */
/*   Updated: 2024/07/11 12:54:36 by lbegliom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirc(t_redir *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	count_pipe(t_cmd *cmd, int *n_pipe)
{
	t_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->next)
			(*n_pipe)++;
		curr = curr->next;
	}
	return (*n_pipe);
}

int	nb_cmd(t_cmd *cmd)
{
	int		size;
	t_cmd	*curr;

	size = 0;
	curr = cmd;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

int	**init_tab_fd(t_cmd *curr_cmd, int ***fd)
{
	int	n_redirc;
	int	i;

	i = 0;
	n_redirc = count_redirc(curr_cmd->list_redirc);
	*fd = malloc(sizeof(int *) * n_redirc);
	if (!*fd)
		return (NULL);
	while (i < n_redirc)
	{
		(*fd)[i] = malloc(sizeof(int));
		if (!(*fd)[i])
			return (0);
		i++;
	}
	return (*fd);
}

int	**init_tab_pipes(int n_pipe, int ***tab)
{
	int	i;

	i = 0;
	*tab = malloc(sizeof(int *) * n_pipe);
	if (!*tab)
		return (NULL);
	while (i < n_pipe)
	{
		(*tab)[i] = malloc(sizeof(int) * 2);
		if (!(*tab)[i])
			return (NULL);
		i++;
	}
	i = 0;
	while (i < n_pipe)
	{
		if (pipe((*tab)[i]) == -1)
			return (perror("pipe"), NULL);
		i++;
	}
	return (*tab);
}

// pid_t	**init_tab_fork(pid_t ***f, int n_cmd)
// {
// 	int	i;

// 	i = 0;
// 	*f = malloc(sizeof(pid_t *) * n_cmd);
// 	if (!*f)
// 		return (NULL);
// 	while (i < n_cmd)
// 	{
// 		(*f)[i] = malloc(sizeof(pid_t));
// 		if (!(*f)[i])
// 			return (NULL);
// 		i++;
// 	}
// 	return (*f);
// }
