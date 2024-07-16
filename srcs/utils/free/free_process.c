/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:41:15 by glions            #+#    #+#             */
/*   Updated: 2024/07/15 17:46:49 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_childs(t_process **dt)
{
	t_list_gl	*tmp;

	if ((*dt)->childs)
	{
		tmp = (*dt)->childs;
		while ((*dt)->childs)
		{
			tmp = (*dt)->childs->next;
			free_process((t_process **)&(*dt)->childs->content, 0);
			free((*dt)->childs);
			(*dt)->childs = tmp;
		}
	}
	(*dt)->childs = NULL;
}

void	free_process(t_process **dt, int mode)
{
	t_process	*main;

	if (dt && *dt)
	{
		main = *dt;
		if (mode)
			while (main && main->parent)
				main = main->parent;
		free_childs(&main);
		if (main->utils.close_in && main->pipe_in)
			free(main->pipe_in);
		if (main->pipe_out)
			free(main->pipe_out);
		if (main->cmds)
			free_list_gl(&main->cmds, &free_cmd);
		main->cmds = NULL;
		if (main->env)
			free_list_gl(&main->env, &free_node_env);
		main->env = NULL;
		free(main);
		*dt = NULL;
	}
}
