/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dt_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:13:24 by glions            #+#    #+#             */
/*   Updated: 2024/06/25 11:43:15 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dt_elem(t_dt_elem *elem)
{
	t_dt_elem	*tmp;
	int			i;

	if (!elem)
		printf("Pas de token\n");
	tmp = elem;
	i = 0;
	while (tmp)
	{
		printf("[%d] -> [%s] [%d] [%d]\n", i, tmp->value, tmp->state,
			tmp->type);
		if (tmp->content)
		{
			printf("CONTENT:\n");
			print_dt_elem(tmp->content);
			printf("------------------\n");
		}
		tmp = tmp->next;
		i++;
	}
}
