/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:21:37 by glions            #+#    #+#             */
/*   Updated: 2024/07/16 15:28:18 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_oprt_redirct(char ***op, char ***re)
{
	*op = malloc(sizeof(char *) * 2);
	if (!*op)
		return (0);
	(*op)[0] = "|";
	(*op)[1] = NULL;
	*re = malloc(sizeof(char *) * 5);
	if (!*re)
		return (0);
	(*re)[0] = "<";
	(*re)[1] = ">";
	(*re)[2] = ">>";
	(*re)[3] = "<<";
	(*re)[4] = NULL;
	return (1);
}

static char	**init_paths(void)
{
	char	*stock;
	char	**tab;

	stock = getenv("PATH");
	if (!stock)
		return (NULL);
	tab = ft_split(stock, ':');
	if (!tab)
		return (NULL);
	return (tab);
}

// static char	**init_builtins(void)
// {
// 	char	**tab;

// 	tab = malloc(8 * sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	tab[0] = "echo";
// 	tab[1] = "cd";
// 	tab[2] = "pwd";
// 	tab[3] = "export";
// 	tab[4] = "unset";
// 	tab[5] = "env";
// 	tab[6] = "exit";
// 	tab[7] = NULL;
// 	return (tab);
// }

t_check	*create_check(void)
{
	t_check	*new;

	new = malloc(sizeof(t_check));
	if (!new)
		return (NULL);
	new->oprt = NULL;
	new->line_cmd = NULL;
	new->paths = NULL;
	new->redirct = NULL;
	// new->bltn = init_builtins();
	// if (!new->bltn)
		// return (free(new), NULL);
	if (!init_oprt_redirct(&new->oprt, &new->redirct))
		return (free_check(new), NULL);
	new->paths = init_paths();
	if (!new->paths)
		return (free_check(new), NULL);
	new->curr_state = GENERAL;
	new->new_command = 1;
	new->wait_file = 0;
	new->dup2 = 1;
	return (new);
}
