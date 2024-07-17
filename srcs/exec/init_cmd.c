/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glions <glions@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 03:12:22 by glions            #+#    #+#             */
/*   Updated: 2024/07/17 15:25:03 by glions           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_redir(t_cmd *cmd)
{
	int		i;
	int		k;
	int		j;
	char	**new_opt;

	i = -1;
	while (cmd->tab_opt[++i])
	{
		if (!ft_strncmp(cmd->tab_opt[i], "<<", 2) || !ft_strncmp(cmd->tab_opt[i], "<", 1)  || !ft_strncmp(cmd->tab_opt[i], ">>", 2) || !ft_strncmp(cmd->tab_opt[i], ">", 1))
		{
			free(cmd->tab_opt[i]);
			cmd->tab_opt[i] = NULL;
		}
	}
	k = 0;
	j = i;
	printf("Valeur de i->%d\n", i);
	while (--j >= 0)
		if (cmd->tab_opt[j])
			k++;
	printf("Options restantes->%d\n", k);
	new_opt = malloc((k + 1) * sizeof(char *));
	if (!new_opt)
		return (0);
	j = -1;
	k = 0;
	while (++j < i)
	{
		if (cmd->tab_opt[j])
		{
			new_opt[k] = cmd->tab_opt[j];
			k++;
		}
	}
	new_opt[k] = NULL;
	free(cmd->tab_opt);
	cmd->tab_opt = new_opt;
	return (1);
}


static void	add_list_cmd(t_cmd *list, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

static int	check_next_token(t_dt_elem **tokens, t_cmd **new_c)
{
	t_cmd	*cmd;

	while (*tokens && (*tokens)->type == PIPE_LINE)
	{
		*tokens = (*tokens)->next;
		cmd = create_cmd(tokens);
		if (!cmd)
			return (0);
		remove_redir(cmd);
		add_list_cmd(*new_c, cmd);
	}
	return (1);
}

int	init_cmd(t_dt_elem **tokens, t_cmd **new_c)
{
	*new_c = create_cmd(tokens);
	if (!remove_redir(*new_c))
		return (0);
	if (!*new_c)
		return (0);
	if (!check_next_token(tokens, new_c))
		return (free_cmd(*new_c), 0);
	return (1);
}
