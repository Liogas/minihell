/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:42:02 by glions            #+#    #+#             */
/*   Updated: 2024/07/15 15:52:57 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list_gl	*ft_copy(t_list_gl *src)
{
	t_list_gl	*new;
	t_list_gl	*tmp;
	t_list_gl	*head;

	head = NULL;
	while (src)
	{
		tmp = malloc(sizeof(t_list_gl));
		if (!tmp)
			return (free_list_gl(&head, &free_node_env), NULL);
		tmp->content = dup_node_env(src->content);
		if (!tmp->content)
			return (free_list_gl(&head, &free_node_env), free(tmp), NULL);
		tmp->next = NULL;
		if (!head)
			head = tmp;
		else
			new->next = tmp;
		new = tmp;
		src = src->next;
	}
	return (head);
}

void	init_utils(t_process_utils *utils)
{
	utils->last = -1;
	utils->new_p = 0;
	utils->redir = -1;
	utils->close_in = 0;
}

t_process	*create_process(char **bltn, t_list_gl *env, t_process *parent)
{
	t_process	*new;

	new = malloc(sizeof(t_process));
	if (!new)
		return (NULL);
	new->pid = -1;
	new->status = 0;
	new->bltn = bltn;
	new->parent = parent;
	new->env = ft_copy(env);
	if (!new->env)
		return (free(new), NULL);
	new->childs = NULL;
	new->cmds = NULL;
	new->pipe_in = NULL;
	new->pipe_out = NULL;
	init_utils(&new->utils);
	return (new);
}
