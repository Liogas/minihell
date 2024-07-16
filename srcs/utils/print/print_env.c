/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:11:44 by glions            #+#    #+#             */
/*   Updated: 2024/06/05 14:14:17 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list_gl	*env)
{
	t_list_gl	*tmp;
	t_node_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->content;
		printf("%s:%s\n", tmp2->name, tmp2->value);
		tmp = tmp->next;
	}
}
