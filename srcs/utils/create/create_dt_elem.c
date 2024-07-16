/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dt_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:30:56 by glions            #+#    #+#             */
/*   Updated: 2024/06/24 14:34:16 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_back_elem(t_dt_elem **list, t_dt_elem *new)
{
	t_dt_elem	*tmp;

	tmp = NULL;
	if (!list || !new)
		return (0);
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_dt_elem	*create_dt_elem(char *value, enum e_type type, enum e_state state)
{
	t_dt_elem	*new;

	new = malloc(sizeof(t_dt_elem));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->next = NULL;
	new->value = value;
	new->type = type;
	new->state = state;
	return (new);
}
