/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:47:37 by glions            #+#    #+#             */
/*   Updated: 2024/07/13 16:00:04 by glions           ###   ########.fr       */
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

t_block_child	*create_block_child(t_list_gl *env, char **bltn)
{
	t_block_child	*new;

	new = malloc(sizeof(t_block_child));
	if (!new)
		return (NULL);
	new->pid = -1;
	new->status = -1;
	new->main = 0;
	new->last = -1;
	new->bltn = bltn;
	new->env = ft_copy(env);
	if (!new->env)
		return (free_block_child(new), NULL);
	new->redir = 0;
	new->pipe_in = -1;
	new->pipe_out = NULL;
	new->cmds = NULL;
	new->child = NULL;
	new->new_p = 0;
	new->parent = NULL;
	return (new);
}
