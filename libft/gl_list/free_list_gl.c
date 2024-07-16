/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_gl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:12:32 by glions            #+#    #+#             */
/*   Updated: 2024/07/10 20:14:08 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_list.h"

void	free_list_gl(t_list_gl **list, void (*del)(void *))
{
	t_list_gl	*tmp;

	tmp = NULL;
	while (*list)
	{
		if ((*list)->content && del)
			del((*list)->content);
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_element_gl(t_list_gl **list, void (*del)(void *),
		t_list_gl *element)
{
	t_list_gl	*tmp;
	t_list_gl	*before;

	if (!list || !*list || !element)
		return ;
	if ((*list)->content == element->content)
		*list = element->next;
	else
	{
		before = *list;
		tmp = (*list)->next;
		while (tmp)
		{
			if (tmp->content == element->content)
				before->next = tmp->next;
			else
				before = tmp;
			tmp = tmp->next;
		}
	}
	if (del)
		del(element->content);
	free(element);
}
