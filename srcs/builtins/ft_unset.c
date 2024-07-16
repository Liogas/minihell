/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:04:59 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:28:53 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_gl	*get_node_env(t_list_gl *list, char *name)
{
	t_list_gl	*tmp;
	t_node_env	*node;

	tmp = list;
	while (tmp)
	{
		node = tmp->content;
		if (ft_strcmp(node->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_unset(t_list_gl **list, char *name)
{
	t_list_gl	*element;

	element = get_node_env(*list, name);
	if (!element)
		return (0);
	free_element_gl(list, &free_node_env, element);
	return (1);
}
