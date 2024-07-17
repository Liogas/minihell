/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:22:36 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 13:00:06 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_env(t_list_gl	*env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**gen_env(t_list_gl	*env)
{
	char		**new_env;
	char		*tmp;
	t_node_env	*line;
	int			i;

	new_env = malloc((size_env(env) + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env)
	{
		line = env->content;
		tmp = ft_strjoin(line->name, "=");
		if (!tmp)
			return (ft_split_free(new_env), NULL);
		tmp = ft_strjoin_w_free(tmp, line->value);
		if (!tmp)
			return (ft_split_free(new_env), NULL);
		new_env[i] = tmp;
		env = env->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
