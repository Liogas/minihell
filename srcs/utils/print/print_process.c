/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:27:07 by glions            #+#    #+#             */
/*   Updated: 2024/07/15 15:52:46 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds(t_list_gl *cmds)
{
	t_list_gl	*tmp;
	int			n;

	n = 1;
	tmp = cmds;
	while (tmp)
	{
		printf("CMD n°%d\n", n);
		print_cmd((t_cmd *)tmp->content);
		n++;
		tmp = tmp->next;
	}
}

static void	print_childs(t_list_gl *childs)
{
	t_list_gl	*tmp;
	int			n;

	n = 1;
	tmp = childs;
	while (tmp)
	{
		printf("CHILDS n°%d\n", n);
		print_process((t_process *)tmp->content, 0);
		n++;
		tmp = tmp->next;
	}
}

void	print_process(t_process *dt, int mode)
{
	if (dt)
	{
		if (dt->childs)
			print_childs(dt->childs);
		if (dt->cmds)
			print_cmds(dt->cmds);
		if (dt->pipe_in)
			printf("PIPE_IN[%d]\n", dt->pipe_in[0]);
		if (dt->pipe_out)
			printf("PIPE_OUT[%d;%d]\n", dt->pipe_out[0], dt->pipe_out[1]);
		printf("PID->%d; STATUS->%d\n", dt->pid, dt->status);
		if (mode && dt->parent)
			(printf("PARENT :\n"), print_process(dt->parent, 1));
		printf("\n");
	}
}
