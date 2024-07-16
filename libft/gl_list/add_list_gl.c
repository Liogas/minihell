/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_gl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:28:04 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:45:46 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_list.h"

int	addback_list_gl(t_list_gl **list, t_list_gl *element)
{
	t_list_gl	*tmp;

	if (!list || !element)
		return (0);
	if (!*list)
		*list = element;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = element;
	}
	return (1);
}

int	addfront_list_gl(t_list_gl **list, t_list_gl *element)
{
	if (!list || !element)
		return (0);
	if (!*list)
		*list = element;
	else
	{
		element->next = *list;
		*list = element;
	}
	return (1);
}

int	addafter_list_gl(t_list_gl **before, t_list_gl *element)
{
	if (!before || !*before || !element)
		return (0);
	element->next = (*before)->next;
	(*before)->next = element;
	return (1);
}

int	addbefore_list_gl(t_list_gl **list, t_list_gl *after, t_list_gl *element)
{
	t_list_gl	*tmp;
	t_list_gl	*before;

	if (!list || !*list || !after || !element)
		return (0);
	if (after->content == (*list)->content)
	{
		element->next = *list;
		*list = element;
		return (1);
	}
	tmp = (*list)->next;
	before = *list;
	while (tmp)
	{
		if (tmp->content == after->content)
		{
			if (!addafter_list_gl(&before, element))
				return (0);
			break ;
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (1);
}
