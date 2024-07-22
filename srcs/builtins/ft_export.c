/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:59:04 by lbegliom          #+#    #+#             */
/*   Updated: 2024/06/04 11:58:46 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	update_value(char **tab, t_node_env *env)
{
	free(tab[0]);
	free(env->value);
	env->value = tab[1];
}

int	update_env(t_list_gl **list, char **tab)
{
	t_list_gl	*curr;
	t_node_env	*node_env;

	curr = *list;
	while (curr != NULL)
	{
		node_env = curr->content;
		if (ft_strcmp(tab[0], node_env->name) == 0)
			break ;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		node_env = malloc(sizeof(t_node_env));
		if (!node_env)
			return (printf("ERROR 4\n"), 0);
		node_env->name = tab[0];
		node_env->value = tab[1];
		if (addback_list_gl(list, new_element_gl(node_env)) == 0)
			return (printf("ERROR 3\n"), free(node_env), 0);
	}
	else
		update_value(tab, node_env);
	return (1);
}

char	**split_env(char *str, char c)
{
	int		i;
	char	**tab;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	tab = malloc(2 * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_strndup(str, i);
	if (!tab[0])
		return (free(tab), NULL);
	tab[1] = ft_strndup(str + i + 1, ft_strlen(str + i + 1));
	if (!tab[1])
		return (free(tab[0]), free(tab), NULL);
	return (tab);
}

int	ft_export(char *str, t_list_gl **list)
{
	char	**tab;

	tab = split_env(str, '=');
	if (!tab)
		return (0);
	if (update_env(list, tab) == 0)
		return (ft_split_free(tab), 0);
	free(tab);
	return (1);
}
