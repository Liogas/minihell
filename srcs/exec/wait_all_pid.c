/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:06:03 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 11:44:28 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_all_child(t_process *curr_p)
{
	t_list_gl		*child;
	t_list_gl		*tmp;
	t_process		*dt_child;

	if (!curr_p || !curr_p->childs)
	{
		// printf("process[%d] : ne possede pas de block enfant\n", getpid());
		return ;
	}
	child = curr_p->childs;
	while (child)
	{
		dt_child = child->content;
		waitpid(dt_child->pid, &curr_p->status, 0);
		// printf("process[%d] : l'enfant[%d] s'est terminé avec pour status->%d\n",
			// getpid(), dt_child->pid, curr_p->status);
		// close_process(dt_child, NULL, 0);
		tmp = child->next;
		free_process(&dt_child, 0);
		free(child);
		child = tmp;
	}
	curr_p->childs = NULL;
}

static void	wait_all_cmds(t_process *curr_p)
{
	t_list_gl	*child;
	t_list_gl	*tmp;
	t_cmd		*dt_cmd;

	if (!curr_p || !curr_p->cmds)
	{
		// printf("process[%d] : ne possede pas de cmd enfant\n", getpid());
		return ;
	}
	child = curr_p->cmds;
	while (child)
	{
		dt_cmd = child->content;
		while (dt_cmd)
		{
			waitpid(dt_cmd->pid, &curr_p->status, 0);
			dt_cmd = dt_cmd->next;
			// printf("process[%d] : attente d'une cmd s'est terminée avec pour status->%d\n",
				//    getpid(), curr_p->status);
		}
		// close_cmd(dt_cmd);
		tmp = child->next;
		free_element_gl(&curr_p->cmds, &free_cmd, child);
		child = tmp;
	}
	curr_p->cmds = NULL;
}

void	wait_all_pid(t_process *curr_p)
{
	// printf("process[%d] : Un process attend la fin de ses enfants\n", getpid());
	if (!curr_p->cmds && !curr_p->childs)
	{
		// printf("process[%d] : Aucun enfant a attendre\n", getpid());
		return ;
	}
	else if (!curr_p->utils.last)
		(wait_all_cmds(curr_p), wait_all_child(curr_p));
	else
		(wait_all_child(curr_p), wait_all_cmds(curr_p));
	// printf("process[%d] : Valeur du status->%d\n", getpid(), curr_p->status);
}
