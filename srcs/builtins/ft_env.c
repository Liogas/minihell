/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:51:43 by glions            #+#    #+#             */
/*   Updated: 2024/06/04 10:54:40 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list_gl *list)
{
	t_list_gl	*tmp;
	t_node_env	*tmp2;

	tmp = list;
	while (tmp)
	{
		tmp2 = tmp->content;
		printf("%s=%s\n", tmp2->name, tmp2->value);
		tmp = tmp->next;
	}
}
